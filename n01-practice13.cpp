#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define SIZE 6
int main(){
    setlocale(LC_ALL, "RUS");
    int a[SIZE][SIZE];
    int d[SIZE]; //минимальное расстояние
    int v[SIZE]; //посещенные вершины
    int temp, minindex, min;
    system("chcp 1251");
    system("cls");
    for (int i = 0; i < SIZE; i++) { //заполнение таблицы
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++) {
            printf("Введите расстояние %d - %d: ", i + 1, j + 1);
            scanf("%d", &temp);
            a[i][j] = temp;
            a[j][i] = temp;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { printf("%5d ", a[i][j]); }
        printf("\n");
    }

    for (int i = 0; i < SIZE; i++) { d[i] = 10000; v[i] = 1; }
    d[0] = 0;

    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++) { //вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min)) {
                min = d[i];
                minindex = i;
            }
        }
        
        if (minindex != 10000) { //прошлый путь до вершины + путь на этой итерации; если минимельный => новый минимальный
            for (int i = 0; i < SIZE; i++) {
                if (a[minindex][i] > 0) {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) { d[i] = temp; }
                }
            }
            v[minindex] = 0; //посетили
        }
    } while (minindex < 10000);

    printf("\nКратчайшие расстояния до вершин: \n");
    for (int i = 0; i < SIZE; i++)
        printf("%5d ", d[i]);

    int path[SIZE]; //с конца в начало
    int end = 4;
    path[0] = 5;
    int k = 1;
    int weight = d[end]; //длина пути до конечной вершины

    while (end != 0) { // пока не дошли до начальной вершины
        for (int i = 0; i < SIZE; i++) {
            if (a[i][end] != 0) {
                int temp = weight - a[i][end]; //длина пути до предыдущей вершины
                if (temp == d[i]) { //минимально?
                    weight = temp;
                    end = i;
                    path[k] = i + 1;
                    k++;
                }
            }
        }
    }

    printf("\nВывод кратчайшего пути\n");
    for (int i = k - 1; i >= 0; i--)
        printf("%5d ", path[i]);
    
    printf("\nПредставление графа в виде дерева\n");
    bool first = true;
    printf("\n|1|\n");
    int now[SIZE*SIZE] = { 1,0,0,0,0 };
    int next[SIZE*SIZE] = { 0,0,0,0,0 };
    int index = 0;
    for (int k = 0; k < SIZE - 1; k++) { //уровни дерева
        std::cout << "|";
        for (int i = 0; i < SIZE - 1; i++) { //переход по родителям
            if (now[i] != 0 && now[i] != 6) {
                for (int j = now[i]; j <= SIZE; j++) { //ветки от одного родителя
                    if (a[j-1][now[i]-1] != 0) {
                        if (first) { first = false; std::cout << j; }
                        else { std::cout << " " << j; }
                        next[index] = j;
                        index++;
                    }
                }
                std::cout << "|";
                first = true;
            }
            else if (now[i] == 6) {
                std::cout << " |";
            }
        }
        std::cout << std::endl;
        index = 0;
        for (int q = 0; q < SIZE - 1; q++) { now[q] = next[q]; next[q] = 0; }
    }
    return 0;
}

/*
2
4
5
0
0
0
4
3
0
0
0
7
6
4
2
*/