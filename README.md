# SVGgen

Projekt obejmuje zaprojektowanie oraz zaprogramowanie w języku C++ aplikacji operującej z WinAPI do generowania pliów SVG kompatybilnej z wyświetlaniem obrazów oraz odczytywaniem ich opisów przez sytezator mowy w systemie Android.

# Sposób postepowania z projektem

Uzupełnianie pliku Readme.md - użyjemy go jako raportu końcowego projektu :D

<b>6.1.2020</b>
1. Wprowadzenie poprawnej nazwy pliku (nazwa musi zaczynac się od a-z lub A-Z oraz zawierać tylko znaki alfanumerczyne)
2. Wciśnięcie przycisku Generate (komunikat o poprawności nazwy pliku zostanie wyswietlony w okienku nazwy pliku)

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
  - dodanie guzika generate i kontrolki do wprowadzania nazwy pliku (wraz ze sprawdzaniem nazwy pliku) - Jarek
