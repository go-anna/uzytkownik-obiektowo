#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

class Uzytkownik
{
   public:
           int id;
    string login;
    string haslo;

     static void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy);
    static   int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy);
     static void zapiszDaneUzytkownikaDoPliku (vector <Uzytkownik> &uzytkownicy);
     static void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy);
    static  void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika);
    static  void wyswietlMenuLogowania();


};
