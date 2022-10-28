#include "Eval.h"

void strToLower(string& pData)
{
    transform(pData.begin(), pData.end(), pData.begin(),
        [](unsigned char c) {
            return tolower(c);
        }
    );
} // strToLower

void strReplace(string& pStr, string pSearch, string pReplace)
{
    size_t lPos = 0;

    while ((lPos = pStr.find(pSearch)) != std::string::npos) {
        pStr.replace(lPos, pSearch.length(), pReplace);
    }
} // strReplace