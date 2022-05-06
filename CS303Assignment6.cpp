#include<list>
#include<iostream>
#include<iterator>
#include<utility>
#include<string>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

void addPair(list<char>*, int, pair<string, char>, map<string, char>*);
void removeElement(list<char>*, int, pair<string, char>, map<string, char>*);
void traverseHash(list<char>*, int);
list<char>* rehashTable(list<char>*, map<string, char>*, int&, int);

void main() {
	map<string, char>* origMap = new map<string, char>{ 
		{"r98",'A'},
		{"11y",'L'},
		{"q54",'G'},
		{"p88",'O'},
		{"bb1",'R'},
		{"www",'I'},
		{"nbn",'T'},
		{"pop",'H'},
		{"87u",'M'},
		{"ede",'S'},
		{"kk8",'A'},
		{"711",'L'},
		{"mom",'G'},
		{"28m",'O'}
	};

	int dataSize = origMap->size();
	int hashSize = 20;
	list<char>* hashTab = new list<char>[hashSize];
	int index;

	auto iter = origMap->begin();
	while (iter != origMap->end()) {
		index = 0;
		for (int x = 2; x >= 0; x--) {
			index += (((int)(iter->first[x])) * (int)pow(31, x));
		}
		index %= hashSize;
		hashTab[index].push_back(iter->second);
		++iter;
	}
	addPair(hashTab, hashSize, { "2qz", 'Q' }, origMap);
	traverseHash(hashTab, hashSize);
	removeElement(hashTab, hashSize, { "87u",'M' }, origMap);

	cout << "Testing rehash....\n\n" << endl;
	hashTab = rehashTable(hashTab, origMap, hashSize, 23);
	traverseHash(hashTab, hashSize);

	delete[] hashTab;
	system("pause");
}

//pre:  the hash table, current hash size, new element to be added 
//		pair<hash key, value>, and running map of keys and values for rehashing later
//post: element inserted into hash table and also added to map
void addPair(list<char>* hashTab, int hashSize, 
	pair<string, char> newElement, map<string, char>* orig)
{
	int index = 0;
	for (int x = 2; x >= 0; x--) {
		index += ((int)(newElement.first)[x] * (int)pow(31, x));
	}
	index %= hashSize;
	hashTab[index].push_back(newElement.second);
	orig->insert(newElement);
}

//pre:  hash table, current size, element to delete in form pair<key, elem>, and map
//post: remove element from list at hash location, also change value to dummy in map
//		so it doesn't get rehashed later
void removeElement(list<char>* hashTab, int hashSize, 
	pair<string, char> delElement, map<string, char>* orig)
{
	int index = 0;
	for (int x = 2; x >= 0; x--) {
		index += ((int)(delElement.first)[x] * (int)pow(31, x));
	}
	index %= hashSize;
	hashTab[index].remove(delElement.second);
	(*orig)[delElement.first] = ' ';
}

//pre: the hash table ptr and current size
//post: iterate through hash table and internal char lists
void traverseHash(list<char>* hashTab, int hashSize) 
{
	for (int i = 0; i < hashSize; i++) {
		list<char>::iterator b = hashTab[i].begin();
		list<char>::iterator e = hashTab[i].end();
		for (; b != e; b++) {
			cout << *b << "->";
		}
		cout << "NULL" << endl;
	}
}

//pre:  hash table, running map of keys/values, current size, and new size
//post: return old hash table if invalid (less/equal) size, else return new
//		hash table to assignment operator.
list<char>* rehashTable(list<char>* hashTab, map<string, char>* orig, 
	int& currentSize, int newSize) 
{
	if (newSize <= currentSize) {
		cout << "Hash size needs to be greater than original size" << endl;
		return hashTab;
	}
	else {
		currentSize = newSize;
		list<char>* newTab = new list<char>[newSize];

		int index;
		auto iter = orig->begin();
		while (iter != orig->end()) {
			if (iter->second == ' ') {
				++iter;
			}
			else {
				index = 0;
				for (int x = 2; x >= 0; x--) {
					index += (((int)(iter->first[x])) * (int)pow(31, x));
				}
				index %= newSize;
				newTab[index].push_back(iter->second);
				++iter;
			}
		}
		return newTab;
	}
}