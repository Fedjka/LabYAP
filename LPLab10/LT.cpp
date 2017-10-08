#include "LT.h"
#include "stdafx.h"
#include <iostream>
#include "Error.h"


namespace LT
{
	Entry::Entry(char lexema, int snn, char operation, int idxti)
	{
		strcpy_s(this->lexema, 2, &lexema);
		this->sn = snn;
		this->idxTI = idxti;
		strcpy_s(this->operation, 2, &operation);
	}

	LexTable Create(int size)
	{
		LexTable lextable;
		if (size < LT_MAXSIZE) lextable.maxsize = size;
		else throw ERROR_THROW(117);
		lextable.size = NULL;
		lextable.table = new Entry[size];
		return  lextable;
	}
	void Add(LexTable &lextable, Entry entry)
	{
		lextable.table[lextable.size] = entry;
		if (lextable.size < LT_MAXSIZE)	lextable.size++;
		else throw ERROR_THROW(117);
	}
	Entry GetEntry(LexTable &lextable, int n)
	{
		return lextable.table[n];
	}
	void Delete(LexTable &lextable)
	{
		delete lextable.table;
	}
	void GetAllEntry(LexTable &lextable)
	{
		for (int i = 0; i < lextable.size; i++)
		{
			std::cout << "   " <<
				lextable.table[i].sn << "   " <<
				lextable.table[i].lexema << std::endl;
		}
	}
}