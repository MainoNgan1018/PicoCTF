Đây là chall về tấn công vào mạng không dây (Wi-Fi), cụ thể là bẻ khóa mật khẩu WPA/WPA2 thông qua việc bắt gói tin "4-way handshake".

Bắt tay 4 bước trong WPA2 là một quy trình xác thực mật khẩu mà không bao giờ gửi mật khẩu thực sự qua không trung giữa 2 bên (Client và Access Point - AP).

Trước khi bắt tay, cả Client và AP đều biết trước tên mạng (SSID), mật khẩu WiFi và Pairwise Master Key (PMK - được tạo ra từ mật khẩu và SSID).

### Quy trình 4-Way Handshake (WPA2)

Quy trình này giúp Client và Access Point (AP) xác thực lẫn nhau mà không cần gửi mật khẩu trực tiếp qua không trung.
```
| Bước | Người gửi | Thông điệp / Nội dung | Mục đích |
| :--- | :--- | :--- | :--- |
| **1** | AP | Gửi **ANonce** (giá trị ngẫu nhiên từ AP) | AP thách thức Client chứng minh danh tính. |
| **2** | Client | Gửi **SNonce** (giá trị ngẫu nhiên từ Client) + **MIC** | Client tính toán MIC dựa trên mật khẩu và gửi lại để chứng minh mình biết mật khẩu. |
| **3** | AP | Gửi xác nhận + **GTK** (Group Temporal Key) | AP xác nhận Client đúng, gửi khóa mã hóa dữ liệu. |
| **4** | Client | Gửi xác nhận cuối cùng | Hoàn tất bắt tay, bắt đầu truyền dữ liệu an toàn. |
```

> **Lưu ý:** `aircrack-ng` hoạt động bằng cách bắt các gói tin này, sau đó thử các mật khẩu từ wordlist (dictionary attack) để tạo ra một giá trị MIC giả lập. Nếu MIC giả lập khớp với MIC thực tế trong gói tin bắt được, đó chính là mật khẩu đúng.

Sử dụng Aircrack-ng:
```
aircrack-ng wpa-ing_out.pcap -w /đường/dẫn/đến/rockyou.txt
```

```
mainosenpai@DESKTOP-E956SQ4:/mnt/c/Users/ADMIN/Downloads$ aircrack-ng wpa-ing_out.pcap -w /mnt/c/Users/ADMIN/Documents/rockyou.txt
Reading packets, please wait...
Opening wpa-ing_out.pcap
Resetting EAPOL Handshake decoder state.
Resetting EAPOL Handshake decoder state.
Read 23523 packets.

   #  BSSID              ESSID                     Encryption

   1  00:5F:67:4F:6A:1A  Gone_Surfing              WPA (1 handshake)

Choosing first network as target.

Reading packets, please wait...
Opening wpa-ing_out.pcap
Resetting EAPOL Handshake decoder state.
Resetting EAPOL Handshake decoder state.
Read 23523 packets.

1 potential targets

                               Aircrack-ng 1.7

      [00:00:00] 1547/10303727 keys tested (16107.27 k/s)

      Time left: 10 minutes, 39 seconds                          0.02%

                          KEY FOUND! [ mickeymouse ]


      Master Key     : 61 64 B9 5E FC 6F 41 70 70 81 F6 40 80 9F AF B1
                       4A 9E C5 C4 E1 67 B8 AB 58 E3 E8 8E E6 66 EB 11

      Transient Key  : 26 85 7B AC DD 2C 44 E6 06 18 03 B0 0F F2 75 A2
                       32 63 F7 35 74 2D 18 10 1C 25 F9 14 BC 41 DA 58
                       52 48 86 B0 D6 14 89 F6 77 00 67 E0 AD 10 1B 00
                       00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

      EAPOL HMAC     : 65 2F 6C 0E 75 F0 49 27 6A AA 6A 06 A7 24 B9 A9
```
Mật khẩu mạng Wifi bẻ khóa được : mickeymouse.

Flag: picoCTF{mickeymouse}
