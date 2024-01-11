#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>;
using namespace std;

class Sentence 
{
private:
    // предложение
    char** sent;
    int count; 
    char* str;
public:
    Sentence(char** oldsent, int counter) 
    {
        count = counter;
        //
        sent = (char**)malloc(count* sizeof(char**)); // создали память на новое предложение
        for (int i = 0; i < count; i++)
        {
            sent[i] = (char*)malloc(sizeof(char*) * strlen(oldsent[i]));
            strcpy(sent[i], oldsent[i]);
        }
    }


    Sentence() 
    {
        int index = 0; // счётчик символов 
        str = (char*)malloc(81); // выделение памяти для строки на 80 символов
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
        Divvvvv();
    };
    
    char** Copy() 
    {
        char** _sent = (char**)malloc(sizeof(char**) * count);
        for (int i = 0; i < count; i++)
        {
            _sent[i] = (char*)malloc(sizeof(char*) * strlen(sent[i]));
            strcpy(_sent[i], sent[i]);
        }
        return _sent;
    }    

    Sentence Sort() 
    {
        char** tempsent = Copy();

        for (int j = count - 1; j > 0; j--)
            for (int i = 0; i < j; i++)
                // сравнение строк
                if (strcmp(&tempsent[i][0], &tempsent[i+1][0]) < 0)
                {
                    char* flag = tempsent[i];
                    tempsent[i] = tempsent[i + 1];
                    tempsent[i + 1] = flag;
                }
        Sentence newSent(tempsent, count);
        return newSent;
    }

    void Print() 
    {
        for (int i = 0; i < count; i++)
        {
            printf("%s ", sent[i]);
        }
    }


private: 
    void Divvvvv()
    {
        sent = (char**)malloc(sizeof(char**) * 81);
        char* word = strtok(str, " ");
        int i = 0;
        while (word != NULL)
        {
            sent[i] = word;
            word = strtok(NULL, " "); //разделяем предложение на оставшиеся лексемы

            i++;
            count++;
        }
        sent = (char**)realloc(sent, sizeof(char**) * count);
    }
};

int main()
{
    system("chcp 1251");//Использовать кириллицу для консольного ввода/вывода

    Sentence s1;
    printf("1ое исходное предложение:\n");
    s1.Print();
    Sentence s2 = s1.Sort();
    printf("\n2ое исходное предложение:\n");
    s2.Print();   

    system("pause"); //Задержать консоль на экране перед завершением программы
    return 0;
}
