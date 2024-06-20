/*
Hubert Kowalski
197811
ACiR 4 
*/

#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <time.h>
#include <cstring>
#include <iomanip> 

using namespace std;

struct dane_wykresy {
    int ilosc_linii = 0;
    int poz_pocz = 0;
    int dzien=0, miesiac=0, rok=0;
    double open=0, high=0, close=0, low=0, volume=0;
    double dane[5][16000] = {};

    char wykres[505][505] = {};
    char slupek=' ';

    double mini = 100000000, maxi = -1000000000;
    long double odcinki[5005] = {}, roznica=0;
    int x = 0;
    char odstep=' ';

    char tekst[100] = {};
};

//generator logow
void data_log(char tab[300])
{
    time_t currentTime = time(0);
    tm localTime;
    localtime_s(&localTime, &currentTime);
    char buffer[26];
    asctime_s(buffer, sizeof(buffer), &localTime);

    ofstream czas("Logi.log", ios_base::app);

    czas << "[ " << buffer << " ] -> ";
    czas << tab;
    czas << endl << endl;

    czas.close();

}

void czysc_strukture(dane_wykresy& w)
{
    w.ilosc_linii = 0;
    w.poz_pocz = 0;
    w.dzien = 0; w.miesiac = 0; w.rok = 0;
    w.roznica = 0;
    w.x = 0;
    w.mini = 100000000;
    w.maxi = -1000000000;
}

void powrot()
{
    char tab[300];
    strcpy_s(tab, "Zakończono dany podprogram");
    data_log(tab);
    cout << "Wpisz Q, aby wrocic do menu!" << endl;

    char znak;

    while (cin >> znak)
    {
        if (znak == 'q' || znak == 'Q')
        {
            break;
        }
        else
        {
            cout << "Podany znak jest nieprawidlowy! Sproboj ponownie..." << endl;
        }
    }
}

void max_min(dane_wykresy &w)
{
    if (w.high > w.maxi)
    {
        w.maxi = w.high;
    }
    if (w.high < w.mini)
    {
        w.mini = w.high;
    }
    if (w.low > w.maxi)
    {
        w.maxi = w.low;
    }
    if (w.low < w.mini)
    {
        w.mini = w.low;
    }
}

void slupki(dane_wykresy &w)
{
    if (w.open <= w.close)
    {
        w.dane[4][w.x] = 1;
    }
    else
    {
        w.dane[4][w.x] = 0;
    }
}

void przedzialy(dane_wykresy& w, double n)
{
    w.roznica = 1.0 * (w.maxi - w.mini) / n;
    for (int i = 0; i <= n; i++)
    {
        w.odcinki[i] = w.roznica * i;
    }
}

//generowanie słupków, dla podstawowego podprogramu
void generowanie_slupkow(dane_wykresy &w)
{
    if (w.dane[4][w.x] == 0)
    {
        w.slupek = '#';
    }
    else
    {
        w.slupek = 'O';
    }
    w.dane[0][w.x] -= w.mini;
    w.dane[1][w.x] -= w.mini;
    w.dane[2][w.x] -= w.mini;
    w.dane[3][w.x] -= w.mini;
}

//tablica słupków, dla podstawowego podprogramu
void sprawdzanie(dane_wykresy &w, int n){

    double pocz, kon;

    for (int j = 0; j < n; j++)
            {
        if (j > 50)
        {
            break;
        }
                pocz = w.odcinki[j];
                kon = w.odcinki[j + 1];
                //warunki na sprawdzenie przedziałów


                //cialo
                if ((pocz <= w.dane[0][w.x] && w.dane[0][w.x] <= kon) ||
                    (pocz >= w.dane[0][w.x] && kon <= w.dane[3][w.x] && pocz<=w.dane[3][w.x]) ||
                    (pocz <= w.dane[3][w.x] && w.dane[3][w.x] <= kon) ||
                    (pocz <= w.dane[0][w.x] && kon >= w.dane[3][w.x]))
                {
                    w.wykres[w.x][j] = w.slupek;
                }
                else
                {
                    if ((pocz <= w.dane[1][w.x] && w.dane[1][w.x] <= kon) ||
                        (pocz >= w.dane[1][w.x] && kon <= w.dane[2][w.x] && pocz <= w.dane[2][w.x]) ||
                        (pocz <= w.dane[2][w.x] && w.dane[2][w.x] <= kon) ||
                        (pocz <= w.dane[1][w.x] && kon >= w.dane[2][w.x]))
                    {
                        w.wykres[w.x][j] = '|';
                    }
                    else
                    {
                        w.wykres[w.x][j] = ' ';
                    }
                }

            }
}

void laczenie_slupkow(dane_wykresy &w, int pom)
{

    for (int i = 0; i < w.ilosc_linii-w.poz_pocz; i = i + pom)
    {
        for (int j = i; j < i + pom - 1; j++)
        {
            if (w.dane[4][j] == 0)
            {
                if (w.dane[4][j + 1] == 0)
                {
                    w.dane[0][j + 1] = w.dane[0][j];
                    w.dane[1][j + 1] = w.dane[1][j];
                    w.dane[2][j + 1] = w.dane[2][j + 1];
                    w.dane[3][j + 1] = w.dane[3][j + 1];
                    w.dane[4][j + 1] = 0;
                }
                else
                {
                    if (w.dane[0][j] < w.dane[3][j + 1]) //2 rysunek
                    {
                        w.dane[0][j + 1] = w.dane[0][j+1];
                        w.dane[1][j + 1] = w.dane[1][j + 1];
                        w.dane[2][j + 1] = w.dane[1][j];
                        w.dane[3][j + 1] = w.dane[3][j + 1];
                        w.dane[4][j + 1] = 1;
                    }
                    else
                    {
                        w.dane[0][j + 1] = w.dane[0][j];
                        w.dane[1][j + 1] = w.dane[1][j];
                        w.dane[2][j + 1] = w.dane[1][j + 1];
                        w.dane[3][j + 1] = w.dane[3][j ];
                        w.dane[4][j + 1] = 0;
                    }
                }
            }
            else if (w.dane[4][j] == 1)
            {
                if (w.dane[4][j + 1] == 0)
                {
                    if (w.dane[0][j] > w.dane[3][j + 1]) //1 rysunek
                    {
                        w.dane[0][j + 1] = w.dane[0][j+1];
                        w.dane[1][j + 1] = w.dane[2][j];
                        w.dane[2][j + 1] = w.dane[2][j + 1];
                        w.dane[3][j + 1] = w.dane[3][j + 1];
                        w.dane[4][j + 1] = 0;
                    }
                    else
                    {
                        w.dane[0][j + 1] = w.dane[0][j];
                        w.dane[1][j + 1] = w.dane[2][j + 1];
                        w.dane[2][j + 1] = w.dane[2][j];
                        w.dane[3][j + 1] = w.dane[3][j];
                        w.dane[4][j + 1] = 1;
                    }
                }
                else
                {
                    w.dane[0][j + 1] = w.dane[0][j];
                    w.dane[1][j + 1] = w.dane[1][j + 1];
                    w.dane[2][j + 1] = w.dane[2][j];
                    w.dane[3][j + 1] = w.dane[3][j + 1];
                    w.dane[4][j + 1] = 1;
                }
            }
        }
    }
}

void daty_wyznacz(char znaki[], dane_wykresy &w, int &czy, int &d1, int &d2, int &m1, int &m2, int &r1, int &r2)
{
    int czy1=0, czy2=0;
    char znak;
    
    cout << endl;
    cout << "Podaj daty w formacie: dzien.miesiac.rok (liczby oddzielone kropka)." << endl;
    cout << "Pamietaj, dana data musi istniec w podanym pliku wejsciowym, w przeciwnym przypadku" << endl;
    cout << "program sie nie wykona ( powiadomi o braku podanej daty )!!!" << endl << endl;

    cout << "Podaj date poczatkowa:" << endl;
    cin >> d1 >> znak >> m1 >> znak >> r1;
    cout << "Podaj date koncowa:" << endl;
    cin >> d2 >> znak >> m2 >> znak >> r2;



    ifstream wczytywanie(znaki);

    wczytywanie >> w.tekst;

    for (int i = 0; i <= w.ilosc_linii; i++)
    {
        wczytywanie >> w.rok >> w.odstep >> w.miesiac >> w.odstep >> w.dzien >> w.odstep;
        wczytywanie >> w.open >> w.odstep >> w.high >> w.odstep >> w.low >> w.odstep >> w.close >> w.odstep >> w.volume;

        if (w.rok == r1)
        {
            if (w.miesiac == m1)
            {
                if (w.dzien == d1)
                {
                    czy1 = 1;
                    w.poz_pocz = i+1;
                }
            }
        }
        if (w.rok == r2)
        {
            if (w.miesiac == m2)
            {
                if (w.dzien == d2)
                {
                    czy2 = 1;
                    w.ilosc_linii = i+1;
                    break;
                }
            }
        }
    }
    char tab[300];
    
    if (czy1 == 0)
    {
        strcpy_s(tab, "Data początkowa nie jest poprawna");
        data_log(tab);
    }
    if (czy2 == 0)
    {
        strcpy_s(tab, "Data końcowa nie jest poprawna");
        data_log(tab);
    }

    if (czy2 == 1 && czy1 == 1)
    {
        czy = 1;
    }
    else
    {
        czy = 0;
    }
}

void wypisz_kawalek(int &i_pom, int &dokad_wypisac, dane_wykresy &w, int &wysokosc, int &dokad)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int pocz, kon, zlicz=0;
    if (wysokosc > 50)
    {
        wysokosc = 50;
    }
    if (dokad > 100)
    {
        dokad = 100;
    }

    int wysoko = (int)wysokosc;
    for (int i = wysoko-1; i >=0; i--)
    {
        pocz = w.odcinki[i];
        kon = w.odcinki[i + 1];
        zlicz = 0;
        for (int j = i_pom - 1; j < dokad_wypisac * i_pom + 1; j = j + i_pom)
        {
            if (w.dane[4][j] == 0)
            {
                SetConsoleTextAttribute(hConsole, 12);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 10);
            }

            zlicz += 1;
            if (zlicz >= dokad)
            {
                break;
            }
            w.x = j;
            //cialo
            if ((pocz <= w.dane[0][w.x] && w.dane[0][w.x] <= kon) ||
                (pocz >= w.dane[0][w.x] && kon <= w.dane[3][w.x] && pocz <= w.dane[3][w.x]) ||
                (pocz <= w.dane[3][w.x] && w.dane[3][w.x] <= kon) ||
                (pocz <= w.dane[0][w.x] && kon >= w.dane[3][w.x]))
            {
                if (w.dane[4][w.x] == 0)
                {
                    w.slupek = '#';
                }
                else
                {
                    w.slupek = 'O';
                }
                cout << w.slupek;
            }
            else
            {
                if ((pocz <= w.dane[1][w.x] && w.dane[1][w.x] <= kon) ||
                    (pocz >= w.dane[1][w.x] && kon <= w.dane[2][w.x] && pocz <= w.dane[2][w.x]) ||
                    (pocz <= w.dane[2][w.x] && w.dane[2][w.x] <= kon) ||
                    (pocz <= w.dane[1][w.x] && kon >= w.dane[2][w.x]))
                {
                    cout << '|';
                }
                else
                {
                    cout << ' ';
                }
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void rysuj_osie(dane_wykresy &w, int szerokosc, int wysokosc, int dokad_wypisac, int i_pom, char plik_zapis[], int d1, int d2, int m1, int m2, int r1, int r2)
{
    ofstream wypisz(plik_zapis);
    int pocz, kon;

    wypisz << "Wykres świec japońskich!" << endl << endl;

    wypisz.width(8);
    wypisz << "Ceny akcji" << endl;

    wypisz.width(9);
    wypisz << '^' << endl;

    int wysoko = (int)wysokosc;

    for (int i = wysoko - 1; i >= 0; i--)
    {
        wypisz.width(8);
        wypisz << fixed << setprecision(3) << w.odcinki[i];

        wypisz << "|";

        pocz = w.odcinki[i];
        kon = w.odcinki[i+1];
        //warunki na sprawdzenie przedziałów

        for (int j = i_pom - 1; j < dokad_wypisac*i_pom + 1; j = j + i_pom)
        {
            w.x = j;
            //cialo
            if ((pocz <= w.dane[0][w.x] && w.dane[0][w.x] <= kon) ||
                (pocz >= w.dane[0][w.x] && kon <= w.dane[3][w.x] && pocz <= w.dane[3][w.x]) ||
                (pocz <= w.dane[3][w.x] && w.dane[3][w.x] <= kon) ||
                (pocz <= w.dane[0][w.x] && kon >= w.dane[3][w.x]))
            {
                if(w.dane[4][w.x] == 0)
                {
                    w.slupek = '#';
                }
                else
                {
                    w.slupek = 'O';
                }
                wypisz << w.slupek;
            }
            else
            {
                if ((pocz <= w.dane[1][w.x] && w.dane[1][w.x] <= kon) ||
                    (pocz >= w.dane[1][w.x] && kon <= w.dane[2][w.x] && pocz <= w.dane[2][w.x]) ||
                    (pocz <= w.dane[2][w.x] && w.dane[2][w.x] <= kon) ||
                    (pocz <= w.dane[1][w.x] && kon >= w.dane[2][w.x]))
                {
                    wypisz << '|';
                }
                else
                {
                    wypisz << ' ';
                }
            }
        }

        wypisz << endl;
    }

    wypisz << d1 << '.' << m1 << '.' << r1;
    
    for(int j = 0; j < dokad_wypisac; j++)
    {
        wypisz << '-';
    }
    wypisz << '>' << d2 << '.' << m2 << '.' << r2 << endl << endl;

    wypisz << "Podany przedział czasowy to: ";
    if (i_pom == 1)
    {
        wypisz << "1 dzień";
    }
    if (i_pom == 5)
    {
        wypisz << "1 tydzień";
    }
    if (i_pom == 20)
    {
        wypisz << "1 miesiąc";
    }
    wypisz.close();
}

void podstawowy()
{
    char tab[300];

    strcpy_s(tab, "Uruchomiono podstawowy program");

    data_log(tab);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Program do generowania swiec japonskich!" << endl << endl;
    cout << "Hubert Kowalski 197811 ACiR_4" << endl << endl;
    cout << "#####################################" << endl;

    ifstream wczytywanie("intc_us_data.csv");
    ofstream zapis("chart.txt");
    dane_wykresy w;
    czysc_strukture(w);


    if (wczytywanie.is_open())
    {
        strcpy_s(tab, "Poprawnie wczytano plik intc_us_data.csv");
        data_log(tab);

        while (wczytywanie.getline(w.tekst, 100))
        {
            w.ilosc_linii += 1;
        }

        wczytywanie.close();

        ifstream wczyt("intc_us_data.csv");
        
        if (w.ilosc_linii <= 200)
        {
            w.poz_pocz = 0;
            wczyt >> w.tekst;
        }
        else
        {
            w.poz_pocz = w.ilosc_linii - 200;
        }

        strcpy_s(tab, "Wczytano ilość linii");
        data_log(tab);

        for (int i = 0; i < w.ilosc_linii; i++)
        {
            if (i >= w.poz_pocz)
            {
                wczyt >> w.rok >> w.odstep >> w.miesiac >> w.odstep >> w.dzien >> w.odstep;
                wczyt >> w.open >> w.odstep >> w.high >> w.odstep >> w.low >> w.odstep >> w.close >> w.odstep >> w.volume;
                w.dane[0][w.x] = w.open;
                w.dane[1][w.x] = w.high;
                w.dane[2][w.x] = w.low;
                w.dane[3][w.x] = w.close;

                max_min(w);

                slupki(w);

                w.x++;
            }
            else
            {
                wczyt >> w.tekst;
            }
        }

        strcpy_s(tab, "Wczytano dane z pliku wejsciowego");
        data_log(tab);

        wczyt.close();
        przedzialy(w, 50);

        w.x = 0;

        for (int i = w.poz_pocz; i < w.ilosc_linii; i++)
        {
            generowanie_slupkow(w);
            sprawdzanie(w, 50);

            w.x++;
        }

        strcpy_s(tab, "Wygenerowano świece");
        data_log(tab);

        cout << "Wykres (jego kawalek) o rozmiarach 50x100: " << endl;
        for (int i = 49; i >= 0; i--)
        {
            for (int j = 0; j < 200; j++)
            {
                if (w.dane[4][j] == 0)
                {
                    SetConsoleTextAttribute(hConsole, 12);
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 10);
                }

                if (j < 100 && i < 50)
                {
                    cout << w.wykres[j][i];
                }
                zapis << w.wykres[j][i];
            }
                cout << endl;
            zapis << endl;
        }
        SetConsoleTextAttribute(hConsole, 15);

        cout << endl << "Pelny wykres japonskich swiec wygenerowano w pliku chart.txt!!!" << endl;
        zapis.close();

        strcpy_s(tab, "Wypisano w konsoli kawałek wykresu, a pełen wykres wygenerowano w pliku chart.txt");
        data_log(tab);

        powrot();
    }
    else
    {
        strcpy_s(tab, "Nie udało się otworzyć pliku intc_us_data.csv");
        data_log(tab);
        cout << "Nie udalo sie odtworzyc pliku intc_us_data.csv." << endl << "Sprawdz czy plik znajduje sie w poprawnej lokalizacji!" << endl << endl;
        powrot();
    }
}

void zaawansowany()
{
    char tab[300];
    strcpy_s(tab, "Uruchomiono zaawansowany program");
    data_log(tab);

    int dokad = 200;
    int dokad_wypisac=200;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Program do generowania swiec japonskich!" << endl << endl;
    cout << "Hubert Kowalski 197811 ACiR_4" << endl << endl;
    cout << "#####################################" << endl;

    char plik_odczyt[100] = {};
    char plik_zapis[100] = {};

    strcpy_s(tab, "Oczekiwanie na podanie nazwy pliku wejsciowego");
    data_log(tab);

    cout << "Wpisz nazwe pliku wejsciowego: " << endl;
    cin >> plik_odczyt;

    strcpy_s(tab, plik_odczyt);
    data_log(tab);

    ifstream wczytywanie(plik_odczyt);
    dane_wykresy w;
    czysc_strukture(w);

    if (wczytywanie.is_open())
    {
        strcpy_s(tab, "Znaleziono podany plik wejściowy");
        data_log(tab);

        int szerokosc;

        strcpy_s(tab, "Oczekiwanie na podanie nazwy pliku wyjściowego");
        data_log(tab);

        cout << "Wpisz nazwe pliku wyjsciowego: " << endl;
        cin >> plik_zapis;

        strcpy_s(tab, plik_zapis);
        data_log(tab);

        ofstream zapis(plik_zapis);

        cout << "Podaj wysokosc wykresu: " << endl;

        int wysokosc;
        cin >> wysokosc;

        strcpy_s(tab, "Podano wysokość wykresu");
        data_log(tab);

        cout << "Podaj szerokosc wykresu: " << endl;
        cout << "1. 1 dzien" << endl;
        cout << "2. 1 tydzien" << endl;
        cout << "3. 1 miesiac" << endl;

        while (cin >> szerokosc)
        {
            if (szerokosc >= 1 && szerokosc <= 3)
            {
                break;
            }
            else
            {
                cout << "Podana liczba jest nieprawidlowa! Sproboj ponownie:" << endl;
            }
        }

        strcpy_s(tab, "Podano szerokość wykresu");
        data_log(tab);


        while (wczytywanie.getline(w.tekst, 100))
        {
            w.ilosc_linii += 1;
        }

        wczytywanie.close();
        int czy = 0;

        ifstream wczyt(plik_odczyt);

        int d1, d2, m1, m2, r1, r2;

        daty_wyznacz(plik_odczyt, w, czy,d1,d2,m1,m2,r1,r2);
        strcpy_s(tab, "Wczytano przedział datowy");
        data_log(tab);

        if (czy == 0)
        {
            strcpy_s(tab, "Podane daty są nieprawidłowe: data początkowa jest mniejsza od końcowej, lub jedna z dat nie istnieje");
            data_log(tab);
            return;
        }

        strcpy_s(tab, "Podane daty są prawidłowe");
        data_log(tab);

        int i_pom = 1;

        for (int i = 0; i <= w.ilosc_linii; i++)
        {
            if (i >= w.poz_pocz)
            {
                    wczyt >> w.rok >> w.odstep >> w.miesiac >> w.odstep >> w.dzien >> w.odstep;
                    wczyt >> w.open >> w.odstep >> w.high >> w.odstep >> w.low >> w.odstep >> w.close >> w.odstep >> w.volume;
                    w.dane[0][w.x] = w.open;
                    w.dane[1][w.x] = w.high;
                    w.dane[2][w.x] = w.low;
                    w.dane[3][w.x] = w.close;

                    max_min(w);

                    slupki(w);

                    w.x++;
            }
            else
            {
                wczyt >> w.tekst;
            }
        }

        
        strcpy_s(tab, "Wczytano dane z pliku wejsciowego");
        data_log(tab);

        i_pom = 1;
        dokad_wypisac = w.ilosc_linii - w.poz_pocz;
        if (szerokosc == 2)
        {
            laczenie_slupkow(w, 5);
            i_pom = 5;
        }
        if (szerokosc == 3)
        {
            laczenie_slupkow(w, 20);
            i_pom = 20;
        }

        if (szerokosc != 1)
        {
            strcpy_s(tab, "Łączenie słupków");
            data_log(tab);
        }
        dokad_wypisac /= i_pom;

        
        wczyt.close();
        przedzialy(w,wysokosc);

        w.x = i_pom-1;
        int do_50=0;
        int do_100=0;
        for (int i = w.poz_pocz+i_pom-1; i < w.ilosc_linii; i=i+i_pom)
        {
            generowanie_slupkow(w);
            w.x=w.x+i_pom;
        }

        strcpy_s(tab, "Wygenerowano  świece");
        data_log(tab);

        dokad = dokad_wypisac;

        if (wysokosc > 50)
        {
            if (dokad >= 100)
            {
                cout << "Wykres (jego kawalek) o rozmiarach 50x100: " << endl;
            }
            else
            {
                cout << "Wykres (jego kawalek) o rozmiarach 50x"<< dokad <<": " << endl;
            }
        }
        else
        {
            if (dokad >= 100)
            {
                cout << "Wykres (jego kawalek) o rozmiarach " << wysokosc << "x100:" << endl;
            }
            else
            {
                cout << "Wykres (jego kawalek) o rozmiarach " << wysokosc << "x" << dokad << ": " << endl;
            }
        }
        dokad_wypisac -= i_pom;
        SetConsoleTextAttribute(hConsole, 15);
        
        rysuj_osie(w, dokad, wysokosc, dokad_wypisac, i_pom, plik_zapis, d1,d2,m1,m2,r1,r2);
        wypisz_kawalek(i_pom, dokad_wypisac, w, wysokosc, dokad);

        SetConsoleTextAttribute(hConsole, 15);

        zapis.close();

        strcpy_s(tab, "Wypisano w konsoli kawałek wykresu, a pełen wykres wygenerowano w pliku wyjściowym");
        data_log(tab);

        cout << endl << "Pelny wykres japonskich swiec wygenerowano w pliku: " << plik_zapis <<"!!!" << endl;
        powrot();
    }
    
    else
    {
        strcpy_s(tab, "Nie znaleziono podanego pliku wejściowego");
        data_log(tab);
        cout << "Nie udalo sie odtworzyc pliku: " << plik_odczyt << endl << "Sprawdz czy plik znajduje sie w poprawnej lokalizacji!" << endl << endl;
        powrot();
    }
}

void menu(){
    
    char tab[300];
    strcpy_s(tab, "Uruchomiono menu");
    data_log(tab);
    system("cls");

    cout << "Program do generowania swiec japonskich! " << endl << "Aby program dzialal prawidlowo prosze zmienic rozmiar czcionki w konsoli na max. 8!" << endl;
    cout << "Wszystkie informacje (dla czesci funkcjonalnej) znajduja sie w logach!" << endl << endl;
    cout << "Hubert Kowalski 197811 ACiR_4" << endl << endl;
    cout << "#####################################" << endl;
    cout << "Wybierz dany tryb:" << endl;
    cout << "1. Podstawowy program" << endl;
    cout << "2. Funkcjonalny program" << endl;
    cout << "3. Wyjdz z programu" << endl;

    char znak;
    while (cin >> znak)
    {
        if (znak == '1')
        {
            system("cls");
            podstawowy();
            break;
        }
        else if (znak == '2')
        {
            system("cls");
            zaawansowany();
            break;
        }
        else if (znak == '3')
        {
            strcpy_s(tab, "Program został wyłączony");
            data_log(tab);

            system("cls");
            exit(0);
        }
        else {
            cout << "Podany znak jest nieprawidlowy! Wpisz jeszcze raz:" << endl;
            strcpy_s(tab, "Podano nieprawidłowy znak w menu");
            data_log(tab);
        }
    }
}


int main()
{
    time_t currentTime = time(0);
    tm localTime;
    localtime_s(&localTime, &currentTime);
    char buffer[26];
    asctime_s(buffer, sizeof(buffer), &localTime);

    ofstream czas("Logi.log");
    czas << "[ " << buffer << " ] -> Uruchomiono program" << endl << endl;
    czas.close();

    while (true)
    {
        menu();
    }

    return 0;
}
