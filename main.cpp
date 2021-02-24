#include <iostream>
#include <list>
#include <fstream>

class HashTable {
private:
    static const int N = 100;
    std::list<std::string> buckets[N];

    int calcHash(const std::string &word, bool useOnlyTheFirst, int test = 0) {
        int res = 0;
        res = word[0] % N;
        if(!useOnlyTheFirst && word.length()>1) {
            res += word[1]+test;
            res %= N;
        }
        return res;
    }

    bool hasWordInBucket(int index, const std::string &word) {
        for(auto w : buckets[index]) {
            if(w == word) {
                return true;
            }
        }
        return false;
    }

    void addWordToBucket(int index, const std::string &word) {
        buckets[index].push_back(word);
    }

public:
    bool check(const std::string &word, bool useOnlyTheFirst) {
        int hash = calcHash(word, useOnlyTheFirst);
        return hasWordInBucket(hash, word);
    }

    void put(const std::string &word) {
        int hash = calcHash(word, false);

        if(!hasWordInBucket(hash, word)) {
            addWordToBucket(hash, word);
        }
    }
};

int main()
{
    HashTable dictionary;

    std::ifstream infile("../words.txt");

    std::string word;
    while (infile >> word)
    {
        dictionary.put(word);
    }

    infile.close();

    std::string userWord;
    do {
        std::cin >> userWord;
        if(dictionary.check(userWord, true)) {
            std::cout << "Correct word.\n";
        }
        else {
            std::cout << "Wrong word!\n";
        }
    } while (userWord != "exit");

    return 0;
}
