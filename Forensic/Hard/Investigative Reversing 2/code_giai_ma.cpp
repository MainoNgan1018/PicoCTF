#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Mở file encoded.bmp ở chế độ đọc nhị phân ("rb")
    // Sử dụng đường dẫn tuyệt đối hoặc đặt file cùng thư mục với chương trình
    ifstream file("encoded.bmp", ios::binary);
    if (!file.is_open()) {
        cerr << "Khong the mo file encoded.bmp!" << endl;
        return 1;
    }

    // Đọc toàn bộ dữ liệu file vào vector byte
    vector<unsigned char> enc_data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Bỏ qua 2000 byte header đầu tiên (giống như logic chép header trong hàm main của ELF)
    size_t offset = 2000;
    string flag = "";

    // Tổng số ký tự cần giải mã là 50 (đúng với độ dài 0x32 trong mã giả)
    for (int j = 0; j < 50; ++j) {
        unsigned char char_val = 0;
        
        // Mỗi ký tự bao gồm 8 bit (tương ứng vòng lặp k từ 0 đến 7)
        for (int k = 0; k < 8; ++k) {
            // Lấy trực tiếp byte tại vị trí offset hiện tại trong file encoded.bmp
            unsigned char byte_enc = enc_data[offset];
            
            // Trích xuất bit LSB (bit thấp nhất) bằng phép toán bitwise AND với 1
            // Đây chính là bit dữ liệu của flag đã được nhúng vào ảnh
            unsigned char bit = byte_enc & 1;
            
            // Gom bit lại vào đúng vị trí trọng số bit thứ k của ký tự
            char_val |= (bit << k);
            
            // Dịch chuyển offset tới byte tiếp theo của ảnh
            offset += 1;
        }
        
        // Trong code mã hóa gốc: v16[j] - 5. Do đó, giải mã ngược lại ta phải CỘNG 5 (+ 5)
        char original_char = (char)(char_val + 5);
        flag += original_char;
    }

    // In kết quả chuỗi flag hoàn chỉnh ra màn hình
    cout << "Flag tim duoc la:" << endl;
    cout << flag << endl;

    return 0;
}