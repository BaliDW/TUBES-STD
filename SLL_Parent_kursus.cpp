#include "parent.h"
#include "child.h"

void createList(List_Kursus &L) {
// I.S. Sembarang (List L belum terdefinisi nilainya).
// F.S. Terbentuk List L kosong (L.first berisi nullptr).
    L.first = nullptr;
}

void createKursus(string nama, string kode, adr_kursus &P) {
// I.S. Sembarang (P belum teralokasi).
// F.S. Alokasi memori berhasil. P menunjuk ke elemen baru dengan info nama dan kode.
//      Pointer next dan firstModul (child) di-set nullptr.
    P = new elm_kursus;
    P->info.namaKursus = nama;
    P->info.kodeKursus = kode;
    P->next = nullptr;
    P->firstModul = nullptr;
}

void insertLastKursus(List_Kursus &L, adr_kursus P) {
// I.S. List L terdefinisi (bisa kosong), P adalah elemen yang sudah dialokasi.
// F.S. Jika kode kursus P unik (belum ada di L), P dimasukkan ke elemen paling belakang (Insert Last).
//      Jika kode sudah ada, P batal dimasukkan dan muncul pesan error.
    if (L.first == nullptr) {
        L.first = P;
    } else if (searchKursus(L, P->info.kodeKursus) != nullptr) {
        cout << "Kursus dengan kode " << P->info.kodeKursus << " sudah ada." << endl;
    } else{
        adr_kursus Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adr_kursus searchKursus(List_Kursus L, string kodeKursus) {
// I.S. List L terdefinisi, kodeKursus terdefinisi.
// F.S. Mengembalikan alamat elemen kursus jika ditemukan kode yang cocok.
//      Mengembalikan nullptr jika tidak ditemukan.
    adr_kursus P = L.first;
    while (P != nullptr && P->info.kodeKursus != kodeKursus) {
        P = P->next;
    }
    return P;
}

void insertModul(adr_kursus P, adr_modul C) {
// I.S. P terdefinisi (Parent), C terdefinisi (Child baru).
// F.S. Elemen child C dimasukkan ke akhir list child milik P (Insert Last DLL).
//      Pointer next dan prev pada child tersambung dengan benar.
    if (P->firstModul == nullptr) {
        P->firstModul = C;
    } else {
        adr_modul Q = P->firstModul;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
        C->prev = Q;
    }
}

void deleteModulFromKursus(adr_kursus P, string judulModul) {
// I.S. P terdefinisi. judulModul yang ingin dihapus diketahui.
// F.S. Jika modul ditemukan, elemen tersebut diputus (unlinked) dari list child milik P.
//      Menangani penghapusan di awal (First), tengah, atau akhir (Last) list DLL.
    if (P->firstModul != nullptr) {
        adr_modul C = P->firstModul;
        bool found = false;
        if (searchModul(P, judulModul) == nullptr) {
            cout << "Modul dengan judul " << judulModul << " tidak ditemukan." << endl;
        } else {
            while (C != nullptr && !found) {
                if (C->info.judul == judulModul) {
                    if (C == P->firstModul) {
                        P->firstModul = C->next;
                        if (P->firstModul != nullptr) {
                            P->firstModul->prev = nullptr;
                        }
                    } else if (C->next == nullptr) {
                        C->prev->next = nullptr;
                    } else {
                        C->prev->next = C->next;
                        C->next->prev = C->prev;
                    }
                    found = true;
                } else {
                    C = C->next;
                }
            }
        }
    }
}

int countModul(adr_kursus P) {
// I.S. P terdefinisi (Parent).
// F.S. Mengembalikan jumlah total modul (child) yang dimiliki oleh kursus P.
    int count = 0;
    adr_modul Q = P->firstModul;
    while (Q != nullptr) {
        count++;
        Q = Q->next;
    }
    return count;
}
