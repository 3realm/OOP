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
	//��������� ������� ���������
	int gettedPosition = dataBaseDolgh->get(position, positionSize, 0);
	if (gettedPosition == -1) {
		cout << "����� ��������� �� �������." << endl;
		return;
	}

	//���������� ������� � ������
	int gettedSurname = dataBaseFio->get(surname, surnameSize, 0);	//�������� �� ������� ���� ������� � ������
	if (gettedSurname == -1) {
		dataBaseFio->add(surname, surnameSize);
	}
	else {
		cout << "���� ������� ��� ����� � ������." << endl;
		return;
	}

	char strPos[10];
	_itoa(gettedPosition, strPos, 10);			//�������������� ����� � ������ ��������
	int length = 0;
	for (; length < sizeof(strPos); length++) {	//��������� ��������� ������� �������
		if (strPos[length] == '\0') break;
	}
	dataBaseLink->add(strPos, length);		//���������� ������������ ����� �������� � ����������
}

void Executor::addPosition(char* position, int positionSize) {
	int gettedPosition = dataBaseDolgh->get(position, positionSize, 0); //�������� �� ������� ���� ��������� � ������
	if (gettedPosition == -1) {
		dataBaseDolgh->add(position, positionSize);
	}
	else {
		cout << "����� ��������� ��� ����." << endl;
	}
}

void Executor::getSurnamesByPosition(char* position, int positionSize) {
	int gettedPosition = dataBaseDolgh->get(position, positionSize, 0); //�������� �� ������� ���� ��������� � ������
	if (gettedPosition == -1) {
		cout << "����� ��������� �� �������." << endl;
		return;
	}

	char strPos[10];
	_itoa(gettedPosition, strPos, 10);			//�������������� ����� � ������ ��������
	int length = 0;
	for (; length < sizeof(strPos); length++) {	//��������� ��������� ������� �������
		if (strPos[length] == '\0') break;
	}

	int* personsIndexes = dataBaseLink->getAll(strPos, length);	//��������� ������� ��������, ������� ������������� ��������� strPos

	//���� �������������� �������� � �������
	for (int i = 0; personsIndexes[i] != -1; i++) {
		char* gettedSurname = dataBaseFio->getById(personsIndexes[i]);
		if (*gettedSurname != '\0') {
			printf(gettedSurname);
		}
	}
}
