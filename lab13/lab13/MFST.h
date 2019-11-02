#pragma once
#include <iostream>
#include <stack>
#include "GRB.h"
#include "LT.h"
#define MFST_DAIGN_NUMBER 3	//колво диагностик
typedef std::stack<short> MFSTSTACK;
namespace MFST {
	struct MfstState {
		short nrule;		//номер правила
		short lenta_position;	//позиция
		short nrulechain;	//номер цепочки
		MFSTSTACK st;	//стэк
		MfstState(short pposition, MFSTSTACK pst, short pnurelchain, short pnrule) {
			lenta_position = pposition;
			nrulechain = pnurelchain;
			st = pst;
			nrule = pnrule;
		}
	};

	struct Mfst {
		enum ENUM_STEP {
			NS_OK,		// найдено правило и записано в стек
			NS_NORULE,	//не найдено правило или ошибка грамматики
			NS_NORULECHAIN,	//не найдена подходящая цепочка
			NS_ERROR,	//неизвестный нетерминальный символ
			TS_OK,		//текущий символ == вершине стека
			TS_NOK,		//ткущий символ != вершине стека
			LENTA_END,	//цепочка окончена
			SURPRISE	//возвращение  в сохраненную строку
		};

		GRBHALPHABET* lenta;	//цепочка лексем
		short lenta_position;	//позиция на ленте
		short nrule;		//номер правила
		short nrulechain;		//номер симвлаа текущего правила
		short lenta_size;	//размер ленты
		GRB::Greibach greibach;		//грамматика
		LT::LexTable lexTable;	//таблица лексем
		MFSTSTACK st;	//стек
		std::stack<MfstState> statesStack;	// стэк , который сохраняет прошлое значение

		ENUM_STEP step();	//сделать шаг
		bool saveState();	//сохранить состояние автомата
		bool resState();	//обновить состояние
		bool pushChain(GRB::Rule::Chain chain);	//положить в стек значение
		bool start();	
		void StateInfo();	//информация об значении автомата
		bool isTopStateEqual();	// одинаковые ли вершина стека и текущее состояние автомата

		Mfst(LT::LexTable table, GRB::Greibach gr) {
			lexTable = table;
			greibach = gr;
			st.push(gr.stbottomT);
			st.push(gr.startN);
			char* clenta = LT::PrintTable(table);
			int psize = table.size;
			GRBHALPHABET* plenta = new GRBHALPHABET[psize];
			for (int i = 0; i < psize; i++) {
				plenta[i] = GRB::Rule::Chain::T(clenta[i]);
			}
			lenta_size = table.size;
			lenta = plenta;
			lenta_position = 0;
		}

		struct MfstDiagnosis {
			short lenta_position = -1;	//позиция на ленте
			ENUM_STEP step = ENUM_STEP::SURPRISE;	//код завершения
			short nrule = -1;
			short nrulechain = -1;
			MfstDiagnosis() {
			};
			MfstDiagnosis(short lenta_position, ENUM_STEP step, short nrule, short nrulechain);
		} diagnosis[MFST_DAIGN_NUMBER];


		void pushNewDiagnosis(Mfst::ENUM_STEP step);
		void printLastDiagnosis();
	};
	//вывесці правіла у кансоль
	void printRule(GRB::Rule rule, GRB::Rule::Chain chain);
	void printRule(GRBHALPHABET nt, GRB::Rule::Chain chain);
	std::string getStrRule(GRB::Rule rule, GRB::Rule::Chain nchain);

	void PrintMessage(char* str);

	void printError(Mfst::ENUM_STEP e);	
}