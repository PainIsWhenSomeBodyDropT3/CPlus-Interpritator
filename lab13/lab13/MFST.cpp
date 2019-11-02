#include "MFST.h"
#include "GRB.h"
#include "Log.h"
#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

namespace MFST {
	
	Mfst::ENUM_STEP Mfst::step() {
		StateInfo();
		// находится ли в вершине стека терм символ
		if (GRB::Rule::Chain::isT(st.top()) == true) {
			if (st.top() == lenta[lenta_position]) {
				lenta_position++;
				st.pop();
				return Mfst::ENUM_STEP::TS_OK;
			}
			else {
				//pushNewDiagnosis(Mfst::ENUM_STEP::NS_NORULECHAIN);
				return Mfst::ENUM_STEP::TS_NOK;
			}
		}
		GRB::Rule rule;
		nrule = greibach.getRule(st.top(), rule);	//ищем правило
		GRB::Rule::Chain chain;

		
		if (nrule != greibach.size) {
			//выбор ленты
			if (statesStack.empty() == true || isTopStateEqual() == false) {
				nrulechain = rule.getNextChain(lenta[lenta_position], chain, -1);
			}
			else {
				nrulechain = rule.getNextChain(lenta[lenta_position], chain, statesStack.top().nrulechain);
				//ищем правую часть правила
				statesStack.pop();
			}

			if (nrulechain != -1) {
				printRule(rule, chain);
				saveState();
				st.pop();
				pushChain(chain);
				return Mfst::ENUM_STEP::NS_OK;
			}
			else {
				pushNewDiagnosis(Mfst::ENUM_STEP::NS_NORULECHAIN);
				return Mfst::ENUM_STEP::NS_NORULECHAIN;
			}
		}
		else {
			return Mfst::ENUM_STEP::NS_NORULE;
		}


		return Mfst::ENUM_STEP::LENTA_END;
	}

	//поместить правило в стек
	bool Mfst::saveState() {
		statesStack.push(*new MFST::MfstState(lenta_position, st, nrulechain, nrule));
		cout << "\n-------------------------------------State was saved: " << statesStack.size();
		return false;
	}

	//вернуться у прошлой сохр цепочке
	bool Mfst::resState() {
		if (statesStack.empty()) {
			return false;
		}
		MfstState state = statesStack.top();
		lenta_position = state.lenta_position;
		nrulechain = state.nrulechain;
		nrule = state.nrule;
		st = state.st;
		cout << "\n-------------------------------------State was reseted: " << statesStack.size();
		return true;
	}

	//закинуть в стек правую часть правила
	bool Mfst::pushChain(GRB::Rule::Chain chain) {
		for (int a = chain.size - 1; a >= 0; a--) {
			st.push(chain.nt[a]);
		}
		return false;
	}

	
	bool Mfst::start() {
		bool cycle = true;
		//statesStack.push(*new MFST::MfstState(0,st,0));
		Mfst::ENUM_STEP result;
		bool Syntax = true;
		while (cycle) {
			result = step();
			switch (result)
			{
			case MFST::Mfst::NS_OK:
				break;
			case MFST::Mfst::NS_NORULE:
				printError(result);
				cycle = false;
				break;
			case MFST::Mfst::NS_NORULECHAIN:
				printError(result);
				if (!resState()) {
					cycle = false;
					Syntax = false;
				}
				//cycle = false;
				break;
			case MFST::Mfst::NS_ERROR:
				cycle = false;
				break;
			case MFST::Mfst::TS_OK:
				if (lenta_position == lenta_size) {
					cycle = false;
					Syntax = true;
				}
				//cycle = false;
				break;
			case MFST::Mfst::TS_NOK:
				printError(result);
				if (!resState()) {
					cycle = false;
					Syntax = false;
				}
				//cycle = false;
				break;
			case MFST::Mfst::LENTA_END:
				cycle = false;
				break;
			case MFST::Mfst::SURPRISE:
				cycle = false;
				break;
			default:
				break;
			}
		}
		if (Syntax == true) {
			PrintMessage((char*)"\nYes!!!");
			while (statesStack.empty() == false) {
				printRule(greibach.getRule(statesStack.top().nrule), greibach.getRule(statesStack.top().nrule).chains[statesStack.top().nrulechain]);
				statesStack.pop();
			}
			return true;
		}
		else {
			printLastDiagnosis();
		}
		return cycle;
	}

	//вывести правило
	void printRule(GRB::Rule rule, GRB::Rule::Chain nchain) {
		std::cout << "\n-------------------------------------" << GRB::Rule::Chain::alphabet_to_char(rule.nn);
		std::cout << " -> ";
		std::cout << nchain.getCChain();
	}
	void printRule(GRBHALPHABET nt, GRB::Rule::Chain nchain) {
		std::cout << "\n-------------------------------------" << GRB::Rule::Chain::alphabet_to_char(nt);
		std::cout << " -> ";
		std::cout << nchain.getCChain();
	}
	std::string getStrRule(GRB::Rule rule, GRB::Rule::Chain nchain) {
		std::string str;
		str += GRB::Rule::Chain::alphabet_to_char(rule.nn);
		str += " -> ";
		str += nchain.getCChain();
		return str;
	}
	//информация о шагах
	void Mfst::StateInfo() {
		int length = 15;
		char *str = new char[length + 1];
		MFSTSTACK st2 = st;
		int i;
		cout << '\n';
		for (i = 0; i < length && i < lenta_size - lenta_position; i++) {
			str[i] = GRB::Rule::Chain::alphabet_to_char(lenta[lenta_position + i]);
		}
		str[i] = '\0';
		cout << setw(length) << str;
		cout << '\t';
		for (i = 0; st2.empty() == false && i < length; i++) {
			str[i] = GRB::Rule::Chain::alphabet_to_char(st2.top());
			st2.pop();
		}
		str[i] = '\0';
		cout << setw(length) << str << '\n';
	}	//информаация о шаге автомата

	//одинак вершина стека и шаг автомата
	bool Mfst::isTopStateEqual() {
		if (statesStack.top().lenta_position == lenta_position
			&& statesStack.top().st == st
			&& statesStack.top().nrulechain == nrulechain
			&& statesStack.top().nrule == nrule) {
			return true;
		};
		return false;
	}

	void PrintMessage(char* str) {
		std::cout << str;
	}

	//вывести ошибку
	void printError(Mfst::ENUM_STEP e) {
		if (e == Mfst::ENUM_STEP::NS_NORULE) {
			std::cout << "\n-------------------------------------" << "No rule";
		}
		else if (e == Mfst::ENUM_STEP::NS_NORULECHAIN) {
			std::cout << "\n-------------------------------------" << "No chain";
		}
		else if (e == Mfst::ENUM_STEP::TS_NOK) {
			std::cout << "\n-------------------------------------" << "incorrect symbol";
		}
		else if (e == Mfst::ENUM_STEP::NS_NORULE) {
			std::cout << "\n-------------------------------------" << "No rule";
		}
		else if (e == Mfst::ENUM_STEP::NS_NORULE) {
			std::cout << "\n-------------------------------------" << "No rule";
		}
	}

	Mfst::MfstDiagnosis::MfstDiagnosis(short lenta_position, ENUM_STEP step, short nrule, short nrulechain) {
		this->lenta_position = lenta_position;
		this->nrule = nrule;
		this->nrulechain = nrulechain;
		this->step = step;
	}

	//захватить новую диагностику
	void Mfst::pushNewDiagnosis(Mfst::ENUM_STEP step) {
		int k = 0;
		while (k < MFST_DAIGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) {
			k++;
		}
		if (k < MFST_DAIGN_NUMBER) {
			diagnosis[k] = MfstDiagnosis(lenta_position, step, nrule, nrulechain);
			for (int j = k + 1; j < MFST_DAIGN_NUMBER; j++) {
				diagnosis[j].lenta_position = -1;
			}
		}
	}

	//вывести прошлые дигностики
	void Mfst::printLastDiagnosis() {
		int k = 0;
		while (k < MFST_DAIGN_NUMBER && diagnosis[k].lenta_position != -1) {
			std::string str = "\n";
			str += "line: ";
			str += std::to_string(LT::GetEntry(lexTable, diagnosis[k].lenta_position)->sn);
			str += ", ";
			str += Error::getError(greibach.getRule(diagnosis[k].nrule).idError).message;
			/*str+=". ";
			str+= getStrRule(greibach.getRule(diagnosis[k].nrule), greibach.getRule(diagnosis[k].nrule).chains[diagnosis[k].nrulechain]);
			*/
			PrintMessage((char*)(&str[0]));
			k++;
		}
	}
}