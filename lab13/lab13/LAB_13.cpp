#include <iostream>
#include <locale>
#include <cwchar>
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "Recognize.h"
#include "IT.h"
#include "LT.h"
#include "PolishNotation.h"
#include "MFST.h"
using namespace std;
int main(int argc, const wchar_t* argv[])
{

	setlocale(LC_ALL, "rus");
	LT::LexTable ltable = LT::Create(LT_TABLE_SIZE);
	IT::IdTable itable = IT::Create(TI_TABLE_SIZE);
	argv[0] = L"-in:D:\\лабы\\2курс\\япэ\\lab_13\\lab13\\lab13\\In.txt";

	

	Log::LOG log;
	Parm::PARM parm;
	try {
		parm = Parm::getParm(1, argv);


		Log::writeLine(Log::getLog(parm.log), "Текст ", "без ", "ошибок ", "");
		Log::writeLog(Log::getLog(parm.log));
		Log::writeParm(Log::getLog(parm.log), parm);
		
		In::IN in = In::getIn(parm.in);
		Log::writeIn(Log::getLog(parm.log), in);
		RE::ChainRecognition(log, in, parm,ltable,itable);
		Log::writeLexTable(Log::getLog(parm.log), ltable);
		Log::WriteId(Log::getLog(parm.log), itable);
		//PN::showPolishNotation(ltable, itable);
		//Log::writeLexTable(Log::getLog(parm.log), ltable);

		MFST::Mfst *automatos = new MFST::Mfst(ltable, GRB::getGreibach());
		automatos->start();
		
		IT::Delete(itable);
		LT::Delete(ltable);
		Log::close(Log::getLog(parm.log));
		

	}
	catch (Error::ERROR e) {

		writeError(Log::getLog(parm.log), e);

	}
	
	system("pause");
}