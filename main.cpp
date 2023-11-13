#include "pred.h"

int main() {
	int op, k;
	string s1, s2;
	double slic;


	cout << "Ime datoteke: ";
	cin >> s1;
	Graf graf(s1 + ".txt");
	cout << "1.Ispisi reprezentaciju grafa" << endl;
	cout << "2.Dodaj cvor" << endl;
	cout << "3.Dodaj granu" << endl;
	cout << "4.Brisi cvor" << endl;
	cout << "5.Brisi granu" << endl;
	cout << "6.Brisi graf" << endl;
	cout << "7.Ispisi k najslicnijih reci" << endl;
	cout << "8.Ispisi najkraci put" << endl;
	cout << "9.Ispisi jako povezane komponente" << endl;
	while (true) {
		cin >> op;
		switch (op)
		{
		case 1: {
			graf.ispisi();
			break;
		}
		case 2: {
			cout << "Novi cvor(rec): ";
			cin >> s1;
			graf.dodajCvor(s1);
			break;
		}
		case 3: {
			cout << "Nova grana(rec1 rec2 slicnost): ";
			cin >> s1 >> s2 >> slic;
			graf.dodajGranu(s1, s2, slic);
			break;
		}
		case 4: {
			cout << "Brisi cvor(rec): ";
			cin >> s1;
			graf.brisiCvor(s1);
			break;
		}
		case 5: {
			cout << "Brisi granu(rec1 rec2): ";
			cin >> s1 >> s2;
			graf.brisiGranu(s1, s2);
			break;
		}
		case 6: {
			graf.obrisi();
			cout << "Graf je obrisan" << endl;
			break;
		}
		case 7: {
			cout << "Unesite rec i broj k: ";
			cin >> s1 >> k;
			cout << "Najslicnije reci sa recju " << s1 << " su: " << endl;
			graf.najslicnijeReci(s1, k);
			break;
		}
		case 8: {
			cout << "Unesite dve reci: ";
			cin >> s1 >> s2;
			cout << "Najkraci put izmedju njih je: " << endl;
			graf.ispisiPut(s1, s2);
			break;
		}
		case 9: {
			cout << "Unesite rec: ";
			cin >> s1;
			cout << "Njene jako povezane komponente su: " << endl;
			graf.ispisiJakoPovezane(s1);
			break;
		}
		default:
			break;
		}
	}
	
	}