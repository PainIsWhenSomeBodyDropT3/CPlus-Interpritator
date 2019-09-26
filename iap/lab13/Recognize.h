#pragma once
#include"fst.h"
#include"Log.h"
#include"Parm.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
#include<iostream>
#define STD_SUBSTR "substr"
#define STD_STRLEN "strlen"
#define STD_BIBLE_SIZE 2
const char* const StdBible[STD_BIBLE_SIZE] = { STD_SUBSTR, STD_STRLEN };
namespace RE {
	void ChainRecognition(Log::LOG& log, In::IN& in, Parm::PARM &parm, LT::LexTable& lextable, IT::IdTable& idtable);
	
	/*string modernizeText(string text);
	string modernizeLine(string line);*/
	/*void defineAVT(char * strrr);
	bool check(string str);
	bool check(char str);
	string fomateOther(string toCheck);*/
	void write(char * strrr, int j, FST::FST &fst1, Parm::PARM & parm);
	bool newLex(FST::FST& fst, char* word, char lexema);
	void addLex(char lexema, char* word);
	void addId(char* word, IT::IDDATATYPE dataType, IT::IDTYPE idType);
	bool isLetter(char ch);
	void ChainRecognition(Log::LOG& log, In::IN& in, Parm::PARM &parm, LT::LexTable& lextable, IT::IdTable& idtable);
	bool isThatLexem(char word[]);
}
