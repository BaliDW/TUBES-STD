#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include "parent.h" 
using namespace std;

void addDataKursus(List_Kursus &L);
void addDataModul(List_Kursus &L);
void showAll(List_Kursus L);
void showModulOfKursus(List_Kursus L);
void deleteDataModul(List_Kursus &L);
void deleteDataKursus(List_Kursus &L);
void showStatistics(List_Kursus L);

void header();
void main_menu(List_Kursus &L);

#endif // MENU_H_INCLUDED