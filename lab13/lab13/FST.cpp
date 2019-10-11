#include"fst.h"

FST::RELATION::RELATION(char c, short ns) {
	nnode = ns;
	symbol = c;
}

FST::NODE::NODE() {
	n_relation = 0;
	relations = NULL;
}

FST::NODE::NODE(short n, RELATION rel, ...) {
	n_relation = n;
	relations = new RELATION[n];
	RELATION* temp = &rel;
	for (int i = 0; i < n; i++, temp++)
		relations[i] = *temp;
}

FST::FST::FST(char * s, short ns, NODE n, ...) {
	string = s;
	nstates = ns;
	position = -1;
	nodes = new NODE[ns];
	NODE *temp = &n;
	for (int i = 0; i < ns; i++, temp++)
		nodes[i] = *temp;
	rstates = new short[ns];
	memset(rstates, 0xff, sizeof(short)*ns);
	rstates[0] = 0;
}
void FST::newFST(FST& f, char* str)
{
	f.position = -1;
	f.string = str;
	f.rstates[0] = 0;
}

bool step(FST::FST& fst, short* &rstates) {
	bool rc = false;
	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; i++) {
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; j++) {
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) {
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				};
			};
	};
	return rc;
};

bool FST::execute(FST& fst) {
	short* rstates = new short[fst.nstates];
	memset(rstates, 0xff, sizeof(short)*fst.nstates);
	short lstring = strlen(fst.string);
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++) {
		fst.position++;
		rc = step(fst, rstates);
	};
	delete[] rstates;
	return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}

void FST::udpdate(FST & fst, char* str) {
	fst.string = str;
	memset(fst.rstates, 0xff, sizeof(short)*fst.nstates);
	fst.rstates[0] = 0;
	fst.position = -1;
};
