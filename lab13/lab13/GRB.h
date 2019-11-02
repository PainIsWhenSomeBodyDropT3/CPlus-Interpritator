#pragma once
#include "Error.h"
typedef short GRBHALPHABET;	//символ алфавита
namespace GRB {
	struct Rule {	//правило в граматике
		GRBHALPHABET nn;	//не терминал (левый символ)
		int idError;
		short size;	//кол-во повторений правых правил
		struct Chain {	//правая часть правила
			short size;		//размер
			GRBHALPHABET* nt;	//список терминалов и нетерминалов
			Chain() { size = 0; nt = 0; };
			Chain(short psize, GRBHALPHABET s, ...);
			char* getCChain();	//получить правую часть правила
			static GRBHALPHABET T(char t) { return GRBHALPHABET(t); };	//трэмінал
			static GRBHALPHABET N(char n) { return -GRBHALPHABET(n); };	//не тэрмінал
			static bool isT(GRBHALPHABET s) { return s > 0; };
			static bool isN(GRBHALPHABET s) { return !isT(s); };
			static char alphabet_to_char(GRBHALPHABET s)
			{
				return isT(s) ? char(s) : char(-s);
			}
		}*chains;
		Rule() {
			nn = 0x00;
			size = 0;
		}
		Rule(GRBHALPHABET pnn, int idError, short psize, Chain c, ...);
		char *getCRule(short nchain);	//получить правило в виде строки
		short getNextChain(
			GRBHALPHABET t, Rule::Chain& pchain, short j
		);	//получить след цепочку
	};
	struct Greibach {
		short size;		//кол-во правил
		GRBHALPHABET startN;	//начальный символ
		GRBHALPHABET stbottomT;	//дно стэка
		Rule* rules;//правила
		Greibach() {
			short size = 0;
			startN = 0;
			stbottomT = 0;
			rules = 0;
		};
		Greibach(
			GRBHALPHABET pstartN,
			GRBHALPHABET pstbottomT,
			short psize,
			Rule r, ...
		);
		short getRule(
			GRBHALPHABET pnn,
			Rule& prule
		);	//получить номер правила 
		Rule getRule(short n);	//получить правило с номера
	};
	Greibach getGreibach();
}
