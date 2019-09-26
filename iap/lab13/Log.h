#pragma once

#include<fstream>
#include"In.h"
#include"Parm.h"
#include"Error.h"
#include"LT.h"
#include"IT.h"
namespace Log {	//работа с протоколом
	struct LOG {	//протокол
		wchar_t logfile[PARM_MAX_SIZE] = L"";		//имя файла протокола
		ofstream  stream;				//выходной поток протокола
		bool access = true;
	};
	//структура для начальной инициализации LOG

	LOG getLog(wchar_t logfile[]);					//сформировать структуру LOG
	void writeLine(LOG log, const char* c, ...);			//вывести в протокол конкатенацию строк
	void writeLine(LOG log, wchar_t* c, ...);		//вывести в протокол конкатенацию строк
	void writeLog(LOG log);							//вывести в протокол заголовок
	void writeParm(LOG log, Parm::PARM parm);		//вывести в протокол информацию о входных параметрах
	void writeLexTable(LOG log, LT::LexTable& ltable);				//вывести в протокол информацию о входном потоке
	void writeOut(Parm::PARM parm, const char* c, ...);				//вывести в протокол информацию о входном потоке
	void writeError(LOG log, Error::ERROR e);	//вывести в протокол информацию об входной ошибке
	void close(LOG log);			
	void WriteId(LOG log, IT::IdTable& itable);//закрыть протокол

}