#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdlib.h>
#include <assert.h>
#pragma warning (disable:4489)
#define ON 1
#define OFF 0

struct page {
	int freq = 1;
	int data = 0;
};

typedef class std::list <page> Cash;

typedef class std::unordered_map <int, int> Hash;

// Find min in list
int fmin(Cash* list) {
	int min = list->front().freq;

	for (Cash::iterator it = list->begin(); it != list->end(); it++) {
		if (it->freq < min) {
			min = it->freq;
		}

		return min;
	}
}

// Check elm in list and return hit iterator
Cash::iterator check_cash(page node, Cash* list) {
	for (Cash::iterator it = list->begin(); it != list->end(); it++) {
		if (node.data == it->data)
			return it;
	}
	return list->end();
}

// Change min elm in list to value
void change_list(Cash* list, int size, page node) {

	int min = list->front().freq;
	Cash::iterator pmin = list->begin();

	for (Cash::iterator it = list->begin(); it != list->end(); it++) {
		if (it->freq < min) {
			min = it->freq;
			pmin = it;
		}

	}
	pmin->data = node.data;
	pmin->freq = node.freq;

}

void LFU(int argc, char** argv) {
	Cash Mycash;
	Hash Myhash;
	page node;

	int cash_size = 0;
	int num = 0;
	int hit = 0;
	bool FILE_MODE = OFF;

	//input values
	std::ifstream file;
	if (argc == 1) {
		std::cin >> cash_size;
		std::cin >> num;
		FILE_MODE = OFF;

	}
	else {

		//		std::cout << argv[1];
		file.open(argv[1]);
		assert(file);
		file >> cash_size;
		file >> num;
		FILE_MODE = ON;
	}


	for (int i = 0; i < num; i++) {

		// Create a request
		if (FILE_MODE == ON)
			file >> node.data;
		else
			std::cin >> node.data;
		node.freq = 1;

		//Find in hash a request
		Hash::iterator it = Myhash.find(node.data);

		// Added page in hash or update page
		if (it != Myhash.end()) {
			it->second++;
			node.freq = it->second;
		}
		// Create new page
		else
			Myhash[node.data] = 1;

		// Added elm in cash or update cash
		if (check_cash(node, &Mycash) == Mycash.end()) {
			//Add in cash if cash is empty
			if (int(Mycash.size()) < cash_size)
				Mycash.push_front(node);
			//Add in cash if freq cash less then request
			else if (node.freq > fmin(&Mycash))
				change_list(&Mycash, cash_size, node);
		}
		//Update cash
		else {
			check_cash(node, &Mycash)->freq++;
			hit++;
		}

	}

	printf("LFU hits is = [%d] \n", hit);

}
