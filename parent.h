#ifndef PARENT_H_INCLUDED
#define PARENT_H_INCLUDED

#include <iostream>
#include "child.h" 
using namespace std;

struct infotype_kursus {
    string namaKursus;
    string kodeKursus;
};

typedef struct elm_kursus *adr_kursus;

struct elm_kursus {
    infotype_kursus info;
    adr_kursus next;
    adr_modul firstModul; 
};

struct List_Kursus {
    adr_kursus first;
};

// Primitif Parent
void createList(List_Kursus &L);
void createKursus(string nama, string kode, adr_kursus &P);
void insertLastKursus(List_Kursus &L, adr_kursus P);
adr_kursus searchKursus(List_Kursus L, string kodeKursus);

// Primitif Relasi
void insertModul(adr_kursus P, adr_modul C);
void deleteModulFromKursus(adr_kursus P, string judulModul);
int countModul(adr_kursus P);

#endif // PARENT_H_INCLUDED