#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "Executor.h"

using namespace std;

Executor::Executor(DataBase& dataBaseFioInput, DataBase& dataBaseDolghInput, DataBase& dataBaseLinkInput) {
	dataBaseFio = &dataBaseFioInput;
	dataBaseDolgh = &dataBaseDolghInput;
	dataBaseLink = &dataBaseLinkInput;
}

void Executor::addPerson(char* surname, int surnameSize, char* position, int positionSize) {
	//Получение индекса должности
	int gettedPosition = dataBaseDolgh->get(position, positionSize, 0);
	if (gettedPosition == -1) {
		cout << "Такой должности не найдено." << endl;
		return;
	}

	//Добавление фамилии в список
	int gettedSurname = dataBaseFio->get(surname, surnameSize, 0);	//Проверка на наличие этой фамилии в списке
	if (gettedSurname == -1) {
		dataBaseFio->add(surname, surnameSize);
	}
	else {
		cout << "Этот человек уже внесён в список." << endl;
		return;
	}

	char strPos[10];
	_itoa(gettedPosition, strPos, 10);			//Преобразование числа в массив символов
	int length = 0;
	for (; length < sizeof(strPos); length++) {	//Получение реального размера массива
		if (strPos[length] == '\0') break;
	}
	dataBaseLink->add(strPos, length);		//Добавление соответствия между фамилией и должностью
}

void Executor::addPosition(char* position, int positionSize) {
	int gettedPosition = dataBaseDolgh->get(position, positionSize, 0); //Проверка на наличие этой должности в списке
	if (gettedPosition == -1) {
		dataBaseDolgh->add(position, positionSize);
	}
	else {
		cout << "Такая должность уже есть." << endl;
	}
}

void Executor::getSurnamesByPosition(char* position, int positionSize) {
	int gettedPosition = dataBaseDolgh->get(position, positionSize, 0); //Проверка на наличие этой должности в списке
	if (gettedPosition == -1) {
		cout << "Такой должности не найдено." << endl;
		return;
	}

	char strPos[10];
	_itoa(gettedPosition, strPos, 10);			//Преобразование числа в массив символов
	int length = 0;
	for (; length < sizeof(strPos); length++) {	//Получение реального размера массива
		if (strPos[length] == '\0') break;
	}

	int* personsIndexes = dataBaseLink->getAll(strPos, length);	//Получение массива индексов, которые соответствуют должности strPos

	//Цикл преобразования индексов в фамилии
	for (int i = 0; personsIndexes[i] != -1; i++) {
		char* gettedSurname = dataBaseFio->getById(personsIndexes[i]);
		if (*gettedSurname != '\0') {
			printf(gettedSurname);
		}
	}
}
