#include <bits/stdc++.h>
using namespace std;

// 🔑 Tạo ma trận khóa 5x5 cho Playfair
vector<vector<char>> generateKeyMatrix(string key) {
    // Xử lý: loại bỏ chữ trùng lặp, đổi 'J' thành 'I'
    vector<bool> used(26, false);
    vector<vector<char>> matrix(5, vector<char>(5));
    string newKey = "";

    for (char c : key) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I'; // Quy ước: J = I
            if (!used[c - 'A']) {
                newKey += c;
                used[c - 'A'] = true;
            }
        }
    }

    // Thêm các ký tự còn lại của bảng chữ cái
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; // bỏ J vì đã gộp với I
        if (!used[c - 'A']) {
            newKey += c;
            used[c - 'A'] = true;
        }
    }

    // Điền vào ma trận 5x5
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = newKey[k++];
        }
    }
    return matrix;
}

// 🔍 Tìm vị trí của ký tự trong ma trận
pair<int,int> findPosition(vector<vector<char>>& matrix, char c) {
    if (c == 'J') c = 'I'; // quy ước I = J
    c = toupper(c);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) return {i, j};
        }
    }
    return {-1,-1};
}

// ✏️ Chuẩn bị văn bản: chia thành từng cặp (digraph)
string prepareText(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) result += toupper(c);
    }
    // Thêm X nếu 2 chữ cái liền nhau giống nhau hoặc nếu độ dài lẻ
    string prepared = "";
    for (int i = 0; i < result.size(); i++) {
        prepared += result[i];
        if (i + 1 < result.size() && result[i] == result[i+1]) {
            prepared += 'X'; // chèn X nếu trùng
        }
    }
    if (prepared.size() % 2 != 0) prepared += 'X'; // thêm X nếu lẻ
    return prepared;
}

// 🔒 Mã hóa Playfair
string playfairEncrypt(string text, vector<vector<char>>& matrix) {
    string prepared = prepareText(text);
    string result = "";

    for (int i = 0; i < prepared.size(); i += 2) {
        char a = prepared[i];
        char b = prepared[i+1];
        auto [r1, c1] = findPosition(matrix, a);
        auto [r2, c2] = findPosition(matrix, b);

        if (r1 == r2) {
            // Cùng hàng → lấy ký tự bên phải
            result += matrix[r1][(c1+1)%5];
            result += matrix[r2][(c2+1)%5];
        } else if (c1 == c2) {
            // Cùng cột → lấy ký tự bên dưới
            result += matrix[(r1+1)%5][c1];
            result += matrix[(r2+1)%5][c2];
        } else {
            // Hình chữ nhật → lấy ký tự cùng hàng, cột đối diện
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

// 🔓 Giải mã Playfair
string playfairDecrypt(string text, vector<vector<char>>& matrix) {
    string result = "";

    for (int i = 0; i < text.size(); i += 2) {
        char a = text[i];
        char b = text[i+1];
        auto [r1, c1] = findPosition(matrix, a);
        auto [r2, c2] = findPosition(matrix, b);

        if (r1 == r2) {
            // Cùng hàng → lấy ký tự bên trái
            result += matrix[r1][(c1+4)%5];
            result += matrix[r2][(c2+4)%5];
        } else if (c1 == c2) {
            // Cùng cột → lấy ký tự bên trên
            result += matrix[(r1+4)%5][c1];
            result += matrix[(r2+4)%5][c2];
        } else {
            // Hình chữ nhật → lấy ký tự cùng hàng, cột đối diện
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

int main() {
    string plainText, key;

    cout << "=== Playfair Cipher ===\n";
    cout << "Nhap van ban goc: ";
    getline(cin, plainText);

    cout << "Nhap khoa (chuoi ky tu): ";
    getline(cin, key);

    // Tạo ma trận khóa 5x5
    auto keyMatrix = generateKeyMatrix(key);

    // In ma trận khóa
    cout << "\nMa tran khoa (5x5):\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << keyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Mã hóa
    string cipherText = playfairEncrypt(plainText, keyMatrix);
    cout << "\nVan ban da ma hoa: " << cipherText << endl;

    // Giải mã
    string decryptedText = playfairDecrypt(cipherText, keyMatrix);
    cout << "Van ban da giai ma: " << decryptedText << endl;

    return 0;
}
