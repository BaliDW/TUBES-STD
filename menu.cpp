#include "menu.h"

void addDataKursus(List_Kursus &L) {
// I.S. List L terdefinisi (bisa kosong). Pengguna akan diminta memasukkan data kursus.
// F.S. Jika kode kursus belum ada, elemen kursus baru terbentuk dan dimasukkan ke akhir List L (Insert Last).
//      Jika kode sudah ada, menampilkan pesan kesalahan dan data tidak masuk.
    string nama, kode;
    cout << "Masukkan Nama Kursus: ";
    cin >> nama;
    cout << "Masukkan Kode Kursus: ";
    cin >> kode;
    if (searchKursus(L, kode) != nullptr) {
        cout << "Kursus sudah ada!" << endl;
    } else {
        adr_kursus P;
        createKursus(nama, kode, P);
        insertLastKursus(L, P);
    cout << "Kursus berhasil dibuat." << endl;
    }
}

void addDataModul(List_Kursus &L) {
// I.S. List L terdefinisi. Pengguna akan diminta memasukkan kode kursus tujuan dan data modul.
// F.S. Jika kursus ditemukan dan modul belum ada di kursus tersebut, modul baru ditambahkan ke dalam kursus (Insert Modul).
//      Jika kursus tidak ada atau modul duplikat, menampilkan pesan kesalahan.
    string targetKode, judul, durasi, diff;
    cout << "Masukkan Kode Kursus Tujuan: ";
    cin >> targetKode;

    adr_kursus P = searchKursus(L, targetKode);
    adr_modul Q = searchModul(P, targetKode);
    cout << "Judul Modul: ";
    cin >> judul;
    cout << "Durasi (Menit): ";
    cin >> durasi;
    cout << "Kesulitan (Mudah/Sedang/Sulit): ";
    cin >> diff;
    if (P != nullptr) {
        if (Q != nullptr) {
            cout << "Modul sudah ada!" << endl;
        } else {
            adr_modul M;
            createModul(judul, durasi, diff, M);
            insertModul(P, M);
            cout << "Modul berhasil ditambahkan ke " << P->info.namaKursus << endl;
        }
    } else {
        cout << "Kursus tidak ditemukan!" << endl;
    }
}

void showAll(List_Kursus L) {
// I.S. List L terdefinisi (bisa kosong).
// F.S. Menampilkan seluruh data Kursus beserta Modul-modul yang ada di dalamnya ke layar.
//      Jika list kosong, menampilkan pesan "Data Kosong".
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
// I.S. List L terdefinisi. Pengguna diminta input kode kursus yang dicari.
// F.S. Jika kursus ditemukan, menampilkan daftar modul milik kursus tersebut.
//      Jika tidak, menampilkan pesan kursus tidak ditemukan.
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
// I.S. List L terdefinisi. Pengguna input kode kursus dan judul modul yang akan dihapus.
// F.S. Jika kursus dan modul ditemukan, elemen modul dihapus dari list modul milik kursus tersebut (Delete Child).
    string targetKode, judul;
    cout << "Kode Kursus: ";
    cin >> targetKode;

    adr_kursus P = searchKursus(L, targetKode);
    if (P != nullptr) {
        cout << "Judul Modul yg dihapus: ";
        cin >> judul;
        deleteModulFromKursus(P, judul);
        cout << "Modul berhasil dihapus." << endl;
    } else {
        cout << "Kursus tidak ditemukan." << endl;
    }
}

void deleteDataKursus(List_Kursus &L) {
// I.S. List L terdefinisi. Pengguna input kode kursus yang akan dihapus.
// F.S. Jika kursus ditemukan, seluruh modul di dalamnya dihapus terlebih dahulu,
//      kemudian elemen kursus dihapus dari List L (Delete Parent & All Children).
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
            cout << "Kursus berhasil dihapus." << endl;
        } else {
            cout << "Kursus tidak ditemukan." << endl;
        }
    }
}

void showStatistics(List_Kursus L) {
// I.S. List L terdefinisi.
// F.S. Menampilkan statistik jumlah modul per kursus, serta kursus dengan modul terbanyak dan tersedikit.
    if (L.first == nullptr) {
        cout << "Data kursus kosong." << endl;
    } else {
        cout << "\n=== STATISTIK PLATFORM PEMBELAJARAN ===" << endl;

        cout << "\n--- DAFTAR KURSUS & JUMLAH MODUL ---" << endl;
        adr_kursus K = L.first;
        adr_kursus maxK = K;
        adr_kursus minK = K;

        int maxCount = countModul(K);
        int minCount = maxCount;
        int nomor = 1;

        while (K != nullptr) {
            int jumlahModul = countModul(K);
            cout << nomor << ". " << K->info.namaKursus
                 << " (" << K->info.kodeKursus << ") - "
                 << jumlahModul << " modul" << endl;

            if (jumlahModul > maxCount) {
                maxCount = jumlahModul;
                maxK = K;
            }

            if (jumlahModul < minCount) {
                minCount = jumlahModul;
                minK = K;
            }

            nomor++;
            K = K->next;
        }

        cout << "\n--- ANALISIS ---" << endl;
        if (maxK != nullptr) {
            cout << "Kursus dengan Modul TERBANYAK: " << maxK->info.namaKursus
                 << " (" << maxK->info.kodeKursus << ") dengan "
                 << maxCount << " modul" << endl;
        }
        if (minK != nullptr) {
            cout << "Kursus dengan Modul TERSEDIKIT: " << minK->info.namaKursus
                 << " (" << minK->info.kodeKursus << ") dengan "
                 << minCount << " modul" << endl;
        }
    }
}

void header() {
// I.S. Sembarang.
// F.S. Menampilkan judul aplikasi (Header) ke layar.
    cout << "\n==============================" << endl;
    cout << "   PLATFORM KURSUS & MODUL    " << endl;
    cout << "==============================" << endl;
}

void main_menu(List_Kursus &L) {
// I.S. List L terdefinisi (biasanya kosong saat program baru mulai).
// F.S. Menampilkan menu interaktif terus menerus hingga user memilih angka 0 (Keluar).
//      List L mungkin berubah isinya sesuai pilihan user (tambah/hapus).
    int pilihan = -1;
    while (pilihan != 0) {
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
    };
}
