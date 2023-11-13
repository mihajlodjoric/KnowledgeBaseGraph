#ifndef _pred_h
#define _pred_h_
#include "graf.h"

class PRed {
	struct ElemR {
		Graf::Cvor* cvor, * prethCvor;
		double slicnost;
		ElemR* sled;
		ElemR(Graf::Cvor* c, Graf::Cvor* p, double s) : cvor(c), prethCvor(p), slicnost(s), sled(nullptr) {}

	};
	ElemR* prvi = nullptr, * maks = nullptr;

	friend Graf;
public:
	PRed(Graf& graf, string rec);

	void ubaci(Graf::Cvor* cvor, Graf::Cvor* prcvor, double sl);
	ElemR* izbaciMaks() { ElemR* m = maks; if (maks) maks = maks->sled; return m; }
	ElemR* izbaci(ElemR* e);
};

#endif //_pred_h_