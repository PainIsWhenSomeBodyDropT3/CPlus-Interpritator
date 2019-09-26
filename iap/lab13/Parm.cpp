#include "Parm.h"
#include "Error.h"
#include <iostream>
#include <locale>
#include <cwchar>


namespace Parm {

	PARM getParm(int argc, const wchar_t* agrv[]) {




		bool in = 0, out = 0, log = 0;
		int i = argc;
		wchar_t forout[PARM_MAX_SIZE] = L"";
		wchar_t forlog[PARM_MAX_SIZE] = L"";
		wchar_t forin[PARM_MAX_SIZE] = L"";

		PARM e;


		if (wcslen(*agrv) > ERROR_MAXSIZE_MESSAGE) { throw ERROR_THROW(104) }
		int size = wcslen(*agrv);

		if (wcsstr(*agrv, PARM_OUT))
		{
			out = true;
			const wchar_t *a = wcsstr(*agrv, (wchar_t*)L"D");
			wcsncpy_s(e.out, a, wcslen(a));
		}
		if (wcsstr(*agrv, PARM_LOG))
		{
			log = true;
			const wchar_t *a = wcsstr(*agrv, (wchar_t*)L"D");
			wcsncpy_s(e.log, a, wcslen(a));


		}
		if (wcsstr(*agrv, PARM_IN))
		{
			in = true;
			const wchar_t *a = wcsstr(*agrv, (wchar_t*)L"D");


			wcsncpy_s(forout, a, wcslen(a));
			wcsncpy_s(forlog, a, wcslen(a));
			wcsncpy_s(forin, a, wcslen(a));

			wcsncat_s(forin, TXT, wcslen(TXT));
			wprintf(L"%ls\n", forin);
			wcsncpy_s(e.in, forin, wcslen(forin));

		}

		if (!in) throw ERROR_THROW(100);
		if (!out) {
			wcsncat_s(forout, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
			wprintf(L"%ls\n", forout);
			wcsncpy_s(e.out, forout, wcslen(forout));
		}

		if (!log) {
			wcsncat_s(forlog, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
			wprintf(L"%ls\n", forlog);
			wcsncpy_s(e.log, forlog, wcslen(forlog));
		}

		return e;

	}
};