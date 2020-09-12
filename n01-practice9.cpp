#include <iostream>
#include <vector>
#include <string>
using namespace std;

class vec_queue {
private:
	struct inf {
		string kat;
		int ns;
		int time;
	};

	vector<inf> q;
	int maxsize;

public:
	vec_queue(int size) { maxsize = size; };

	void insert(string kat, int ns, int time) {
		inf x = { kat, ns, time };
		q.push_back(x);
	}

	void del(int n) { q.erase(q.begin() + n); }

	string toString(int n) {
		string s2 = to_string(this->q[n].ns);
		string s3 = to_string(this->q[n].time);
		return ((this->q[n].kat + " №" + s2 + ": " + s3 + " мин"));
	}

	bool isempty() { return q.empty(); }

	bool isfull() { if (q.size() == maxsize) { return true; } else { return false; } }

	string getkat(int n) { return this->q[n].kat; }

	int getns(int n) { return this->q[n].ns; }

	int gettime(int n) { return this->q[n].time; }
};

class list_queue {
protected:
	list_queue* next;
	string zn;
	int num;
	int maxsize;

public:
	list_queue(string zn, int num, int maxsize) {
		this->zn = zn;
		this->num = num;
		this->maxsize = maxsize;
	}

	void setnext(list_queue* next) { this->next = next; }

	void insert(string x) {
		list_queue* nl = new list_queue(x, this->num + 1, this->maxsize);
		this->setnext(nl);
	}

	void del(int n) {
		if (n == 0) { //first
			this->next->num = this->num;
			if (this->next != NULL) { this->next->del(n); }
		}
		else { //other
			if (this->next->num == n && this->next->next != NULL) {
				this->next = this->next->next;
				this->next->next->num = this->next->num;
			}
			else { this->next->del(n); }
		}
	}

	string getzn(int n) {
		if (this->num == n) { return this->zn; }
		else { this->next->getzn(n); }
	}

	bool isempty() {
		if (this->next == NULL && this->zn == "") { return true; }
		else { return false; }
	}

	bool isfull() {
		if (this->num == this->maxsize - 1) { return true; }
		else { return false; }
	}
};

int main() {
	setlocale(LC_ALL, "rus");

	string kat;
	int ns = 0, time = 0, size = 0;

	cout << "Введите размер очереди: "; cin >> size;
	vec_queue* q1 = new vec_queue(size);

	for (int i = 0; i < size; i++) {
		cout << "Введите статус работника, его идентификационный номер и время выполнения заявки: "; cin >> kat >> ns >> time;
		q1->insert(kat, ns, time);
	}

	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << q1->toString(i) << endl;
	}

	vec_queue* q2 = new vec_queue(size);
	string a[3] = { "M", "K", "P" };
	int m = 0, k = 0, p = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < size; j++) {
			if (a[i] == q1->getkat(j)) {
				q2->insert(q1->getkat(j), q1->getns(j), q1->gettime(j));
			}
		}
	}

	cout << endl << "Приоритет:" << endl << endl;

	for (int i = 0; i < size; i++) {
		cout << q2->toString(i) << endl;
		if (q2->getkat(i) == a[0]) { m += q2->gettime(i); }
		else if (q2->getkat(i) == a[1]) { k += q2->gettime(i); }
		else { p += q2->gettime(i); }
	}

	cout << endl << "На менеждеров затрачено " << m << " минут, на контролёров - " << k << ", а на рабочих - " << p << "."<< endl;

	return 0;
}

/*
	30
	P 28 13
	M 3 90
	K 24 9
	P 6 20
	P 1 17
	P 7 4
	K 30 13
	P 17 1
	P 5 5
	K 19 57
	P 26 6
	P 16 11
	P 18 48
	M 4 8
	K 11 44
	M 13 14
	K 14 12
	P 29 11
	P 8 72
	P 22 31
	P 15 31
	P 25 15
	K 21 16
	P 9 20
	K 23 3
	K 10 29
	P 12 2
	M 20 7
	P 27 35
	M 2 18
*/