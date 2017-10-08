#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "IT.h"
#include "LT.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream * stream;
	};

	LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);
	void Close(LOG log);
	In::IN getin(wchar_t infile[], LOG log);
	void writeLexTable(const LOG &log, LT::LexTable &Lextable);
	void writeIDtable(const LOG &log, IT::IdTable &IDtable);
}