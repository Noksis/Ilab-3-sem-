#include <stdio.h>
#include <list>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdlib.h>
#include <assert.h>
#pragma warning (disable:4996)

#define ON 1
#define OFF 0

struct page {
	int freq = 1;
	int data = 0;
};

typedef class std::list <page> Cash;

typedef class std::unordered_map <int, int> Hash;


void input(int* cash_len, int* req_len);

void create_hash(int cash_len, int** hash_t);

void add_hash(int* hash_t, int cash_len, int value);

void replace_hash(int* hash_t, int value, int  i);

int find_hash(int value, int* hash_t, int cash_len);

int LRU(int argc, char** argv);

int fmin(Cash* list);

Cash::iterator check_cash(page node, Cash* list);

void change_list(Cash* list, int size, page node);

void LFU(int argc, char** argv);