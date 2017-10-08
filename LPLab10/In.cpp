#include "stdafx.h"

using namespace std;
using namespace In;

void In::addToken(IN &myIn, char* &buffer, int &bufPos, int line, bool isLiteral)
{
	buffer[bufPos] = 0x00;
	myIn.tokens[myIn.tokensCount].line = line;
	strcpy_s((myIn.tokens[myIn.tokensCount++].token), (bufPos + 1), buffer);
	myIn.tokens->isLiteral = isLiteral;
	buffer[0] = 0x00;
	bufPos = NULL;
	return;
}
void letter(IN &myIn, char* &buffer, int &bufPos, char tempChar)
{
	buffer[bufPos++] = tempChar;
	myIn.text[myIn.size] = tempChar;
	return;
}

namespace Log
{
	IN getin(wchar_t infile[], LOG log)
	{
		IN myIn;

		int position = 0, bufPos = 0;

		myIn.size = 0;
		myIn.lines = 1;
		myIn.ignor = 0;
		myIn.Errors = 0;
		myIn.tokensCount = 0;
		myIn.text = new char[IN_MAX_LEN_TEXT];

		myIn.tokens = new Token[1024];
		char *buffer = new char[1024];
		bool isLiteral = false;
		bool isFull = true;
		bool isBracket = false;
		int cnt = 0;
		char prev = '\0';

		ifstream inFile;
		inFile.open(infile);

		if (!inFile)
		{
			throw ERROR_THROW(110);
		}
		else     
		{
			unsigned char tempChar;
			while ((tempChar = inFile.get()) && !inFile.eof())
			{
				switch (myIn.code[tempChar])
				{
				case myIn.STAB:
				{
					if (tempChar == ' ' && prev == ' ') continue;
					if (!isFull && tempChar == ' ')
					{
						letter(myIn, buffer, bufPos, tempChar);
					}
					if (bufPos != 0 && isFull)
					{
						In::addToken(myIn, buffer, bufPos, myIn.lines, isLiteral);
						isLiteral = false;
					}
					if (tempChar == IN_CODE_ENDL && prev != IN_CODE_ENDL && !isBracket)
					{
						myIn.text[myIn.size] = IN_CODE_ENDL;
						myIn.lines++;
						position = 0;
					}
					break;
				}
				case myIn.SEP:
				{
					if (!isFull) letter(myIn, buffer, bufPos, tempChar);
					else
					{
						if (tempChar == '(') isBracket = true;
						else if (tempChar == ')') isBracket = false;
						if (bufPos != 0) In::addToken(myIn, buffer, bufPos, myIn.lines, isLiteral);
						letter(myIn, buffer, bufPos, tempChar);
						if (bufPos != 0) In::addToken(myIn, buffer, bufPos, myIn.lines, isLiteral);
						isLiteral = false;
					}
					break;
				}
				case myIn.F:
				{
					myIn.Errors++;
					throw ERROR_THROW_IN(111, myIn.lines, position);
					Log::WriteError(log, Error::geterrorin(111, myIn.lines, (position + 1)));
					break;
				}
				case myIn.T:
				{
					letter(myIn, buffer, bufPos, tempChar);
					if (tempChar == '\'')
					{
						isFull = false;
						cnt++;
						isLiteral = true;
						if (cnt == 2)
						{
							isFull = true;
							cnt = 0;
						}
					}
 					break;
				}
				case myIn.I:
				{
					myIn.ignor++;
					continue;
				}
				}
				prev = tempChar;
				position++;
				myIn.size++;
			}

			myIn.text[myIn.size] = '\0';
 			myIn.size--;

			inFile.close();
		}

		if (myIn.size == 0)
		{
			myIn.lines = 0;
		} 
		return myIn;
	}
}
