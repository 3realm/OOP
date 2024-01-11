#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "DataBase.h"

using namespace std;

DataBase::DataBase(char* namefile) {
	bool isAvailable = false; //Доступ к файлу
	stream = fopen(namefile, "rt");	//Попытка открыть файл на чтение
	if (stream == NULL) {//Проверка на существование файла
		puts("Файла не существует...");
	}
	else {
		this->fileName = namefile;
		fclose(stream);
	}
}

DataBase::~DataBase() {
	free(fileName);	//освобождение памяти, выделенной под название файла
}

void DataBase::add(char* note, int noteSize) {
	stream = fopen(fileName, "a");	//Открыть файл в режим append

	if (stream == NULL) {//Проверка на существование файла
		puts("Файла не существует.");
		return;
	}

	char newLineSymbol[] = { '\n' };
	fwrite(note, 1, noteSize, stream);							//Добавление записи
	fwrite(newLineSymbol, 1, sizeof(newLineSymbol), stream);	//переход каретки на новую строку
	fclose(stream);
}

int DataBase::get(char* note, int noteSize, int indexOfOriginString) {
	stream = fopen(fileName, "r");			//Открыть файл в режим read

	if (stream == NULL) {					//Проверка на существование файла
		puts("Файла не существует.");
		return -1;
	}

	int index = 0;
	int counterForDesiredString = 0;
	char currentSymbol = '/0';
	bool isDesiredString = true;

	//Размер файла
	fseek(stream, 0, SEEK_END);
	long fileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);

	//Получение нужного индекса
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
	int* result = (int*)malloc(sizeof(int) * resultSize);	//Выделение памяти под хранение массива индексов, соответствующих введённой строке
	for (int i = 0; i < resultSize; i++) {					//Инициализация (-1)-ми
		result[i] = -1;
	}

	//Получение всех индексов, который равны указанному note 
	for (int currentIndex = get(note, noteSize, 0), i = 0; currentIndex != -1; i++) {
		result[i] = currentIndex;
		currentIndex = get(note, noteSize, currentIndex + 1);
	}

	int length = 0;
	for (; length < resultSize; length++) {								//Получение реального размера массива
		if (result[length] == -1) break;
	}
	resultSize = length;
	result = (int*)realloc(result, sizeof(int) * (resultSize + 1));		//Перераспределение памяти

	fclose(stream);
	return result;
}

char* DataBase::getById(int id) {
	stream = fopen(fileName, "r");			//Открыть файл в режим read

	if (stream == NULL) {					//проверка на существование файла
		puts("Файла не существует.");
		char nullArray[] = "\n";
		return nullArray;
	}

	char* mem = (char*)calloc(sizeof(char) * 255, 1);							//Выделение памяти для хранения считываемых строк из файла
	for (int i = 0; i <= id && (mem = fgets(mem, 255, stream)) != NULL; i++);	//Цикл по нахождению нужной строки через индекс
	if (mem == NULL) {															//Проверка на существование индекса
		puts("Выход за границу файла.");
		char nullArray[] = "\n";
		return nullArray;
	}

	fclose(stream);
	return mem;
}
