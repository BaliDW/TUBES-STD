#ifndef CHILD_H_INCLUDED
#define CHILD_H_INCLUDED
#include "parent.h"
#include <iostream>
using namespace std;

struct infotype_modul {
    string judul;
    string durasi;
    string difficulty;
};

typedef struct elm_modul *adr_modul;

struct elm_modul {
    infotype_modul info;
    adr_modul next;
    adr_modul prev;
};

void createModul(string judul, string durasi, string diff, adr_modul &M);
adr_modul searchModul(adr_kursus P, string judulModul);

#endif // CHILD_H_INCLUDED