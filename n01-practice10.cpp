#include <iostream>
using namespace std;

struct node {
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p) {
	return p ? p->height : 0;
}

int bfactor(node* p) {
	return height(p->right) - height(p->left);
}

void fixheight(node* p) {
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) {
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) {
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) {
	fixheight(p);
	if (bfactor(p) == 2) {
		if (bfactor(p->right) < 0) p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2) {
		if (bfactor(p->left) > 0) p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* insert(node* p, int k) {
	if (!p) return new node(k);
	if (k < p->key) p->left = insert(p->left, k);
	else p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) {
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) {
	if (p->left == 0) { return p->right; }
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) {
	if (!p) return 0;
	if (k < p->key) { p->left = remove(p->left, k); }
	else if (k > p->key) { p->right = remove(p->right, k); }
	else {
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}



int main(){
	setlocale(LC_ALL, "RUS");

	int n;
	cout << "Введите кол-во добавляемых узлов: "; cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cout << "Введите значение очередного узла: "; cin >> arr[i];
	}

	node* root = insert(0, arr[0]);

	for (int i = 1; i < n; i++) {
		insert(root, arr[i]);
	}

	cout << 1;

    return 0;
}

/*
	11
	8 6 10 4 7 9 15 2 5 14 16
*/