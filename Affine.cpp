#include <bits/stdc++.h>
using namespace std;

// Hàm tìm nghịch đảo modular của a theo mod m (dùng Extended Euclidean)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // không tồn tại nghịch đảo
}

// Hàm mã hóa Affine
string affineEncrypt(string text, int a, int b) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; 
            // E(x) = (a*x + b) mod 26
            result += char(((a * (c - base) + b) % 26) + base);
        } else {
            result += c; // giữ nguyên ký tự đặc biệt
        }
    }
    return result;
}

// Hàm giải mã Affine
string affineDecrypt(string text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26); // tìm nghịch đảo a theo mod 26
    if (a_inv == -1) {
        return "Khong ton tai nghich dao modular. Khoa a khong hop le!";
    }
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // D(x) = a_inv * (y - b) mod 26
            int y = c - base;
            int decrypted = (a_inv * (y - b + 26)) % 26;
            result += char(decrypted + base);
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string plainText, cipherText;
    int a, b;

    cout << "=== Affine Cipher ===\n";
    cout << "Nhap van ban goc: ";
    getline(cin, plainText);

    cout << "Nhap khoa a (nguyen to cung nhau voi 26): ";
    cin >> a;
    cout << "Nhap khoa b: ";
    cin >> b;

    // Mã hóa
    cipherText = affineEncrypt(plainText, a, b);
    cout << "\nVan ban da ma hoa: " << cipherText << endl;

    // Giải mã
    string decryptedText = affineDecrypt(cipherText, a, b);
    cout << "Van ban da giai ma: " << decryptedText << endl;

    return 0;
}
