#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Urzytkownik.h"

using namespace std;


void Uzytkownik::rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    int id;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik Osoba;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        while(itr -> login == login)
        {
            cout << "Podany uztkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
        }
    }

    cout << "Podaj haslo: ";
    cin >> haslo;

    if (uzytkownicy.empty() == true)
    {
        Osoba.id = 1;
    }
    else
    {
        Osoba.id = uzytkownicy.back().id + 1;
    }

    Osoba.login = login;
    Osoba.haslo = haslo;

    uzytkownicy.push_back(Osoba);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> id) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    }
    cout<< "Konto zalozone." <<endl;
    Sleep(1000);
}
int Uzytkownik::logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string loginUzytkownika, hasloUzytkownika;
    bool znalezionyUzytkownik = 0;
    int proby = 0;
    cout << "Podaj login: ";
    cin >>  loginUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> login == loginUzytkownika)
        {
            znalezionyUzytkownik = 1;
            for(int iloscProb = 0; iloscProb < 3; iloscProb++)
            {
                proby = iloscProb + 1;
                cout << "Podaj haslo. Pozostalo prob " << 3 - iloscProb << ":";
                cin >> hasloUzytkownika;
                if (itr -> haslo == hasloUzytkownika)
                {
                    cout<< "Jestes zalogowany."<<endl;
                    return itr -> id;
                }
            }
            if( proby == 3)
            {
                cout << "Podales bledne haslo.Wprowadz ponownie haslo." << endl;
            }
        }
    }

    if(!znalezionyUzytkownik)
    {
        cout << "Nie ma uzytkownika z takim loginem." << endl;
    }

    Sleep(1500);
    return 0;
}
void Uzytkownik::zapiszDaneUzytkownikaDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string liniaZDanymiUzytkownika = "";
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> id) + '|';
            liniaZDanymiUzytkownika += itr -> login + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku." << endl;
        system("pause");
    }
}
void Uzytkownik::wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    string dane;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int iloscUzytkownikow = 0;
    fstream plik;
    Uzytkownik pusty;

    uzytkownicy.clear();
    plik.open("Uzytkownicy.txt",ios::in);
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            uzytkownicy.push_back(pusty);
            iloscUzytkownikow++;
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscPionowychKresek++;
                    dane = linia.substr (poczatek,ileZnakowWyjac);
                    switch (iloscPionowychKresek)
                    {
                    case 1:
                        uzytkownicy[iloscUzytkownikow - 1].id = atoi(dane.c_str());
                        break;
                    case 2:
                        uzytkownicy[iloscUzytkownikow - 1].login = dane;
                        break;
                    case 3:
                        uzytkownicy[iloscUzytkownikow - 1].haslo = dane;
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }
}
void Uzytkownik::zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string noweHaslo = "";
    cout << "Podaj nowe haslo: ";
    cin>>noweHaslo;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr -> id == idZalogowanegoUzytkownika)
        {
            itr -> haslo = noweHaslo;
            cout << "Haslo zostalo zmienione." << endl << endl;
            system("pause");
        }
    }
    zapiszDaneUzytkownikaDoPliku(uzytkownicy);

}
int Uzytkownik::wylogujUzytkownika (vector <Adresat> &adresat, int idZalogowanegoUzytkownika)
{

    char wyborFunkcji;
    cout << "Czy na pewno chcesz sie wylogowac (t/n)?" << endl;

    while (true)
    {
        cin >> wyborFunkcji;
        if (wyborFunkcji == 't')
        {
            idZalogowanegoUzytkownika = 0;
            adresat.clear();
            cout << "Poprawnie wylogowano.";
            Sleep(2000);
            return idZalogowanegoUzytkownika;
        }
        else if (wyborFunkcji == 'n')
        {
            return idZalogowanegoUzytkownika;
        }
        else
        {
            system("cls");
            cout << "Czy na pewno chcesz sie wylogowac (t/n)?" << endl;
        }
    }
}
void Uzytkownik::wyswietlMenuLogowania()
{
    system("cls");
    cout << "1. Zarejestruj sie" << endl;
    cout << "2. Zaloguj sie" << endl;
    cout << "9. Zakoncz program" << endl;
}
