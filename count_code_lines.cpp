#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

int count_line(ifstream &fin);
string trip(const string &src);

int main(int argc, char **argv) {
	if (argc == 0) {
		cerr << "no input file, exit...\n";
		return 1;
	}
	ifstream fin(argv[1]);
	if (!fin.is_open()) {
		cerr << "input file doens't exist, exit...\n";
		return 1;
	}

	cout << count_line(fin) << endl;
	return 0;
}

int count_line(ifstream &fin) {
	size_t nlines = 0, spos, epos;
	bool flag = false;
	string line;
	while (getline(fin, line)) {
		line = trip(line);
		if (line.length() == 0)
			continue;
FLAG_IS_TRUE:
		if (true == flag) {
			if ((epos = line.find("*/")) != string::npos) {
				flag = false;
				if (epos != line.length() - 2)
					++nlines;
			}
			continue;
		}

		if (line.substr(0, 2) == "//")
			continue;

		if ((spos = line.find("/*")) != string::npos) {
			flag = true;
			if (spos == 0)
				goto FLAG_IS_TRUE;
			else {
				++nlines;
				if ((epos = line.find("*/")) != string::npos)
					flag = false;
			}
			continue;
		}

		++nlines;
	}
	return nlines;
}

string trip(const string &src) {
	size_t i = 0, j = src.length() - 1;
	while (i < src.length() && isspace(src[i]))
		++i;
	while (j >= 0 && isspace(src[j]))
		--j;
	++j;
	return src.substr(i, j);
}

