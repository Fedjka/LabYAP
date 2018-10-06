#include "stdafx.h"
#include "LexAnalysis.h"
#include "FST.h"
using namespace GR;

namespace LexAnalysis
{
	Graph graph[N_GRAPHS] =
	{
		{ 't', FST::FST(GRAPH_INTEGER) },
		{ 't', FST::FST(GRAPH_STRING) },
		{ 'd', FST::FST(GRAPH_DECLARE) },
		{ 'l', FST::FST(GRAPH_INT_LITERAL) },
		{ 'l', FST::FST(GRAPH_CHAR_LITERAL) },
		{ 'm', FST::FST(GRAPH_MAIN) },
		{ 'f', FST::FST(GRAPH_FUNCTION) },
		{ 'r', FST::FST(GRAPH_RETURN) },
		{ 'p', FST::FST(GRAPH_PRINT) },
		{ ';', FST::FST(GRAPH_SEPARATOR) },
		{ '=', FST::FST(GRAPH_EQUALS) },
		{ ',', FST::FST(GRAPH_COMMA) },
		{ '{', FST::FST(GRAPH_LEFT_CURLY_BRACE) },
		{ '}', FST::FST(GRAPH_RIGHT_CURLY_BRACE) },
		{ '(', FST::FST(GRAPH_OPEN_PARENTHESIS) },
		{ ')', FST::FST(GRAPH_CLOSE_PARENTHESIS) },
		{ '+', FST::FST(GRAPH_PLUS) },
		{ '-', FST::FST(GRAPH_MINUS) },
		{ '*', FST::FST(GRAPH_ASTERISK) },
		{ '/', FST::FST(GRAPH_FORWARD_SLASH) },
		{ ',', FST::FST(GRAPH_COMMA) },
		{ 'i', FST::FST(GRAPH_ID) }
	};

	LEX Analysis(In::IN inStruct, Log::LOG &log)
	{
		LEX Table;
		Table.Lextable = LT::Create(inStruct.tokensCount);
		Table.IDtable = IT::Create(inStruct.tokensCount);
		bool isExecuted = false;
		bool isParametr = false;
		bool isLiteral = false;
		int id = 0, litIndex;
		char operation = LEX_ZERO_OPERATION;
		char visibility[ID_MAXSIZE], prevFun[ID_MAXSIZE];
		for (int i = 0; i < inStruct.tokensCount; i++)//avtomat
		{
			for (int j = 0; j < N_GRAPHS; j++)
			{
				FST::FST FST1(inStruct.tokens[i].token, graph[j].graph);
				if (FST::execute(FST1).rc)
				{
					isExecuted = true;
					switch (graph[j].lexema)
					{
					case 'i':
					{
						if (IT::IsId(Table.IDtable, inStruct.tokens[i].token, visibility) == -1)
						{
							if (*Table.Lextable.table[i - 1].lexema == LEX_FUNCTION)
							{
								strncpy_s(visibility, ID_MAXSIZE, "All", ID_MAXSIZE - 1);
								if (!strcmp(inStruct.tokens[i - 2].token, LEX_TYPE_INT))
								{
									IT::Entry entryit(inStruct.tokens[i].token, id++, IT::INT, IT::F, visibility);
									IT::Add(Table.IDtable, entryit);
								}
								else if (!strcmp(inStruct.tokens[i - 2].token, LEX_TYPE_STRING))
								{
									IT::Entry entryit(inStruct.tokens[i].token, id++, IT::STR, IT::F, visibility);
									IT::Add(Table.IDtable, entryit);
								}
								LT::Entry entrylt(graph[j].lexema, inStruct.tokens[i].line, operation, Table.IDtable.size - 1);
								LT::Add(Table.Lextable, entrylt);
								strncpy_s(visibility, ID_MAXSIZE, inStruct.tokens[i].token, ID_MAXSIZE - 1);
								isParametr = true;
								break;
							}
							else if (*Table.Lextable.table[i - 1].lexema == LEX_TYPE)
							{
								if (!isParametr)
								{
									if (!strcmp(inStruct.tokens[i - 1].token, LEX_TYPE_INT))
									{
										IT::Entry entryit(inStruct.tokens[i].token, id++, IT::INT, IT::V, visibility);
										IT::Add(Table.IDtable, entryit);
									}
									else if (!strcmp(inStruct.tokens[i - 1].token, LEX_TYPE_STRING))
									{
										IT::Entry entryit(inStruct.tokens[i].token, id++, IT::STR, IT::V, visibility);
										IT::Add(Table.IDtable, entryit);
									}
								}
								else if (isParametr)
								{
									if (!strcmp(inStruct.tokens[i - 1].token, LEX_TYPE_INT))
									{
										IT::Entry entryit(inStruct.tokens[i].token, id++, IT::INT, IT::P, visibility);
										IT::Add(Table.IDtable, entryit);
									}
									else if (!strcmp(inStruct.tokens[i - 1].token, LEX_TYPE_STRING))
									{
										IT::Entry entryit(inStruct.tokens[i].token, id++, IT::STR, IT::P, visibility);
										IT::Add(Table.IDtable, entryit);
									}
									if (*inStruct.tokens[i + 1].token == LEX_RIGHTSESIS)
									{
										isParametr = false;
									}
									if (*inStruct.tokens[i + 2].token == LEX_LEFTBRACE)
									{
										strcpy_s(prevFun, ID_MAXSIZE, visibility);
									}
									else if (*inStruct.tokens[i + 2].token == LEX_SEMICOLON) 
									{
										strcpy_s(visibility, ID_MAXSIZE, prevFun);
									}
								}

								LT::Entry entrylt(graph[j].lexema, inStruct.tokens[i].line, operation, Table.IDtable.size - 1);
								LT::Add(Table.Lextable, entrylt);
								break;
							}
						}
						else
						{
							LT::Entry entrylt(graph[j].lexema, inStruct.tokens[i].line, operation,
								IT::IsId(Table.IDtable, inStruct.tokens[i].token, visibility));
							LT::Add(Table.Lextable, entrylt);
							break;
						}
					}
					case 'l':
					{
						isLiteral = true;
						break;
					}
					case '+':
					case '-':
					case '*':
					case '/':
					{
						operation = graph[j].lexema;
						LT::Entry entrylt('v', inStruct.tokens[i].line, operation);
						LT::Add(Table.Lextable, entrylt);
						operation = LEX_ZERO_OPERATION;
						break;
					}
					case 'm':
					{
						strncpy_s(visibility, ID_MAXSIZE, inStruct.tokens[i].token, ID_MAXSIZE - 1);
						LT::Entry entrylt('m', inStruct.tokens[i].line, operation);
						LT::Add(Table.Lextable, entrylt);
						break;
					}
					default:
					{
						LT::Entry entrylt(graph[j].lexema, inStruct.tokens[i].line, operation);
						LT::Add(Table.Lextable, entrylt);
						break;
					}
					}
					break;
				}
			}
			if (!isExecuted || isLiteral)
			{
				if ((inStruct.tokens[i].isLiteral || isLiteral) 
					&& IT::IsId(Table.IDtable, inStruct.tokens[i].token, visibility) == -1)
				{
					if ((litIndex = IsLiteral(Table.IDtable, inStruct.tokens[i].token)) == -1)
					{
						strcpy_s(Table.IDtable.literals[Table.IDtable.litCount], 50, inStruct.tokens[i].token);
						litIndex = Table.IDtable.litCount++;
					}
					switch (*Table.Lextable.table[i - 1].lexema)
					{
					case '=':
					{
						LT::Entry entrylt('l', inStruct.tokens[i].line, operation, Table.IDtable.size);
						LT::Add(Table.Lextable, entrylt);
						FST::FST typeINT(inStruct.tokens[i].token, graph[12].graph);
						FST::FST typeSTR(inStruct.tokens[i].token, graph[13].graph);
						if ((FST::execute(typeINT).rc && Table.IDtable.table[Table.Lextable.table[i - 2].idxTI].iddatatype == IT::STR) ||
							(FST::execute(typeSTR).rc && Table.IDtable.table[Table.Lextable.table[i - 2].idxTI].iddatatype == IT::INT))
						{
							throw ERROR_THROW_IN(114, inStruct.tokens[i].line, NULL)
						}
						/*if (Table.IDtable.table[Table.Lextable.table[i - 2].idxTI].idtype == IT::F)
						{
							throw ERROR_THROW_IN(115, inStruct.tokens[i].line, NULL);
						}*/
						if (Table.IDtable.table[Table.Lextable.table[i - 2].idxTI].idtype == IT::V)
						{
							IT::SetValue(Table.IDtable, Table.Lextable.table[i - 2].idxTI,
								Table.IDtable.literals[litIndex]);
						}
						break;
					}
					default:
						LT::Entry entrylt('l', inStruct.tokens[i].line, operation, Table.IDtable.size);
						LT::Add(Table.Lextable, entrylt);
						break;
					}
				}
				else throw ERROR_THROW_IN(124, Table.Lextable.table[i - 2].sn, NULL);
			}
			isExecuted = false;
			isLiteral = false;
		}
		return Table;
	}
}
