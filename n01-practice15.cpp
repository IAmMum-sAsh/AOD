#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

class node{
public:
	int count;
	char symbol;
	node* left;
	node* right;

	node() { }

	node(char symbol, int count) {
		this->symbol = symbol;
		this->count = count;
	}

	node(node* l, node* r) {
		symbol = 0;
		left = l;
		right = r;
		count = l->count + r->count;
	}

	static void print(node* root, int depth = 0) {	// рекурсивный вывод дерева; точки - уровень листа от корня
		if (!root) return;

		if (root->symbol) {
			for (int i = 0; i < depth; i++) { cout << "."; }
			cout << root->symbol << endl;
		}
		else { depth++; }
		print(root->left, depth);
		print(root->right, depth); 
	}
};

void buildTable(node* root, vector<bool>& code, map<char, vector<bool>>& table) {	// обходим дерево, создаём таблицу сжатых кодов
	if (root->left) {
		code.push_back(0);	// налево - 0/f
		buildTable(root->left, code, table);
	}

	if (root->right) {
		code.push_back(1);	// направо - 1/t
		buildTable(root->right, code, table);
	}

	if (root->symbol) { table[root->symbol] = code; }	// дошли до конца - положили в словарь по ключу
	if (code.size()) { code.pop_back(); }		
}

bool sortNode(const node* a, const node* b) {
	return a->count < b->count;
}

string decode(string& str, map<vector<bool>, char>& table) {
	string out = "";
	vector<bool> code;
	for (int i = 0; i < str.length(); i++) {
		code.push_back(str[i] == '0' ? false : true);
		if (table[code]) {
			out += table[code];
			code.clear();
		}
	}
	return out;
}

int main() {
	setlocale(LC_ALL, "RUS");
	string raw = "разработать процедуру сжатия данных на основе жадного алгоритма хаффмана";	// сжимаемая строка
	map<char, int> symbols;

	for (int i = 0; i < raw.length(); i++) { symbols[raw[i]]++; }	// разложили в словарь по ключу-символу, сразу получили в значении частоту встречаемости

	list<node*> trees;
	map<char, int>::iterator itr;
	for (itr = symbols.begin(); itr != symbols.end(); itr++) {
		node* p = new node(itr->first, itr->second);	// first - ключ, second - значение
		trees.push_back(p);
	}	// листья будущего дерева в списке

	while (trees.size() != 1) {
		trees.sort(sortNode);	// сортируем по возрастанию

		node* l = trees.front();	// вынимаем элементы с наиментшим весом [из начала]
		trees.pop_front();
		node* r = trees.front();
		trees.pop_front();

		node* parent = new node(l, r);	// связываем их новым родительским узлом
		trees.push_back(parent);	// кладём обратно
	}

	node* root = trees.front();	// дерево построено
	root->print(root);	// вывод дерева

	vector<bool> code;	// буфер
	map<char, vector<bool> > table;
	buildTable(root, code, table);	// создаём словарь, где ключ - символ, и значение - последовательность булевых значений = его код


	for (itr = symbols.begin(); itr != symbols.end(); itr++) {	//вывод: символ - код
		cout << itr->first << " - ";
		for (int j = 0; j < table[itr->first].size(); j++) {
			cout << table[itr->first][j];
		}
		cout << endl;
	}


	string out = "";
	for (int i = 0; i < raw.length(); i++) {	// кодируем изначальную строку
		for (int j = 0; j < table[raw[i]].size(); j++) {
			out += table[raw[i]][j] + '0';
		}
	}
	cout << endl << out.c_str() << endl;


	map<vector<bool>, char> ftable;
	for (auto i = table.begin(); i != table.end(); i++) { ftable[i->second] = i->first; } // и обратно
	cout << endl << decode(out, ftable).c_str() << endl;

	while (true);
}

/*
	Максимальная сложность O(n^2).
*/