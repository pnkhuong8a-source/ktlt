#ifndef UTILITY_H
#define UTILITY_H

#include <cstdio>

void shuffleInt(int* arr, int n);
void trimNewline(char* str);
bool docDongKhongRong(FILE* f, char* buffer, int maxLen);
int tachSoNguyen(const char* line, int* arr, int max);
//Giúp chương trình chạy được trên nhiều hệ điều hành:))
#ifdef _WIN32
    #include <conio.h>
    #define kbhit _kbhit
    #define getch _getch
#else
    int kbhit();
    int getch();
#endif

#endif