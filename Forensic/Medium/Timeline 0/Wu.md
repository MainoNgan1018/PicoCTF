Bài này mình giải bằng 2 cách:

## Sử dụng Autopsy:

Vào timeline:

Nhìn phần thời gian ta thấy thời điểm bắt đầu là Jan2, 1985, đây là một mốc thời gian quá xa và cũ so với thời gian kết thúc vào 2025.

Đây là kĩ thuật Sloppy Timestomping:

- Timestomping là hành động chỉnh sửa các thông tin thời gian (ngày tạo, ngày truy cập, ngày sửa đổi) để nó trông hợp pháp, hợp lý.

- Nó thêm Sloppy (cầu thả) ám chỉ việc thay đổi nhưng không đồng bộ, logic , có lỗ hổng để nhà phân tích phát hiện.

<img width="1999" height="873" alt="image23" src="https://github.com/user-attachments/assets/265a0721-538f-4b74-aa39-4360b3014216" />

Lướt lên vào file đó và nó hiện ra flag dạng base64 ở phần File Metadata.

<img width="1999" height="943" alt="image17" src="https://github.com/user-attachments/assets/7259ba7c-e1ac-44ee-bb3d-0ed069fa1204" />

## Sử dụng Sleuthkit

Các bước làm giống hệt bài Timeline 1 để tạo Mactime.

<img width="1999" height="231" alt="image9" src="https://github.com/user-attachments/assets/3080f347-339f-476f-b918-67e383418679" />

Vì cũng biết cờ ở đâu rồi nên mình icat luôn nội dung file đó.

<img width="1999" height="139" alt="image8" src="https://github.com/user-attachments/assets/50152d39-3031-4975-95cb-9ca420a79f46" />

Flag: picoCTF{71m311n3_0u7113r_h3r_43a2e7af}
