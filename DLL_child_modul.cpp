#include "child.h"

void createModul(string judul, string durasi, string diff, adr_modul &M) {
    M = new elm_modul;
    M->info.judul = judul;
    M->info.durasi = durasi;
    M->info.difficulty = diff;
    M->next = nullptr;
    M->prev = nullptr;
}

void dealokasiModul(adr_modul &M) {
    // Hanya disiapkan jika butuh delete fisik
    delete M;
    M = nullptr;
}