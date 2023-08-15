#include <fstream>
#include <vector>
#include <map>


class Aib;
class Record;
class Dict;

class Aib {
private:
	std::vector<int64_t> __aib;
	int lsb(int number);
	int64_t __querry(size_t pos);
public:
	void update(size_t pos, int64_t val);
	size_t find(int64_t val);
	int64_t total();
	Aib();
	Aib(std::vector<int64_t> *arr);
	int64_t operator[](size_t pos);
};

class Record {
private:
public:
	static Dict *parent;
	static const int64_t DEFAULT_SCORE;
	std::string mode;
	std::string command;
	std::string action;
	int64_t score;
	size_t number;
	Record(std::string mode, std::string command, std::string action);
	Record(std::string mode, std::string command, std::string action, size_t pos);
	void modify_score(int64_t diff);
};

class Dict {
private:
	typedef std::string mode_name;
	std::map<mode_name, std::vector<Record>> __dict;
	std::map<mode_name, int64_t> __total_score;
	std::map<mode_name, Aib> __score_aib;
	std::map<mode_name, std::vector<int64_t>> __scores;
	mode_name __current_mode;
	void __read();
	void __init_score_aib();
public:
	mode_name mode = "Insert";
	Dict();
	Record random();
	void modify_score(size_t pos, int64_t score);
};
