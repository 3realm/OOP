#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

class DataBase {
private:
	FILE* stream;			//��������� �� �����
	char* fileName;			//��� �����		

public:
	DataBase(char* fileName);
	~DataBase();
	void add(char* note, int noteSize);		//�������� � ���� ������ 
	int get(char* note, int noteSize);		//�������� � ����� ������ ������
	int* getAll(char* note, int noteSize);	//�������� � ����� ��� �������, ������� ������������� ��������� ������
	char* getById(int id);					//�������� � ����� ������ �� �������
};

