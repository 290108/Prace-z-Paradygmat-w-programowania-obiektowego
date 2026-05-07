#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Osoba {
private: //zmienne w klasie do któych potrzebne są funkcje by zmienic
    string imie;
    string nazwisko;
    string indeks;

bool czyPoprawne(string tekst) {  //funkacja sprawdza czy imie lub nazwisko posiada minimum 2 listery oraz nie posiada znaków z poza alfabetu
        int licznikLiter = 0;
        for (char c : tekst) {
            if (!isalpha(static_cast<unsigned char>(c))) {
                return false; 
            }
            if (isalpha(static_cast<unsigned char>(c))) {
                licznikLiter++;
            }
        }
        return licznikLiter >= 2;
    }

bool czyCyfry(string tekst) {       //osobna funkcja od sprawdzania czy indeks posiada tylko cyfry
        if (tekst.empty()) return false;
        for (char c : tekst) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                return false; 
            }
        }
        return true;
    }

public://dostep do funkcji zmieniających wartosci w klasie
    Osoba() : imie(""), nazwisko(""), indeks("") {} //czyści miejsce pod tabelke

    void setImie(string _imie) { if(czyPoprawne(_imie))
        {imie = _imie; } 
    else {cout <<"Bledne imie, musi posiadac minimum 2 litery bez znakow specjalnych"<<endl;}}
    string getImie() { return imie; }

    void setNazwisko(string _nazwisko) {if(czyPoprawne(_nazwisko)){nazwisko=_nazwisko;}
    else {cout << "Bledne nazwisko, musi posiadac minimum 2 litery oraz bez znaków specjalnych"<<endl;}}
    string getNazwisko() { return nazwisko; }

    void setIndeks(string _indeks) {if(czyCyfry(_indeks)){indeks=_indeks;}
    else{cout << "bledny indeks, powinien zawierac same cyfry"<< endl;} }
    string getIndeks() { return indeks; }

    bool isEmpty() { return imie.empty(); }
    void wyczysc() { imie = ""; nazwisko = ""; indeks = ""; }
};

void dodajOsobe(Osoba *tab, string nazwisko, string imie, string indeks)
{       //funkcja dodajaca osoba jezeli dane spelniaja warunki
    bool miejsce=0;
    int i=0;
    
    do{ 
    if (tab[i].isEmpty())
    {
        miejsce=1;
            tab[i].setImie(imie);
            tab[i].setNazwisko(nazwisko);
            tab[i].setIndeks(indeks);
            if(tab[i].getImie() == "" || tab[i].getNazwisko() == "" || tab[i].getIndeks() == "") {
                tab[i].wyczysc();}

        break;
    }
        i++;
    }
    while(i<10);
    if(miejsce==0)
    {
        cout << "lista jest pelna nie mozna dodac wiecej osob " << endl;
    }
}

void drukujListe(Osoba *tab, bool *tabObecnosc)
{           //funkcja wyswietlajaca tablice na ekran
    for(int i=0; i<10; i++)
    {
        if(tab[i].isEmpty())
        {
            break;
        }
        else 
        {
            cout << tab[i].getImie() << " " << tab[i].getNazwisko()   << "  " <<tab[i].getIndeks() << "  " << tabObecnosc[i] << endl;

        }
    }
}

void ustawObecnosc(Osoba *tab,  bool *tabObecnosc,string nazwisko, bool obecnosc )
{       //funkcja do zmiany obecnosci studentow
    bool znaleziono=0;
    for(int i=0; i<10; i++)
    {
        if(tab[i].getNazwisko()==nazwisko)
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

void usun(Osoba *tab, bool *tabObecnosc, string nazwisko)
{       //fukcja usuwa wybranego studenta i zsuwa studentuw powyzej
bool znaleziono=0;
    for(int i=0; i<10; i++)
    {
        if(tab[i].getNazwisko() == nazwisko)
        {
            znaleziono=1;
            for(int j=i; j<9; j++)
            {
                tab[j]=tab[j+1];
                tabObecnosc[j]=tabObecnosc[j+1];
            }
            tab[9].wyczysc();
            tabObecnosc[9] = false;
            return ;
        }
        
    }
    if(znaleziono==0)
    {
        cout << "Nie znaleziono osoby" << endl;
    }
}

void Edytuj(Osoba *tab, string nazwisko, string imie,  string indeks, int i)
{// fukcja do edytacjich poszczegolnych danych studenta (imie, nazwisko, indeks)
    tab[i].setImie(imie);
    tab[i].setNazwisko(nazwisko);
    tab[i].setIndeks(indeks);
}

//funkcja glowna z wyborem co zamierzamy zrobic w programie
int main() {
    Osoba studenci[10];
    bool tabObecnosc[10]={false};
    string nazwisko;
    string imie;
    string indeks;
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
                dodajOsobe(studenci, nazwisko, imie, indeks);
            break;
            case 2: // funkja zmieniajaca obecnosc 
            cout << "Podaj nazwisko" << endl;
                cin >> nazwisko;
                cout << "Podaj obecnosc" << endl;
                cin >> obecnosc;
                ustawObecnosc(studenci,tabObecnosc, nazwisko, obecnosc);
            break;
            case 3: //funkcja ukazujaca liste studentow na ekranie
            drukujListe(studenci, tabObecnosc);
            break;
            case 4: //funkcja usuwajaca studenta i zsuwajaca studentow 
            cout << "Podaj nazwisko student ktorego chcesz usunc" << endl;
            cin >> nazwisko;
            usun(studenci, tabObecnosc, nazwisko);
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
        if(studenci[i].getNazwisko() == nazwisko)
        {
            cout << "Co chcesz edytowac: nazwisko, imie, indeks " << endl;
            cin >> wyborDane;
            if(wyborDane == "nazwisko")
            {
          
            cout << "Podaj nazwisko:" << endl;
            cin >> nazwisko;
            indeks=studenci[i].getIndeks();
            imie=studenci[i].getImie();  
            }
            else if (wyborDane== "imie")
            {
                cout << "Podaj Imie:" << endl;
            cin >> imie;
            indeks = studenci[i].getIndeks();
            nazwisko = studenci[i].getNazwisko();
            }
            else if (wyborDane== "indeks")
            {
                  cout << "Podaj indeks:" << endl;
            cin >> indeks; 
            nazwisko=studenci[i].getNazwisko();
            imie=studenci[i].getImie();    
            }
            znaleziono=1;
            Edytuj(studenci, nazwisko,  imie,  indeks, i);
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

