#include <iostream>
#include <cstdlib>
#include <ctime>
#include "cauhoi.h"
#include "dethi.h"
#include "nguoidung.h"
#include "ketqua.h"

using namespace std;

void thoatVaGhiFile() {
    ghiFileCauHoi();
    ghiFileDeThi();
    ghiFileNguoiDung();
    ghiFileKetQua();
    dsCauHoi.giaiPhong();
    dsDeThi.giaiPhong();
    dsNguoiDung.giaiPhong();
    dsKetQua.giaiPhong();
    exit(0);
}

int main() {
    srand(time(NULL));  //Seed cho số ngẫu nhiên
    dsCauHoi.khoiTao();
    dsDeThi.khoiTao();
    dsNguoiDung.khoiTao();
    dsKetQua.khoiTao();

    docFileCauHoi();
    docFileDeThi();
    docFileNguoiDung();
    docFileKetQua();
    //tạo tài khoản giáo viên admin/admin
    if (dsNguoiDung.size == 0) {
        NguoiDung gv;
        strcpy(gv.username, "admin");
        strcpy(gv.password, "admin");
        gv.vaiTro = 0;
        dsNguoiDung.them(gv);
    }

    char username[MAX_USERNAME];
    int vaiTro;
    bool daDangNhap = false;

    cout << "=== HỆ THỐNG THI TRẮC NGHIỆM ===\n";
    while (!daDangNhap) {       //Lặp cho đến khi đăng nhập thành công
        cout << "\n1. Đăng nhập\n2. Đăng ký (dành cho học sinh)\n0. Thoát\nChọn: ";
        int chon; cin >> chon; cin.ignore();
        if (chon == 1) {
            if (dangNhap(username, vaiTro)) daDangNhap = true;
            else cout << "Sai username hoặc password.\n";
        } else if (chon == 2) dangKyHocSinh();
        else if (chon == 0) thoatVaGhiFile();
        else cout << "Lựa chọn không hợp lệ.\n";
    }

    cout << "Đăng nhập thành công. Xin chào " << username << "!\n";
//Phân quyền
    if (vaiTro == 0) {      //Giáo viên
        int chon;
        do {
            cout << "\n=== MENU GIÁO VIÊN ===\n";
            cout << "1. Quản lý câu hỏi\n2. Quản lý đề thi\n3. Xem kết quả thi\n0. Đăng xuất & thoát\nChọn: ";
            cin >> chon;
            switch (chon) {
                case 1: menuQuanLyCauHoi(); break;
                case 2: menuQuanLyDeThi(); break;
                case 3: xemKetQuaGiaoVien(); break;
                case 0: thoatVaGhiFile(); break;
                default: cout << "Chọn sai.\n";
            }
        } while (true);
    } else {    //Học sinh
        int chon;
        do {
            cout << "\n=== MENU HỌC SINH ===\n";
            cout << "1. Thi trắc nghiệm\n2. Xem kết quả thi\n0. Đăng xuất & thoát\nChọn: ";
            cin >> chon;
            switch (chon) {
                case 1: thiTracNghiem(username); break;
                case 2: xemKetQuaHocSinh(username); break;
                case 0: thoatVaGhiFile(); break;
                default: cout << "Chọn sai.\n";
            }
        } while (true);
    }
    return 0;
}
