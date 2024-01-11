#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "DataBase.h"

class Executor {
private:
	//указатели на объекы базы данных
	DataBase* dataBaseFio;
	DataBase* dataBaseDolgh;
	DataBase* dataBaseLink;

public:
	Executor(DataBase& dataBaseFio, DataBase& dataBaseDolgh, DataBase& dataBaseLink);

	void addPerson(char* surname, int surnameSize, char* position, int positionSize);	//Добавить сотрудника
	void addPosition(char* position, int positionSize);									//Добавить должность
	void getSurnamesByPosition(char* position, int positionSize);						//Вывод фамилий по должности
};

