#ifndef LAUNDRY_H
#define LAUNDRY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>


using namespace std;

// --- KONFIGURASI HARGA ---
const double HARGA_REGULER = 6000;
const double HARGA_EXPRESS = 10000;
const float MIN_BERAT_DISKON = 10.0;
const double PERSEN_DISKON = 0.10;

struct Laundry {
    int id;
    string nama;
    int tipe;
    float berat;
    int tahun;              
    string waktuMasuk;
    double totalBayar;
};

typedef Laundry infotype;
typedef struct Node *address;

struct Node {
    infotype info;
    address left;
    address right;
};

// --- BST ---
bool isEmpty(address root);
address createNode(infotype data);
void insertNode(address &root, infotype data);
void processOrder(address &root, infotype &keluaran, bool &berhasil);
void printInOrder(address root);

// --- SEARCH ---
address searchByID(address root, int cariID);
void searchByWeight(address root, float cariBerat, bool &found);
void searchByName(address root, string cariNama, bool &found);


// --- FITUR BARU (RELEVAN TREE) ---
void filterByYear(address root, int tahun, bool &found);
double totalPendapatanByYear(address root, int tahun);

// --- HELPER ---
infotype newLaundryData(int id, string nama, int tipe, float berat);
string getRealTime();
int getCurrentYear();       
string formatRupiah(double angka);

#endif