Mở file ta thấy một loạt gói tin TCP nhưng Info ghi [TCP Retransmission] chứng tỏ hệ thống đang đánh dấu đây là các gói tin truyền lại.

Thông thường, một gói tin [SYN] để bắt tay ba bước sẽ không chứa dữ liệu (tức là Len=0).

Tuy nhiên, ở đây các gói tin lại có Len=8, Len=12, và Len=4 chứng tỏ gói đã bị nhét thêm dữ liệu thô.

<img width="1199" height="556" alt="image" src="https://github.com/user-attachments/assets/71f08adc-7d2a-4436-b5d2-63d5a41eb8f2" />

Nhìn vào phần Data của các gói tin ta thấy các chuỗi như bnR..==,...

Nhưng những chuỗi có 2 dấu = thì chỉ ở gói mà len=12 là đặc trưng của Base64, còn như gói len=8 thì chỉ có 1 dấu = và nó không thực sự giống base64.

<img width="1202" height="534" alt="image" src="https://github.com/user-attachments/assets/dd5d75a2-332e-4ee9-aad4-e775973226bb" />

Nếu để nguyên số thứ tự thì các chuỗi Base64 này bị lộn xộn nên ta để ý cột Time

Chỉnh cột time bằng cách click vào nó chuyển đúng về thứ tự mình muốn hoặc:

`View → Time Display Format → Seconds Since First Captured Packets`

<img width="1175" height="593" alt="image" src="https://github.com/user-attachments/assets/be26c08e-b0de-4bc8-858f-a8ff3916c73d" />

Sau khi đúng thứ tự thì ta sẽ lấy các phần payload trong các gói length 12 với length 4.

<img width="1169" height="131" alt="image" src="https://github.com/user-attachments/assets/4fe19c9f-0243-4c63-b98f-2c5f14ecea84" />

Cách lấy chuỗi ra:

`Chuột phải vào TCP payload -> Show Packet Bytes`

<img width="1932" height="540" alt="image28" src="https://github.com/user-attachments/assets/91f0ba95-4da8-4d5a-ab0e-d92cc25d211f" />

Cho lần lượt vào CyberChef để giải mã:
<img width="1999" height="869" alt="image12" src="https://github.com/user-attachments/assets/30926cd2-31e7-489b-a036-8af600e59f84" />

Flag: picoCTF{1t_w4snt_th4t_34sy_tbh_4r_966d0bfb}
