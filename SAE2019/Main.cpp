#include "stdafx.h"

int wmain(int argc, wchar_t* argv[])
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	In::IN in = In::INITIN;
	try
	{
		Parm::PARM parm = Parm::GetParm(argc, argv);
		log = Log::GetLog(parm.log);
		Log::WriteLine(log, (char*)"����:", (char*)"��� ������", (char*)"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		in = In::GetIn(parm.in);
		Log::WriteIn(log, in);
		cout << in.text << endl;
		cout << "����� ��������: " << in.size << endl;
		cout << "����� �����: " << in.lines << endl;
		cout << "���������: " << in.ignore << endl;

		Lex::LEX lex = Lex::LexAnaliz(log, in);
		IT::showTable(lex.idtable, log);
		LT::showTable(lex.lextable, log);
		MFST_TRACE_START;
		MFST::MFST mfst(lex.lextable, GRB::getGreibach(), log);
		mfst.start();
		mfst.saveoutputTree();
		mfst.printRules();
		Lex::PolishNotation(lex.lextable, lex.idtable);

		CodeGeneration::CodeGeneration(lex, log);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		std::cout << "������ " << e.id << ": " << e.message <<" ������: "<<e.inext.line<<endl << endl;
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}
