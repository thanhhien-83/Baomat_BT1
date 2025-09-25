# Baomat_BT1  
# BAI_TAP_1  
# TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN  
Caesar  
Affine  
Hoán vị  
Vigenère  
Playfair  

# Với mỗi phương pháp, hãy tìm hiểu:  
Tên gọi  
Thuật toán mã hoá, thuật toán giải mã  
Không gian khóa  
Cách phá mã (mà không cần khoá)  
Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript  
# Thuật toán 2: Caesar.
# Tên gọi: 
Caesar cipher (mã Caesar) — một thuật toán mã hóa cổ điển đặt theo tên Julius Caesar. Nó là hình thức thay thế đơn giản: dịch mỗi chữ cái một số vị trí cố định trong bảng chữ cái.  
# Thuật toán mã hoá và giải mã:  
Quy ước: ánh xạ chữ cái → số: a=0, b=1, ..., z=25.
Khóa: số nguyên k (0..25).  
Mã hoá: C=(P+k)mod26  
Giải mã: P=(C−k+26)mod26  
# Không gian khóa:   
Khóa k có 26 giá trị khả dĩ (0..25).  
Kích thước không gian khóa = 26 (thực tế 25 khóa hữu dụng nếu bỏ k=0).  
→ Rất nhỏ, dễ phá bằng brute-force.  
# Phá mã:  
brute-force (thử 26) là đủ; phân tích tần suất giúp tự động hóa.  
Code C++ và web ở trên cho phép bạn mã hoá/giải mã và thử brute-force; cả hai đều chuyển đầu vào về chữ thường trước xử lý.  
# Hình ảnh kiểm thử: 
# Mã Hóa  
<img width="1422" height="752" alt="image" src="https://github.com/user-attachments/assets/97fd6498-c1d1-46dd-889f-e9f133b59dc5" />  

# Giải Mã
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/3ff90397-0f77-41ab-9e81-c0dcaecc9eba" />  
# Thuật toán 2: Affine 
# Tên gọi: 
Affine cipher — mã Affine (một substitution cipher tuyến tính).  
# Thuật toán mã hoá & giải mã (ngắn gọn)  
Quy ước: a=0, b=1, ..., z=25 (xử lý chữ thường).  
Khóa gồm hai số nguyên: a và b.  
Mã Hóa: c=(a⋅p+b)mod26  
Giải Mã: cần nghịch đảo modular a^{-1} (mod 26), gọi là a_inv:  
  p=ainv​⋅(c−b)mod26  
# Không gian khóa
a phải nguyên tố cùng nhau với 26: các giá trị hợp lệ:
1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25 → 12 giá trị.

b có thể là 0..25 → 26 giá trị.
Tổng không gian khóa = 12 * 26 = 312 cặp (a,b).
# Cách phá mã (không cần khóa) — ngắn gọn
Brute-force: thử hết 312 cặp (a,b) và kiểm tra kết quả (bằng mắt hoặc bằng dictionary) — nhanh.

Phân tích tần suất: giống substitution — nếu ciphertext đủ dài, map ký tự hay xuất hiện nhất về ký tự phổ biến → suy a,b.

Known-plaintext (crib): biết một đoạn plaintext → giải nhanh a,b.
Kết luận: Affine không an toàn cho ứng dụng thật vì không gian khóa nhỏ và có thể brute-force.

# Hình ảnh kiểm thử: 
# Mã Hóa
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/ed0e298e-7331-42d3-b021-58b9d301f4e6" />

# Giải Mã
![Uploading image.png…]()














     
