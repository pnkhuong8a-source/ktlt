#ifndef DETHI_H
#define DETHI_H

#include "vector.h"
#include "constants.h"

extern Vector<DeThi> dsDeThi;
extern int nextDeThiID;

void taoDeThi();
void xemDanhSachDeThi();
void suaDeThi();
void xoaDeThi();
void menuQuanLyDeThi();
void docFileDeThi();
void ghiFileDeThi();
DeThi* timDeThiTheoID(int id);
void suaDanhSachCauHoiDe(DeThi& dt);
void xemDanhSachCauHoiTrongDe(const DeThi& dt);
void suaCauHoiTrongDe(DeThi& dt);
void themCauHoiMoiVaoDe(DeThi& dt);
void themCauHoiTuNganHangVaoDe(DeThi& dt);
void xoaCauHoiKhoiDe(DeThi& dt);

#endif