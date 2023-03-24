#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SAVE_FILE "game.fdx" ///nazwa pliku z zapisem stanu gry
#define MAX_SCENA 5 ///maksymalna liczba scen

HANDLE kolor; ///zmienna przechowujaca kolor konsoli

///funkcja generujaca liczbe psudolosowa w zakresie od a do b
unsigned int rand_int_fromto (int a, int b){
    int i, liczba_losowa;

    for(i = 0; i < 3; i ++) {   ///petla zwiekszajaca losowosc wygenerowanej liczby
        liczba_losowa = (rand() % b) + a;   ///wylosowanie liczby w zakresie od a do b
    }
    return liczba_losowa;   ///zwrocenie wylosowanej wartosci
}

///funkcja wczytujaca stan gry
int save_read(void) {
    FILE *save_fd;  ///deskryptor pliku stanu gry
    unsigned int i, stan_gry;   ///zmienna ze stanem gry

    stan_gry = 0; ///stan poczatkowy gry
    save_fd = fopen(SAVE_FILE, "rb");   ///otworzenie pliku stanu gry,  r-otwiera plik tylko do zapisu, b-plik zapisany binarnie
    if (save_fd == NULL) {  ///gdy plik z zapisem stanu gry nie istnieje
        SetConsoleTextAttribute(kolor, 5);
        printf ("\n\nBlad! Nie znaleziono zapisu stanu gry.\n\n");
        return stan_gry;    ///zwracamy stan_gry = poczatek
    }
    for (i = 0; i < 11 ; i ++) {   ///petla wczytujaca 11 liczb z pliku zapisu stanu gry
        fread(&stan_gry, sizeof(stan_gry), 1, save_fd); ///wczytywanie pojedynczej liczby
     }

    stan_gry = (stan_gry - 2793) / 3;   ///deszyfracja zapisanego stanu gry
    fclose(save_fd);    ///zamkniecie pliku
    return stan_gry;    ///zwracamy wczytany stan gry
}
///funkcja zapisujaca stan gry
void save_write(unsigned int stan_gry) {
    FILE *save_fd;  ///deskryptor pliku stanu gry
    unsigned int i, liczba;

    save_fd = fopen(SAVE_FILE, "w+b");  ///sapisanie stanu gry w pliku,  w+-nadpisuje poprzedni tekst, jesli nie ma pliku to go tworzy,  b-plik zapisany binarnie
    if (save_fd == NULL) {  ///gdy plik do zapisu stanu gry nie istnieje
        SetConsoleTextAttribute(kolor, 5);
        printf("\n\nBlad zapisu stanu gry!");
        return;
    }
    for (i = 0; i < 20; i ++) {  ///system zabezpieczen przeciw falszowaniu plikow stanu gry - zapisuje 20 liczb pseudolosowych, z czego 11 liczba to przeksztalcony stan gry
        if (i == 10) {
            liczba = 2793 + (stan_gry * 3); ///szyfrowanie stanu gry
        } else {
            liczba = rand_int_fromto(1, 10000); ///wygenerowanie liczb pseudolosowych
        }
        fwrite(&liczba, sizeof(liczba), 1, save_fd);    ///zapis liczby do pliku stanu gry
    }
    fclose(save_fd);    ///zamkniecie pliku ze stanem gry
}




int main () {

    unsigned int wynik_walki;

    srand(time(NULL));  ///inicjalizacja generatora liczb pseudolosowych

    ///funkcja implementujaca kolory tekstu w konsoli
    kolor = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( kolor, 12);
    printf("v.0.0.4\n");

    int aktual_scena = 0;   ///zdefiniowanie aktualnej sceny

    ///jesli aktualna_scena = 0 program wyswietla menu glowne
    ///jesli aktualna_scena < 0 program wylacza sie
    ///jesli aktualna_scena > 0 program odtwarza sie dalej

    ///MENU - aktual_scena = 0
    ///PROLOG - aktual_scena = 1
    ///WALKA - aktual_scena = 2
    ///KOPALNIA - aktual_scena = 3
    ///BRAMA - aktual_scenea = 4
    ///LAS - aktual_scena = 5
    ///WALKA2 - aktual_scena = 6
    ///ROZDZIAL I - aktual_scena = 7


    while(aktual_scena>=0){ ///glowna petla do przemieszczania sie po strukturze gry

        while(!aktual_scena){   ///petla menu glownego

            SetConsoleTextAttribute( kolor, 12);
            printf("\n\n\n\n\nWitamy w grze Tzaryat - Text Game\n");
            SetConsoleTextAttribute(kolor,6);
            printf (" \n\n 1)Nowa gra \n 2)Wczytaj gre \n 3)Informacje o tworcach \n 4)Zakoncz przygode\n");

            char wybor;


            do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
            {
                scanf(" %s", &wybor);
                if((wybor!='1')&&(wybor!='2')&&(wybor!='3')&&(wybor!='4')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
            }
            while((wybor!='1')&&(wybor!='2')&&(wybor!='3')&&(wybor!='4'));

            ///zapis && oznacza spójnik i, zapis || oznacza spójnik lub

            switch (wybor) {
                case '1':
                    SetConsoleTextAttribute(kolor,6);
					printf("\nCzy chcesz rozpoczac nowa przygode?\n\n1)TAK\n2)NIE\n");

	                do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
                    {
                        scanf(" %s", &wybor);
                        if((wybor!='1')&&(wybor!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
                    }
                    while((wybor!='1')&&(wybor!='2'));

                    if(wybor=='1') aktual_scena = 1;

					break;

                case '2':
                    aktual_scena = save_read(); ///wczyranie zapisu stanu gry z pliku
                    if(aktual_scena > MAX_SCENA){   ///zabezpieczenie w przypadku uszkodzonego pliku stanu zapisu gry
                        aktual_scena = 0;
                    }
                    break;

                case '3': printf("\n\nGra znajduje się w wersji testowej.\nJezeli cos nie dziala, napisz do nas, a my sie tym zajmiemy:\n[e-mail]\n\n\nProgramisci:\n\nKacper Suder\nHistoria:\n\nMarcin Rzesista\n");
					SetConsoleTextAttribute(kolor,8);
					system("pause");
					break;


                case '4':
					SetConsoleTextAttribute(kolor,6);
					printf("\nPrawdziwy bohater nigdy nie ucieka z pola walki\nCzy chcesz uciec i pokryc sie hanba? \n\n1) Nie, nigdy sie nie poddam!\n2) Jestem tchorzem i uciekam\n\n");

                    do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
                    {
                        scanf(" %s", &wybor);
                        if((wybor!='1')&&(wybor!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
                    }
                    while((wybor!='1')&&(wybor!='2'));

                    if (wybor=='1'){
                        SetConsoleTextAttribute(kolor,2);
                        printf ("\nWybrales honor\n\n");
                    }
                    if (wybor=='2') {
                        SetConsoleTextAttribute( kolor, 12);
                        printf ("\nWybrales ucieczke TCHORZU!!\n");
                        SetConsoleTextAttribute(kolor,8);
                        aktual_scena = -1;
                        return 0;
                    }
                    break;
            }
        }

///PROLOG
if(aktual_scena==1) {

            save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
            SetConsoleTextAttribute(kolor, 5);
            printf("\n\n\nPoprawnie zapisano postepy.");

            SetConsoleTextAttribute( kolor, 12);
            printf ("\n\n\n\n\nPROLOG\n\n\n");
            SetConsoleTextAttribute(kolor,7);
            printf("Zarys fabularny krainy:\n");
            printf("Kolonia na Wyspach Macierzystych Tzaryatu zostala zalozona przez jednego z 5 wielkich mistrzow architektury Kontynetu Nowego Tzaryatu, Ardona.\n15 lat temu w roku 1215 po zalozeniu Wielkiego Miasta Kolonijnego wladze nie byly w stanie poradzic sobie z narastajacym problemem gromadzenia\ncoraz to wiekszej liczby skazancow, mordercow oraz nachalnych przestepcow.\n");
            system("pause");
            printf("Wielki Mistrz Zakonu Swietego Ryszarda nakazal staremu architektowi znalezc miejsce, w ktorym wszelkie zlo bedzie pokutowac za swe czyny.\nPolwysep zwany Cyplem Rakovitza nadawal sie do tego celu doskonale.\n");
            system("pause");
            printf("Od reszty kontynentu oddzielal go potezny Lancuch gorski Fraze Cliffs.\nLegendy mowia, ze najpotezniejsi wladcy demonow maja tam swoje siedziby, a mroczne lasy u jego podnoza zamieszkiwane sa przez najgrozniejsze\npotwory Wysp Macierzystych Tzaryatu.\n");
            system("pause");
            printf("Za lasem rozciagal sie olbrzymi pas rownin i pustkowi, gdzie mieszcza sie zgliszcza po dawniej pelnych zycia wioskach i mniejszych osrodkow miejskich.\nZa rowninami po wschodniej stronie polwyspu rozciagalo sie dosc duze pasmo gorskie polaczone z ciesnina Dardiano, przez co uniemozliwialo przejscie\ndalej polnocnym wschodem, pozostawalo tylko zachodnie przejscie. Gory te byly bogate w zloza rudy zelaza, kamienia oraz wegla, mialy rowniez duzy\npotencjal obronny. Na zachodzie rozpoczynal sie szereg pagorkow oraz pomniejszych wzgorz, wyzynne tereny Narfang z wyniszczalym przez wojne pustkowiem.\n Oddzielona od zachodu przez pasmo gorskie, otoczona przez pogorza dolina byla idealnym miejscem na zalozenie Kolonii Karnej.\n");
            system("pause");
            printf("Na poludniowy wschod doliny rozpociagala sie Gola Ziemia pozbawiona jakiego kolwiek bytu, a za nia urozmaicona linia brzegowa Cyplu Rakovitza,\nz ktorej dostrzec mozna owite mgla zarysy Wielkiego Miasta Kolonijnego.\n");
            system("pause");
            printf("Dolina w sercu polwyspu nazywana byla Dolina Utraconych. Owila wokol tego miejsca legenda opowiadala o wspanialych kopalniach zbudowanych w gorach.\nWydobywano w tej dolinie najlepszej jakosci zelazo, dzieki niemu wojownicy Tzaryatu miało zapewnione najpotezniejsze orze zamieszchlych czasow.\nMieszkancy doliny wybudowali wowczas pierwszy port na polwyspie. Handel kwitl, a mieszkancy zyli szczesliwie I spokojnie.\nDzialo sie to 5 lat przed upadkiem Wysp Macierzystych.\n");
            system("pause");
            printf("\n\nZnajdujesz sie w Kolonii Karnej. Spogladasz za siebie widzac potezny, trzymetrowy, kamienny mur ze strzelistymi wiezyczkami i blankami obronnymi\noraz brame z dwoma szeregami krat zawieszonych szescioma stalowymi lancuchami na kolowrotach. Przygladasz sie przez chwile monumentalnej konstrukcji\noraz rzeszy straznikow piastujacych swoje codzienne obowiazki.\n");
            system("pause");
            printf("\n\nSchodzisz wglab kopalni. Znajdujesz sie w waskiej i ciemnej grocie. W rece trzymasz kilof. Jestes odziany w stare, przetarte, lniane spodnie i koszule.\nNagle ze strony wejscia do sztolni slychac krzyki.");



		char wybor;

		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
        {
            SetConsoleTextAttribute(kolor,3);
            printf ("\n\nDecydujesz sie:\n\n1)Sprawdzic co sie dzieje\n2)Zignorowac to\n");
            scanf(" %s", &wybor);
            if((wybor!='1')&&(wybor!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
        }
        while((wybor!='1')&&(wybor!='2'));

		switch (wybor) {
		    case '1':
		        SetConsoleTextAttribute(kolor,7);
		        printf ("\nPowolnym krokiem przesuwasz sie w strone wyjscia, a z czasem krzyki narastaja. Po chwili wychodzisz na powierzchnie,\na twoim oczom ukazuje sie krajobraz bitwy. Kolonia karna, w ktorej przebywales zostala zaatakowana przez Horde Ciemnosci.\n");

                do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
                {
                    SetConsoleTextAttribute(kolor,3);
                    printf ("\nDecydujesz sie:\n\n1)Stanac do walki z wrogiem\n2)Uciec w glab kopalni\n");
                    scanf(" %s", &wybor);
                    if((wybor!='1')&&(wybor!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
                }
                while((wybor!='1')&&(wybor!='2'));

                switch (wybor) {
                    case '1':
                        SetConsoleTextAttribute(kolor,7);
                        printf ("\n\nStajesz do walki.\n\n");
                        aktual_scena=2;
                        break;
                    case '2':
                        SetConsoleTextAttribute(kolor,7);
                        printf ("\n\nUciekasz w glab kopalni.\n\n");
                        aktual_scena=3;
                        break;
                }

		    case '2':
		        SetConsoleTextAttribute(kolor,7);
		        printf ("\nKrzyki nie ustaja. Nagle slyszysz glos jednego ze skazancow: Ludzie, potwory atakuja!");

		        do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
                {
                    SetConsoleTextAttribute(kolor,3);
                    printf ("\nDecydujesz sie:\n\n1)Stanac do walki z wrogiem\n2)Uciec w glab kopalni\n");
                    scanf(" %s", &wybor);
                    if((wybor!='1')&&(wybor!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
                }
                while((wybor!='1')&&(wybor!='2'));

		        switch (wybor) {
		            case '1':
		                SetConsoleTextAttribute(kolor,7);
		                printf ("\n\nStajesz do walki.\n\n");
		                aktual_scena=2;
		                break;
		            case '2':
		                SetConsoleTextAttribute(kolor,7);
		                printf ("\n\nUciekasz w glab kopalni.\n\n");
		                aktual_scena=3;
		                break;
                }
        }
}


///WALKA
if(aktual_scena == 2){
	save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
    SetConsoleTextAttribute(kolor, 5);
    printf("\n\n\nPoprawnie zapisano postepy.");
	SetConsoleTextAttribute(kolor,7);
    printf ("\n\n\nWychodzisz na dziedziniec, ktory jest pelen skazancow walczacych ramie w ramie ze straznikami przeciwko Hordzie Ciemnosci.\nZauwazasz jednego z nieumarlych, ktory biegnie w strone niczego nie spodziewajacego sie zolnierza.\n");
	char prolog4;
	
	do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
           {
            SetConsoleTextAttribute(kolor,3);
    		printf ("\nDecydujesz sie:\n\n1)Ochronic go\n2)Przebic sie w strone bramy glownej\n");
			 scanf(" %s", &prolog4);
             if((prolog4!='1')&&(prolog4!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
           }
             while((prolog4!='1')&&(prolog4!='2'));
	switch (prolog4) {
        case 1:
            SetConsoleTextAttribute(kolor,7);
            printf ("\nPodbiegasz do przeciwnika i zadajesz mu cios kilofem w:");
            char prolog5;
		   	do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
        {
            SetConsoleTextAttribute(kolor,3);
            printf("\n\n1)Glowe\n2)Tulow\n3)Nogi\n");;
            scanf(" %s", &prolog5);
            if((prolog5!='1')&&(prolog5!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
        }
       	    while((prolog5!='1')&&(prolog5!='2')&&(prolog5!='3'));
            switch (prolog5) {
                case 1:
                    wynik_walki = rand_int_fromto(1, 100);  ///wygenerowanie pseudolosowego wyniku walki
					if (wynik_walki >= 90){
						SetConsoleTextAttribute(kolor,7);
						printf("\n\nUderzenie krytyczne! Wrog pada martwy na ziemie, a ty biegniesz dalej, w strone bramy glownej.\n");
						SetConsoleTextAttribute(kolor,8);
						system("pause");
						aktual_scena = 4;   ///przejscie do BRAMA
						return 0;
            		} else { if (35 < wynik_walki < 85){
 						SetConsoleTextAttribute(kolor,7);
						printf("\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Zdenerwowany, zaczyna biec w twoja strone.\n");
						char prolog6=0;
						
				        do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
						{
							SetConsoleTextAttribute(kolor,3);
		                    printf ("\nPostanawiasz:\n\n1)Uniknac jego ataku w ostatniej chwili odskakujac.\n2)Zostac w miejscu.\n3)Kopnac go\n");
		                    scanf(" %s", &prolog6);
		                    if((prolog6!='1')&&(prolog6!='2')&&(prolog6!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		                }
						while((prolog6!='1')&&(prolog6!='2')&&(prolog6!='3'));
                        switch(prolog6){
                            case 1:
                                SetConsoleTextAttribute(kolor,7);
                                printf("\nNiestety nie udaje ci sie. Zostajesz zabity.\n");
                                SetConsoleTextAttribute(kolor,12);
                                printf("\n\nGAME OVER\n\n\n\n\n");
                                aktual_scena = 0;   ///powrot do MENU
                                break;
                            case 2:
                                SetConsoleTextAttribute(kolor,7);
                                printf("\nNiestety nie udaje ci sie. Zostajesz zabity.\n");
                                SetConsoleTextAttribute(kolor,12);
                                printf("\n\nGAME OVER\n\n\n\n\n");
                                aktual_scena = 0;   ///powrot do MENU
                                break;
                            case 3:
                                SetConsoleTextAttribute(kolor,7);
                                printf("\nKopiesz go, a ten upada, nadziewajac sie na miecz innego czlowieka. Ty decydujesz sie dotrzec do bramy glownej.\n");
                                aktual_scena = 4;   ///przejscie do BRAMA
                                break;
                            default:
                                SetConsoleTextAttribute(kolor, 8);
                                printf("\nWybrano niewlasciwa komende, sprobuj ponownie\n");
                                SetConsoleTextAttribute(kolor,8);
                                system("pause");
                                break;

                        }

                }   else {
					SetConsoleTextAttribute(kolor,7);
					printf("\nNiestety nie udaje ci sie trafic. Zostajesz zabity.\n");
					SetConsoleTextAttribute(kolor,12);
					printf("\nGAME OVER!\n\n\n\n\n");
					aktual_scena = 0;   ///powrot do menu MENU
				}
				system("pause");
				return 0;
	            break;

        case 2:
                wynik_walki = rand_int_fromto(1, 100);  ///wygenerowanie pseudolosowego wyniku walki
				if (wynik_walki >= 65){
					SetConsoleTextAttribute(kolor,7);
					printf("\n\nUderzenie krytyczne! Wrog pada martwy na ziemie, a ty biegniesz dalej, w strone bramy glownej.\n");
					SetConsoleTextAttribute(kolor,8);
					aktual_scena = 4;   ///przejscie do BRAMA
					system("pause");
					return 0;
           		 } else { if (20 < wynik_walki < 65){
 					SetConsoleTextAttribute(kolor,7);
					printf("\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Zdenerwowany, zaczyna biec w twoja strone.\n");	
				        char prolog6=0;
						do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
						{
							SetConsoleTextAttribute(kolor,3);
		                    printf ("\nPostanawiasz:\n\n1)Uniknac jego ataku w ostatniej chwili odskakujac.\n2)Zostac w miejscu.\n3)Kopnac go\n");
		                    scanf(" %s", &prolog6);
		                    if((prolog6!='1')&&(prolog6!='2')&&(prolog6!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		                }
					while((prolog6!='1')&&(prolog6!='2')&&(prolog6!='3'));
					switch(prolog6){
						case 1:
							SetConsoleTextAttribute(kolor,7);
							printf("\nNiestety nie udaje ci sie. Zostajesz zabity.\n");
							SetConsoleTextAttribute(kolor,12);
							printf("\n\nGAME OVER\n\n\n\n\n");
							aktual_scena = 0;   ///powrot do MENU
							break;
						case 2:
							SetConsoleTextAttribute(kolor,7);
							printf("\nNiestety nie udaje ci sie. Zostajesz zabity.\n");
							SetConsoleTextAttribute(kolor,12);
							printf("\n\nGAME OVER\n\n\n\n\n");
							aktual_scena = 0;   ///powrot do MENU
							break;
						case 3:
							SetConsoleTextAttribute(kolor,7);
							printf("\nKopiesz go, a ten upada, nadziewajac sie na miecz innego czlowieka. Ty decydujesz sie dotrzec do bramy glownej.");
							aktual_scena = 4;   ///przejscie do BRAMA
							SetConsoleTextAttribute(kolor,8);
							system("pause");
							return 0;
							break;
                    }

       			 }   else {SetConsoleTextAttribute(kolor,7);
						printf("\nNiestety nie udaje ci sie trafic. Zostajesz zabity.\n");
						SetConsoleTextAttribute(kolor,12);
						printf("\nGAME OVER!\n\n\n\n\n");
						aktual_scena = 0;   ///powrot do MENU

			}

            break;

        case 3:
            wynik_walki = rand_int_fromto(1, 100);  ///wygenerowanie pseudolosowego wyniku walki
			if (wynik_walki >= 50){
				SetConsoleTextAttribute(kolor,7);
				printf("\n\nUderzenie krytyczne! Wrog pada martwy na ziemie, a ty biegniesz dalej, w strone bramy glownej.\n");
				SetConsoleTextAttribute(kolor,8);
				aktual_scena = 4;   ///przejscie do BRAMA
				system("pause");
				return 0;
            } else { if (10 < wynik_walki < 50){
 				SetConsoleTextAttribute(kolor,7);
				printf("\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Zdenerwowany, zaczyna biec w twoja strone.");
				char prolog6;
				do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
						{
							SetConsoleTextAttribute(kolor,3);
		                    printf ("\nPostanawiasz:\n\n1)Uniknac jego ataku w ostatniej chwili odskakujac.\n2)Zostac w miejscu.\n3)Kopnac go\n");
		                    scanf(" %s", &prolog6);
		                    if((prolog6!='1')&&(prolog6!='2')&&(prolog6!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		                }
					while((prolog6!='1')&&(prolog6!='2')&&(prolog6!='3'));
				switch(prolog6){
					case 1:
						SetConsoleTextAttribute(kolor,7);
						printf("\nNiestety nie udaje ci sie. Zostajesz zabity.");
						SetConsoleTextAttribute(kolor,12);
						printf("\n\nGAME OVER\n\n\n\n\n");
						aktual_scena = 0;   ///powrot do MENU
						break;
					case 2:
						SetConsoleTextAttribute(kolor,7);
						printf("\nNiestety nie udaje ci sie. Zostajesz zabity.");
						SetConsoleTextAttribute(kolor,12);
						printf("\n\nGAME OVER\n\n\n\n\n");
						aktual_scena = 0;   ///powrot do MENU
						break;
					case 3:
						SetConsoleTextAttribute(kolor,7);
						printf("\nKopiesz go, a ten upada, nadziewajac sie na miecz innego czlowieka. Ty decydujesz sie dotrzec do bramy glownej.\n");
						aktual_scena = 4;   ///przejscie do BRAMA
						SetConsoleTextAttribute(kolor,8);
						system("pause");
						return 0;
						break;

				}

        }   else {SetConsoleTextAttribute(kolor,7);
				printf("\nNiestety nie udaje ci sie trafic. Trex cie dopada i zabija.\n");
				SetConsoleTextAttribute(kolor,12);
				printf("\nGAME OVER!\n\n\n\n\n");
				aktual_scena = 0;   ///powrot do MENU
			}
            break;
    }
    }
	}
    }
        case 2:
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nDecydujesz sie przedostac do bramy.\n");
            aktual_scena = 4;   ///przejscie do BRAMA
            SetConsoleTextAttribute(kolor,8);
			system("pause");
            return 0;
            break;
}
}

///BRAMA
if (aktual_scena = 4){
    save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
    SetConsoleTextAttribute(kolor, 5);
    printf("\n\n\nPoprawnie zapisano postepy.");

    SetConsoleTextAttribute(kolor,7);
    printf ("\n\nUdaje ci sie przedostac do bramy, jednak wrota sa zamkniete.\n");

	SetConsoleTextAttribute(kolor,3);
    printf ("\nDecydujesz sie:\n\n1)Przedrzec sie do kolowrotu sterujacego brama\n2)przedostac sie na zewnatrz przez mury\n");
    char brama1;
		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
			{
			SetConsoleTextAttribute(kolor,3);
    		printf ("\nDecydujesz sie:\n\n1)Przedrzec sie do kolowrotu sterujacego brama\n2)przedostac sie na zewnatrz przez mury\n");
		    scanf(" %s", &brama1);
		    if((brama1!='1')&&(brama1!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		    }
	while((brama1!='1')&&(brama1!='2'));
    switch (brama1) {
   		case 1:
       		SetConsoleTextAttribute(kolor,7);
            printf ("\nDocierasz na szczyt bramy i chwytasz za kolowrot, jednak nie jestes w stanie samodzielnie podniesc bramy. Nagle slyszysz kroki za soba.\nOdwracasz sie i widzisz wojownika Hordy Ciemnosci, wyprowadzajacego cios w twoja strone. Wiesz ze to twoj koniec. Zamykasz oczy, czekajac na cios,\njednak on nie nadchodzi. Powoli otwierasz powieki, a twoim oczom ukazuje sie widok innego skazanca, ktory uratowal ci zycie.\nDobrze wiecie co dalej robic. Chwytacie za kolowrot i otwieracie brame. Po kilku chwilach znajdujecie sie juz w glebi lasu.\n");
        	SetConsoleTextAttribute(kolor,8);
            system("pause");
        	aktual_scena = 5;   ///przejscie do LAS

        	break;

    	case 2:
        	SetConsoleTextAttribute(kolor,7);
            printf ("\nWspinasz sie na mury i docierasz na ich szczyt. Nagle slyszysz kroki za soba. Odwracasz sie i widzisz wojownika Hordy Ciemnosci, wyprowadzajacego\ncios w twoja strone. Wiesz ze to twoj koniec. Zamykasz oczy, czekajac na cios, jednak on nie nadchodzi. Powoli otwierasz powieki, a twoim oczom\nukazuje sie widok innego skazanca, ktory uratowal ci zycie. Pomagacie sobie zejsc z murow i uciekacie w glab lasu.\n");
            SetConsoleTextAttribute(kolor,8);
            system("pause");
        	aktual_scena = 5;   ///przejscie do LAS
        	break;
        }
}

///KOPALNIA
if (aktual_scena = 3) {

    save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
    SetConsoleTextAttribute(kolor, 5);
    printf("/n/n/nPoprawnie zapisano postepy.");


    SetConsoleTextAttribute(kolor,7);
    printf ("\n\nSchodzisz w glab kopalni w nadziei, ze wrog cie nie znajdzie. Po kilku godzinach siedzenia w ciemnosci wszelkie dzwieki cichna. Zdajesz sie slyszec kroki z glebi korytarza jednak szybko rozpoznajesz je jako nieludzkie...");

    char kopalnia1;
	do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
		{
		SetConsoleTextAttribute(kolor,3);
    	printf ("\nDecydujesz sie:\n1)Ukryc wewnatrz szybu\n2)Ominac zagrozenie bocznym korytarzem\n3)Stawic czolo zagrozeniu");
		scanf(" %s", &kopalnia1);
		if((kopalnia1!='1')&&(kopalnia1!='2')&&(kopalnia1!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		}
	while((kopalnia1!='1')&&(kopalnia1!='2')&&(kopalnia1!='3'));	
    switch (kopalnia1) {
    	case 1:
       		SetConsoleTextAttribute(kolor,7);
       		printf ("\n\nWchodzisz do szybu i wisisz na linie. Tajemnicze kroki zblizaja sie do ciebie. Nagle slyszysz trzask. Lina na ktorej wisisz peka, a ty spadasz kilkanascie metrow w dol i giniesz.\n");
        	SetConsoleTextAttribute( kolor, 12);
        	printf ("\n\n\nGAME OVER\n\n\n\n\n");
        	aktual_scena = 0; ///powrot do MENU
        	break;

    	case 2:
        	SetConsoleTextAttribute(kolor,7);
        	printf ("\n\nOmijasz zagrozenie i wychodzisz na zewnatrz kopalni. Twoim oczom ukazuje sie pogorzelisko na miejscu dziedzinca. Zmierzasz w strone bramy. Nagle slyszysz za soba szelest. Odwracasz sie i widzisz trzech wojownikow Hordy Ciemnosci.\n");
			char kopalnia2;
			do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
				{
					SetConsoleTextAttribute(kolor,3);
				printf ("\nDecydujesz sie:\n1)Uciec\n2)Podjac walke\n");
				scanf(" %s", &kopalnia2);
				if((kopalnia2!='1')&&(kopalnia2!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
				}
			while((kopalnia2!='1')&&(kopalnia2!='2'));
        	switch (kopalnia2) {

				case 1:
	            	SetConsoleTextAttribute(kolor,7);
	            	printf ("\n\nUciekasz w strone bramy, jednak jest zamknieta, jestes zmuszony podjac walke.\n");
                    SetConsoleTextAttribute(kolor,8);
	   				system("pause");
	            	aktual_scena = 6;
	            	break;

				case 2:
	            	SetConsoleTextAttribute(kolor,7);
	            	printf ("\n\nStajesz do walki.\n");
	           		SetConsoleTextAttribute(kolor,8);
	   				system("pause");
	            	aktual_scena = 6;
	            	break;
        }

	    case 3:
	         SetConsoleTextAttribute(kolor,7);
	         printf("\n\nStajesz do walki.");
	      
	         char kopalnia3;
				do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
					{
					SetConsoleTextAttribute(kolor,3);
	         		printf ("\nZadajesz cios w:\n1)Glowe\n2)Tulow\n3)Nogi\n");
					scanf(" %s", &kopalnia3);
					if((kopalnia3!='1')&&(kopalnia3!='2')&&(kopalnia3!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
					}
				while((kopalnia3!='1')&&(kopalnia3!='2')&&(kopalnia3!='3'));
	         switch (kopalnia3) {
                case 1:
                    wynik_walki = rand_int_fromto(1, 100);
                	if (wynik_walki >= 85){
						SetConsoleTextAttribute(kolor,7);
						printf("\n\nUdaje ci sie powalic przeciwnika, co daje ci mozliwosc ucieczki na powierzchnie. Gdzie czeka na ciebie trzech kolejnych wrogow.");
						aktual_scena = 6;   ///przejscie do WALKA2
						getchar();
						return 0;
          		  } else { if (35 < wynik_walki < 65){
 						SetConsoleTextAttribute(kolor,7);
						printf("\n\nUdalo ci sie wyprowadzic atak, jednak przeciwnik nie padl martwy. Wyprowadza atak w twoja strone.");
						char kopalnia4;
						do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
							{
							SetConsoleTextAttribute(kolor,3);
							printf("\nPostanawiasz:\n1)Wykonac unik\n2)Zablokowac cios kilofem\n3)Kopnac go\n");
							scanf(" %s", &kopalnia4);
							if((kopalnia4!='1')&&(kopalnia4!='2')&&(kopalnia4!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
							}
						while((kopalnia4!='1')&&(kopalnia4!='2')&&(kopalnia4!='3'));
						switch(kopalnia4){
							case 1:
								SetConsoleTextAttribute(kolor,7);
								printf("\n\nNiestety nie udaje ci sie. Zostajesz zabity.");
								SetConsoleTextAttribute(kolor,12);
								printf("\n\nGAME OVER\n\n\n\n\n");
								aktual_scena = 0;   ///powrot do MENU
								break;
							case 2:
								SetConsoleTextAttribute(kolor,7);
								printf("\nTwoj blok zostaje przebity, a ostrze orezu przeciwnika utyka w twojej czasce.");
								SetConsoleTextAttribute(kolor,12);
								printf("\n\nGAME OVER\n\n\n\n\n");
								aktual_scena = 0;   ///powrot do MENU
								break;
							case 3:
								SetConsoleTextAttribute(kolor,7);
								printf("\nKopiesz go. Gdy ten upada, dobijasz go, a nastepnie zmierzasz ku powierzchni.");
								SetConsoleTextAttribute(kolor,8);
		   						system("pause");
								aktual_scena = 6;   ///przejscie do WALKA2

								break;
                        }
                    } else {
                        SetConsoleTextAttribute(kolor,7);
                        printf("\nNiestety nie udaje ci sie trafic. Trex cie dopada i zabija.\n");
                        SetConsoleTextAttribute(kolor,12);
                        printf("\nGAME OVER!\n\n\n\n\n");
                        aktual_scena = 0;   ///powrot do MENU
                    }
                }

                }
    }
}

///WALKA2
if (aktual_scena = 6) {

    save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
    SetConsoleTextAttribute(kolor, 5);
    printf("\n\n\nPoprawnie zapisano postepy.");

    SetConsoleTextAttribute(kolor,7);
    printf("\n\nPrzed toba stoi trzech wojownikow Hordy Ciemnosci. Przeciwnik z lewej jest uzbrojony w miecz i tarcze, ten w srodku jest masywny i posada dwureczny topor, a ten z prawej trzyma naprezony luk.\n");

   	char walka;
		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
		{
		SetConsoleTextAttribute(kolor,3);
		printf("\nDecydujesz sie:\n1)zaatakowac tego po lewej\n2)Zaatakowac tego w srodku\n3)Zaatakowac tego po prawej\n");
		scanf(" %s", &walka);
		if((walka!='1')&&(walka!='2')&&(walka!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		}
	while((walka!='1')&&(walka!='2')&&(walka!='3'));
    switch (walka) {
	    case 1:
	        SetConsoleTextAttribute(kolor,7);
	        printf ("\n\nTwoj cios zostal zablokowany przez jego tarcze. Twoje plecy zostaja przeszyte przez strzale, a glowa roztrzaskana toporem");
	        SetConsoleTextAttribute(kolor,12);
	        printf ("\n\nGAME OVER\n\n\n\n\n");
	        aktual_scena = 0;   ///powrot do MENU

	        break;

	    case 2:
	        SetConsoleTextAttribute(kolor,7);
	        printf ("\n\nUdaje ci sie zadac cios, jednak twoj kilof utknal w ciele wroga. Juz zegnasz sie z zyciem, widzac strzale lecaca w twoja strone, lecz zostaje ona zablokowana. Na ratunek przybywa ci jeden ze skazancow, ktorzy przetrwali. Po pokonaniu przeciwnikow razem udajecie sie w strone lasu.\n");
	        SetConsoleTextAttribute(kolor,8);
			system("pause");
			aktual_scena = 5;   ///przejscie do LAS

	        break;

	    case 3:
	        SetConsoleTextAttribute(kolor,7);
	        printf ("\n\nZabijasz przeciwnika z lukiem, jednak reszta rzuca sie na ciebie, a twoje cialo zostaje przebite mieczem i toporem.");
	        SetConsoleTextAttribute(kolor,12);
	        printf ("\n\nGAME OVER\n\n\n\n\n");
	        aktual_scena = 0;   ///powrot do MENU

	        break;
    }
}
if (aktual_scena = 5) {

	save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
    SetConsoleTextAttribute(kolor, 5);
    printf("/n/n/nPoprawnie zapisano postepy.");

    SetConsoleTextAttribute(kolor,7);
    printf("\n\nWraz z nowo poznanym znajomym udajecie sie wglab lasu i zmierzacie na wschod. Po kilkudziesiecu minutach wedrowki postanawiacie odpoczac przy strumieniu.\nWywiazuje sie miedzy wami dialog.");
    SetConsoleTextAttribute(kolor,2);
    system ("pause");
    printf ("\n\nTak w ogole to jak sie zwiesz, ja jestem Taul");
    system ("pause");
    SetConsoleTextAttribute(kolor,3);
    printf ("\n\n[podaj swoje imie] Zwe sie: \n");
   	char im[100];
   	scanf("%99s",&im);
    SetConsoleTextAttribute(kolor,2);
    printf ("\n\nA wiec milo mi cie poznac ");
    printf(im);
    system ("pause");
    char las1;
		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
		{
		SetConsoleTextAttribute(kolor,3);
	    printf ("\n\n1)Dziekuje za pomoc w ucieczce\n2)Co teraz zrobimy?\n3)Dlaczego Horda Ciemnosci zaatakowala Kolonie Karna?\n");
		scanf(" %s", &las1);
		if((las1!='1')&&(las1!='2')&&(las1!='3')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		}
	while((las1!='1')&&(las1!='2')&&(las1!='3'));
    switch (las1) {
        case 1:
            SetConsoleTextAttribute(kolor,2);
            printf ("\n\nNie ma sprawy, trzeba sobie pomagac, by przetrwac...Slyszysz?");
            system ("pause");
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nZ glebi lasu dalo sie slyszec rozmowe grupy ludzi");
            system ("pause");
            SetConsoleTextAttribute(kolor,3);
            printf ("\n\nTo patrol Zakonu Swietego Ryszarda, lepiej sie nie ujawniac");
            system ("pause");
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nPrzez jakis czas ty wraz z nowo poznanym znajomym lezeliscie wsrod listowia, jednak po chwili zostaliscie zauwazeni i pochwyceni.\nPatrol zabral was bezposrednio do Miasta Kolonialniego, gdzie nazajutrz mieliscie stanac przed sadem.");
            system ("pause");
            SetConsoleTextAttribute(kolor, 8);
            system ("pause");
            aktual_scena = 7;

            break;
        case 2:
            SetConsoleTextAttribute(kolor,2);
            printf ("\n\nSzczerze to nie mam pojecia, ale trzeba sobie pomagac, by przetrwac...Slyszysz?");
            system ("pause");
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nZ glebi lasu dalo sie slyszec rozmowe grupy ludzi");
            system ("pause");
            SetConsoleTextAttribute(kolor,3);
            printf ("\n\nTo patrol Zakonu Swietego Ryszarda, lepiej sie nie ujawniac");
            system ("pause");
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nPrzez jakis czas ty wraz z nowo poznanym znajomym lezeliscie wsrod listowia, jednak po chwili zostaliscie zauwazeni i pochwyceni.\nPatrol zabral was bezposrednio do Miasta Kolonialniego, gdzie nazajutrz mieliscie stanac przed sadem.");
            system ("pause");
            SetConsoleTextAttribute(kolor,8);
            aktual_scena = 7;

            break;

        case 3:
            SetConsoleTextAttribute(kolor,2);
            printf ("\n\nSam nie sadzilem ze oni zapuszczaja sie na te tereny, ale...Slyszysz?");
            system ("pause");
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nZ glebi lasu dalo sie slyszec rozmowe grupy ludzi");
            system ("pause");
            SetConsoleTextAttribute(kolor,3);
            printf ("\n\nTo patrol Zakonu Swietego Ryszarda, lepiej sie nie ujawniac");
            system ("pause");
            SetConsoleTextAttribute(kolor,7);
            printf ("\n\nPrzez jakis czas ty wraz z nowo poznanym znajomym lezeliscie wsrod listowia, jednak po chwili zostaliscie zauwazeni i pochwyceni.\nPatrol zabral was bezposrednio do Miasta Kolonialniego, gdzie nazajutrz mieliscie stanac przed sadem.");
            system ("pause");
            SetConsoleTextAttribute(kolor,8);
            aktual_scena = 7;

            break;


    }
}

///ROZDZIAL I
if (aktual_scena = 7) {

    save_write(aktual_scena);   ///automatyczny zapis stanu gry do pliku
    SetConsoleTextAttribute(kolor, 5);
    printf("\n\n\nPoprawnie zapisano postepy.");


    SetConsoleTextAttribute(kolor,12);
    printf("\n\n\n\n\nROZDZIAL I\n\n\n");
    SetConsoleTextAttribute(kolor,7);
    printf("Prowadzeni w lancuchach Ty i twoj nowo poznany towarzysz broni docieracie do szalupy wieziennej jednego z krolewskich statkow.\nWaszym celem jest Wielkie Miasto Kolonialne, powszechnie uznawane za stolice Wysp Macierzystych Tzaryatu.\n");
    system("pause");
    printf("Podczas rozbrzmiewania szumu fal rozmyslasz o swoim losie oraz pelnym ostatnio niespodziewanych zwrotow akcji zyciu. Z prostego czlowieka\ntrudzacego sie handlem zostales skazany za zabojstwo i wywieziony do Kolonii Karnej, nastepnie toczyles walke o przetrwanie\nw tej przerazajacej rzeczywistosci, potem doszlo do najazdu Hord Ciemnosci i rozpetanie batalii o wlasne zycie,\nkonczac na schwytaniu przez patrol Zakonu sw. Ryszarda.\n");
    system("pause");
    printf("Patrzysz przez bulaj i ku twoim oczom ukazuje sie nieziemski widok. Ostoja sprawiedliwosci, przyczolek ludzkosci, emblemat kultury i sztuki,\nduma wspolczesnej architektury, miejsce wybrane przez bogow, potega wojskowa, wrecz najczystsza perla wsrod perel, Wielkie Miasto Kolonijne.\nDobijacie do tetniacego zyciem portu. Otaczajace Cie magazyny, punkty sprzedazy, zaklady przemyslowe oraz domy towarowe stanowia glowna czesc\ngalezi handlowej miasta. Z kolei cumujace armady oraz flotylle wszelkiego rodzaju okretow wojskowych, fregat czy karaweli daja ci do zrozumienia\nz jaka potaga militarna masz do czynienia.\n");
    system("pause");
    printf("Wychodzisz ze statku wraz z przyjacielem oraz gromada rycerzy zakonnych i kierujecie sie powoli w strone Fortecy na przesluchanie. Opuszczajac port,\nprzechodzisz przez pierwsze warstwy murow i docierasz do podgrodzia. W trakcie tulaczki przygladasz sie rozradowanym mieszkancom, ktorzy z usmiechami\npracuja na rozwinietych polach uprawnych oraz hodowlach zwierzat. Uliczki oraz chatki wiesniakow sa utrzymane w doskonalym stanie.\nNagle przychodzi ci na mysl jak to miejsce bardzo sie rozni od Kolonii Karnej, w ktorej dane bylo ci spedzic najgorsze dni twego zycia.\n");
    system("pause");
    printf("Pokonujesz kolejne mury, tym razem wyposazone w dziesiec murowanych baszt oraz dwadziescia wiez strzelniczych zabezpieczonych blankami. Wchodzisz do miasta. Rozgladasz sie. Wyczuwasz zapach swiezo palonej gliny w zakladach ceglarzy i przygladasz sie wspanialym wyrobom doswiadczonych kamieniarzy krolestwa.\nIdac dalej w glab przygladasz sie ciezkiej pracy kowali wykuwajacych najwspanialsze bronie dla rycerstwa Zakonu sw. Ryszarda.\nZaraz obok dostrzegasz przeprowadzane doswiadczenia oraz zachodzace reakcje chemiczne w laboratoriach krolestwa, ktore wspolpracuja z doskonale wyposazonymi ludwisarniami, produkujacymi potezne armaty. Docierasz do glownego skrzyzowania, lecz Plac Centralny dostrzegasz tylko katem oka,\ngdyz idacy za toba rycerz w pogardliwy sposob zmusza cie do nie zatrzymywania sie. Stojace wozy handlowe, rozlegly tlum gawiedzi,\nnadworni komicy oraz wszelakiego rodzaju atrakcje rozrywkowe podkreslaja donioslosc tego miejsca.\n");
    system("pause");
    printf("Idac przed siebie mijasz dzielnice naukowa pelna bibliotek, kryjacych wiedze starozytnych cywilizacji, mase uniwersytetow ksztalcacych dzisiejsza mlodziez\noraz niepojete przez ciebie astrolabia. Kolejna dzielnica, przez ktora przechodzisz jest bogata dzielnica biznesowa.\nOgrom bankow, skarbcow, gield, targowisk, kantorow walutowych klania sie twoim oczom. Mozna rzecz, ze w tym miejscu papiery wartosciowe\noraz pieniadze walaja sie wrecz po ziemi. Tutaj jednak ma miejsce ciagla walka z czasem, pracownicy biznesowi nie maja lekko.\nNie majac czasu na dluzsze ogledziny idziesz dalej. Dostrzegasz powoli zarysy Marmurowej Fortecy zakonu, ale przed nia stoi jeszcze dzielnica kulturowa.\nNigdy wczesniej nie bylo ci dane zobaczyc tak z twojej perspektywy smiesznie ubranej arystokracji. Jest to miejsce rozmow, spacerow oraz spedzania czasu\nwyzszych warstw spolecznych do ktorych naleza margrabiowie, baronowie, hrabiowie, markizy oraz ksiazeta. Tutaj powstaja wszelakie dziela malarskie,\npismienne oraz muzyczne. To tu muzea sa przepelnione znaleziskami archeologicznymi. Tutaj egzystuja pod mecenatem arystokracji najbardziej cenieni\ni znani tworcy sztuki. Twoje napawanie sie pieknem dzielnicy i zachwyt przerwal znow podirytowany juz toba straznik targajac cie do przodu.\n");
    system("pause");
    printf("Dotarles do końca miasta i ze zdumieniem dostrzegasz, ze Forteca znajduje sie na osobnej wyspie oddzielonej od glownej wyspy ciesnina Kuzynova.\nObie wyspy sa jednak polaczone swietnie bronionym kamiennym mostem. Dotarlszy do glownej bramy strzegacej wejscia na wyspe sw. Ryszarda\nprzed twymi oczyma wylania sie wspanialy widok. Ta lokacja zdaje sie byc nieskazitelnie piekna. Ogrom budynkow wojskowych, kapliczek oraz kosciolow\njest przycmiony absolutnie niesamowitym widokiem Katedry Zakonu sw. Ryszarda. Styl gotycki wyrozniajacy sie marmurowymi, strzelistymi wiezyczkami,\nolbrzymi, w kolorach teczy witraz promieniujacy blaskiem, dwanascie tympanonow, wyrzezbione dzwonnice oraz olsniewajace luki wprowadzaja cie w zachwyt.\nNie sadziles ze liczebnosc braci zakonnych modlacych sie wraz z prowadzacymi rozmowy rycerzami przebije tlum gawiedzi spotykajacy sie na rynku glownym\nw miescie. Mijajac najpiekniejsze miejsce Wielkiego Miasta Kolonijnego, calkowicie wyczerpany, ledwo ustajesz na nogach przed wrotami mosieznej\nFortecy Zakonnej na Wzgorzu. Mimo pieknych zdobien i lekko powiewajacych sztandarow Zakonu ta lokalizacja napawa cie przerazeniem.\nW koncu nie przybyles tu jako gosc, ale jako jeniec, oczekujacy na przesluchanie.");
    printf("\n\n\nZnajdujesz sie w malej, ciasnej i ciemnej celi. Lezysz na przegnitym sianie, a na scianach widac grzyb. Po chwili do srodka lochu wchodza straznicy\ni przetransportowuja cie do wielkiej sali, gdzie zebral sie sad, ktory zadecyduje co sie z toba stanie. Obok ciebie stoi Taul.\n");
    system("pause");
    R000:
	SetConsoleTextAttribute(kolor,2);
	printf("\n\n[Sedzia] - Jak uciekliscie z Koloni Karnej?");
    char r001;
		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
		{
		SetConsoleTextAttribute(kolor,3);
   		 printf("\n[TY]:\n1)Podczas ataku\n2)Nie twoja sprawa\n");
		scanf(" %s", &r001);
		if((r001!='1')&&(r001!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		}
	while((r001!='1')&&(r001!='2'));
    switch (r001) {
		case 1:
    		aktual_scena = 8;   ///przejscie do punktu R001
   			break;
		case 2:
   			aktual_scena = 8;  ///przjscie do punktu R001
   		    break;
    }
}

///R001
if (aktual_scena = 8) {
    SetConsoleTextAttribute(kolor,2);
    printf("\n\n[Sedzia] - Dlaczego uciekliscie?");
    char r002;
		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
		{
		SetConsoleTextAttribute(kolor,3);
    	printf("\n\n[TY]:\n1)Jedyny sposob by przetrwac atak\n2)Nie twoja sprawa\n");
		scanf(" %s", &r002);
		if((r002!='1')&&(r002!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		}
	while((r002!='1')&&(r002!='2'));
    switch (r002){
case 1:

	SetConsoleTextAttribute(kolor,2);
    printf("\n\n[Sedzia] - Jaki atak?");
   char r003;
		do  ///zabezpieczenie przed wpisaniem niepoprawnej wartosci
		{
		SetConsoleTextAttribute(kolor,3);
    	printf("\n\n[TY]:\n1)Hordy Ciemnosci\n2)Nie twoja sprawa\n");
		scanf(" %s", &r003);
		if((r003!='1')&&(r003!='2')) printf("\nWybrano zla opcje, sprobuj ponownie\n");
		}
	while((r003!='1')&&(r003!='2'));
    switch (r003) {
        case 1:
            R012:
            SetConsoleTextAttribute(kolor,2);
            printf("\n\n[Sedzia] - Chyba nie sadzisz ze w to uwierzymy? Horda Ciemnosci nie zapuszcza sie tak ");
            SetConsoleTextAttribute(kolor,3);
            printf("\n\n[TY]:\n1)To byla rzez!\n2)Skoro nie wierzycie to po co pytacie\n");
            int r004=0;
            scanf("%d", &r004);
            switch(r004) {
            case 1:
                aktual_scena = 9;
                break;
            case 2:
                aktual_scena = 10;
                break;
            }
        case 2:
            aktual_scena = 10;
            break;

        }
	case 2:
   	 	aktual_scena =10;
   		break;

    }
}

///ROO2
if (aktual_scena = 10) {
    SetConsoleTextAttribute(kolor,2);
    printf("\n\n[Sedzia] - W takim razie zawisniesz!");
    SetConsoleTextAttribute(kolor,12);
	printf ("\n\nGAME OVER\n\n\n\n\n");
	aktual_scena = 0;   ///powrot do MENU
}

///R003
if (aktual_scena = 9) {
       SetConsoleTextAttribute(kolor,12);
    printf("\nGRATULACJE UDALO CI SIE PRZEJSC WERSJE DEMONSTRACYJNA GRY\n");
}


system("pause");
return 0;
}
}













