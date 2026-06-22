#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include "utility.h"

#ifdef _WIN32
    #include <windows.h>   // chỉ dùng Sleep nếu cần (nhưng hiện không dùng)
#else
    #include <sys/select.h>
    #include <sys/time.h>
    #include <termios.h>
    #include <unistd.h>
#endif
//Trộn ngẫu nhiên mảng số nguyên, thuật toán Fisher-Yates Shuffle
void shuffleInt(int* arr, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);   //sinh vị trí ngẫu nhiên
        //hoán đổi
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
//xóa \n, \r, khoảng trắng đầu dòng
void trimNewline(char* str) {
    int len = strlen(str);      //độ dài str
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) { //Nếu cuối chuỗi là \n hoặc \r thì xóa
        str[len-1] = '\0';      //cắt chuỗi tại vị trí đó
        len--;      //cập nhật độ dài
    }
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t') start++; // bỏ qua dấu cách và tab
    //dồn chuỗi về đầu
    if (start > 0) {
        int i = 0;
        while (str[start + i]) {
            str[i] = str[start + i];
            i++;
        }
        str[i] = '\0'; // kết thúc chuỗi
    }
}
//đọc dòng tiếp theo không rỗng trong file
bool docDongKhongRong(FILE* f, char* buffer, int maxLen) {
    while (fgets(buffer, maxLen, f)) {  //Đọc từng dòng
        trimNewline(buffer);        //làm sạch dòng
        if (strlen(buffer) > 0) return true;    //nếu không rỗng => trả về true
    }
    return false; 
}
//tách số nguyên từ chuỗi
int tachSoNguyen(const char* line, int* arr, int max) {
    int count = 0;      //đếm số lượng số 
    const char* p = line;       //con trỏ quét chuỗi
    while (*p) {
        while (*p == ' ' || *p == '\t') p++;    //bỏ qua khoảng trắng 
        if (*p == '\0') break;
        int num = 0;
        bool coSo = false;
        //tạo số
        while (*p >= '0' && *p <= '9') {
            num = num * 10 + (*p - '0');
            coSo = true;
            p++;
        }
        //lưu số vào mảng
        if (coSo && count < max) {
            arr[count++] = num;
        }
        while (*p == ' ' || *p == '\t') p++;
    }
    return count;
}

#ifndef _WIN32
//kiểm tra có phím nào vừa được nhấn chưa
int kbhit() {
    struct timeval tv = {0,0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
//đọc 1 ký tự mà không cần enter
int getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif
