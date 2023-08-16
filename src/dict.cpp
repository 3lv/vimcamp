#include <chrono>
#include <random>
#include "../include/dict.h"

int Aib::lsb(int number) {
	return number & (-number);
}
int64_t Aib::__querry(size_t pos) {
	++pos;
	int64_t s = 0;
	while(pos) {
		s += __aib[pos];
		pos -= lsb(pos);
	}
	return s;
}
void Aib::update(size_t pos, int64_t val) {
	++pos;
	size_t n = __aib.size() - 1;
	while(pos <= n) {
		__aib[pos] += val;
		pos += lsb(pos);
	}
}
size_t Aib::find(int64_t val) {
	size_t ac = 0;
	size_t pas = 1 << 20;
	size_t n = __aib.size() - 1;
	while(pas) {
		if(ac + pas <= n && __aib[ac + pas] < val) {
			ac += pas;
			val -= __aib[ac];
		}
		pas >>= 1;
	}
	return ac;
}
int64_t Aib::total() {
	size_t n = __aib.size() - 1;
	return __querry(n);
}
Aib::Aib() {
}
Aib::Aib(std::vector<int64_t> *arr) {
	size_t n = arr->size();
	__aib = std::vector<int64_t>(n + 1, 0);
	for(unsigned int i = 0; i < n; ++i) {
		update(i, arr->at(i));
	}
}
int64_t Aib::operator[](size_t pos) {
	return __querry(pos);
}

Dict *Record::parent = NULL;
const int64_t Record::DEFAULT_SCORE = 1000;
Record::Record(std::string mode, std::string command, std::string action) {
	this->mode = mode;
	this->command = command;
	this->action = action;
	score = DEFAULT_SCORE;
}
Record::Record(std::string mode, std::string command, std::string action, size_t number) {
	this->mode = mode;
	this->command = command;
	this->action = action;
	score = DEFAULT_SCORE;
	this->number = number;
}
std::ostream &operator<<(std::ostream &os, Record record) {
	return os << "[" << record.command << ": " << record.action << "]";
}

void Dict::__read() {
	std::ifstream fin("index.txt");
	std::string line;
	while(getline(fin, line)) {
		if(line.size() == 0) {
			continue;
		}
		if(line[0] == '#') { // this is a comment
			continue;
		}
		if(line.substr(0,7) == "[[END]]") {
			break;
		}
		if(line.substr(0, 9) == "[[MODE]] ") {
			__current_mode = line.substr(9);
			continue;
		}
		std::string command;
		int cmdlen = line.find('\t');
		if(cmdlen == -1) {
			continue;
		}
		command = line.substr(0, cmdlen);
		// find first printable char
		int i = cmdlen;
		while(line[++i] <= ' ');
		std::string action = line.substr(i);
		Record record(__current_mode, command, action, __dict[__current_mode].size());
		__dict[__current_mode].push_back(record);
		__scores[__current_mode].push_back(record.score);
		__total_score[__current_mode] += record.score;
	}
}
void Dict::__init_score_aib() {
	for(auto mode_it : __scores) {
		mode_name mode = mode_it.first;
		std::vector<int64_t> scores = mode_it.second;
		__score_aib[mode] = Aib(&scores);
	}
}
void Dict::add_score(size_t pos, int64_t score) {
	if(__dict[mode][pos].score + score < 0) {
		score = -__dict[mode][pos].score;
	}
	__dict[mode][pos].score += score;
	__score_aib[mode].update(pos, score);
}
Dict::mode_name Dict::mode = "Normal";
Dict::Dict() {
	this->__current_mode = "None";
	__read();
	__init_score_aib();
	Record::parent = this;
}
Record Dict::random() {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	if(__dict[mode].size() == 0) {
		return Record("ERR", "Mode " + mode + " not found in file", "");
	}
	int64_t random_score = rng() % (__score_aib[mode].total() + 1);
	size_t record_number = __score_aib[mode].find(random_score);
	Record record =  __dict[mode][record_number];
	return record;
}

void Record::add_score(int64_t diff) {
	Record::parent->add_score(this->number, diff);
}
