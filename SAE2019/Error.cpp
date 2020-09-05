#include "stdafx.h"      

namespace Error
{

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),		// ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY(20, "�������� -in ������ ���� �����"),
		ERROR_ENTRY(21, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(22),ERROR_ENTRY_NODEF(23),ERROR_ENTRY_NODEF(24),
		ERROR_ENTRY_NODEF(25),ERROR_ENTRY_NODEF(26),ERROR_ENTRY_NODEF(27),
		ERROR_ENTRY_NODEF(28),ERROR_ENTRY_NODEF(29),
		ERROR_ENTRY(30, "������ ��� �������� ����� � �������� ����� (-in)"),//+
		ERROR_ENTRY(31, "������������ ������ � �������� ����� (-in)"),//+
		ERROR_ENTRY(32, "������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(33,"������ �������� ��������� asm �����"),
		ERROR_ENTRY_NODEF(34),
		ERROR_ENTRY_NODEF(35),ERROR_ENTRY_NODEF(36),
		ERROR_ENTRY_NODEF(37),ERROR_ENTRY_NODEF(38),ERROR_ENTRY_NODEF(39),
		ERROR_ENTRY(40,"�������� ����������� ������ ������� ������"),//+
		ERROR_ENTRY(41,"������� ������ �����������"),//+
		ERROR_ENTRY(42,"������ ������������ �������"),//+
		ERROR_ENTRY(43,"������� ��������������� �����������"),//+
		ERROR_ENTRY(44,"�������� ����������� ������ ������� ���������������"),//+
		ERROR_ENTRY(45,""),
		ERROR_ENTRY(46,""),
		ERROR_ENTRY(47,"��� ���������� � ����������� �������� �� ���������"),//+
		ERROR_ENTRY(48,"��������� ������ ���� ���������� ��� ��������� ������������� ���������"),//5=bl;
		ERROR_ENTRY(49,"��������� ������ ���������� � �������������� ����"),//100b+"string"

		ERROR_ENTRY(50,"�������� ��� ������������� ���������"),//Fmath(c,2);
		ERROR_ENTRY(51,"�������� ���������� ����������"),//Fmath(a);
		ERROR_ENTRY(52,"������� main �� ���������"),//+
		ERROR_ENTRY(53,"������� main ��������� ��������"),//+
		ERROR_ENTRY(54,"��������� ���������� ����������"),//+
		ERROR_ENTRY(55,"��������� ���������� �������"),//+
		ERROR_ENTRY(56,"������������� ����� �������"),//+
		ERROR_ENTRY(57,"����������� �������������"),//+
		ERROR_ENTRY(58,""),//
		ERROR_ENTRY(59,""),

		ERROR_ENTRY(60,"������� ������ ���������� ��������"),//+
		ERROR_ENTRY(61,"�������� return �� ����� ��������� ������ ��������� �����"),//+
		ERROR_ENTRY(62,"�������� ������������� ���"),//+
		ERROR_ENTRY(63,"������� �� ����� ��������� ������ 3-x ����������"),//+
		ERROR_ENTRY(64,""),//+
		ERROR_ENTRY(65,""),//+
		ERROR_ENTRY(66,""),//+
		ERROR_ENTRY(67,""),//+
		ERROR_ENTRY(68,""),//+
		ERROR_ENTRY(69,""),

		ERROR_ENTRY(70,"������ ������ ������ ����������� ����������"),//"������ �� ������� Fstrddddddddddddd";
		ERROR_ENTRY(71,"������� ������� ������������� �������"),//+
		ERROR_ENTRY(72,""),//
		ERROR_ENTRY(73,"����������� ������ �������� ������������ ������� ���������"),//+
		ERROR_ENTRY(74,"����������� ������ �������� �������� ������� ���������"),//+
		ERROR_ENTRY(75,""),//
		ERROR_ENTRY(76,""),//
		ERROR_ENTRY(77,""),//
		ERROR_ENTRY(78,""),//
		ERROR_ENTRY(79,""),


		ERROR_ENTRY(80,"�������� ��������� ���������"),//+
		ERROR_ENTRY(81,"�������� ��������� �������"),//+
		ERROR_ENTRY(82,"������ � ���������"),//+
		ERROR_ENTRY(83,"������ � ���������� ���������� �������"),//+
		ERROR_ENTRY(84,"������ � ����������� ����������  �������"),//+
		ERROR_ENTRY(85,"������ � �������� ���������"),//
		ERROR_ENTRY(86,""),//
		ERROR_ENTRY(87,""),//
		ERROR_ENTRY(88,""),//
		ERROR_ENTRY(89,""),

		ERROR_ENTRY_NODEF10(90)
	};

	ERROR GetError(short id)
	{
		ERROR error;
		if (id < 0 || id > ERROR_MAX_ENTRY)
		{
			return errors[0];
		}
		error.id = id;
		strcpy_s(error.message, errors[id].message);
		return error;
	}

	ERROR GetErrorIn(short id, short line = -1, short column = -1)
	{
		ERROR error;
		if (id < 0 || id > ERROR_MAX_ENTRY)
		{
			return errors[0];
		}
		error.id = id;
		error.inext.line = line;
		error.inext.column = column;
		strcpy_s(error.message, errors[id].message);
		return error;
	}
};