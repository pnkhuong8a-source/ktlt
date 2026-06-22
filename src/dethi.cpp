#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include "dethi.h"
#include "cauhoi.h"
#include "utility.h"

using namespace std;

Vector<DeThi> dsDeThi;
int nextDeThiID = 1;

DeThi* timDeThiTheoID(int id) {
    for (int i = 0; i < dsDeThi.size; ++i)
        if (dsDeThi.data[i].id == id) return &dsDeThi.data[i];
    return NULL;
}

void ghiFileDeThi() {
    FILE* f = fopen("dethi.txt", "w");
    if (!f) return;
    for (int i = 0; i < dsDeThi.size; ++i) {
        DeThi& dt = dsDeThi.data[i];
        fprintf(f, "%d\n%s\n%d\n", dt.id, dt.monHoc, dt.soLuongCauHoi);
        for (int j = 0; j < dt.soLuongCauHoi; ++j)
            fprintf(f, "%d ", dt.dsCauHoi[j]);
        fprintf(f, "\n%d\n%ld\n\n", dt.thoiGianLamBai, (long)dt.ngayTao);
    }
    fclose(f);
}

void docFileDeThi() {
    FILE* f = fopen("dethi.txt", "r");
    if (!f) return;
    char line[MAX_LINE];
    while (docDongKhongRong(f, line, MAX_LINE)) {
        DeThi dt;
        dt.id = atoi(line);
        if (!docDongKhongRong(f, dt.monHoc, MAX_MON_HOC)) break;
        if (!docDongKhongRong(f, line, 10)) break;
        dt.soLuongCauHoi = atoi(line);
        if (!docDongKhongRong(f, line, MAX_LINE)) break;
        tachSoNguyen(line, dt.dsCauHoi, MAX_CAU_HOI);
        if (!docDongKhongRong(f, line, 10)) break;
        dt.thoiGianLamBai = atoi(line);
        if (!docDongKhongRong(f, line, 20)) break;
        dt.ngayTao = (time_t)atol(line);
        dsDeThi.them(dt);
        if (dt.id >= nextDeThiID) nextDeThiID = dt.id + 1;
        fgets(line, MAX_LINE, f); // dòng trắng
    }
    fclose(f);
}

void xemDanhSachCauHoiTrongDe(const DeThi& dt) {
    cout << "Danh sách câu hỏi trong đề ID " << dt.id << " (Môn: " << dt.monHoc << "):\n";
    for (int i = 0; i < dt.soLuongCauHoi; ++i) {
        CauHoi* ch = timCauHoiTheoID(dt.dsCauHoi[i]);
        if (ch)
            cout << i+1 << ". ID " << ch->id << " - " << ch->noiDung << " (" << (ch->mucDo?"Khó":"Dễ") << ")\n";
        else
            cout << i+1 << ". ID " << dt.dsCauHoi[i] << " - KHÔNG TỒN TẠI\n";
    }
}

void suaCauHoiTrongDe(DeThi& dt) {
    if (dt.soLuongCauHoi == 0) { cout << "Đề không có câu hỏi nào.\n"; return; }
    xemDanhSachCauHoiTrongDe(dt);
    int stt;
    cout << "Chọn số thứ tự (1-" << dt.soLuongCauHoi << "): ";
    cin >> stt; cin.ignore();
    if (stt < 1 || stt > dt.soLuongCauHoi) { cout << "Sai.\n"; return; }
    CauHoi* ch = timCauHoiTheoID(dt.dsCauHoi[stt-1]);
    if (!ch) { cout << "Câu hỏi không tồn tại.\n"; return; }
    char buffer[500];
    cout << "Sửa câu hỏi ID " << ch->id << " (Enter giu nguyen)\n";
    cout << "Môn học [" << ch->monHoc << "]: "; cin.getline(buffer, 500);
    if (strlen(buffer) > 0) { strcpy(ch->monHoc, buffer); trimNewline(ch->monHoc); }
    cout << "Nội dung [" << ch->noiDung << "]: "; cin.getline(buffer, 500);
    if (strlen(buffer) > 0) strcpy(ch->noiDung, buffer);
    for (int i = 0; i < 4; ++i) {
        cout << "Đáp án " << char('A'+i) << " [" << ch->dapAn[i] << "]: ";
        cin.getline(buffer, 500);
        if (strlen(buffer) > 0) strcpy(ch->dapAn[i], buffer);
    }
    cout << "Đáp án đúng [" << ch->dapAnDung << "]: ";
    if (cin.peek() == '\n') cin.ignore();
    else { char c; cin >> c; cin.ignore(INT_MAX, '\n'); if (c>='A'&&c<='D') ch->dapAnDung = c; }
    cout << "Mức độ (0: Dễ, 1: Khó) [" << ch->mucDo << "]: ";
    if (cin.peek() == '\n') cin.ignore();
    else { int md; cin >> md; cin.ignore(INT_MAX, '\n'); if (md==0||md==1) ch->mucDo = md; }
    cout << "Đã cập nhật.\n";
}

void themCauHoiMoiVaoDe(DeThi& dt) {
    if (dt.soLuongCauHoi >= MAX_CAU_HOI) { cout << "Đề đầy.\n"; return; }
    CauHoi ch;
    ch.id = nextCauHoiID++;
    cout << "Nhập môn học: "; cin.ignore(); cin.getline(ch.monHoc, MAX_MON_HOC); trimNewline(ch.monHoc);
    cout << "Nội dung: "; cin.getline(ch.noiDung, MAX_NOI_DUNG);
    for (int i = 0; i < 4; ++i) {
        cout << "Đáp án " << char('A'+i) << ": ";
        cin.getline(ch.dapAn[i], MAX_DAP_AN);
    }
    cout << "Đáp án đúng (A/B/C/D): "; cin >> ch.dapAnDung; cin.ignore();
    cout << "Mức độ (0/1): "; cin >> ch.mucDo; cin.ignore();
    dsCauHoi.them(ch);
    dt.dsCauHoi[dt.soLuongCauHoi++] = ch.id;
    cout << "Đã thêm câu hỏi mới ID " << ch.id << " vào đề thi và ngân hàng.\n";
}

void themCauHoiTuNganHangVaoDe(DeThi& dt) {
    if (dt.soLuongCauHoi >= MAX_CAU_HOI) { cout << "Đề đầy.\n"; return; }
    int id;
    cout << "Nhập ID câu hỏi muốn thêm: "; cin >> id;
    CauHoi* ch = timCauHoiTheoID(id);
    if (!ch || strcmp(ch->monHoc, dt.monHoc) != 0) { cout << "Không hợp lệ.\n"; return; }
    for (int i = 0; i < dt.soLuongCauHoi; ++i)
        if (dt.dsCauHoi[i] == id) { cout << "Đã tồn tại.\n"; return; }
    dt.dsCauHoi[dt.soLuongCauHoi++] = id;
    cout << "Đã thêm.\n";
}

void xoaCauHoiKhoiDe(DeThi& dt) {
    if (dt.soLuongCauHoi == 0) { cout << "Đề rỗng.\n"; return; }
    xemDanhSachCauHoiTrongDe(dt);
    int stt;
    cout << "Nhập số thứ tự muốn xóa: "; cin >> stt;
    if (stt < 1 || stt > dt.soLuongCauHoi) return;
    for (int i = stt-1; i < dt.soLuongCauHoi-1; ++i)
        dt.dsCauHoi[i] = dt.dsCauHoi[i+1];
    dt.soLuongCauHoi--;
    cout << "Đã xóa.\n";
}

void suaDanhSachCauHoiDe(DeThi& dt) {
    int chon;
    do {
        cout << "\n=== SỬA DANH SÁCH CÂU HỎI CỦA ĐỀ ===\n";
        cout << "1. Xem danh sách\n2. Sửa câu hỏi\n3. Thêm mới\n4. Thêm từ ngân hàng\n5. Xóa\n0. Quay lại\nChọn: ";
        cin >> chon;
        if (chon == 1) xemDanhSachCauHoiTrongDe(dt);
        else if (chon == 2) suaCauHoiTrongDe(dt);
        else if (chon == 3) themCauHoiMoiVaoDe(dt);
        else if (chon == 4) themCauHoiTuNganHangVaoDe(dt);
        else if (chon == 5) xoaCauHoiKhoiDe(dt);
    } while (chon != 0);
}

void taoDeThi() {
    DeThi dt;
    dt.id = nextDeThiID++;
    cout << "Nhập môn học: "; cin.ignore(); cin.getline(dt.monHoc, MAX_MON_HOC); trimNewline(dt.monHoc);
    cout << "Số câu hỏi: "; cin >> dt.soLuongCauHoi;
    cout << "Thời gian (phút): "; cin >> dt.thoiGianLamBai; cin.ignore();

    Vector<int> ids; ids.khoiTao();
    for (int i = 0; i < dsCauHoi.size; ++i)
        if (strcmp(dsCauHoi.data[i].monHoc, dt.monHoc) == 0)
            ids.them(dsCauHoi.data[i].id);
    if (ids.size < dt.soLuongCauHoi) {
        cout << "Không đủ câu hỏi cho môn \"" << dt.monHoc << "\". Chỉ có " << ids.size << " câu.\n";
        ids.giaiPhong();
        return;
    }
    shuffleInt(ids.data, ids.size);
    for (int i = 0; i < dt.soLuongCauHoi; ++i)
        dt.dsCauHoi[i] = ids.data[i];
    ids.giaiPhong();
    dt.ngayTao = time(NULL);
    dsDeThi.them(dt);
    cout << "Đã tạo đề thi ID = " << dt.id << endl;
}

void xemDanhSachDeThi() {
    if (dsDeThi.size == 0) { cout << "Chưa có đề thi nào.\n"; return; }
    for (int i = 0; i < dsDeThi.size; ++i) {
        DeThi& dt = dsDeThi.data[i];
        cout << "ID: " << dt.id << " | Môn: " << dt.monHoc << " | Số câu: " << dt.soLuongCauHoi
             << " | Thời gian: " << dt.thoiGianLamBai << " phút\n";
    }
}

void suaDeThi() {
    int id;
    cout << "Nhập ID để sửa: "; cin >> id; cin.ignore();
    int idx = dsDeThi.timTheoID(id);
    if (idx == -1) { cout << "Không tìm thấy.\n"; return; }
    DeThi& dt = dsDeThi.data[idx];
    cout << "1. Đổi thời gian\n2. Tạo lại ngẫu nhiên\n3. Sửa thủ công\nChọn: ";
    int chon; cin >> chon; cin.ignore();
    if (chon == 1) {
        cout << "Thời gian mới: "; cin >> dt.thoiGianLamBai; cin.ignore();
    } else if (chon == 2) {
        Vector<int> ids; ids.khoiTao();
        for (int i = 0; i < dsCauHoi.size; ++i)
            if (strcmp(dsCauHoi.data[i].monHoc, dt.monHoc) == 0)
                ids.them(dsCauHoi.data[i].id);
        if (ids.size < dt.soLuongCauHoi) cout << "Không đủ câu hỏi.\n";
        else {
            shuffleInt(ids.data, ids.size);
            for (int i = 0; i < dt.soLuongCauHoi; ++i) dt.dsCauHoi[i] = ids.data[i];
            cout << "Đã tạo lại.\n";
        }
        ids.giaiPhong();
    } else if (chon == 3) {
        suaDanhSachCauHoiDe(dt);
    }
    dt.ngayTao = time(NULL);
    cout << "Đã cập nhật.\n";
}

void xoaDeThi() {
    int id;
    cout << "Nhập ID để xóa: "; cin >> id; cin.ignore();
    int idx = dsDeThi.timTheoID(id);
    if (idx != -1) { dsDeThi.xoa(idx); cout << "Đã xóa.\n"; }
    else cout << "Không tìm thấy.\n";
}

void menuQuanLyDeThi() {
    int chon;
    do {
        cout << "\n=== QUẢN LÝ ĐỀ THI ===\n1. Tạo đề\n2. Xem danh sách\n3. Sửa đề\n4. Xóa đề\n0. Quay lại\nChọn: ";
        cin >> chon;
        if (chon == 1) taoDeThi();
        else if (chon == 2) xemDanhSachDeThi();
        else if (chon == 3) suaDeThi();
        else if (chon == 4) xoaDeThi();
    } while (chon != 0);
}
