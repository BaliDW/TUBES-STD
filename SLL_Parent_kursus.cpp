#include "kursus.h"

// Inisialisasi List Utama
void createList(List &L) {
    L.first = nullptr;
}

// Buat Elemen Kursus Baru
adr_kursus newElementKursus(string nama, string kode) {
    adr_kursus P = new elm_kursus;
    P->info.namaKursus = nama;
    P->info.kodeKursus = kode;
    P->next = nullptr;
    P->firstModul = nullptr;
    return P;
}

// Mencari Kursus (Search SLL)
adr_kursus searchKursus(List L, string kodeKursus) {
    adr_kursus P = L.first;
    while (P != nullptr) {
        if (P->info.kodeKursus == kodeKursus) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

// Menambah Kursus (Insert Last SLL)
void insertKursus(List &L, adr_kursus P) {
    if (P == nullptr) return;
    
    // Cek duplikat agar tidak ada kode yang sama
    if (searchKursus(L, P->info.kodeKursus) != nullptr) {
        cout << "Gagal: Kursus " << P->info.kodeKursus << " sudah ada." << endl;
        return;
    }

    if (L.first == nullptr) {
        L.first = P;
    } else {
        adr_kursus Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

// Menghapus Kursus (Delete SLL)
void deleteKursus(List &L, string kodeKursus) {
    if (L.first == nullptr) return;

    adr_kursus P = L.first;
    adr_kursus prec = nullptr;

    while (P != nullptr && P->info.kodeKursus != kodeKursus) {
        prec = P;
        P = P->next;
    }

    if (P != nullptr) {
        if (P == L.first) {
            L.first = P->next;
        } else {
            prec->next = P->next;
        }
        // Isolasi Parent dan Child-nya
        P->next = nullptr;
        P->firstModul = nullptr; 
        cout << "Kursus " << kodeKursus << " berhasil dihapus." << endl;
    } else {
        cout << "Error: Kursus tidak ditemukan." << endl;
    }
}