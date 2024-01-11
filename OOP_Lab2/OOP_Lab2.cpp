#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

void Add(char *str) 
{
    int index = 0; // счётчик символов 
    char element; // определение пременной для символа
    while ((element = getchar()) != '\n') // введенный элемент не равен символу перехода
    {
        if (index < 80) // заполнение массива символов при кол-ве элементов в нем меньше 80
        {
            str[index] = element; // добавление элемента в массив
            index++; // обновление счётчика для перехода к новому элементу 
        }
    }
    str[index] = '\0'; // последний элемент
}

int comp(const void* i, const void* j) // по возрастанию 
{
    return *(int*)i - *(int*)j; // преобразование указателей
}

struct Bear
{
    int _data;
    int _numer;
};

class Sentences
{
    char* name;
    FILE* fp;
    int* arrdata;
    int k;
    struct Bear structur[80];

public:
    Sentences()
    {
        name = (char*)malloc(81);
        Add(name);
        fp = fopen(name, "wt");
        Strok();
        Quantity();
    }


    ~Sentences() 
    {
        if (name != NULL)
        {
            free(name);
            name = NULL;
        }
        if (fp != NULL)
        {
            free(fp);
            fp = NULL;
        }
    }

    void Qsort() 
    {
        int comp(const void*, const void*); // прототип функции
        qsort((int*)arrdata, k, sizeof(int), comp);

        for (int i = 0; i < k; i++)
        {
            structur[i]._data = arrdata[i];
            structur[i]._numer = i + 1;
        }
    }

    void Print() 
    {
        for (int i = 0; i < k; i++)
        {
            printf("Номер_строки:%d | \t | Количество_различных_символов: %d | \n", structur[i]._numer, structur[i]._data);
        }
    }

private:
    void Strok() 
    {
        printf("Введите количество строк: ");
        int count = 0;
        scanf("%d", &count);
        cin.ignore(); // чистка буфера

        for (int i = 0; i < count; i++)
        {
            printf("%d: ", i + 1);
            char* strok = (char*)malloc(81);
            Add(strok);
            fprintf(fp, "%s\n", strok);
            free(strok);
        }

        fclose(fp);
    }

    void Quantity()
    {
        fp = fopen(name, "rt");
        arrdata = (int*)malloc(81);

        char* slenght = (char*)malloc(81);

        k = 0;
        int* index = &k;
        *index = 0;

        while (!feof(fp))
        {
            if (fgets(slenght, 81, fp) != NULL)
            {
                printf("%s  ", slenght);
                int data = strlen(slenght);

                arrdata[k] = data - 1;
                printf("%d\n", arrdata[k]);
                k++;
            }
        }
       
        char* word = (char*)malloc(81);

        for (int i = 0; i < k; i++)
        {
            structur[i]._data = arrdata[i];
            structur[i]._numer = i + 1;
        }

        fclose(fp);
    }
};


int main()
{   
    printf("Hallo world\n");
    system("chcp 1251"); // Использовать кириллицу для консольного ввода/вывода

    printf("Введите имя файла\n");
    Sentences s;
    s.Print();
    s.Qsort();
    printf("\nОтсортированный массив: \n");
    s.Print();  
    
    system("pause");//Задержать консоль на экране перед завершением программы
    return 0;
}
