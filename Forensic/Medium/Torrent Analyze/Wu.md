Vì bài liên quan đến giao thức BitTorrent nên ta sẽ filter bt-dht trong Wireshark.

<img width="2827" height="1170" alt="image" src="https://github.com/user-attachments/assets/09ce90a4-2f1b-4963-b5e5-02895f00efd8" />

Lọc toàn bộ kí tự sau Info_hash và ta tập trung vào chuỗi xuất hiện với tần suất lớn:
```
e2467cbf021192c241367b892230dc1e05c0580e
```

Cho mã hash lên phần tìm kiếm của VirusTotal:

<img width="3817" height="1955" alt="image" src="https://github.com/user-attachments/assets/a4c7fd1e-fe74-4e53-8946-9203cfe0a729" />

Flag: picoCTF{ubuntu-19.10-desktop-amd64.iso}
