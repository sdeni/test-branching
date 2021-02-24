#include <iostream>
#include <list>
#include <fstream>

class HashTable {
private:
    static const int N = 100;
    std::list<std::string> buckets[N];

    int calcHash(const std::string &word) {
        return word[0] % N;
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
    void put(const std::string &word) {
        int hash = calcHash(word);

        if(!hasWordInBucket(hash, word)) {
            addWordToBucket(hash, word);
        }
    }

    bool check(const std::string &word) {
        int hash = calcHash(word);
        return hasWordInBucket(hash, word);
    }
};

int main()
{
    std::cout << "Start\n";

    HashTable hashTable;

    std::ifstream infile("../words.txt");

    std::string word;
    while (infile >> word)
    {
        std::cout << word << std::endl;
        hashTable.put(word);
    }

    infile.close();

    std::string userWord;
    do {
        std::cin >> userWord;
        if(hashTable.check(userWord)) {
            std::cout << "Correct word.\n";
        }
        else {
            std::cout << "Wrong word!\n";
        }
    } while (userWord != "exit");

    std::cout << "Finish\n";

    return 0;
}
