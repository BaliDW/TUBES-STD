#include "menu.h"

void addDataKursus(List_Kursus &L) {
    string nama, kode;
    cout << "Masukkan Nama Kursus: ";
    cin >> nama;
    cout << "Masukkan Kode Kursus: ";
    cin >> kode;

    adr_kursus P;
    createKursus(nama, kode, P);
    insertLastKursus(L, P);
    cout << "Kursus berhasil dibuat." << endl;
}

void addDataModul(List_Kursus &L) {
    string targetKode, judul, durasi, diff;
    cout << "Masukkan Kode Kursus Tujuan: ";
    cin >> targetKode;

    adr_kursus P = searchKursus(L, targetKode);
    if (P != nullptr) {
        cout << "Judul Modul: ";
        cin >> judul;
        cout << "Durasi: ";
        cin >> durasi;
        cout << "Kesulitan: ";
        cin >> diff;

        adr_modul M;
        createModul(judul, durasi, diff, M);
        insertModul(P, M);
        cout << "Modul berhasil ditambahkan ke " << P->info.namaKursus << endl;
    } else {
        cout << "Kursus tidak ditemukan!" << endl;
    }
}

void showAll(List_Kursus L) {
    if (L.first == nullptr) {
        cout << "Data Kosong." << endl;
    } else {
        adr_kursus P = L.first;
        while (P != nullptr) {
            cout << "--------------------------------" << endl;
            cout << "KURSUS: " << P->info.namaKursus << " (" << P->info.kodeKursus << ")" << endl;
            adr_modul Q = P->firstModul;
            if (Q == nullptr) {
                cout << "   (Tidak ada modul)" << endl;
            } else {
                while (Q != nullptr) {
                    cout << "   -> " << Q->info.judul
                         << " [" << Q->info.durasi << "]" << endl;
                    Q = Q->next;
                }
            }
            P = P->next;
        }
    }
}

void showModulOfKursus(List_Kursus L) {
    string targetKode;
    cout << "Cari Kode Kursus: ";
    cin >> targetKode;

    adr_kursus P = searchKursus(L, targetKode);
    if (P != nullptr) {
        cout << "Daftar Modul " << P->info.namaKursus << ":" << endl;
        adr_modul Q = P->firstModul;
        while(Q != nullptr) {
            cout << "- " << Q->info.judul << endl;
            Q = Q->next;
        }
    } else {
        cout << "Kursus tidak ditemukan." << endl;
    }
}

void deleteDataModul(List_Kursus &L) {
    string targetKode, judul;
    cout << "Kode Kursus: ";
    cin >> targetKode;

    adr_kursus P = searchKursus(L, targetKode);
    if (P != nullptr) {
        cout << "Judul Modul yg dihapus: ";
        cin >> judul;
        deleteModulFromKursus(P, judul);
        cout << "Modul Dihapus" << endl;
    } else {
        cout << "Kursus tidak ditemukan." << endl;
    }
}

void deleteDataKursus(List_Kursus &L) {
    string targetKode;
    cout << "Hapus Kode Kursus: ";
    cin >> targetKode;
    
    if (L.first != nullptr) {
        adr_kursus P = L.first;
        adr_kursus prev = nullptr;

        while(P != nullptr && P->info.kodeKursus != targetKode) {
            prev = P;
            P = P->next;
        }

        if (P != nullptr) {
            while (P->firstModul != nullptr) {
                string judulModul = P->firstModul->info.judul;
                deleteModulFromKursus(P, judulModul);
            }
            if (P == L.first) {
                L.first = P->next;
            } else {
                prev->next = P->next;
            }
            P->next = nullptr;
            cout << "Kursus beserta modulnya berhasil di-unlink." << endl;
        } else {
            cout << "Kursus tidak ditemukan." << endl;
        }
    }
}

void showStatistics(List_Kursus L) {
    if (L.first == nullptr) {
        cout << "Data Kosong." << endl;
    } else {
        adr_kursus P = L.first, maxP = P, minP = P;
        int maxV = countModul(P), minV = countModul(P);

        P = P->next;
        while (P != nullptr) {
            int curV = countModul(P);
            if (curV > maxV) { 
                maxV = curV; 
                maxP = P; 
            }
            if (curV < minV) { 
                minV = curV; 
                minP = P; 
            }
            P = P->next;
        }

        cout << "=== STATISTIK ===" << endl;
        cout << "Terbanyak : " << maxP->info.namaKursus << " (" << maxV << ")" << endl;
        cout << "Tersedikit: " << minP->info.namaKursus << " (" << minV << ")" << endl;
    }
}

void header() {
    cout << "\n==============================" << endl;
    cout << "   PLATFORM KURSUS & MODUL    " << endl;
    cout << "==============================" << endl;
}

void main_menu(List_Kursus &L) {
    int pilihan;
    do {
        header();
        cout << "1. Tambah Kursus" << endl;
        cout << "2. Tambah Modul" << endl;
        cout << "3. Tampilkan Semua" << endl;
        cout << "4. Cari Modul Kursus" << endl;
        cout << "5. Hapus Modul" << endl;
        cout << "6. Hapus Kursus" << endl;
        cout << "7. Statistik" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1: addDataKursus(L); break;
            case 2: addDataModul(L); break;
            case 3: showAll(L); break;
            case 4: showModulOfKursus(L); break;
            case 5: deleteDataModul(L); break;
            case 6: deleteDataKursus(L); break;
            case 7: showStatistics(L); break;
        }
    } while (pilihan != 0);
}