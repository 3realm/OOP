#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

class DataBase {
private:
	FILE* stream;			//указатель на поток
	char* fileName;			//имя файла		

public:
	DataBase(char* fileName);
	~DataBase();
	void add(char* note, int noteSize);		//Добавить в файл запись 
	int get(char* note, int noteSize);		//Получить с файла индекс записи
	int* getAll(char* note, int noteSize);	//Получить с файла все индексы, которые соответствуют указанной записи
	char* getById(int id);					//Получить с файла запись по индексу
};

