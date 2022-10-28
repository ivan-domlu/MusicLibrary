#include "WebServer.h"
#include "Eval.h"
#include "DLists.h"

#include <fstream>

using namespace std;

struct USER {
    string username;
    string id;    
};

USER user;
DList gLista = DList();
string gPath = "";
string username = "";

string fnGetTemplate(string pName)
{
    string lContent = "";

    string lPath = KS_Path + pName;
    ifstream lStream(lPath);
    stringstream lBuff;
    lBuff << lStream.rdbuf();
    lContent = lBuff.str();

    return lContent;
} // fnGetTemplate

strVec fnGetPath(string pCaller)
{
    strVec lParts;
    strVec lSects;
    strVec lPath;

    strSplit(pCaller, '?', lParts);
    if (lParts.size() == 0)
        lParts.push_back(pCaller);
    if (lParts.size() > 0) {
        strSplit(lParts[0], ':', lSects);
        if (lSects.size() >= 3)
            strSplit(lSects[2], '/', lPath);
    }

    return lPath;
} // fnGetPath

map<string, string> fnGetParams(string pCaller)
{
    strVec lParts;
    strVec lPrms;
    strVec lItem;
    map<string, string> lParams;

    strSplit(pCaller, '?', lParts);
    if (lParts.size() == 2) {
        strSplit(lParts[1], '&', lPrms);
        if (lPrms.size() > 0) {
            for (int lIdx = 0; lIdx < lPrms.size(); lIdx++) {
                strSplit(lPrms[lIdx], '=', lItem);
                if (lItem.size() == 2)
                    lParams.insert(pair<string, string>(lItem[0], lItem[1]));
                else
                    lParams.insert(pair<string, string>(lItem[0], ""));
                lItem.clear();
            }
        }
    }

    return lParams;
} // fnGetParams

string fnGetIndexedEP(void)
{
    string lRes = fnGetTemplate("user.tpl.html");
    strReplace(lRes, "{{username}}", username);
    strReplace(lRes, "{{pData}}", "");

    return lRes;
} // fnGetIndexedEP

string fnGetIndexedRP(ECampos pCampo)
{
    string lHTML = "";
    PDATA lData = NULL;
    int lRow = 0;
    string lColor = "";
    while (lData = gLista.get(pCampo)) {
        lColor = "";
        if (lRow % 2 == 0)
            lColor = "background-color:#E0E0E0;";
        lHTML += "<div class='row' style='" + lColor + "'>\n";
        lHTML += "<div class='col-md-3'>\n" + lData->sNombre + "</div>";
        lHTML += "<div class='col-md-3'>\n" + lData->sApellido + "</div>";
        lHTML += "<div class='col-md-2'>\n" + lData->sFNac + "</div>";
        lHTML += "<div class='col-md-2'>\n" + to_string(lData->sSalario) + "</div>";
        lHTML += "<div class='col-md-2'>\n<a href='/indexada?borrar=" + to_string(lData->sID) + "'>[ Borrar (" + to_string(lData->sID) + ")]</a></div>";
        lHTML += "</div>";
        lRow++;
    }

    string lRes = fnGetTemplate("indexed.tpl.html");
    strReplace(lRes, "{{pData}}", lHTML);

    return lRes;
} // fnGetIndexedRP


string fnIndexedLists(string pCaller)
{
    string lRes = "NoFile";

    map<string, string> lParams = fnGetParams(pCaller);
    if (lParams["nombre"] != "") {
        gLista.push_back(lParams["nombre"], lParams["apellido"], lParams["fnac"], stod(lParams["salario"]));
        gLista.resetCurr();
        gLista.write(gPath);
        lRes = fnGetIndexedRP(ECampos::nombre);
    }
    else if (lParams["orden"] != "") {
        lRes = fnGetIndexedRP((ECampos)(stoi(lParams["orden"])));
    }
    else if (lParams["borrar"] != "") {
        gLista.del(stol(lParams["borrar"]));
        gLista.resetCurr();
        gLista.write(gPath);
        lRes = fnGetIndexedRP(ECampos::nombre);
    }
    else
        lRes = fnGetIndexedRP(ECampos::nombre);
    //lRes = fnGetIndexedEP();

    return lRes;
} // fnIndexedLists


string fnPlayer(string pCaller)
{
    string lRes = "NoFile";
    
    lRes = fnGetTemplate("player.tpl.html");

    return lRes;
}

string fnGetValidationEP()
{
    string lRes = fnGetTemplate("init.tpl.html");
    strReplace(lRes, "{{pData}}", "");

    return lRes;
} // fnGetValidationEP

string fnGetValidationRP(string alert)
{
    string lRes = fnGetTemplate("init.tpl.html");
    string lHTML = "<p class='alerta'>" + alert + "<p/>";
    strReplace(lRes, "{{pData}}", lHTML);

    return lRes;
} // fnGetValidationRP

string fnValidation(string pCaller)
{
    string pPath = KS_Path;
    CSVReader lector(pPath + "usuarios.csv");
    TCSVTbl lTbl = lector.read();

    map<string, string> lParams = fnGetParams(pCaller);

    string lRes = "";

    if (lTbl.size() > 0) {
        for (size_t i = 0; i < lTbl.size(); i++) {
            if (lParams["usuario"] == lTbl[i][0])
            {
                if (lParams["contrasena"] == lTbl[i][1])
                {
                    username = lTbl[i][0];
                    lRes = fnGetIndexedEP();
                    return lRes;
                }
                else
                {
                    lRes = fnGetValidationRP("Contraseña incorrecta");
                    return lRes;
                }
                break;
            }
        }
        lRes = fnGetValidationRP("El usuario no existe");
    }

    return lRes;
} // fnValidation

string fnGetFuncS(string pCaller)
{
    string lRes = "NoFile";

    if (pCaller != "http://localhost:8080/favicon.ico") {

        strVec lPath = fnGetPath(pCaller);
        if (lPath.size() > 1) {
            cout << "Path: " << lPath[1] << endl;
            if (lPath[1] == "userV")
                lRes = fnValidation(pCaller);
            else if (lPath[1] == "indexada")
                lRes = fnIndexedLists(pCaller);
            else if (lPath[1] == "player")
                lRes = fnPlayer(pCaller);
            else
                lRes = fnGetValidationEP();
        }
        else
            lRes = fnGetValidationEP();
    }

    return lRes;
} // fnGetFuncS


int main()
{
    /*gPath = KS_Path;
    gPath += "bibliotecaGeneral.csv";
    gLista.read(gPath);*/

    MyHTTPSrv lSrv = MyHTTPSrv(NULL, NULL);
    lSrv.SetGetFunc(&fnGetFuncS);
    lSrv.Run();

} // main
