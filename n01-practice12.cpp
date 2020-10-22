#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct owner {
	long long nomber;
	string adress;
	string fio;
};

void write_bin_file(const char* filename);
vector<owner*> read_bin_file(const char* filename);
void remove_node_in_bin_file(const char* filename, string nom);
void get_by_nombers();
void del_by_nomber();
void print_bin_file();

int main(){
	setlocale(LC_ALL, "RUS");

	write_bin_file("ter.dat");
	
	while (true) {
		cout << endl << "/*\n1 for search\n2 to delete\n3 to print\n4 to reload from data.txt in binary file\n*/" << endl << endl;
		int y; cin >> y;

		if (y == 1) {
			get_by_nombers();
		}
		else if(y == 2) {
			del_by_nomber();
		}
		else if (y == 3) {
			print_bin_file();
		}
		else if (y == 4) {
			write_bin_file("ter.dat");
			cout << "Done." << endl;
		}
	}
	return 0;
}

void print_bin_file(){
	vector<owner*> uwu = read_bin_file("ter.dat");

	for (int i = 0; i < uwu.size(); ++i) {
		cout << uwu[i]->nomber << " " << uwu[i]->adress << " " << uwu[i]->fio << endl;
	}
}

void write_bin_file(const char* filename) {
	int n;

	char buf1[50];
	char buf2[50];
	char buf3[50];

	ifstream fin("data.txt");
	fin.getline(buf1, 50);
	n = atoi(buf1);

	int a;
	FILE* f = fopen(filename, "wb");
	fwrite(&n, sizeof(int), 1, f);

	for (int i = 0; i < n; ++i) {

		fin.getline(buf1, 50);
		long long jery = atoll(buf1);
		fwrite(&jery, sizeof(long long), 1, f);

	
		fin.getline(buf2, 50);
		int r = 0;
		while (buf2[r] != '\0') { ++r; }
		fwrite(&r, sizeof(int), 1, f);
		fwrite(&buf2, sizeof(char)*r, 1, f);

		fin.getline(buf3, 50);
		r = 0;
		while (buf3[r] != '\0') { ++r; }
		fwrite(&r, sizeof(int), 1, f);
		fwrite(&buf3, sizeof(char) * r, 1, f);
	}
	fclose(f);
}


vector<owner*> read_bin_file(const char* filename){
	vector<owner*> mass;

	int n;
	FILE* f1 = fopen(filename, "rb");
	fread(&n, sizeof(int), 1, f1);

	long long a1;
	char adress[50];
	string tadr = "";
	char fio[50];
	string tfio = "";
	
	for (int j = 0; j < n; ++j) {
		fread(&a1, sizeof(long long), 1, f1);
		
		int er;
		fread(&er, sizeof(int), 1, f1);
		fread(&adress, sizeof(char)*er, 1, f1);
		for (int i = 0; i < er; ++i) { tadr += adress[i]; }


		fread(&er, sizeof(int), 1, f1);
		fread(&fio, sizeof(char) * er, 1, f1);
		for (int i = 0; i < er; ++i) { tfio += fio[i]; }

		owner* owo_uwu = new owner;
		owo_uwu->nomber = a1;
		owo_uwu->adress = tadr;
		owo_uwu->fio = tfio;

		mass.push_back(owo_uwu);

		tadr = "";
		tfio = "";
	}
	fclose(f1);
	return mass;
}

void get_by_nombers(){
	cout << "Input 3 first nombers to search: ";
	int znal; cin >> znal;

	vector<owner*> ow;

	ow = read_bin_file("ter.dat");

	for (int i = 0; i < ow.size(); ++i) {

		string q1 = to_string(znal);
		string q2 = to_string(ow[i]->nomber);

		if (q1[0] == q2[0] && q1[1] == q2[1] && q1[2] == q2[2]) {
			cout << ow[i]->nomber << " " << ow[i]->adress << " " << ow[i]->fio << endl;
		}
		else if (i == ow.size()-1) {
			cout << "Can't find nomber." << endl;
		}
	}
}

void del_by_nomber(){
	cout << "Input first nomber of nomber to del: ";
	int znal; cin >> znal;

	vector<owner*> ow;

	ow = read_bin_file("ter.dat");

	for (int i = 0; i < ow.size(); ++i) {

		string q1 = to_string(znal);
		string q2 = to_string(ow[i]->nomber);

		if (q1[0] == q2[0]) {
			remove_node_in_bin_file("ter.dat", q2);
		}
	}
}

void remove_node_in_bin_file(const char* filename, string nom){
	vector<owner*> ow;
	ow = read_bin_file("ter.dat");

	int mesto = -1;

	for (int i = 0; i < ow.size(); ++i) {
		string q2 = to_string(ow[i]->nomber);

		if (nom == q2) {
			mesto = i;
			break;
		}
	}

	if (mesto == -1) {
		cout << endl << "Can't find nomber " << nom << endl;
		return;
	}

	ow[mesto]->nomber = ow[ow.size() - 1]->nomber;
	ow[mesto]->adress = ow[ow.size() - 1]->adress;
	ow[mesto]->fio = ow[ow.size() - 1]->fio;

	ow.erase(ow.begin() + ow.size() - 1);

	ofstream fin("data.txt");

	fin << ow.size() << "\n";

	for (int i = 0; i < ow.size(); ++i) {
		fin << ow[i]->nomber << "\n";
		fin << ow[i]->adress << "\n";
		fin << ow[i]->fio << "\n";
	}

	fin.close();

	write_bin_file("ter.dat");
}