#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <ctime>   // để dùng time_t

const int MAX_NOI_DUNG = 500;
const int MAX_DAP_AN = 200;
const int MAX_MON_HOC = 100;
const int MAX_USERNAME = 50;
const int MAX_PASSWORD = 50;
const int MAX_CAU_HOI = 100;
const int MAX_KET_QUA = 100;
const int MAX_LINE = 1024;

struct CauHoi {
    int id;
    char noiDung[MAX_NOI_DUNG];
    char dapAn[4][MAX_DAP_AN];
    char dapAnDung;     // 'A','B','C','D'
    int mucDo;          // 0: Dễ, 1: Khó
    char monHoc[MAX_MON_HOC];
};

struct DeThi {
    int id;
    char monHoc[MAX_MON_HOC];
    int soLuongCauHoi;
    int dsCauHoi[MAX_CAU_HOI];
    int thoiGianLamBai;   // phút
    time_t ngayTao;
};

struct NguoiDung {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int vaiTro;           // 0: Giáo viên, 1: Học sinh
};

struct KetQuaThi {
    char username[MAX_USERNAME];
    int idDeThi;
    time_t thoiGianBatDau;
    time_t thoiGianKetThuc;
    int soCauHoi;
    int dsIDCauHoi[MAX_KET_QUA];
    char dapAnDungHienThi[MAX_KET_QUA];
    char cauTraLoi[MAX_KET_QUA];
    float diem;
};

#endif