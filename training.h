#ifndef TRAINING_H
#define TRAINING_H

#include <map>
#include <string>

class training {
	private:
		static std::string word_ref(const std::string wd);
	public:
		static void start(int& spam, int& ham, std::map<std::string, int>& spam_words, std::map<std::string, int>& ham_words);
};
#endif