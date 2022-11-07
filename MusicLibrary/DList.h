#pragma once

//#ifndef __dlists_h_
//#define __dlists_h_

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "CSV.h"

using namespace std;

typedef struct DNODE* PDNODE;

typedef struct DATA* PDATA;

struct DATA {
    unsigned int sID;
    string sCancion;
    string sArtista;
    string sAlbum;
    string sFLanz;
};

struct DNODE {
    PDATA sData;
    PDNODE sPrev;
    PDNODE sNext;
};

enum class ECampos { index, cancion, artista, album, flanz };

class DLIndex
{
protected:
    ECampos aType;
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;

public:
    DLIndex(ECampos pType);
    ~DLIndex(void);

    void clean(void);

    void push_front(PDATA pData);
    void push_back(PDATA pData);
    void push(PDATA pData);

    PDATA get(bool pRev = false);
    void resetCurr(void);

    void pop_front(void);
    void pop_back(void);
    void del(PDATA pData);

    bool isEmpty(void);
    void repr(bool pRev = false);

    PDNODE search(string pVal);
    PDNODE search(unsigned long int pID);

private:
    PDNODE find(PDATA pData);
    PDNODE search(PDATA pData);
    PDNODE getNewNode(PDATA pData);
    int comp(PDATA pA, PDATA pB);
    int comp(string pVal, PDATA pB);
};

class DList
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;

    unsigned long int aCurrID;

    DLIndex* aID;
    DLIndex* aCancion;
    DLIndex* aArtista;
    DLIndex* aAlbum;
    DLIndex* aFLanz;

public:
    DList(void);
    ~DList(void);

    void clean(void);

    void push_back(string pCancion, string pArtista, string pAlbum, string pFLanz);

    PDATA get(ECampos pCampo, bool pRev = false);
    void resetCurr(void);

    void del(string pCancion, string pArtista, string pAlbum, string pFLanz);
    void del(unsigned int pID);

    bool isEmpty(void);
    void repr(ECampos pCampo, bool pRev = false);
    void read(string pPath);
    void write(string pPath);

private:
    void pop_front(void);
    void pop_back(void);
    void del(PDATA pData);
    PDNODE find(PDATA pData);
    PDNODE find(string pCancion, string pArtista, string pAlbum, string pFLanz);
    PDNODE getNewNode(string pCancion, string pArtista, string pAlbum, string pFLanz);
};

//#endif