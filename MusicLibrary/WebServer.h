#pragma once

#include "precomp.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

#define KS_Path "wroot/"

//
// Macros.
//
#define INITIALIZE_HTTP_RESPONSE( resp, status, reason )    \
    do                                                      \
    {                                                       \
        RtlZeroMemory( (resp), sizeof(*(resp)) );           \
        (resp)->StatusCode = (status);                      \
        (resp)->pReason = (reason);                         \
        (resp)->ReasonLength = (USHORT) strlen(reason);     \
    } while (FALSE)

#define ADD_KNOWN_HEADER(Response, HeaderId, RawValue)               \
    do                                                               \
    {                                                                \
        (Response).Headers.KnownHeaders[(HeaderId)].pRawValue =      \
                                                          (RawValue);\
        (Response).Headers.KnownHeaders[(HeaderId)].RawValueLength = \
            (USHORT) strlen(RawValue);                               \
    } while(FALSE)

#define ALLOC_MEM(cb) HeapAlloc(GetProcessHeap(), 0, (cb))

#define FREE_MEM(ptr) HeapFree(GetProcessHeap(), 0, (ptr))

#define K_MAX_STR   100

DWORD
SendHttpResponse(
    IN HANDLE        hReqQueue,
    IN PHTTP_REQUEST pRequest,
    IN USHORT        StatusCode,
    IN PSTR          pReason,
    IN PSTR          pEntity
);

DWORD
SendHttpPostResponse(
    IN HANDLE        hReqQueue,
    IN PHTTP_REQUEST pRequest
);

typedef vector <string> strVec;

void strSplit(string& pStr, char pDelim, strVec& pOut);


class MyHTTPSrv {
protected:
    wchar_t aDomain[K_MAX_STR];
    wchar_t aPort[K_MAX_STR];
    wchar_t aURL[2 * K_MAX_STR];

    string(*aGetFuncW)(PCWSTR);
    string(*aGetFuncS)(string);

public:
    MyHTTPSrv(wchar_t* pDomain, wchar_t* pPort);

    void SetGetFunc(string(*pGetFuncW)(PCWSTR));
    void SetGetFunc(string(*pGetFuncS)(string));

    int Run(void);

private:
    DWORD DoReceiveRequests(IN HANDLE hReqQueue);

    DWORD SendHttpResponse(
        IN HANDLE        hReqQueue,
        IN PHTTP_REQUEST pRequest,
        IN USHORT        StatusCode,
        IN PSTR          pReason,
        IN PSTR          pEntityString,
        IN string        pMimeType = "text/html"
    );

    DWORD SendHttpPostResponse(
        IN HANDLE        hReqQueue,
        IN PHTTP_REQUEST pRequest
    );
};


