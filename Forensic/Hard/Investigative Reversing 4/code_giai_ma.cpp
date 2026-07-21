#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void decodeFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return; // Bỏ qua nếu file không tồn tại
    }

    vector<unsigned char> enc_data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Bỏ qua 2019 byte header đầu tiên theo đúng mã giả v5 = 2019
    size_t offset = 2019;
    string extracted_chars = "";

    // Vòng lặp j chạy từ 0 đến 49 mô phỏng y hệt logic encodeDataInFile
    for (int j = 0; j <= 49; ++j) {
        if ((j % 5) != 0) {
            // Nếu j không chia hết cho 5: Lúc mã hóa, chương trình chép byte gốc và dịch offset 1 đơn vị
            offset += 1;
        } 
        else {
            // Nếu j chia hết cho 5: Lúc mã hóa, chương trình đã giấu 1 ký tự (8 bit) qua 8 pixel liên tiếp
            unsigned char char_val = 0;
            
            for (int k = 0; k <= 7; ++k) {
                unsigned char byte_enc = enc_data[offset];
                
                // Trích xuất bit LSB từ file ảnh
                unsigned char bit = byte_enc & 1;
                
                // Gom bit lại theo đúng trọng số bit thứ k
                char_val |= (bit << k);
                
                // Dịch offset qua pixel tiếp theo
                offset += 1;
            }
            
            extracted_chars += (char)char_val;
        }
    }

    cout << "Ket qua tu " << filename << ": " << extracted_chars << endl;
}

int main() {
    // Duyệt qua toàn bộ 5 file ảnh sản phẩm tương ứng với vòng lặp encodeAll
    for (int i = 1; i <= 5; ++i) {
        string filename = "Item0" + to_string(i) + "_cp.bmp";
        decodeFile(filename);
    }

    return 0;
}