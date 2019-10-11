#pragma once
#include "LT.h"
#include "IT.h"
#include "iostream"
#define EXP1 28
#define EXP2 3
#define EXP3 24
#define FUNCTION_REF '@'
#define FILL_SYMBOL '#'
/*
	(, ) _____ 1
	+, - _____ 2
	/* - _____ 3

	запрещенный символ - #
*/
namespace PN
{
	struct OperationStack
	{
		char operation_;
		int priority;
		OperationStack* next;
	};

	bool PolishNotation(int, LT::LexTable&, IT::IdTable&);				//Построение польской записи в таблице лексем(позиция выражения в lextable, табл лексем, табл ид)
//true - построение польской записи выполнено успешно
//false - построение польской записи не выполнено
	void showPolishNotation(LT::LexTable&, IT::IdTable&);
}