#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

struct HashTable {
	vector<vector<Company>> table;
};

long long hashString(const string& str) {
	long long p = 31;
	long long m = 2000;
	
	string s = str.length() > 20 ? str.substr(0, 20) : str;

	long long hashValue = 0;
	for (int i = 0; i < s.length(); ++i) {
		hashValue = hashValue * p + s[i];
	}
	hashValue = hashValue % m;

	return hashValue;
}

HashTable* createHashTable(vector<Company> list_company) {
	HashTable* hashTable = new HashTable();
	hashTable->table.resize(2000);

	for (size_t i = 0; i < list_company.size(); ++i) {
		Company company = list_company[i];
		int index = hashString(company.name);
		hashTable->table[index].push_back(company);
	}

	return hashTable;
}

void insert(HashTable* hash_table, Company company) {
	int index = hashString(company.name);
	hash_table->table[index].push_back(company);
}

Company* search(HashTable* hash_table, string company_name) {
	int index = hashString(company_name);
	for (size_t i = 0; i < hash_table->table[index].size(); ++i) {
		if (hash_table->table[index][i].name == company_name) {
			return &hash_table->table[index][i];
		}
	}
	return nullptr;
}

vector<string> readCompanyNames(const string& filename) {
	ifstream file(filename);
	vector<string> company_names;
	string line;
	while (getline(file, line)) {
		company_names.push_back(line);
	}
	return company_names;
}

vector<Company> readCompanyInfo(const string& filename, const vector<string>& company_names) {
	ifstream file(filename);
	vector<Company> companies;
	string line;
	size_t idx = 0;

	getline(file, line);

	while (getline(file, line) && idx < company_names.size()) {
		stringstream ss(line);
		string name, profit_tax, address;

		getline(ss, name, '|');
		getline(ss, profit_tax, '|');
		getline(ss, address, '|');

		Company company;
		company.name = company_names[idx];
		company.profit_tax = profit_tax;
		company.address = address;

		companies.push_back(company);
		++idx;
	}
	return companies;
}


void writeResults(const string& filename, const vector<Company>& companies) {
	ofstream file(filename);
	for (size_t i = 0; i < companies.size(); ++i) {
		const Company& company = companies[i];
		file << company.name << "|" << company.profit_tax << "|" << company.address << endl;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cerr << "Usage: ./main <input.txt> <MST.txt> <output.txt>" << endl;
		return 1;
	}

	vector<string> company_names = readCompanyNames(argv[1]);
	vector<Company> companies = readCompanyInfo(argv[2], company_names);
	HashTable* hashTable = createHashTable(companies);

	vector<Company> results;
	for (const string& company_name : company_names) {
		Company* company = search(hashTable, company_name);
		if (company != nullptr) {
			results.push_back(*company);
		}
		else {
			Company not_found;
			not_found.name = company_name;
			not_found.profit_tax = "Not Found";
			not_found.address = "Not Found";
			results.push_back(not_found);
		}
	}

	writeResults(argv[3], results);

	cout << "Results are saved to " << argv[3] << endl;

	return 0;
}