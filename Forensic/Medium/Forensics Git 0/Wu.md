Cho file vào FTK để nhìn qua.
<img width="1024" height="455" alt="image" src="https://github.com/user-attachments/assets/5ab85ac6-31b8-4215-a37c-5128ad42c902" />
Vào wsl sử dụng SleuthKit-TSK
### Xác định offset của phân vùng
```
mmls disk.img
```

<img width="2087" height="505" alt="image" src="https://github.com/user-attachments/assets/0a19654f-e90a-4cab-ad1e-f4e35c9e9e46" />
Có 2 phân vùng:
* Phân vùng 1: bắt đầu tại sector 2048
* Phân vùng 2: bắt đầu tại sector 1140736
Linux Swap / Solaris x86 (0x82) là phân vùng Swap (bộ nhớ ảo). Nó không phải là một hệ thống tập tin có thư mục, file hay inode như ext4. Ní là một vùng nhớ đệm mà hệ điều hành dùng để tràn dữ liệu RAM sang đĩa khi hết bộ nhớ.

Vì thế các lệnh như fls hay icat sẽ không thể hoạt động trên phân vùng này.

Khi phân tích ta sẽ bỏ qua các phân vùng như Swap hay Extended Partition ( là cái container chứa các phân vùng logic khác ) hoặc các phân vùng EFI/Boot nhỏ lẻ.

### Kiệt kê toàn bộ file, bao gồm cả file đã xóa có ký hiệu *
```
fls -r -o <offset> disk.img
```

<img width="2230" height="737" alt="image" src="https://github.com/user-attachments/assets/605035a7-b1dc-4ae9-94a6-7aad42add09e" />
<img width="2412" height="1200" alt="image" src="https://github.com/user-attachments/assets/885faab3-cc7f-459b-8342-95e1d0149c49" />
Phân vùng 2 là phân vùng chứa dữ liệu người dùng, còn phân vùng 1 chỉ là phân vùng /boot.

Kiểm tra thư mục `secrets` nằm ở inode 65665. Liệt kê nội dung của thư mục đó:
```
mainosenpai@DESKTOP-E956SQ4:/mnt/c/Users/ADMIN/Downloads/disk.img$ fls -r -o 1140736 disk.img 65665
d/d 65666:      branches
r/r 65667:      description
d/d 65668:      hooks
+ r/r 65669:    applypatch-msg.sample
+ r/r 65670:    pre-commit.sample
+ r/r 65671:    commit-msg.sample
+ r/r 65672:    pre-push.sample
+ r/r 65673:    pre-applypatch.sample
+ r/r 65674:    post-update.sample
+ r/r 65675:    sendemail-validate.sample
+ r/r 65676:    pre-rebase.sample
+ r/r 65677:    pre-receive.sample
+ r/r 65678:    update.sample
+ r/r 65679:    push-to-checkout.sample
+ r/r 65680:    pre-merge-commit.sample
+ r/r 65681:    prepare-commit-msg.sample
d/d 65682:      info
+ r/r 65683:    exclude
d/d 65684:      refs
+ d/d 65686:    heads
++ r/r 65702:   master
+ d/d 65687:    tags
r/r 65685:      config
d/d 65689:      objects
+ d/d 65690:    pack
+ d/d 65691:    info
+ d/d 65694:    46
++ r/r 65695:   064ac3ab7afd9a95bc1224aa8b4cef23741fcc
+ d/d 65697:    18
++ r/r 65698:   6ca660f488a4e4cdd92e7678fcfa3da478aee7
+ d/d 65699:    32
++ r/r 65700:   7681bb38cf467cec328eec9707b240e3e74ced
r/r 65688:      HEAD
r/r 65662:      index
r/r 65693:      COMMIT_EDITMSG
d/d 65703:      logs
+ r/r 65704:    HEAD
+ d/d 65705:    refs
++ d/d 65706:   heads
+++ r/r 65707:  master
```
### Trích xuất file đó:
```
icat -o <offset> disk.img <inode_number> > recovered_file
```
Xem các tin nhắn commit qua file COMMIT_EDITMSG:

<img width="2360" height="85" alt="image" src="https://github.com/user-attachments/assets/9bf5db8d-8984-4c9f-92cb-14b5a359dd1b" />

Flag: picoCTF{g17_1n_7h3_d15k_041217d8}
