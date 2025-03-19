#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str) {
	if (n == 0) {
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n - 1, str + "0");
	generateBinaryStrings(n - 1, str + "1");
}

int main() {
	int n;
	cout << "Enter a number: ";
	cin >> n;
	generateBinaryStrings(n, "");
	return 0;
}