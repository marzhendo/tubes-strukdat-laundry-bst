#include "laundry.h"
#include <cstdio>

string getRealTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, 20, "%d/%m %H:%M", ltm);
    return string(buffer);
}

int getCurrentYear() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

string formatRupiah(double angka) {
    return "Rp " + to_string((int)angka);
}

string getStatusLabel(int status) {
    if (status == STS_ANTRI) return "ANTRI";
    if (status == STS_PROSES) return "PROSES";
    if (status == STS_SELESAI) return "SELESAI";
    return "UNKNOWN";
}

bool isEmpty(address root) {
    return root == NULL;
}

address createNode(infotype data) {
    address P = new Node;
    P->info = data;
    P->left = NULL;
    P->right = NULL;
    return P;
}

void insertNode(address &root, infotype data) {
    if (isEmpty(root)) {
        root = createNode(data);
    } else {
        bool kiri = false;
        // Prioritas: Tipe -> Berat -> ID
        if (data.tipe < root->info.tipe) kiri = true;
        else if (data.tipe == root->info.tipe) {
            if (data.berat < root->info.berat) kiri = true;
            else if (data.berat == root->info.berat && data.id < root->info.id)
                kiri = true;
        }
        
        if (kiri) insertNode(root->left, data);
        else insertNode(root->right, data);
    }
}

// Mencari node dengan prioritas tertinggi yang masih ANTRI
void findNextQueue(address root, address &found) {
    if (root != NULL && found == NULL) {
        findNextQueue(root->left, found);
        if (found == NULL && root->info.status == STS_ANTRI) {
            found = root;
            return;
        }
        if (found == NULL) findNextQueue(root->right, found);
    }
}

void processNextJob(address root, bool &berhasil) {
    address candidate = NULL;
    findNextQueue(root, candidate);
    
    if (candidate != NULL) {
        candidate->info.status = STS_PROSES; // Ubah status jadi Proses
        cout << "\n>> Cucian Milik [" << candidate->info.nama << "] sekarang DIPROSES." << endl;
        berhasil = true;
    } else {
        berhasil = false;
    }
}

void printInOrder(address root) {
    if (!isEmpty(root)) {
        printInOrder(root->left);
        string labelTipe = (root->info.tipe == 1) ? "EXP" : "REG";
        cout << "| " << setw(4) << root->info.id
             << "| " << setw(11) << root->info.waktuMasuk
             << "| " << setw(12) << root->info.nama
             << "| " << setw(4) << labelTipe
             << "| " << setw(5) << root->info.berat
             << "| " << setw(10) << formatRupiah(root->info.totalBayar)
             << "| " << setw(8) << getStatusLabel(root->info.status)
             << " |" << endl;
        printInOrder(root->right);
    }
}

address findMin(address root) {
    while (root->left != NULL) root = root->left;
    return root;
}

bool deleteNodeByID(address &root, int id) {
    if (root == NULL) return false;


    if (root->info.id == id) {
        // Node ditemukan, lakukan penghapusan
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            address temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            address temp = root;
            root = root->left;
            delete temp;
        } else {
            // 2 children
            address temp = findMin(root->right);
            root->info = temp->info; // Copy data dari suksesor
            // Hapus suksesor (yang ID-nya sudah dipindah ke root)
            deleteNodeByID(root->right, temp->info.id); 
        }
        return true;
    }
    
    // Cari di kiri atau kanan
    if (deleteNodeByID(root->left, id)) return true;
    return deleteNodeByID(root->right, id);
}

void updateData(address &root, int id) {
    address node = searchByID(root, id);
    
    if (node == NULL) {
        cout << ">> Gagal: ID tidak ditemukan." << endl;
        return;
    }

    if (node->info.status != STS_ANTRI) {
        cout << ">> Gagal: Hanya data status 'ANTRI' yang bisa diupdate/hapus." << endl;
        cout << "   Status saat ini: " << getStatusLabel(node->info.status) << endl;
        return;
    }

    int subPilih;
    cout << "\n   [UPDATE MENU - ID " << id << "]" << endl;
    cout << "   1. Ubah Nama" << endl;
    cout << "   2. Ubah Berat (Hitung Ulang Harga)" << endl;
    cout << "   3. Hapus Data (Cancel Order)" << endl;
    cout << "   0. Batal" << endl;
    cout << "   Pilih: ";
    cin >> subPilih;

    if (subPilih == 1) {
        cout << "   Masukkan Nama Baru: ";
        cin.ignore();
        getline(cin, node->info.nama);
        cout << ">> Sukses update nama." << endl;
    } else if (subPilih == 2) {
        float beratBaru;
        cout << "   Masukkan Berat Baru (Kg): ";
        cin >> beratBaru;
        if (beratBaru < 1) {
            cout << ">> Gagal: Berat minimal 1 kg." << endl; 
            return;
        }

        int oldID = node->info.id;
        string oldNama = node->info.nama;
        int oldTipe = node->info.tipe;
        
        deleteNodeByID(root, oldID);

        infotype newData = newLaundryData(oldID, oldNama, oldTipe, beratBaru);
        
        insertNode(root, newData);
        
        cout << ">> Sukses update berat & harga." << endl;
        cout << "   Total Baru: " << formatRupiah(newData.totalBayar) << endl;

    } else if (subPilih == 3) {
        char yakin;
        cout << "   Yakin hapus ID " << id << "? (y/n): ";
        cin >> yakin;
        if (yakin == 'y' || yakin == 'Y') {
            if (deleteNodeByID(root, id)) {
                cout << ">> Sukses menghapus data." << endl;
            } else {
                cout << ">> Gagal menghapus." << endl;
            }
        }
    }
}

void markAsFinished(address root, int id, bool &berhasil) {
    address node = searchByID(root, id);
    if (node != NULL && node->info.status == STS_PROSES) {
        node->info.status = STS_SELESAI;
        berhasil = true;
    } else {
        berhasil = false;
    }
}

address searchByID(address root, int cariID) {
    if (isEmpty(root)) return NULL;
    if (root->info.id == cariID) return root;
    address kiri = searchByID(root->left, cariID);
    if (kiri != NULL) return kiri;
    return searchByID(root->right, cariID);
}

void searchByWeight(address root, float cariBerat, bool &found) {
    if (!isEmpty(root)) {
        if (root->info.berat == cariBerat) {
            cout << "- " << root->info.nama
                 << " | " << formatRupiah(root->info.totalBayar) 
                 << " | " << getStatusLabel(root->info.status) << endl;
            found = true;
        }
        searchByWeight(root->left, cariBerat, found);
        searchByWeight(root->right, cariBerat, found);
    }
}

string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

void searchByName(address root, string cariNama, bool &found) {
    if (!isEmpty(root)) {
        if (toLower(root->info.nama).find(toLower(cariNama)) != string::npos) { // Partial search
            cout << "- " << root->info.nama
                 << " | " << getStatusLabel(root->info.status)
                 << " | " << formatRupiah(root->info.totalBayar) << endl;
            found = true;
        }
        searchByName(root->left, cariNama, found);
        searchByName(root->right, cariNama, found);
    }
}

infotype newLaundryData(int id, string nama, int tipe, float berat) {
    infotype data;
    data.id = id;
    data.nama = nama;
    data.tipe = (tipe < 1 || tipe > 2) ? 2 : tipe;
    data.status = STS_ANTRI; // Default status

    if (berat < 1) berat = 1;

    data.berat = berat;
    data.waktuMasuk = getRealTime();
    data.tahun = getCurrentYear();

    double harga = (data.tipe == 1) ? HARGA_EXPRESS : HARGA_REGULER;
    double total = harga * berat;
    if (berat > MIN_BERAT_DISKON)
        total -= total * PERSEN_DISKON;

    data.totalBayar = total;
    return data;
}