#ifndef CAUHOI_H
#define CAUHOI_H

#include "vector.h"
#include "constants.h"

extern Vector<CauHoi> dsCauHoi;
extern int nextCauHoiID;

void themCauHoiThuCong();
void themCauHoiTuFile();
void xemDanhSachCauHoi();
void suaCauHoi();
void xoaCauHoi();
void menuQuanLyCauHoi();
void docFileCauHoi();
void ghiFileCauHoi();
CauHoi* timCauHoiTheoID(int id);

#endif