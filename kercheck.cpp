#include <iostream>

using namespace std;

const int n = 8;				//sta�a ilo�� wierszy w tablicy
const int m = 8;				//sta�a ilo�� kolumn w tablicy

//funkcja przypisuje odpowiednim polom w tablicy odpowiednie warto�ci
void inicjalizuj_plansze(int tab[][m])
{
    for(int i=0; i<n; i++)												//przej�cie po wierszach
        for(int j=0; j<m; j++)											//przej�cie po kolumnach
        {
            if ((i<=1 || i>=6) || (j<=1 || j>=6)) tab[i][j] = 0;		//wype�nienie pustymi polami "ramki" dooko�a p�l z pionkami
            else
            {
                if((i+j)%2 == 0) tab[i][j] = 1;							//parzysta suma indeks�w odpowiada pionkowi bia�emu 
                else tab[i][j] = -1;									//w innym przypadku wpisany zostanie pionek czarny
            }
        }
}

//funkcja rysuje plansz� w oparciu o tablic� z pionkami
void rysuj(int tab[][m])
{	
	system("cls");																//przed narysowaniem planszy czy�ci konsol�
    for(int i=0; i<n; i++)														//przej�cie po wierszach
    {
    	cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        int linijka = 1;														//pierwsze przej�cie nast�pnej p�tli dotyczy pierwszej linijki
        for(int k=0; k<2; k++)													//p�tla do tworzenia dw�ch linijek dla ka�dego wiersza planszy
        {
            if (linijka == 1) cout << "  |";									//w pierwszej linijce nie podpisuje wiersza
            else cout << i+1 << " |";											//w drugiej linijce podpisuje wiersz jego numerem
            for(int j=0; j<m; j++)												//przej�cie po kolumnach
            {
                if(tab[i][j] == 0) cout << "     |";							//"kolorowanie" p�l planszy: pole puste, pionek bia�y i pionek czarny
                else if(tab[i][j] == 1) cout << " OOO |";
                else cout <<" ### |";
            }
            linijka = 2;														//nast�pne przej�cie p�tli b�dzie dotyczy� drugiej linijki
			cout << endl;
        }
    }
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl		//p�tla zaczyna�a si� od narysowania "belki" wi�c ostatni� nale�y zrobi� manualnie
         << "     A     B     C     D     E     F     G     H   " << endl << endl;
}

//funkcja sprawdza ile ruch�w ma wybrany pionek i zwraca warto�ci od 0 do 4
int czy_ma_ruch(int tab[][m], int a, int b)
{
	int ruchy = 0;
	
	if(tab[a][b]==0) return 0;										//warunek dla pola pustego
	
	if(a>=1 && a<=6)																								//warunek dla mo�liwo�ci bicia w poziomie
		if((tab[a-1][b]==-tab[a][b] && tab[a+1][b]==0) || (tab[a-1][b]==0 && tab[a+1][b]==-tab[a][b])) ruchy++;		//sprawdza czy s�siednie poziomo pola s�: 1 puste i jedno z pionkiem przeciwnym
	if(b>=1 && b<=6)																								//warunek dla mo�liwo�ci bicia w pionie
		if((tab[a][b-1]==-tab[a][b] && tab[a][b+1]==0) || (tab[a][b-1]==0 && tab[a][b+1]==-tab[a][b])) ruchy++;		//sprawdza czy s�siednie pionowo pola s�: 1 puste i 1 z pionkiem przeciwnym
	if((a>=1 && a<=6) && (b>=1 && b<=6))																			//warunek dla mo�liwo�ci bicia po diagonali
		{
			if((tab[a-1][b-1]==-tab[a][b] && tab[a+1][b+1]==0) || (tab[a-1][b-1]==0 && tab[a+1][b+1]==-tab[a][b])) ruchy++;		//sprawdza czy s�siednie diagonalnie pola s�: 1 puste i jedno z pionkiem przeciwnym
			if((tab[a-1][b+1]==-tab[a][b] && tab[a+1][b-1]==0) || (tab[a-1][b+1]==0 && tab[a+1][b-1]==-tab[a][b])) ruchy++;
		}
	return ruchy;
}

//funkcja rysuje od nowa tablic� i podaje kto ma tur�, gdy gracz �le wybierze pionek
void procedura_zly_pionek(int tab[][m], int gracz)
{
	system("pause");
	rysuj(tab);
	if (gracz == 1) cout << "Ture ma gracz bialy" << endl;
	else if (gracz == -1) cout << "Ture ma gracz czarny" << endl;
}

//funkcja sprawdza czy gracz wybra� poprawnie pole z pionkiem, kt�ry nale�y do niego i posiada ruch
void wybor_pionka(int tab[][m], int &wiersz, int &kolumna, int gracz)
{
	char znak_wiersza, znak_kolumny;
	while(1)																//p�tla zako�czy si� dopiero gdy wybrane zostanie poprawne pole z pionkiem
	{
		cout << "Wybierz pionek: ";
		cin >> znak_wiersza;
		cin >> znak_kolumny;
		cin.ignore();
		cin.clear();
		
		if(znak_wiersza<49 || znak_wiersza>56)								//sprawdza, czy pierwszy znak jest z przedzia�u 1-8	
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_pionek(tab, gracz);								//funkcja czy�ci konsol�, rysuje od nowa tablic� i podaje kto ma tur� 
			continue;														//powt�rzenie p�tli w przypadku z�ego znaku
		}
		wiersz = znak_wiersza - 48;											//gdy znak jest dobry, konwertuje si� go do zmiennej ca�kowitej (wiersz)
		
		if(znak_kolumny>=97 && znak_kolumny<=104) znak_kolumny -= 32;		//sprawdza, czy drugi znak jest z przedzia�u a-h, jesli tak to zmienia go na A-H
		if(znak_kolumny<65 || znak_kolumny>72)								//sprawdza, czy drugi znak jest z przedzia�u A-H
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_pionek(tab, gracz);
			continue;
		}
		kolumna = znak_kolumny - 64;										//gdy znak jest dobry, konwertuje si� go do zmiennej ca�kowitej jako warto�� 1-8 (kolumna)
		
		if(tab[wiersz-1][kolumna-1]==-gracz)								//sprawdza, czy gracz nie wybra� pionka przeciwnika
		{
			cout << "Wybrales pionek gracza przeciwnego, wybierz swoj pionek!" << endl;
			procedura_zly_pionek(tab, gracz);
			continue;
		}
		
		if(tab[wiersz-1][kolumna-1]==0)										//sprawdza czy wybrane pole nie jest puste
		{
			cout << "Wybrales puste pole! Wybierz jeszcze raz" << endl;
			procedura_zly_pionek(tab, gracz);
			continue;
		}
		
		if(czy_ma_ruch(tab, wiersz-1, kolumna-1)==0)						//sprawdza, czy wybrany pionek nie ma ruch�w
		{
			cout << "Wybrany pionek nie ma ruchow! Wybierz inny pionek" << endl;
			procedura_zly_pionek(tab, gracz);
			continue;
		}
		break;														//p�tla przerywa si� tylko, gdy wszystkie warunki zostan� spe�nione
	}
}

//funkcja od nowa rysuje tablic�, podaje kto ma tur� i jaki pionek zosta� wcze�niej wybrany, gdy gracz wybierze z�e pole ruchu
void procedura_zly_ruch(int tab[][m], int wiersz, int kolumna, int gracz)
{
	char znak_kolumna;
	znak_kolumna = kolumna + 64;						//zamienia warto�� liczbow� kolumny na odpowiadaj�cy znak z przedzia�u A-H
	system("pause");
	rysuj(tab);
	if (gracz == 1) cout << "Ture ma gracz bialy" << endl;
	else if (gracz == -1) cout << "Ture ma gracz czarny" << endl;
	cout << "Wybrany pionek znajduje sie na polu " << wiersz << znak_kolumna << endl;
	
}

//funkcja sprawdza czy gracz poprawnie wybra� pole, na kt�re chce si� poruszy� wybranym pionkiem
void ruch_pionka(int tab[][m], int wiersz_pionek, int kolumna_pionek, int gracz)
{
	char znak_wiersza, znak_kolumny;
	int wiersz_ruch, kolumna_ruch;
	while(1)
	{
		cout << "Wybierz pole na ktore chcesz sie poruszyc: ";
		cin >> znak_wiersza;
		cin >> znak_kolumny;
		cin.ignore();
		cin.clear();
		
		if (znak_wiersza<49 || znak_wiersza>56)									//sprawdza czy wiersz jest z przedzia�u 1-8
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_ruch(tab, wiersz_pionek, kolumna_pionek, gracz);
			continue;
		}
		wiersz_ruch = znak_wiersza - 48;										//je�li tak, to przypisuje innej zmiennej liczb� ca�kowit� na podstawie warto�ci znakowej
		
		if (znak_kolumny>=97 && znak_kolumny<=104) znak_kolumny -= 32;			//sprawdza czy kolumna jest z przedzia�i a-h, je�li tak to zmienia na wielk� liter�
		if (znak_kolumny<65 || znak_kolumny>72)									//sprawdza czy kolumna jest z przedzia�u A-H
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_ruch(tab, wiersz_pionek, kolumna_pionek, gracz);
			continue;
		}
		kolumna_ruch = znak_kolumny - 64;										//je�li tak, przypisuje innej zmiennej liczb� ca�kowit� z przedzia�u 1-8 odpowiadaj�c� przedzia�owi A-H

		//warunek ruchu poprawnego: pole w takiej samej odleg�o�ci i tym samym kierunku co wybrane pole ruchu, lecz przeciwnym zwrocie do pola wybranego pionka, 		
		if (tab[wiersz_ruch-1][kolumna_ruch-1]==0 && tab[2*(wiersz_pionek-1) - (wiersz_ruch-1)][2*(kolumna_pionek-1) - (kolumna_ruch-1)]==-gracz)
		{
			tab[wiersz_pionek-1][kolumna_pionek-1] = 0;														//pole pionka staje si� puste
			tab[wiersz_ruch-1][kolumna_ruch-1] = gracz;														//pole ruchu staje si� polem pionka
			tab[2*(wiersz_pionek-1) - (wiersz_ruch-1)][2*(kolumna_pionek-1) - (kolumna_ruch-1)] = 0;		//pole przeciwnika staje si� puste
		}
		else
		{
			cout << "Podany ruch jest niepoprawny! Wykonaj inny ruch" << endl;
			procedura_zly_ruch(tab, wiersz_pionek, kolumna_pionek, gracz);
			continue;
		}
		break;
	}
}

//funkcja liczy pionki czarne i bia�e w tablicy
void licz_pionki(int tab[][m], int &biale, int &czarne)
{
	biale = 0;
	czarne = 0;
	for(int i=0; i<n; i++)									//przej�cie po wierszach
		for(int j=0; j<m; j++)								//przej�cie po kolumnach
		{
			if(tab[i][j]==1) biale++;						//pionki bia�e maj� warto�� 1 w tablicy
			else if(tab[i][j]==-1) czarne++;				//pionki czarne maj� warto�c -1 w tablicy
		}		
}

//funkcja przechodzi po tablicy, szuka pionk�w i bada czy maj� mo�liwe ruchy
 void licz_ruchy_pionkow(int tab[][m], int &biale, int &czarne)
{
	biale = 0;
	czarne = 0;
	for(int i=0; i<n; i++)								//przej�cie po wierszach
		for(int j=0; j<m; j++)							//przej�cie po kolumnach
		{
			if(tab[i][j]==1)							//gracz bia�y ma warto�� 1 w tabeli
				if(czy_ma_ruch(tab, i, j)>0) biale++;	//funkcja czy_ma_ruch zwraca warto�ci od 0 do 4, w zale�no�ci od ilo�ci mo�liwych ruch�w wybranego pionka
				
			if(tab[i][j]==-1)							//gracz czarny ma warto�� -1 w tabeli				
				if(czy_ma_ruch(tab, i, j)>0) czarne++;	//funkcja czy_ma_ruch zwraca warto�ci od 0 do 4 (jak wy�ej)
		}
}

//funkcja bada kt�ry gracz ma obecnie tur�
int stan_tury(int tab[][m], int ruchy_biale, int ruchy_czarne, int &gracz)
{
	int omija_ture = 0;
    if(gracz == 1)											//gracz bia�y ma warto�c 1 w tablicy
	{
		cout << "Ture ma gracz bialy" << endl;
		if(ruchy_biale == 0)
		{
			cout << "Gracz bialy nie moze wykonac zadnego ruchu i musi oddac ture!" << endl;
			omija_ture = 1;
			system("pause");
		}
	}
	else if(gracz == -1)									//gracz czarny ma warto�c -1 w tablicy
	{
		cout << "Ture ma gracz czarny" << endl;
		if (ruchy_czarne == 0)								//gdy gracz czarny nie ma ruch�w nast�puje zmiana gracza i funkcja zwraca 1
			{
				cout << "Gracz czarny nie moze wykonac zadnego ruchu i musi oddac ture!" << endl;
				omija_ture = 1;
				system("pause");
			}
	}
	return omija_ture;			//funkcja zwraca warto�� liczbow�, od kt�rej zale�y, czy tura w funkcji main dalej b�dzie trwa�, czy si� sko�czy
}

//funkcja ta jest opcjonalna, pokazuje ile jest jakich pionk�w na planszy oraz ile z nich ma ruch
void funkcja_pomocnicza(int pionki_biale, int pionki_czarne, int ruchy_biale, int ruchy_czarne)
{
    cout << "Na planszy jest " << pionki_biale << " pionkow bialych i " << pionki_czarne << " czarnych" << endl;
    cout << ruchy_biale << " pionkow bialych i " << ruchy_czarne << " pionkow czarnych ma ruch" << endl << endl;	
}


int main()
{
    int plansza[n][m];
    int wiersz_pionek, kolumna_pionek, wiersz_ruch, kolumna_ruch;
    int pionki_biale, pionki_czarne, ruchy_biale, ruchy_czarne;
    int gracz = 1;													//zaczyna gracz bia�y - w tablicy ma warto�� 1
    
    inicjalizuj_plansze(plansza);									//wype�nia tablic� odpowiednimi warto�ciami

    while(1)						//nieskoczona p�tla przedstawiaj�ca przebieg tury, sko�czy sie tylko gdy zostanie spe�niony okre�lony warunek
    {
        licz_pionki(plansza, pionki_biale, pionki_czarne);											//funkcja liczy ilo�� pionk�w bia�ych i czarnych
        licz_ruchy_pionkow(plansza, ruchy_biale, ruchy_czarne);										//funkcja liczy ilo�� pionk�w bia�ych i czarnych, kt�re mog� wykona� jaki� ruch
        
		rysuj(plansza);																				//funkcja czy�ci konsol� i rysuje plansz�
        
		funkcja_pomocnicza(pionki_biale, pionki_czarne, ruchy_biale, ruchy_czarne);        		 	//funkcja pomocnicza pokazuje ilo�� pionk�w i ilo�� pionk�w, kt�re maj� ruchy
        
        if(pionki_biale == 0 || pionki_czarne == 0 || (ruchy_biale == 0 && ruchy_czarne == 0)) break;		//warunek zako�czenia gry(brak pionk�w jednego gracza lub brak ruch�w obu graczy)

		if(stan_tury(plansza, ruchy_biale, ruchy_czarne, gracz)==1)									//pokazuje kt�ry gracz ma tur� i czy przypadkiem jej nie omija (wtedy ko�czy tur�)
		{
			gracz *= -1;
			continue;
		}
		
		wybor_pionka(plansza, wiersz_pionek, kolumna_pionek, gracz);								//bada wyb�r poprawnego pionka
		ruch_pionka(plansza, wiersz_pionek, kolumna_pionek, gracz);									//bada czy wybrany ruch jest dozwolony - je�li tak to nast�puje bicie

        gracz *= -1;																				//zmiana gracza na przeciwnego, koniec tury
    }
    
    cout << "Koniec gry!" << endl;
    if(pionki_biale > pionki_czarne) cout << "Wygrywa gracz bialy!" << endl;
    else if(pionki_biale == pionki_czarne) cout << "Remis!" << endl;
    else cout << "Wygrywa gracz czarny!" << endl;
       
    system("PAUSE");
    return 0;
}
