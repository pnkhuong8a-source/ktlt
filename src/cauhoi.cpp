#include <iostream>
#include <cstring>
#include <cstdio>
#include "cauhoi.h"
#include "utility.h"

using namespace std;

Vector<CauHoi> dsCauHoi;    //Tạo danh sách câu hỏi
int nextCauHoiID = 1;       //Lưu ID tiếp theo sẽ được cấp

CauHoi* timCauHoiTheoID(int id) {
    for (int i = 0; i < dsCauHoi.size; ++i)
        if (dsCauHoi.data[i].id == id) return &dsCauHoi.data[i];
    return NULL;
}
//Nạp dữ liệu từ file vào bộ nhớ
void ghiFileCauHoi() {
    FILE* f = fopen("cauhoi.txt", "w");
    if (!f) return;
    for (int i = 0; i < dsCauHoi.size; ++i) {
        CauHoi& ch = dsCauHoi.data[i];      //tạo biến ch viết cho nhanh
        fprintf(f, "%d\n%s\n%s\n", ch.id, ch.monHoc, ch.noiDung);
        for (int j = 0; j < 4; ++j) fprintf(f, "%s\n", ch.dapAn[j]);
        fprintf(f, "%c\n%d\n\n", ch.dapAnDung, ch.mucDo);
    }
    fclose(f);
}
//Nạp dữ liệu từ file vào bộ nhớ
void docFileCauHoi() {
    FILE* f = fopen("cauhoi.txt", "r");
    if (!f) return;
    char line[MAX_LINE];
    while (docDongKhongRong(f, line, MAX_LINE)) {   //đọc từng khối câu hỏi
        CauHoi ch;
        ch.id = atoi(line);     //đổi chuỗi => số
        if (!docDongKhongRong(f, ch.monHoc, MAX_MON_HOC)) break;
        if (!docDongKhongRong(f, ch.noiDung, MAX_NOI_DUNG)) break;
        for (int j = 0; j < 4; ++j)
            if (!docDongKhongRong(f, ch.dapAn[j], MAX_DAP_AN)) { fclose(f); return; }
        if (!docDongKhongRong(f, line, 10)) break;
        ch.dapAnDung = line[0];
        if (!docDongKhongRong(f, line, 10)) break;
        ch.mucDo = atoi(line);
        dsCauHoi.them(ch);
        if (ch.id >= nextCauHoiID) nextCauHoiID = ch.id + 1;
        fgets(line, MAX_LINE, f); // dòng trắng
    }
    fclose(f);
}

void themCauHoiThuCong() {
    CauHoi ch;
    ch.id = nextCauHoiID++;
    cout << "Nhập môn học: ";
    cin.ignore();
    cin.getline(ch.monHoc, MAX_MON_HOC);
    trimNewline(ch.monHoc);
    cout << "Nhập nội dung câu hỏi: ";
    cin.getline(ch.noiDung, MAX_NOI_DUNG);
    for (int i = 0; i < 4; ++i) {
        cout << "Nhập đáp án " << char('A'+i) << ": ";
        cin.getline(ch.dapAn[i], MAX_DAP_AN);
    }
    cout << "Nhập đáp án đúng (A/B/C/D): ";
    cin >> ch.dapAnDung;
    cin.ignore();
    cout << "Nhập mức độ (0: Dễ, 1: Khó): ";
    cin >> ch.mucDo;
    cin.ignore();
    dsCauHoi.them(ch);
    cout << "Đã thêm câu hỏi ID = " << ch.id << endl;
}

void themCauHoiTuFile() {
    char tenFile[200];
    cout << "Nhập tên file văn bản: ";
    cin.ignore();
    cin.getline(tenFile, 200);
    FILE* f = fopen(tenFile, "r");
    if (!f) { cout << "Không mở được file.\n"; return; }

    int dem = 0;
    char line[500];
    while (true) {
        CauHoi ch;
        if (!docDongKhongRong(f, ch.monHoc, MAX_MON_HOC)) break;
        if (!docDongKhongRong(f, ch.noiDung, MAX_NOI_DUNG)) break;
        for (int i = 0; i < 4; ++i)
            if (!docDongKhongRong(f, ch.dapAn[i], MAX_DAP_AN)) { fclose(f); return; }
        if (!docDongKhongRong(f, line, 10)) break;
        ch.dapAnDung = toupper(line[0]);
        if (!docDongKhongRong(f, line, 10)) break;
        ch.mucDo = atoi(line);
        ch.id = nextCauHoiID++;
        dsCauHoi.them(ch);
        dem++;
    }
    fclose(f);
    cout << "Đã thêm " << dem << " câu hỏi.\n";
}

void xemDanhSachCauHoi() {
    if (dsCauHoi.size == 0) { cout << "Chưa có câu hỏi nào.\n"; return; }
    for (int i = 0; i < dsCauHoi.size; ++i) {
        CauHoi& ch = dsCauHoi.data[i];
        cout << "ID: " << ch.id << " | Môn: " << ch.monHoc << " | Mức độ: " << (ch.mucDo ? "Kho" : "De") << "\n";
        cout << ch.noiDung << "\n";
        for (int j = 0; j < 4; ++j) cout << char('A'+j) << ". " << ch.dapAn[j] << "\n";
        cout << "Đáp án đúng: " << ch.dapAnDung << "\n-------------------\n";
    }
}

void suaCauHoi() {
    int id;
    cout << "Nhập ID câu hỏi cần sửa: ";
    cin >> id; cin.ignore();
    int idx = dsCauHoi.timTheoID(id);
    if (idx == -1) { cout << "Không tìm thấy.\n"; return; }
    CauHoi& ch = dsCauHoi.data[idx];
    char buffer[500];
    cout << "Sửa câu hỏi ID " << id << " (Enter để giữ nguyên)\n";
    cout << "Môn học [" << ch.monHoc << "]: "; cin.getline(buffer, 500);
    if (strlen(buffer) > 0) { strcpy(ch.monHoc, buffer); trimNewline(ch.monHoc); }
    cout << "Nội dung [" << ch.noiDung << "]: "; cin.getline(buffer, 500);
    if (strlen(buffer) > 0) strcpy(ch.noiDung, buffer);
    for (int i = 0; i < 4; ++i) {
        cout << "Đáp án " << char('A'+i) << " [" << ch.dapAn[i] << "]: ";
        cin.getline(buffer, 500);
        if (strlen(buffer) > 0) strcpy(ch.dapAn[i], buffer);
    }
    cout << "Đáp án đúng [" << ch.dapAnDung << "]: ";
    if (cin.peek() == '\n') cin.ignore();
    else { char c; cin >> c; cin.ignore(INT_MAX, '\n'); if (c>='A'&&c<='D') ch.dapAnDung = c; }
    cout << "Mức độ (0: Dễ, 1: Khó) [" << ch.mucDo << "]: ";
    if (cin.peek() == '\n') cin.ignore();
    else { int md; cin >> md; cin.ignore(INT_MAX, '\n'); if (md==0||md==1) ch.mucDo = md; }
    cout << "Đã cập nhật.\n";
}

void xoaCauHoi() {
    int id;
    cout << "Nhập ID câu hỏi cần xóa: ";
    cin >> id; cin.ignore();
    int idx = dsCauHoi.timTheoID(id);
    if (idx == -1) cout << "Không tìm thấy.\n";
    else { dsCauHoi.xoa(idx); cout << "Đã xóa.\n"; }
}

void menuThemCauHoi() {
    int chon;
    do {
        cout << "\n=== THÊM CÂU HỎI ===\n1. Nhập thủ công\n2. Nhập từ file\n0. Quay lại\nChọn: ";
        cin >> chon;
        if (chon == 1) themCauHoiThuCong();
        else if (chon == 2) themCauHoiTuFile();
    } while (chon != 0);
}

void menuQuanLyCauHoi() {
    int chon;
    do {
        cout << "\n=== QUẢN LÝ NGÂN HÀNG CÂU HỎI ===\n";
        cout << "1. Thêm câu hỏi\n2. Xem danh sách\n3. Sửa câu hỏi\n4. Xóa câu hỏi\n0. Quay lại\nChọn: ";
        cin >> chon;
        if (chon == 1) menuThemCauHoi();
        else if (chon == 2) xemDanhSachCauHoi();
        else if (chon == 3) suaCauHoi();
        else if (chon == 4) xoaCauHoi();
    } while (chon != 0);
}