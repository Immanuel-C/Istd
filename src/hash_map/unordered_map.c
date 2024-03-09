#include "unordered_map.h"

#include <stdlib.h>
#include "safe/string_safe.h"

typedef struct _istd_unordered_map_item_t {
	size_t key;
	void* value;
} _istd_unordered_map_item;

typedef struct _istd_unordered_map_t {
	_istd_unordered_map_item** items;
	size_t length;
	size_t capacity;
	size_t type_size;
	istd_pfn_hash_function hash_function;
} _istd_unordered_map;

istd_unordered_map _istd_unordered_map_create(
	_In_ const size_t type_size,
	_In_ const size_t capacity,
	_In_ istd_pfn_hash_function hash_function
) {
	_istd_unordered_map* map = (_istd_unordered_map*)malloc((size_t)sizeof(_istd_unordered_map));

	if (!map) return istd_nullptr;

	map->items = calloc(capacity, sizeof(_istd_unordered_map_item*));

	if (!map->items) { 
		free(map);
		return istd_nullptr; 
	}

	map->type_size = type_size;
	map->length = 0;
	map->capacity = capacity;
	map->hash_function = hash_function;

	return (istd_unordered_map)map;
}

int istd_unordered_map_insert(
	_Inout_ istd_unordered_map map,
	_In_ const void* key,
	_In_ size_t key_size,
	_In_ const void* value
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;

	if (_map == istd_nullptr) return ISTD_EFAULT;
	if (_map->capacity == _map->length) return ISTD_ENOMEM;

	_istd_unordered_map_item** item = &_map->items[_map->length];

	(*item) = malloc(sizeof(_istd_unordered_map_item));
	
	if ((*item) == istd_nullptr) return ISTD_EFAULT;

	(*item)->key = _map->hash_function(key, key_size);

	(*item)->value = malloc(_map->type_size);

	if ((*item)->value == istd_nullptr) {
		free((*item));
		return ISTD_EFAULT; 
	}

	istd_memcpy_safe((*item)->value, _map->type_size, value, _map->type_size);

	_map->length++;

	return 0;
}

void* istd_unordered_map_search(
	_Inout_ istd_unordered_map map,
	_In_	const void* key,
	_In_	const size_t key_size
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;

	if (_map == istd_nullptr || key == istd_nullptr || key_size == 0)
		return istd_nullptr;

	for (size_t i = 0; i < _map->length; i++) 
		if (_map->items[i]->key == _map->hash_function(key, key_size)) return _map->items[i]->value;

	return istd_nullptr;
}

int istd_unordered_map_free(
	_Inout_ istd_unordered_map* map
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)(*map);

	if (_map == istd_nullptr || map == istd_nullptr)
		return ISTD_EFAULT;

	for (size_t i = 0; i < _map->length; i++) {
		free(_map->items[i]->value);
		free(_map->items[i]);
	}

	free(_map->items);
	free(_map);
	map = istd_nullptr;
}

