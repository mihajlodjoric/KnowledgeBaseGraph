#include "pred.h"

void PRed::ubaci(Graf::Cvor* cvor, Graf::Cvor* prcvor, double slicnost) {
	ElemR* novi = new ElemR(cvor, prcvor, slicnost), * tek = prvi, * preth = nullptr;
	while (tek && (slicnost < tek->slicnost || (slicnost == tek->slicnost && cvor->rec > tek->cvor->rec))) { preth = tek; tek = tek->sled; }
	novi->sled = tek;
	if (!preth) maks = prvi = novi;
	else {
		preth->sled = novi;
		if (maks->slicnost < novi->slicnost) maks = novi;
	}
}
PRed::PRed(Graf& graf, string rec) {
	Graf::Cvor* cvor = graf.prvi;
	while (cvor && cvor->rec != rec) cvor = cvor->sled;
	if (!cvor) prvi = maks = nullptr;
	else {
		Graf::Elem* tekEl = cvor->prvi;
		Graf::Cvor* tek = graf.prvi;

		while (tek) {
			if (tek->rec != cvor->rec) {
				if (!tekEl || tek->rec != tekEl->rec) {
					ubaci(tek, nullptr, 0);
				}
				else {
					ubaci(tek, cvor, tekEl->slicnost);
					tekEl = tekEl->sled;
				}
			}
			tek = tek->sled;
		}
	}
}


PRed::ElemR* PRed::izbaci(ElemR* e) {
	ElemR* tek = maks, * preth = nullptr;
	while (tek->sled && tek != e) { preth = tek; tek = tek->sled; }
	preth->sled = tek->sled;
	return tek;
	
}