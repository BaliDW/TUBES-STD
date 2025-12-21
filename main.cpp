#include "kursus.h"

/* --- INISIALISASI --- */

// Buat List Parent Kosong
void createList(List &L) {
    L.first = nullptr;
}

// Buat Elemen Kursus Baru (Parent - SLL)
adr_kursus newElementKursus(string nama, string kode) {
    adr_kursus P = new elm_kursus;
    P->info.namaKursus = nama;
    P->info.kodeKursus = kode;
    P->next = nullptr;
    P->firstModul = nullptr;
    return P;
}

// Buat Elemen Modul Baru (Child - DLL)
adr_modul newElementModul(string judul, string durasi, string diff) {
    adr_modul P = new elm_modul;
    P->info.judul = judul;
    P->info.durasi = durasi;
    P->info.difficulty = diff;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

/* --- FUNGSIONALITAS --- */

// a. Menambahkan Kursus (Insert Last SLL + Cek Duplikat)
void insertKursus(List &L, adr_kursus P) {
    if (P == nullptr) return;

    // Cek apakah kursus dengan kode yang sama sudah ada
    if (searchKursus(L, P->info.kodeKursus) != nullptr) {
        cout << "Gagal: Kursus dengan kode " << P->info.kodeKursus << " sudah ada." << endl;
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

// c. Mencari Kursus Berdasarkan Kode
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

// b & d. Menambahkan Modul ke Kursus (Insert Last DLL)
void addModulToKursus(List &L, string kodeKursus, adr_modul C) {
    if (C == nullptr) return;

    adr_kursus P = searchKursus(L, kodeKursus);
    if (P == nullptr) {
        cout << "Gagal: Kursus dengan kode " << kodeKursus << " tidak ditemukan!" << endl;
        return;
    }

    // Insert Last pada Doubly Linked List (Child)
    if (P->firstModul == nullptr) {
        P->firstModul = C;
    } else {
        adr_modul Q = P->firstModul;
        while (Q->next != nullptr) {
            // Cek jika modul sudah ada (opsional, berdasarkan judul)
            if (Q->info.judul == C->info.judul) {
                cout << "Peringatan: Modul dengan judul tersebut sudah ada di kursus ini." << endl;
            }
            Q = Q->next;
        }
        // Cek elemen terakhir untuk duplikat
        if (Q->info.judul == C->info.judul) {
            cout << "Peringatan: Modul dengan judul tersebut sudah ada di kursus ini." << endl;
        }

        Q->next = C;
        C->prev = Q;
    }
}

// e. Menampilkan Modul berdasarkan Kursus tertentu
void showModulByKursus(List L, string kodeKursus) {
    adr_kursus P = searchKursus(L, kodeKursus);
    if (P == nullptr) {
        cout << "Kursus \"" << kodeKursus << "\" tidak ditemukan." << endl;
        return;
    }

    cout << "Daftar Modul untuk Kursus: " << P->info.namaKursus << " (" << P->info.kodeKursus << ")" << endl;
    adr_modul Q = P->firstModul;
    if (Q == nullptr) {
        cout << "  [Belum ada modul]" << endl;
    } else {
        int i = 1;
        while (Q != nullptr) {
            cout << "  " << i << ". " << Q->info.judul << " | Durasi: " << Q->info.durasi 
                 << " | Level: " << Q->info.difficulty << endl;
            Q = Q->next;
            i++;
        }
    }
}

// f. Menghapus Kursus beserta seluruh modulnya (Unlink SLL)
void deleteKursus(List &L, string kodeKursus) {
    if (L.first == nullptr) {
        cout << "List kosong, tidak ada yang dihapus." << endl;
        return;
    }

    adr_kursus P = L.first;
    adr_kursus prec = nullptr;

    // Pencarian elemen dan previous-nya
    while (P != nullptr && P->info.kodeKursus != kodeKursus) {
        prec = P;
        P = P->next;
    }

    if (P == nullptr) {
        cout << "Kursus \"" << kodeKursus << "\" tidak ditemukan." << endl;
        return;
    }

    // Proses Unlink
    if (P == L.first) {
        L.first = P->next;
    } else {
        prec->next = P->next;
    }

    // Isolasi pointer (Anak-anak otomatis ikut terlepas dari list utama)
    P->next = nullptr;
    P->firstModul = nullptr; 

    cout << "Kursus \"" << kodeKursus << "\" berhasil dilepas dari sistem." << endl;
}

// g. Menghapus Modul dari Kursus (Unlink DLL)
void deleteModul(List &L, string kodeKursus, string judulModul) {
    adr_kursus P = searchKursus(L, kodeKursus);
    if (P == nullptr) {
        cout << "Kursus tidak ditemukan." << endl;
        return;
    }

    adr_modul C = P->firstModul;
    while (C != nullptr && C->info.judul != judulModul) {
        C = C->next;
    }

    if (C == nullptr) {
        cout << "Modul \"" << judulModul << "\" tidak ditemukan di kursus ini." << endl;
        return;
    }

    // Proses Unlink Doubly Linked List
    if (C == P->firstModul) { // Kasus: Elemen Pertama
        P->firstModul = C->next;
        if (P->firstModul != nullptr) {
            P->firstModul->prev = nullptr;
        }
    } else if (C->next == nullptr) { // Kasus: Elemen Terakhir
        C->prev->next = nullptr;
    } else { // Kasus: Di Tengah
        C->prev->next = C->next;
        C->next->prev = C->prev;
    }

    // Isolasi
    C->next = nullptr;
    C->prev = nullptr;
    cout << "Modul \"" << judulModul << "\" berhasil dihapus." << endl;
}

// h. Menampilkan Seluruh Kursus beserta Modulnya
void showAllData(List L) {
    if (L.first == nullptr) {
        cout << "Sistem kosong. Belum ada data kursus." << endl;
        return;
    }

    adr_kursus P = L.first;
    cout << "========== DATA SELURUH KURSUS ==========" << endl;
    while (P != nullptr) {
        cout << "\nKursus: " << P->info.namaKursus << " [" << P->info.kodeKursus << "]" << endl;
        adr_modul Q = P->firstModul;
        if (Q == nullptr) {
            cout << "  (Tidak ada modul)" << endl;
        } else {
            while (Q != nullptr) {
                cout << "  - " << Q->info.judul << " (" << Q->info.durasi << ")" << endl;
                Q = Q->next;
            }
        }
        P = P->next;
    }
    cout << "\n==========================================" << endl;
}

// i. Menghitung Jumlah Modul (Helper)
int countModul(adr_kursus P) {
    int count = 0;
    if (P != nullptr) {
        adr_modul Q = P->firstModul;
        while (Q != nullptr) {
            count++;
            Q = Q->next;
        }
    }
    return count;
}

// j. Menampilkan Kursus dengan Modul Terbanyak dan Tersedikit
void showMinMaxModul(List L) {
    if (L.first == nullptr) {
        cout << "Data kosong, tidak bisa menghitung statistik." << endl;
        return;
    }

    adr_kursus P = L.first;
    adr_kursus maxP = P, minP = P;
    int maxVal = countModul(P);
    int minVal = countModul(P);

    P = P->next;
    while (P != nullptr) {
        int currentCount = countModul(P);
        if (currentCount > maxVal) {
            maxVal = currentCount;
            maxP = P;
        }
        if (currentCount < minVal) {
            minVal = currentCount;
            minP = P;
        }
        P = P->next;
    }

    cout << "--- Statistik Kursus ---" << endl;
    cout << "Modul Terbanyak   : " << maxP->info.namaKursus << " (" << maxVal << " modul)" << endl;
    cout << "Modul Tersedikit  : " << minP->info.namaKursus << " (" << minVal << " modul)" << endl;
}