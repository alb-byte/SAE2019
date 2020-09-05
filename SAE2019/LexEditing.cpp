#include "stdafx.h"

void clearSpace(unsigned char source[], int size)			// ������� ���������� ��������
{
	char SP[] = { " ,;(){}=+-*%/?|" };
	bool findLit = false;
	for (int i = 0; i < size; i++) { // ��������� �����������
		if (source[i] == '\n')
			source[i] = '|';
	}
	for (int i = 0; i < size; i++) 
	{
		if (source[i] == '\"')	// ���� ����������� �������
			findLit = !findLit;	// ���������� ���� � ��������������� (false)
		if ( source[i] == ' ' && findLit == false)
		{		// ���� i-��� ������ - ������ � ��� �� �������
			for (int j = 0; j < sizeof(SP) - 1; j++)
			{
				if (source[i + 1] == SP[j] || source[i - 1] == SP[j] || i == 0)
				{	// ���� ��������� ��� ���������� ������ - ����������
					for (int k = i; k < size; k++)
					{	// ����� �������
						source[k] = source[k + 1];
					}
					i--;		// ������� �� �� �� �������
					break;
				}
			}
		}
	}
}

unsigned char** divideText(unsigned char source[], int size)		// ������������ ������� �����
{
	unsigned char** word = new unsigned char* [max_word];	//  ������ ����
	for (int i = 0; i < max_word; i++)
		word[i] = new unsigned char[size_word] {NULL};

	bool findSP, findLit = false;	// ������ ���������, ������ �������
	int j = 0;
	char SP[] = { " ,;(){}=+-*%/?|" };
	for (int i = 0, k = 0; i < size - 1; i++, k++)
	{
		findSP = false;
		if (source[i] == '\"')	// ���� ����������� �������
			findLit = !findLit;	// ���������� ���� � ��������������� (false)

		for (int t = 0; t < sizeof(SP) - 1; t++)
		{
			if (source[i] == SP[t] && findLit == false)		// ���� i-��� - ��������� � ��� �� �������
			{
				findSP = true;
				if (word[j][0] != NULL) {  // ���� � ������ ����� �� null
					word[j++][k] = '\0';	// �� �������� � ����� ����� \0
					k = 0;	// ������ ������� � ������� �������
				}
				if (SP[t] == ' ') {  // ���� ������ - ������ => ������� � ���������� �����
					k = -1;
					break;
				}
				word[j][k++] = SP[t];	// �������� ���������
				word[j++][k] = '\0';	// �������� � ����� ����� \0
				k = -1;		// ���������� � ������������� ������� �������
				break;
			}
		}
		if (!findSP)	// ���� �� ���������
			word[j][k] = source[i];		//�������� ������ � ������
	}
	word[j] = NULL;		//����������� ������ � null
	for (int i = 0; i < j; i++)
		if (!strcmp((char*)word[i], ""))	// ���� ���� ������ ������ => ������� null
			return NULL;
	return word;	// ����� - ������ ����
}

