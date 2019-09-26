#pragma once
#include<iostream>

namespace FST {
	struct RELATION {						//ребро: символ -> вершина графа переходов КА
		char symbol;						//символ перехода
		short nnode;						//номер смежной вершины
		RELATION(char c = 0x00,				//символ перехода
			short  ns = NULL);				//новое состояние
	};
	struct NODE {					//вершина графа переходов
		short n_relation;			//кол-во инцидентных ребер
		RELATION *relations;		//инцидентные ребра
		NODE();
		NODE(short n,				//кол-во инцидентных ребер
			RELATION rel, ...);		//список ребер
	};
	struct FST {				//недетерминированный конечный автомат
		char *string;			//цепочка(строка, завершается 0х00)
		short position;			//текущая позиция в строке
		short nstates;			//кол-во состояний автомата
		NODE* nodes;			//граф переходов: [0] - начальное состояние, [nstate -1] - конечное
		short* rstates;			//возможные состояния автомата на этой позиции
		FST(char* s,			//цепочка (строка, завершаестся 0х00)
			short ns,			//кол-во состояний автомата
			NODE n, ...); //список состояний автомата
		
			
	};
	

	bool execute(	//выполнить распознование цепочки
		FST& fst);	//недетерминированный автомат

	void udpdate(FST& fst, char* str);
	void newFST(FST&, char*);
}
