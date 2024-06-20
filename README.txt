**********************************************
Generator świec japońskich
**********************************************

Program składa się z funkcjonalności podstawowej, oraz zaawansowanej.

**********************************************

Program powinien posiadać następujące podstawowe funkcjonalności z domyślnymi
wartościami:

1. Powitanie, menu programu:
a. kończenie program, inne opcje nie kończą programu.
b. pobiera dane z pliku intc_us_data.csv, generuje wykres i zapisuje do
pliku chart.txt

2. Ciało białej świecy to “O”, ciało czarnej świecy to “#” a cień świecy to “|”.
3. Domyślny zakres reprezentowany przez jedną świecę to jeden dzień
4. Domyślna wysokość wygenerowanego wykresu to 50 znaków.
5. Domyślny zakres dat do przetworzenia to ostatnie 200 odczytów.

**********************************************

Funkcjonalności zaawansowane:
1. Możliwość wyboru pliku wejściowego i wyjściowego z poziomu menu.
2. Możliwość wyboru wysokości wykresu

3. Możliwość wyboru szerokości wykresu:
Całkowita szerokość wykresu jest zależna od zakresu czasowego reprezentowanego
przez jedną świecę (jeden dzień, jeden tydzień albo jeden miesiąc) i zakresu
czasowego obejmowanego przez cały wykres.

4. Wybór zakresu czasowego pokrytego przez jedną świecę (grupowanie)
i. jedna świeca = jeden tydzień
ii. jedna świeca = jeden miesiąc

5. Wybór zakresu dat do przetworzenia - możliwość zmiany początku i
końcu zakresu
6. Podpisane osie wykresu wraz z podziałką i skrajnymi wartościami
7. Wyświetlenie kawałka wykresu na konsoli
8. Utworzenie pliku .log, w którym będą zapisane wszystkie akcje użytkownika
wraz z czasem ich wystąpienia.