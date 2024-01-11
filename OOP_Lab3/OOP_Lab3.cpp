#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

void Add(char* str)
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

string s_Add(char* str)
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
    return str;
}

struct Index
{
    int i_name;
    int i_post;
};

class Sentences
{
    char* name;
    FILE* fp;
    
public:
    Sentences() 
    {

    }
};


int main()
{
    system("chcp 1251");//Использовать кириллицу для консольного ввода/вывода

    FILE* fio;
    FILE* post;
    FILE* index;

    printf("Выберете режим:\n 1-Добавление новой фамилии с указание должности\n 2-Добавлени новой должности\n");
    printf(" 3-Вывод должности при вводе фамилии\n");

    int count = 0;
    int k = 0;
    scanf("%d", &k);
    cin.ignore();



    switch (k)
    {
    case 1: {

    
        fio = fopen("FIO.DAT.txt", "wt");

        printf("Введите количество лиц, кторые вы хотите добавить через пробел: ");        
        scanf("%d", &count);
        cin.ignore(); // чистка буфера

        for (int i = 0; i < count; i++)
        {
            printf("%d: ", i + 1);
            char* strok = (char*)malloc(81);
            Add(strok);
            fprintf(fio, "%s\n", strok);
            free(strok);
        }

        fclose(fio);

        post = fopen("DOLGH.DAT.txt", "wt");

        char* strok = (char*)malloc(81);
        Add(strok);

        for (int i = 0; i < count; i++)
        {
            printf("%d: ", i + 1);
            
            fprintf(post, "%s\n", strok);            
        }

        fclose(post);

        

        /*
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
        */

        //fclose();
        break; }

    case 2: {

        char* i_strok = (char*)malloc(81);
        char* i_slenght = (char*)malloc(81);

        for (int i = 0; i < 1; i++)
        {
            printf("%d: ", i + 1);
            char* strok = (char*)malloc(81);
            Add(strok);
            strncpy(i_strok, strok, strlen(strok));
            free(strok);
        }

        post = fopen("DOLGH.DAT.txt", "rt");

        while (!feof(post))
        {
            if (fgets(i_slenght, 81, post) != NULL)
            {
                int n = strcmp(i_slenght, i_strok);
                if (n == 0)
                {
                    printf("Строки равны");
                }
            }
        }

        fclose(post);

        post = fopen("DOLGH.DAT.txt", "wt");

        for (int i = 0; i < count; i++)
        {
            printf("%d: ", i + 1);
            char* strok = (char*)malloc(81);
            Add(strok);
            fprintf(post, "%s\n", strok);
            free(strok);
            system("pause");
        }

        fclose(post);
        system("pause");
    
        break; }
    case 3:
        break;
    }


    system("chcp 1251");//Использовать кириллицу для консольного ввода/вывода
    printf("Hallo world\n");
    system("pause");//Задержать консоль на экране перед завершением программы
    return 0;
}