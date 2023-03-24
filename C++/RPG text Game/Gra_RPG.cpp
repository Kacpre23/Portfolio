#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

#define SAVE_FILE "game.fdx" //name of the game save file
#define MAX_SCENA 8 //maximum number of scenes

HANDLE kolor; //variable that holds the color
int wrog[9][3] = { {35, 2, 15 }, {50, 2, 10}, {45, 32, 8}, {100, 5, 25}, {35, 6, 13}, {34, 6, 12}, {400, 6, 14}, {50, 10, 24}, {98, 8, 64} }; //[HP] [ARMOR] [Attack]
int boh[1][3] = { 50, 10, 42 }; //[HP] [ARMOR] [Attack]
using namespace std;
int aktual_scena; //global variable used for transitions between scenes
unsigned int rand_int_fromto(int a, int b); //pseudo-random number function
int save_read(void); //the function responsible for reading the state of the game 
void save_write(unsigned int stan_gry); //the function responsible for saving the state of the game
int losowanie_walki(); //the function responsible for the draw of the fight (whether it will take place)
int losowanie_przeciwnika(int a); //the function responsible for drawing the opponent
int system_walki(int kolumn, int kolumnB, string enemy, string bohater); //combat system function
void wstep();
void s1();
void s2walka();
void scena4brama();
void s3kopalnia();
void s62walka();
void s5();
void s7();
void s8();
void s9();
void s10();
unsigned int wynik_walki;



int main()
{
	srand(time(NULL));  //pseudo-random number generator initialization
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);// a function that implements the colors of the text in the console
	//if aktual_scena = 0 the program displays the main menu
	//if aktual_scena < 0 program exits
	//if aktual_scena > 0 the program continues to play

//MENU - aktual_scena = 0
//PROLOG - aktual_scena = 1
//WALKA - aktual_scena = 2
//KOPALNIA - aktual_scena = 3
//BRAMA - aktual_scenea = 4
//LAS - aktual_scena = 5
//WALKA2 - aktual_scena = 6
//ROZDZIAL I - aktual_scena = 7

	wstep();
	//PROLOG
	s1();
	//FIGHT
	s2walka();
	///BRAMA
	scena4brama();
	///KOPALNIA
	s3kopalnia();
	///WALKA2
	s62walka();
	s5();
	///ROZDZIAL I
	s7();
	///R001
	s8();
	///ROO2
	///R003
	s9();

	system("pause");
	system("cls");
	aktual_scena = 0;
}

void wstep()
{
	while (aktual_scena == 0)  //the main loop to move around the game structure
	{
	menu:
		system("cls");
		SetConsoleTextAttribute(kolor, 4);
		cout << "v.1.0.0\n" << endl;
		SetConsoleTextAttribute(kolor, 12);
		cout << "Witamy w grze Tzaryat - Text Game\n" << endl;
	pocz:
		SetConsoleTextAttribute(kolor, 6);

		cout << "\n 1)Nowa gra \n 2)Wczytaj gre \n 3)Informacje o tworcach \n 4)Zakoncz przygode \n 5)TRYB DEBAGOWY \n" << endl;

		int wybor;
		cin >> wybor;
		system("cls");

		switch (wybor)
		{
		case 1:
		wyb:
			SetConsoleTextAttribute(kolor, 6);
			cout << "\nCzy chcesz rozpoczac nowa przygode?\n\n 1) TAK\n 2) NIE\n" << endl;
			cin >> wybor;
			if (wybor == 1)
			{
				system("cls");
				aktual_scena = 1;

			}
			else if (wybor == 2)
			{
				system("cls");
				cout << "Skoro nie chcesz...\n" << endl;
				goto menu; // do zmiany
			}
			else
			{
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				goto wyb;
			}
			break;

		case 2:
		{
			aktual_scena = save_read(); //load save game from file
			if (aktual_scena > MAX_SCENA)
			{  //protection in the event of a corrupted game save file
				aktual_scena = 0;
			}
			break;
		}

		case 3:
		{
			getchar();
			cout << "\n\nGra znajduje się w wersji testowej.\nJezeli cos nie dziala, napisz do nas, a my sie tym zajmiemy:\n[e-mail]\n\n\nProgramisci:\n\nKacper Suder\n\nHistoria: \n\nMarcin Rzesista" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			goto menu;
		}

		case 4:
		{
		wroc:
			SetConsoleTextAttribute(kolor, 6);
			cout << "\nPrawdziwy bohater nigdy nie ucieka z pola walki\nCzy chcesz uciec i pokryc sie hanba? \n\n1) Nie, nigdy sie nie poddam!\n2) Jestem tchorzem i uciekam\n\n" << endl;
			cin >> wybor;
			system("cls");
			if (wybor == 1)
			{
				break;
			}
			else if (wybor == 2)
			{
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrales ucieczke TCHORZU!!\n" << endl;
				return;
			}
			else
			{
				SetConsoleTextAttribute(kolor, 4);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				goto wroc;
			}
		}
		case 5:  //debug mode - we check the added functions
			cout << "Witam w trybie debagowym" << endl;
			losowanie_walki();
			break;
		}


	}
}

void s1()
{
	if (aktual_scena == 1) {

		SetConsoleTextAttribute(kolor, 12);
		cout << "\n\nPROLOG\n\n\n" << endl;
		SetConsoleTextAttribute(kolor, 7);
		cout << "Zarys fabularny krainy:\n" << endl;
		cout << "Kolonia na Wyspach Macierzystych Tzaryatu zostala zalozona przez jednego z 5 wielkich mistrzow architektury Kontynetu Nowego Tzaryatu, Ardona.\n15 lat temu w roku 1215 po zalozeniu Wielkiego Miasta Kolonijnego wladze nie byly w stanie poradzic sobie z narastajacym problemem gromadzenia\ncoraz to wiekszej liczby skazancow, mordercow oraz nachalnych przestepcow.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nWielki Mistrz Zakonu Swietego Ryszarda nakazal staremu architektowi znalezc miejsce, w ktorym wszelkie zlo bedzie pokutowac za swe czyny.\nPolwysep zwany Cyplem Rakovitza nadawal sie do tego celu doskonale.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nOd reszty kontynentu oddzielal go potezny Lancuch gorski Fraze Cliffs.\nLegendy mowia, ze najpotezniejsi wladcy demonow maja tam swoje siedziby, a mroczne lasy u jego podnoza zamieszkiwane sa przez najgrozniejsze\npotwory Wysp Macierzystych Tzaryatu.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nZa lasem rozciagal sie olbrzymi pas rownin i pustkowi, gdzie mieszcza sie zgliszcza po dawniej pelnych zycia wioskach i mniejszych osrodkow miejskich.\nZa rowninami po wschodniej stronie polwyspu rozciagalo sie dosc duze pasmo gorskie polaczone z ciesnina Dardiano, przez co uniemozliwialo przejscie\ndalej polnocnym wschodem, pozostawalo tylko zachodnie przejscie. Gory te byly bogate w zloza rudy zelaza, kamienia oraz wegla, mialy rowniez duzy\npotencjal obronny. Na zachodzie rozpoczynal sie szereg pagorkow oraz pomniejszych wzgorz, wyzynne tereny Narfang z wyniszczalym przez wojne pustkowiem.\n Oddzielona od zachodu przez pasmo gorskie, otoczona przez pogorza dolina byla idealnym miejscem na zalozenie Kolonii Karnej.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nNa poludniowy wschod doliny rozpociagala sie Gola Ziemia pozbawiona jakiego kolwiek bytu, a za nia urozmaicona linia brzegowa Cyplu Rakovitza,\nz ktorej dostrzec mozna owite mgla zarysy Wielkiego Miasta Kolonijnego.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nDolina w sercu polwyspu nazywana byla Dolina Utraconych. Owila wokol tego miejsca legenda opowiadala o wspanialych kopalniach zbudowanych w gorach.\nWydobywano w tej dolinie najlepszej jakosci zelazo, dzieki niemu wojownicy Tzaryatu mia³o zapewnione najpotezniejsze orze zamieszchlych czasow.\nMieszkancy doliny wybudowali wowczas pierwszy port na polwyspie. Handel kwitl, a mieszkancy zyli szczesliwie I spokojnie.\nDzialo sie to 5 lat przed upadkiem Wysp Macierzystych.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nZnajdujesz sie w Kolonii Karnej. Spogladasz za siebie widzac potezny, trzymetrowy, kamienny mur ze strzelistymi wiezyczkami i blankami obronnymi\noraz brame z dwoma szeregami krat zawieszonych szescioma stalowymi lancuchami na kolowrotach. Przygladasz sie przez chwile monumentalnej konstrukcji\noraz rzeszy straznikow piastujacych swoje codzienne obowiazki.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nSchodzisz wglab kopalni. Znajdujesz sie w waskiej i ciemnej grocie. W rece trzymasz kilof. Jestes odziany w stare, przetarte, lniane spodnie i koszule.\nNagle ze strony wejscia do sztolni slychac krzyki." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		int wybor = 0;;

		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\nDecydujesz sie:\n\n1)Sprawdzic co sie dzieje\n2)Zignorowac to\n" << endl;
			cin >> wybor;
			system("cls");
			if ((wybor != 1) && (wybor != 2)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((wybor != 1) && (wybor != 2));

		switch (wybor) {
		case 1:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\nPowolnym krokiem przesuwasz sie w strone wyjscia, a z czasem krzyki narastaja. Po chwili wychodzisz na powierzchnie,\na twoim oczom ukazuje sie krajobraz bitwy. Kolonia karna, w ktorej przebywales zostala zaatakowana przez Horde Ciemnosci.\n" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");

			do { //protection against entering an invalid value
				SetConsoleTextAttribute(kolor, 3);
				cout << "\nDecydujesz sie:\n\n1)Stanac do walki z wrogiem\n2)Uciec w glab kopalni\n" << endl;
				cin >> wybor;
				system("cls");
				if ((wybor != 1) && (wybor != 2)) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
			} while ((wybor != 1) && (wybor != 2));

			switch (wybor) {
			case 1:
				SetConsoleTextAttribute(kolor, 7);
				cout << "\n\nStajesz do walki." << endl;
				aktual_scena = 2;
				break;
			case 2:
				SetConsoleTextAttribute(kolor, 7);
				cout << "\n\nUciekasz w glab kopalni.\n\n" << endl;
				aktual_scena = 3;
				break;
			}

		case 2:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\nKrzyki jednak nie ustaja. Nagle slyszysz glos jednego ze skazancow: Ludzie, potwory atakuja!" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");

			do { //protection against entering an invalid value
				SetConsoleTextAttribute(kolor, 3);
				cout << "\nDecydujesz sie:\n\n1)Pozostac przy swojej decyzji i stanac do walki z wrogiem\n2)Uciec w glab kopalni\n" << endl;
				cin >> wybor;
				SetConsoleTextAttribute(kolor, 6);
				if ((wybor != 1) && (wybor != 2)) {
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
			} while ((wybor != 1) && (wybor != 2));

			switch (wybor) {
			case 1:
				SetConsoleTextAttribute(kolor, 7);
				cout << "\n\nStajesz do walki.\n\n" << endl;
				aktual_scena = 2;
				break;
			case 2:
				SetConsoleTextAttribute(kolor, 7);
				cout << "\n\nUciekasz w glab kopalni.\n\n" << endl;
				aktual_scena = 3;
				break;
			}
		}
	}
}
void s2walka()
{
	if (aktual_scena == 2) {
		save_write(aktual_scena);   //automatic saving of the game state to a file
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\n\nPoprawnie zapisano postepy." << endl;
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\n\nWychodzisz na dziedziniec, ktory jest pelen skazancow walczacych ramie w ramie ze straznikami przeciwko Hordzie Ciemnosci.\nZauwazasz jednego z nieumarlych, ktory biegnie w strone niczego nie spodziewajacego sie zolnierza.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		int prolog4 = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\nDecydujesz sie:\n\n 1)Ochronic go\n 2)Przebic sie w strone bramy glownej\n" << endl;
			cin >> prolog4;
			system("cls");
			if ((prolog4 != 1) && (prolog4 != 2)) {
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((prolog4 != 1) && (prolog4 != 2));
		switch (prolog4) {
		case 1:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\nPodbiegasz do przeciwnika i zadajesz mu cios kilofem w:" << endl;
			int prolog5 = 0;
			do { //protection against entering an invalid value
				SetConsoleTextAttribute(kolor, 3);
				cout << "\n\n1)Glowe\n2)Tulow\n3)Nogi\n" << endl;
				cin >> prolog5;
				system("cls");
				if ((prolog5 != 1) && (prolog5 != 2) && (prolog5 != 3)) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
			} while ((prolog5 != 1) && (prolog5 != 2) && (prolog5 != 3));

			switch (prolog5) {
			case 1:
				wynik_walki = rand_int_fromto(1, 100);  //generating a pseudo-random combat result
				if (wynik_walki >= 90) {
					SetConsoleTextAttribute(kolor, 7);
					cout << "\n\nUderzenie krytyczne! Wrog pada martwy na ziemie, a ty biegniesz dalej, w strone bramy glownej.\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					aktual_scena = 4;   //go to BRAMA
					break;
				}
				else {
					if (35 < wynik_walki < 85) {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Zdenerwowany, zaczyna biec w twoja strone.\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						int prolog6 = 0;;

						do { //protection against entering an invalid value
							SetConsoleTextAttribute(kolor, 3);
							cout << "\nPostanawiasz:\n\n 1)Uniknac jego ataku w ostatniej chwili odskakujac.\n 2)Zostac w miejscu.\n 3)Kopnac go\n" << endl;
							cin >> prolog6;
							system("cls");
							if ((prolog6 != 1) && (prolog6 != 2) && (prolog6 != 3)) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
						} while ((prolog6 != 1) && (prolog6 != 2) && (prolog6 != 3));
						switch (prolog6) {
						case 1:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nNiestety nie udaje ci sie. Zostajesz zabity.\n" << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							return;
						case 2:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nNiestety nie udaje ci sie. Zostajesz zabity.\n" << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							aktual_scena = 0;   //back to MENU
							return;
						case 3:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nKopiesz go, a ten upada, nadziewajac sie na miecz innego czlowieka. Ty decydujesz sie dotrzec do bramy glownej.\n" << endl;
							aktual_scena = 4;   //go to BRAMA
							break;
						default:
							SetConsoleTextAttribute(kolor, 6);
							cout << "\nWybrano niewlasciwa komende, sprobuj ponownie\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							break;

						}

					}
					else {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\nNiestety nie udaje ci sie trafic. Zostajesz zabity.\n" << endl;
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nGAME OVER!\n\n\n\n\n" << endl;
						return;
					}
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					break;

			case 2:
				wynik_walki = rand_int_fromto(1, 100);  //generate a pseudo-random combat result
				if (wynik_walki >= 65) {
					SetConsoleTextAttribute(kolor, 7);
					cout << "\n\nUderzenie krytyczne! Wrog pada martwy na ziemie, a ty biegniesz dalej, w strone bramy glownej.\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					aktual_scena = 4;   //go to BRAMA
				}
				else {
					if (20 < wynik_walki < 65) {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Zdenerwowany, zaczyna biec w twoja strone.\n" << endl;
						int prolog6 = 0;
						do { //protection against entering an invalid value
							SetConsoleTextAttribute(kolor, 3);
							cout << "\nPostanawiasz:\n\n1)Uniknac jego ataku w ostatniej chwili odskakujac.\n2)Zostac w miejscu.\n3)Kopnac go\n" << endl;
							cin >> prolog6;
							system("cls");
							if ((prolog6 != 1) && (prolog6 != 2) && (prolog6 != 3)) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
						} while ((prolog6 != 1) && (prolog6 != 2) && (prolog6 != 3));
						switch (prolog6) {
						case 1:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nNiestety nie udaje ci sie. Zostajesz zabity.\n" << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							return;
							break;
						case 2:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nNiestety nie udaje ci sie. Zostajesz zabity.\n" << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							return;
							break;
						case 3:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nKopiesz go, a ten upada, nadziewajac sie na miecz innego czlowieka. Ty decydujesz sie dotrzec do bramy glownej." << endl;
							aktual_scena = 4;   //go to BRAMA
							break;
						}

					}
					else {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\nNiestety nie udaje ci sie trafic. Zostajesz zabity.\n" << endl;
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nGAME OVER!\n\n\n\n\n" << endl;
						return;

					}

					break;

			case 3:
				wynik_walki = rand_int_fromto(1, 100);  //generate a pseudo-random combat result
				if (wynik_walki >= 50) {
					SetConsoleTextAttribute(kolor, 7);
					cout << "\n\nUderzenie krytyczne! Wrog pada martwy na ziemie, a ty biegniesz dalej, w strone bramy glownej.\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					aktual_scena = 4;   //go to BRAMA
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					break;
				}
				else {
					if (10 < wynik_walki < 50) {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Zdenerwowany, zaczyna biec w twoja strone." << endl;
						int prolog6 = 0;
						do { //protection against entering an invalid value
							SetConsoleTextAttribute(kolor, 3);
							cout << "\nPostanawiasz:\n\n1)Uniknac jego ataku w ostatniej chwili odskakujac.\n2)Zostac w miejscu.\n3)Kopnac go\n" << endl;
							cin >> prolog6;
							system("cls");
							if ((prolog6 != 1) && (prolog6 != 2) && (prolog6 != 3)) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
						} while ((prolog6 != 1) && (prolog6 != 2) && (prolog6 != 3));

						switch (prolog6) {
						case 1:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nNiestety nie udaje ci sie. Zostajesz zabity." << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							aktual_scena = 0;   //back to MENU
							break;
						case 2:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nNiestety nie udaje ci sie. Zostajesz zabity." << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							aktual_scena = 0;   //back to MENU
							break;
						case 3:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nKopiesz go, a ten upada, nadziewajac sie na miecz innego czlowieka. Ty decydujesz sie dotrzec do bramy glownej.\n" << endl;
							aktual_scena = 4;   //go to BRAMA
							break;

						}

					}
					else {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\nNiestety nie udaje ci sie trafic. Trex cie dopada i zabija.\n" << endl;
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nGAME OVER!\n\n\n\n\n" << endl;
						aktual_scena = 0;   //back to MENU
					}
					break;
				}
				}
				}
			}
		case 2:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nDecydujesz sie przedostac do bramy.\n" << endl;
			aktual_scena = 4;   //go to BRAMA
			break;
		}
	}
}
void s3kopalnia()
{
	if (aktual_scena == 3) {

		save_write(aktual_scena);   //automatic saving of the game state to a file
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\n\nPoprawnie zapisano postepy." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");


		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nSchodzisz w glab kopalni w nadziei, ze wrog cie nie znajdzie. Po kilku godzinach siedzenia w ciemnosci wszelkie dzwieki cichna. Zdajesz sie slyszec kroki z glebi korytarza jednak szybko rozpoznajesz je jako nieludzkie..." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		int kopalnia1 = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\nDecydujesz sie:\n1)Ukryc wewnatrz szybu\n2)Ominac zagrozenie bocznym korytarzem\n3)Stawic czolo zagrozeniu" << endl;
			cin >> kopalnia1;
			if ((kopalnia1 != 1) && (kopalnia1 != 2) && (kopalnia1 != 3)) {
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((kopalnia1 != 1) && (kopalnia1 != 2) && (kopalnia1 != 3));
		switch (kopalnia1) {
		case 1:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nWchodzisz do szybu i wisisz na linie. Tajemnicze kroki zblizaja sie do ciebie. Nagle slyszysz trzask. Lina na ktorej wisisz peka, a ty spadasz kilkanascie metrow w dol i giniesz.\n" << endl;
			SetConsoleTextAttribute(kolor, 12);
			cout << "\n\n\nGAME OVER\n\n\n\n\n" << endl;
			aktual_scena = 0; //back to MENU
			break;

		case 2:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nOmijasz zagrozenie i wychodzisz na zewnatrz kopalni. Twoim oczom ukazuje sie pogorzelisko na miejscu dziedzinca. Zmierzasz w strone bramy. Nagle slyszysz za soba szelest. Odwracasz sie i widzisz trzech wojownikow Hordy Ciemnosci.\n" << endl;
			int kopalnia2 = 0;
			do { //protection against entering an invalid value
				SetConsoleTextAttribute(kolor, 3);
				cout << "\n\nDecydujesz sie:\n1)Uciec\n2)Podjac walke\n" << endl;
				cin >> kopalnia2;
				system("cls");
				if ((kopalnia2 != 1) && (kopalnia2 != 2)) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
			} while ((kopalnia2 != 1) && (kopalnia2 != 2));
			switch (kopalnia2) {

			case 1:
				SetConsoleTextAttribute(kolor, 7);
				cout << "\n\nUciekasz w strone bramy, jednak jest zamknieta, jestes zmuszony podjac walke.\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				aktual_scena = 6;
				break;

			case 2:
				SetConsoleTextAttribute(kolor, 7);
				cout << "\n\nStajesz do walki.\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				aktual_scena = 6;
				break;
			}

		case 3:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nStajesz do walki." << endl;

			int kopalnia3 = 0;
			do { //protection against entering an invalid value
				SetConsoleTextAttribute(kolor, 3);
				cout << "\nZadajesz cios w:\n1)Glowe\n2)Tulow\n3)Nogi\n" << endl;
				cin >> kopalnia3;
				system("cls");
				if ((kopalnia3 != 1) && (kopalnia3 != 2)) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
			} while ((kopalnia3 != 1) && (kopalnia3 != 2) && (kopalnia3 != 3));
			switch (kopalnia3) {
			case 1:
				wynik_walki = rand_int_fromto(1, 100);
				if (wynik_walki >= 85) {
					SetConsoleTextAttribute(kolor, 7);
					cout << "\n\nUdaje ci sie powalic przeciwnika, co daje ci mozliwosc ucieczki na powierzchnie. Gdzie czeka na ciebie trzech kolejnych wrogow." << endl;
					aktual_scena = 6;   //go to WALKA2
					getchar();
				}
				else {
					if (35 < wynik_walki < 65) {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Wyprowadza atak w twoja strone." << endl;
						int kopalnia4 = 0;
						do { //protection against entering an invalid value
							SetConsoleTextAttribute(kolor, 3);
							cout << "\nPostanawiasz:\n1)Wykonac unik\n2)Zablokowac cios kilofem\n3)Kopnac go\n" << endl;
							cin >> kopalnia4;
							system("cls");
							if ((kopalnia4 != 1) && (kopalnia4 != 2) && (kopalnia4 != 3)) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
						} while ((kopalnia4 != 1) && (kopalnia4 != 2) && (kopalnia4 != 3));
						switch (kopalnia4) {
						case 1:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\n\nNiestety nie udaje ci sie. Zostajesz zabity." << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							aktual_scena = 0;   //back to MENU
							break;
						case 2:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nTwoj blok zostaje przebity, a ostrze orezu przeciwnika utyka w twojej czasce." << endl;
							SetConsoleTextAttribute(kolor, 12);
							cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
							aktual_scena = 0;   //back to MENU
							break;
						case 3:
							SetConsoleTextAttribute(kolor, 7);
							cout << "\nKopiesz go. Gdy ten upada, dobijasz go, a nastepnie zmierzasz ku powierzchni." << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							aktual_scena = 6;   //go to WALKA2

							break;
						}
					}
					else {
						SetConsoleTextAttribute(kolor, 7);
						cout << "\nNiestety nie udaje ci sie trafic. Trex cie dopada i zabija.\n" << endl;
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nGAME OVER!\n\n\n\n\n" << endl;
						aktual_scena = 0;   //back to MENU
					}
				}

			}
		}
	}
}
void scena4brama()
{
	if (aktual_scena == 4) {
		save_write(aktual_scena);   //automatic saving of the game state to a file
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\n\nPoprawnie zapisano postepy." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		losowanie_walki();
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nUdaje ci sie przedostac do bramy, jednak wrota sa zamkniete.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		int brama1 = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\nDecydujesz sie:\n\n1)Przedrzec sie do kolowrotu sterujacego brama\n2)przedostac sie na zewnatrz przez mury\n" << endl;
			cin >> brama1;
			system("cls");
			if ((brama1 != 1) && (brama1 != 2)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((brama1 != 1) && (brama1 != 2));
		switch (brama1) {
		case 1:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\nDocierasz na szczyt bramy i chwytasz za kolowrot, jednak nie jestes w stanie samodzielnie podniesc bramy. Nagle slyszysz kroki za soba.\nOdwracasz sie i widzisz wojownika Hordy Ciemnosci, wyprowadzajacego cios w twoja strone. Wiesz ze to twoj koniec. Zamykasz oczy, czekajac na cios,\njednak on nie nadchodzi. Powoli otwierasz powieki, a twoim oczom ukazuje sie widok innego skazanca, ktory uratowal ci zycie.\nDobrze wiecie co dalej robic. Chwytacie za kolowrot i otwieracie brame. Po kilku chwilach znajdujecie sie juz w glebi lasu.\n" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			aktual_scena = 5;   //go to LAS

			break;

		case 2:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\nWspinasz sie na mury i docierasz na ich szczyt. Nagle slyszysz kroki za soba. Odwracasz sie i widzisz wojownika Hordy Ciemnosci, wyprowadzajacego\ncios w twoja strone. Wiesz ze to twoj koniec. Zamykasz oczy, czekajac na cios, jednak on nie nadchodzi. Powoli otwierasz powieki, a twoim oczom\nukazuje sie widok innego skazanca, ktory uratowal ci zycie. Pomagacie sobie zejsc z murow i uciekacie w glab lasu.\n" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			aktual_scena = 5;   //go to LAS
			break;
		}
	}
}
void s5()
{
	if (aktual_scena == 5) {

		save_write(aktual_scena);   //automatic saving of the game state to a file
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\n\nPoprawnie zapisano postepy." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		losowanie_walki();
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nWraz z nowo poznanym znajomym udajecie sie wglab lasu i zmierzacie na wschod. Po kilkudziesiecu minutach wedrowki postanawiacie odpoczac przy strumieniu.\nWywiazuje sie miedzy wami dialog." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 2);
		cout << "\n\nTak w ogole to jak sie zwiesz, ja jestem Taul" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 3);
		cout << "\n\n[podaj swoje imie] Zwe sie: \n" << endl;
		char im[100];
		cin >> im;
		system("cls");
		SetConsoleTextAttribute(kolor, 2);
		cout << "\n\nA wiec milo mi cie poznac " << endl;
		cout << im << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");

		int las1 = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\n1)Dziekuje za pomoc w ucieczce\n2)Co teraz zrobimy?\n3)Dlaczego Horda Ciemnosci zaatakowala Kolonie Karna?\n" << endl;
			cin >> las1;
			system("cls");
			if ((las1 != 1) && (las1 != 2) && (las1 != 3)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((las1 != 1) && (las1 != 2) && (las1 != 3));

		switch (las1) {
		case 1:
			losowanie_walki();
			SetConsoleTextAttribute(kolor, 2);
			cout << "\n\nNie ma sprawy, trzeba sobie pomagac, by przetrwac...Slyszysz?" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nZ glebi lasu dalo sie slyszec rozmowe grupy ludzi" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\nTo patrol Zakonu Swietego Ryszarda, lepiej sie nie ujawniac" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nPrzez jakis czas ty wraz z nowo poznanym znajomym lezeliscie wsrod listowia, jednak po chwili zostaliscie zauwazeni i pochwyceni.\nPatrol zabral was bezposrednio do Miasta Kolonialniego, gdzie nazajutrz mieliscie stanac przed sadem." << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			aktual_scena = 7;

			break;
		case 2:
			SetConsoleTextAttribute(kolor, 2);
			cout << "\n\nSzczerze to nie mam pojecia, ale trzeba sobie pomagac, by przetrwac...Slyszysz?" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nZ glebi lasu dalo sie slyszec rozmowe grupy ludzi" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\nTo patrol Zakonu Swietego Ryszarda, lepiej sie nie ujawniac" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nPrzez jakis czas ty wraz z nowo poznanym znajomym lezeliscie wsrod listowia, jednak po chwili zostaliscie zauwazeni i pochwyceni.\nPatrol zabral was bezposrednio do Miasta Kolonialniego, gdzie nazajutrz mieliscie stanac przed sadem." << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			aktual_scena = 7;

			break;

		case 3:
			SetConsoleTextAttribute(kolor, 2);
			cout << "\n\nSam nie sadzilem ze oni zapuszczaja sie na te tereny, ale...Slyszysz?" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nZ glebi lasu dalo sie slyszec rozmowe grupy ludzi" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\nTo patrol Zakonu Swietego Ryszarda, lepiej sie nie ujawniac" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nPrzez jakis czas ty wraz z nowo poznanym znajomym lezeliscie wsrod listowia, jednak po chwili zostaliscie zauwazeni i pochwyceni.\nPatrol zabral was bezposrednio do Miasta Kolonialniego, gdzie nazajutrz mieliscie stanac przed sadem." << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 8);
			aktual_scena = 7;

			break;


		}
	}
}
void s62walka()
{
	if (aktual_scena == 6) {

		save_write(aktual_scena);   //automatic saving of the game state to a file
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\n\nPoprawnie zapisano postepy." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\nPrzed toba stoi trzech wojownikow Hordy Ciemnosci. Przeciwnik z lewej jest uzbrojony w miecz i tarcze, ten w srodku jest masywny i posada dwureczny topor, a ten z prawej trzyma naprezony luk.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		int walka = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\nDecydujesz sie:\n1)zaatakowac tego po lewej\n2)Zaatakowac tego w srodku\n3)Zaatakowac tego po prawej\n" << endl;
			cin >> walka;
			system("cls");
			if ((walka != 1) && (walka != 2) && (walka != 3)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((walka != 1) && (walka != 2) && (walka != 3));
		switch (walka) {
		case 1:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nTwoj cios zostal zablokowany przez jego tarcze. Twoje plecy zostaja przeszyte przez strzale, a glowa roztrzaskana toporem" << endl;
			SetConsoleTextAttribute(kolor, 12);
			cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
			aktual_scena = 0;   //back to MENU

			break;

		case 2:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nUdaje ci sie zadac cios, jednak twoj kilof utknal w ciele wroga. Juz zegnasz sie z zyciem, widzac strzale lecaca w twoja strone, lecz zostaje ona zablokowana. Na ratunek przybywa ci jeden ze skazancow, ktorzy przetrwali. Po pokonaniu przeciwnikow razem udajecie sie w strone lasu.\n" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			aktual_scena = 5;   //go to LAS

			break;

		case 3:
			SetConsoleTextAttribute(kolor, 7);
			cout << "\n\nZabijasz przeciwnika z lukiem, jednak reszta rzuca sie na ciebie, a twoje cialo zostaje przebite mieczem i toporem." << endl;
			SetConsoleTextAttribute(kolor, 12);
			cout << "\n\nGAME OVER\n\n\n\n\n" << endl;
			aktual_scena = 0;   //back to MENU

			break;
		}
	}
}
void s7()
{
	if (aktual_scena == 7) {

		save_write(aktual_scena);   //automatic saving of the game state to a file
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\n\nPoprawnie zapisano postepy." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 12);
		cout << "\n\n\n\n\nROZDZIAL I\n\n\n" << endl;
		SetConsoleTextAttribute(kolor, 7);
		cout << "Prowadzeni w lancuchach Ty i twoj nowo poznany towarzysz broni docieracie do szalupy wieziennej jednego z krolewskich statkow.\nWaszym celem jest Wielkie Miasto Kolonialne, powszechnie uznawane za stolice Wysp Macierzystych Tzaryatu.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "Podczas rozbrzmiewania szumu fal rozmyslasz o swoim losie oraz pelnym ostatnio niespodziewanych zwrotow akcji zyciu. Z prostego czlowieka\ntrudzacego sie handlem zostales skazany za zabojstwo i wywieziony do Kolonii Karnej, nastepnie toczyles walke o przetrwanie\nw tej przerazajacej rzeczywistosci, potem doszlo do najazdu Hord Ciemnosci i rozpetanie batalii o wlasne zycie,\nkonczac na schwytaniu przez patrol Zakonu sw. Ryszarda.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "Patrzysz przez bulaj i ku twoim oczom ukazuje sie nieziemski widok. Ostoja sprawiedliwosci, przyczolek ludzkosci, emblemat kultury i sztuki,\nduma wspolczesnej architektury, miejsce wybrane przez bogow, potega wojskowa, wrecz najczystsza perla wsrod perel, Wielkie Miasto Kolonijne.\nDobijacie do tetniacego zyciem portu. Otaczajace Cie magazyny, punkty sprzedazy, zaklady przemyslowe oraz domy towarowe stanowia glowna czesc\ngalezi handlowej miasta. Z kolei cumujace armady oraz flotylle wszelkiego rodzaju okretow wojskowych, fregat czy karaweli daja ci do zrozumienia\nz jaka potaga militarna masz do czynienia.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "Wychodzisz ze statku wraz z przyjacielem oraz gromada rycerzy zakonnych i kierujecie sie powoli w strone Fortecy na przesluchanie. Opuszczajac port,\nprzechodzisz przez pierwsze warstwy murow i docierasz do podgrodzia. W trakcie tulaczki przygladasz sie rozradowanym mieszkancom, ktorzy z usmiechami\npracuja na rozwinietych polach uprawnych oraz hodowlach zwierzat. Uliczki oraz chatki wiesniakow sa utrzymane w doskonalym stanie.\nNagle przychodzi ci na mysl jak to miejsce bardzo sie rozni od Kolonii Karnej, w ktorej dane bylo ci spedzic najgorsze dni twego zycia.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "Pokonujesz kolejne mury, tym razem wyposazone w dziesiec murowanych baszt oraz dwadziescia wiez strzelniczych zabezpieczonych blankami. Wchodzisz do miasta. Rozgladasz sie. Wyczuwasz zapach swiezo palonej gliny w zakladach ceglarzy i przygladasz sie wspanialym wyrobom doswiadczonych kamieniarzy krolestwa.\nIdac dalej w glab przygladasz sie ciezkiej pracy kowali wykuwajacych najwspanialsze bronie dla rycerstwa Zakonu sw. Ryszarda.\nZaraz obok dostrzegasz przeprowadzane doswiadczenia oraz zachodzace reakcje chemiczne w laboratoriach krolestwa, ktore wspolpracuja z doskonale wyposazonymi ludwisarniami, produkujacymi potezne armaty. Docierasz do glownego skrzyzowania, lecz Plac Centralny dostrzegasz tylko katem oka,\ngdyz idacy za toba rycerz w pogardliwy sposob zmusza cie do nie zatrzymywania sie. Stojace wozy handlowe, rozlegly tlum gawiedzi,\nnadworni komicy oraz wszelakiego rodzaju atrakcje rozrywkowe podkreslaja donioslosc tego miejsca.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "Idac przed siebie mijasz dzielnice naukowa pelna bibliotek, kryjacych wiedze starozytnych cywilizacji, mase uniwersytetow ksztalcacych dzisiejsza mlodziez\noraz niepojete przez ciebie astrolabia. Kolejna dzielnica, przez ktora przechodzisz jest bogata dzielnica biznesowa.\nOgrom bankow, skarbcow, gield, targowisk, kantorow walutowych klania sie twoim oczom. Mozna rzecz, ze w tym miejscu papiery wartosciowe\noraz pieniadze walaja sie wrecz po ziemi. Tutaj jednak ma miejsce ciagla walka z czasem, pracownicy biznesowi nie maja lekko.\nNie majac czasu na dluzsze ogledziny idziesz dalej. Dostrzegasz powoli zarysy Marmurowej Fortecy zakonu, ale przed nia stoi jeszcze dzielnica kulturowa.\nNigdy wczesniej nie bylo ci dane zobaczyc tak z twojej perspektywy smiesznie ubranej arystokracji. Jest to miejsce rozmow, spacerow oraz spedzania czasu\nwyzszych warstw spolecznych do ktorych naleza margrabiowie, baronowie, hrabiowie, markizy oraz ksiazeta. Tutaj powstaja wszelakie dziela malarskie,\npismienne oraz muzyczne. To tu muzea sa przepelnione znaleziskami archeologicznymi. Tutaj egzystuja pod mecenatem arystokracji najbardziej cenieni\ni znani tworcy sztuki. Twoje napawanie sie pieknem dzielnicy i zachwyt przerwal znow podirytowany juz toba straznik targajac cie do przodu.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "Dotarles do koñca miasta i ze zdumieniem dostrzegasz, ze Forteca znajduje sie na osobnej wyspie oddzielonej od glownej wyspy ciesnina Kuzynova.\nObie wyspy sa jednak polaczone swietnie bronionym kamiennym mostem. Dotarlszy do glownej bramy strzegacej wejscia na wyspe sw. Ryszarda\nprzed twymi oczyma wylania sie wspanialy widok. Ta lokacja zdaje sie byc nieskazitelnie piekna. Ogrom budynkow wojskowych, kapliczek oraz kosciolow\njest przycmiony absolutnie niesamowitym widokiem Katedry Zakonu sw. Ryszarda. Styl gotycki wyrozniajacy sie marmurowymi, strzelistymi wiezyczkami,\nolbrzymi, w kolorach teczy witraz promieniujacy blaskiem, dwanascie tympanonow, wyrzezbione dzwonnice oraz olsniewajace luki wprowadzaja cie w zachwyt.\nNie sadziles ze liczebnosc braci zakonnych modlacych sie wraz z prowadzacymi rozmowy rycerzami przebije tlum gawiedzi spotykajacy sie na rynku glownym\nw miescie. Mijajac najpiekniejsze miejsce Wielkiego Miasta Kolonijnego, calkowicie wyczerpany, ledwo ustajesz na nogach przed wrotami mosieznej\nFortecy Zakonnej na Wzgorzu. Mimo pieknych zdobien i lekko powiewajacych sztandarow Zakonu ta lokalizacja napawa cie przerazeniem.\nW koncu nie przybyles tu jako gosc, ale jako jeniec, oczekujacy na przesluchanie." << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
		SetConsoleTextAttribute(kolor, 7);
		cout << "\n\n\nZnajdujesz sie w malej, ciasnej i ciemnej celi. Lezysz na przegnitym sianie, a na scianach widac grzyb. Po chwili do srodka lochu wchodza straznicy\ni przetransportowuja cie do wielkiej sali, gdzie zebral sie sad, ktory zadecyduje co sie z toba stanie. Obok ciebie stoi Taul.\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");
	R000:
		SetConsoleTextAttribute(kolor, 2);
		cout << "\n\n[Sedzia] - Jak uciekliscie z Koloni Karnej?" << endl;
		int r001 = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n[TY]:\n1)Podczas ataku\n2)Nie twoja sprawa\n" << endl;
			cin >> r001;
			system("cls");
			if ((r001 != 1) && (r001 != 2)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((r001 != 1) && (r001 != 2));
		switch (r001) {
		case 1:
			aktual_scena = 8;   ///go to point R001
			break;
		case 2:
			aktual_scena = 8;  ///go to point R001
			break;
		}
	}
}
void s8()
{
	if (aktual_scena == 8) {
		SetConsoleTextAttribute(kolor, 2);
		cout << "\n\n[Sedzia] - Dlaczego uciekliscie?" << endl;
		int r002 = 0;
		do { //protection against entering an invalid value
			SetConsoleTextAttribute(kolor, 3);
			cout << "\n\n[TY]:\n1)Jedyny sposob by przetrwac atak\n2)Nie twoja sprawa\n" << endl;
			cin >> r002;
			system("cls");
			if ((r002 != 1) && (r002 != 2)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
			}
		} while ((r002 != 1) && (r002 != 2));

		switch (r002) {

		case 1:
			SetConsoleTextAttribute(kolor, 2);
			cout << "\n\n[Sedzia] - Jaki atak?" << endl;
			int r003 = 0;
			do { //protection against entering an invalid value
				SetConsoleTextAttribute(kolor, 3);
				cout << "\n\n[TY]:\n1)Hordy Ciemnosci\n2)Nie twoja sprawa\n" << endl;
				cin >> r003;
				system("cls");
				if ((r003 != 1) && (r003 != 2)) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
			} while ((r003 != 1) && (r003 != 2));
			switch (r003) {
			case 1:
			R012:
				SetConsoleTextAttribute(kolor, 2);
				cout << "\n\n[Sedzia] - Chyba nie sadzisz ze w to uwierzymy? Horda Ciemnosci nie zapuszcza sie tak " << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 3);
				cout << "\n\n[TY]:\n1)To byla rzez!\n2)Skoro nie wierzycie to po co pytacie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				int r004;
				cin >> r004;
				do { //protection against entering an invalid value
					SetConsoleTextAttribute(kolor, 3);
					cout << "\n\n[TY]:\n1)Hordy Ciemnosci\n2)Nie twoja sprawa\n" << endl;
					cin >> r003;
					system("cls");
					if ((r004 != 1) && (r004 != 2)) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				} while ((r004 != 1) && (r004 != 2));

				switch (r004) {
				case 1: {
					aktual_scena = 9;
					break;
				}
				case 2: {
					aktual_scena = 10;
					break;
				}
				}



			}
		}
	}
}
void s9()
{
	if (aktual_scena == 9) {
		SetConsoleTextAttribute(kolor, 12);
		cout << "\nGRATULACJE UDALO CI SIE PRZEJSC WERSJE DEMONSTRACYJNA GRY\n" << endl;
		system("pause");
		system("cls");
		aktual_scena = 0;
	}
}
void s10()
{
	if (aktual_scena == 10) {
		SetConsoleTextAttribute(kolor, 2);
		cout << "\n\n[Sedzia] - W takim razie zawisniesz!" << endl;
		SetConsoleTextAttribute(kolor, 12);
		cout << "\n\nGAME OVER\n\n\n" << endl;
		system("pause");
		system("cls");
		aktual_scena = 0;
	}
}



//function that generates a pseudo-random number in the range from a to b
unsigned int rand_int_fromto(int a, int b) {
	return (rand() % (b - a)) + a;
}
//game loading function
int save_read(void) {
	FILE* save_fd;  //game state file descriptor
	unsigned int i, stan_gry;   //variable with the state of the game which must be positive!

	stan_gry = 0; //initial state of the game
	save_fd = fopen(SAVE_FILE, "rb");   //open game save file, r-open save-only file, b-binary saved file
	if (save_fd == NULL) {  //when the save file does not exist
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\nBlad! Nie znaleziono zapisu stanu gry.\n\n" << endl;
		system("pause");
		return stan_gry;    //game_state stan_gry = start
	}
	for (i = 0; i < 11; i++) {   //a loop that reads 11 numbers from a save game file
		fread(&stan_gry, sizeof(stan_gry), 1, save_fd); //reading a single number
	}

	stan_gry = (stan_gry - 2793) / 3;   //decryption of the saved game state
	fclose(save_fd);    //closing the file
	return stan_gry;    //the loaded state of the game is returned
}

void save_write(unsigned int stan_gry) {
	FILE* save_fd;  //game state file descriptor
	unsigned int i, liczba;

	save_fd = fopen(SAVE_FILE, "w+b");  //save the game to a file, w+-overwrites the previous text, if there is no file, creates it, b-file saved in binary
	if (save_fd == NULL) {  //when the save file does not exist
		SetConsoleTextAttribute(kolor, 5);
		cout << "\n\nBlad zapisu stanu gry!" << endl;
		return;
	}
	for (i = 0; i < 20; i++) {  //system of protection against forgery of game files - saves 20 pseudo-random numbers, of which the 11th number is a transformed state of the game
		if (i == 10) {
			liczba = 2793 + (stan_gry * 3); //game state encryption
		}
		else {
			liczba = rand_int_fromto(1, 10000); //generating pseudo-random numbers
		}
		fwrite(&liczba, sizeof(liczba), 1, save_fd);    //saving the number to the game save file
	}
	fclose(save_fd);    //close the game file
}

int losowanie_walki() {
	int a = 0;
	int wynik = rand_int_fromto(0, 100); //drawing a number from 0 to 100
	if (wynik < 54) {

		losowanie_przeciwnika(a);

	}
	else if (wynik > 85) {
		a = 3;
		losowanie_przeciwnika(a);
	}
}
//Draw an opponent
int losowanie_przeciwnika(int a) {
	int kolumn, statystyki;
	if (a != 3) a = rand_int_fromto(0, 8);
	string enemy;
	string bohater = "Wojownik";

	switch (a) {
	case 0:
		kolumn = 0;
		enemy = "Wilka";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez wilka\n" << endl;
		cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika przed walka?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));
		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
		}
		break;
	case 1:
		kolumn = 1;
		enemy = "Wilki";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez wilki\n" << endl;
		cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2))
			{
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		break;
	case 2:
		kolumn = 2;
		enemy = "Niedzwiedz";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez niedzwiedzia\n" << endl;
		cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");

		do {
			if ((statystyki != 1) && (statystyki != 2))
			{
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
	case 3:
		kolumn = 3;
		enemy = "Zboje";
		SetConsoleTextAttribute(kolor, 6);
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez gromade zboji\n" << endl;
		cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		break;
	case 4:
		kolumn = 4;
		enemy = "Zboj";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez zboja\n" << endl;
		cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		break;
	case 5:
		kolumn = 5;
		enemy = "Legendarny Lolik";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez Legendarnego Lolika\n" << endl;
		cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		break;
	case 6:
		kolumn = 6;
		enemy = "Bezimienny";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez Bezimiennego" << endl;
		cout << "\nCzy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n 1)TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		break;
	case 7:
		kolumn = 7;
		enemy = "Ktos";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez Kogos" << endl;
		cout << "\nCzy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		break;
	case 8:
		kolumn = 8;
		enemy = "Nieznana Postac";
		cout << "\nW trakcie twojej wyprawy zostales zaatakowany z nienadzka przez Nieznana Postac" << endl;
		cout << "\nCzy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		system("cls");
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy chcesz sprawdzic statystyki przeciwnika?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
				system("cls");
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << wrog[kolumn][0] << endl;
			cout << "\nPancerz = " << wrog[kolumn][1] << endl;
			cout << "\nAtak = " << wrog[kolumn][2] << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}
		else if (statystyki == 2) {
			cout << "\n" << endl;
			system_walki(kolumn, 0, enemy, bohater);
			break;
		}

	}
}

int system_walki(int kolumn, int kolumnB, string enemy, string bohater) {
	int wybor, DEFb2, ATKb2, HPb2, HPw, DEFw, ATKw, HPb, DEFb, ATKb, i;
	//enemy stats
	HPw = wrog[kolumn][0];
	DEFw = wrog[kolumn][1];
	ATKw = wrog[kolumn][2];
	//hero stats
	HPb = boh[kolumnB][0];
	DEFb = boh[kolumnB][1];
	ATKb = boh[kolumnB][2];
	SetConsoleTextAttribute(kolor, 8);
	system("pause");
	system("cls");
	SetConsoleTextAttribute(kolor, 6);

	//ratio based on the class of the hero
	if ((bohater == "Wojownik") && (3 >= kolumn)) {
		ATKb2 = ATKb + 1;
		DEFb2 = DEFb + 1;
		HPb2 = HPb;
	}
	else if ((bohater == "Wojownik") && (kolumn > 3)) {
		ATKb2 = ATKb;
		DEFb2 = DEFb;
		HPb2 = HPb;
	}
	// security in statistics
	if (DEFb2 >= ATKw) {
		ATKw = 2;
		DEFb2 = 1;
	}
	if (DEFw >= ATKb) {
		ATKb = 2;
		DEFb = 1;
	}
	//turn selection
	if (rand_int_fromto(0, 10) <= 4) {
		SetConsoleTextAttribute(kolor, 6);
		cout << "\n" << bohater << " atakuje jako pierwszy\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		do {
			if ((HPw > 0) || (HPb2 > 0)) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\n\nDecydujesz sie:\n\n 1) Uderzyc przeciwnika w glowe \n 2) Uderzyc przeciwnika w tulow\n" << endl;
				cin >> wybor;
				system("cls");

				do {
					if ((wybor != 1) && (wybor != 2))
					{
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n\nDecydujesz sie:\n\n 1) Uderzyc przeciwnika w glowe \n 2) Uderzyc przeciwnika w tulow\n" << endl;
						cin >> wybor;
						system("cls");
					}
				} while ((wybor != 1) && (wybor != 2));

				if (wybor == 1) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nAtakujesz przeciwnika w glowe\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
					if (rand_int_fromto(0, 10) > 7) {
						ATKb2 += 2;
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nTrafienie krytyczne! " << enemy << " obecnie posiada: " << HPw << "Hp\n" << endl;
						ATKb2 = ATKb;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						if (HPw <= 0) {
							break;
						}
					}
					else {
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 6);
						cout << "\nUdalo ci sie trafic wroga! " << enemy << " obecnie posiada: " << HPw << "Hp\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						if (HPw <= 0) {
							break;
						}
					}
					if (HPw > 0) {
						for (i = 0; i < 3; i++) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n...\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
						}
						wybor = rand_int_fromto(0, 2);
						if (wybor == 0) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n" << enemy << " wyprowadza atak w glowe!\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
							for (i = 0; i < 3; i++) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\n...\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
							if (rand_int_fromto(0, 10) > 7) {
								ATKw += 2;
								HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
								SetConsoleTextAttribute(kolor, 12);
								cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

								ATKw = wrog[kolumn][2];

								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								SetConsoleTextAttribute(kolor, 6);
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}
							else {
								HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

								SetConsoleTextAttribute(kolor, 6);
								cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}

						}
						else if (wybor == 1) {

							for (i = 0; i < 3; i++) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\n...\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}

							SetConsoleTextAttribute(kolor, 6);
							cout << "\n" << enemy << " wyprowadza atak w tulow\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
							for (i = 0; i < 3; i++) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\n...\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
							if (rand_int_fromto(0, 10) >= 9) {
								ATKw += 2;
								HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
								SetConsoleTextAttribute(kolor, 12);
								cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

								ATKw = wrog[kolumn][2];

								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}
							else {
								HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

								SetConsoleTextAttribute(kolor, 6);
								cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}


						}
						else if (wybor == 2) {
							SetConsoleTextAttribute(kolor, 8);
							cout << enemy << " wyprowadza atak w nogi\n" << endl;
							if (rand_int_fromto(0, 10) >= 10) {
								ATKw += 3;
								HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
								SetConsoleTextAttribute(kolor, 12);
								cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

								ATKw = wrog[kolumn][2];

								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}
							else {
								HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

								SetConsoleTextAttribute(kolor, 6);
								cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}

						}
					}
				}
				else if (wybor == 2) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nAtakujesz przeciwnika w tulow\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
					if (rand_int_fromto(0, 10) >= 9) {
						ATKb2 += 2;
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 6);
						cout << "\nTrafienie krytyczne! " << enemy << " obecnie posiada: " << HPw << "Hp\n" << endl;
						ATKb2 = ATKb;
						SetConsoleTextAttribute(kolor, 8);

						system("pause");
						system("cls");

						if (HPw <= 0) {
							break;
						}
					}
					else {
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 6);
						cout << "\nUdalo ci sie trafic wroga! " << enemy << "  obecnie posiada: " << HPw << "Hp\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						if (HPw <= 0) {
							break;
						}
					}


					if (HPw > 0) {
						for (i = 0; i < 4; i++) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n...\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
						}

						wybor = rand_int_fromto(0, 2);

						if (wybor == 0) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n" << enemy << " wyprowadza atak w glowe!\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
							for (i = 0; i < 3; i++) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\n...\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
							if (rand_int_fromto(0, 10) > 7) {
								ATKw += 2;
								HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
								SetConsoleTextAttribute(kolor, 12);
								cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

								ATKw = wrog[kolumn][2];

								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");

								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 4; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}
							else {
								HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

								SetConsoleTextAttribute(kolor, 6);
								cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");

								if (HPb2 <= 0) {
									break;
								}

								for (i = 0; i < 4; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}

						}
						else if (wybor == 1) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n" << enemy << " wyprowadza atak w tulow\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							for (i = 0; i < 3; i++) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\n...\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}

							if (rand_int_fromto(0, 10) >= 9) {
								ATKw += 2;
								HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
								SetConsoleTextAttribute(kolor, 12);
								cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

								ATKw = wrog[kolumn][2];

								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}

								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}
							else {
								HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

								SetConsoleTextAttribute(kolor, 6);
								cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 3; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}


						}
						else if (wybor == 2) {

							SetConsoleTextAttribute(kolor, 6);
							cout << "\n" << enemy << " wyprowadza atak w nogi\n" << endl;
							for (i = 0; i < 3; i++) {
								SetConsoleTextAttribute(kolor, 6);
								cout << "\n...\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
							}
							if (rand_int_fromto(0, 10) >= 10) {
								ATKw += 3;
								HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
								SetConsoleTextAttribute(kolor, 12);
								cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;
								ATKw = wrog[kolumn][2];

								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 4; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}
							else {
								HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

								SetConsoleTextAttribute(kolor, 6);
								cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
								SetConsoleTextAttribute(kolor, 8);
								system("pause");
								system("cls");
								if (HPb2 <= 0) {
									break;
								}
								for (i = 0; i < 4; i++) {
									SetConsoleTextAttribute(kolor, 6);
									cout << "\n...\n" << endl;
									SetConsoleTextAttribute(kolor, 8);
									system("pause");
									system("cls");
								}
							}

						}
					}
				}
			}
		} while ((HPw > 0) || (HPb2 > 0));

	}
	else {
		system("cls");
		SetConsoleTextAttribute(kolor, 6);
		cout << "\n" << enemy << " atakuje jako pierwszy\n" << endl;
		SetConsoleTextAttribute(kolor, 8);
		system("pause");
		system("cls");

		for (i = 0; i < 3; i++) {
			SetConsoleTextAttribute(kolor, 6);
			cout << "\n...\n" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
		}
		do {
			wybor = rand_int_fromto(0, 2);
			if (wybor == 0) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\n" << enemy << " wyprowadza atak w glowe!\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				for (i = 0; i < 3; i++) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\n...\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
				if (rand_int_fromto(0, 10) > 7) {
					ATKw += 2;
					HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
					SetConsoleTextAttribute(kolor, 12);
					cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

					ATKw = wrog[kolumn][2];

					if (HPb2 <= 0) {
						break;
					}

					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					SetConsoleTextAttribute(kolor, 6);
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				}
				else {
					HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

					SetConsoleTextAttribute(kolor, 6);
					cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					if (HPb2 <= 0) {
						break;
					}
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				}

			}
			else if (wybor == 1) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\n" << enemy << " wyprowadza atak w tulow\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				for (i = 0; i < 3; i++) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\n...\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
				if (rand_int_fromto(0, 10) >= 9) {
					ATKw += 2;
					HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
					SetConsoleTextAttribute(kolor, 12);
					cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;

					ATKw = wrog[kolumn][2];

					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				}
				else {
					HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

					SetConsoleTextAttribute(kolor, 6);
					cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					if (HPb2 <= 0) {
						break;
					}
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				}


			}
			else if (wybor == 2) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\n" << enemy << " wyprowadza atak w nogi\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				for (i = 0; i < 3; i++) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\n...\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
				}
				if (rand_int_fromto(0, 10) >= 10) {
					ATKw += 3;
					HPb2 = HPb - (ATKw - ((DEFb2) * 4) / 5);
					SetConsoleTextAttribute(kolor, 12);
					cout << "\nTrafienie krytyczne! Posiadasz obecnie:" << HPb2 << " Hp\n" << endl;
					ATKw = wrog[kolumn][2];

					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					if (HPb2 <= 0) {
						break;
					}
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				}
				else {
					HPb2 = HPb2 - (ATKw - ((DEFb2) * 4) / 5);

					SetConsoleTextAttribute(kolor, 6);
					cout << "\nOtrzymales obrazenia od wroga! Posiadasz obecnie: " << HPb2 << "Hp\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					if (HPb2 <= 0) {
						break;
					}
					for (i = 0; i < 4; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
				}

			}
			if (HPb2 > 0) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\n\nDecydujesz sie:\n\n 1) Uderzyc przeciwnika w glowe \n 2) Uderzyc przeciwnika w tulow\n" << endl;
				cin >> wybor;
				system("cls");
				do {
					if ((wybor != 1) && (wybor != 2))
					{
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n\nDecydujesz sie:\n\n 1) Uderzyc przeciwnika w glowe\n 2) Uderzyc przeciwnika w tulow\n" << endl;
						cin >> wybor;
						system("cls");
					}
				} while ((wybor != 1) && (wybor != 2));

				if (wybor == 1) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nAtakujesz przeciwnika w glowe\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
					if (rand_int_fromto(0, 10) > 7) {
						ATKb2 += 2;
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nTrafienie krytyczne! Przeciwnik obecnie posiada: " << HPw << " Hp\n" << endl;
						ATKb2 = ATKb;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
						if (HPw <= 0) {
							break;
						}
						for (i = 0; i < 3; i++) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n...\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
						}
					}
					else {
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 6);
						cout << "\nUdalo ci sie trafic wroga! Przeciwnik obecnie posiada: " << HPw << " Hp\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");

						if (HPw <= 0) {
							break;
						}

						for (i = 0; i < 3; i++) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n...\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
						}
					}

				}
				else if (wybor == 2) {
					SetConsoleTextAttribute(kolor, 6);
					cout << "\nAtakujesz przeciwnika w tulow\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					for (i = 0; i < 3; i++) {
						SetConsoleTextAttribute(kolor, 6);
						cout << "\n...\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");
					}
					if (rand_int_fromto(0, 10) >= 9) {
						ATKb2 += 2;
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 12);
						cout << "\nTrafienie krytyczne! Przeciwnik obecnie posiada: " << HPw << "Hp\n" << endl;
						ATKb2 = ATKb;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");

						if (HPw <= 0) {
							break;
						}
						for (i = 0; i < 3; i++) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n...\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
						}
					}
					else {
						HPw = HPw - (ATKb2 - ((DEFw) * 4) / 5);
						SetConsoleTextAttribute(kolor, 6);
						cout << "\nUdalo ci sie trafic wroga! Przeciwnik obecnie posiada: " << HPw << "Hp\n" << endl;
						SetConsoleTextAttribute(kolor, 8);
						system("pause");
						system("cls");

						if (HPw <= 0) {
							break;
						}

						for (i = 0; i < 3; i++) {
							SetConsoleTextAttribute(kolor, 6);
							cout << "\n...\n" << endl;
							SetConsoleTextAttribute(kolor, 8);
							system("pause");
							system("cls");
						}
					}
				}
			}
		} while ((HPw > 0) || (HPb2 > 0));
	}

	if (HPw <= 0) {
		boh[kolumnB][0] = HPb + 1;
		boh[kolumnB][1] = DEFb + 1;
		boh[kolumnB][2] = ATKb + 1;
		int statystyki;
		if (enemy == "Bezimienny") {
			SetConsoleTextAttribute(kolor, 12);
			cout << "\nTak konczy sie, gdy mylisz gry w ktorych wystepujesz. Nawet twoje towary cie nie uratuja" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
		}
		SetConsoleTextAttribute(kolor, 10);
		cout << "\nGratulacje, udalo ci sie pokonac przeciwnika, w nagrode zdobywasz dodatkowy lvl!" << endl;
		SetConsoleTextAttribute(kolor, 6);
		cout << "\nCzy wyswietlic aktualne statystyki?\n\n 1) TAK\n 2) NIE\n" << endl;
		cin >> statystyki;
		do {
			if ((statystyki != 1) && (statystyki != 2)) {
				SetConsoleTextAttribute(kolor, 12);
				cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				SetConsoleTextAttribute(kolor, 6);
				cout << "Czy wyswietlic aktualne statystyki?\n\n 1) TAK\n 2) NIE\n" << endl;
				cin >> statystyki;
			}
		} while ((statystyki != 1) && (statystyki != 2));

		if (statystyki == 1) {
			cout << "\nHP = " << boh[kolumnB][0] << endl;
			cout << "\nPancerz = " << boh[kolumnB][1] << endl;
			cout << "\nAtak = " << boh[kolumnB][2] << endl;
			system("pause");
			return boh[kolumnB][0], boh[kolumnB][1], boh[kolumnB][2];
		}
		else if (statystyki == 2) {
			return boh[kolumnB][0], boh[kolumnB][1], boh[kolumnB][2];
		}

	}
	if (HPb2 <= 0) {
		boh[kolumnB][0] = HPb - 1;
		if (DEFb > 1)	boh[kolumnB][1] = DEFb - 1;
		if (ATKb > 1) boh[kolumnB][2] = ATKb - 1;

		if (boh[kolumnB][0] <= 0) {
			SetConsoleTextAttribute(kolor, 12);
			cout << "\nNiestety nie udaje ci sie. Zostajesz zabity." << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			system("cls");
			SetConsoleTextAttribute(kolor, 4);
			cout << "\nGAME OVER\n\n" << endl;
			SetConsoleTextAttribute(kolor, 8);
			system("pause");
			aktual_scena = 0;
		}
		else {
			SetConsoleTextAttribute(kolor, 6);
			cout << "\nZostales pokonany. Obrazenia otrzymane w trakcie walki cie oslabily.\nCzy chcesz zobaczyc aktualne statystyki?\n\n 1) TAK \n 2) NIE\n" << endl;
			cin >> wybor;
			system("cls");
			do {
				if ((wybor != 1) && (wybor != 2))
				{
					SetConsoleTextAttribute(kolor, 12);
					cout << "\nWybrano zla opcje, sprobuj ponownie\n" << endl;
					SetConsoleTextAttribute(kolor, 8);
					system("pause");
					system("cls");
					SetConsoleTextAttribute(kolor, 6);
					cout << "Czy chcesz zobaczyc aktualne statystyki?\n\n 1) TAK\n 2) NIE\n" << endl;
					cin >> wybor;
				}
			} while ((wybor != 1) && (wybor != 2));

			if (wybor == 1) {
				SetConsoleTextAttribute(kolor, 6);
				cout << "\nHP = " << boh[kolumnB][0] << endl;
				cout << "\nPancerz = " << boh[kolumnB][1] << endl;
				cout << "\nAtak = " << boh[kolumnB][2] << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				return boh[kolumnB][0], boh[kolumnB][1], boh[kolumnB][2];
			}
			else if (wybor == 2) {
				return boh[kolumnB][0], boh[kolumnB][1], boh[kolumnB][2];
			}
		}
	}
}

