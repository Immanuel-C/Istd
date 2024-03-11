#include "unordered_map.h"

#include <stdlib.h>
#include "safe/string_safe.h"
#include <stdio.h>

typedef struct _istd_unordered_map_item_t {
	void* key;
	void* value;
	struct _istd_unordered_map_item_t* next;
} _istd_unordered_map_item;

typedef struct {
	_istd_unordered_map_item** items;
	size_t capacity;
	size_t type_size;
	istd_pfn_hash_function hash_function;
} _istd_unordered_map;

istd_unordered_map _istd_unordered_map_create(
	_In_ const size_t type_size,
	_In_ const size_t capacity,
	_In_ istd_pfn_hash_function hash_function
) {
	_istd_unordered_map* map = malloc(sizeof(_istd_unordered_map));

	if (map == istd_nullptr) 
		return istd_nullptr;

	size_t items_size = capacity * sizeof(_istd_unordered_map_item*);
	map->items = malloc(items_size);

	if (map->items == istd_nullptr) {
		free(map);
		return istd_nullhnd;
	}

	map->capacity = capacity;
	map->type_size = type_size;
	map->hash_function = hash_function;

	for (size_t i = 0; i < capacity; i++) 
		map->items[i] = istd_nullptr;

	return (istd_unordered_map)map;
}

static inline void istd_stdcall _istd_free_item(
	_Pre_valid_ _Post_invalid_ _istd_unordered_map_item* item
) {
	free(item->key);
	free(item->value);
	free(item);
}

static _istd_unordered_map_item* istd_stdcall _istd_create_item(
	_Inout_ _istd_unordered_map* map,
	_In_ const void* key,
	_In_ size_t key_size,
	_In_ const void* value
) {
	_istd_unordered_map_item* item = malloc(sizeof(_istd_unordered_map_item));

	if (item == istd_nullptr) 
		return istd_nullptr;

	item->key = malloc(key_size);

	if (item->key == istd_nullptr) {
		free(item);
		return istd_nullptr;
	}

	item->value = malloc(map->type_size);

	if (item->value == istd_nullptr) {
		free(item->key);
		free(item);
		return istd_nullptr;
	}

	item->next = istd_nullptr;

	if (istd_memcpy_safe(item->key, key_size, key, key_size) != ISTD_ENONE || 
		istd_memcpy_safe(item->value, map->type_size, value, map->type_size) != ISTD_ENONE) {
		_istd_free_item(item);
		return istd_nullptr;
	}

	return item;
}

istd_result istd_unordered_map_insert(
	_Inout_ istd_unordered_map map,
	_In_ const void* key,
	_In_ size_t key_size,
	_In_ const void* value
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;
	
	_istd_unordered_map_item* item = _istd_create_item(_map, key, key_size, value);

	if (item == istd_nullptr)
		return ISTD_RESULT_ALLOCATION_FAILED;

	size_t index = _map->hash_function(key, key_size) % _map->capacity;

	// Empty slot
	if (_map->items[index] == istd_nullptr) 
		_map->items[index] = item;
	// Collision
	else 
		_map->items[index]->next = item;

	return ISTD_RESULT_SUCCESS;
}

istd_result istd_unordered_map_erase(
	_Inout_ istd_unordered_map map,
	_In_	const void* key,
	_In_	size_t key_size
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;

	size_t index = _map->hash_function(key, key_size) % _map->capacity;

	_istd_unordered_map_item* item = _map->items[index];
	_istd_unordered_map_item* prev = istd_nullptr;

	while (item != istd_nullptr) {
		if (item->key == istd_nullptr	|| 
			item->value == istd_nullptr || 
			memcmp(item->key, key, key_size) != 0
		) {
			prev = item;
			item = item->next;
			continue;
		}

		// The item is the head
		if (prev == istd_nullptr) 
			_map->items[index] = item->next;
		// The item is not the head
		else
			prev->next = item->next;

		_istd_free_item(item);

		return ISTD_RESULT_SUCCESS;
	}

	return ISTD_RESULT_NOT_FOUND;
}

void* _istd_unordered_map_search(
	_In_ istd_unordered_map map,
	_In_ const void* key,
	_In_ const size_t key_size
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;

	size_t index = _map->hash_function(key, key_size) % _map->capacity;

	_istd_unordered_map_item* item = _map->items[index];

	if (item == istd_nullptr)
		return istd_nullptr;

	while (item != istd_nullptr) {
		if (memcmp(item->key, key, key_size) == 0)
			return item->value;

		item = item->next;
	}

	return istd_nullptr;
}

istd_result istd_unordered_map_free(
	_Pre_valid_ _Post_invalid_ istd_unordered_map map
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;
	
	if (_map == istd_nullptr)
		return ISTD_RESULT_PARAMETER_NULL;

	for (size_t i = 0; i < _map->capacity; i++) {
		_istd_unordered_map_item* item = _map->items[i];

		if (item == istd_nullptr)
			continue;

		_istd_unordered_map_item* tmp = istd_nullptr;

		while (item != istd_nullptr) {
			tmp = item;

			item = item->next;

			_istd_free_item(tmp);
		}

	}

	free(_map->items);
	free(_map);

	return ISTD_RESULT_SUCCESS;
}