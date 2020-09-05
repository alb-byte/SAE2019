#pragma once
#include "GRB.h"
#include "LT.h"
#include <stack>
#include <iomanip>
#include "Log.h"
#define MFST_DIAGN_MAXSIZE 2 * ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

static int FST_TRACE_n = -1;
static char rbuf[1000]{}, sbuf[205]{}, lbuf[1000]{};
#define MFST_TRACE_START *log.stream<<std::setfill(' ')<<std::setw( 4)<< std::left<<"���"<< ':'		\
								  <<std::setw(20)<< std::left<<" �������"		\
								  <<std::setw(30)<< std::left<<" ������� �����"	\
								  <<std::setw(20)<< std::left<<" ����"			\
								  <<std::endl;

#define MFST_TRACE1		*log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<< ": "	\
									<<std::setw(20)<<std::left<<rule.getCRule(rbuf, nrulechain) \
									<<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position)	\
									<<std::setw(20)<<std::left<<getCSt(sbuf)	\
									<<std::endl;
#define MFST_TRACE2		*log.stream<<std::setw(4)<<std::left<<FST_TRACE_n<< ": "	\
									<<std::setw(20)<<std::left<< " "	\
									<<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position)	\
									<<std::setw(20)<<std::left<<getCSt(sbuf)	\
									<<std::endl;
#define MFST_TRACE3		*log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<< ": "	\
									<<std::setw(20)<<std::left<< " "	\
									<<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position)	\
									<<std::setw(20)<<std::left<<getCSt(sbuf)	\
									<<std::endl;

#define MFST_TRACE4(c) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<< ": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(c) *log.stream<<std::setw(4)<<std::left<<  FST_TRACE_n<< ": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE6(c,k) *log.stream<<std::setw(4)<<std::left<<  FST_TRACE_n<< ": "<<std::setw(20)<<std::left<<c<<k<<std::endl;
#define	MFST_TRACE7		*log.stream << std::setw(4) << std::left << state.lenta_position<<": "	\
									<<std::setw(20)<<std::left<<rule.getCRule(rbuf, state.nrulechain)	\
									<<std::endl;


namespace MFST
{
	struct MFSTState	// ��������� �������� (��� ����������)
	{
		short lenta_position;
		short nrule;
		short nrulechain;		// ����� ������� �������, �������� �������
		std::stack<short> stack_mfst;	// ���� ��������

		MFSTState();
		MFSTState(short posInLent, std::stack<short>& a_steck, short currentChain);
		MFSTState(short posInLent, std::stack<short>& a_stack, short currentRule, short currentChain);

	};

	struct MFST // ���������� �������
	{
		enum RC_STEP //��� �������� ������� step
		{
			NS_OK,			// ������� ������� � �������, ������� �������� � ���� 
			NS_NORULE,		// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,	// �� ������� ��������� ������� ������� (������ � �������� ����)
			NS_ERROR,		// ���������� �������������� ������ ����������
			TS_OK,			// ���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,			// ���. ������ ����� != ������� �����, �������������� ��������� 
			LENTA_END,		// ������ ������� ����� >= lenta_size 
			SURPRISE		// ����������� ��� �������� (������ � step)
		};

		struct MFST_Diagnosis	// �����������
		{
			short	lenta_position;		// ������� �� ����� 
			RC_STEP	rc_step;			// ��� ���������� ���� 
			short	nrule;			// ����� ������� 
			short	nrulechain;		// ����� ������� �������
			MFST_Diagnosis();
			MFST_Diagnosis(short lenta_position, RC_STEP rc_step, short nrule, short nrulechain);
		} diagnosis[MFST_DIAGN_NUMBER]; // ��������� ����� �������� ���������

		GRBALPHABET* lenta;					// ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;				// ������� ������� �� �����
		short nrule;					// ����� �������� �������
		short nrulechain;				// ����� ������� �������, �������� �������
		short lenta_size;					// ������ �����
		GRB::Greibach grebach;				// ���������� �������
		LT::LexTable lexTable;
		std::stack<short> stack_mfst;				// ���� ��������
		std::stack<MFSTState> storestate;	// ���� ��� ���������� ���������
		Log::LOG log;
		MFST();
		MFST(const LT::LexTable& lexTable, GRB::Greibach grebach, Log::LOG log);

		char* getCSt(char* buf);			//�������� ��������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	//�����: n ��������, ������� � pos
		char* getDiagnosis(short n, char* buf);		//�������� n-�� ������ ����������� ��� '\0'

		bool savestate();	//��������� ��������� ��������
		bool resetstate();	//������������ ��������� ��������
		bool push_chain(GRB::Rule::Chain chain);

		RC_STEP step();		//��������� ��� ��������
		bool start();		//��������� �������
		bool savedDiagnosis(RC_STEP prc_step);

		void printRules();	//������� ������������������ ������

		struct Output
		{
			short stepscounter;
			short* nrules;
			short* nrulechain;

			Output()
			{
				this->stepscounter = 0;
				this->nrules = 0;
				this->nrulechain = 0;
			}
		}output;

		bool saveoutputTree();
	};
}

