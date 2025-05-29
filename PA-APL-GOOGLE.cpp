#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <conio.h> 
#include <limits>

using namespace std;

const int MAX_BARANG = 100;
const int MAX_USER = 100;
const int MAX_NAMA_BARANG = 25;
const int MAX_USERNAME_PASSWORD = 15;

struct Barang {
    string nama;
    string jenis;
    int jumlah;
};

struct User {
    string username;
    string password;
};

struct VapeStore {
    Barang barang[MAX_BARANG];
    User users[MAX_USER];
    int jumlahBarang = 6;
    int jumlahUser = 0;
};

void printWithColor(const string& text, const string& color) {
    string colorCode;
    if (color == "red") colorCode = "\033[31m"; 
    else if (color == "green") colorCode = "\033[32m"; 
    else if (color == "yellow") colorCode = "\033[33m"; 
    else if (color == "blue") colorCode = "\033[34m";   
    else if (color == "cyan") colorCode = "\033[36m";   
    else colorCode = "\033[0m"; 
    cout << colorCode << text << "\033[0m"; 
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getInputWithValidation(const string& prompt, int maxLength = 0) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.find_first_not_of(' ') == string::npos) {
            printWithColor("Input tidak boleh hanya spasi!\n", "red");
            continue;
        }
        if (input.empty()) {
            printWithColor("Input tidak boleh kosong!\n", "red");
            continue;
        }
        
        if (maxLength > 0 && input.length() > maxLength) {
            printWithColor("Input tidak boleh lebih dari " + to_string(maxLength) + " karakter!\n", "red");
            continue;
        }
        
        break;
    }
    return input;
}

void tampilkanMenuLogin();
void prosesLogin(VapeStore* store, bool* loginBerhasil, bool* isAdmin); 
void prosesRegister(VapeStore* store); 
void tampilkanMenuUser();
void tampilkanMenuAdmin();
void tampilkanBarang(VapeStore* store); 
void tambahBarang(VapeStore* store); 
void ubahBarangDenganPointer(Barang* barang, int jumlahBarang); 
void hapusBarang(VapeStore* store); 
void tampilkanHeaderTabel();
void tampilkanBarisBarang(Barang* barang, int index); 
void tampilkanFooterTabel();
int hitungTotalBarang(VapeStore* store); 
int hitungTotalBarangByJenis(VapeStore* store, string* jenis);
void tampilkanInfoTotalBarang(VapeStore* store); 

void bubbleSortAscendingHuruf(Barang arr[], int n);
void selectionSortDescendingAngka(Barang arr[], int n);
void quickSortAscendingHuruf(Barang arr[], int low, int high);
int partition(Barang arr[], int low, int high);
void menuSortingUser(VapeStore* store);
void menuSortingAdmin(VapeStore* store);
void menuSearchUser(VapeStore* store);
void tulisanIndah();

string masukkanPassword() {
    string password;
    char ch;

    cout << "Password: ";
    while (true) {
        ch = _getch();

        if (ch == '\r') { 
            break;
        } else if (ch == '\b') { 
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; 
            }
        } else {
            password += ch;
            cout << '*'; 
        }
    }
    cout << endl;
    
    if (password.empty()) {
        printWithColor("Password tidak boleh kosong!\n", "red");
        return masukkanPassword();
    }
    
    return password;
}

int main() {
    VapeStore store = {
         {
            {"Oxva xlim GO", "Device", 10}, 
            {"Voopoo Drag X", "Device", 7}, 
            {"TRML T99", "Device", 5}, 
            {"Geekvape Aegis", "Device", 8},
            {"Smok Nord 4", "Device", 12},
            {"Vaporesso Xros", "Device", 6},
            {"Uwell Caliburn", "Device", 15},
            {"Vandy Vape Pulse", "Device", 9},
            {"Lost Vape Orion", "Device", 7},
            {"Aspire Nautilus", "Device", 11},
            {"Innokin Zenith", "Device", 5},
            {"Sigelei 150W", "Device", 4},
            {"Wismec Reuleaux", "Device", 6},
            {"Eleaf iStick", "Device", 10},
            {"Joyetech eVic", "Device", 8},
            {"Voopoo Vinci", "Device", 12},
            {"Geekvape Zeus", "Device", 9},
            {"Smok RPM80", "Device", 7},
            {"Vaporesso Luxe", "Device", 5},
            {"Uwell Crown", "Device", 11},
            {"Vandy Vape Jackaroo", "Device", 6},
            {"Lost Vape Thelema", "Device", 8},
            {"Aspire PockeX", "Device", 14},
            {"Innokin Endura", "Device", 7},
            {"Sigelei Fuchai", "Device", 5},
            {"Wismec Predator", "Device", 6},
            {"Eleaf Pico", "Device", 10},
            {"Joyetech Cuboid", "Device", 8},
            {"Voopoo Argus", "Device", 12},
            {"Geekvape Legend", "Device", 9},
            {"Smok Alien", "Device", 7},
            {"Vaporesso Target", "Device", 5},
            {"Uwell Valyrian", "Device", 11},
            {"Vandy Vape Pulse V2", "Device", 6},
            {"Lost Vape Centaurus", "Device", 8},
            {"Aspire Cleito", "Device", 14},
            {"Innokin Kroma", "Device", 7},
            {"Sigelei 213", "Device", 5},
            {"Wismec Gen", "Device", 6},
            {"Eleaf Invoke", "Device", 10},
            {"Joyetech Exceed", "Device", 8},
            {"Voopoo Drag 2", "Device", 12},
            {"Geekvape Nova", "Device", 9},
            {"Smok G-Priv", "Device", 7},
            {"Vaporesso Revenger", "Device", 5},
            {"TRML T200", "Device", 11},
            {"R234 Pro", "Device",15},
            {"Mango Tango 3mg", "Liquid", 18},
            {"Strawberry Milk 6mg", "Liquid", 15},
            {"Blueberry Ice 3mg", "Liquid", 20},
            {"Vanilla Custard 6mg", "Liquid", 12},
            {"Watermelon Chill 3mg", "Liquid", 22},
            {"Caramel Latte 6mg", "Liquid", 14},
            {"Peach Rings 3mg", "Liquid", 19},
            {"Mint Chocolate 6mg", "Liquid", 11},
            {"Durian Express 3mg", "Liquid", 17},
            {"Banana Pudding 6mg", "Liquid", 13},
            {"Lemon Tart 3mg", "Liquid", 21},
            {"Coffee Cake 6mg", "Liquid", 10},
            {"Berry Blast 3mg", "Liquid", 23},
            {"Cinnamon Roll 6mg", "Liquid", 9},
            {"Apple Pie 3mg", "Liquid", 16},
            {"Honeydew Melon 6mg", "Liquid", 14},
            {"Grape Soda 3mg", "Liquid", 18},
            {"Peanut Butter 6mg", "Liquid", 12},
            {"Orange Cream 3mg", "Liquid", 20},
            {"Coconut Macaroon 6mg", "Liquid", 11},
            {"Raspberry Donut 3mg", "Liquid", 19},
            {"Butterscotch 6mg", "Liquid", 13},
            {"Pomegranate 3mg", "Liquid", 17},
            {"Almond Joy 6mg", "Liquid", 15},
            {"Kiwi Strawberry 3mg", "Liquid", 21},
            {"Chocolate Mint 6mg", "Liquid", 10},
            {"Guava Nectar 3mg", "Liquid", 22},
            {"Cinnamon Toast 6mg", "Liquid", 8},
            {"Lychee Ice 3mg", "Liquid", 24},
            {"Tiramisu 6mg", "Liquid", 9},
            {"Makna V2 3mg", "Liquid", 15}, 
            {"Bolu Bakar V1 6mg", "Liquid", 12}, 
            {"The Orama V1 3mg", "Liquid", 20},
        },
        {},
        80, 
        0
    };


    while (true) {
        tampilkanMenuLogin();
        int menuLogin;
        cout << "Pilihan: ";
        
        string input;
        getline(cin, input);
        if (input.find_first_not_of(' ') == string::npos) {
            printWithColor("Input tidak boleh hanya spasi!\n", "red");
            continue;
        }
        if (input.empty()) {
            printWithColor("Input tidak boleh kosong!\n", "red");
            continue;
        }
        
        try {
            menuLogin = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (menuLogin < 1 || menuLogin > 3) {
            printWithColor("Input tidak valid! Masukkan angka 1-3: ", "red");
            continue;
        }

        switch (menuLogin) {
            case 1: {
                bool loginBerhasil = false;
                bool isAdmin = false;
                prosesLogin(&store, &loginBerhasil, &isAdmin);
                
                if (loginBerhasil) {
                    if (isAdmin) {
                        while (true) {
                            tampilkanMenuAdmin();
                            int pilihan;
                            cout << "Pilihan: ";
                            
                            getline(cin, input);
                            
                            if (input.empty()) {
                                printWithColor("Input tidak boleh kosong!\n", "red");
                                continue;
                            }
                            
                            try {
                                pilihan = stoi(input);
                            } catch (...) {
                                printWithColor("Input harus angka!\n", "red");
                                continue;
                            }
                            
                            if (pilihan < 1 || pilihan > 6) {
                                printWithColor("Input tidak valid! Masukkan angka 1-6: ", "red");
                                continue;
                            }

                            switch (pilihan) {
                                case 1: tampilkanBarang(&store); break;
                                case 2: tambahBarang(&store); break;
                                case 3: ubahBarangDenganPointer(store.barang, store.jumlahBarang); break;
                                case 4: hapusBarang(&store); break;
                                case 5: tampilkanInfoTotalBarang(&store); break;
                                case 6: 
                                    printWithColor("Logout berhasil.\n", "green");
                                    goto logout;
                            }
                        }
                    } else {
                        while (true) {
                            tampilkanMenuUser();
                            int pilihan;
                            cout << "Pilihan: ";
                            
                            getline(cin, input);
                            
                            if (input.empty()) {
                                printWithColor("Input tidak boleh kosong!\n", "red");
                                continue;
                            }
                            
                            try {
                                pilihan = stoi(input);
                            } catch (...) {
                                printWithColor("Input harus angka!\n", "red");
                                continue;
                            }
                            
                            if (pilihan < 1 || pilihan > 4) {
                                printWithColor("Input tidak valid! Masukkan angka 1-4: ", "red");
                                continue;
                            }

                            switch (pilihan) {
                                case 1: tampilkanBarang(&store); break;
                                case 2: menuSortingUser(&store); break;
                                case 3: menuSearchUser(&store); break;
                                case 4: 
                                    printWithColor("Logout berhasil.\n", "green");
                                    goto logout;
                            }
                        }
                    }
                    logout:;
                }
                break;
            }
            case 2:
                prosesRegister(&store); 
                break;
            case 3:
                printWithColor("Anda berhasil keluar dari program ini!.\n", "blue");
                return 0;
        }
    }

    return 0;
}

void tampilkanMenuLogin() {
    tulisanIndah();
    printWithColor("\n=== Menu Login ===\n", "cyan");
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Keluar\n";
}

void tulisanIndah() {
    printWithColor( R"(
  _____             _                     _      _             _     _ 
 |  __ \           (_)            ___    | |    (_)           (_)   | |
 | |  | | _____   ___  ___ ___   ( _ )   | |     _  __ _ _   _ _  __| |
 | |  | |/ _ \ \ / / |/ __/ _ \  / _ \/\ | |    | |/ _` | | | | |/ _` |
 | |__| |  __/\ V /| | (_|  __/ | (_>  < | |____| | (_| | |_| | | (_| |
 |_____/ \___| \_/ |_|\___\___|  \___/\/ |______|_|\__, |\__,_|_|\__,_|
                                                      | |              
                                                      |_|              
    )", "yellow");
}
void prosesLogin(VapeStore* store, bool* loginBerhasil, bool* isAdmin) {
    string username, password;
    int attempts = 0;
    *loginBerhasil = false;
    *isAdmin = false;

    while (attempts < 3 && !(*loginBerhasil)) {
        username = getInputWithValidation("Username: ", MAX_USERNAME_PASSWORD);
        password = masukkanPassword();

        if (username == "google" && password == "kelompok4") {
            *loginBerhasil = true;
            *isAdmin = true;
            printWithColor("Login sebagai admin berhasil!\n", "green");
            return;
        }

        bool userFound = false;
        for (int i = 0; i < store->jumlahUser; i++) {
            if (store->users[i].username == username) {
                userFound = true;
                if (store->users[i].password == password) {
                    *loginBerhasil = true;
                    printWithColor("Login berhasil!\n", "green");
                    return;
                } else {
                    printWithColor("Password salah!\n", "red");
                    return;
                }
            }
        }
        if (!userFound) {
            printWithColor("Username tidak ditemukan!\n", "red");
            return;
        }

        printWithColor("Login gagal! Coba lagi.\n", "red");
        attempts++;
    }

    if (attempts == 3) {
        printWithColor("Kesempatan login anda habis.\n", "red");
    }
}

void prosesRegister(VapeStore* store) {
    if (store->jumlahUser >= MAX_USER) {
        printWithColor("Kapasitas user penuh!\n", "red");
        return;
    }

    string username = getInputWithValidation("Username :", MAX_USERNAME_PASSWORD);
    
    for (int i = 0; i < store->jumlahUser; i++) {
        if (store->users[i].username == username) {
            printWithColor("Username sudah digunakan!\n", "red");
            return;
        }
    }
    
    store->users[store->jumlahUser].username = username;
    store->users[store->jumlahUser].password = masukkanPassword();
    store->jumlahUser++;
    printWithColor("Registrasi berhasil!\n", "green");
}

void tampilkanMenuUser() {
    printWithColor("\n=== Menu User ===\n", "yellow");
    cout << "1. Tampilkan Barang\n";
    cout << "2. Sorting Barang\n";
    cout << "3. Cari Barang\n";
    cout << "4. Logout\n";
}

void tampilkanMenuAdmin() {
    printWithColor("\n=== Menu Admin ===\n", "yellow");
    cout << "1. Tampilkan Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Ubah Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Info Total Barang\n";
    cout << "6. Logout\n";
}

void tampilkanBarang(VapeStore* store) {
    if (store->jumlahBarang == 0) {
        printWithColor("Belum ada barang dalam daftar.\n", "red");
        return;
    }

    tampilkanHeaderTabel();
    for (int i = 0; i < store->jumlahBarang; i++) {
        tampilkanBarisBarang(&(store->barang[i]), i + 1); 
    }
    tampilkanFooterTabel();
}

void tambahBarang(VapeStore* store) {
    if (store->jumlahBarang >= MAX_BARANG) {
        printWithColor("Kapasitas penyimpanan penuh!\n", "red");
        return;
    }

    string namaBarang = getInputWithValidation("Nama barang (maksimal " + to_string(MAX_NAMA_BARANG) + " karakter): ", MAX_NAMA_BARANG);
    
    store->barang[store->jumlahBarang].nama = namaBarang;

    cout << "Pilih jenis:\n";
    cout << "1. Device\n";
    cout << "2. Liquid\n";
    
    string input;
    int jenisPilihan;
    while (true) {
        input = getInputWithValidation("Masukkan pilihan (1-2): ");
        
        try {
            jenisPilihan = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (jenisPilihan < 1 || jenisPilihan > 2) {
            printWithColor("Pilihan harus 1 atau 2!\n", "red");
            continue;
        }
        break;
    }
    
    store->barang[store->jumlahBarang].jenis = (jenisPilihan == 1) ? "Device" : "Liquid";

    int jumlah;
    while (true) {
        input = getInputWithValidation("Jumlah: ");
        
        try {
            jumlah = stoi(input);
        } catch (...) {
            printWithColor("Jumlah harus angka!\n", "red");
            continue;
        }
        
        if (jumlah < 0) {
            printWithColor("Jumlah tidak boleh negatif!\n", "red");
            continue;
        }
        break;
    }
    
    store->barang[store->jumlahBarang].jumlah = jumlah;
    store->jumlahBarang++;

    printWithColor("Barang berhasil ditambahkan!\n", "green");
    tampilkanBarang(store);
}

void ubahBarangDenganPointer(Barang* barang, int jumlahBarang) {
    if (jumlahBarang == 0) {
        printWithColor("Tidak ada barang untuk diubah.\n", "red");
        return;
    }

    tampilkanHeaderTabel();
    for (int i = 0; i < jumlahBarang; i++) {
        tampilkanBarisBarang(&barang[i], i + 1);
    }
    tampilkanFooterTabel();

    int index;
    string input;
    while (true) {
        input = getInputWithValidation("Pilih nomor barang yang ingin diubah: ");
        
        try {
            index = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (index < 1 || index > jumlahBarang) {
            printWithColor("Nomor tidak valid! Masukkan angka antara 1-" + to_string(jumlahBarang) + ": ", "red");
            continue;
        }
        break;
    }

    Barang* barangToEdit = &barang[index - 1]; 
    
    string namaBaru = getInputWithValidation("Nama baru (maksimal " + to_string(MAX_NAMA_BARANG) + " karakter): ", MAX_NAMA_BARANG);
    barangToEdit->nama = namaBaru;

    cout << "Pilih jenis:\n";
    cout << "1. Device\n";
    cout << "2. Liquid\n";
    
    int jenisPilihan;
    while (true) {
        input = getInputWithValidation("Masukkan pilihan (1-2): ");
        
        try {
            jenisPilihan = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (jenisPilihan < 1 || jenisPilihan > 2) {
            printWithColor("Pilihan harus 1 atau 2!\n", "red");
            continue;
        }
        break;
    }
    
    barangToEdit->jenis = (jenisPilihan == 1) ? "Device" : "Liquid";

    int jumlahBaru;
    while (true) {
        input = getInputWithValidation("Jumlah baru: ");
        
        try {
            jumlahBaru = stoi(input);
        } catch (...) {
            printWithColor("Jumlah harus angka!\n", "red");
            continue;
        }
        
        if (jumlahBaru < 0) {
            printWithColor("Jumlah tidak boleh negatif!\n", "red");
            continue;
        }
        break;
    }
    
    barangToEdit->jumlah = jumlahBaru;
    
    printWithColor("Barang berhasil diubah!\n", "green");
    VapeStore* store = nullptr;
    tampilkanHeaderTabel();
    for (int i = 0; i < jumlahBarang; i++) {
        tampilkanBarisBarang(&barang[i], i + 1);
    }
    tampilkanFooterTabel();
}

void hapusBarang(VapeStore* store) {
    if (store->jumlahBarang == 0) {
        printWithColor("Tidak ada barang untuk dihapus.\n", "red");
        return;
    }
    tampilkanBarang(store);
    int index;
    string input;
    while (true) {
        input = getInputWithValidation("Pilih nomor barang yang akan dihapus: ");
        
        try {
            index = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (index < 1 || index > store->jumlahBarang) {
            printWithColor("Nomor tidak valid! Masukkan angka antara 1-" + to_string(store->jumlahBarang) + ": ", "red");
            continue;
        }
        break;
    }
    for (int i = index - 1; i < store->jumlahBarang - 1; i++) {
        store->barang[i] = store->barang[i + 1];
    }
    store->jumlahBarang--;
    printWithColor("Barang berhasil dihapus!\n", "green");
    tampilkanBarang(store);
}

void tampilkanHeaderTabel() {
    printWithColor("+-----+----------------------+------------+--------+\n","blue");
    printWithColor("| No  | Nama Barang          | Jenis      | Jumlah |\n", "blue");
    printWithColor("+-----+----------------------+------------+--------+\n", "blue");
}

void tampilkanBarisBarang(Barang* barang, int index) {
    cout << "| " << setw(3) << index << " | " << setw(20) << barang->nama << " | " 
         << setw(10) << barang->jenis << " | " 
         << setw(6) << barang->jumlah << " |\n";
}

void tampilkanFooterTabel() {
    printWithColor("+-----+----------------------+------------+--------+\n", "blue");
}

int hitungTotalBarang(VapeStore* store) {
    int total = 0;
    for (int i = 0; i < store->jumlahBarang; i++) {
        total += store->barang[i].jumlah;
    }
    return total;
}

int hitungTotalBarangByJenis(VapeStore* store, string* jenis) {
    int total = 0;
    for (int i = 0; i < store->jumlahBarang; i++) {
        if (store->barang[i].jenis == *jenis) {
            total += store->barang[i].jumlah;
        }
    }
    return total;
}

void tampilkanInfoTotalBarang(VapeStore* store) {
    printWithColor("\n=== Informasi Total Barang ===\n", "cyan");
    cout << "Total semua barang: " << hitungTotalBarang(store) << endl;
    
    string jenis1 = "Device";
    string jenis2 = "Liquid";
    cout << "Total Device: " << hitungTotalBarangByJenis(store, &jenis1) << endl;
    cout << "Total Liquid: " << hitungTotalBarangByJenis(store, &jenis2) << endl;
}

void bubbleSortAscendingHuruf(Barang arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].nama > arr[j+1].nama) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void selectionSortDescendingAngka(Barang arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int max_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j].jumlah > arr[max_idx].jumlah) {
                max_idx = j;
            }
        }
        swap(arr[max_idx], arr[i]);
    }
}

int partition(Barang arr[], int low, int high) {
    string pivot = arr[high].nama;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].nama < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortAscendingHuruf(Barang arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortAscendingHuruf(arr, low, pi - 1);
        quickSortAscendingHuruf(arr, pi + 1, high);
    }
}

void menuSortingUser(VapeStore* store) {
    if (store->jumlahBarang == 0) {
        printWithColor("Tidak ada barang untuk diurutkan.\n", "red");
        return;
    }

    printWithColor("\n=== Menu Sorting User ===\n", "yellow");
    cout << "1. Sorting Sesuai Abjad (A-Z)\n";
    cout << "2. Sorting dari jumlah terbesar - terkecil\n";
    cout << "3. Kembali\n";
    
    string input;
    int pilihan;
    while (true) {
        input = getInputWithValidation("Pilihan: ");
        
        try {
            pilihan = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (pilihan < 1 || pilihan > 3) {
            printWithColor("Input tidak valid! Masukkan angka 1-3: ", "red");
            continue;
        }
        break;
    }

    Barang temp[MAX_BARANG];
    for (int i = 0; i < store->jumlahBarang; i++) {
        temp[i] = store->barang[i];
    }

    switch (pilihan) {
        case 1:
            bubbleSortAscendingHuruf(temp, store->jumlahBarang);
            cout << "\nHasil Sorting sesuai abjad:\n";
            break;
        case 2:
            selectionSortDescendingAngka(temp, store->jumlahBarang);
            cout << "\nHasil Sorting dari jumlah angka terbesar ke terkecil:\n";
            break;
        case 3:
            return;
    }

    tampilkanHeaderTabel();
    for (int i = 0; i < store->jumlahBarang; i++) {
        tampilkanBarisBarang(&temp[i], i + 1);
    }
    tampilkanFooterTabel();
}

void menuSearchUser(VapeStore* store){
    if (store->jumlahBarang == 0){
        printWithColor("Tidak ada barang yang dicari.\n", "red");
        return;
    }

    string prefix = getInputWithValidation(
        "Silahkan masukkan nama barang yang ingin dicari: ", MAX_NAMA_BARANG);
    bool ditemukan = false;

    for (int i = 0; i < store->jumlahBarang; i++) {
        string namaBarang = store->barang[i].nama;
        if (namaBarang.length() >= prefix.length() &&
            equal(prefix.begin(), prefix.end(), namaBarang.begin(),
                [](char a, char b) {
                    return tolower(a) == tolower(b);
                })) {
            if (!ditemukan) tampilkanHeaderTabel();
            tampilkanBarisBarang(&store->barang[i], i + 1);
            ditemukan = true;
        }
    }
    if (ditemukan) {
        tampilkanFooterTabel();
    } else {
        printWithColor("Barang tidak ditemukan.\n", "red");
    }
}

void menuSortingAdmin(VapeStore* store) {
    if (store->jumlahBarang == 0) {
        printWithColor("Tidak ada barang untuk diurutkan.\n", "red");
        return;
    }

    printWithColor("\n=== Menu Sorting Admin ===\n", "cyan");
    cout << "1. Sorting Sesuai Abjad (A-Z):\n";
    cout << "2. Kembali\n";
    
    string input;
    int pilihan;
    while (true) {
        input = getInputWithValidation("Pilihan: ");
        
        try {
            pilihan = stoi(input);
        } catch (...) {
            printWithColor("Input harus angka!\n", "red");
            continue;
        }
        
        if (pilihan < 1 || pilihan > 2) {
            printWithColor("Input tidak valid! Masukkan angka 1-2: ", "red");
            continue;
        }
        break;
    }

    Barang temp[MAX_BARANG];
    for (int i = 0; i < store->jumlahBarang; i++) {
        temp[i] = store->barang[i];
    }

    switch (pilihan) {
        case 1:
            quickSortAscendingHuruf(temp, 0, store->jumlahBarang - 1);
            cout << "\nSorting Sesuai Abjad (A-Z):\n";
            break;
        case 2:
            return;
    }

    tampilkanHeaderTabel();
    for (int i = 0; i < store->jumlahBarang; i++) {
        tampilkanBarisBarang(&temp[i], i + 1);
    }
    tampilkanFooterTabel();
}