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

# Tên gọi: Mật mã Caesar.  
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
