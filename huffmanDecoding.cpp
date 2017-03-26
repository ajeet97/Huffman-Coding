/*
*	Program: Huffman Decoding Program
*	Author : Ajeet Goyal
*/

#include <bits/stdc++.h>

using namespace std;

void printCharCode(unordered_map<string, char> &charCode) {
	unordered_map<string, char>::iterator it;
	for(it=charCode.begin(); it!=charCode.end(); it++)
		cout<<it->first<<": "<<it->second<<endl;
	cout<<endl;
}

int main() {
	ifstream encoding, in;
	encoding.open("encoding.txt");
	in.open("encodedOutput.txt");

	ofstream out;
	out.open("decodedOutput.txt");

	if(!encoding.is_open()) {
		cout << "Could not open encoding.txt!" << endl;
		return 1;
	}

	if(!in.is_open()) {
		cout << "Could not open encodedOutput.txt!" << endl;
		return 1;
	}

	if(!out.is_open()) {
		cout << "Could not open decodedOutput.txt!" << endl;
		return 1;
	}

	unordered_map<string, char> charCode;

	int chAscii;
	string code;
	while(encoding >> chAscii >> code)
		charCode[code] = (char)chAscii;

	printCharCode(charCode);

	char ch;
	code = "";
	while(in >> noskipws >> ch) {
		code += ch;
		if(charCode.find(code) != charCode.end()) {
			out << charCode[code];
			code = "";
		}
	}

	out.close();
	in.close();
	encoding.close();

	return 0;
}