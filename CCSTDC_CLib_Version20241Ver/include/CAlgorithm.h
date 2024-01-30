#ifndef CUTILS_CALGORITHM_H
#define CUTILS_CALGORITHM_H
#include "CLibUtility.h"
/// Utilities
void CAlg_SwapBuf(void* buf1, void* buf2, void* tmpBuf, Size elemSize);
void CAlg_SwapBufOnce(void* buf1, void* buf2, Size elemSize);

// sorts
void CAlg_BubbleSort(void* begin, Size numSize, Size elemSize, CompareFunc f);

// String Utils
bool CAlg_isCharNum(const char* numString, int how_much);
bool CAlg_isUpperAlphaBit(const char* numString, int how_much);
bool CAlg_isLowerAlphaBit(const char* numString, int how_much);
bool CAlg_isCharAlphaBet(const char* numString, int how_much);

char* CAlg_ToUpperChar(const char* numString, int how_much);
char* CAlg_ToLowerChar(const char* numString, int how_much);

char* CAlg_FromInt2Char(int num);
char* CAlg_FromDouble2Char(double num, int percision);
#endif //CUTILS_CALGORITHM_H
