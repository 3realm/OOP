#pragma once
#include <list>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
class Base
{
private:
	typedef struct 
	{
		unsigned code; // шифр датчика
		string name; // имя датчика
	} sensor;

	typedef struct 
	{
		unsigned code; // шифр подсистемы
		string name; // имя подсистемы
	} subsystem;

	typedef struct 
	{
		sensor* sensor_idx; // индекс датчика - указатель
		unsigned subsys_idx; // индекс подсистемы - порядковый номер в списке подсистем
	} link;

	list<sensor*> list_sens;	// список датчиков
	list<subsystem*> list_subsys; // список подсистем
	list<link*> list_links; // список связей между датчиками и подсистемами


	// получение индекса датчика по его шифру
	sensor* getSensonrIndex(unsigned sensor_code) 
	{
		for (sensor*& sensor : list_sens) 
		{						// в цикле по списку датчиков
			if (sensor->code == sensor_code) return sensor;		// если найден датчик с нужным шифром - возвращаем его
		}
		return NULL;												// цикл прошел, а датчика так и не нашли, то вернули NULL
	}

	// получение индекса подсистемы по ее шифру
	int getSubsystemIndex(unsigned subsystem_code) 
	{
		int i = 0;
		for (subsystem*& subsystem : list_subsys) 
		{				
			// в цикле по списку подсистем
			if (subsystem->code == subsystem_code) return i;	
			// возвращаем не указатель, а его номер в списке
			i++;
		}
		return -1;
	}

	// получение связки по индексу датчика
	link* getLink(sensor* sensor) 
	{
		for (link*& link : list_links) 
		{
			if (link->sensor_idx == sensor) return link;			// ищем не по шифру, а по "индексу" датчика
		}
		return NULL;
	}

	// получение связки по индексу подсистемы
	link* getLink(unsigned subsystem_idx) 
	{
		for (link*& link : list_links) 
		{
			if (link->subsys_idx == subsystem_idx) return link;		// сравниваем индекс подсистемы с текущим в связке
		}
		return NULL;
	}


public:
	~Base() 
	{
		for (sensor*& sensor : list_sens) delete sensor;				// проходим в цикле по списку датчиков и удаляем каждый
		for (subsystem*& subsystem : list_subsys) delete subsystem;
		for (link*& link : list_links) delete link;
	}
	// статический метод ввода шифра с указанием размерности
	static unsigned inputCode(char code_length) {
		string res;
		cin >> res;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		char err_message[256];
		sprintf_s(err_message, "Вводимое значение должно быть %d-значным целым числом", code_length); 
		// сохраняет последовательнось символов и значений
		if (res.length() != code_length || res[0] == '0') throw err_message;
		// если длина шифра не равна нужной, сразу выдаём ошибку
		unsigned long tmp;
		try 
		{
			tmp = stoul(res);										// пробуем получить из введенной строки число
		}
		catch (invalid_argument) 
		{
			cout << "Ошибка" << endl;
			// throw err_message;										// если не получилось, значит это не число, ошибка
		}
		return tmp;
	}


	// добавление датчика
	void addSensor(unsigned sensor_code, string sensor_name) {
		if (getSensonrIndex(sensor_code)) throw "Датчик с таким шифром уже имеется в базе"; // проверяем, нет ли уже такого
		sensor* sensor_ptr = new sensor;							// выделяем память под новый датчик
		sensor_ptr->code = sensor_code;							// присваиваем ему введенный шифр
		sensor_ptr->name = sensor_name;
		list_sens.push_back(sensor_ptr);							// добавляем датчик в список list
	}

	// добавление подсистемы
	void addSubsys(unsigned subsystem_code, string subsystem_name) {
		if (getSubsystemIndex(subsystem_code) > -1) throw "Подсистема с таким шифром уже есть в базе";
		subsystem* subsystem_ptr = new subsystem;
		subsystem_ptr->code = subsystem_code;
		subsystem_ptr->name = subsystem_name;
		list_subsys.push_back(subsystem_ptr);
	}

	//привязка датчика к подсистеме
	void Bind(unsigned sensor_code, unsigned subsystem_code) {
		sensor* sensor_ptr = getSensonrIndex(sensor_code);				// получаем указатель на датчик по шифру
		if (sensor_ptr == NULL) throw "Нет датчика с таким шифром";			// если вернуло null, то выкидываем исключение
		if (getLink(sensor_ptr)) throw "Датчик уже привязан к подсистеме"; // проверяем, не включен ли датчик уже куда-то
		int subsystem_idx = getSubsystemIndex(subsystem_code);			// получаем индекс подсистемы по шифру
		if (subsystem_idx == -1) throw "Нет подсистемы с таким шифром";		// если вернуло -1, то кидаем исключение - нет такой
		link* link_ptr = new link;										// создаем запись типа link (связь м/у датч. и подсист.)
		link_ptr->sensor_idx = sensor_ptr;								// записываем в нее указатель на датчик (индекс датчика)
		link_ptr->subsys_idx = subsystem_idx;							// и указатель подсистемы (индекс подсистемы)
		list_links.push_back(link_ptr);									// запись добавляем в список связок
	}

	//отвязка датчика от подсистем
	void unBind(unsigned sensor_code) {
		sensor* sensor_ptr = getSensonrIndex(sensor_code);		// получаем указатель на датчик по шифру
		if (!getLink(sensor_ptr)) throw "Датчик не привязан ни к одной подсистеме"; // проверяем, включен ли в подсистему
		for (list<link*>::iterator it = list_links.begin(), end = list_links.end(); it != end; it++) { // итерируясь в цикле по списку
			if ((*it)->sensor_idx == sensor_ptr) {					// если у текущей "связки" индекс датчика равен нужному,
				list_links.erase(it);								// удаляем связку - теперь датчик отвязан от подсистемы
				return;												// останавливаемся, чтобы не перебирать зря остальные
			}
	}

	// удаление подсистемы
	void deleteSubsys(unsigned subsystem_code) {
		int subsystem_idx = getSubsystemIndex(subsystem_code);	// получаем индекс подсистемы по шифру
		if (subsystem_idx == -1) throw "Нет подсистемы с таким шифром";	// если не найдена, сообщаем об этом 
		for (list<link*>::iterator it = list_links.begin(), end = list_links.end(); it != end;) { // итерируясь по списку "связок"
			if ((*it)->subsys_idx == subsystem_idx) {				// проверяем, если у связки нужный индекс подсистемы
				list<link*>::iterator next_it = next(it);			// получаем ссылку на следующий эл-т списка (итератор)
				list_links.erase(it);								// удаляем связку (отвязываем датчик)
				it = next_it;										// присваиваем ее переменной цикла (переход к следующему)
			}
			else {
				it++;												// иначе - просто переходим к следующему итератору
				if ((*it)->subsys_idx > subsystem_idx) {			// для инд.записей с большими индексами подсистем
					(*it)->subsys_idx--;							// уменьшаем индекс подсистемы,
				}													// т.к. удалили одну подсистему - уменьшился номер у следующих
			}
			//удаляем записи потому что итератор идёт дальше даже после удаления записи, а не останавливается.
		}
		int i = 0;
		for (list<subsystem*>::iterator it = list_subsys.begin(), end = list_subsys.end(); it != end; it++, i++) {
			if ((*it)->code == subsystem_code) {				// так же проходим по списку подсистем, если нашли нужную
				list_subsys.erase(it);							// то удаляем ее
				break;												// и останавливаем цикл
			}
		}
	}

	// удаление всех неиспользуемых датчиков
	void deleteUnused() {
		for (list<sensor*>::iterator it = list_sens.begin(), end = list_sens.end(); it != end;) { //проходим в цикле по датчикам
			sensor* sensor_ptr = *it;								// получаем указатель на текущий датчик
			if (!getLink(sensor_ptr)) {							// если он не привязан ни к какой подсистеме то удаляем
				list<sensor*>::iterator next_it = next(it);			// и получаем ссылку на следующий итератор
				list_sens.erase(it);								// удаляем датчик
				it = next_it;										// переходим к следующему
			}
			else it++;												// иначе - просто переходим к следующему
		}
	}

	// вывод подсистем, к которым не привязаны датчики
	void printSubsysNoSens() {
		int num_output = 0;											// счетчик количества выводимых подсистем
		unsigned idx = 0;											// переменная для индекса (номера) очередной подсистемы
		for (subsystem*& subsys : list_subsys) 
		{				// проходим по списку подсистем
			if (!getLink(idx)) 
			{									// если не нашли индексную запись(связку) для подсистемы
				cout << subsys->name << endl;						// то датчиков у нее нет, выводим название
				num_output++;										// увеличили счетчик
			}
			idx++;													// увеличили номер, переходим к следующей
		}
		if (!num_output)
			cout << "Нет таких подсистем" << endl;
	}

	// вывод списка датчиков
	void printSensors() 
	{
		if (list_sens.begin() != list_sens.end()) 
		{			// если список датчиков не пуст
			cout << "Датчики:" << endl;
			cout << left << setw(20) << "Шифр" << setw(40) << "Название" << endl;
			for (sensor*& sensor_ptr : list_sens) 
			{				// в цикле по списку
				cout << left << setw(20) << sensor_ptr->code << setw(40) << sensor_ptr->name << endl; // выводим датчики
			}
			cout << endl;
		}
	}

	// вывод списка подсистем
	void printSubsys() 
	{
		if (list_subsys.begin() != list_subsys.end()) 
		{
			cout << "Подсистемы:" << endl;
			cout << left << setw(20) << "Шифр" << setw(40) << "Название" << endl;
			for (subsystem*& subsystem_ptr : list_subsys) 
			{
				cout << left << setw(20) << subsystem_ptr->code << setw(40) << subsystem_ptr->name << endl;
			}
			cout << endl;
		}
	}


};
