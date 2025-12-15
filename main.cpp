#include <iostream>
#include "laundry.h" // Wajib include header buatan sendiri

using namespace std;

int main() {
    adrNode root = NULL;
    int pilihan, id, berat;
    string nama;

    do {
        cout << "\n=== LAUNDRY FRESHNODE SYSTEM (BST) ===" << endl;
        cout << "1. Tambah Pesanan Baru" << endl;
        cout << "2. Lihat Daftar Antrian" << endl;
        cout << "3. Tracking Status Cucian" << endl;
        cout << "4. Update Status Cucian" << endl;
        cout << "5. Ambil Cucian (Checkout)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "Masukkan ID Pesanan (Angka Unik): ";
            cin >> id;
            cout << "Masukkan Nama Pelanggan: ";
            cin.ignore(); 
            getline(cin, nama);
            cout << "Masukkan Berat (kg): ";
            cin >> berat;
            root = insertNode(root, createNode(id, nama, berat));
            break;

        case 2:
            cout << "\n--- Daftar Antrian Laundry ---" << endl;
            if (root == NULL) {
                cout << "(Antrian Kosong)" << endl;
            } else {
                printAntrian(root);
            }
            break;

        case 3:
            cout << "Masukkan ID untuk Tracking: ";
            cin >> id;
            {
                adrNode hasil = searchNode(root, id);
                if (hasil != NULL) {
                    cout << "\n[DITEMUKAN]" << endl;
                    cout << "Nama: " << hasil->data.namaPelanggan << endl;
                    cout << "Status: " << hasil->data.status << endl;
                } else {
                    cout << "\n[TIDAK DITEMUKAN]" << endl;
                }
            }
            break;

        case 4:
            cout << "Masukkan ID yang akan diupdate: ";
            cin >> id;
            if (searchNode(root, id) != NULL) {
                cout << "Pilih Status (1. Dicuci, 2. Disetrika, 3. Selesai): ";
                int s;
                cin >> s;
                string statBaru;
                if (s == 1) statBaru = "Sedang Dicuci";
                else if (s == 2) statBaru = "Sedang Disetrika";
                else statBaru = "Siap Diambil";
                
                updateStatus(root, id, statBaru);
            } else {
                cout << "Data tidak ditemukan." << endl;
            }
            break;

        case 5:
            cout << "Masukkan ID Pesanan yang diambil: ";
            cin >> id;
            if (searchNode(root, id) != NULL) {
                root = deleteNode(root, id);
                cout << "Pesanan ID " << id << " berhasil diambil (dihapus)." << endl;
            } else {
                cout << "Data tidak ditemukan." << endl;
            }
            break;
        }
    } while (pilihan != 0);

    return 0;
}