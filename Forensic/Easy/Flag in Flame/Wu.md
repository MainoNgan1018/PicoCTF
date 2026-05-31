Mở file `logs.txt` ta thấy là đoạn văn bản Base64

<img width="1130" height="451" alt="image" src="https://github.com/user-attachments/assets/7242c6d0-473f-41ef-805f-f6a5e0faa574" />

Giải mã bằng công cụ CyberChef:

Ta thấy ở phần Output là định dạng của một file ảnh PNG với các chunk IHDR, IDAT..

<img width="1999" height="1050" alt="image22" src="https://github.com/user-attachments/assets/5b8609dd-8e8b-4b9b-b52a-bbf254cbc593" />

Bấm vào ` Save ouput to file ` - biểu tượng nằm ở góc trên cùng bên phải của ô Output trong CyberChef để xuất ra ảnh.

Mở file ảnh và lấy mã hex:

<img width="1999" height="1011" alt="image7" src="https://github.com/user-attachments/assets/5a1df384-24ad-4f9d-b6fe-5dd3629ac1c4" />

Cho lên CyberChef và dùng model `From Hex`:

<img width="1999" height="1074" alt="image26" src="https://github.com/user-attachments/assets/eea3a5f9-c9ce-4aae-aaf2-9621b882e977" />

Flag: picoCTF{forensics_analysis_is_amazing_be860279}
