#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include "ketqua.h"
#include "dethi.h"
#include "cauhoi.h"
#include "utility.h"

using namespace std;

Vector<KetQuaThi> dsKetQua;     //Danh sách toàn bộ kết quả thi
//Vai trò của struct KetQuaThi là mỗi lần học sinh làm bài sẽ sinh ra một bản ghi

//Sắp xếp kết quả theo thời gian bắt đầu thi
void sapXepKetQuaTheoThoiGian() {
    for (int i = 0; i < dsKetQua.size - 1; ++i) {
        for (int j = i + 1; j < dsKetQua.size; ++j) {
            if (dsKetQua.data[i].thoiGianBatDau > dsKetQua.data[j].thoiGianBatDau) {
                KetQuaThi tmp = dsKetQua.data[i];
                dsKetQua.data[i] = dsKetQua.data[j];
                dsKetQua.data[j] = tmp;
            }
        }
    }
}
//Lưu toàn bộ kết quả xuống ketqua.txt
void ghiFileKetQua() {
    FILE* f = fopen("ketqua.txt", "w");
    if (!f) return;
    for (int i = 0; i < dsKetQua.size; ++i) {
        KetQuaThi& kq = dsKetQua.data[i];
        fprintf(f, "%s\n%d\n%ld\n%ld\n%d\n", kq.username, kq.idDeThi,
                (long)kq.thoiGianBatDau, (long)kq.thoiGianKetThuc, kq.soCauHoi);
        for (int j = 0; j < kq.soCauHoi; ++j) fprintf(f, "%d ", kq.dsIDCauHoi[j]);
        fprintf(f, "\n");
        for (int j = 0; j < kq.soCauHoi; ++j) fprintf(f, "%c", kq.dapAnDungHienThi[j]);
        fprintf(f, "\n");
        for (int j = 0; j < kq.soCauHoi; ++j) fprintf(f, "%c", kq.cauTraLoi[j]);
        fprintf(f, "\n%.1f\n\n", kq.diem);
    }
    fclose(f);
}

void docFileKetQua() {
    FILE* f = fopen("ketqua.txt", "r");
    if (!f) return;
    char line[MAX_LINE];
    while (docDongKhongRong(f, line, MAX_LINE)) {
        KetQuaThi kq;
        strcpy(kq.username, line);
        if (!docDongKhongRong(f, line, 10)) break;
        kq.idDeThi = atoi(line);
        if (!docDongKhongRong(f, line, 20)) break;
        kq.thoiGianBatDau = (time_t)atol(line);
        if (!docDongKhongRong(f, line, 20)) break;
        kq.thoiGianKetThuc = (time_t)atol(line);
        if (!docDongKhongRong(f, line, 10)) break;
        kq.soCauHoi = atoi(line);
        if (!docDongKhongRong(f, line, MAX_LINE)) break;
        tachSoNguyen(line, kq.dsIDCauHoi, MAX_KET_QUA);
        if (!docDongKhongRong(f, line, MAX_LINE)) break;
        for (int j = 0; j < kq.soCauHoi; ++j) kq.dapAnDungHienThi[j] = line[j];
        if (!docDongKhongRong(f, line, MAX_LINE)) break;
        for (int j = 0; j < kq.soCauHoi; ++j) kq.cauTraLoi[j] = line[j];
        if (!docDongKhongRong(f, line, 10)) break;
        kq.diem = (float)atof(line);
        dsKetQua.them(kq);
        fgets(line, MAX_LINE, f); // dòng trắng
    }
    fclose(f);
}

void thiTracNghiem(const char* username) {
    if (dsDeThi.size == 0) { cout << "Chưa có đề thi nào.\n"; return; }
    for (int i = 0; i < dsDeThi.size; ++i)      //Hiển thị danh sách đề
        cout << "ID: " << dsDeThi.data[i].id << " - " << dsDeThi.data[i].monHoc
             << " - " << dsDeThi.data[i].soLuongCauHoi << " câu - "
             << dsDeThi.data[i].thoiGianLamBai << " phút\n";
    //Chọn đề
    int idDe;
    cout << "Chọn ID đề thi: "; cin >> idDe; cin.ignore();
    //Tìm đề
    int idxDe = dsDeThi.timTheoID(idDe);
    if (idxDe == -1) { cout << "Không tồn tại.\n"; return; }
    DeThi& de = dsDeThi.data[idxDe];
    int soCau = de.soLuongCauHoi;
    //Sao chép danh sách câu hỏi
    int* idsThi = new int[soCau];
    for (int i = 0; i < soCau; ++i) idsThi[i] = de.dsCauHoi[i];
    //Trộn thứ tự câu hỏi
    shuffleInt(idsThi, soCau);
    char* dapAnDungMoi = new char[soCau];
    //Tạo đáp án người dùng
    char* cauTraLoi = new char[soCau];
    for (int i = 0; i < soCau; ++i) cauTraLoi[i] = '-';   //khởi tạo đáp án
    time_t start = time(NULL);      //Thời gian bắt đầu
    time_t deadline = start + de.thoiGianLamBai * 60;       //Deadline
    cout << "\nBẮT ĐẦU THI (" << de.thoiGianLamBai << " phút).\n";
    for (int i = 0; i < soCau; ++i) {   //Duyệt mỗi câu hỏi
        time_t now = time(NULL);
        //Kiểm tra còn thời gian
        int remain = (int)(deadline - now); if (remain < 0) remain = 0;
        cout << "\n[Còn " << remain/60 << ":" << remain%60 << "] ";
        if (now >= deadline) { cout << "HẾT GIỜ!\n"; break; }
        CauHoi* ch = timCauHoiTheoID(idsThi[i]);
        if (!ch) continue;
        //Trộn đáp án và tìm đáp án đúng mới
        char thuTu[4] = {'A','B','C','D'};
        int indices[4] = {0,1,2,3};
        shuffleInt(indices, 4);
        char dapDungMoi = 'A';
        for (int j = 0; j < 4; ++j) {
            if (thuTu[indices[j]] == ch->dapAnDung) dapDungMoi = 'A'+j;
        }
        dapAnDungMoi[i] = dapDungMoi;
        cout << "Câu " << i+1 << ": " << ch->noiDung << "\n";
        for (int j = 0; j < 3; ++j)
            cout << char('A'+j) << ". " << ch->dapAn[indices[j]] << "\n";
        cout << char('A'+3) << ". " << ch->dapAn[indices[3]];
        cout << "Trả lời (A/B/C/D/-): ";
        char tl = '-';
        bool done = false;
        //Nhập đáp án
        while (!done) {
            if (time(NULL) >= deadline) { cout << "\nHẾT GIỜ.\n"; break; }
            if (kbhit()) {
                int key = getch();
                if (key == '\r' || key == '\n') {
                    if (tl == '-') continue;
                    done = true;
                } else if (key == 8 || key == 127) {
                    if (tl != '-') { cout << "\b \b"; tl = '-'; }
                } else if ((key >= 'A' && key <= 'D') || (key >= 'a' && key <= 'd') || key == '-') {
                    if (tl == '-') {
                        tl = (key >= 'a' && key <= 'd') ? key - 'a' + 'A' : key;
                        cout << tl;
                        if (tl == '-' || (tl >= 'A' && tl <= 'D')) done = true;
                    }
                }
            }
        }
        if (time(NULL) >= deadline) break;
        cauTraLoi[i] = tl;
    }
    time_t finish = time(NULL); if (finish > deadline) finish = deadline;
    //Chấm điểm
    int correct = 0;
    for (int i = 0; i < soCau; ++i) if (cauTraLoi[i] == dapAnDungMoi[i]) correct++;
    float diem = (float)correct / soCau * 10.0f;    //Công thức điểm
    //Lưu kết quả
    KetQuaThi kq;       
    strcpy(kq.username, username);
    kq.idDeThi = de.id;
    kq.thoiGianBatDau = start;
    kq.thoiGianKetThuc = finish;
    kq.soCauHoi = soCau;
    for (int i = 0; i < soCau; ++i) {
        kq.dsIDCauHoi[i] = idsThi[i];
        kq.dapAnDungHienThi[i] = dapAnDungMoi[i];
        kq.cauTraLoi[i] = cauTraLoi[i];
    }
    kq.diem = diem;
    dsKetQua.them(kq);

    // In kết quả kèm thời gian làm bài
    int thoiGianLam = (int)(finish - start);
    int phut = thoiGianLam / 60;
    int giay = thoiGianLam % 60;
    cout << "\n=== KẾT QUẢ ===\n";
    cout << "Đề thi ID: " << de.id << " | Môn: " << de.monHoc << "\n";
    cout << "Thời gian làm bài: " << phut << " phút " << giay << " giây\n";
    cout << "Số câu đúng: " << correct << "/" << soCau << " | Điểm: " << diem << "\n";
    //Giải phóng bộ nhớ
    delete[] idsThi;
    delete[] dapAnDungMoi;
    delete[] cauTraLoi;
}

void xemKetQuaHocSinh(const char* username) {
    cout << "\n=== KẾT QUẢ THI CỦA BẠN ===\n";
    bool co = false;
    for (int i = 0; i < dsKetQua.size; ++i) {
        if (strcmp(dsKetQua.data[i].username, username) == 0) {
            co = true;
            KetQuaThi& kq = dsKetQua.data[i];
            int thoiGianLam = (int)(kq.thoiGianKetThuc - kq.thoiGianBatDau);
            int phut = thoiGianLam / 60;
            int giay = thoiGianLam % 60;
            cout << "Đề ID: " << kq.idDeThi
                 << " | Điểm: " << kq.diem
                 << " | Đúng: " << (int)(kq.diem * kq.soCauHoi / 10.0f + 0.5f) << "/" << kq.soCauHoi
                 << " | Thời gian: " << phut << " phút " << giay << " giây\n";
        }
    }
    if (!co) cout << "Chưa có kết quả.\n";
}

void xemKetQuaGiaoVien() {
    cout << "\n=== TẤT CẢ KẾT QUẢ ===\n";
    if (dsKetQua.size == 0) { cout << "Chưa có dữ liệu.\n"; return; }
    sapXepKetQuaTheoThoiGian();
    for (int i = 0; i < dsKetQua.size; ++i) {
        KetQuaThi& kq = dsKetQua.data[i];
        int thoiGianLam = (int)(kq.thoiGianKetThuc - kq.thoiGianBatDau);
        int phut = thoiGianLam / 60;
        int giay = thoiGianLam % 60;
        cout << "Thí sinh: " << kq.username
             << " - Đề ID: " << kq.idDeThi
             << " - Điểm: " << kq.diem
             << " | Đúng: " << (int)(kq.diem * kq.soCauHoi / 10.0f + 0.5f) << "/" << kq.soCauHoi
             << " | Thời gian: " << phut << " phút " << giay << " giây\n";
    }
}
