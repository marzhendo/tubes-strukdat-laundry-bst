#include "laundry.h"

int main() {
    address root = NULL;
    int pilihan;
    int autoID = 0;

    string inNama;
    int inTipe;
    float inBerat;

    autoID++;
    insertNode(root, newLaundryData(autoID, "Aedil Tegal", 1, 6.0));
    autoID++;
    insertNode(root, newLaundryData(autoID, "Fatir Biawak", 2, 12.0));
    autoID++;
    insertNode(root, newLaundryData(autoID, "Maruf PSHT", 1, 5.0));
    do {
        cout << "\n====================================================================" << endl;
        cout << "                           Fresh Node Laundry                           " << endl;
        cout << "====================================================================" << endl;
        cout << "1. Tambah Cucian" << endl;
        cout << "2. Lihat Daftar Cucian & Status" << endl;
        cout << "3. Proses Cucian" << endl;
        cout << "4. Cari Data (ID / Berat / Nama)" << endl;
        cout << "5. Update Data" << endl;
        cout << "6. Selesaikan Cucian" << endl;
        cout << "7. Hapus Data" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
            cout << "\n[INPUT DATA BARU]" << endl;
            cout << "Nama Pelanggan : ";
            cin.ignore();
            getline(cin, inNama);

            while (true) {
                cout << "Tipe (1=Express, 2=Reguler) : ";
                if (!(cin >> inTipe)) {
                cout << ">> Input tidak valid. Masukkan angka.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
                }
                if (inTipe == 1 || inTipe == 2) break;
                cout << ">> Invalid! Pilihan hanya 1 atau 2.\n";
            }

            do {
                cout << "Berat (Kg) : ";
                cin >> inBerat;
                if (inBerat < 1) cout << ">> Berat minimal 1 Kg.\n";
            } while (inBerat < 1);

            autoID++;
            infotype newData = newLaundryData(autoID, inNama, inTipe, inBerat);
            insertNode(root, newData);

            cout << ">> Sukses! ID Transaksi: " << autoID << endl;
            cout << "   Total: " << formatRupiah(newData.totalBayar);
            if (inBerat > MIN_BERAT_DISKON) cout << " (Diskon 10%)";
            cout << endl;
            break;
            }
            case 2: {
                cout << "\n[MONITORING STATUS LAUNDRY]" << endl;
                cout << "--------------------------------------------------------------------------" << endl;
                cout << "| ID | Jam Masuk | Nama        | Tipe| Berat| Tagihan   | STATUS   |" << endl;
                cout << "--------------------------------------------------------------------------" << endl;
                if (isEmpty(root)) {
                    cout << "|                             DATA KOSONG                                |" << endl;
                } else {
                    printInOrder(root);
                }
                cout << "--------------------------------------------------------------------------" << endl;
                break;
            }
            case 3: {
                bool status;
                cout << "\n[PROSES NEXT JOB]" << endl;
                processNextJob(root, status);
                if (!status) {
                    cout << ">> Tidak ada antrian yang statusnya 'ANTRI'." << endl;
                }
                break;
            }
            case 4: {
                int subPilih;
                while (true) {
                    cout << "\n[PENCARIAN DATA]" << endl;
                    cout << "1. Cari ID\n2. Cari Berat\n3. Cari Nama\nPilih: ";
                    if (!(cin >> subPilih)) {
                        cout << ">> Input tidak valid. Masukkan angka 1-3.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    if (subPilih >= 1 && subPilih <= 3) break;
                    cout << ">> Pilihan hanya 1, 2, atau 3.\n";
                }

                if (subPilih == 1) {
                    int cariID;
                    cout << "Masukkan ID: ";
                    cin >> cariID;
                    address hasil = searchByID(root, cariID);
                    if (hasil != NULL) {
                        cout << ">> DITEMUKAN: " << hasil->info.nama
                             << " | Status: " << getStatusLabel(hasil->info.status)
                             << " | Tagihan: " << formatRupiah(hasil->info.totalBayar) << endl;
                    } else {
                        cout << ">> ID " << cariID << " tidak ditemukan." << endl;
                    }
                } else if (subPilih == 2) {
                    float cariBerat;
                    bool ketemu = false;
                    cout << "Masukkan Berat: ";
                    cin >> cariBerat;
                    cout << ">> Hasil Berat " << cariBerat << " kg:" << endl;
                    searchByWeight(root, cariBerat, ketemu);
                    if (!ketemu) cout << "(Tidak ada data)" << endl;
                } else if (subPilih == 3) {
                    string cariNama;
                    bool ketemu = false;
                    cout << "Masukkan Nama: ";
                    cin.ignore();
                    getline(cin, cariNama);
                    cout << ">> Hasil Nama \"" << cariNama << "\":" << endl;
                    searchByName(root, cariNama, ketemu);
                    if (!ketemu) cout << "(Tidak ada data)" << endl;
                }
                break;
            }
            case 5: {
                int idUpdate;
                cout << "\n[UPDATE DATA (KHUSUS ANTRI)]" << endl;
                cout << "Masukkan ID Transaksi yang ingin diupdate: ";
                cin >> idUpdate;
                updateData(root, idUpdate);
                break;
            }
            case 6: {
                int idSelesai;
                bool berhasil;
                cout << "\n[SELESAIKAN CUCIAN]" << endl;
                cout << "Masukkan ID yang sudah diproses: ";
                cin >> idSelesai;
                markAsFinished(root, idSelesai, berhasil);
                if (berhasil) cout << ">> Sukses! ID " << idSelesai << " statusnya sekarang SELESAI." << endl;
                else cout << ">> Gagal. ID tidak ditemukan atau status belum PROSES." << endl;
                break;
            }
            case 7: { 
                int idHapus;
                cout << "\n[HAPUS RIWAYAT SELESAI]" << endl;
                cout << "Masukkan ID yang akan dihapus: ";
                cin >> idHapus;

                address target = searchByID(root, idHapus);
                
                if (target == NULL) {
                    cout << ">> Gagal: ID " << idHapus << " tidak ditemukan." << endl;
                } 
                else if (target->info.status != STS_SELESAI) { 
                    cout << ">> Gagal: Hanya cucian status 'SELESAI' yang boleh dihapus." << endl;
                    cout << "   Status cucian ini: " << getStatusLabel(target->info.status) << endl;
                    cout << "   (Selesaikan cucian dulu jika ingin menghapus)" << endl;
                } else {
                    char yakin;
                    cout << ">> Data: " << target->info.nama << " (Tagihan Lunas)\n";
                    cout << ">> Hapus data ini dari riwayat? (y/n): ";
                    cin >> yakin;

                    if (yakin == 'y' || yakin == 'Y') {
                        if (deleteNodeByID(root, idHapus)) {
                            cout << ">> Sukses! Data riwayat berhasil dihapus." << endl;
                        } else {
                            cout << ">> Error sistem saat menghapus." << endl;
                        }
                    } else {
                        cout << ">> Batal." << endl;
                    }
                }
                break;
            }
            default:
                if (pilihan != 0)
                    cout << ">> Pilihan tidak valid. Pilih yang tersedia (0-7)." << endl;
                break;
        }
    } while (pilihan != 0);
    cout << ">> Terima kasih telah menggunakan Fresh Node." << endl;

    return 0;
}
