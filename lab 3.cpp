#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Osoba {
private:  //priwatne dane classy osoba (imie, nazwisko, indeks)
    string imie;
    string nazwisko;
    string indeks;

    bool czyPoprawne(string tekst) { //funkacja sprawdza czy imie lub nazwisko posiada minimum 2 listery oraz nie posiada znaków z poza alfabetu
        int licznikLiter = 0;
        for (char c : tekst) {
            if (!isalpha(static_cast<unsigned char>(c))) {
                return false; 
            }
            licznikLiter++;
        }
        return licznikLiter >= 2;
    }

    bool czyCyfry(string tekst) {  //osobna funkcja od sprawdzania czy indeks posiada tylko cyfry
        if (tekst.empty()) return false;
        for (char c : tekst) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                return false; 
            }
        }
        return true;
    }

public: //publiczny dostep do funkcji zmieniających wartosci w klasie
    Osoba() : imie(""), nazwisko(""), indeks("") {} // czysci miejce pod tabelke

    void setImie(string _imie) { 
        if(czyPoprawne(_imie)) { imie = _imie; } 
        else { cout << "Bledne imie, musi posiadac minimum 2 litery bez znakow specjalnych" << endl; }
    }
    string getImie() { return imie; }

    void setNazwisko(string _nazwisko) {
        if(czyPoprawne(_nazwisko)) { nazwisko = _nazwisko; }
        else { cout << "Bledne nazwisko, musi posiadac minimum 2 litery oraz bez znakow specjalnych" << endl; }
    }
    string getNazwisko() { return nazwisko; }

    void setIndeks(string _indeks) {
        if(czyCyfry(_indeks)) { indeks = _indeks; }
        else { cout << "bledny indeks, powinien zawierac same cyfry" << endl; } 
    }
    string getIndeks() { return indeks; }

    bool isEmpty() { return imie.empty(); }
    void wyczysc() { imie = ""; nazwisko = ""; indeks = ""; }
};

// class ListaObecnosci ma prywatne dane o studentach oraz ich obesnosci oraz fukcje do operacji na danych studentuw
class ListaObecnosci { 
private:
    Osoba tab[10];
    bool obecnosc[10];

public:
    ListaObecnosci() {
        for(int i = 0; i < 10; i++) {
            obecnosc[i] = false;
        }
    }


    //funkcja dodajaca osoba jezeli spelnia warunki i tablica nie jest pelna
    void dodajOsobe(string nazwisko, string imie, string indeks) {

        bool miejsce = 0;
        for(int i = 0; i < 10; i++) {
            if (tab[i].isEmpty()) {
                miejsce = 1;
                tab[i].setImie(imie);
                tab[i].setNazwisko(nazwisko);
                tab[i].setIndeks(indeks);
                if(tab[i].getImie() == "" || tab[i].getNazwisko() == "" || tab[i].getIndeks() == "") {
                    tab[i].wyczysc();
                }
                break;
            }
        }
        if(miejsce == 0) {
            cout << "Lista jest pelna, nie mozna dodac wiecej osob." << endl;
        }
    }

    //funkcja wyswietla tablice konkretnej listy 
    void drukujListe() {
        for(int i = 0; i < 10; i++) {

            if(!tab[i].isEmpty()) {
                cout << tab[i].getImie() << " " << tab[i].getNazwisko() << "  " << tab[i].getIndeks() << " " << obecnosc[i]  << endl;
            }
            else{break;}
        }
      
    }

    //funkcja pozwala wybrac czy student jest obecny czy nie
    void ustawObecnosc(string nazwisko, bool stanObecnosci) {
        bool znaleziono = 0;
        for(int i = 0; i < 10; i++) {
            if(tab[i].getNazwisko() == nazwisko) {
                obecnosc[i] = stanObecnosci;
                znaleziono = 1;
                break;
            }
        }
        if(znaleziono == 0) {
            cout << "Nie znaleziono osoby" << endl;
        }
    }

    //funkcja usuwa wybranego studenta oraz przesuwa pozostalych by nie zostawic pustego miejsca w tabeli
    void usun(string nazwisko) {
        bool znaleziono = 0;
        for(int i = 0; i < 10; i++) {
            if(tab[i].getNazwisko() == nazwisko) {
                znaleziono = 1;
                for(int j = i; j < 9; j++) {
                    tab[j] = tab[j+1];
                    obecnosc[j] = obecnosc[j+1];
                }
                tab[9].wyczysc();
                obecnosc[9] = false;
                cout << "Student zostal usuniety." << endl;
                return;
            }
        }
        if(znaleziono == 0) {
            cout << "Nie znaleziono osoby" << endl;
        }
    }

    //fukcja do edytacjich poszczegolnych danych studenta (imie, nazwisko, indeks)

    void edytuj(string nazwisko, string imie, string indeks, int i) {
         
            tab[i].setImie(imie);
            tab[i].setNazwisko(nazwisko);
            tab[i].setIndeks(indeks);
        
    }

    Osoba& getOsoba(int i) { return tab[i]; } 
};

// class interface - zawiera menu z funkcjami do dzialania na listach 
class Interfejs {
    //prywatne dane classy: wskazniki na listy uczniuw i inne dane
private:
    ListaObecnosci* analiza1;      
    ListaObecnosci* ppo1;         
    ListaObecnosci* listaAktywna;  
    string nazwaAktywnejListy;    
    Osoba* studenci;               

    //publiczne funkcje do dzialania na listach i danych 
public:
    Interfejs() { //funkcja rezerwujaca pamiec pod classy oraz tabele
        analiza1 = new ListaObecnosci();
        ppo1 = new ListaObecnosci();
        listaAktywna = analiza1;    // Domyślnie wybrana lista jest analiza 1
        nazwaAktywnejListy = "Analiza 1";
        studenci = new Osoba[10];
    }

    ~Interfejs() {    //destruktor opruzniajacy pamiec wykorzystana na classy i tabele
        delete analiza1;
        delete ppo1;
        delete[] studenci;
    }

    //dluga funkcja z menu i petla operujaca programem
    void uruchom() { 
        string nazwisko, imie, indeks;
        bool obecnosc;
        int wybor;

        do {
           //MENU z wyborem jakie czynnosci chcemy wykonac w programie
            cout << "____________ "<<"Aktualna lista"<<" " <<nazwaAktywnejListy  <<" ________________" << endl;
            cout << "napisz 0. aby zamknac program" << endl;
            cout << "napisz 1. aby dodac osobe" << endl;
            cout << "napisz 2. aby ustawic obecnosc" << endl;
            cout << "napisz 3. aby wypisac liste" << endl;
            cout << "napisz 4. aby usunac studenta z listy" << endl;
            cout << "napisz 5. aby wybrac edytowac dane konkretnego studenta" << endl;
            cout << "napisz 6. aby Zmienic liste uczniuw " << endl;
            cout << "napisz 7. aby Wypisac Studentów z obu list" << endl;
            cout << "Wybor: ";

            cin >> wybor;
            cout<< endl;
            //funkcja switch zajmujaca sie wyborem dzialan
            switch (wybor) {
                case 1: // dodawanie osoby
                    cout << "Podaj nazwisko:" << endl;
                    cin >> nazwisko;
                    cout << "Podaj Imie:" << endl;
                    cin >> imie;
                    cout << "Podaj Indeks:" << endl;
                    cin >> indeks;
                    listaAktywna->dodajOsobe(nazwisko, imie, indeks);
                    break;

                case 2: //zmiana obecnosci
                    cout << "Podaj nazwisko:" << endl;
                    cin >> nazwisko;
                    cout << "Podaj obecnosc tylko 1 albo 0" << endl;
                    cin >> obecnosc;
                    listaAktywna->ustawObecnosc(nazwisko, obecnosc);
                    break;

                case 3: // wyswietlanie aktywnej listy
                    cout << "--- Studenci na przedmiocie " << nazwaAktywnejListy << " ---" << endl;
                    listaAktywna->drukujListe();
                    break;

                case 4: // usuwanie wybranego studenta z listy
                    cout << "Podaj nazwisko studenta do usuniecia:" << endl;
                    cin >> nazwisko;
                    listaAktywna->usun(nazwisko);
                    break;

                case 5: { // edytowanie danych studenta
                    cout << "Wybierz studenta do edycji po nazwisku:" << endl;
                    cin >> nazwisko;
                    string wyborDane = " ";
                    bool znaleziono = false;

                    for(int i = 0; i < 10; i++) {
                        if(listaAktywna->getOsoba(i).getNazwisko() == nazwisko) {
                            cout << "Co chcesz edytowac? (nazwisko,  imie, indeks): " << endl;
                            cin >> wyborDane;
                            
                            imie = listaAktywna->getOsoba(i).getImie();
                            nazwisko = listaAktywna->getOsoba(i).getNazwisko();
                            indeks = listaAktywna->getOsoba(i).getIndeks();

                            if(wyborDane == "nazwisko") {
                                cout << "Podaj nowe nazwisko:" << endl;
                                cin >> nazwisko;
                            } else if (wyborDane == "imie") {
                                cout << "Podaj nowe Imie:" << endl;
                                cin >> imie;
                            } else if (wyborDane == "indeks") {
                                cout << "Podaj nowy indeks:" << endl;
                                cin >> indeks; 
                            }
                            
                            znaleziono = true;
                            listaAktywna->edytuj(nazwisko, imie, indeks, i);
                            cout << "Dane zostaly zaktualizowane." << endl;
                            break;
                        }
                    }
                    if(!znaleziono) {
                        cout << "Nie znaleziono osoby o tym nazwisku." << endl;
                    }
                    break;
                }

                case 6: { // zmiana listy przedmiotu
                    int opcjaPrzedmiotu;
                    cout << "Wybierz przedmiot: "<< endl << " 1. Analiza 1 " << endl << " 2. PPO 1 " << endl << "Twoj wybor: ";
                    cin >> opcjaPrzedmiotu;
                    if(opcjaPrzedmiotu == 1) {
                        listaAktywna = analiza1;
                        nazwaAktywnejListy = "Analiza 1";
                    } else if(opcjaPrzedmiotu == 2) {
                        listaAktywna = ppo1;
                        nazwaAktywnejListy = "PPO 1";
                    } else {
                        cout << "Bledny wybor, nie zmieniono przedmiotu." << endl;
                    }
                    break;
                }

                case 7: //lista wszystkich studentuw podzielona na przedmioty
                    cout << " LISTA WSZYSTKICH STUDENTUW:" << endl;
                    cout << "==========================================" << endl;
                    cout << " Analiza 1:" << endl;
                    analiza1->drukujListe();
                    
                    cout << "===========================================" << endl;
                    cout << " PPO 1:" << endl;
                    ppo1->drukujListe();
                    break;

                case 0: // zamykanie programu
                    cout << "Zamykanie programu..." << endl;
                    break;

                default:
                    cout << "Nieznany wybor!" << endl;
                    break;
            }
        } while (wybor != 0);
    }
};

int main() { // glowna funkcja 
    Interfejs program; // tworzy classe interfejs
    program.uruchom();  // zaczyna petle z funkcjami
    return 0;
}