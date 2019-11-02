#include "LT.h"
#include "Error.h"
#include <iostream>

namespace LT
{
	LexTable Create(int size)
	{
		if (size >= LT_MAXSIZE)
			throw ERROR_THROW(113);
		LexTable ltable = { size, -1, new Entry[size] };
		return ltable;
	}

	void Add(LexTable& ltable, Entry& lstr)
	{
		
		if (ltable.size >= ltable.maxsize)
			throw ERROR_THROW(113);
		ltable.table[++ltable.size] = lstr;
	}

	void Delete(LexTable& ltable)
	{
		if (!&ltable)
			throw ERROR_THROW(3);
		delete ltable.table;
		ltable.table = nullptr;
	}

	Entry *GetEntry(LexTable& ltable, int nstr)
	{
		if (ltable.size < nstr || nstr < 0)
			throw ERROR_THROW(5);
		return &ltable.table[nstr];
	}
	char* PrintTable(LexTable& lexTable) {
		char *str = new char[lexTable.size + 1];
		for (int i = 0; i < lexTable.size; i++) {
			str[i] = GetEntry(lexTable, i)->lexema;
		}
		str[lexTable.size] = '\0';
		return str;
	}
}