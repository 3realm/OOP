#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
class Database
{
private:
	FILE* lastNameStream; // ����� � ����� � ��������� FIO.DAT
	FILE* postStream; // ����� � ����� � ����������� DOLGH.DAT
	FILE* linkStream; // ����� � ����� �� �������� LINK.IDX
	struct Worker
	{
		unsigned long lastname_idx; // ������ ������� � ����� FIO.DAT;
		unsigned long post_idx;     // ������ ��������� � ����� DOLGH.DAT
	};

public:
	void AddLastname(char* lastname, char* post)  // ���������� ������� � ���������� � L
	{
		int postPosition;
		// ��������
		bool postExist = ChekingRecExist(postStream, post, postPosition);
		if (!postExist) {
			puts("\n��������� ��������� �� ����������, ������� �������� � � ����.");
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

	void AddPost(char* post) // ���������� ��������� 
	{
		if (strchr(post, '\n') == NULL)
			strcat(post, "\n");

		int postPos;
		bool postExist = ChekingRecExist(postStream, post, postPos);

		if (postExist)
		{
			puts("\n����� ��������� ��� ����������.");
			return;
		}

		fputs(post, postStream);
	}

	// ����� ��������� �� ��������� �������
	void PrintPostByLastname(char* lastname) 
	{
		int lastnamePosition;
		bool postExist = ChekingRecExist(lastNameStream, lastname, lastnamePosition);

		if (!postExist) 
		{
			puts("\n��������� ������� �� ����������, ������� �������� � � ����.");
			return;
		}

		fseek(linkStream, 0, SEEK_SET);

		Worker worker;

		int i = 0;
		// ��������� , ��� ����� ���� ������ worker �������� Worker
		// ������
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
		// �������� ��� �������� ��������� �����
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
	// ���������� ���� �� � ����� ������ � �������� �������� ��� ����������
	// ���������� ������ � ������� ��� ��������� � ����� 
	bool ChekingRecExist(FILE* filestream, char* record, int& position)
	{
		fseek(filestream, 0, SEEK_SET);
		// ����� ���������
		if (strchr(record, '\n') == 0)
			strcat(record, "\n");

		int currentPos = 0;

		while (true)
		{
			currentPos = ftell(filestream);
			// BUFSIZ � ������ ������� �����������
			char* reading = fgets((char*)malloc(sizeof(char) * BUFSIZ), BUFSIZ - 1, filestream);
			//���� ����� �����, �� ������ �� �����
			if (feof(filestream)) 
				break;

			// ��������� �����
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
