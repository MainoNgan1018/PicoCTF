#include <iostream>
#include <string>

using namespace std;

int main() {
    // Chuỗi bạn lấy được trực tiếp từ mystery.png
    string encrypted_data = "picoCTK.k5zsid6q_b3ea3199}";
    string original_flag = "";

    for (size_t i = 0; i < encrypted_data.length(); ++i) {
        char c = encrypted_data[i];
        if (i <= 5) {
            // for (i = 0; i <= 5) -> fputc(ptr[i], v8)
            original_flag += c;
        } 
        else if (i >= 6 && i <= 14) {
            // for (i = 6; i <= 14) -> fputc((char)(ptr[i] + 5), v8)
            // Giải mã ngược: trừ 5
            original_flag += (char)(c - 5);
        } 
        else if (i == 15) {
            // ptr[15] -> fputc((char)(ptr[15] - 3), v8)
            // Giải mã ngược: cộng 3
            original_flag += (char)(c + 3);
        } 
        else {
            // for (j = 16; j <= 25) -> fputc((char)ptr[j], v8)
            original_flag += c;
        }
    }

    cout << "Flag chuan:" << endl;
    cout << original_flag << endl;

    return 0;
}