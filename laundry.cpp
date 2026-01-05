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
<<<<<<< HEAD
        bool kiri = false;
        if (data.tipe < root->info.tipe) kiri = true;
        else if (data.tipe == root->info.tipe) {
            if (data.berat < root->info.berat) kiri = true;
            else if (data.berat == root->info.berat && data.id < root->info.id)
                kiri = true;
=======
        cout << "Error: ID Pesanan " << newNode->data.idPesanan << " sudah ada!" << endl;
    }
    return root;
}

adrNode searchNode(adrNode root, int idDicari) {
    if (root == NULL || root->data.idPesanan == idDicari) {
        return root;
    }

    if (idDicari < root->data.idPesanan) {
        return searchNode(root->left, idDicari);
    }
    return searchNode(root->right, idDicari);
}

adrNode findMin(adrNode node) {
    adrNode current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

adrNode deleteNode(adrNode root, int idHapus) {
    if (root == NULL) return root;
    
    if (idHapus < root->data.idPesanan) {
        root->left = deleteNode(root->left, idHapus);
    } else if (idHapus > root->data.idPesanan) {
        root->right = deleteNode(root->right, idHapus);
    } else {
        // Node ditemukan
        if (root->left == NULL) {
            adrNode temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            adrNode temp = root->left;
            delete root;
            return temp;
>>>>>>> 0077793221dc214904c67ad19b3fcebc626d023b
        }
        if (kiri) insertNode(root->left, data);
        else insertNode(root->right, data);
    }
}

void processOrder(address &root, infotype &keluaran, bool &berhasil) {
    if (isEmpty(root)) berhasil = false;
    else if (root->left == NULL) {
        address temp = root;
        keluaran = temp->info;
        root = root->right;
        delete temp;
        berhasil = true;
    } else {
        processOrder(root->left, keluaran, berhasil);
    }
}

void printInOrder(address root) {
    if (!isEmpty(root)) {
        printInOrder(root->left);
        string label = (root->info.tipe == 1) ? "EXP" : "REG";
        cout << "| " << setw(4) << root->info.id
             << "| " << setw(12) << root->info.waktuMasuk
             << "| " << setw(15) << root->info.nama
             << "| " << setw(5) << label
             << "| " << setw(6) << root->info.berat
             << "| " << setw(6) << root->info.tahun
             << "| " << setw(12) << formatRupiah(root->info.totalBayar)
             << "| " << endl;
        printInOrder(root->right);
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
                 << " | " << formatRupiah(root->info.totalBayar) << endl;
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
        if (toLower(root->info.nama) == toLower(cariNama)) {
            cout << "- " << root->info.nama
                 << " | " << root->info.waktuMasuk
                 << " | " << formatRupiah(root->info.totalBayar) << endl;
            found = true;
        }
        searchByName(root->left, cariNama, found);
        searchByName(root->right, cariNama, found);
    }
}

void filterByYear(address root, int tahun, bool &found) {
    if (!isEmpty(root)) {
        if (root->info.tahun == tahun) {
            cout << "- " << root->info.nama
                 << " | " << formatRupiah(root->info.totalBayar) << endl;
            found = true;
        }
        filterByYear(root->left, tahun, found);
        filterByYear(root->right, tahun, found);
    }
}

double totalPendapatanByYear(address root, int tahun) {
    if (isEmpty(root)) return 0;
    double total = 0;
    if (root->info.tahun == tahun)
        total += root->info.totalBayar;
    total += totalPendapatanByYear(root->left, tahun);
    total += totalPendapatanByYear(root->right, tahun);
    return total;
}

infotype newLaundryData(int id, string nama, int tipe, float berat) {
    infotype data;
    data.id = id;
    data.nama = nama;
    data.tipe = (tipe < 1 || tipe > 2) ? 2 : tipe;

    if (berat < 1)
        berat = 1;

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
