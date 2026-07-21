#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Mở file encoded.bmp ở chế độ đọc nhị phân
    ifstream file("encoded.bmp", ios::binary);
    if (!file.is_open()) {
        cerr << "Khong the mo file encoded.bmp!" << endl;
        return 1;
    }

    // Đọc toàn bộ dữ liệu file vào vector
    vector<unsigned char> enc_data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Bỏ qua 723 byte header đầu tiên theo đúng mã giả v11 = 723
    size_t offset = 723;
    string flag = "";

    // Vòng lặp j chạy từ 0 đến 99 mô phỏng lại logic mã hóa
    for (int j = 0; j <= 99; ++j) {
        if ((j & 1) != 0) {
            // Nếu j là số lẻ: Lúc mã hóa, chương trình chỉ chép 1 byte pixel gốc và dịch offset 1 đơn vị
            offset += 1;
        } 
        else {
            // Nếu j là số chẵn: Lúc mã hóa, chương trình đã giấu 1 ký tự (gồm 8 bit) qua 8 pixel liên tiếp
            unsigned char char_val = 0;
            
            for (int k = 0; k <= 7; ++k) {
                unsigned char byte_enc = enc_data[offset];
                
                // Lấy bit LSB (bit thấp nhất) từ file encoded.bmp
                unsigned char bit = byte_enc & 1;
                
                // Gom bit lại theo đúng trọng số bit thứ k
                char_val |= (bit << k);
                
                // Dịch offset qua pixel tiếp theo
                offset += 1;
            }
            
            // Vì mã giả không có phép trừ/cộng biến đổi nào trên v16[j / 2], ta giữ nguyên giá trị byte thu được
            flag += (char)char_val;
        }
    }

    // In kết quả chuỗi flag hoàn chỉnh ra màn hình
    cout << "Flag tim duoc la:" << endl;
    cout << flag << endl;

    return 0;
}