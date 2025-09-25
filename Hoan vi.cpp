#include <bits/stdc++.h>
using namespace std;

// ===== Hàm mã hóa =====
string permutationEncrypt(string text, vector<int> key) {
    int n = key.size();
    string result = "";
    while (text.size() % n != 0) {
        text += 'X';
    }
    for (int i = 0; i < text.size(); i += n) {
        string block = text.substr(i, n);
        string newBlock(n, ' ');
        for (int j = 0; j < n; j++) {
            newBlock[j] = block[key[j] - 1];
        }
        result += newBlock;
    }
    return result;
}

// ===== Hàm giải mã =====
string permutationDecrypt(string text, vector<int> key) {
    int n = key.size();
    string result = "";
    for (int i = 0; i < text.size(); i += n) {
        string block = text.substr(i, n);
        string newBlock(n, ' ');
        for (int j = 0; j < n; j++) {
            newBlock[key[j] - 1] = block[j];
        }
        result += newBlock;
    }
    return result;
}

int main() {
    string plainText;
    int n;

    cout << "=== Permutation Cipher ===\n";
    cout << "Nhap van ban goc: ";
    getline(cin, plainText);

    cout << "Nhap do dai khoa (block size): ";
    cin >> n;
    cin.ignore(); // fix lỗi nhập

    vector<int> key(n);
    cout << "Nhap khoa hoan vi (vd: 3 1 4 2 neu block size=4): ";
    for (int i = 0; i < n; i++) cin >> key[i];

    // Mã hóa
    string cipherText = permutationEncrypt(plainText, key);
    cout << "\nVan ban da ma hoa: " << cipherText << endl;

    // Giải mã
    string decryptedText = permutationDecrypt(cipherText, key);
    cout << "Van ban da giai ma: " << decryptedText << endl;

    return 0;
}
