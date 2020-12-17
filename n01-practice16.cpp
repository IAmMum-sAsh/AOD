#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

const int nm = 5;

int a[nm][nm];

int n;

void makebase(int ik, int jk) {	// сокращение таблицы
	int i, j;
	for (i = 0; i < n; i++) if (a[i][jk] >= 0) { a[i][jk] = -1; }
	for (j = 0; j < n; j++) if (a[ik][j] >= 0) { a[ik][j] = -1; }
	a[ik][jk] = -2;
	if (a[jk][ik] >= 0) { a[jk][ik] = -1; }
}

int main() {
	setlocale(LC_ALL, "RUS");
	int i, j, c, i2, j2, i3, j3;
	int cnt;
	int minv, miniv, minjv, maxv;
	int flag;

	// ввод
	cout << "Введите кол-во городов: ";
	cin >> n;
	cout << "Введите полную таблицу расстояний между городами [диагональные элементы вводятся, например, нулями]" << endl << "Можно построчно через пробел" << endl;
	for (i = 0; i < n; i++) for (j = 0; j < n; j++) { cin >> a[i][j]; }
	for (i = 0; i < n; i++) { a[i][i] = -1; }

	for (c = 0; c < n; c++) {
		// проверка на последний цикл
		flag = 0;
		for (i = 0; (i < n) && (flag == 0); i++) {
			cnt = 0;
			for (j = 0; j < n; j++) {
				if (a[i][j] >= 0) {
					i2 = i;
					j2 = j;
					cnt++;
				}
			}
			if (cnt == 1) { flag = 1; }
		}
		for (j = 0; (j < n) && (flag == 0); j++) {
			cnt = 0;
			for (i = 0; i < n; i++) {
				if (a[i][j] >= 0) {
					i2 = i;
					j2 = j;
					cnt++;
				}
			}
			if (cnt == 1) { flag = 1; }
		}
		if (flag == 1) {
			makebase(i2, j2);
			continue;
		}

		// вычет минимального
		for (i = 0; i < n; i++) {
			minv = 30000;
			for (j = 0; j < n; j++) {
				if ((a[i][j] >= 0) && (a[i][j] < minv)) minv = a[i][j];
			}
			for (j = 0; j < n; j++) if (a[i][j] >= 0) { a[i][j] -= minv; }
		}
		for (j = 0; j < n; j++) {
			minv = 30000;
			for (i = 0; i < n; i++) {
				if ((a[i][j] >= 0) && (a[i][j] < minv)) { minv = a[i][j]; }
			}
			for (i = 0; i < n; i++) if (a[i][j] >= 0) { a[i][j] -= minv; }
		}

		// сравнение и определение точки пересчёта
		maxv = -1;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (a[i][j] == 0) {
					miniv = 30000;
					minjv = 30000;
					for (i2 = 0; i2 < n; i2++) {
						if ((a[i2][j] >= 0) && (i2 != i) && (a[i2][j] < miniv)) { miniv = a[i2][j]; }
					}
					for (j2 = 0; j2 < n; j2++) {
						if ((a[i][j2] >= 0) && (j2 != j) && (a[i][j2] < minjv)) { minjv = a[i][j2]; }
					}
					if (miniv + minjv > maxv) {
						maxv = miniv + minjv;
						i3 = i;
						j3 = j;
					}
				}
			}
		}
		makebase(i3, j3);
	}

	// вывод
	i2 = 0;
	cout << endl << i2 + 1;
	for (c = 0; c < n; c++) {
		for (j = 0; j < n; j++) {
			if (a[i2][j] == -2) {
				cout << "->" << j + 1;
				i2 = j;
				break;
			}
		}
	}
}

/*
	5
	0 90 80 40 100
	60 0 40 50 70
	50 30 0 60 20
	10 70 20 0 50
	20 40 50 20 0

	1->4->3->5->2->1
*/