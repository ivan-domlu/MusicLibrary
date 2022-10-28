#include "DLists.h"

//int main()
//{
//	DList lLista = DList();
//
//	/*lLista.read("users.csv");*/
//
//	lLista.push_back("Clark", "Kent", "1938-04-18", 100);
//	lLista.push_back("Bruno", "Diaz", "1939-03-30", 5500);
//	lLista.push_back("Diana", "Prince", "1941-01-01", 500);
//
//
//	cout << "Datos organizados por nombre: " << endl;
//	lLista.repr(ECampos::nombre);
//
//	cout << endl << "Datos organizados por fecha: " << endl;
//	PDATA lItem = NULL;
//	while (lItem = lLista.get(ECampos::fnac)) {
//		cout << lItem->sNombre << " " << lItem->sApellido << " " << lItem->sFNac << " " << lItem->sSalario << endl;
//	}
//
//	cout << endl << "Datos organizados por salario (desc): " << endl;
//	while (lItem = lLista.get(ECampos::salario, true)) {
//		cout << lItem->sNombre << " " << lItem->sApellido << " " << lItem->sFNac << " " << lItem->sSalario << endl;
//	}
//
//	lLista.write("users.csv");
//
//}