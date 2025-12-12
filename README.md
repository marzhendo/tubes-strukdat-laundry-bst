# 🧺 Laundry Management System (BST Implementation)

> **Tugas Besar Struktur Data - Telkom University Purwokerto**
>
> Sistem pengelolaan antrian dan tracking status cucian laundry berbasis CLI (Command Line Interface) yang mengimplementasikan struktur data **Binary Search Tree (BST)** untuk efisiensi pencarian dan pengurutan data.

---

## 👨‍💻 Kelompok 5: FreshNode

| No | NIM | Nama Anggota | 
| :-- | :--- | :--- | 
| 1 | **103112400101** | Aedil Riski Ansyah |
| 2 | **103112400102** | Marzhendo Galang Saputra | 
| 3 | **103112400153** | Fatir Gibran | 
| 4 | **103112400128** | Ma’ruf Sarifudin |

---

## 📖 Deskripsi Project

Sistem ini dibuat untuk membantu operasional laundry dalam mengelola antrian pelanggan. Menggunakan algoritma **Binary Search Tree (BST)**, program ini memungkinkan admin untuk:
1.  Menyimpan data pesanan (Order) dengan cepat.
2.  Mencari status cucian pelanggan berdasarkan ID/Nama dalam waktu logaritmik $O(\log n)$.
3.  Menampilkan antrian secara urut (Sorting) otomatis menggunakan traversal In-Order.

### Mengapa BST?
Kami memilih BST karena struktur ini memberikan keseimbangan performa yang baik antara proses *insertion* (tambah antrian) dan *searching* (cek status) dibandingkan dengan Array atau Linked List biasa.

---

## 🚀 Fitur Utama

* **[Insert] Tambah Pesanan:** Input data pelanggan (Nama, Berat, Jenis Layanan) ke dalam node tree.
* **[Search] Cek Status:** Mencari posisi data pelanggan untuk melihat status (Pending/Proses/Selesai).
* **[Update] Update Status:** Mengupdate status pengerjaan laundry.
* **[View] Lihat Antrian:** Menampilkan seluruh daftar antrian yang sedang berjalan secara terurut (Ascending).
* **[Delete] Ambil Cucian:** Menghapus node pelanggan dari tree setelah transaksi selesai/diambil.

---
