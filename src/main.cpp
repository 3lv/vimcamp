#include <iostream>
#include <string>
#include "../include/dict.h"
using namespace std;


const vector<string> MODES({"Insert", "Normal", "Normal.window", "Normal.square", "Normal.g", "Normal.z", "Visual", "Command-line", "Terminal", "Ex"});


int main() {
	Dict dict;
	bool running = true;
	/*
	cout << "Possible modes are: " << endl;
	for(auto x: MODES) {
		cout << x << " ";
	}
	cout << endl;
	*/
	//cout << "Choose mode(leave blank for all): ";
	while(running) {
		string input;
		//getline(fin, 
		Record rec = dict.random();
		cout << rec.command << "             " << rec.score;
		getline(cin, input);
		cout << rec.action << endl;
		cout << "Did you know what it does? [Y(es)/n(o)/a(bsolutely)]";
		getline(cin, input);
		if(input.size() == 0) {
			dict.modify_score(rec.number, -rec.score / 2);
		} else if(input[0] == 'n') {
			dict.modify_score(rec.number, 1000 * 100);
		} else if(input[0] == 'a') {
			
		}
		cout << endl;
	}
	return 0;
}
