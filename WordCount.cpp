// WordCount.cpp

#include "WordCount.h"
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int count = 0; 
    for(size_t i = 0; i < CAPACITY; i++){
        for(const auto& elem : table[i]) {
            count += elem.second;
        }
    }
    return count;
}

int WordCount::getNumUniqueWords() const {
	int count = 0; 
    for(size_t i = 0; i < CAPACITY; i++) {
        count += static_cast<int>(table[i].size());
    }
    return count;
}

int WordCount::getWordCount(std::string word) const {
	string nb_word = makeValidWord(word);
    if(nb_word.empty()){
        return 0;
    }
    size_t ind = hash(nb_word);
    const auto& bucket = table[ind];
    for(const auto& elem : bucket) {
        if(elem.first == nb_word) {
            return elem.second;
        }
    }
    return 0;
}
	
int WordCount::incrWordCount(std::string word) {
    string nb_word = makeValidWord(word); 
    if(nb_word.empty()) return 0; 
    
    size_t ind = hash(nb_word);
    auto& bucket = table[ind];
    for(auto& elem : bucket) {
        if(elem.first == nb_word) {
            elem.second++; 
            return elem.second;
        }
    }
    bucket.push_back({nb_word, 1});
    return 1; 
}

int WordCount::decrWordCount(std::string word) {
	string nb_word = makeValidWord(word); 
    if(nb_word.empty()) return -1;
    size_t ind = hash(nb_word);
    auto& bucket = table[ind];
    for(size_t i = 0; i < bucket.size(); i++) {
        if(bucket[i].first == nb_word) {
            if(bucket[i].second > 1) {
                bucket[i].second--;
                return bucket[i].second;
            }
            else {
                bucket.erase(bucket.begin() + static_cast<long>(i));
                return 0;
            }
        }
    }
    return -1;
}


bool WordCount::isWordChar(char c) {
	return std::isalpha(static_cast<unsigned char>(c)) != 0; 
}

std::string WordCount::makeValidWord(std::string word) {
	std::string output;
    output.reserve(word.size());

    auto is_alpha = [](char ch) {
        return std::isalpha(static_cast<unsigned char>(ch)) != 0;
    };

    for (size_t i = 0; i < word.size(); i++) {
        unsigned char un_c = static_cast<unsigned char>(word[i]);
        char c = static_cast<char>(un_c);

        if (is_alpha(c)) {
            output.push_back(static_cast<char>(std::tolower(un_c)));
            continue;
        }

        if ((c == '\'' || c == '-') &&  i > 0 && i + 1 < word.size() &&  is_alpha(word[i - 1]) &&  is_alpha(word[i + 1])) {

            output.push_back(c);
            continue;
        }

    }

    return output;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	std::vector<std::string> words;
	for (size_t i = 0; i < CAPACITY; i++){
		for(size_t j = 0; j < table[i].size(); j++){
			words.push_back(table[i][j].first);
		}
	}
	sort(words.begin(), words.end());
	for (const std::string &w : words){
	out << w << "," << getWordCount(w) << endl;
	}
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> count;
	for (size_t i = 0; i < CAPACITY; i++){
		for(size_t j = 0; j < table[i].size(); j++){
			count.push_back(table[i][j]);
		}
	}
	sort(count.begin(), count.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
		if (a.second == b.second){
			return a.first < b.first;
		}
		return a.second < b.second; //sort by count and return
	});
	for (const auto &pair : count){
		out << pair.first << "," << pair.second << endl;
	}
}


void WordCount::addAllWords(std::string text) {
	std::istringstream iss(text);
	std::string word;
	while (iss >> word){
		incrWordCount(word);
	}
}
