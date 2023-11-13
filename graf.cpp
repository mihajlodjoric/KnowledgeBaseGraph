#include "graf.h"
#include "pred.h"
class Stek {
	struct ElemS {
		string rec;
		double slicnost;
		ElemS* sled;
		ElemS(string r, double s) : rec(r), slicnost(s), sled(nullptr) {}
	};
	ElemS* vrh = nullptr;
public:
	void push(string r, double s) {
		ElemS* novi = new ElemS(r, s);
		novi->sled = vrh;
		vrh = novi;
	}
	void pisi(bool strela) {
		if (vrh) {
			if (strela) cout << "-(" << vrh->slicnost << ")->";
			cout << vrh->rec;
			vrh = vrh->sled;
		}
		else return;
	}
	bool prazan() const { return !vrh; }
	string dohvVrh() const { return vrh->rec; }
	void brisi() {
		ElemS* stari;
		while (!prazan()) {
			stari = vrh;
			vrh = vrh->sled;
			delete stari;
		}
	}
};
Graf::Graf(string imeDatoteke) {
	ifstream file(imeDatoteke);
	int n, e;
	float f;
	string s1, s2;
	file >> n >> e;
	brCvorova = n;
	Cvor* prvi = nullptr, * preth = nullptr;
	for (int i = 0; i < n; i++) {
		file >> s1;
		Cvor* novi = new Cvor(s1);
		if (!prvi) prvi = novi;
		else preth->sled = novi;
		preth = novi;
	}

	Cvor* tek = prvi;
	Elem* poslEl = nullptr;
	for (int i = 0; i < e; i++) {
		file >> s1 >> s2 >> f;
		Elem* novi = new Elem(s2, f);
		while (tek && tek->rec != s1) {
			tek = tek->sled;
			poslEl = nullptr;
		}
		if (!poslEl) { tek->prvi = novi; }
		else { poslEl->sled = novi; };
		poslEl = novi;
	}
	this->prvi = prvi;
}
void Graf::ispisi() {
	Cvor* tek = prvi;
	int i = 1;
	while (tek) {
		cout << i++ << ". " << tek->rec;
		Elem* tekEl = tek->prvi;
		while (tekEl) {
			cout << " -> ";
			cout << tekEl->rec;
			cout << "(" << tekEl->slicnost << ")";
			tekEl = tekEl->sled;
		}
		tek = tek->sled;
		cout << endl;
	}


}
void Graf::dodajCvor(string rec) {
	Cvor* tek = prvi, * posl = nullptr;
	Cvor* novi = new Cvor(rec);
	while (tek && rec > tek->rec) {
		posl = tek;
		tek = tek->sled;
	}
	novi->sled = tek;
	if (!posl) prvi = novi;
	else posl->sled = novi;

}
void Graf::brisiCvor(string rec) {
	Cvor* tek = prvi, * stari, * posl = nullptr;
	while (tek) {
		stari = tek;
		tek = tek->sled;
		if (stari->rec == rec) {
			if (!posl) prvi = tek;
			else posl->sled = tek;
			Elem* tekEl = stari->prvi, * stariEl;
			while (tekEl) {
				stariEl = tekEl;
				tekEl = tekEl->sled;
				delete stariEl;
			}
			posl = stari;
			delete stari;
		}
		else {
			Elem* tekEl = stari->prvi, * poslEl = nullptr;
			while (tekEl && tekEl->rec != rec) {
				poslEl = tekEl;
				tekEl = tekEl->sled;
			}
			if (tekEl) {
				if (!poslEl) stari->prvi = tekEl->sled;
				else poslEl->sled = tekEl->sled;
				delete tekEl;
			}
			posl = stari;
		}
	}
}
void Graf::dodajGranu(string rec1, string rec2, double t) {
	Cvor* tek = prvi;
	while (tek && tek->rec != rec1) tek = tek->sled;
	if (!tek) return;
	Elem* tekEl = tek->prvi, * poslEl = nullptr;
	while (tekEl && rec2 > tekEl->rec) { poslEl = tekEl; tekEl = tekEl->sled; }
	Elem* novi = new Elem(rec2, t);
	novi->sled = tekEl;
	if (!poslEl) tek->prvi = novi;
	else poslEl->sled = novi;
}
void Graf::brisiGranu(string rec1, string rec2) {
	Cvor* tek = prvi;
	while (tek && tek->rec != rec1) tek = tek->sled;
	if (!tek) return;
	Elem* tekEl = tek->prvi, * poslEl = nullptr;
	while (tekEl && rec2 != tekEl->rec) { poslEl = tekEl; tekEl = tekEl->sled; }
	if (!tekEl) return;
	if (!poslEl) { tek->prvi = tekEl->sled; }
	else poslEl->sled = tekEl->sled;
	delete tekEl;
}
void Graf::obrisi() {
	Cvor* tek = prvi, * stari;
	while (tek) {
		stari = tek;
		tek = tek->sled;
		Elem* tekEl = stari->prvi, * stariEl;
		while (tekEl) {
			stariEl = tekEl;
			tekEl = tekEl->sled;
			delete stariEl;
		}
	}
	prvi = nullptr;
}
PRed* Graf::dijkstra(string s) {
	PRed* pRed = new PRed(*this, s);
	if (!pRed->maks) return nullptr;
	while (pRed->maks->sled) {
		PRed::ElemR* maks = pRed->izbaciMaks();
		Cvor* cvor = maks->cvor;
		PRed::ElemR* tek = pRed->maks;
		while (tek) {
			Elem* tekEl = cvor->prvi;
			while (tekEl) {
				if (tek->cvor->rec < tekEl->rec) { tek = tek->sled; break; };
				if (tek->cvor->rec == tekEl->rec) {
					if (maks->slicnost * tekEl->slicnost > tek->slicnost) {
						if (tek == pRed->maks) {
							tek->slicnost = maks->slicnost * tekEl->slicnost;
							tek->prethCvor = maks->cvor;
							tek = tek->sled;
							break;
						}
						else {
							PRed::ElemR* stari = tek;
							tek->prethCvor = maks->cvor;
							tek = tek->sled;
							stari = pRed->izbaci(stari);
							pRed->ubaci(stari->cvor, stari->prethCvor, maks->slicnost * tekEl->slicnost);
							delete stari;
							break;
						}
					}
					else { tek = tek->sled; break; }
				}
				tekEl = tekEl->sled;
			}
			if (!tekEl) tek = tek->sled;
		}
	}
	
	return pRed;
}
void Graf::najslicnijeReci(string rec, int k) {
	PRed* pRed = dijkstra(rec);
	if (!pRed) return;
	PRed::ElemR* tek = pRed->prvi;
	while (tek && k-- && tek->slicnost) {
		cout << tek->cvor->rec << "(" << tek->slicnost << ")" << endl;
		tek = tek->sled;
	}
}
void Graf::ispisiPut(string rec1, string rec2) {
	Stek stek;
	string rec = rec2, pRec;
	double slicnost;
	PRed* red = dijkstra(rec1);
	PRed::ElemR* tek;
	while (red && rec != rec1){
		tek = red->prvi;
		while (tek && tek->cvor->rec != rec) tek = tek->sled;
		if (!tek || tek->slicnost == 0) break;
		Elem* tekEl = tek->prethCvor->prvi;
		while (tekEl->rec != rec) tekEl = tekEl->sled;
		slicnost = tekEl->slicnost;
		stek.push(rec, slicnost);
		rec = tek->prethCvor->rec;
	}
	stek.push(rec, 0);
	if (rec == rec2) cout << "Put ne postoji";
	else while (!stek.prazan()) stek.pisi(stek.dohvVrh() != rec1);
	stek.brisi();
	cout << endl;
}
void Graf::ispisiJakoPovezane(string s) {

	PRed** mat = new PRed*[brCvorova];
	Cvor* tekCvor = this->prvi;
	PRed* red = nullptr;
	int i = 0;
	while (tekCvor) {
		mat[i] = dijkstra(tekCvor->rec);
		tekCvor->br = i;
		if (tekCvor->rec == s) red = mat[i];
		tekCvor = tekCvor->sled;
		i++;
	}
	PRed::ElemR* tekI = red->prvi;
	while (tekI && tekI->slicnost != 0) {
		PRed::ElemR* tekJ = mat[tekI->cvor->br]->prvi;
		while (tekJ && tekJ->cvor->rec != s) tekJ = tekJ->sled;
		if (!tekJ || tekJ->slicnost == 0);
		else cout << tekI->cvor->rec << endl;
		tekI = tekI->sled;
	}
	
}