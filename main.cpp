#include "laundry.h"

int main() {
    address root = NULL;
    int pilihan;
    int autoID = 0;

    string inNama;
    int inTipe;
    float inBerat;

    do {
        cout << "\n=======================================================" << endl;
        cout << "                      Fresh Node                       " << endl;
        cout << "=======================================================" << endl;
        cout << "1. Tambah Cucian (Auto Hitung Harga)" << endl;
        cout << "2. Lihat Antrian & Pendapatan" << endl;
        cout << "3. Proses Cucian (Next Job)" << endl;
        cout << "4. Cari Data (ID / Berat / Nama)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "\n[INPUT DATA]" << endl;
                cout << "Nama Pelanggan : ";
                cin.ignore();
                getline(cin, inNama);
                cout << "Tipe (1=Express, 2=Reguler) : ";
                cin >> inTipe;
                do {
                    cout << "Berat (Kg) : ";
                    cin >> inBerat;

                    if (inBerat < 1) {
                        cout << ">> Gagal: Berat minimal 1 Kg.\n";
                    }
                } while (inBerat < 1);

                autoID++;
                infotype newData = newLaundryData(autoID, inNama, inTipe, inBerat);

                insertNode(root, newData);

                cout << ">> Sukses! Total Tagihan: " << formatRupiah(newData.totalBayar);
                if (inBerat > MIN_BERAT_DISKON)
                cout << " (Termasuk Diskon 10%)";
                cout << endl;
                break;
            }
            case 2: {
                cout << "\n[DAFTAR ANTRIAN & HARGA]" << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "| No | Jam Masuk | Nama Pelanggan | Tipe | Berat (Kg) | Tahun  | Tagihan |" << endl;
                cout << "-------------------------------------------------------------" << endl;
                if (isEmpty(root)) {
                    cout << "|                      ANTRIAN KOSONG                       |" << endl;
                } else {
                    printInOrder(root);
                }
                cout << "-------------------------------------------------------------" << endl;
                break;
            }
            case 3: {
                infotype diproses;
                bool status;
                processOrder(root, diproses, status);
                if (status) {
                    cout << "\n>> CUCIAN SELESAI DIPROSES:" << endl;
                    cout << "   Pelanggan : " << diproses.nama << endl;
                    cout << "   Total Bayar : " << formatRupiah(diproses.totalBayar) << endl;
                    cout << "   Status    : Dihapus dari antrian." << endl;
                } else {
                    cout << ">> Gagal: Antrian kosong." << endl;
                }
                break;
            }
            case 4: {
                int subPilih;
                cout << "\n[PENCARIAN DATA]" << endl;
                cout << "1. Cari berdasarkan ID Transaksi" << endl;
                cout << "2. Cari berdasarkan Berat Cucian" << endl;
                cout << "3. Cari berdasarkan Nama Pelanggan" << endl;
                cout << "Pilih: ";
                cin >> subPilih;

                if (subPilih == 1) {
                    int cariID;
                    cout << "Masukkan ID: ";
                    cin >> cariID;
                    address hasil = searchByID(root, cariID);

                    if (hasil != NULL) {
                        cout << ">> DITEMUKAN: " << hasil->info.nama
                             << " | Berat: " << hasil->info.berat << "kg"
                             << " | Tagihan: " << formatRupiah(hasil->info.totalBayar) << endl;
                    } else {
                        cout << ">> Data dengan ID " << cariID << " tidak ditemukan." << endl;
                    }
                } else if (subPilih == 2) {
                    float cariBerat;
                    bool ketemu = false;
                    cout << "Masukkan Berat (Kg): ";
                    cin >> cariBerat;
                    cout << ">> Hasil Pencarian Berat " << cariBerat << " kg:" << endl;
                    searchByWeight(root, cariBerat, ketemu);

                    if (!ketemu) cout << "(Tidak ada data dengan berat tersebut)" << endl;
                } else if (subPilih == 3) {
                    string cariNama;
                    bool ketemu = false;

                    cout << "Masukkan Nama Pelanggan: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, cariNama);

                    cout << ">> Hasil Pencarian Nama \"" << cariNama << "\":" << endl;
                    searchByName(root, cariNama, ketemu);

                    if (!ketemu)
                    cout << "(Tidak ada data dengan nama tersebut)" << endl;
                    }
                    break;

            }
        }
    } while (pilihan != 5);

    return 0;
}
