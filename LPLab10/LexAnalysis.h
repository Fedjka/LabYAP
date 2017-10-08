#pragma once
#include "stdafx.h"

namespace LexAnalysis
{
	struct LEX
	{
		LT::LexTable Lextable;
		IT::IdTable	IDtable;
	};

	struct Graph
	{
		char lexema;
		FST::FST graph;
	};
	LEX Analysis(In::IN inStruct, Log::LOG &log);
}
