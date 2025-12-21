#include "parent.h"

void createList(List_Kursus &L) {
    L.first = nullptr;
}

void createKursus(string nama, string kode, adr_kursus &P) {
    P = new elm_kursus;
    P->info.namaKursus = nama;
    P->info.kodeKursus = kode;
    P->next = nullptr;
    P->firstModul = nullptr;
}

void insertLastKursus(List_Kursus &L, adr_kursus P) {
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

adr_kursus searchKursus(List_Kursus L, string kodeKursus) {
    adr_kursus P = L.first;
    while (P != nullptr) {
        if (P->info.kodeKursus == kodeKursus) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void insertModul(adr_kursus P, adr_modul C) {
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
    if (P->firstModul == nullptr) return;

    adr_modul C = P->firstModul;
    while (C != nullptr) {
        if (C->info.judul == judulModul) {
            // Unlink Logic (Tanpa delete memori, hanya putus pointer)
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
            // Isolasi
            C->next = nullptr;
            C->prev = nullptr;
            return;
        }
        C = C->next;
    }
}

int countModul(adr_kursus P) {
    int count = 0;
    adr_modul Q = P->firstModul;
    while (Q != nullptr) {
        count++;
        Q = Q->next;
    }
    return count;
}