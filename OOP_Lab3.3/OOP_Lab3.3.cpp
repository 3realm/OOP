#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <Windows.h>
#include "Database.h"

int main()
{
	printf("Hallo world\n");
	system("chcp 1251"); // Использовать кириллицу для консольного ввода/вывода

	Database database;

	char buffer_lastname[BUFSIZ];
	char buffer_post[BUFSIZ];
	char menu;

	do {
		system("cls");
		puts("Меню:");
		puts("0 - Выход");
		puts("1 - Добавить новую фамилию с указанием должности");
		puts("2 - Добавить должность");
		puts("3 - Вывести должность по фамилии");

		menu = getchar();
		// устанавливает внутренний указатель положения файла в начальное положение
		rewind(stdin);	

		putchar('\n');

		switch (menu) 
		{
			case '1': 
			{
				puts("Введите новую фамилию: ");
				gets_s(buffer_lastname);
				puts("Введите существующую должность: ");
				gets_s(buffer_post);
				database.AddLastname(buffer_lastname, buffer_post);
				break;
			}
			case '2': 
			{
				puts("Введите новую должность: ");
				gets_s(buffer_lastname);
				database.AddPost(buffer_lastname);
				break;
			}
			case '3': 
			{
				puts("Введите фамилию: ");
				gets_s(buffer_lastname);
				puts("\nДолжность :");
				database.PrintPostByLastname(buffer_lastname);
				break;
			}
		}
		putchar('\n');
		system("pause");

	} while (menu != '0');

	return 0;
}
