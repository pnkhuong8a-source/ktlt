#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>   // để dùng strcmp

template <typename T>   
struct Vector {
    T* data;        //con trỏ tới mảng động
    int size;       //số phần tử hiện đang có
    int capacity;   //dung lượng tối đa hiện tại (trước khi đc cấp phát động)
    //khởi tạo vector
    void khoiTao() {
        data = NULL;
        size = 0; 
        capacity = 0;      
    }
    //thêm phần tử vào cuối vector
    void them(const T& value) {
        if (size >= capacity) {         // Nếu mảng đã đầy
            capacity = (capacity == 0) ? 2 : capacity * 2;   // Nếu chưa có dung lượng thì cấp 2 ô, ngược lại tăng gấp đôi dung lượng
            T* newData = new T[capacity];    // Tạo mảng động mới có kích thước capacity
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];     // Sao chép dữ liệu từ mảng cũ sang mảng mới
            delete[] data;    // Giải phóng mảng cũ
            data = newData;      // Cho data trỏ tới mảng mới
        }
        data[size++] = value;     // Gán value vào cuối mảng, sau đó tăng size lên 1
    }
    // Xóa phần tử tại vị trí index
    void xoa(int index) {
        if (index < 0 || index >= size) return;  
        for (int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];   // Dời các phần tử phía sau sang trái 1 vị trí
        --size;     // Giảm số lượng phần tử đi 1
    }
    // Tìm vị trí phần tử có id truyền vào
    int timTheoID(int id) const {
        for (int i = 0; i < size; ++i) {
            if (data[i].id == id)
                return i;  
        }
        return -1;
    }

    int timUser(const char* user) const {     // Tìm vị trí user theo username
        for (int i = 0; i < size; ++i) {
            if (strcmp(data[i].username, user) == 0)   // strcmp trả về 0 nếu hai chuỗi giống nhau
                return i;
        }
        return -1;
    }
    // Giải phóng toàn bộ bộ nhớ của vector
    void giaiPhong() {
        delete[] data;  // Xóa mảng động
        data = NULL;   // Tránh con trỏ treo
        size = capacity = 0;  // Đưa vector về trạng thái rỗng
    }
};

#endif
