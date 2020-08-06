#include <iostream>
#include "urzytkownik.h"

using namespace std;

int main()
{
    Uzytkownik uzytkownik;
    uzytkownik.rejestracjaUzytkownika(uzytkownicy);
    uzytkownik.logowanieUzytkownika(uzytkownicy);
    uzytkownik.zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
    uzytkownik.wyswietlMenuLogowania();

}
