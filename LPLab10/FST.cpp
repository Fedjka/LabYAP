#include "stdafx.h"

namespace FST
{

	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	}

	NODE::NODE()
	{
		n_relation = 0;
		RELATION *relations = NULL;
	}

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++)
		{
			relations[i] = *p;
			p++;
		}
	}

	FST::FST(short ns, NODE n, ...)
	{
		this->nodes = new NODE[ns];
		NODE* temp = &n;
		short i = 0;
		this->nstates = ns;
		this->rstates = new short[ns];
		while (i < ns)
		{
			this->nodes[i] = *(temp + i);
			i++;
		};

	}
	FST::FST(char* s, FST& fst)
	{
		this->nodes = new NODE[fst.nstates];
		NODE* temp = fst.nodes;
		short i = 0;
		this->string = s;
		this->nstates = fst.nstates;
		this->rstates = new short[this->nstates];
		while (i < nstates)
		{
			this->nodes[i] = *(temp + i);
			i++;
		};
		rstates[0] = 0;
		position = -1;
	}

	FST::FST(char *s, short ns, NODE n, ...)
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++)
		{
			nodes[k] = *p++;
		}
		rstates = new short[nstates];
		memset(rstates, 0xFF, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;
	}

	bool step(FST &fst, short *&rstates)
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
			{
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						return rc = true;
					};
				};
			};
		};
		return rc;
	}

	gek sw;
	gek execute(FST &fst)
	{
		short *rstates = new short[fst.nstates];
		memset(rstates, 0xFF, sizeof(short)*fst.nstates);
		int lstring = strlen(fst.string);
		sw.rc = true;
		short i;
		for (i = 0; (i < lstring) && sw.rc; i++)
		{
			fst.position++;
			sw.rc = step(fst, rstates);
		}

		delete[] rstates;

		if (fst.rstates[fst.nstates - 1] == lstring)
		{
			sw.rc = true;
		}
		else
		{
			sw.rc = false;
		}
		sw.column = fst.position + 1;
		return sw;
	}
}