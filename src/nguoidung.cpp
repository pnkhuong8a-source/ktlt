#include <iostream>
#include <cstring>
#include <cstdio>
#include "nguoidung.h"
#include "utility.h"

using namespace std;

Vector<NguoiDung> dsNguoiDung;
//Lưu toàn bộ tài khoản vào file
void ghiFileNguoiDung() {
    FILE* f = fopen("nguoidung.txt", "w");  //Mở file ở chế độ ghi
    if (!f) return;
    //Ghi từng người dùng
    for (int i = 0; i < dsNguoiDung.size; ++i)
        fprintf(f, "%s %s %d\n", dsNguoiDung.data[i].username,
                dsNguoiDung.data[i].password, dsNguoiDung.data[i].vaiTro);
    fclose(f);
}
//Đọc file tài khoản vào bộ nhớ
void docFileNguoiDung() {
    FILE* f = fopen("nguoidung.txt", "r");  //Mở file để đọc
    if (!f) return;
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, f)) {  //Đọc từng dòng
        trimNewline(line);  //Xóa ký tự xuống dòng
        if (strlen(line) == 0) continue;    //Bỏ qua dòng rỗng
        NguoiDung nd;               //tạo người dùng mới
        char* token = strtok(line, " \t");  //tách chuỗi
        if (!token) continue;       //nếu dòng sai định dạng => bỏ qua
        strcpy(nd.username, token);     //Lưu username
        token = strtok(NULL, " \t");    //Lấy password
        if (!token) continue;
        strcpy(nd.password, token);     //Lấy vai trò
        token = strtok(NULL, " \t");
        if (!token) continue;
        nd.vaiTro = atoi(token);
        dsNguoiDung.them(nd);       //Thêm vào danh sách
    }
    fclose(f);
}
//Tạo tài khoản học sinh mới
void dangKyHocSinh() {
    NguoiDung nd;
    cout << "\n--- ĐĂNG KÝ TÀI KHOẢN HỌC SINH ---\n";
    cout << "Nhập username: ";
    cin.getline(nd.username, MAX_USERNAME);
    cout << "Nhập password: ";
    cin.getline(nd.password, MAX_PASSWORD);
    //Kiểm tra trùng tài khoản
    if (dsNguoiDung.timUser(nd.username) != -1) {
        cout << "Username đã tồn tại.\n";
        return;
    }
    nd.vaiTro = 1;  //Gán vai trò
    dsNguoiDung.them(nd);   //Thêm vào danh sách
    ghiFileNguoiDung();
    cout << "Đăng ký thành công.\n";
}
//Kiểm tra tài khoản đăng nhập
bool dangNhap(char* username, int& vaiTro) {
    char pass[MAX_PASSWORD];
    cout << "\n--- ĐĂNG NHẬP ---\n";
    cout << "Username: ";
    cin.getline(username, MAX_USERNAME);
    cout << "Password: ";
    cin.getline(pass, MAX_PASSWORD);
    int idx = dsNguoiDung.timUser(username);    //Tìm người dùng
    //Kiểm tra tài khoản
    if (idx != -1 && strcmp(dsNguoiDung.data[idx].password, pass) == 0) {
        vaiTro = dsNguoiDung.data[idx].vaiTro;  //Lưu vai trò
        return true;
    }
    return false;
}
