#include <iostream>
#include <string>
#include "../include/dict.h"
using namespace std;

const vector<string> MODES({"Insert", "Normal", "Normal.window", "Normal.square", "Normal.g", "Normal.z", "Visual", "Command-line", "Terminal", "Ex"});

int main() {
	Dict dict;
	Dict::mode = "Normal";
	bool running = true;
	while(running) {
		string input;
		Record rec = dict.random();
		cout << rec.command;
		getline(cin, input);
		cout << rec.action << endl;
		cout << "Did you know what it does? [Y(es)/n(o)/a(bsolutely)] ";
		getline(cin, input);
		if(input.size() == 0) {
			rec.add_score(-rec.score / 2);
		} else if(input[0] == 'n') {
			rec.add_score(1000 * 10);
		} else if(input[0] == 'a') {
			
		}
		cout << endl;
	}
	return 0;
}
