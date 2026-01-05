#ifndef LAUNDRY_H
#define LAUNDRY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// --- SETTING HARGA ---
const double HARGA_REGULER = 6000;
const double HARGA_EXPRESS = 10000;
const float MIN_BERAT_DISKON = 10.0;
const double PERSEN_DISKON = 0.10;

// --- SETTING STATUS ---
const int STS_ANTRI = 0;
const int STS_PROSES = 1;
const int STS_SELESAI = 2;

struct Laundry {
    int id;
    string nama;
    int tipe;       // 1: Express, 2: Reguler
    float berat;
    int tahun;
    string waktuMasuk;
    double totalBayar;
    int status;     // 0: Antri, 1: Proses, 2: Selesai
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
void printInOrder(address root);

// --- OPERASIONAL ---
void processNextJob(address root, bool &berhasil); 
void markAsFinished(address root, int id, bool &berhasil);
void updateData(address &root, int id); 
bool deleteNodeByID(address &root, int id); 

// --- SEARCH ---
address searchByID(address root, int cariID);
void searchByWeight(address root, float cariBerat, bool &found);
void searchByName(address root, string cariNama, bool &found);


infotype newLaundryData(int id, string nama, int tipe, float berat);
string getRealTime();
int getCurrentYear();
string formatRupiah(double angka);
string getStatusLabel(int status);

#endif