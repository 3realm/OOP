#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
class Database
{
private:
	FILE* lastNameStream; // поток к файлу с фамили€ми FIO.DAT
	FILE* postStream; // поток к файлу с должност€ми DOLGH.DAT
	FILE* linkStream; // поток к файлу со св€зками LINK.IDX
	struct Worker
	{
		unsigned long lastname_idx; // индекс фамилии в файле FIO.DAT;
		unsigned long post_idx;     // индекс должности в файле DOLGH.DAT
	};

public:
	void AddLastname(char* lastname, char* post)  // добавление фамилии и св€зывание с L
	{
		int postPosition;
		// проверка
		bool postExist = ChekingRecExist(postStream, post, postPosition);
		if (!postExist) {
			puts("\n”казанной должности не существует, сначала добавьте еЄ в базу.");
			return;
		}
		if (strchr(lastname, '\n') == 0)
			strcat(lastname, "\n");

		int lastname_index;
		fputs(lastname, lastNameStream);

		ChekingRecExist(lastNameStream, lastname, lastname_index);

		Worker worker;
		worker.lastname_idx = lastname_index;
		worker.post_idx = postPosition;

		fwrite(&worker, sizeof(worker), 1, linkStream);
	}

	void AddPost(char* post) // добавление должности 
	{
		if (strchr(post, '\n') == NULL)
			strcat(post, "\n");

		int postPos;
		bool postExist = ChekingRecExist(postStream, post, postPos);

		if (postExist)
		{
			puts("\n“ака€ должность уже существует.");
			return;
		}

		fputs(post, postStream);
	}

	// вывод должности по указанной фамилии
	void PrintPostByLastname(char* lastname) 
	{
		int lastnamePosition;
		bool postExist = ChekingRecExist(lastNameStream, lastname, lastnamePosition);

		if (!postExist) 
		{
			puts("\n”казанной фамилии не существует, сначала добавьте еЄ в базу.");
			return;
		}

		fseek(linkStream, 0, SEEK_SET);

		Worker worker;

		int i = 0;
		// проверить , что будеи если вместо worker вставить Worker
		// чтение
		while (fread(&worker, sizeof(worker), 1, linkStream)) 
		{
			if (worker.lastname_idx == lastnamePosition) 
			{
				fseek(postStream, worker.post_idx, SEEK_SET);
				char* reading = fgets((char*)malloc(sizeof(char) * BUFSIZ), BUFSIZ - 1, postStream);
				puts(reading);
				++i;
			}
		}
	}

	Database()
	{
		// создание или рткрытие бинарного файла
		lastNameStream = fopen("FIO.DAT", "a+b");
		postStream = fopen("DOLGH.DAT", "a+b");
		linkStream = fopen("LINK.IDX", "a+b");
	}

	~Database()
	{
		fclose(lastNameStream);
		fclose(postStream);
		fclose(linkStream);
	}

private:
	// показывает есть ли в файле строка с заданной фамилией или должностью
	// возвращает индекс в фамилии или должности в файле 
	bool ChekingRecExist(FILE* filestream, char* record, int& position)
	{
		fseek(filestream, 0, SEEK_SET);
		// поиск вхождени€
		if (strchr(record, '\n') == 0)
			strcat(record, "\n");

		int currentPos = 0;

		while (true)
		{
			currentPos = ftell(filestream);
			// BUFSIZ Ц размер массива буферизации
			char* reading = fgets((char*)malloc(sizeof(char) * BUFSIZ), BUFSIZ - 1, filestream);
			//если конец файла, то выйдем из цикла
			if (feof(filestream)) 
				break;

			// сравнение строк
			int res = _stricmp(record, reading);

			if (res == 0) 
			{
				position = currentPos;
				return true;
			}
		}
		return false;
	}
};
