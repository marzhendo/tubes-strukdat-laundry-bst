#ifndef LAUNDRY_H
#define LAUNDRY_H

#include <iostream>
#include <string>

using namespace std;

// Definisi Struktur Data
struct LaundryData {
    int idPesanan;
    string namaPelanggan;
    int berat;
    string status;
};

struct Node {
    LaundryData data;
    Node* left;
    Node* right;
};

typedef Node* adrNode;

// Prototype Fungsi (Daftar Isi)

// Creator
adrNode createNode(int id, string nama, int berat);

// Operasi BST Utama
adrNode insertNode(adrNode root, adrNode newNode);
adrNode searchNode(adrNode root, int idDicari);
adrNode deleteNode(adrNode root, int idHapus);

// Helper / Bantuan
adrNode findMin(adrNode node);
void printAntrian(adrNode root);
void updateStatus(adrNode root, int id, string statusBaru);

#endif