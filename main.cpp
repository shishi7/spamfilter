#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "training.h"
#include "executer.h"

using namespace std;

int spam, ham;
map <string, int> spam_words, ham_words;

int main(){
	training::start(spam, ham, spam_words, ham_words);	
	cout << spam << ' ' << ham << "\n";
	executer ex;
	ex.exec(spam, ham, spam_words, ham_words);
}
