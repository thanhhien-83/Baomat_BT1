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

# Thuật toán 1: Caesar.
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
# Cách phá mã:  
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
<img width="1600" height="847" alt="image" src="https://github.com/user-attachments/assets/daf0a1b9-1f42-41be-8bbc-53ea6418b956" />  

# Thuật toán 3: Hoán vị  
# Tên gọi
Permutation cipher — mã hoán vị (thuộc nhóm transposition cipher).  

# Thuật toán mã hoá & giải mã  
Ý tưởng: giữ nguyên ký tự nhưng đổi vị trí theo một khóa là hoán vị (ví dụ khóa độ dài n).  
Chia văn bản gốc thành các khối (block) có độ dài n.  
Với mỗi block:  
Mã hoá: hoán đổi vị trí ký tự trong block theo thứ tự của khóa.  
Giải mã: áp dụng hoán vị ngược để đưa ký tự về vị trí ban đầu.  

# Không gian khóa  
Với độ dài block = n, số hoán vị = n!. 
 
# Cách phá mã (không cần khóa)  
Brute-force: thử tất cả hoán vị có thể (nhỏ thì khả thi).  
Phân tích mẫu từ: nhìn cấu trúc chữ (bigram, trigram).  
Phân tích tần suất: vị trí xuất hiện lặp lại → đoán cấu trúc khối.  

# Hình ảnh kiểm thử:  
# Mã Hóa  
<img width="1541" height="885" alt="image" src="https://github.com/user-attachments/assets/0f372e2c-11fe-4584-b2eb-3532a394c99f" />  

# Giải Mã
<img width="1462" height="820" alt="image" src="https://github.com/user-attachments/assets/773587df-7c1b-4a77-a01b-115131ba601f" />  


# Thuật toán 4:Vigenère  
# Tên gọi  
Mã hóa Vigenère (Vigenère Cipher) – thuật toán thay thế đa bảng (polyalphabetic substitution).  
# Thuật toán mã hóa và giải mã
Mã hóa: Ci​=(Pi​+Ki​)mod26
Giải mã: Pi​=(Ci​−Ki​+26)mod26
#  Không gian khóa  
Khóa là chuỗi chữ cái độ dài tùy ý.  

Nếu chỉ dùng bảng chữ cái 26 chữ: số lượng khóa là (26)^𝑚  
với m = độ dài khóa.  
# Cách phá mã (không cần khóa)  
Phân tích tần suất nâng cao: tìm độ dài khóa bằng phương pháp Kasiski hoặc chỉ số trùng hợp (IC – Index of Coincidence).  
Sau đó coi mỗi cột như Caesar Cipher để phá.  
Tuy an toàn hơn Caesar, nhưng vẫn phá được nếu văn bản đủ dài  

# Hình ảnh kiểm thử: 
# Mã Hóa  
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/de7176dc-87bc-47c9-8f3d-02a21bd5efaf" />  

# Giải Mã
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/5f77f9b6-a754-4421-b933-92300c94074d" />  

# Thuật toán 5: Playfair 
# Tên gọi  
Mã hóa Playfair (Playfair Cipher) – là một dạng mã hóa thay thế theo cặp ký tự (digraph substitution cipher).  
# Thuật toán mã hóa và giải mã  
Bước 1: Tạo ma trận khóa 5×5 từ một từ khóa (loại bỏ trùng, gộp J = I).  
Bước 2: Chia văn bản gốc thành từng cặp chữ cái (digraph). Nếu hai chữ cái giống nhau → chèn thêm ‘X’. Nếu còn dư một chữ cái → thêm ‘X’.  
Bước 3: Quy tắc mã hóa:  
Hai chữ cái cùng hàng → thay bằng chữ bên phải (vòng tròn sang trái nếu ở cuối).  
Hai chữ cái cùng cột → thay bằng chữ bên dưới.  
Khác hàng & cột → mỗi chữ thay bằng chữ ở góc còn lại cùng hàng.  
Bước 4: Giải mã → làm ngược lại (trái thay phải, trên thay dưới).  
#  Không gian khóa  
Có 25! khả năng sắp xếp ma trận khóa (rất lớn).  
Nhưng trên thực tế phụ thuộc vào độ dài và nội dung từ khóa.  
# Cách phá mã (không cần khóa)  
Dùng phân tích tần suất cặp chữ (digraph frequency analysis).  
Với đủ văn bản, có thể suy ra khóa vì tiếng Anh (hay tiếng Việt) có các cặp xuất hiện phổ biến.  

# Hình ảnh kiểm thử:  
# Mã Hóa  
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/d80c602e-c3c2-481a-933e-b6c47e3cd320" />  

# Giải mã  
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/35c19aab-2882-4b59-b150-d0edf70763ff" />


















     
