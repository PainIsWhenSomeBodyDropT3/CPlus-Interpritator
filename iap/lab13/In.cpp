#include "Parm.h"
#include "Error.h"
#include "In.h"
#include <iostream>
#include <locale>
#include <cwchar>
#include <fstream>
using namespace std;
ifstream reading;
namespace In {
	IN In::getIn(wchar_t infile[]) {
		//wprintf(L"%ls\n", infile);
		IN in;
		char s;
		in.text = "";

		in.size = 0;
		in.lines = 0;
		in.ignor = 0;
		int i = 0;
		int inCode[256] = IN_CODE_TABLE;
		reading.open(infile);
		if (reading.fail())throw ERROR_THROW(110);
		while (reading.read(&s, 1)) {

			if (s == IN_CODE_ENDL) {
				in.text += s;
				in.lines++;
				i = 0;
			}
			else if ((int)s > 0 && (int)s < 256) {
				if (inCode[(int)s] == in.F) {
					throw ERROR_THROW_IN(111, in.lines, i);
				}
				else if (inCode[(int)s] == in.T) {
					in.text += s;


				}
				else if (inCode[(int)s] == in.I) {
					in.ignor++;

				}
				else {
					in.text += inCode[(int)s];
				}


			}


			i++;
			in.size++;
		}
		reading.close();

		return in;

	}
};