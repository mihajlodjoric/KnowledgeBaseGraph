#ifndef _graf_h_
#define _graf_h_
#include <iostream>
#include <fstream>
using namespace std;

class Graf {
	int brCvorova;
	struct Elem {
		string rec;
		Elem* sled;
		double slicnost;
		Elem(string r, double f = 0) : rec(r), slicnost(f), sled(nullptr) {}
	};

	struct Cvor {
		string rec;
		Elem* prvi;
		Cvor* sled;
		int br = 0;
		Cvor(string r) : rec(r), prvi(nullptr), sled(nullptr) {}
	};
	Cvor* prvi;
	friend class PRed;
	PRed* dijkstra(string s);
public:

	Graf(string imeDatoteke);
	Graf(Graf& graf) = delete;
	~Graf() { obrisi(); }
	void ispisi();
	void obrisi();
	void dodajCvor(string rec);
	void brisiCvor(string rec);
	void dodajGranu(string rec1, string rec2, double t);
	void brisiGranu(string rec1, string rec2);

	void najslicnijeReci(string rec, int k);
	void ispisiPut(string rec1, string rec2);
	void ispisiJakoPovezane(string rec);

};

#endif //_graf_h_
