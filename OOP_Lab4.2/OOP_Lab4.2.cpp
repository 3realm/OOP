
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <Windows.h>
#include "Base.h"
#include <iostream>

int main() try
{
	SetConsoleCP(1251);				// Кодировка windows-1251 на ввод
	SetConsoleOutputCP(1251);		// Кодировка windows-1251 на вывод
	setlocale(LC_ALL, "");			// Правка локали

	Base db;

	char item;
	do {
		system("cls");
		db.printSensors();
		db.printSubsys();

		cout << " " << endl;
		cout << "0 - выход" << endl;
		cout << "1 - добавление подсистемы" << endl;
		cout << "2 - добавление датчика" << endl;
		cout << "3 - включение датчика в подсистему" << endl;
		cout << "4 - исключение датчика из подсистемы" << endl;
		cout << "5 - удаление подсистемы" << endl;
		cout << "6 - удаление неиспользуемых датчиков" << endl;
		cout << "7 - вывод всех подсистем, не содержащих датчики" << endl;
		try {
			if (!(cin >> item)) {
				throw "Пункт меню должен быть задан символом";
				cin.clear(); // очищение флагов, чтобы будущие операции ввода-вывода работали правильно
				cin.ignore(cin.rdbuf()->in_avail()); //очистка данных, функция rdbuf возвращет буфер, а in_avail - количество байт в нем.
			}
			switch (item) {
			case '1': 
			{
				cout << "Введите шифр подсистемы: ";
				unsigned cipher = Base::inputCode(2);
				cout << "Введите название подсистемы: ";
				string name;
				getline(cin, name); // ввод данных из потока
				db.addSubsys(cipher, name);
				break;
			}
			case '2': 
			{
				cout << "Введите шифр датчика: ";
				unsigned cipher = Base::inputCode(3);
				cout << "Введите название датчика: ";
				string name;
				getline(cin, name);
				db.addSensor(cipher, name);
				break;
			}
			case '3': 
			{
				cout << "Введите шифр подсистемы: ";
				unsigned subsys_cipher = Base::inputCode(2);
				cout << "Введите шифр датчика: ";
				unsigned sensor_cipher = Base::inputCode(3);
				db.Bind(sensor_cipher, subsys_cipher);
				cout << "Подсистема создана" << endl;
				break;
			}
			case '4': 
			{
				cout << "Введите шифр датчика: ";
				unsigned sensor_cipher = Base::inputCode(3);
				db.unBind(sensor_cipher);
				cout << "Датчик создан" << endl;
				break;
			}
			case '5': 
			{
				cout << "Введите шифр подсистемы: ";
				unsigned subsys_cipher = Base::inputCode(2);
				db.deleteSubsys(subsys_cipher);
				cout << "Подсистема удалена" << endl;
				break;
			}
			case '6': {
				db.deleteUnused();
				cout << "Неиспользуемые датчики удалены" << endl;
				break;
			}
			case '7': {
				cout << "Результат: " << endl;
				db.printSubsysNoSens();
				break;
			}
			}
		}
		catch (const char* except) {
			cout << "Ошибка: " << except << endl;
		}

		cout << endl;
		system("pause");
	} while (item != '0');
	return 0;
}
catch (...) {
	cout << "Ошибка!" << endl;
}

