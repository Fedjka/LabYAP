#pragma once
#include "stdafx.h"
#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255

namespace IT
{
	enum IDDATATYPE
	{
		INT = 1, STR = 2
	};
	enum IDTYPE
	{
		V = 1, F = 2, P = 3, L = 4
	};
	struct Entry
	{
		int idxfirstLE;
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		char visibility[ID_MAXSIZE];
		union
		{
			int vint;	
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr[TI_STR_MAXSIZE];
		} value;
		Entry()
		{
			this->value.vint = TI_INT_DEFAULT;
			this->value.vstr->len = TI_STR_DEFAULT;
		}
		Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype, char* visibility);
	};
	struct IdTable
	{
		int maxsize;
		int size;
		char literals[30][100];
		int litCount;
		Entry *table;
	};
	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char *visibility);
	int IsLiteral(IdTable& idtable, char *litrl);
	void Delete(IdTable& idtable);
	void SetValue(IdTable &idtable, int indTI, char* token);
}