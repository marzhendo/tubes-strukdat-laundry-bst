#include "laundry.h"

adrNode createNode(int id, string nama, int berat) {
    adrNode newNode = new Node;
    newNode->data.idPesanan = id;
    newNode->data.namaPelanggan = nama;
    newNode->data.berat = berat;
    newNode->data.status = "Dalam Antrian"; 
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

adrNode insertNode(adrNode root, adrNode newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (newNode->data.idPesanan < root->data.idPesanan) {
        root->left = insertNode(root->left, newNode);
    } else if (newNode->data.idPesanan > root->data.idPesanan) {
        root->right = insertNode(root->right, newNode);
    } else {
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
        }

        adrNode temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.idPesanan);
    }
    return root;
}

void printAntrian(adrNode root) {
    if (root != NULL) {
        printAntrian(root->left);
        cout << "| ID: " << root->data.idPesanan 
             << " | Nama: " << root->data.namaPelanggan 
             << " | Berat: " << root->data.berat << "kg"
             << " | Status: " << root->data.status << " |" << endl;
        printAntrian(root->right);
    }
}

void updateStatus(adrNode root, int id, string statusBaru) {
    adrNode target = searchNode(root, id);
    if (target != NULL) {
        target->data.status = statusBaru;
        cout << "Status berhasil diubah menjadi: " << statusBaru << endl;
    } else {
        cout << "ID Pesanan tidak ditemukan!" << endl;
    }
}