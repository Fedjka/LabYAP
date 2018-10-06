#include "IT.h"
#include <cstring>
#include "stdafx.h"

namespace IT
{
	Entry::Entry(char * id, int idxfirstLE, IDDATATYPE datatype, IDTYPE idtype, char* visibility)
	{
		strncpy_s(this->id, ID_MAXSIZE, id, ID_MAXSIZE - 1);
		this->idxfirstLE = idxfirstLE;
		this->iddatatype = datatype;
		this->idtype = idtype;
		this->value.vint = TI_INT_DEFAULT;
		this->value.vstr->len = TI_STR_DEFAULT;
		this->value.vstr->str[0] = TI_STR_DEFAULT;
		strncpy_s(this->visibility, ID_MAXSIZE, visibility, ID_MAXSIZE - 1);
	}
	IdTable IT::Create(int size)
	{
		IdTable idTable;
		idTable.maxsize = ID_MAXSIZE;
		idTable.size = 0;
		idTable.litCount = 0;
		idTable.table = new Entry[size];
		return idTable;
	}
	void IT::Add(IdTable & idtable, Entry entry)
	{
		idtable.table[idtable.size] = entry; 
		idtable.size++;
	}
	Entry GetEntry(IdTable &idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable &idtable, char id[ID_MAXSIZE], char *visibility)
	{
		char ident[ID_MAXSIZE];
		strncpy_s(ident, ID_MAXSIZE, id, ID_MAXSIZE - 1);
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, ident) == NULL  && strcmp(idtable.table[i].visibility, visibility) == NULL)
				return i;
		}
		return -1;
	}
	int IT::IsLiteral(IdTable &idtable, char *litrl)
	{
		for (int k = 0; k < idtable.litCount;k++)
		{
			if (!strcmp(idtable.literals[k], litrl))
			{
				return k;
			}
		}
		return -1;
	}
	void SetValue(IdTable &idtable, int indTI, char* token)
	{
		if (idtable.table[indTI].iddatatype == INT)
		{
			idtable.table[indTI].value.vint = atoi(token);
		}
		else if (idtable.table[indTI].iddatatype == STR)
		{
			idtable.table[indTI].value.vstr->len = (char)strlen(token);
			strcpy_s(idtable.table[indTI].value.vstr->str, TI_STR_MAXSIZE, token);
		}
	}
	void Delete(IdTable &idTable)
	{
		delete idTable.table;
	}
}
