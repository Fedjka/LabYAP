#include "stdafx.h"
#include "LexAnalysis.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log;
	int line = 1, col = 0;
	FST::gek sw;
	cout << "---- ���� getlog ----" << endl << endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "����:", "��� ������ ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = Log::getin(parm.in, log);
		LexAnalysis::LEX Lex = LexAnalysis::Analysis(in, log);
		Log::writeLexTable(log, Lex.Lextable);
		Log::writeIDtable(log, Lex.IDtable);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		cout << "������� ������!" << endl;
		cout << "��� ������: " << e.id << endl;
		cout << "�������� ������: " << e.message << endl;
		cout << "������ � �������: " << e.inext.line << endl;
		cout << "������� ������: " << e.inext.col << endl;
		Log::Close(log);
	}
	//system("pause");
	return 0;
}

