#include "stdafx.h"
#include <iomanip>

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{ 
		LOG tempLog = Log::INITLOG;

		tempLog.stream = new std::ofstream;
		tempLog.stream->open(logfile);

		if (!tempLog.stream)

		{
			throw ERROR_THROW(112);
		}
		return tempLog;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char **p = &c;

		while (*p != "")
		{
			(*log.stream) << *p;
			p += sizeof(**p);
		}
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t **p = &c;
		char buffer[50];

		while (*p != L"")
		{
			wcstombs(buffer, *p, sizeof(buffer));
			(*log.stream) << buffer;
			p += sizeof(**p) / 2;
		}
	}

	void WriteLog(LOG log)
	{
		char buffer[PARM_MAX_SIZE];

		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, PARM_MAX_SIZE, "Дата: %d.%m.%y %H:%M:%S", timeinfo);
		(*log.stream) << "\n---- Протокол ---- " << buffer << " ---- \n";
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char inInfo[PARM_MAX_SIZE];
		char outInfo[PARM_MAX_SIZE];
		char logInfo[PARM_MAX_SIZE];

		wcstombs(inInfo, parm.in, sizeof(inInfo));
		wcstombs(outInfo, parm.out, sizeof(outInfo));
		wcstombs(logInfo, parm.log, sizeof(logInfo));

		(*log.stream) << "---- Параметры ---- \n"
			<< " -in: " << inInfo << "\n"
			<< " -out: " << outInfo << "\n"
			<< " -log: " << logInfo << "\n";
	}

	void WriteIn(LOG log, In::IN in)
	{
		(*log.stream) << "---- Исходные данные ---- \n"
			<< "Всего символов: " << in.size << "\n"
			<< "Всего строк: " << in.lines << "\n"
			<< "Пропущено: " << in.ignor << "\n";
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (error.id == 100)
		{
			std::cout << "ОШИБКА " << error.id << ": " << error.message << "\n";
		}
		else
		{
			(*log.stream) << "ОШИБКА " << error.id << ": " << error.message << "\n"
				<< "Строка " << error.inext.line << ", позиция: " << error.inext.col << "\n";
		}
	}
	void writeLexTable(const LOG &log, LT::LexTable &Lextable)
	{
		*log.stream << "\n---------------Таблица лексем--------------------------------\n" <<
			std::endl;
		int c = 0;
		for (int i = 0; i < Lextable.size; i++)
		{
			if (Lextable.table[i].sn != c)
			{
				c++;
				*log.stream << std::setw(2) << std::left << Lextable.table[i].sn << ' ';
			}
			*log.stream << Lextable.table[i].lexema;
			if (Lextable.table[i + 1].sn > (Lextable.table[i].sn)) *log.stream << std::endl;
		}
	}
	void writeIDtable(const LOG &log, IT::IdTable &IDtable)
	{
		*log.stream << "\n---------------Таблица идентификаторов-------------------------------\n" <<
			std::setw(10) << std::left << "Имя идент " <<
			std::setw(13) << std::left << "Обл. видим." <<
			std::setw(10) << std::left << "Тип даных " <<
			std::setw(11) << std::left << "Тип идент. " <<
			std::setw(15) << std::left << "№ табл. лекс. " <<
			std::setw(8) << std::left << "Значение" <<
			std::endl;


		for (int i = 0; i < IDtable.size; i++)
		{
			*log.stream << std::setw(10) << std::left <<
				std::setw(10) << std::left << IDtable.table[i].id << std::setw(10) << std::left;

			*log.stream << std::setw(13) << std::left << IDtable.table[i].visibility;

			*log.stream << std::setw(10) << std::left;
			if (IDtable.table[i].iddatatype == IT::INT)
			{
				*log.stream << LEX_TYPE_INT;
			}
			else if (IDtable.table[i].iddatatype == IT::STR)
			{
				*log.stream << LEX_TYPE_STRING;
			}

			*log.stream << std::setw(11) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:				*log.stream << "Function"; break;
			case IT::V:				*log.stream << "Variable"; break;
			case IT::P:				*log.stream << "Parameter"; break;
			case IT::L:				*log.stream << "Literal"; break;
			}

			*log.stream << std::setw(15) << std::left << IDtable.table[i].idxfirstLE;
			if (IDtable.table[i].idtype == IT::F)
			{
				*log.stream << "no";
			}
			else if (IDtable.table[i].iddatatype == IT::INT)
			{
				*log.stream << IDtable.table[i].value.vint;
			}
			else if (IDtable.table[i].iddatatype == IT::STR)
			{
				if (IDtable.table[i].value.vstr->len != 0)
				{
					*log.stream << IDtable.table[i].value.vstr->str;
				}
				else *log.stream << "no";
			}
			*log.stream << std::endl;
		}
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}
}