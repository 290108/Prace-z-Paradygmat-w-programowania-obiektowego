#include <iostream>
#include <string>
using namespace std;

void dodajOsobe(string *tabNazwisko, string nazwisko, string *tabImie, string imie, unsigned int *tabIndeks, unsigned int indeks)
{  
    bool miejsce=0;
    int i=0;
    do{ 
    if (tabNazwisko[i].empty())
    {
        tabNazwisko[i]=nazwisko;
        tabImie[i]=imie;
        tabIndeks[i]=indeks;
        miejsce=1;
        break;
    }
        i++;
    }
    while(i<=10);
    if(miejsce==0)
    {
        cout << "lista jest pelna nie mozna dodac wiecej osob " << endl;
    }
}

void drukujListe(string *tabNazwisko, bool *tabObecnosc, string *tabImie, unsigned int *tabindeks)
{
    for(int i=0; i<10; i++)
    {
        if(tabImie[i].empty())
        {
            break;
        }
        else 
        {
            cout << tabImie[i] << " " << tabNazwisko[i]   << "  " << tabindeks[i] << "  " << tabObecnosc[i] << endl;

        }
    }
}

void ustawObecnosc(string *tabNazwisko,  bool *tabObecnosc,string nazwisko, bool obecnosc )
{
    bool znaleziono=0;
    for(int i=0; i<10; i++)
    {
        if(tabNazwisko[i]==nazwisko)
        {
            tabObecnosc[i]=obecnosc;
            znaleziono=1;
            break;
        }
        
    }
    if(znaleziono==0)
    {
        cout << "Nie znaleziono osoby" << endl;
    }
    
}

void usun(string *tabNazwisko, string *tabImie, unsigned int *tabIndeks, bool *tabObecnosc, string nazwisko)
{
bool znaleziono=0;
    for(int i=0; i<10; i++)
    {
        if(tabNazwisko[i]==nazwisko)
        {
            for(int j=i; j<(10-i); j++)
            {
                tabNazwisko[j]=tabNazwisko[j+1];
                tabImie[j]=tabImie[j+1];
                tabIndeks[j]=tabIndeks[j+1];
                tabObecnosc[j]=tabObecnosc[j+1];
                znaleziono=1;
            }
            break;
        }
        
    }
    if(znaleziono==0)
    {
        cout << "Nie znaleziono osoby" << endl;
    }
}

void Edytuj(string *tabNazwisko, string nazwisko, string *tabImie, string imie, unsigned int *tabIndeks, unsigned int indeks, int i)
{
    tabImie[i]=imie;
    tabNazwisko[i]=nazwisko;
    tabIndeks[i]=indeks;
}

int main() {
    string tabImie[10]={};
    unsigned int tabIndeks[10]={};
    string tabNazwisko[10]={};
    bool tabObecnosc[10]={false};
    string nazwisko;
    string imie;
    unsigned int indeks;
    bool obecnosc;
    int wybor;
    do{
        cout << "_______________________________" << endl;
        cout << "napisz 0. aby zamknac program" << endl;
        cout << "napisz 1. aby dodac osobe" << endl;
        cout << "napisz 2. aby ustawic obecnosc" << endl;
        cout << "napisz 3. aby wypisac liste" << endl;
        cout << "napisz 4. aby usunac studenta z listy" << endl;
        cout << "napisz 5. aby wybrac edytowac dane konkretnego studenta" << endl;

        cin >> wybor;
        switch (wybor)
        {
            case 1: // funkcja dodaj osobe
                cout << "Podaj nazwisko" << endl;
                cin >> nazwisko;
                cout << "Podaj Imie" << endl;
                cin >> imie;
                cout << "Podaj Indeks" << endl;
                cin >> indeks;
                dodajOsobe(tabNazwisko,  nazwisko, tabImie, imie, tabIndeks, indeks);
            break;
            case 2: // funkja zmieniajaca obecnosc 
            cout << "Podaj nazwisko" << endl;
                cin >> nazwisko;
                cout << "Podaj obecnosc" << endl;
                cin >> obecnosc;
                ustawObecnosc(tabNazwisko,tabObecnosc, nazwisko, obecnosc);
            break;
            case 3: //funkcja ukazujaca liste studentow na ekranie
            drukujListe(tabNazwisko, tabObecnosc, tabImie, tabIndeks);
            break;
            case 4: //funkcja usuwajaca studenta i zsuwajaca studentow 
            cout << "Podaj nazwisko student ktorego chcesz usunc" << endl;
            cin >> nazwisko;
            usun(tabNazwisko, tabImie, tabIndeks, tabObecnosc, nazwisko);
            break;
            case 0: // funkcja by zakonczyc dzialanie programu
            cout << "zamykanie programu" << endl;
            break;
            case 5: // funkcja edytujaca dane o studencie (indeks, imie, nazwisko)
            {
                cout <<"Wybierz Studenta do edytacji po nazwisku" << endl;
                cin >> nazwisko;
                string wyborDane=" ";
        bool znaleziono=0;
    for(int i=0; i<10; i++)
    {
        if(tabNazwisko[i]==nazwisko)
        {
            cout << "Co chcesz edytowac: nazwisko, imie, indeks " << endl;
            cin >> wyborDane;
            if(wyborDane == "nazwisko")
            {
          
            cout << "Podaj nazwisko:" << endl;
            cin >> nazwisko;
            indeks=tabIndeks[i];
            imie=tabImie[i];  
            }
            else if (wyborDane== "imie")
            {
                cout << "Podaj Imie:" << endl;
            cin >> imie;
            indeks=tabIndeks[i];
            nazwisko=tabNazwisko[i];
            }
            else if (wyborDane== "indeks")
            {
                  cout << "Podaj indeks:" << endl;
            cin >> indeks; 
            tabNazwisko[i];
            imie=tabImie[i];    
            }
            znaleziono=1;
            Edytuj(tabNazwisko, nazwisko, tabImie, imie, tabIndeks, indeks, i);
            break;
        }
        
    }
    if(znaleziono==0)
    {
        cout << "Nie znaleziono osoby" << endl;
    }
    break;
            }

            default:
            cout << "nieznany wybór"<<endl;
            break;
        }
        
    }while (wybor !=0);
    return 0;
}
