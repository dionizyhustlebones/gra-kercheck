#include <iostream>

using namespace std;

const int n = 8;				//sta³a iloœæ wierszy w tablicy
const int m = 8;				//sta³a iloœæ kolumn w tablicy

//funkcja przypisuje odpowiednim polom w tablicy odpowiednie wartoœci
void inicjalizuj_plansze(int tab[][m])
{
    for(int i=0; i<n; i++)												//przejœcie po wierszach
        for(int j=0; j<m; j++)											//przejœcie po kolumnach
        {
            if ((i<=1 || i>=6) || (j<=1 || j>=6)) tab[i][j] = 0;		//wype³nienie pustymi polami "ramki" dooko³a pól z pionkami
            else
            {
                if((i+j)%2 == 0) tab[i][j] = 1;							//parzysta suma indeksów odpowiada pionkowi bia³emu 
                else tab[i][j] = -1;									//w innym przypadku wpisany zostanie pionek czarny
            }
        }
}

//funkcja rysuje planszê w oparciu o tablicê z pionkami
void rysuj(int tab[][m])
{	
	system("cls");																//przed narysowaniem planszy czyœci konsolê
    for(int i=0; i<n; i++)														//przejœcie po wierszach
    {
    	cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        int linijka = 1;														//pierwsze przejœcie nastêpnej pêtli dotyczy pierwszej linijki
        for(int k=0; k<2; k++)													//pêtla do tworzenia dwóch linijek dla ka¿dego wiersza planszy
        {
            if (linijka == 1) cout << "  |";									//w pierwszej linijce nie podpisuje wiersza
            else cout << i+1 << " |";											//w drugiej linijce podpisuje wiersz jego numerem
            for(int j=0; j<m; j++)												//przejœcie po kolumnach
            {
                if(tab[i][j] == 0) cout << "     |";							//"kolorowanie" pól planszy: pole puste, pionek bia³y i pionek czarny
                else if(tab[i][j] == 1) cout << " OOO |";
                else cout <<" ### |";
            }
            linijka = 2;														//nastêpne przejœcie pêtli bêdzie dotyczyæ drugiej linijki
			cout << endl;
        }
    }
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl		//pêtla zaczyna³a siê od narysowania "belki" wiêc ostatni¹ nale¿y zrobiæ manualnie
         << "     A     B     C     D     E     F     G     H   " << endl << endl;
}

//funkcja sprawdza ile ruchów ma wybrany pionek i zwraca wartoœci od 0 do 4
int czy_ma_ruch(int tab[][m], int a, int b)
{
	int ruchy = 0;
	
	if(tab[a][b]==0) return 0;										//warunek dla pola pustego
	
	if(a>=1 && a<=6)																								//warunek dla mo¿liwoœci bicia w poziomie
		if((tab[a-1][b]==-tab[a][b] && tab[a+1][b]==0) || (tab[a-1][b]==0 && tab[a+1][b]==-tab[a][b])) ruchy++;		//sprawdza czy s¹siednie poziomo pola s¹: 1 puste i jedno z pionkiem przeciwnym
	if(b>=1 && b<=6)																								//warunek dla mo¿liwoœci bicia w pionie
		if((tab[a][b-1]==-tab[a][b] && tab[a][b+1]==0) || (tab[a][b-1]==0 && tab[a][b+1]==-tab[a][b])) ruchy++;		//sprawdza czy s¹siednie pionowo pola s¹: 1 puste i 1 z pionkiem przeciwnym
	if((a>=1 && a<=6) && (b>=1 && b<=6))																			//warunek dla mo¿liwoœci bicia po diagonali
		{
			if((tab[a-1][b-1]==-tab[a][b] && tab[a+1][b+1]==0) || (tab[a-1][b-1]==0 && tab[a+1][b+1]==-tab[a][b])) ruchy++;		//sprawdza czy s¹siednie diagonalnie pola s¹: 1 puste i jedno z pionkiem przeciwnym
			if((tab[a-1][b+1]==-tab[a][b] && tab[a+1][b-1]==0) || (tab[a-1][b+1]==0 && tab[a+1][b-1]==-tab[a][b])) ruchy++;
		}
	return ruchy;
}

//funkcja rysuje od nowa tablicê i podaje kto ma turê, gdy gracz Ÿle wybierze pionek
void procedura_zly_pionek(int tab[][m], int gracz)
{
	system("pause");
	rysuj(tab);
	if (gracz == 1) cout << "Ture ma gracz bialy" << endl;
	else if (gracz == -1) cout << "Ture ma gracz czarny" << endl;
}

//funkcja sprawdza czy gracz wybra³ poprawnie pole z pionkiem, który nale¿y do niego i posiada ruch
void wybor_pionka(int tab[][m], int &wiersz, int &kolumna, int gracz)
{
	char znak_wiersza, znak_kolumny;
	while(1)																//pêtla zakoñczy siê dopiero gdy wybrane zostanie poprawne pole z pionkiem
	{
		cout << "Wybierz pionek: ";
		cin >> znak_wiersza;
		cin >> znak_kolumny;
		cin.ignore();
		cin.clear();
		
		if(znak_wiersza<49 || znak_wiersza>56)								//sprawdza, czy pierwszy znak jest z przedzia³u 1-8	
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_pionek(tab, gracz);								//funkcja czyœci konsolê, rysuje od nowa tablicê i podaje kto ma turê 
			continue;														//powtórzenie pêtli w przypadku z³ego znaku
		}
		wiersz = znak_wiersza - 48;											//gdy znak jest dobry, konwertuje siê go do zmiennej ca³kowitej (wiersz)
		
		if(znak_kolumny>=97 && znak_kolumny<=104) znak_kolumny -= 32;		//sprawdza, czy drugi znak jest z przedzia³u a-h, jesli tak to zmienia go na A-H
		if(znak_kolumny<65 || znak_kolumny>72)								//sprawdza, czy drugi znak jest z przedzia³u A-H
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_pionek(tab, gracz);
			continue;
		}
		kolumna = znak_kolumny - 64;										//gdy znak jest dobry, konwertuje siê go do zmiennej ca³kowitej jako wartoœæ 1-8 (kolumna)
		
		if(tab[wiersz-1][kolumna-1]==-gracz)								//sprawdza, czy gracz nie wybra³ pionka przeciwnika
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
		
		if(czy_ma_ruch(tab, wiersz-1, kolumna-1)==0)						//sprawdza, czy wybrany pionek nie ma ruchów
		{
			cout << "Wybrany pionek nie ma ruchow! Wybierz inny pionek" << endl;
			procedura_zly_pionek(tab, gracz);
			continue;
		}
		break;														//pêtla przerywa siê tylko, gdy wszystkie warunki zostan¹ spe³nione
	}
}

//funkcja od nowa rysuje tablicê, podaje kto ma turê i jaki pionek zosta³ wczeœniej wybrany, gdy gracz wybierze z³e pole ruchu
void procedura_zly_ruch(int tab[][m], int wiersz, int kolumna, int gracz)
{
	char znak_kolumna;
	znak_kolumna = kolumna + 64;						//zamienia wartoœæ liczbow¹ kolumny na odpowiadaj¹cy znak z przedzia³u A-H
	system("pause");
	rysuj(tab);
	if (gracz == 1) cout << "Ture ma gracz bialy" << endl;
	else if (gracz == -1) cout << "Ture ma gracz czarny" << endl;
	cout << "Wybrany pionek znajduje sie na polu " << wiersz << znak_kolumna << endl;
	
}

//funkcja sprawdza czy gracz poprawnie wybra³ pole, na które chce siê poruszyæ wybranym pionkiem
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
		
		if (znak_wiersza<49 || znak_wiersza>56)									//sprawdza czy wiersz jest z przedzia³u 1-8
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_ruch(tab, wiersz_pionek, kolumna_pionek, gracz);
			continue;
		}
		wiersz_ruch = znak_wiersza - 48;										//jeœli tak, to przypisuje innej zmiennej liczbê ca³kowit¹ na podstawie wartoœci znakowej
		
		if (znak_kolumny>=97 && znak_kolumny<=104) znak_kolumny -= 32;			//sprawdza czy kolumna jest z przedzia³i a-h, jeœli tak to zmienia na wielk¹ literê
		if (znak_kolumny<65 || znak_kolumny>72)									//sprawdza czy kolumna jest z przedzia³u A-H
		{
			cout << "Niepoprawne dane! Podaj pole jeszcze raz" << endl;
			procedura_zly_ruch(tab, wiersz_pionek, kolumna_pionek, gracz);
			continue;
		}
		kolumna_ruch = znak_kolumny - 64;										//jeœli tak, przypisuje innej zmiennej liczbê ca³kowit¹ z przedzia³u 1-8 odpowiadaj¹c¹ przedzia³owi A-H

		//warunek ruchu poprawnego: pole w takiej samej odleg³oœci i tym samym kierunku co wybrane pole ruchu, lecz przeciwnym zwrocie do pola wybranego pionka, 		
		if (tab[wiersz_ruch-1][kolumna_ruch-1]==0 && tab[2*(wiersz_pionek-1) - (wiersz_ruch-1)][2*(kolumna_pionek-1) - (kolumna_ruch-1)]==-gracz)
		{
			tab[wiersz_pionek-1][kolumna_pionek-1] = 0;														//pole pionka staje siê puste
			tab[wiersz_ruch-1][kolumna_ruch-1] = gracz;														//pole ruchu staje siê polem pionka
			tab[2*(wiersz_pionek-1) - (wiersz_ruch-1)][2*(kolumna_pionek-1) - (kolumna_ruch-1)] = 0;		//pole przeciwnika staje siê puste
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

//funkcja liczy pionki czarne i bia³e w tablicy
void licz_pionki(int tab[][m], int &biale, int &czarne)
{
	biale = 0;
	czarne = 0;
	for(int i=0; i<n; i++)									//przejœcie po wierszach
		for(int j=0; j<m; j++)								//przejœcie po kolumnach
		{
			if(tab[i][j]==1) biale++;						//pionki bia³e maj¹ wartoœæ 1 w tablicy
			else if(tab[i][j]==-1) czarne++;				//pionki czarne maj¹ wartoœc -1 w tablicy
		}		
}

//funkcja przechodzi po tablicy, szuka pionków i bada czy maj¹ mo¿liwe ruchy
 void licz_ruchy_pionkow(int tab[][m], int &biale, int &czarne)
{
	biale = 0;
	czarne = 0;
	for(int i=0; i<n; i++)								//przejœcie po wierszach
		for(int j=0; j<m; j++)							//przejœcie po kolumnach
		{
			if(tab[i][j]==1)							//gracz bia³y ma wartoœæ 1 w tabeli
				if(czy_ma_ruch(tab, i, j)>0) biale++;	//funkcja czy_ma_ruch zwraca wartoœci od 0 do 4, w zale¿noœci od iloœci mo¿liwych ruchów wybranego pionka
				
			if(tab[i][j]==-1)							//gracz czarny ma wartoœæ -1 w tabeli				
				if(czy_ma_ruch(tab, i, j)>0) czarne++;	//funkcja czy_ma_ruch zwraca wartoœci od 0 do 4 (jak wy¿ej)
		}
}

//funkcja bada który gracz ma obecnie turê
int stan_tury(int tab[][m], int ruchy_biale, int ruchy_czarne, int &gracz)
{
	int omija_ture = 0;
    if(gracz == 1)											//gracz bia³y ma wartoœc 1 w tablicy
	{
		cout << "Ture ma gracz bialy" << endl;
		if(ruchy_biale == 0)
		{
			cout << "Gracz bialy nie moze wykonac zadnego ruchu i musi oddac ture!" << endl;
			omija_ture = 1;
			system("pause");
		}
	}
	else if(gracz == -1)									//gracz czarny ma wartoœc -1 w tablicy
	{
		cout << "Ture ma gracz czarny" << endl;
		if (ruchy_czarne == 0)								//gdy gracz czarny nie ma ruchów nastêpuje zmiana gracza i funkcja zwraca 1
			{
				cout << "Gracz czarny nie moze wykonac zadnego ruchu i musi oddac ture!" << endl;
				omija_ture = 1;
				system("pause");
			}
	}
	return omija_ture;			//funkcja zwraca wartoœæ liczbow¹, od której zale¿y, czy tura w funkcji main dalej bêdzie trwaæ, czy siê skoñczy
}

//funkcja ta jest opcjonalna, pokazuje ile jest jakich pionków na planszy oraz ile z nich ma ruch
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
    int gracz = 1;													//zaczyna gracz bia³y - w tablicy ma wartoœæ 1
    
    inicjalizuj_plansze(plansza);									//wype³nia tablicê odpowiednimi wartoœciami

    while(1)						//nieskoczona pêtla przedstawiaj¹ca przebieg tury, skoñczy sie tylko gdy zostanie spe³niony okreœlony warunek
    {
        licz_pionki(plansza, pionki_biale, pionki_czarne);											//funkcja liczy iloœæ pionków bia³ych i czarnych
        licz_ruchy_pionkow(plansza, ruchy_biale, ruchy_czarne);										//funkcja liczy iloœæ pionków bia³ych i czarnych, które mog¹ wykonaæ jakiœ ruch
        
		rysuj(plansza);																				//funkcja czyœci konsolê i rysuje planszê
        
		funkcja_pomocnicza(pionki_biale, pionki_czarne, ruchy_biale, ruchy_czarne);        		 	//funkcja pomocnicza pokazuje iloœæ pionków i iloœæ pionków, które maj¹ ruchy
        
        if(pionki_biale == 0 || pionki_czarne == 0 || (ruchy_biale == 0 && ruchy_czarne == 0)) break;		//warunek zakoñczenia gry(brak pionków jednego gracza lub brak ruchów obu graczy)

		if(stan_tury(plansza, ruchy_biale, ruchy_czarne, gracz)==1)									//pokazuje który gracz ma turê i czy przypadkiem jej nie omija (wtedy koñczy turê)
		{
			gracz *= -1;
			continue;
		}
		
		wybor_pionka(plansza, wiersz_pionek, kolumna_pionek, gracz);								//bada wybór poprawnego pionka
		ruch_pionka(plansza, wiersz_pionek, kolumna_pionek, gracz);									//bada czy wybrany ruch jest dozwolony - jeœli tak to nastêpuje bicie

        gracz *= -1;																				//zmiana gracza na przeciwnego, koniec tury
    }
    
    cout << "Koniec gry!" << endl;
    if(pionki_biale > pionki_czarne) cout << "Wygrywa gracz bialy!" << endl;
    else if(pionki_biale == pionki_czarne) cout << "Remis!" << endl;
    else cout << "Wygrywa gracz czarny!" << endl;
       
    system("PAUSE");
    return 0;
}
