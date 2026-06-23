# Hệ thống thi trắc nghiệm

Bài tập lớn môn Kỹ thuật lập trình – xây dựng chương trình hỗ trợ thi trắc nghiệm đơn giản.
 
## Tài khoản mặc định

| Vai trò   | Username | Password |
|-----------|----------|----------|
| Giáo viên | admin    | admin    |
| Học sinh  | *(tự đăng ký)* | |

Có thể sử dụng tài khoản mẫu cho học sinh với username: hocsinh và password: 1
## Các chức năng chính

**1. Quản lý người dùng**  
- Đăng nhập, đăng ký (học sinh).  
- Phân quyền: giáo viên quản lý hệ thống, học sinh thi và xem kết quả.

**2. Quản lý ngân hàng câu hỏi** *(giáo viên)*  
- Thêm câu hỏi: nhập thủ công hoặc từ file `.txt` (theo định dạng 8 dòng/câu).  
- Xem danh sách, sửa, xóa câu hỏi theo ID.  
- Dữ liệu lưu trong `cauhoi.txt`.

**3. Quản lý đề thi** *(giáo viên)*  
- Tạo đề thi tự động: chọn môn, số câu, thời gian – hệ thống lấy ngẫu nhiên câu hỏi từ ngân hàng.  
- Xem danh sách, sửa (đổi thời gian, làm mới ngẫu nhiên, chỉnh sửa thủ công), xóa đề.  
- Dữ liệu lưu trong `dethi.txt`.

**4. Thi trắc nghiệm** *(học sinh)*  
- Chọn đề thi, làm bài với đồng hồ đếm ngược.  
- Xáo trộn thứ tự câu hỏi và đáp án mỗi lần thi.  
- Nhập đáp án không cần Enter (dùng phím A/B/C/D hoặc '-').  
- Tự động nộp bài khi hết giờ.  
- Hiển thị ngay điểm, số câu đúng, thời gian làm bài.

**5. Quản lý kết quả thi**  
- Học sinh: xem lại các lần thi của mình (điểm, thời gian).  
- Giáo viên: xem toàn bộ kết quả, sắp xếp theo thời gian.  
- Dữ liệu lưu trong `ketqua.txt`.

**6. Lưu trữ và khôi phục dữ liệu**  
- Khi thoát chương trình, toàn bộ dữ liệu được ghi vào các file `.txt`.  
- Khi khởi động lại, dữ liệu được đọc từ file, đảm bảo không mất mát.

## Định dạng file câu hỏi nhập ngoài

Mỗi câu hỏi gồm 8 dòng theo thứ tự:

1. Môn học  
2. Nội dung câu hỏi  
3. Đáp án A  
4. Đáp án B  
5. Đáp án C  
6. Đáp án D  
7. Đáp án đúng (A/B/C/D)  
8. Mức độ (0: Dễ, 1: Khó)

Các câu hỏi cách nhau bởi một dòng trắng.

## Ghi chú

- Chương trình không sử dụng `std::vector`, `std::list`, `std::sort`, … mà tự cài đặt cấu trúc `Vector`, thuật toán tìm kiếm tuyến tính, sắp xếp nổi bọt, Fisher–Yates shuffle.  
- File dữ liệu `.txt` được lưu cùng thư mục với file thực thi. Khi chạy lần đầu, các file này sẽ được tạo mới.  
- Mặc định hệ thống đã có tài khoản giáo viên `admin/admin`. Học sinh phải đăng ký trước khi đăng nhập.
- Chạy nhanh bằng GitHub Codespaces

Nếu không muốn cài đặt g++, bạn vẫn có thể biên dịch và chạy chương trình trực tiếp trên trình duyệt nhờ Codespaces.

1. Nhấn **<> Code** → chọn tab **Codespaces** → **Create codespace on main**.
2. Đợi môi trường khởi động.
3. Mở Terminal trong Codespace, gõ:
   ```bash
   g++ -o tracnghiem src/*.cpp -Iinclude
   ./tracnghiem

---

**Người thực hiện:** Phạm Ngọc Khương, Nguyễn Phạm Thu Uyên  
**Môn học:** Kỹ thuật lập trình
