#include "DList.h"

DLIndex::DLIndex(ECampos pType) {
    
}

DLIndex::~DLIndex(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DLIndex::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DLIndex::push_front(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        PDNODE lTemp = getNewNode(pData);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }
} // push_front

void DLIndex::push_back(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        PDNODE lTemp = getNewNode(pData);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
} // push_back

void DLIndex::push(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        if (comp(pData, aHead->sData) <= 0)
            push_front(pData);
        else if (comp(pData, aTail->sData) >= 0)
            push_back(pData);
        else {
            PDNODE lItem = search(pData);
            if (lItem) {
                PDNODE lTemp = getNewNode(pData);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
} // push

PDATA DLIndex::get(bool pRev)
{
    PDATA lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL)
            aCurr = (pRev == false ? aHead : aTail);
        else
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        if (aCurr)
            lTemp = aCurr->sData;
    }

    return lTemp;
} // get

void DLIndex::resetCurr(void)
{
    aCurr = NULL;
} // resetCurr

void DLIndex::pop_front(void)
{
    if (aHead) {
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;
        if (aHead) {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
        else {
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DLIndex::pop_back(void)
{
    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

void DLIndex::del(PDATA pData)
{
    if (aHead) {
        if (aHead->sData == pData)
            pop_front();
        else if (aTail->sData == pData)
            pop_back();
        else {
            PDNODE lTemp = find(pData);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }
} // del

bool DLIndex::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DLIndex::repr(bool pRev)
{
    if (aHead) {
        PDNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " -> ";
            if (lTemp->sData) {
                cout << "[(" << lTemp->sData->sID;
                cout << ") " << lTemp->sData->sCancion;
                cout << ", " << lTemp->sData->sArtista;
                cout << ", " << lTemp->sData->sAlbum;
                cout << ", " << lTemp->sData->sFLanz << "]";
            }
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " ->|| " << endl;
    }
} // repr

PDNODE DLIndex::search(string pVal)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pVal, lTemp->sData) <= 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::search(unsigned long int pID)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pID <= lTemp->sData->sID)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::find(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pData == lTemp->sData)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PDNODE DLIndex::search(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pData, lTemp->sData) <= 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::getNewNode(PDATA pData)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sData = pData;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode

int DLIndex::comp(PDATA pA, PDATA pB)
{
    int lRes = 0;

    switch (aType) {
    case ECampos::index:
        if (pA->sID < pB->sID) lRes = -1;
        else if (pA->sID == pB->sID) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::cancion:
        if (pA->sCancion < pB->sCancion) lRes = -1;
        else if (pA->sCancion == pB->sCancion) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::artista:
        if (pA->sArtista < pB->sArtista) lRes = -1;
        else if (pA->sArtista == pB->sArtista) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::album:
        if (pA->sAlbum < pB->sAlbum) lRes = -1;
        else if (pA->sAlbum == pB->sAlbum) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::flanz:
        if (pA->sFLanz < pB->sFLanz) lRes = -1;
        else if (pA->sFLanz == pB->sFLanz) lRes = 0;
        else lRes = 1;
        break;
    }

    return lRes;
} // comp

int DLIndex::comp(string pVal, PDATA pB)
{
    int lRes = 0;
    unsigned long int lValI = 0;
    double lValD = 0;

    switch (aType) {
    case ECampos::index:
        lValI = stol(pVal);
        if (lValI < pB->sID) lRes = -1;
        else if (lValI == pB->sID) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::cancion:
        if (pVal < pB->sCancion) lRes = -1;
        else if (pVal == pB->sCancion) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::artista:
        if (pVal < pB->sArtista) lRes = -1;
        else if (pVal == pB->sArtista) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::album:
        if (pVal < pB->sAlbum) lRes = -1;
        else if (pVal == pB->sAlbum) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::flanz:
        if (pVal< pB->sFLanz) lRes = -1;
        else if (pVal == pB->sFLanz) lRes = 0;
        else lRes = 1;
        break;
    }

    return lRes;
} // comp


//---------------


DList::DList(void)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;

    aCurrID = 0;

    aID = new DLIndex(ECampos::index);
    aCancion = new DLIndex(ECampos::cancion);
    aArtista = new DLIndex(ECampos::artista);
    aAlbum = new DLIndex(ECampos::album);
    aFLanz = new DLIndex(ECampos::flanz);
} // Constructor

DList::~DList(void)
{
    delete aID;
    delete aCancion;
    delete aArtista;
    delete aAlbum;
    delete aFLanz;

    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DList::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        if (aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DList::push_back(string pCancion, string pArtista,
    string pAlbum, string pFLanz)
{
    if (aHead == NULL) {
        aHead = getNewNode(pCancion, pArtista, pAlbum, pFLanz);
        aTail = aHead;

        aID->push(aHead->sData);
        aCancion->push(aHead->sData);
        aArtista->push(aHead->sData);
        aAlbum->push(aHead->sData);
        aFLanz->push(aHead->sData);
    }
    else {
        PDNODE lTemp = getNewNode(pCancion, pArtista, pAlbum, pFLanz);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;

        aID->push(lTemp->sData);
        aCancion->push(lTemp->sData);
        aArtista->push(lTemp->sData);
        aAlbum->push(lTemp->sData);
        aFLanz->push(lTemp->sData);
    }
} // push_back

PDATA DList::get(ECampos pCampo, bool pRev)
{
    PDATA lTemp = NULL;

    switch (pCampo) {
    case ECampos::index: lTemp = aID->get(pRev); break;
    case ECampos::cancion: lTemp = aCancion->get(pRev); break;
    case ECampos::artista: lTemp = aArtista->get(pRev); break;
    case ECampos::album: lTemp = aAlbum->get(pRev); break;
    case ECampos::flanz: lTemp = aFLanz->get(pRev); break;
    }

    return lTemp;
} // get

void DList::resetCurr(void)
{
    aID->resetCurr();
    aCancion->resetCurr();
    aArtista->resetCurr();
    aAlbum->resetCurr();
    aFLanz->resetCurr();
} // resetCurr

void DList::del(string pCancion, string pArtista, string pAlbum, string pFLanz)
{
    if (aHead) {
        PDNODE lItem = find(pCancion, pArtista, pAlbum, pFLanz);
        if (lItem) {
            del(lItem->sData);
        }
    }
} // del

void DList::del(unsigned int pID)
{
    if (aHead) {
        PDNODE lItem = aID->search(pID);
        if (lItem && (lItem->sData->sID == pID)) {
            del(lItem->sData);
        }
    }
} // del

bool DList::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DList::repr(ECampos pCampo, bool pRev)
{
    switch (pCampo) {
    case ECampos::index: aID->repr(pRev); break;
    case ECampos::cancion: aCancion->repr(pRev); break;
    case ECampos::artista: aArtista->repr(pRev); break;
    case ECampos::album: aAlbum->repr(pRev); break;
    case ECampos::flanz: aFLanz->repr(pRev); break;
    }
} // repr

void DList::read(string pPath)
{
    CSVReader lReader = CSVReader(pPath);

    TCSVTbl lTbl = lReader.read();

    if (lTbl.size() > 0) {
        for (size_t lCol = 0; lCol < lTbl.size(); lCol++) {
            push_back(lTbl[lCol][0], lTbl[lCol][1], lTbl[lCol][2], lTbl[lCol][3]);
        }
    }
} // read

void DList::write(string pPath)
{
    if (aHead) {
        CSVWriter lWriter = CSVWriter(pPath);
        PDNODE lTemp = aHead;
        while (lTemp) {
            lWriter.write(lTemp->sData->sCancion);
            lWriter.write(lTemp->sData->sArtista);
            lWriter.write(lTemp->sData->sAlbum);
            lWriter.write(lTemp->sData->sFLanz);
            lWriter.writeeol();
            lTemp = lTemp->sNext;
        }
    }
} // write

void DList::pop_front(void)
{
    if (aHead) {
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        if (aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
        if (aHead) {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
        else {
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DList::pop_back(void)
{
    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        if (aTail->sData)
            delete aTail->sData;
        delete aTail;
        aTail = lTemp;
        if (aTail) {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

void DList::del(PDATA pData)
{
    if (pData) {
        aID->del(pData);
        aCancion->del(pData);
        aArtista->del(pData);
        aAlbum->del(pData);
        aFLanz->del(pData);

        PDNODE lItem = find(pData);
        if (lItem) {
            if (lItem == aHead)
                pop_front();
            else if (aTail == lItem)
                pop_back();
            else {
                if (aCurr == lItem)
                    aCurr = lItem->sNext;
                lItem->sPrev->sNext = lItem->sNext;
                lItem->sNext->sPrev = lItem->sPrev;
                if (lItem->sData)
                    delete lItem->sData;
                delete lItem;
            }
        }
    }
} // del

PDNODE DList::find(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pData == lTemp->sData)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PDNODE DList::find(string pCancion, string pArtista, string pAlbum, string pFLanz)
{
    PDNODE lItem = aCancion->search(pCancion);

    if (lItem && (lItem->sData->sCancion == pCancion)) {
        bool lFound = false;
        do {
            PDATA lData = lItem->sData;
            if (lData->sCancion == pCancion) {
                if (
                    (lData->sArtista == pArtista) &&
                    (lData->sAlbum == pAlbum) &&
                    (lData->sFLanz == pFLanz)
                    )
                    lFound = true;
                if (lFound == false)
                    lItem = lItem->sNext;
            }
            else {
                lItem = NULL;
            }
        } while (lItem && (lFound == false));
        if (lFound == false)
            lItem = NULL;
    }
    else {
        lItem = NULL;
    }

    return lItem;
} // find

PDNODE DList::getNewNode(string pCancion, string pArtista,
    string pAlbum, string pFLanz)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sData = new DATA;
        if (lTemp->sData) {
            aCurrID++;
            lTemp->sData->sID = aCurrID;
            lTemp->sData->sCancion = pCancion;
            lTemp->sData->sArtista = pArtista;
            lTemp->sData->sAlbum = pAlbum;
            lTemp->sData->sFLanz = pFLanz;
        }
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode