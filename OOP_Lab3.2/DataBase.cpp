#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "DataBase.h"

using namespace std;

DataBase::DataBase(char* namefile) {
	bool isAvailable = false; //������ � �����
	stream = fopen(namefile, "rt");	//������� ������� ���� �� ������
	if (stream == NULL) {//�������� �� ������������� �����
		puts("����� �� ����������...");
	}
	else {
		this->fileName = namefile;
		fclose(stream);
	}
}

DataBase::~DataBase() {
	free(fileName);	//������������ ������, ���������� ��� �������� �����
}

void DataBase::add(char* note, int noteSize) {
	stream = fopen(fileName, "a");	//������� ���� � ����� append

	if (stream == NULL) {//�������� �� ������������� �����
		puts("����� �� ����������.");
		return;
	}

	char newLineSymbol[] = { '\n' };
	fwrite(note, 1, noteSize, stream);							//���������� ������
	fwrite(newLineSymbol, 1, sizeof(newLineSymbol), stream);	//������� ������� �� ����� ������
	fclose(stream);
}

int DataBase::get(char* note, int noteSize, int indexOfOriginString) {
	stream = fopen(fileName, "r");			//������� ���� � ����� read

	if (stream == NULL) {					//�������� �� ������������� �����
		puts("����� �� ����������.");
		return -1;
	}

	int index = 0;
	int counterForDesiredString = 0;
	char currentSymbol = '/0';
	bool isDesiredString = true;

	//������ �����
	fseek(stream, 0, SEEK_END);
	long fileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);

	//��������� ������� �������
	for (int i = 0; ftell(stream) != fileSize;) {
		currentSymbol = fgetc(stream);
		if (currentSymbol == '\n') {
			if (index >= indexOfOriginString && isDesiredString && counterForDesiredString == noteSize) {
				fclose(stream);
				return index;
			}
			index++;
			i = 0;
			counterForDesiredString = 0;
			isDesiredString = true;
		}
		else {
			if (isDesiredString && currentSymbol == note[i]) counterForDesiredString++;
			else isDesiredString = false;
			i++;
		}
	}
	if (ftell(stream) == fileSize) index = -1;
	fclose(stream);

	return index;
}

int* DataBase::getAll(char* note, int noteSize) {
	int resultSize = MAXINT16;
	int* result = (int*)malloc(sizeof(int) * resultSize);	//��������� ������ ��� �������� ������� ��������, ��������������� �������� ������
	for (int i = 0; i < resultSize; i++) {					//������������� (-1)-��
		result[i] = -1;
	}

	//��������� ���� ��������, ������� ����� ���������� note 
	for (int currentIndex = get(note, noteSize, 0), i = 0; currentIndex != -1; i++) {
		result[i] = currentIndex;
		currentIndex = get(note, noteSize, currentIndex + 1);
	}

	int length = 0;
	for (; length < resultSize; length++) {								//��������� ��������� ������� �������
		if (result[length] == -1) break;
	}
	resultSize = length;
	result = (int*)realloc(result, sizeof(int) * (resultSize + 1));		//����������������� ������

	fclose(stream);
	return result;
}

char* DataBase::getById(int id) {
	stream = fopen(fileName, "r");			//������� ���� � ����� read

	if (stream == NULL) {					//�������� �� ������������� �����
		puts("����� �� ����������.");
		char nullArray[] = "\n";
		return nullArray;
	}

	char* mem = (char*)calloc(sizeof(char) * 255, 1);							//��������� ������ ��� �������� ����������� ����� �� �����
	for (int i = 0; i <= id && (mem = fgets(mem, 255, stream)) != NULL; i++);	//���� �� ���������� ������ ������ ����� ������
	if (mem == NULL) {															//�������� �� ������������� �������
		puts("����� �� ������� �����.");
		char nullArray[] = "\n";
		return nullArray;
	}

	fclose(stream);
	return mem;
}
