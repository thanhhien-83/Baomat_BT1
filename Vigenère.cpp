#include <bits/stdc++.h>
using namespace std;

// 🔑 Hàm mở rộng khóa sao cho có độ dài bằng văn bản gốc
string generateKey(string text, string key) {
    int n = text.size();
    string newKey = key;
    // Lặp lại các ký tự của key cho đến khi đủ độ dài
    for (int i = 0; newKey.size() < n; i++) {
        newKey += key[i % key.size()];
    }
    return newKey;
}

// 🔒 Hàm mã hóa Vigenère
string vigenereEncrypt(string text, string key) {
    string result = "";
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        if (isalpha(c)) { // Nếu là chữ cái
            char base = isupper(c) ? 'A' : 'a'; // Xác định viết hoa/thường
            // (c - base): đưa ký tự về dạng số (0-25)
            // (tolower(key[i]) - 'a'): giá trị dịch từ ký tự khóa
            // Cộng vào và mod 26 để đảm bảo trong bảng chữ cái
            result += char((c - base + (tolower(key[i]) - 'a')) % 26 + base);
        } else {
            result += c; // Nếu không phải chữ cái thì giữ nguyên
        }
    }
    return result;
}

// 🔓 Hàm giải mã Vigenère
string vigenereDecrypt(string text, string key) {
    string result = "";
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // Giải mã thì trừ đi giá trị của ký tự khóa
            // +26 để tránh số âm, rồi mod 26
            result += char((c - base - (tolower(key[i]) - 'a') + 26) % 26 + base);
        } else {
            result += c; // Ký tự không phải chữ cái giữ nguyên
        }
    }
    return result;
}

int main() {
    string plainText, key;

    cout << "=== Vigenere Cipher ===\n";
    cout << "Nhap van ban goc: ";
    getline(cin, plainText); // Nhập chuỗi cần mã hóa

    cout << "Nhap khoa (chuoi ky tu): ";
    getline(cin, key); // Nhập chuỗi khóa (ví dụ: KEY)

    // 🔑 Sinh khóa có độ dài bằng văn bản gốc
    string fullKey = generateKey(plainText, key);

    // Thực hiện mã hóa
    string cipherText = vigenereEncrypt(plainText, fullKey);
    cout << "\nVan ban da ma hoa: " << cipherText << endl;

    // Thực hiện giải mã (từ văn bản mã hóa và cùng khóa)
    string decryptedText = vigenereDecrypt(cipherText, fullKey);
    cout << "Van ban da giai ma: " << decryptedText << endl;

    return 0; // Kết thúc chương trình
}
