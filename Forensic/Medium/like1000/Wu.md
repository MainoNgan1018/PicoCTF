Mở file ra thì ta thấy có 999 tệp .rar được giải nén y hệt và ta check vài tệp đầu, mỗi tệp chứa file filler.txt với nội dung y như nhau.

Ta không chắc là trong các tệp chỉ có file .txt y như vậy hay không mà có thể ở tệp nào đó chứa flag.

Tạo Script quét check từng tệp .tar và kiểm tra xem trong đó có file fillter.txt y hệt không, nếu giống thì xóa cả tệp .tar đi để tiết kiệm dung lượng rồi kiểm tra tiếp.

Script Python:
```bash
import tarfile
import os
import hashlib

def get_md5(filename):
    if not os.path.exists(filename):
        return None
    with open(filename, 'rb') as f:
        return hashlib.md5(f.read()).hexdigest()

# Hash của file filler.txt rác ban đầu để làm mẫu so sánh
# (Bạn có thể chạy thử 1 lần để lấy hash chuẩn hoặc để script tự nhận diện thay đổi)
known_bad_hash = None 

current_dir = os.getcwd()

while True:
    # Tìm file .tar trong thư mục
    tar_files = [f for f in os.listdir('.') if f.endswith('.tar')]
    
    if not tar_files:
        print("Đã giải nén hết các tầng tar.")
        break
        
    tar_filename = tar_files[0]
    print(f"Đang xử lý: {tar_filename}")
    
    try:
        # Mở và giải nén
        with tarfile.open(tar_filename) as tar:
            tar.extractall()
            
        # Sau khi giải nén thành công, xóa file tar cũ đi
        os.remove(tar_filename)
        
        # Kiểm tra file filler.txt sau khi giải nén
        if os.path.exists('filler.txt'):
            current_hash = get_md5('filler.txt')
            
            if known_bad_hash is None:
                known_bad_hash = current_hash
                print(f"[+] Đã ghi nhận MD5 mẫu của filler.txt: {known_bad_hash}")
            
            elif current_hash != known_bad_hash:
                print(f" NYA! Phát hiện filler.txt có nội dung KHÁC BIỆT tại tầng giải nén của {tar_filename}!")
                print(f"MD5 mới: {current_hash}")
                # Đổi tên để không bị file tầng sau ghi đè
                os.rename('filler.txt', f'flag_candidate_{tar_filename}.txt')
                
    except Exception as e:
        print(f"Lỗi khi giải nén {tar_filename}: {e}")
        break

print("Kiểm tra thư mục hiện tại để xem kết quả cuối cùng!")
```
Kết quả mở `File Explore` và ta có:
<img width="2851" height="974" alt="image" src="https://github.com/user-attachments/assets/5c1421b4-6d8d-478e-b91d-5726d6850de8" />


Flag: picoCTF{l0t5_0f_TAR5}
