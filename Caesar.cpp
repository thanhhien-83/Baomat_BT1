#include <bits/stdc++.h>
using namespace std;

// Hàm Caesar mã hóa
// Dịch chuyển mỗi ký tự chữ cái sang phải theo khóa k
// Công thức: C = (P + k) mod 26
string caesarEncrypt(string text, int key) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) { // kiểm tra có phải chữ cái không
            char base = isupper(c) ? 'A' : 'a'; // xác định bảng chữ cái (hoa/thường)
            result += char((c - base + key) % 26 + base); // dịch chuyển ký tự
        } else {
            result += c; // nếu không phải chữ thì giữ nguyên
        }
    }
    return result;
}

// Hàm Caesar giải mã
// Dịch ngược lại theo khóa k
// Công thức: P = (C - k + 26) mod 26
string caesarDecrypt(string text, int key) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base - key + 26) % 26 + base); // dịch ngược
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string plainText, cipherText;
    int key;

    cout << "=== Caesar Cipher ===\n";

    // Nhập văn bản gốc
    cout << "Nhap van ban goc: ";
    getline(cin, plainText);

    // Nhập khóa k (số dịch chuyển)
    cout << "Nhap khoa (key): ";
    cin >> key;
    key = key % 26; // đảm bảo khóa nằm trong phạm vi 0–25

    // --- Bước 1: Mã hóa ---
    cipherText = caesarEncrypt(plainText, key);
    cout << "\nVan ban da ma hoa: " << cipherText << endl;

    // --- Bước 2: Giải mã ---
    // Người dùng nhập lại văn bản đã mã hóa để kiểm tra
    string inputCipher;
    cout << "\nNhap van ban da ma hoa de giai ma: ";
    cin.ignore(); // loại bỏ ký tự thừa trong bộ đệm
    getline(cin, inputCipher);

    // Thực hiện giải mã
    string decryptedText = caesarDecrypt(inputCipher, key);
    cout << "Van ban da giai ma: " << decryptedText << endl;

    return 0;
}
