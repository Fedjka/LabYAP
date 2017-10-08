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
		FST(char* s, short ns, NODE n, ...); //�������(������, ����������� 0�00), ���������� ��������� ��������, ������ ���������(���� ���������)
		FST(short ns, NODE n, ...); //		��� �������					, ���������� ��������� ��������, ������ ���������(���� ���������)
		FST(char* s, FST&); //				��� ������ �������			, ���������� ��������� ��������, ������ ���������(���� ���������)
	};

	bool step(FST &fst, short *&rstates);
	gek execute(FST &fsts);
}