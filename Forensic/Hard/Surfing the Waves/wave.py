import string
from scipy.io import wavfile

# Đọc file âm thanh
_, audio_data = wavfile.read('main.wav')

# Lấy các giá trị (bỏ phần đuôi nhiễu nhỏ ở các chữ số cuối nếu có, hoặc làm tròn theo cụm 16 mốc)
# Dựa trên phân tích, các giá trị chia hết cho 500 hoặc có quy luật 16 mốc giá trị duy nhất:
rounded_data = [int(str(data)[:2]) for data in audio_data]

# Lấy danh sách các giá trị độc nhất và sắp xếp lại
unique_data = list(set(rounded_data))
unique_data.sort()

flag_hex = []
for encoded_hex_char in rounded_data:
    # Ánh xạ giá trị về vị trí trong hệ hex (0-15)
    decimal_hex_char = unique_data.index(encoded_hex_char)
    hex_char = hex(decimal_hex_char)[2:]
    flag_hex.append(hex_char)

# Ghép các ký tự hex lại và chuyển về chuỗi ASCII (Flag)
hex_str = "".join(flag_hex)
try:
    print(bytearray.fromhex(hex_str).decode())
except Exception as e:
    print("Hex string:", hex_str)