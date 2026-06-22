#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H

#include "vector.h"
#include "constants.h"

// Khai báo biến toàn cục dsNguoiDung
// extern nghĩa là biến này được định nghĩa ở file .cpp khác
// Các file include header này đều có thể sử dụng nó
extern Vector<NguoiDung> dsNguoiDung;

void dangKyHocSinh();
bool dangNhap(char* username, int& vaiTro);
void docFileNguoiDung();
void ghiFileNguoiDung();

#endif