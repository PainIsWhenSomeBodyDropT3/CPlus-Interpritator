#include "PolishNotation.h"
using namespace std;
int globalCounter=0;

namespace PN
{
	bool PolishNotation(int position, LT::LexTable& ltable, IT::IdTable& itable)
	{
		bool rc = false, isFunc = false;
		OperationStack* operation = nullptr;
		OperationStack* operationHead = nullptr;
		LT::LexTable lexTable = ltable;
		IT::IdTable idTable = itable;
		if (position > lexTable.table[lexTable.size].sn || position < 0)
			return rc;
		 int startLex = 0;
		char* postExpression = new char[LT_TABLE_SIZE]; 
		bool access;
		do {
			 access = false;
		for (int i = 0, k = 0; i < lexTable.size; i++) {
			if (lexTable.table[i].sn == position)
			{
				access = true;
				startLex = i;
				while (position == lexTable.table[i].sn)
				{
					postExpression[k] = lexTable.table[i].lexema;
					k++;
					i++;
				}
				postExpression[k] = LEX_END;
				break;
			}
		}
		if (!access) {
			position++;
			globalCounter++;
		}
		} while (!access);
		char* finalExpression = new char[(int)strlen(postExpression)];
		
		 int countParams = 0;
		int j = 0;
		for (int i = 0; i < (int)strlen(postExpression); i++)
		{
			switch (postExpression[i])
			{
			case LEX_LEFTHESIS:
			case LEX_RIGHTHESIS:
			case LEX_SIGN:
			{
				LT::SIGNTYPE signtype = lexTable.table[startLex + i].sign;									
				int prior = 1;
				char sign;
				switch (signtype)
				{
				case LT::PLUS:
					sign = LEX_PLUS;
					break;
				case LT::MINUS:
					sign = LEX_MINUS;
					break;
				case LT::STAR:
					sign = LEX_STAR;
					break;
				case LT::DIRSLASH:
					sign = LEX_DIRSLASH;
					break;
				default:
					sign = postExpression[i];
					break;
				}
				if (signtype == LT::PLUS || signtype == LT::MINUS) {
					prior = 2;
				}
				if (signtype == LT::STAR || signtype == LT::DIRSLASH) {
					prior = 3;
				}
				if (!operation || operationHead->priority < prior || postExpression[i] == LEX_LEFTHESIS)
				{
					operation = new OperationStack;
					operation->operation_ = sign;
					operation->priority = prior;
					operation->next = operationHead;
					operationHead = operation;
				}
				else
				{
					if (postExpression[i] == LEX_RIGHTHESIS)
					{
						if (isFunc) {																//reference on function and its params
							finalExpression[j++] = FUNCTION_REF;
						}
						while (operationHead && operationHead->operation_ != LEX_LEFTHESIS)
						{
							finalExpression[j++] = operationHead->operation_;
							operationHead = operationHead->next;
						}
						operationHead = operationHead->next;
					}
					else
					{
						while (operationHead && operationHead->priority >= prior)
						{
							finalExpression[j++] = operationHead->operation_;
							operationHead = operationHead->next;
						}
						operation = new OperationStack;
						operation->operation_ = sign;
						operation->priority = prior;
						operation->next = operationHead;
						operationHead = operation;
					}
				}
				break;
			}
			case LEX_COMMA:
			{
				countParams++;
				break;
			}
			case LEX_ID:
			{
				if (idTable.table[lexTable.table[startLex + i].indxTI].idtype == IT::F && postExpression[i + 1] == LEX_LEFTHESIS) {
					isFunc = true;
				}
				else {
					finalExpression[j++] = postExpression[i];
				}
				break;
			}
			default:
				if (postExpression[i + 1] == LEX_END)
				{
					while (operationHead)
					{
						finalExpression[j++] = operationHead->operation_;
						operationHead = operationHead->next;
					}
					finalExpression[j++] = postExpression[i];
					finalExpression[j] = LEX_END;
					break;
				}
				finalExpression[j++] = postExpression[i];
				break;
			}
		}
		finalExpression[j] = LEX_END;
		bool isEnd = false;
		for (int i = 0; i < (int)strlen(finalExpression); i++)
		{
			if (i == (int)strlen(finalExpression)) {
				isEnd = true;
			}
			if (isEnd) {
				ltable.table[startLex + i].lexema = FILL_SYMBOL;
			}
			else {
				ltable.table[startLex + i].lexema = finalExpression[i];
			}
			std::cout << ltable.table[startLex + i].lexema;
		}
		rc = true;
		std::cout << endl;
		return rc;
	}

	void showPolishNotation(LT::LexTable& ltable, IT::IdTable& itable)
	{
		

			if (PolishNotation(30, ltable, itable))
				std::cout << 3 + globalCounter << ": польская запись построена" << endl;
			else
				std::cout << 3 + globalCounter << ": польская запись не построена" << endl;
		
		
	//	}


		/*if (PolishNotation(5, ltable, itable))
			std::cout << 6+ globalCounter << ": польская запись построена" << endl;
		else
			std::cout << 6+ globalCounter << ": польская запись не построена" << endl;
*/

		/*if (PolishNotation(EXP2, ltable, itable))
			std::cout << EXP2 << ": польская запись построена" << endl;
		else
			std::cout << EXP2 << ": польская запись не построена" << endl;
		if (PolishNotation(EXP3, ltable, itable))
			std::cout << EXP3 << ": польская запись построена" << endl;
		else
			std::cout << EXP3 << ": польская запись не построена" << endl;*/
	}
}
