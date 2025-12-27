#include "child.h"

void createModul(string judul, string durasi, string diff, adr_modul &M) {
// I.S. Terdefinisi data judul, durasi, dan difficulty yang akan dimasukkan ke dalam modul.
// F.S. Terbentuk elemen modul baru M yang berisi info judul, durasi, dan difficulty. Pointer next dan prev dari M bernilai NULL.
    M = new elm_modul;
    M->info.judul = judul;
    M->info.durasi = durasi;
    M->info.difficulty = diff;
    M->next = nullptr;
    M->prev = nullptr;
}

adr_modul searchModul(adr_kursus P, string judulModul) {
// I.S. Terdefinisi pointer kursus P (tidak NULL) dan judulModul yang ingin dicari. List modul mungkin kosong.
// F.S. Mengembalikan alamat elemen modul jika judulModul ditemukan di dalam list modul milik P, atau mengembalikan NULL jika tidak ditemukan.
    adr_modul C = P->firstModul;
    while (C != nullptr && C->info.judul != judulModul) {
        C = C->next;
    }
    return C;
}
