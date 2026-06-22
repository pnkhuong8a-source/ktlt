#ifndef KETQUA_H
#define KETQUA_H

#include "vector.h"
#include "constants.h"

extern Vector<KetQuaThi> dsKetQua;

void thiTracNghiem(const char* username);
void xemKetQuaHocSinh(const char* username);
void xemKetQuaGiaoVien();
void docFileKetQua();
void ghiFileKetQua();
void sapXepKetQuaTheoThoiGian();

#endif