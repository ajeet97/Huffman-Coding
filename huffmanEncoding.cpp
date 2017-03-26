/*
*	Program: Huffman Encoding Program
*	Author : Ajeet Goyal
*/

#include <bits/stdc++.h>

using namespace std;

unordered_map<char, string> charCode;

struct MinHeapNode
{
	char data;
	unsigned freq;
	MinHeapNode *left, *right;
 
	MinHeapNode(char data, unsigned freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};
 
struct compare
{
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		return (l->freq > r->freq);
	}
};
 
void printCodes(struct MinHeapNode* root, string str)
{
	if (!root)
		return;
 
	if (root->data != '$')
		cout << (int)(root->data) << "(" << root->data << ")" << ": " << str << "\n";
 
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

void writeCodes(ofstream &out, struct MinHeapNode* root, string prefix) {
	if(!root)
		return;

	if(root->data != '$') {
		charCode[root->data] = prefix;
		out << (int)(root->data) << " " << prefix << endl;
	}

	writeCodes(out, root->left, prefix + "0");
	writeCodes(out, root->right, prefix + "1");
}
 
void HuffmanCodes(vector<char> data, vector<int> freq)
{
	int size = data.size();

	struct MinHeapNode *left, *right, *top;
 
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));
 
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();
 
		right = minHeap.top();
		minHeap.pop();
 
		top = new MinHeapNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}

	printCodes(minHeap.top(), "");

	ofstream out;
	out.open("encoding.txt");
	if(!out.is_open()) {
		cout << "Could not open encoding.txt!" << endl;
		return;
	}

	writeCodes(out, minHeap.top(), "");

	out.close();
}

void encodeFile(string inFileName, string outFileName, unordered_map<char, string> charCode) {
	ifstream in;
	in.open(inFileName.c_str());
	if(!in.is_open()) {
		cout << "Could not open " << inFileName << " !\n";
		return;
	}

	ofstream out;
	out.open(outFileName.c_str());
	if(!out.is_open()) {
		cout << "Could not open " << outFileName << " !\n";
		return;
	}

	char ch;
	while(in >> noskipws >> ch)
		out<<charCode[ch];

	out.close();
	in.close();
}

double compressionRatio(vector<char> uniqueChars, vector<int> freq, unordered_map<char, string> charCode) {
	if(uniqueChars.size() == 0) return 0.0;

	int totalChars = 0;
	for(int i=0; i<freq.size(); i++)
		totalChars += freq[i];

	int bitsPerChar = (int)ceil(log2(uniqueChars.size()));
	cout<<"bitsPerChar: "<<bitsPerChar<<endl;

	int totalBitsWithoutCompression = bitsPerChar * totalChars;

	int totalBitsWithCompression = 0;
	for(int i=0; i<uniqueChars.size(); i++)
		totalBitsWithCompression += freq[i] * charCode[uniqueChars[i]].length();

	return (double)totalBitsWithCompression / (double)totalBitsWithoutCompression;
}

int main()
{
	ifstream input;
	input.open("input.txt");
	if(!input.is_open()) {
		cout << "Could not open input.txt!" << endl;
		return 1;
	}

	unordered_map<char, int> charFreq;

	vector<char> uniqueChars;
	vector<int> freq;

	char ch;
	while(input >> noskipws >> ch)
		charFreq[ch]++;

	input.close();

	unordered_map<char, int>::iterator it = charFreq.begin();

	for(; it != charFreq.end(); it++) {
		uniqueChars.push_back(it->first);
		freq.push_back(it->second);
	}

	HuffmanCodes(uniqueChars, freq);

	encodeFile("input.txt", "encodedOutput.txt", charCode);

	cout << "\nCompressiont Ration: "<<compressionRatio(uniqueChars, freq, charCode) << endl << endl;

	return 0;
}