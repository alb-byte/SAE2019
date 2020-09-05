#pragma once
#define ERROR_THROW(id) Error::GetError(id);					// ������������ ERROR ��� ERROR_THROW;		//	throw	ERROR_THROW(id)
#define ERROR_THROW_IN(id, l, c) Error::GetErrorIn(id,l,c);		//	throw	ERROR_THROW(id, ������, ������� � ������)
#define ERROR_ENTRY(id, m) {id, m, {-1, -1}}					//	������� ������� ������
#define ERROR_MAXSIZE_MESSAGE 200								//	������������ ����� ��������� �� ������
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(-id, "�������������� ������")	// 1 �������������� ������� ������� ������
// ERROR_ENTRY_NODEF10(id) - 10 �������������� ��������� ������� ������
#define ERROR_ENTRY_NODEF10(id)	   ERROR_ENTRY_NODEF(id + 0), ERROR_ENTRY_NODEF(id + 1), ERROR_ENTRY_NODEF(id + 2), ERROR_ENTRY_NODEF(id + 3), \
		ERROR_ENTRY_NODEF(id + 4), ERROR_ENTRY_NODEF(id + 5), ERROR_ENTRY_NODEF(id + 6), ERROR_ENTRY_NODEF(id + 7), \
		ERROR_ENTRY_NODEF(id + 8), ERROR_ENTRY_NODEF(id + 9)
#define ERROR_MAX_ENTRY 100			//	���������� ��������� � ������� ������

namespace Error
{
	struct ERROR	// ��� ���������� ��� throw ERROR_THROW |ERROR_THROW_IN � catch(ERROR)
	{
		int id;									// ��� ������
		char message[ERROR_MAXSIZE_MESSAGE];	// ��������� �� ������
		struct IN								// ���������� ��� ������ ��� ��������� ������� ������
		{
			short line;							// ����� ������ (0, 1, 2, ...)
			short column;							// ����� ������� � ������ (0, 1, 2, ...)
		} inext;
	};
	ERROR GetError(short id);							// ������������ ERROR ��� ERROR_THROW
	ERROR GetErrorIn(short id, short line, short column);	// ������������ ERROR ��� ERROR_THROW_IN
}