#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <vector>

using namespace std;

//==================================================WARNING==================================================
// 
//When creating an FEM mesh, the difference in the numbering of nodes on one element should be as small as 
//possible.



/*
 * Example of global element:
 *
 *       ID[3]      2        ID[2]
 *            ________________
 *           /               |
 *          /                |
 *         /                 |
 *    3   /                  | 1
 *       /                   |
 *      /                    |
 *     /_____________________|
 *				   0
 *  ID[0]                    ID[1]
 */


 //=========================================FUNCTIONS DECLARATION=============================================
 //
 //Used for numerical integration:
double kwadratury(double wezly[], double wspolczynnik[], int ilosc_wezlow, int petla2);
double kwadratury(double wezly[], double wspolczynnik[], int petla, int poczatek, int koniec);

//Used in FEM:
vector<vector<double>> stworzMacierzN(double eta, vector<double>ksi, int iloscPc);
vector<vector<double>> stworzMacierzN(vector<double> eta, double ksi, int iloscPc);
vector <vector<double>> T(vector <vector<double>>& pom, int pc);


//=================================================STRUCTURE=================================================
//
//Node structure:
struct NODE {
	double x = 0.0; //x-coordinate.
	double y = 0.0; //y-coordinate.
	double nodeTemp = 0.0; //temperature on the node.
	int BC = 0; //flag indicating the presence of a boundary condition (0 means no boundary condition).
};

//Struktura zawierająca ID dla danego elementu (gdyby byly potrzebne różne ilości węzłów w elemencie wówczas
//należy dodać kolejną strukturę elementów

struct ELEMENT {
	int ID[4] = { 0, 0, 0, 0 };
	double conductivity = 0.0;
	double density = 0.0;
	double cp = 0.0;
	double alfa = 0.0;
};
/*
 * Loading Node ID:
 *
 *    ID[3]               ID[2]
 *        _________________
 *        |               |
 *        |     <--_      |
 *        |          \    |
 *        |   \      /    |
 *        |     -__-      |
 *        |               |
 *        |_______________|
 *
 *   ID[0]                   ID[1]
 */

 //Grid structure (struktura siatki)
struct GRID {
	int nE = 0; //numeber of element.
	int nN = 0; //number of nodes.
	NODE* ND = new NODE[nN]; //node Table.
	ELEMENT* EL = new ELEMENT[nE]; //Element table.
} struktura;

//Structure of data from file (about simulations and thermal characteristics)
//warunek brzegowy - konwekcja: q = alfa (t - alfa)

struct GlobalData {
	double alfa = 0.0; //współczynnik konwekcji
	double tOt = 0.0; //temperatura otoczenia
	double cp = 0.0; //ciepło właściwe
	double gamma = 0.0; //gęstość
	double simulationTime = 0.0; // czas symulacji
	double delt = 0.0; //interwał (co ile krok)
	double pc = 0.0; // przewodniość cieplna
	double initialTemp = 0.0; // temp poczatkowa
	vector<NODE> pom_nN;
	vector<ELEMENT> pom_nE;

} dane;

//wektory do stworzenia węzłów i elementów:

vector <NODE> Utworz_nN(int i) {
	vector <NODE> pom_nN(i + 2);
	return pom_nN;
}

vector <ELEMENT> Utworz_nE(int i) {
	vector <ELEMENT> pom_nE(i + 2);
	return pom_nE;
}

struct Bok { //warunek brzegowy konwekcji
	int iloscPc = 0;
	int ID; //wybor budowanego boku - 0 dolny bok, 1 prawy bok, 2 górny bok, 3 lewy bok.
	vector<int> nrElementu;
	vector <double> ksi;
	vector <double> eta;
	vector <double> wspolczynnik;
	vector<vector<double>> P; //wektor obciążeń
	vector<vector<double>> N; //funkcja kształtu
	vector<vector<double>> NT;//funkcja ksztaltu transponowana
	vector<vector<vector<double>>> HBC;//Macierz HBC
	Bok(int iloscPunktow, int ID);
	void stworzBok();
};

Bok::Bok(int iloscPunktow, int Id) {
	vector<vector<vector<double>>> pom(struktura.nE, vector<vector<double>>(4, vector<double>(4, 0.0)));
	vector<double> pom2(4, 0.0);

	for (int i = 0; i < struktura.nE; i++) {
		P.push_back(pom2);
	}
	HBC = pom;

	iloscPc = iloscPunktow;
	ID = Id;
	stworzBok();
}

void Bok::stworzBok() {
	// vector<vector<vector<int>>> vector_3d(z, vector<vector<int>>(y, vector<int>(x, value)));
	// x = number of elements in 1D vector
	// y = number of 1D vectors in 2D vector
	// z = number of 2D vectors in 3D vector
	// value = value for each element

	if (iloscPc == 2) {
		ksi = { -(double)(1.0 / sqrt(3.0)),  (double)(1.0 / sqrt(3.0)) };
		eta = { -(double)(1.0 / sqrt(3.0)),  (double)(1.0 / sqrt(3.0)) };
		wspolczynnik = { 1.0, 1.0 };
	}
	else if (iloscPc == 3) {
		ksi = { -((double)sqrt(3.0 / 5.0)), 0.0, (double)(sqrt((3.0 / 5.0))) };
		eta = { -((double)sqrt(3.0 / 5.0)), 0.0, (double)(sqrt((3.0 / 5.0))) };
		wspolczynnik = { (5.0 / 9.0), (8.0 / 9.0), (5.0 / 9.0) };

	}
	else if (iloscPc == 4) {
		ksi = { -((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))), -((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))),  ((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))), ((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))) };
		eta = { -((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))), -((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))),  ((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))), ((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))) };
		wspolczynnik = { ((18.0 - sqrt(30.0)) / 36.0), ((18.0 + sqrt(30.0)) / 36.0), ((18.0 + sqrt(30.0)) / 36.0), ((18.0 - sqrt(30.0)) / 36.0) };
	}
	else {
		cout << "Niepoprawna liczba punktow calkowania!!!" << endl;
		return;
	}
	//cout << "BOKI:" << endl;

	if (ID == 0) {
		//cout << "Macierz n dla dolu: " << endl;
		N = stworzMacierzN(-1, ksi, iloscPc);
	}
	else if (ID == 1) {
		//cout << "Macierz n dla prawa: " << endl;
		N = stworzMacierzN(eta, 1, iloscPc);
	}
	else if (ID == 2) {
		//cout << "Macierz n dla gory:" << endl;
		reverse(ksi.begin(), ksi.end());//odwrócenie kolejności całkowania
		N = stworzMacierzN(1, ksi, iloscPc);
	}
	else {
		//cout << "Macierz n dla lewo: " << endl;
		reverse(eta.begin(), eta.end());
		N = stworzMacierzN(eta, -1, iloscPc);
	}
	/*
	for (int i = 0; i < N.size(); i++) {
		for (int k = 0; k < 4; k++) {
			cout << N[i][k] << " \t ";
		}
		cout << endl;
	}
	cout << endl << endl;
	*/

	NT = T(N, iloscPc);


	for (int k = 0; k < struktura.nE; k++) {
		if (ID == 0 && dane.pom_nN[dane.pom_nE[k].ID[0] - 1].BC && dane.pom_nN[dane.pom_nE[k].ID[1] - 1].BC) { //dół

			nrElementu.push_back(k);

			double detJ = sqrt(pow((dane.pom_nN[dane.pom_nE[k].ID[1] - 1].x - dane.pom_nN[dane.pom_nE[k].ID[0] - 1].x), 2) + (pow((dane.pom_nN[dane.pom_nE[k].ID[1] - 1].y - dane.pom_nN[dane.pom_nE[k].ID[0] - 1].y), 2))) / 2.0;
			int pom = 0;
			int pom2 = 0;
			int pom3 = 0;
			for (int j = 0; j < iloscPc; j++) { // po punktach calkowania:
				for (int m = 0; m < 4; m++) { //po wierszach
					for (int l = 0; l < 4; l++) {//po kolumnach
						HBC[k][m][l] += wspolczynnik[pom] * dane.alfa * (NT[pom3][0] * N[pom2][l]) * detJ;
					}
					pom3++;
				}
				pom++;
				pom2++;
			}

			pom3 = 0;
			for (int i = 0; i < iloscPc; i++) {
				for (int j = 0; j < 4; j++) {
					P[k][j] += dane.alfa * (wspolczynnik[i] * NT[pom3][0] * dane.tOt) * detJ;
					//cout << dane.alfa << " * (" << wspolczynnik[i] << " * " << NT[pom3][0] << " * " << dane.tOt << " * " << detJ << endl;
					pom3++;
				}
			}
			/*
			cout << "Otrzymana macierz HBC dla dolu dla elementu: " << k + 1 << endl;
				for (int m = 0; m < 4; m++) { //po wierszach
					for (int l = 0; l < 4; l++) {//po kolumnach
						cout << HBC[k][m][l] << " ";
					}
					cout << endl;
				}

			cout << "\n\nWektor P: " << endl;
				for (int i = 0; i < 4; i++) {
					cout << P[k][i] << endl;
				}
	*/

		}
		if (ID == 1 && dane.pom_nN[dane.pom_nE[k].ID[1] - 1].BC && dane.pom_nN[dane.pom_nE[k].ID[2] - 1].BC) { //prawo

			nrElementu.push_back(k);

			double detJ = sqrt(pow((dane.pom_nN[dane.pom_nE[k].ID[2] - 1].x - dane.pom_nN[dane.pom_nE[k].ID[1] - 1].x), 2) + (pow((dane.pom_nN[dane.pom_nE[k].ID[2] - 1].y - dane.pom_nN[dane.pom_nE[k].ID[1] - 1].y), 2))) / 2.0;
			//cout << "Jestem tuu prawo dla ID: " << dane.pom_nE[k].ID[1] << " i " << dane.pom_nE[k].ID[2] << endl;
			int pom = 0;
			int pom2 = 0;
			int pom3 = 0;
			for (int j = 0; j < iloscPc; j++) { // po punktach calkowania:
				for (int m = 0; m < 4; m++) { //po wierszach
					for (int l = 0; l < 4; l++) {//po kolumnach
						HBC[k][m][l] += wspolczynnik[pom] * dane.alfa * (NT[pom3][0] * N[pom2][l]) * detJ;
					}
					pom3++;
				}
				pom++;
				pom2++;
			}
			pom3 = 0;
			for (int i = 0; i < iloscPc; i++) {
				for (int j = 0; j < 4; j++) {
					P[k][j] += dane.alfa * wspolczynnik[i] * NT[pom3][0] * dane.tOt * detJ;
					pom3++;
				}
			}
			/*
				cout << "Otrzymana macierz HBC dla prawego boku dla elementu: " << k + 1 << endl;
					for (int m = 0; m < 4; m++) { //po wierszach
						for (int l = 0; l < 4; l++) {//po kolumnach
							cout << HBC[k][m][l] << " ";
						}
						cout << endl;
					}

			cout << "\n\nWektor P : " << endl;
			for (int i = 0; i < 4; i++) {
				cout << P[k][i] << endl;
			}
			*/

		}
		if (ID == 2 && dane.pom_nN[dane.pom_nE[k].ID[3] - 1].BC && dane.pom_nN[dane.pom_nE[k].ID[2] - 1].BC) { //góra

			nrElementu.push_back(k);

			double detJ = sqrt(pow((dane.pom_nN[dane.pom_nE[k].ID[2] - 1].x - dane.pom_nN[dane.pom_nE[k].ID[3] - 1].x), 2) + (pow((dane.pom_nN[dane.pom_nE[k].ID[2] - 1].y - dane.pom_nN[dane.pom_nE[k].ID[3] - 1].y), 2))) / 2.0;
			//cout << "Jestem tuu gora dla ID: " << dane.pom_nE[k].ID[3] << " i " << dane.pom_nE[k].ID[2] << endl;
			int pom = 0;
			int pom2 = 0;
			int pom3 = 0;
			for (int j = 0; j < iloscPc; j++) { // po punktach calkowania:
				for (int m = 0; m < 4; m++) { //po wierszach
					for (int l = 0; l < 4; l++) {//po kolumnach
						HBC[k][m][l] += wspolczynnik[pom] * dane.alfa * (NT[pom3][0] * N[pom2][l]) * detJ;
					}
					pom3++;
				}
				pom++;
				pom2++;
			}

			pom3 = 0;
			for (int i = 0; i < iloscPc; i++) {
				for (int j = 0; j < 4; j++) {
					P[k][j] += dane.alfa * wspolczynnik[i] * NT[pom3][0] * dane.tOt * detJ;
					pom3++;
				}
			}
			/*
				cout << "Otrzymana macierz HBC dla górnego boku dla elementu: " << k + 1 << endl;
					for (int m = 0; m < 4; m++) { //po wierszach
						for (int l = 0; l < 4; l++) {//po kolumnach
							cout << HBC[k][m][l] << " ";
						}
						cout << endl;
					}

			cout << "\n\nWektor P: " << endl;
			for (int i = 0; i < 4; i++) {
				cout << P[k][i] << endl;
			}
		*/

		}
		if (ID == 3 && dane.pom_nN[dane.pom_nE[k].ID[3] - 1].BC && dane.pom_nN[dane.pom_nE[k].ID[0] - 1].BC) { //lewo
			//cout << "ID wezlow: " << dane.pom_nE[k].ID[3] << " i " << dane.pom_nE[k].ID[0] << endl;
			nrElementu.push_back(k);

			double detJ = sqrt(pow((dane.pom_nN[dane.pom_nE[k].ID[0] - 1].x - dane.pom_nN[dane.pom_nE[k].ID[3] - 1].x), 2) + (pow((dane.pom_nN[dane.pom_nE[k].ID[0] - 1].y - dane.pom_nN[dane.pom_nE[k].ID[3] - 1].y), 2))) / 2.0;
			//cout << "Jestem tuu lewo dla ID: " << dane.pom_nN[dane.pom_nE[k].ID[0] - 1].x << " i " << dane.pom_nN[dane.pom_nE[k].ID[3] - 1].x << endl;
			int pom = 0;
			int pom2 = 0;
			int pom3 = 0;
			for (int j = 0; j < iloscPc; j++) { // po punktach calkowania:
				for (int m = 0; m < 4; m++) { //po wierszach
					for (int l = 0; l < 4; l++) {//po kolumnach
						HBC[k][m][l] += wspolczynnik[pom] * dane.alfa * (NT[pom3][0] * N[pom2][l]) * detJ;
					}
					pom3++;
				}
				pom++;
				pom2++;
			}
			pom3 = 0;
			for (int i = 0; i < iloscPc; i++) {
				for (int j = 0; j < 4; j++) {
					P[k][j] += dane.alfa * wspolczynnik[i] * NT[pom3][0] * dane.tOt * detJ;
					//cout << "\nObliczenie wektora P dla lewego:\n Mnoze: " << dane.alfa << " * " << wspolczynnik[i] << " * " << NT[pom3][0] << " * "  << dane.tOt << " * "  << detJ << " = " << P[k][j];
					pom3++;
				}
			}
			/*
			cout << "Otrzymana macierz HBC dla lewego boku dla elementu: " << k + 1 << endl;
					for (int m = 0; m < 4; m++) { //po wierszach
						for (int l = 0; l < 4; l++) {//po kolumnach
							cout << HBC[k][m][l] << " ";
						}
						cout << endl;
					}

			cout << "\n\nWektor P: " << endl;
			for (int i = 0; i < 4; i++) {
				cout << P[k][i] << endl;
			}
			//system("PAUSE");
			*/
		}
	}
}

vector<vector<double>> stworzMacierzN(double eta, vector<double>ksi, int iloscPc) {
	vector <vector<double>> tmp;
	vector <double> pom(4, 0.0);
	for (int i = 0; i < iloscPc; i++) {
		tmp.push_back(pom);
	}
	for (int k = 0; k < iloscPc; k++) {
		tmp[k][0] = 0.25 * (1 - ksi[k]) * (1 - eta);
		tmp[k][1] = 0.25 * (1 + ksi[k]) * (1 - eta);
		tmp[k][2] = 0.25 * (1 + ksi[k]) * (1 + eta);
		tmp[k][3] = 0.25 * (1 - ksi[k]) * (1 + eta);
	}
	return tmp;
}
vector<vector<double>> stworzMacierzN(vector<double> eta, double ksi, int iloscPc) {
	vector <vector<double>> tmp;
	vector <double> pom(4, 0.0);
	for (int i = 0; i < iloscPc; i++) {
		tmp.push_back(pom);
	}
	for (int k = 0; k < iloscPc; k++) {
		tmp[k][0] = 0.25 * (1 - ksi) * (1 - eta[k]);
		tmp[k][1] = 0.25 * (1 + ksi) * (1 - eta[k]);
		tmp[k][2] = 0.25 * (1 + ksi) * (1 + eta[k]);
		tmp[k][3] = 0.25 * (1 - ksi) * (1 + eta[k]);
	}

	return tmp;
}

struct Element4 {
	friend Bok;
public:
	//Punkty całkowania:
	vector <double> ksi;
	vector <double> eta;

	//Do macierzy Jakobiego (zwykłego i odwróconego):
	vector <vector <double>> pochodna_ksi;
	vector <vector <double>> pochodna_eta;
	vector <vector <double>> pochodnaDlaNPoX;
	vector <vector <double>> pochodnaDlaNPoY;

	vector <vector <double>> pochodna_Po_X_Y;
	vector <vector <double>> odwroconaDlaEta;
	vector <vector <double>> odwroconaDlaKsi;

	vector <double> pochodna_Po_Ksi;
	vector <double> pochodna_Po_Eta;

	//częsciowe macierze H
	vector <vector <double>> macierzH;

	//zsumowane macierze H dla danego elementu
	vector <vector <double>> macierzHFinall;

	//Warunki brzegowe na poszczególnych bokach:
	vector <Bok> boki;

	//Macierz warunków brzegowych
	vector<vector<vector<double>>> HBC;

	//Wektor obciążeń 
	vector <vector <double>> P;
	vector <vector <double>> pAgregowane;

	//Macierz C
	vector<vector<double>> macierzC;
	vector <vector <double>> macierzCFinall;

	//Funkcje kształtu po objętości
	vector <vector <double>> N;
	vector <vector <double>> NT;

	//Temperatura na węzłach
	vector <vector <double>> tempNaWezlach;

	//"Finałowa macierz" (agregowana macierz HBC + H)
	vector <vector <double>> agregacja;

	//"Finałowa macierz" (agregowana macierz C)
	vector <vector <double>> agregacjaMacierzyC;

	//wyznacznik macierzy
	vector <double> detJ;

	vector <double> wspolczynnik;
	//ilość punktów całkowania
	int rozmiar = 0;

	Element4(int value, int punktyBok);
	void pchodnKsi();//Obliczanie pochodnej N po ksi
	void pochodnaEta();//Obliczanie pochodnej N po eta
	void jakobian();//Obliczanie macierzy Jakobiego wraz z wyznacznikiem
	void macierzOdwrotna(); //Obliczanie macierzy odwrotnej Jakobiego
	void pochodnaDlaN(); //Obliczanie pochodnej N po x oraz N po Y
	void macierzHBCorazWektorP(); //Zsumowanie macierzyHBC i P z poszczególnych boków 
	void macierzHplusC();//Zsumowanie macierzyH oraz macierzyC z punktów całkowania dla poszczególnych elementów
	void Agregacja(); //Agregacja macierzy H oraz macierzy C
	void obliczanieTemperaturyNaWezlach();//Przeprowadzenie symulacji
	//Tworzenie funkcji kształtu dla całki po objętości:
	vector<vector<double>> stworzMacierzN(vector<double> eta, vector<double>ksi, int iloscPc);

	vector <vector<double>> T(vector <vector<double>>& pom);

	void print();
};

Element4::Element4(int value, int punktyBok) {
	rozmiar = value;
	double zero = 0.0;
	HBC = vector(struktura.nE, vector<vector<double>>(4, vector<double>(4, 0.0)));
	//pAgregowane = vector <double> (struktura.nN);
	vector <double> pom(4, 0.0);// wektor pomocniczy mający 4 pola wypełnione wartościami 0.0
	vector <double> pom2(36, 0.0);
	vector <double> pom4(1, 0.0);
	vector <double> pom3(struktura.nN, 0.0);

	Bok bok1(punktyBok, 0); //dół
	Bok bok2(punktyBok, 1); //prawo
	Bok bok3(punktyBok, 2); //góra
	Bok bok4(punktyBok, 3); //lewo

	boki.push_back(bok1);
	boki.push_back(bok2);
	boki.push_back(bok3);
	boki.push_back(bok4);
	for (int i = 0; i < struktura.nE; i++) {
		P.push_back(pom);
	}
	for (int i = 0; i < struktura.nE * pow(rozmiar, 2); i++) {
		pochodna_Po_X_Y.push_back(pom);
		odwroconaDlaEta.push_back(pom);
		odwroconaDlaKsi.push_back(pom);
		detJ.push_back(0);
	}

	for (int i = 0; i < struktura.nE * 4; i++) {
		macierzHFinall.push_back(pom);
		macierzCFinall.push_back(pom);
	}
	for (int i = 0; i < pow(rozmiar, 2) * 4 * struktura.nE; i++) {
		macierzH.push_back(pom);
		macierzC.push_back(pom);
	}

	for (int i = 0; i < pow(rozmiar, 2) * 4; i++) {
		NT.push_back(pom4);
	}

	for (int i = 0; i < pow(rozmiar, 2) * pow(rozmiar, 2) * struktura.nE; i++) {
		pochodnaDlaNPoX.push_back(pom);
		pochodnaDlaNPoY.push_back(pom);
	}

	for (int i = 0; i < pow(rozmiar, 2); i++) {
		pochodna_ksi.push_back(pom);
		pochodna_eta.push_back(pom);
		N.push_back(pom);

		for (int j = 0; j < pow(rozmiar, 3); j++) {

			pochodna_Po_Ksi.push_back(zero);
			pochodna_Po_Eta.push_back(zero);
		}
	}

	for (int i = 0; i < struktura.nN; i++) {
		agregacja.push_back(pom3);
		pAgregowane.push_back(pom4);
		agregacjaMacierzyC.push_back(pom3);
	}

	if (value == 2) {
		ksi = { -(double)(1.0 / sqrt(3.0)),  (double)(1.0 / sqrt(3.0)) };
		eta = { -(double)(1.0 / sqrt(3.0)),  (double)(1.0 / sqrt(3.0)) };
		wspolczynnik = { 1.0, 1.0 };
	}
	else if (value == 3) {
		ksi = { -((double)sqrt(3.0 / 5.0)), 0.0, (double)(sqrt((3.0 / 5.0))) };
		eta = { -((double)sqrt(3.0 / 5.0)), 0.0, (double)(sqrt((3.0 / 5.0))) };
		wspolczynnik = { (5.0 / 9.0), (8.0 / 9.0), (5.0 / 9.0) };
	}
	else if (value == 4) {
		ksi = { -((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))), -((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))),  ((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))), ((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))) };
		eta = { -((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))), -((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))),  ((double)sqrt((3.0 / 7.0) - (2.0 / 7.0) * sqrt(6.0 / 5.0))), ((double)sqrt((3.0 / 7.0) + (2.0 / 7.0) * sqrt(6.0 / 5.0))) };
		wspolczynnik = { ((18.0 - sqrt(30.0)) / 36.0), ((18.0 + sqrt(30.0)) / 36.0), ((18.0 + sqrt(30.0)) / 36.0), ((18.0 - sqrt(30.0)) / 36.0) };
	}
	else {
		cout << "Niepoprawna liczba punktow calkowania!!!" << endl;
		return;
	}
	N = stworzMacierzN(eta, ksi, rozmiar);


	NT = T(N);

	pchodnKsi();
	pochodnaEta();
	jakobian();
	macierzOdwrotna();
	pochodnaDlaN();
	macierzHBCorazWektorP();
	macierzHplusC();
	Agregacja();
	obliczanieTemperaturyNaWezlach();
}

vector<vector<double>> Element4::stworzMacierzN(vector<double> eta, vector<double>ksi, int iloscPc) {
	vector <vector<double>> tmp;
	vector <double> pom(4, 0.0);
	for (int i = 0; i < pow(iloscPc, 2); i++) {
		tmp.push_back(pom);
	}
	int i = 0;
	for (int j = 0; j < iloscPc; j++) {
		for (int k = 0; k < iloscPc; k++) {
			tmp[i][0] = 0.25 * (1 - ksi[k]) * (1 - eta[j]);
			tmp[i][1] = 0.25 * (1 + ksi[k]) * (1 - eta[j]);
			tmp[i][2] = 0.25 * (1 + ksi[k]) * (1 + eta[j]);
			tmp[i][3] = 0.25 * (1 - ksi[k]) * (1 + eta[j]);
			i++;
		}
	}
	return tmp;
}

void Element4::pchodnKsi() { //dobrze, uniwersalne
	int loop = pow(rozmiar, 2);
	int mnoznik = 1;
	int index = 0;

	for (int k = 0; k < loop; k++) {

		pochodna_ksi[k][0] = -0.25 * (1 - (eta[k / eta.size()]));
		pochodna_ksi[k][1] = 0.25 * (1 - (eta[k / eta.size()]));
		pochodna_ksi[k][2] = 0.25 * (1 - (-eta[k / eta.size()]));
		pochodna_ksi[k][3] = -0.25 * (1 - (-eta[k / eta.size()]));

	}
	/*
	cout << "Otrzymana macierz dla pochodnej N po Ksi: \n";
	for (int i = 0; i < rozmiar * rozmiar; i++) {
		for (int j = 0; j < 4; j++) cout << pochodna_ksi[i][j] << "   ";
		cout << "\n";
	}
	cout << endl;
	*/
	return;
}

void Element4::pochodnaEta() { //dobrze, uniwersalne
	int loop = pow(rozmiar, 2);
	//cout << loop << endl;
	int index = 0;

	for (int k = 0; k < loop; k++) {
		if (rozmiar == 4 && k % 4 == 0) index = 0;
		if (rozmiar == 3 && k % 3 == 0) index = 0;
		if (rozmiar == 2 && k % 2 == 0) index = 0;
		//cout << index << endl;
		pochodna_eta[k][0] = -0.25 * (1 - (ksi[index]));
		pochodna_eta[k][1] = -0.25 * (1 - (-ksi[index]));
		pochodna_eta[k][2] = 0.25 * (1 - (-ksi[index]));
		pochodna_eta[k][3] = 0.25 * (1 - (ksi[index]));
		index++;
	}
	/*
	cout << "Otrzymana macierz dla pochodnej N po eta: \n";
	for (int i = 0; i < rozmiar * rozmiar; i++) {
		for (int j = 0; j < 4; j++) cout << pochodna_eta[i][j] << "   ";
		cout << "\n";
	}
	*/
	return;
}

void Element4::jakobian() { //nie, funkcja
	int loop = pow(rozmiar, 2);
	int i = 0;
	int j = 0;
	int zet = 0;
	for (int k = 0; k < struktura.nE; k++) { //chodzenie po elementach
		for (int m = 0; m < loop; m++) { //chodzenie po punktach
			for (int l = 0; l < 4; l++) { //chodzenie potabelach

				//pochodna po ksi
				pochodna_Po_X_Y[zet][0] += pochodna_ksi[m][l] * dane.pom_nN[dane.pom_nE[k].ID[l] - 1].x;
				pochodna_Po_X_Y[zet][1] += pochodna_ksi[m][l] * dane.pom_nN[dane.pom_nE[k].ID[l] - 1].y;
				//pochodna po eta
				pochodna_Po_X_Y[zet][2] += pochodna_eta[m][l] * dane.pom_nN[dane.pom_nE[k].ID[l] - 1].x;
				pochodna_Po_X_Y[zet][3] += pochodna_eta[m][l] * dane.pom_nN[dane.pom_nE[k].ID[l] - 1].y;
			}
			detJ[zet] = ((pochodna_Po_X_Y[zet][0] * pochodna_Po_X_Y[zet][3]) - (pochodna_Po_X_Y[zet][1] * pochodna_Po_X_Y[zet][2]));
			zet++;
		}
	}
	/*
		cout << "\nOtrzymana macierz Jakobiego: \n";
		for (int k = 0; k < pochodna_Po_X_Y.size(); k++) {
			cout << pochodna_Po_X_Y[k][0] << " " << pochodna_Po_X_Y[k][1] << " " << pochodna_Po_X_Y[k][2] << " " << pochodna_Po_X_Y[k][3] << endl << endl;
		}

		cout << "\nWyznacznik macierzy: " << endl;

		for (int i = 0; i < detJ.size(); i++) cout << detJ[i] << endl;

	*/

}

void Element4::macierzOdwrotna() { //nie, funkcja
	int loop = pow(rozmiar, 2);
	for (int k = 0; k < struktura.nE * loop; k++) {

		odwroconaDlaKsi[k][0] = pochodna_Po_X_Y[k][3] * (1 / detJ[k]);
		//cout << " Obliczanie Jakobiego: " << pochodna_Po_X_Y[k][1] << " * " << (1 / detJ[k]) << " (1/" << detJ[k] << ") " << " = ";
		odwroconaDlaKsi[k][1] = -(pochodna_Po_X_Y[k][1] * (1 / detJ[k]));
		//cout << odwroconaDlaKsi[k][1] << endl;
		odwroconaDlaEta[k][0] = -(pochodna_Po_X_Y[k][2] * (1 / detJ[k]));

		odwroconaDlaEta[k][1] = pochodna_Po_X_Y[k][0] * (1 / detJ[k]);

	}
	//system("PAUSE");
	//cout << "\n\nMACIERZ ODWROCONA:\n ";
	/*
	int licznik = 1;
	for (int k = 0; k < struktura.nE * loop; k++) {
		cout << "Dla  PC " << licznik << " :" << endl;
		cout << odwroconaDlaKsi[k][0] << " " << odwroconaDlaKsi[k][1] << endl;
		cout << odwroconaDlaEta[k][0] << " " << odwroconaDlaEta[k][1] << endl;
		cout << endl;

		licznik++;
	}
	*/
}

void Element4::pochodnaDlaN() { //nie, w funkcji
	int loop = pow(rozmiar, 2);
	int index = 0;
	int j = 0;
	int zet = 0;
	for (int k = 0; k < struktura.nE * loop * loop; k++) {//chodzenie po punktach
		if (k != 0 && k % loop == 0) index++;
		if (zet == loop) zet = 0;
		pochodnaDlaNPoX[j][0] += odwroconaDlaKsi[index][0] * pochodna_ksi[zet][0] + odwroconaDlaKsi[index][1] * pochodna_eta[zet][0];
		pochodnaDlaNPoX[j][1] += odwroconaDlaKsi[index][0] * pochodna_ksi[zet][1] + odwroconaDlaKsi[index][1] * pochodna_eta[zet][1];
		pochodnaDlaNPoX[j][2] += odwroconaDlaKsi[index][0] * pochodna_ksi[zet][2] + odwroconaDlaKsi[index][1] * pochodna_eta[zet][2];
		pochodnaDlaNPoX[j][3] += odwroconaDlaKsi[index][0] * pochodna_ksi[zet][3] + odwroconaDlaKsi[index][1] * pochodna_eta[zet][3];


		//cout << odwroconaDlaKsi[k][0] << " * " << pochodna_ksi[zet][0] << "  +  " << odwroconaDlaKsi[k][1] * pochodna_eta[zet][0] << endl;
		pochodnaDlaNPoY[j][0] += odwroconaDlaEta[index][0] * pochodna_ksi[zet][0] + odwroconaDlaEta[index][1] * pochodna_eta[zet][0];
		pochodnaDlaNPoY[j][1] += odwroconaDlaEta[index][0] * pochodna_ksi[zet][1] + odwroconaDlaEta[index][1] * pochodna_eta[zet][1];
		pochodnaDlaNPoY[j][2] += odwroconaDlaEta[index][0] * pochodna_ksi[zet][2] + odwroconaDlaEta[index][1] * pochodna_eta[zet][2];
		pochodnaDlaNPoY[j][3] += odwroconaDlaEta[index][0] * pochodna_ksi[zet][3] + odwroconaDlaEta[index][1] * pochodna_eta[zet][3];

		zet++;
		j++;
	}


}

void Element4::macierzHBCorazWektorP() {


	for (int i = 0; i < struktura.nE; i++) {
		for (int j = 0; j < 4; j++) {
			for (int z = 0; z < 4; z++) {
				HBC[i][j][z] += boki[0].HBC[i][j][z] + boki[1].HBC[i][j][z] + boki[2].HBC[i][j][z] + boki[3].HBC[i][j][z];
			}
		}
	}

	for (int i = 0; i < struktura.nE; i++) {
		for (int j = 0; j < 4; j++) {
			P[i][j] = boki[0].P[i][j] + boki[1].P[i][j] + boki[2].P[i][j] + boki[3].P[i][j];
		}
	}

}

void Element4::macierzHplusC() {

	int loop = pow(rozmiar, 2);

	vector<vector<double>> dNxT = T(pochodnaDlaNPoX);
	vector<vector<double>> dNyT = T(pochodnaDlaNPoY);

	int index_pom = 0;
	int index_pom_poch = 0;
	int wiersze = 0;
	int licznikNT = 0;
	int szybkapom = 0;
	for (int i = 0; i < struktura.nE; i++) { //po elementach
		licznikNT = 0;
		for (int j = 0; j < loop; j++) { //po punktach
			for (int k = 0; k < 4; k++) { //po wierszu
				for (int l = 0; l < 4; l++) {//po kolumnie
					macierzH[wiersze][l] = dane.pc * (dNxT[index_pom][0] * pochodnaDlaNPoX[index_pom_poch][l] + dNyT[index_pom][0] * pochodnaDlaNPoY[index_pom_poch][l]) * detJ[szybkapom];
					macierzC[wiersze][l] = dane.cp * dane.gamma * (N[j][l] * NT[licznikNT][0]) * detJ[szybkapom];
					//cout << "Licze macierzC dla elementu " << i + 1 << " i pc " <<j+1 << ": \n\tWymnazanie funkcji ksztaltu : " << N[j][l] << " * " << NT[licznikNT][0]<< "\n\twyznacznik jakbobiego : " << detJ[szybkapom] << "\n\t gestosc oraz cieplo wlasciwe : " << dane.gamma << " i " << dane.cp << endl;
				}
				wiersze++;
				index_pom++;
				licznikNT++;
			}
			if (j != loop - 1) {
				index_pom += 4 * loop;
				index_pom_poch += loop + 1;
			}
			else {
				index_pom_poch++;
			}
			szybkapom++;

		}
	}

	/*
	cout << "\nMACIERZ C, rozmiar :  " << macierzC.size() << endl;
	for (int i = 0; i < macierzC.size(); i++) {
		if (i != 0 && i % 4 == 0) cout << "\n\n";
		for (int j = 0; j < 4; j++)cout << macierzC[i][j] << " ";
		cout << "\n";
	}
	*/
	int pom = 0;
	int pom2 = 0;
	int pom3 = 0;
	int k = 0;
	int licz = 1;

	while (k != 4 * struktura.nE) {

		if (k != 0 && loop == 4 && k % 4 == 0) {
			pom3 = licz * 16;
			licz++;
		}
		else if (k != 0 && loop == 9 && k % 4 == 0) {
			pom3 = licz * 36;
			licz++;
		}
		else if (k != 0 && loop == 16 && k % 4 == 0) {
			pom3 = licz * 64;
			licz++;
		}

		for (int i = 0; i < loop; i++) {
			if (pom != 0 && pom % rozmiar == 0) {
				pom = 0;
				pom2++;
			}
			if (pom2 != 0 && pom2 % rozmiar == 0) {
				pom = 0;
				pom2 = 0;
			}
			//cout << " Mnozone wspolczynnyki: " << wspolczynnik[abs(pom)] << " i " << wspolczynnik[abs(pom2)] << endl;
			//cout << "Jestem tu i MacierzH : \n kolumna " << k << "\ndodaje wartość z macierzy H " << macierzH[pom3 + i * 4][0] << "Mnoze razy: " << wspolczynnik[abs(pom)] << " * " << wspolczynnik[abs(pom2)] << " Index: " << pom3 + i * 4 << endl;
			macierzHFinall[k][0] += macierzH[pom3 + i * 4][0] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];
			macierzHFinall[k][1] += macierzH[pom3 + i * 4][1] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];
			macierzHFinall[k][2] += macierzH[pom3 + i * 4][2] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];
			macierzHFinall[k][3] += macierzH[pom3 + i * 4][3] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];

			macierzCFinall[k][0] += macierzC[pom3 + i * 4][0] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];
			macierzCFinall[k][1] += macierzC[pom3 + i * 4][1] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];
			macierzCFinall[k][2] += macierzC[pom3 + i * 4][2] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];
			macierzCFinall[k][3] += macierzC[pom3 + i * 4][3] * wspolczynnik[abs(pom)] * wspolczynnik[abs(pom2)];

			pom++;
		}
		pom3++;
		k++;
	}

	int elem = 0;
	int wiersz = 0;


	for (int i = 0; i < macierzHFinall.size(); i++) {
		if (i != 0 && i % 4 == 0) {
			elem++;
			wiersz = 0;
		}
		//cout << "ELEMENT NUMER: " << elem << "\n\n";
		for (int j = 0; j < 4; j++) {
			//cout << "Dodaje do " << macierzHFinall[i][j] << " wartsc z boku: " << boki[0].HBC[elem][wiersz][j] << endl;
			macierzHFinall[i][j] += HBC[elem][wiersz][j];

		}
		wiersz++;
	}
}

void Element4::Agregacja() {
	//cout << "AGREGUJE" << endl;
	int i = 0;
	int j = 0;
	int loop = pow(rozmiar, 2);
	//IDEXy to jest miejsce w macierzy (mapowanie) gdzie dodajemy wartości
	for (int k = 0; k < struktura.nE; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				agregacja[dane.pom_nE[k].ID[i] - 1][dane.pom_nE[k].ID[j] - 1] += macierzHFinall[i + k * 4][j];
				agregacjaMacierzyC[dane.pom_nE[k].ID[i] - 1][dane.pom_nE[k].ID[j] - 1] += macierzCFinall[i + k * 4][j];
			}
		}
	}

	for (int i = 0; i < struktura.nE; i++) {
		for (int j = 0; j < 4; j++) {
			pAgregowane[dane.pom_nE[i].ID[j] - 1][0] += P[i][j];
		}
	}
	/*
	cout << "\nAgregacaj P: " << endl;
	for (int i = 0; i < struktura.nN; i++) {
		cout << pAgregowane[i][0] << endl;
	}
	cout << endl << endl;
	cout << "\nAgegacja macierzy H (z warunkiem brzegowym): " << endl;
	for (int i = 0; i < agregacja.size(); i++) {;
		for (int j = 0; j < 16; j++)cout << agregacja[i][j] << " ";
		cout << "\n";
	}

	cout << "\nAgegacja macierzy C: " << endl;
	for (int i = 0; i < agregacjaMacierzyC.size(); i++) {
		;
		for (int j = 0; j < 16; j++)cout << agregacjaMacierzyC[i][j] << " ";
		cout << "\n";
	}
	*/
}

//Rozwiązując równianie metodą eliminacji Gaussa otrzymujemy nN równań (dla każdego węzła)
//wzór x = n + 1 (np dla 1 elementu 5 + 1 = 6) określa na ilu miejscach w macierzy nN x nN
//pojawią się elemnty, a na pozostałych miejscach 0 
void Element4::obliczanieTemperaturyNaWezlach() {

	//cout.precision(4);
	vector <vector<double >> pom(struktura.nN, vector<double>(1, 0.0));
	vector <vector<double >> tempT0(struktura.nN, vector<double>(1, 0.0));
	vector <vector<double >> pom2(struktura.nN, vector<double>(struktura.nN + 1, 0.0));
	vector <vector<double >> clean(struktura.nN, vector<double>(struktura.nN + 1, 0.0));
	vector <vector<double >> pom3(struktura.nN, vector<double>(1, 0.0));



	//uzupełnienie wartościami wektora T0
	for (int i = 0; i < tempT0.size(); i++) {
		tempT0[i][0] = dane.pom_nN[i].nodeTemp;
	}

	cout << "===========================" << endl;
	double time = dane.delt;

	while (time <= dane.simulationTime) {
		pom2 = clean;
		//Obliczenie 
		for (int i = 0; i < tempT0.size(); i++) {
			pom3[i][0] = pAgregowane[i][0];
			for (int j = 0; j < tempT0.size(); j++) {
				pom3[i][0] += (agregacjaMacierzyC[i][j] / dane.delt) * tempT0[j][0]; //Macierz C /krok czasowy * temperatura poczatkowa
				//cout << "Temperatura na wezle " << i << ": " << tempT0[j][0] << " * " << agregacjaMacierzyC[i][j] << " / " << dane.delt << " + " << pAgregowane[i][0] << " = " << pom3[i][0] << endl;
			}
		}



		//przołączenie macierzy w jedną
		for (int i = 0; i < struktura.nN; i++) {
			for (int j = 0; j < struktura.nN + 1; j++) {
				if (j == struktura.nN) {
					pom2[i][j] += pom3[i][0]; //dodanie prawej strony
				}
				else {
					pom2[i][j] += agregacja[i][j] + (agregacjaMacierzyC[i][j] / dane.delt);
				}
			}
		}

		//metoda Crouta:
		for (int i = 0; i < struktura.nN; i++) { // jeżeli wartości nie są odpowiednio ułożone w macierzy
			for (int j = i + 1; j < struktura.nN; j++) {
				if (abs(pom2[i][i]) < abs(pom2[j][i])) {
					for (int k = 0; k < struktura.nN + 1; k++) {
						pom2[i][k] = pom2[i][k] + pom2[j][k];
						pom2[j][k] = pom2[i][k] - pom2[j][k];
						pom2[i][k] = pom2[i][k] - pom2[j][k];
					}
				}
			}
		}

		long double mnoznik = 0.0;

		//metoda eliminacji gaussa

		for (int i = 0; i < struktura.nN - 1; i++) { // petla po wierszach ktore sa odejmowane
			for (int j = i + 1; j < struktura.nN; j++) { // pętla po wierszach od ktorych sie odejmuje
				mnoznik = (long double)pom2[j][i] / (long double)pom2[i][i];
				//cout << "Obliczony mnoznik : " << pom2[j][i] << " / " << pom2[i][i] << "\nmnoznik: "<< mnoznik << endl;
				for (int k = i; k < struktura.nN + 1; k++) { //petla po kolumnach
					pom2[j][k] -= pom2[i][k] * mnoznik;
					//	if (k != struktura.nN) cout << "Stara wartosc: " << agregacja[j][k] << " Oblcizylem nowa wartosci: " << pom2[j][k] << " przejscie petli: " << k << endl;
				}
			}
		}
		//postępowanie odwrotne w celu znalezienia rozwiązania układu równań
		for (int i = struktura.nN - 1; i >= 0; i--) {
			pom[i][0] = pom2[i][struktura.nN];
			for (int j = i + 1; j < struktura.nN; j++) {
				if (i != j) {
					pom[i][0] = pom[i][0] - pom2[i][j] * pom[j][0];
				}
			}
			pom[i][0] = pom[i][0] / pom2[i][i];
		}

		double minTemp = pom[0][0], maxTemp = pom[0][0];

		cout << "temperatury: " << endl;
		for (int i = 0; i < pom.size() - 1; i++) {
			if (minTemp > pom[i][0]) minTemp = pom[i][0];
			if (maxTemp < pom[i][0]) maxTemp = pom[i][0];
		}

		tempT0 = pom;


		cout << "Time[s]   MinTemp[s]   MaxTemp[s]\n" << time << "      " << minTemp << "      " << maxTemp << endl;
		time += dane.delt;
	}

	//Uzupełnienie temperatury poszczegolnych wezlow
	for (int i = 0; i < tempT0.size(); i++) {
		dane.pom_nN[i].nodeTemp = tempT0[i][0];
	}
}

void Element4::print() {
	int loop = pow(rozmiar, 2);
	/*
	cout << "\nMACIERZ FINALL H: " << endl;
	for (int i = 0; i < macierzHFinall.size(); i++) {
		if (i != 0 && i % 4 == 0) cout << "\n\n";
		for (int j = 0; j < 4; j++)cout << macierzHFinall[i][j] << " ";
		cout << "\n";
	}
	*/
	/*
	cout << "Otrzymana macierz dla pochodnej po Ksi: \n";
	for (int i = 0; i < loop; i++) {
		for (int j = 0; j < 4; j++) cout << pochodna_ksi[i][j] << "   ";
		cout << "\n";
	}

	cout << "\nOtrzymana macierz dla pochodnej po Eta: \n";
	for (int i = 0; i < loop; i++) {
		for (int j = 0; j < 4; j++) cout << pochodna_eta[i][j] << "   ";
		cout << "\n";
	}
	cout << "\nWartosc pochodnej N po y: " << endl;
	for (int i = 0; i < struktura.nE * loop; i++) {
		if (i != 0 && i % loop == 0) cout << "\n\n";
		for (int k = 0; k < 4; k++) {
			cout << pochodnaDlaNPoY[i][k] << " \t ";
		}
		cout << endl;
	}
	cout << "\n\nWartosc pochodnej N po X: " << endl;
	for (int i = 0; i < struktura.nE * loop; i++) {
		if (i != 0 && i % loop == 0) cout << "\n\n";
		for (int k = 0; k < 4; k++) {
			cout << pochodnaDlaNPoX[i][k] << " \t ";
		}
		cout << endl;
	}
	int element = 1;
	int pc = 1;
	cout << "\nMACIERZ H: \n Dla ELEMENTU 1, PC 1:" << endl;

	for (int i = 0; i < macierzH.size(); i++) {
		if (i != 0 && i % 4 == 0) {
			pc++;
			if (pc == pow(rozmiar, 2) + 1) {
				element++;
				pc = 1;
				cout << "\n\n Dla Elementu " << element << endl;
			}
				cout << "\n\n Dla PC " << pc << endl;

		}
		for (int j = 0; j < 4; j++)cout << macierzH[i][j] << " ";
		cout << "\n";
	}
		*/
}



vector <vector<double>> Element4::T(vector <vector<double>>& pom) {
	vector <vector<double>> transpozycja;
	for (int k = 0; k < pom.size(); k++) {
		for (int i = 0; i < pom[k].size(); i++) {
			transpozycja.push_back({ pom[k][i] });
		}
	}

	return transpozycja;
}

vector <vector<double>> T(vector <vector<double>>& pom, int pc) {
	vector <vector<double>> transpozycja;
	for (int k = 0; k < pc; k++) {
		for (int i = 0; i < pom[k].size(); i++) {
			transpozycja.push_back({ pom[k][i] });

		}
	}

	return transpozycja;
}



//Funkcje z których oblicana jest calka:

double return_funkcja(double x) {
	return (2 * pow(x, 2) + 3 * x - 8);
}

double return_funkcja2(double ksi, double eta) {
	return (-5 * pow(ksi, 2) * eta + 2 * ksi * pow(eta, 2) + 10);
}

double return_funkcja3(double x) {
	return (pow(x, 2) - 3 * x + 6);
}


//Całkowanie przy użyciu kwadratury Gaussa:

double calkowanie() { //Funkcja wywoływana do całkowania
	//cout.precision(9);
	int pom = 0;
	double wynik = 0.0;
	cout << "Podaj przestrzen w ktorej operujesz: \n\t1) 1D; \n\t2) 2D; \n";
	cin >> pom;
	double wezly[2] = { (double)(-1.0 / sqrt(3.0)),  (double)(1.0 / sqrt(3.0)) };
	double wspolczynnik[2] = { 1.0, 1.0 };
	double wezly2[3] = { -((double)sqrt(3.0 / 5.0)), 0.0, (double)(sqrt((3.0 / 5.0))) };
	double wspolczynnik2[3] = { (5.0 / 9.0), (8.0 / 9.0), (5.0 / 9.0) };

	double eta[4] = { -0.57735, -0.57735, 0.57735, 0.57735 };


	if (pom == 1) {

		cout << "Wybierz zakres calkowania: \n\t1) od -1 do 1; \n\t2) od 3 do 8; \n";
		cin >> pom;
		if (pom == 1) {
			cout << "\nDla dwoch punktow: " << endl;
			wynik = kwadratury(wezly, wspolczynnik, pom + 1, 2);

			cout << "\nDla trzech punktow: " << endl;
			wynik = kwadratury(wezly2, wspolczynnik2, pom + 1, 3);
		}
		else {
			cout << "\nDla dwoch punktow: " << endl;
			wynik = kwadratury(wezly, wspolczynnik, pom, 3, 8);

			cout << "\nDla trzech punktow: " << endl;
			wynik = kwadratury(wezly2, wspolczynnik2, pom + 1, 3, 8);
		}


	}
	else if (pom == 2) {

		cout << "\nDla dwoch punktow: " << endl;
		wynik = kwadratury(wezly, wspolczynnik, pom + 1, 2);
		cout << "\nDla trzech punktow: " << endl;
		wynik = kwadratury(wezly2, wspolczynnik2, pom + 1, 3);

	}
	else {
		cout << "Niepoprawna ilosc wezlow!" << endl;
		return 0;
	}
	return wynik;
}

double kwadratury(double wezly[], double wspolczynnik[], int ilosc_wezlow, int petla) {  //Funkcja wywoływana przez calkowanie(), oblicza calke od <-1,1> dla 1di 2 d
//	cout.precision(9);
	cout << "\tMetoda kwadratur " << ilosc_wezlow - 1 << "-wych" << endl;
	cout << "Calkowanie funkcji w przedziale od -1 do 1" << "\n\n";
	double wynik = 0;
	if (ilosc_wezlow == 2) {
		for (int i = 0; i < petla; i++) {

			cout << "Wartosc funckji to: " << return_funkcja(wezly[i]) << endl;
			wynik += return_funkcja(wezly[i]) * wspolczynnik[i];
		}
	}
	else if (ilosc_wezlow == 3) {
		for (int i = 0; i < petla; i++) {
			for (int j = 0; j < petla; j++) {
				wynik += return_funkcja2(wezly[i], wezly[j]) * wspolczynnik[i] * wspolczynnik[j];
			}
		}
	}
	else {
		cout << "Niepoprawna liczba wezlow!";
		return 0;
	}

	cout << "wynik metody kwadratur: " << ilosc_wezlow - 1 << "-wych: " << wynik << endl;
	return wynik;

}


double kwadratury(double wezly[], double wspolczynnik[], int petla, int poczatek, int koniec) { //Funkcja wywoływana przez calkowanie(), dla przedzialu od <3,8>
	//cout.precision(9);
	cout << "\tMetoda kwadratur dla calki z poza przedzialu <-1, 1> " << endl;
	cout << "Calkowanie funkcji w przedziale od 3 do 8" << "\n\n";
	double wynik = 0.0;
	vector <double> t(petla);
	double dltJ = (koniec - poczatek) * 0.5;

	for (int i = 0; i < petla; i++) {
		t[i] = (1 - wezly[i]) * 0.5 * poczatek + (wezly[i] + 1) * 0.5 * koniec; //Poniewaz znamy wynik dla punktu z przedzialu od <-1;1>, nie jako skalujemy ten sam przedział (stad 1 - wezel[i]/2) o x1 i w drugim przypadku o x2
	}
	for (int j = 0; j < petla; j++) {
		wynik += (return_funkcja3(t[j]) * wspolczynnik[j]);
		cout << "Wartosc funckji to: " << wynik << endl;
	}
	wynik = wynik * dltJ;
	cout << "wynik kocowy: " << wynik << endl;
	return wynik;
}


//==============================================READDATAFROMFILE==============================================
void readFromFile() {
	double x = 0.0;
	string usun;
	string wyraz;

	cout.precision(6);


	ifstream odczyt;
	//odczyt.open("Test1_4_4.txt");
	//odczyt.open("Test2_4_4_MixGrid.txt");
	odczyt.open("Test3_31_31_kwadrat.txt");

	do {
		odczyt >> wyraz;
		if (wyraz == "SimulationTime") {
			odczyt >> dane.simulationTime;
		}
		else if (wyraz == "SimulationStepTime") {
			odczyt >> dane.delt;
		}
		else if (wyraz == "Conductivity") {
			odczyt >> dane.pc;
		}
		else if (wyraz == "Alfa") {
			odczyt >> dane.alfa;
		}
		else if (wyraz == "Tot") {
			odczyt >> dane.tOt;
		}
		else if (wyraz == "InitialTemp") {
			odczyt >> dane.initialTemp;
		}
		else if (wyraz == "Density") {
			odczyt >> dane.gamma;
		}
		else if (wyraz == "SpecificHeat") {
			odczyt >> dane.cp;
		}
		else if (wyraz == "Nodes") {
			odczyt >> wyraz;
			odczyt >> struktura.nN;
			dane.pom_nN = Utworz_nN(struktura.nN);
			for (int i = 0; i < struktura.nN; i++) { //uzupełnienie temperatury wezłów
				dane.pom_nN[i].nodeTemp = dane.initialTemp;
			}
		}
		else if (wyraz == "Elements") {
			odczyt >> wyraz;
			cout << wyraz << endl;
			odczyt >> struktura.nE;
			dane.pom_nE = Utworz_nE(struktura.nE);
		}
		else if (wyraz == "*Node" || wyraz == "*BC") {
			if (wyraz == "*Node") {
				for (int i = 0; i < struktura.nN; i++) {
					odczyt >> wyraz;
					odczyt >> dane.pom_nN[i].x;
					odczyt >> usun;
					odczyt >> dane.pom_nN[i].y;
				}
			}
			else {
				int pom = 0;
				for (;;) {
					odczyt >> pom;
					dane.pom_nN[pom - 1].BC += 1;
					odczyt >> usun;
					if (odczyt.eof()) { break; }
				}
			}
		}
		else if (wyraz == "*Element,") {
			odczyt >> wyraz;
			for (int i = 0; i < struktura.nE; i++) {
				odczyt >> wyraz;
				for (int j = 0; j < 4; j++) {
					odczyt >> dane.pom_nE[i].ID[j];
					if (j < 3) odczyt >> usun;
				}
			}
		}
		else {
			continue;
		}
	} while (!odczyt.eof());
}


int main() {
	//cout.precision(6);
	readFromFile();
	Element4 Element4_obj(4, 4);
	//Element4_obj.print();

	//calkowanie();

	int pomx = 1;


	return 0;
}

