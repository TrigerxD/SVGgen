# SVGgen

Projekt obejmuje zaprojektowanie oraz zaprogramowanie w języku C++ aplikacji operującej z WinAPI do generowania pliów SVG kompatybilnej z wyświetlaniem obrazów oraz odczytywaniem ich opisów przez sytezator mowy w systemie Android.

# Sposób postepowania z projektem

Uzupełnianie pliku Readme.md - użyjemy go jako raportu końcowego projektu :D

<b>6.1.2020</b>
1. Wprowadzenie poprawnej nazwy pliku (nazwa musi zaczynac się od a-z lub A-Z oraz zawierać tylko znaki alfanumerczyne)
2. Wciśnięcie przycisku Generate (komunikat o poprawności nazwy pliku zostanie wyswietlony w okienku nazwy pliku)
3. Wynik generacji (czerwone kółko) znajduje się w lokalizacji Results

# Wyglad pliku
```xml
<?xml version="1.0" standalone="no"?>
<!DOCTYPE svg PUBLIC " -//W3C//DTD SVG 1.1//EN"
"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">

<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
<circle cx="100" cy="100" r="50" fill="red" /> - figura rysowana
</svg>

<description text="Enter description here"/> - opis figury
```
# Wymagania projektowe

1. User friendly UI
  - możliwość wyboru generowanej figury lub funkcji
  - możliwość dodania opisu do wygenerowanego obrazu, który odczytany będzie przez syntezator mowy w systemie android
2. Generowanie obiektów typu Figure takich jak kwadrat, szesciokąt foremny, gwiazda oraz obiektów typu Chart takich jak funkcja liniowa, kwadratowa, sinusoidalna
  generacja:
    -	wykres
    -	linia (os ukladu wspolrzednych)
    -	kolo
    -	kwadrat
    -	trojkat (rownoboczny, rownoramienny, prostokatny)
    -	prostokat 
    -	trapez (prostokatny, rownoramienny)
    -	romb
    -	rownoleglobok
    -	gwiazda (6-sioramienna)
    -	szeciokat (n-kat max n =10) - foremne

3. (opcjonalnie) możliwość podglądu generowanego obrazu

# Pomocne linki

http://webmaster.helion.pl/index.php/svgbudowa

# Importowanie projektu

W razie problemów w file explorer (Visual Studio) SVGgen -> Proporties:
  1. Configuration properties -> General -> Character set -> Use Multi-Byte Character Set
  2. C/C++ -> General -> SDL checks -> NO
  3. C/C++ -> Code generation -> Security Check -> Disable Security Check
  4. Linker -> System -> Subsystem -> Windows

# Changelog

  - dodanie user UI - UI branch - Jarek
  - dodanie guzika generate i kontrolki do wprowadzania nazwy pliku (wraz ze sprawdzaniem nazwy pliku) - UI branch - Jarek
  - generowanie czerwonego kółka - Generator branch - Jarek
  - generowanie opisu do figury, dodano okno do wpisania opisu - generateDescription branch - Jarek
  - dodanie combobox do UI - generateDescription, Generator branch - Jarek
  - możliwość generowania zdefiniowanych przez użytkownika figur (parametry) - Generator branch - Jarek
  - generowanie kwadratu, prostokąta, trójkąta równobocznego i równoramiennego - Generator branch - Bartek
  
# TODO:
1. Rozszerzenie pola opisu do opisywania poszczególnych składowych parametrów rysowanej figury/wykresu (min 3) -> Bartek
2. Rozdzielczość każdego obrazu - full HD 1920x1080
3. Linie rysować jako małe prostokąty, pomijać kolory oraz <b>wypełnienie</b> - figury -> Bartek
4. Dodać wykresy - parametry: -> Jarek (przykladowy wykres)
    - wzór - np. sin(2x), cos(x/2), x^2+2*x+1, 2x+2, (⅓)x - 3, 1/x
    - przedział - od do : <3,4) ; (5,6) ; <1, 100> ; (,)
    - zbiór - domyślne liczby rzeczywiste (możliwość wybrania całkowitych, naturalnych)

