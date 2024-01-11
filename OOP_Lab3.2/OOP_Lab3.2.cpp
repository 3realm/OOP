#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <Windows.h>
#include <conio.h>
#include "DataBase.h"
#include "Executor.h"

using namespace std;

/*
ВАРИАНТ №5.
Реализовать информационную базу, состоящую из трех файлов: FIO.DAT -
содержит в виде символьных строк, оканчивающихся <\n>, список фамилий;
DOLGH.DAT - содержит в виде символьных строк наименования должностей,
которые не повторяются; LINK.IDX - содержит записи вида struct {unsigned
long name_idx; //индекс записи в файле FIO.DAT; unsigned long post_idx;
//индекс записи в файле DOLGH.DAT}, связывающие между собой фамилию и
должность. В качестве индексов используются значения позиций, с которых
начинаются записи в соответствующих файлах. Записи в FIO.DAT и в LINK.IDX
взаимно-однозначно соответствуют друг другу. Программа должна обеспечивать
выполнение следующих функций: 1) включение новой фамилии с указанием
должности, 2) добавление новой должности, 3) по указанной должности вывод на
экран всех соответствующих фамилий. */

//Описание
void prescription() {
	puts("Автор:\tКажуков Павел, студент группы 6214-020302D, Вариант №5");
	puts("---------------------------------------------------------------------------------------");
	puts("Условия:\nРеализовать информационную базу, состоящую из трех файлов: FIO.DAT - \n\
содержит в виде символьных строк, оканчивающихся <\\n>, список фамилий; \n\
DOLGH.DAT - содержит в виде символьных строк наименования должностей, \n\
которые не повторяются; LINK.IDX - содержит записи вида struct {unsigned \n\
long name_idx; //индекс записи в файле FIO.DAT; unsigned long post_idx; \n\
//индекс записи в файле DOLGH.DAT}, связывающие между собой фамилию и \n\
должность. В качестве индексов используются значения позиций, с которых \n\
начинаются записи в соответствующих файлах. Записи в FIO.DAT и в LINK.IDX \n\
взаимно-однозначно соответствуют друг другу. Программа должна обеспечивать \n\
выполнение следующих функций: \n\
1) включение новой фамилии с указанием должности,\n\
2) добавление новой должности, \n\
3) по указанной должности вывод на экран всех соответствующих фамилий. ");
	puts("---------------------------------------------------------------------------------------");
}
//Вывод на экран текста меню
void showMenu() {
	puts("1 - Добавить сотрудника");
	puts("2 - Добавить должность");
	puts("3 - Вывод фамилий по должности");
	puts("0 - Выход");
}
//Метод очистки буффера ввода
void clear() {
	for (int c = getchar(); c != '\n' && c != EOF; c = getchar());
}
//Метод конкатенации строк
char* concateStr(char* str1, int str1Size, char* str2, int str2Size) {
	char* result = (char*)malloc(sizeof(char) * (str1Size + str2Size));

	int i = 0;
	for (; i < str1Size; i++) {
		if (str1[i] == '\0') break;
		result[i] = str1[i];
	}

	for (int j = 0; j < str2Size; j++) {
		result[i++] = str2[j];
	}

	return result;
}

struct Employee {
	unsigned long name_idx;
	unsigned long post_idx;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "Russian");

	prescription();

	char currentDirectoryPath[MAX_PATH];
	_getcwd(currentDirectoryPath, sizeof(currentDirectoryPath));	//Получение текцщей директории

	//Получение путей до файлов
	char str1[] = "\\FIO.dat";
	char* fioStr = concateStr(currentDirectoryPath, sizeof(currentDirectoryPath), str1, sizeof(str1));
	char str2[] = "\\DOLGH.dat";
	char* dolghStr = concateStr(currentDirectoryPath, sizeof(currentDirectoryPath), str2, sizeof(str2));
	char str3[] = "\\LINK.idx";
	char* linkStr = concateStr(currentDirectoryPath, sizeof(currentDirectoryPath), str3, sizeof(str3));

	DataBase dataBaseFio(fioStr);
	DataBase dataBaseDolgh(dolghStr);
	DataBase dataBaseLink(linkStr);
	Executor executor(dataBaseFio, dataBaseDolgh, dataBaseLink);

	showMenu();
	puts("---------------------------------------------------------------------------------------");
	int choice = 0;
	//Цикл меню
	do {
		cout << "Введите пункт меню: ";
		choice = getchar() - 48;
		clear();

		switch (choice) {

			//Выход
		case 0: {
			break;
		}

			  //Добавить сотрудника
		case 1: {
			char* inputSurname = (char*)malloc(sizeof(char) * 100);
			char* inputPosition = (char*)malloc(sizeof(char) * 100);

			cout << "Введите фамилию сотрудника: ";
			scanf("%s", inputSurname);
			clear();
			int lengthSurname = 0;
			for (; lengthSurname < 100 && inputSurname[lengthSurname] != '\0'; lengthSurname++);		//Получение реальной длины массива символов
			inputSurname = (char*)realloc(inputSurname, lengthSurname);

			cout << "Введите должность сотрудника: ";
			scanf("%s", inputPosition);
			clear();
			int lengthPosition = 0;
			for (; lengthPosition < 100 && inputPosition[lengthPosition] != '\0'; lengthPosition++);	//Получение реальной длины массива символов
			inputPosition = (char*)realloc(inputPosition, lengthPosition);

			executor.addPerson(inputSurname, lengthSurname, inputPosition, lengthPosition);

			//Очитска памяти
			free(inputSurname);
			free(inputPosition);
			break;
		}

			  //Добавить должность
		case 2: {
			char* newPosition = (char*)malloc(sizeof(char) * 100);

			cout << "Введите название должности: ";
			scanf("%s", newPosition);
			clear();
			int lengthPosition = 0;
			for (; lengthPosition < 100 && newPosition[lengthPosition] != '\0'; lengthPosition++);		//Получение реальной длины массива символов
			newPosition = (char*)realloc(newPosition, lengthPosition);

			executor.addPosition(newPosition, lengthPosition);

			//Очитска памяти
			free(newPosition);
			break;
		}

			  //Вывод фамилий по должности
		case 3: {
			char* checkedPosition = (char*)malloc(sizeof(char) * 100);

			cout << "Введите название должности: ";
			scanf("%s", checkedPosition);
			clear();
			int lengthPosition = 0;
			for (; lengthPosition < 100 && checkedPosition[lengthPosition] != '\0'; lengthPosition++);	//Получение реальной длины массива символов
			checkedPosition = (char*)realloc(checkedPosition, lengthPosition + 1);

			executor.getSurnamesByPosition(checkedPosition, lengthPosition);

			//Очистка памяти
			free(checkedPosition);
			break;
		}

		default: {
			cout << "Повторите попытку ввода" << endl;
			break;
		}

		}
		puts("---------------------------------------------------------------------------------------");
	} while (choice != 0);

	system("pause");
	return 0;
}
