#include "IT.h"
#include "Error.h"
#include <iostream>

namespace IT
{
	IdTable Create(int size) //создать 
	{
		if (size >= TI_MAXSIZE)
			throw ERROR_THROW(114);
		IdTable itable = { size, 0, new Entry[size] };
		return itable;
	}

	void Add(IdTable& itable, Entry istr)//добавить 
	{
		
		itable.table[itable.size++] = istr;
		//itable.size++;

		if (itable.size >= itable.maxsize)
			throw ERROR_THROW(113);
	}

	void Delete(IdTable& itable)//удалить 
	{
		if (!&itable)
			throw ERROR_THROW(3);
		delete itable.table;
		itable.table = nullptr;
	}

	Entry GetEntry(IdTable& itable, int nstr)
	{
		if (itable.size < nstr || nstr < 0)
			throw ERROR_THROW(6);
		return itable.table[nstr];
	}

	int IsId(IdTable& itable, char id[ID_MAXSIZE], bool isDeclare)
	{
		int res = TI_NULLIDX;
		if (isDeclare)
			return res;
		for (int i = 0; i < itable.size; i++)
			if (strcmp(itable.table[i].id, id) == 0)
				res = i;
		return res;
	}
}