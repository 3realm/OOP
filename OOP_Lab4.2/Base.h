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
		unsigned code; // ���� �������
		string name; // ��� �������
	} sensor;

	typedef struct 
	{
		unsigned code; // ���� ����������
		string name; // ��� ����������
	} subsystem;

	typedef struct 
	{
		sensor* sensor_idx; // ������ ������� - ���������
		unsigned subsys_idx; // ������ ���������� - ���������� ����� � ������ ���������
	} link;

	list<sensor*> list_sens;	// ������ ��������
	list<subsystem*> list_subsys; // ������ ���������
	list<link*> list_links; // ������ ������ ����� ��������� � ������������


	// ��������� ������� ������� �� ��� �����
	sensor* getSensonrIndex(unsigned sensor_code) 
	{
		for (sensor*& sensor : list_sens) 
		{						// � ����� �� ������ ��������
			if (sensor->code == sensor_code) return sensor;		// ���� ������ ������ � ������ ������ - ���������� ���
		}
		return NULL;												// ���� ������, � ������� ��� � �� �����, �� ������� NULL
	}

	// ��������� ������� ���������� �� �� �����
	int getSubsystemIndex(unsigned subsystem_code) 
	{
		int i = 0;
		for (subsystem*& subsystem : list_subsys) 
		{				
			// � ����� �� ������ ���������
			if (subsystem->code == subsystem_code) return i;	
			// ���������� �� ���������, � ��� ����� � ������
			i++;
		}
		return -1;
	}

	// ��������� ������ �� ������� �������
	link* getLink(sensor* sensor) 
	{
		for (link*& link : list_links) 
		{
			if (link->sensor_idx == sensor) return link;			// ���� �� �� �����, � �� "�������" �������
		}
		return NULL;
	}

	// ��������� ������ �� ������� ����������
	link* getLink(unsigned subsystem_idx) 
	{
		for (link*& link : list_links) 
		{
			if (link->subsys_idx == subsystem_idx) return link;		// ���������� ������ ���������� � ������� � ������
		}
		return NULL;
	}


public:
	~Base() 
	{
		for (sensor*& sensor : list_sens) delete sensor;				// �������� � ����� �� ������ �������� � ������� ������
		for (subsystem*& subsystem : list_subsys) delete subsystem;
		for (link*& link : list_links) delete link;
	}
	// ����������� ����� ����� ����� � ��������� �����������
	static unsigned inputCode(char code_length) {
		string res;
		cin >> res;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		char err_message[256];
		sprintf_s(err_message, "�������� �������� ������ ���� %d-������� ����� ������", code_length); 
		// ��������� ����������������� �������� � ��������
		if (res.length() != code_length || res[0] == '0') throw err_message;
		// ���� ����� ����� �� ����� ������, ����� ����� ������
		unsigned long tmp;
		try 
		{
			tmp = stoul(res);										// ������� �������� �� ��������� ������ �����
		}
		catch (invalid_argument) 
		{
			cout << "������" << endl;
			// throw err_message;										// ���� �� ����������, ������ ��� �� �����, ������
		}
		return tmp;
	}


	// ���������� �������
	void addSensor(unsigned sensor_code, string sensor_name) {
		if (getSensonrIndex(sensor_code)) throw "������ � ����� ������ ��� ������� � ����"; // ���������, ��� �� ��� ������
		sensor* sensor_ptr = new sensor;							// �������� ������ ��� ����� ������
		sensor_ptr->code = sensor_code;							// ����������� ��� ��������� ����
		sensor_ptr->name = sensor_name;
		list_sens.push_back(sensor_ptr);							// ��������� ������ � ������ list
	}

	// ���������� ����������
	void addSubsys(unsigned subsystem_code, string subsystem_name) {
		if (getSubsystemIndex(subsystem_code) > -1) throw "���������� � ����� ������ ��� ���� � ����";
		subsystem* subsystem_ptr = new subsystem;
		subsystem_ptr->code = subsystem_code;
		subsystem_ptr->name = subsystem_name;
		list_subsys.push_back(subsystem_ptr);
	}

	//�������� ������� � ����������
	void Bind(unsigned sensor_code, unsigned subsystem_code) {
		sensor* sensor_ptr = getSensonrIndex(sensor_code);				// �������� ��������� �� ������ �� �����
		if (sensor_ptr == NULL) throw "��� ������� � ����� ������";			// ���� ������� null, �� ���������� ����������
		if (getLink(sensor_ptr)) throw "������ ��� �������� � ����������"; // ���������, �� ������� �� ������ ��� ����-��
		int subsystem_idx = getSubsystemIndex(subsystem_code);			// �������� ������ ���������� �� �����
		if (subsystem_idx == -1) throw "��� ���������� � ����� ������";		// ���� ������� -1, �� ������ ���������� - ��� �����
		link* link_ptr = new link;										// ������� ������ ���� link (����� �/� ����. � �������.)
		link_ptr->sensor_idx = sensor_ptr;								// ���������� � ��� ��������� �� ������ (������ �������)
		link_ptr->subsys_idx = subsystem_idx;							// � ��������� ���������� (������ ����������)
		list_links.push_back(link_ptr);									// ������ ��������� � ������ ������
	}

	//������� ������� �� ���������
	void unBind(unsigned sensor_code) {
		sensor* sensor_ptr = getSensonrIndex(sensor_code);		// �������� ��������� �� ������ �� �����
		if (!getLink(sensor_ptr)) throw "������ �� �������� �� � ����� ����������"; // ���������, ������� �� � ����������
		for (list<link*>::iterator it = list_links.begin(), end = list_links.end(); it != end; it++) { // ���������� � ����� �� ������
			if ((*it)->sensor_idx == sensor_ptr) {					// ���� � ������� "������" ������ ������� ����� �������,
				list_links.erase(it);								// ������� ������ - ������ ������ ������� �� ����������
				return;												// ���������������, ����� �� ���������� ��� ���������
			}
	}

	// �������� ����������
	void deleteSubsys(unsigned subsystem_code) {
		int subsystem_idx = getSubsystemIndex(subsystem_code);	// �������� ������ ���������� �� �����
		if (subsystem_idx == -1) throw "��� ���������� � ����� ������";	// ���� �� �������, �������� �� ���� 
		for (list<link*>::iterator it = list_links.begin(), end = list_links.end(); it != end;) { // ���������� �� ������ "������"
			if ((*it)->subsys_idx == subsystem_idx) {				// ���������, ���� � ������ ������ ������ ����������
				list<link*>::iterator next_it = next(it);			// �������� ������ �� ��������� ��-� ������ (��������)
				list_links.erase(it);								// ������� ������ (���������� ������)
				it = next_it;										// ����������� �� ���������� ����� (������� � ����������)
			}
			else {
				it++;												// ����� - ������ ��������� � ���������� ���������
				if ((*it)->subsys_idx > subsystem_idx) {			// ��� ���.������� � �������� ��������� ���������
					(*it)->subsys_idx--;							// ��������� ������ ����������,
				}													// �.�. ������� ���� ���������� - ���������� ����� � ���������
			}
			//������� ������ ������ ��� �������� ��� ������ ���� ����� �������� ������, � �� ���������������.
		}
		int i = 0;
		for (list<subsystem*>::iterator it = list_subsys.begin(), end = list_subsys.end(); it != end; it++, i++) {
			if ((*it)->code == subsystem_code) {				// ��� �� �������� �� ������ ���������, ���� ����� ������
				list_subsys.erase(it);							// �� ������� ��
				break;												// � ������������� ����
			}
		}
	}

	// �������� ���� �������������� ��������
	void deleteUnused() {
		for (list<sensor*>::iterator it = list_sens.begin(), end = list_sens.end(); it != end;) { //�������� � ����� �� ��������
			sensor* sensor_ptr = *it;								// �������� ��������� �� ������� ������
			if (!getLink(sensor_ptr)) {							// ���� �� �� �������� �� � ����� ���������� �� �������
				list<sensor*>::iterator next_it = next(it);			// � �������� ������ �� ��������� ��������
				list_sens.erase(it);								// ������� ������
				it = next_it;										// ��������� � ����������
			}
			else it++;												// ����� - ������ ��������� � ����������
		}
	}

	// ����� ���������, � ������� �� ��������� �������
	void printSubsysNoSens() {
		int num_output = 0;											// ������� ���������� ��������� ���������
		unsigned idx = 0;											// ���������� ��� ������� (������) ��������� ����������
		for (subsystem*& subsys : list_subsys) 
		{				// �������� �� ������ ���������
			if (!getLink(idx)) 
			{									// ���� �� ����� ��������� ������(������) ��� ����������
				cout << subsys->name << endl;						// �� �������� � ��� ���, ������� ��������
				num_output++;										// ��������� �������
			}
			idx++;													// ��������� �����, ��������� � ���������
		}
		if (!num_output)
			cout << "��� ����� ���������" << endl;
	}

	// ����� ������ ��������
	void printSensors() 
	{
		if (list_sens.begin() != list_sens.end()) 
		{			// ���� ������ �������� �� ����
			cout << "�������:" << endl;
			cout << left << setw(20) << "����" << setw(40) << "��������" << endl;
			for (sensor*& sensor_ptr : list_sens) 
			{				// � ����� �� ������
				cout << left << setw(20) << sensor_ptr->code << setw(40) << sensor_ptr->name << endl; // ������� �������
			}
			cout << endl;
		}
	}

	// ����� ������ ���������
	void printSubsys() 
	{
		if (list_subsys.begin() != list_subsys.end()) 
		{
			cout << "����������:" << endl;
			cout << left << setw(20) << "����" << setw(40) << "��������" << endl;
			for (subsystem*& subsystem_ptr : list_subsys) 
			{
				cout << left << setw(20) << subsystem_ptr->code << setw(40) << subsystem_ptr->name << endl;
			}
			cout << endl;
		}
	}


};
