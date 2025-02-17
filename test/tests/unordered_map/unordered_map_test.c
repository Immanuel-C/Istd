#include "unordered_map_test.h"

#include "hash_map/unordered_map.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

size_t hash_function(const void* buf, size_t len) {
	const uint8_t* bytes = (const uint8_t*)buf;

	size_t hash = 0;

	for (size_t i = 0; i < len; i++) {
		hash += bytes[i];
		hash *= len;
	}

	return hash;
}

istd_test_msg test_unordered_map(void) {
	istd_test_msg msg = { 0 };

	istd_result result;

	istd_unordered_map map = istd_unordered_map_create(int, 3, hash_function, istd_nullptr);

	if (map == istd_nullhnd) {
		msg.err_msg = "Failed to create map.";
	}

	const char* key = "Hello!";
	const char* key1 = "hwf!";
	const char* key2 = "yello! 2434";
	int val = 100;
	result = istd_unordered_map_insert(map, key, (strlen(key) + 1) * sizeof(char), &val);

	if (result == ISTD_RESULT_ALLOCATION_FAILED) {
		msg.err_msg = "Failed to insert new pair into map";
		return msg;
	}

	printf("Inserted: %i\n", val);

	val += 50;
	result = istd_unordered_map_insert(map, key1, strlen(key1) + 1, &val);

	if (result == ISTD_RESULT_ALLOCATION_FAILED) {
		msg.err_msg = "Failed to insert new pair into map";
		return msg;
	}
	
	printf("Inserted: %i\n", val);


	val += 150;
	result = istd_unordered_map_insert(map, key2, strlen(key2) + 1, &val);

	if (result == ISTD_RESULT_ALLOCATION_FAILED) {
		msg.err_msg = "Failed to insert new pair into map";
		return msg;
	}

	printf("Inserted: %i\n", val);

	size_t key_size = (strlen(key) + 1) * sizeof(char);
	int* pval = istd_unordered_map_search(int, map, key, key_size);
	if (pval == istd_nullptr) {
		msg.err_msg = "Searched for value but couldn't find it";
		return msg;
	}
		
	printf("Found: %i\n", *pval);

	pval = istd_unordered_map_search(int, map, key1, strlen(key1) + 1);

	if (pval == istd_nullptr) {
		msg.err_msg = "Searched for value but couldn't find it";
		return msg;
	}

	printf("Found: %i\n", *pval);

	pval = istd_unordered_map_search(int, map, key2, strlen(key2) + 1);

	if (pval == istd_nullptr) {
		msg.err_msg = "Searched for value but couldn't find it";
		return msg;
	}

	printf("Found: %i\n", *pval);

	result = istd_unordered_map_erase(map, key, strlen(key) + 1);

	if (result == ISTD_RESULT_NOT_FOUND) {
		msg.err_msg = "Failed to erase a pair from the map. The function could not find it.";
		return msg;
	}

	result = istd_unordered_map_erase(map, key1, strlen(key1) + 1);

	if (result == ISTD_RESULT_NOT_FOUND) {
		msg.err_msg = "Failed to erase a pair from the map. The function could not find it.";
		return msg;
	}


	pval = istd_unordered_map_search(int, map, key1, strlen(key1) + 1);

	if (pval != istd_nullptr) {
		msg.err_msg = "Found a pair that should be deleted.";
		return msg;
	}

	if (istd_unordered_map_free(map) != ISTD_RESULT_SUCCESS) {
		msg.err_msg = "Failed to free map!";
		return msg;
	}

	msg.passed = true;

	return msg;
}
