#pragma once
#define ID_MAXSIZE		10			// ������������ ���������� �������� � ��������������
#define TI_MAXSIZE		4096		// ������������ ���������� ����� � ������� ���������������
#define TI_BYTE_DEFAULT	0x00000000	// �������� �� ��������� ��� ���� byte
#define TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string
#define TI_BOOL_DEFAULT	0			// �������� �� ��������� ��� ���� bool
#define TI_NULLIDX		0xffffffff	// ��� ��e����� ������� ���������������
#define TI_STR_MAXSIZE	127			 
#include "Log.h"

namespace IT			// ������� ���������������
{
	enum IDDATATYPE { BOOL = 1, BYTE = 2, STR = 3 };			// ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5 };	// ���� ���������������: ����������, �������, ��������, �������, ��������
	//queue<IDDATATYPE> funparametrs;
	struct Entry	// ������ ������� ���������������
	{
		int			idxfirstLE;			// ������ ������ ������ � ������� ������
		unsigned char	id[ID_MAXSIZE];		// �������������� (������������� ��������� �� ID_MAXSIZE)
		unsigned char visibility[ID_MAXSIZE];
		IDDATATYPE	iddatatype;			// ��� ������
		IDTYPE		idtype;				// ��� ��������������
		union
		{
			int vbyte=0;					// �������� i
			struct
			{
				int len;						// ���������� �������� � string
				unsigned char str[TI_STR_MAXSIZE - 1];	// ������� string
			} vstr;				// �������� string
			bool vbool;
		} value;		// �������� ��������������
		struct funparms
		{
			int countparm = 0;//���������� ���������� 
			IDDATATYPE parmtypes[10];//������ ����� ����������
		}funparm;
	};

	struct IdTable				// ��������� ������� ���������������
	{
		int maxsize;			// ������� ������� ��������������� < TI_MAXSIZE
		int size;				// ������� ������ ������� ��������������� < maxsize
		Entry* table;			// ������ ����� ������� ���������������
	};

	IdTable Create(				// ������� ������� ���������������
		int size				// ������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		Entry entry			// ������ ������� ���������������
	);

	Entry GetEntry(			// �������� ������ ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		int n				// ����� ���������� ������
	);

	int IsId(				// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���)
		IdTable& idtable,	// ��������� ������� ���������������
		unsigned char id[ID_MAXSIZE]	// �������������
	);

	void Delete(IdTable& idtable);	// ������� ������� ��������������� (���������� ������)
	void showTable(IdTable& idtable, Log::LOG& log);  // ����� ������� ���������������
};