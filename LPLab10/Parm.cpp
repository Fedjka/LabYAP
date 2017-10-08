#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

namespace Parm 
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM p = { L"", L"", L"" };

		for (int i = 1; i < argc; i++)
		{
			std::wstring ws(argv[i]);
			std::string str(ws.begin(), ws.end());
			if (wcsncmp(argv[i], PARM_IN, wcslen(PARM_IN)) == 0)
			{
				if (wcslen(argv[i])>PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				wcscpy_s(p.in, argv[i] + wcslen(PARM_IN));
			};
			if (wcsncmp(argv[i], PARM_OUT, wcslen(PARM_OUT)) == 0)
			{
				if (wcslen(argv[i])>PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				wcscpy_s(p.out, argv[i] + wcslen(PARM_OUT));
			};
			if (wcsncmp(argv[i], PARM_LOG, wcslen(PARM_LOG)) == 0)
			{
				if (wcslen(argv[i])>PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				wcscpy_s(p.log, argv[i] + wcslen(PARM_LOG));
			};
		}

		if (p.in[0] == NULL)
			throw ERROR_THROW(100);

		if (p.out[0] == NULL)
		{
			wcscpy_s(p.out, p.in);
			wcsncat_s(p.out, PARM_OUT_DEFAULT_EXT, sizeof(PARM_OUT_DEFAULT_EXT));
		}

		if (p.log[0] == 0x0000)
		{
			wcscpy_s(p.log, p.in);
			wcsncat_s(p.log, PARM_LOG_DEFAULT_EXT, sizeof(PARM_LOG_DEFAULT_EXT));
		}

		return p;
	};
}