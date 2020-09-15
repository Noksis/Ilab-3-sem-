#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)
#define ON 1
#define OFF 0

const int MAX_LEN = 100;
int NO_FIND = -1;

// Задаем размер кэша и кол-во запросов
void input(int* cash_len, int* req_len) {
	assert(scanf("%d %d", cash_len, req_len) == 2);
}

// Создаем кэш и заполняем нулями
void create_hash(int cash_len, int** hash_t) {
	*hash_t = (int*)calloc(cash_len, sizeof(int));
}

// Добавляем в кэш новое значени и сдвигаем все предыдущие
void add_hash(int* hash_t, int cash_len, int value) {
	int tmp1 = hash_t[0];
	int tmp2 = hash_t[1];
	for (int i = 0; i < cash_len; i++) {
		tmp2 = hash_t[i + 1];
		hash_t[i + 1] = tmp1;
		tmp1 = tmp2;
	}
	hash_t[0] = value;
}

// Берем из кэша нужное значение и сдвигаем в начало
void replace_hash(int* hash_t, int value, int  i) {
	int tmp1 = hash_t[0];
	int tmp2 = hash_t[1];
	for (int j = 0; j < i; j++) {
		tmp2 = hash_t[j + 1];
		hash_t[j + 1] = tmp1;
		tmp1 = tmp2;
	}
	hash_t[0] = value;
}

// Ищем в кэше элемент. Возвращает номер элемента либо -1.
int find_hash(int value, int* hash_t, int cash_len) {
	for (int i = 0; i < cash_len; i++) {
		if (value == hash_t[i]) {
			replace_hash(hash_t, value, i);
			return i;
		}
	}
	add_hash(hash_t, cash_len, value);
	return NO_FIND;
}

int LRU(int argc, char** argv) {

	////////////////////
	// 1. Input values
	// 2. Create Xash tabl
	// 3. Full Xash tabl and Cash
	// 4. Answer
	/////////////////////
	int cash_len = 0;
	int req_len = 0;
	int value = 0;

	int cash_miss = 0;
	int cash_catch = 0;

	int* hash_t = NULL;
	bool FILE_MODE = OFF;
	char answer[MAX_LEN] = { 0 };

	//1. Input
	std::ifstream file;
	if (argc == 1) {
		std::cin >> cash_len;
		std::cin >> req_len;
		FILE_MODE = OFF;

	}
	else {

		file.open(argv[1]);
		assert(file);

		//answer LRU
		file.seekg(-15, std::ios::end);
		file >> answer;
		std::cout << answer << std::endl;
		file.seekg(0, std::ios::beg);

		//input data
		file >> cash_len;
		file >> req_len;
		FILE_MODE = ON;

		
	}

	//2. Create Hash table
	create_hash(cash_len, &hash_t);

	//3. Full cash and hash table
	for (int i = 0; i < req_len; i++) {

		//assert(scanf("%d", &value) == 1);

		if (FILE_MODE == ON)
			file >> value;
		else
			std::cin >> value;

		if (find_hash(value, hash_t, cash_len) == -1)
			cash_miss++;
		else
			cash_catch++;
	}
	
	file.close();
	//4. Answer
	printf("\nMy alg LRU answer is = [%d]", cash_catch);



	return 0;
}