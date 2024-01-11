#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "DataBase.h"

class Executor {
private:
	//��������� �� ������ ���� ������
	DataBase* dataBaseFio;
	DataBase* dataBaseDolgh;
	DataBase* dataBaseLink;

public:
	Executor(DataBase& dataBaseFio, DataBase& dataBaseDolgh, DataBase& dataBaseLink);

	void addPerson(char* surname, int surnameSize, char* position, int positionSize);	//�������� ����������
	void addPosition(char* position, int positionSize);									//�������� ���������
	void getSurnamesByPosition(char* position, int positionSize);						//����� ������� �� ���������
};

