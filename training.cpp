//training class implementation
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "training.h"

using namespace std;

string training::word_ref(const string wd){
	string res = "";
	for(int i = 0; i < wd.size(); i++){
		if('A' <= wd[i] && wd[i] <= 'Z')
			res += char(tolower(wd[i]));
		else if ('a' <= wd[i] && wd[i] <= 'z')
			res += wd[i];
	}
	
	 return res;
}

void training::start(int& spam, int& ham, map<string, int>& spam_words, map<string, int>& ham_words){
	ifstream file;
	file.open ("train_set/spam_ham.txt");
	string str;
	while(getline(file, str)){
    	istringstream iss(str);
    	bool flag = true;
    	string word;
    	iss >> word;
    	if(word == "spam")
    		flag = false;
    	while (iss >> word)
    	{
    	    word = word_ref(word);
    	    if(flag){
    	    	if(word != ""){
    	    		ham++;
    	    		ham_words[word]++;
    	    	}
    	    } else {    	    
    	    	if(word != ""){
    	    		spam++;
    	    		spam_words[word]++;	
    	    	}
    	    }
    	}
    }
    file.close();
}