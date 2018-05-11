#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "executer.h"

using namespace std;

executer::executer(){
	save = 0;
}

void executer::exec(int& spam, int& ham, map<string, int>& spam_words, map<string, int>& ham_words){
	printf("Hello, I'm a Simple Spam filter!\nI've been training on 5574 different messages.\nI fill so strong, test me, please!\nIf you want to use me on database granted by my developres and see the statistics - type 1.\nIf you want to test me by yourself - type 2.\n");	
	int fg;
	cin >> fg;
	while(fg != 3){
		if(fg == 2){
			printf("Please, write the name of the file with your email (ex: my_email.txt)\n");	
			string str;
			cin >> str;
			bool res = analyse(spam, ham, spam_words, ham_words, str);
			if(res)
				printf("It's a ham message (probably).\nYou can safely read it.\n");
			else
				printf("It's a spam! (probably). Do not read it, please.\n");
			printf("You may help me, if you leave your little feedback:\nJust type 1 in case it was a ham and 0 - otherwise.\n");
			bool ch;
			cin >> ch;
			if(ch){
				ham += save;
				for(map<string, int>::iterator it = save_words.begin(); it != save_words.end(); it++){
					ham_words[(*it).first] += (*it).second;
				}
			} else {			
				spam += save;
				for(map<string, int>::iterator it = save_words.begin(); it != save_words.end(); it++){
					spam_words[(*it).first] += (*it).second;
				}
			}
		} else {
			test(spam, ham, spam_words, ham_words);
		}
		printf("If you want to use me on database granted by my developres and see the statistics - type 1.\nIf you want to test me by yourself - type 2.\nIf you want to quit - type 3.\n");
		cin >> fg;
	}
}

bool executer::analyse(int& spam, int& ham, map<string, int>& spam_words, map<string, int>& ham_words, const string in){
	fstream file;
	const char * inc = in.c_str();
	file.open(inc);
	string word;
	int cnt = 0;
	map <string, int> tmp;
	while (file >> word){
        word = word_ref(word);
    	tmp[word]++;	
    	cnt++;
    }
	file.close();

	double p_s_w = 1.0, p_h_w = 1.0;
	for(map<string, int>::iterator it = tmp.begin(); it != tmp.end(); it++){
		string cur = (*it).first;
		if(spam_words.find(cur) != spam_words.end()){
			double p_w_s = ((double)spam_words[cur] / (double)spam);	
			double p_w_h = ((double)ham_words[cur] / (double)ham);
			double p = p_w_s / (p_w_s + p_w_h);
			p_s_w *= p;
			p_h_w *= (1.0 - p);
		}
	}
	save = cnt;
	save_words = tmp;
	return (p_s_w / (p_s_w + p_h_w)) < 0.5;
}

void executer::test(int& spam, int& ham, map<string, int>& spam_words, map<string, int>& ham_words){
	double success = 0.0;
	for(int i = 1; i <= 747; i++){
		stringstream ss;
		ss << i;
		string str = ss.str();
		str = "test_set/spam_" + str + ".txt";
		if(analyse(spam, ham, spam_words, ham_words, str) == 0)
			success += 1.0;
	}
	for(int i = 1; i <= 4825; i++){
		stringstream ss;
		ss << i;
		string str = ss.str();
		str = "test_set/ham_" + str + ".txt";
		if(analyse(spam, ham, spam_words, ham_words, str) == 0)
			success += 1.0;
	}

    double stat = success / 5574.0;
    printf("The filter was tested on it's training set.\nThe percetage of success is %f\n", stat * 100.0);	
}

string executer::word_ref(const string wd){
	string res = "";
	for(int i = 0; i < wd.size(); i++){
		if('A' <= wd[i] && wd[i] <= 'Z')
			res += char(tolower(wd[i]));
		else if ('a' <= wd[i] && wd[i] <= 'z')
			res += wd[i];
	}
	
	 return res;
}