# OpenGL-Solar-System
Model Układu Słonecznego  
C++ i OpenGL  
Grafika Komputerowa, 2016/2017  
Autorzy: Mikołaj Balcerek, Rafał Piotrowski  

![Obraz z aplikacji](http://i.imgur.com/LTxwDTC.png)
[gifv z działającej aplikacji](http://i.imgur.com/OA8eeXt.gifv)


## Funkcjonalności i rozdział ról

- **Planety obracają się wokół własnej osi** (Mikołaj Balcerek, Rafał Piotrowski)  
  *Macierze planet są przemnożone przez macierz rotacji zależnej od czasu   (cos, sin, -sin, cos)*
- **Planety krążą dookoła Słońca** (Mikołaj Balcerek, Rafał Piotrowski)  
*Planety obracane są wokół punktu 0,0,0 za pomocą macierzy translacji   (zachowany luźny stosunek pomiędzy promieniem a prędkością obrotu by symulować prawa Keplera)*
- **Strzelanie wieloma pociskami - naciśnij F** (Mikołaj Balcerek)  
*Mechanizm zaczerpnięty z poruszania statkiem zapamiętuje pozycję, kierunek statku oraz czas w momencie wystrzelenia i w renderscene oblicza obecną pozycję pocisków*
- **Światło punktowe pochodzące ze Słońca** (Rafał Piotrowski)  
*Zmodyfikowany shader_tex.frag*
- **Księżyc dodatkowo krąży dookoła Ziemi** (Mikołaj Balcerek)  
*Macierz translacji Księżyca jest przemnożona przez finalą macierz Ziemi*
- Osiem planet Układu Słonecznego i Słońce (Rafał Piotrowski)  
- Słońce jest w całości oświetlone osobnym shaderem (Mikołaj Balcerek, Rafał Piotrowski)  
*Nowe shader_tex_sun, funkcja drawObjectTextureSun*
- Oteksturowany statek (Mikołaj Balcerek)  
*funkcja drawObjectTextureShip*
- Przyczepienie "działa" do statku i wycentrowanie pocisków (Rafał Piotrowski)
- Otaczająca Układ tekstura kosmosu (Mikołaj Balcerek)
- Tryb turbo, szybszego poruszania się statku - naciśnij T, koniec Y (Rafał Piotrowski)
- Rozmiary okna, tła, komentarze (Mikołaj Balcerek)
- Dokumentacja, prezentacja (Mikołaj Balcerek)

#### Sterowanie
- W,S,A,D - poruszanie się przód, tył, lewo, prawo
- Z,X - obracanie się
- F - strzelanie
- T - tryb turbo (szybsze poruszanie się statkiem)

#### Wymagania, TODO:  
Link do szczegółowych wymagań: https://docs.google.com/document/d/1mKzDltdg2EMLVJQcnu4zgKQBtTep7SUKCytHB9KLQ4M/edit?usp=sharing  
• Przygotować 5 minutową prezentację projektu na ostatnich ćwiczeń -  
przygotować się na kilka pytań  
• Implementacja (50%), opis i prezentacja (50%)  

Wybrać jakiś dodatkowy efekt graficzny, np.:  
• Normal lub Environment mapping  
• Proceduralne tekstury: np. szum Perlina  
• Statek ma obracającą bron (strzela)  
• Kolizja obiektów jest obsługiwana  
• Ciekawa scena, np. lot przez asteroidy  


 
