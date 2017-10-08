#pragma once
#include "stdafx.h"

namespace FST
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(char c = 0x00, short ns = NULL);
	};

	struct gek
	{
		bool rc = false;
		int column;
	};

	struct NODE
	{
		short n_relation;
		RELATION *relations;
		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST
	{
		char *string;
		short position;
		short nstates;
		NODE *nodes;
		short *rstates;
		FST(char* s, short ns, NODE n, ...); //цепочка(строка, завершается 0х00), количество состояний автомата, список состояний(граф переходов)
		FST(short ns, NODE n, ...); //		для массива					, количество состояний автомата, список состояний(граф переходов)
		FST(char* s, FST&); //				для лексич разбора			, количество состояний автомата, список состояний(граф переходов)
	};

	bool step(FST &fst, short *&rstates);
	gek execute(FST &fsts);
}