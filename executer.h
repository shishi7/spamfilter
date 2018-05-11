#ifndef EXECUTER_H
#define EXECUTER_H

#include <map>
#include <string>

class executer {
	private:
		int save;
		std::map<std::string, int> save_words;

		std::string word_ref(const std::string wd);
		bool analyse(int& spam, int& ham, std::map<std::string, int>& spam_words, std::map<std::string, int>& ham_words, const std::string in);
		void test(int& spam, int& ham, std::map<std::string, int>& spam_words, std::map<std::string, int>& ham_words);
	public:
		executer();
		void exec(int& spam, int& ham, std::map<std::string, int>& spam_words, std::map<std::string, int>& ham_words);
};
#endif