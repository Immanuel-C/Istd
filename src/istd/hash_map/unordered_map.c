#include "unordered_map.h"

#include "allocator/allocator.h"

#include <string.h>
#include <stdio.h>

typedef struct __istd_unordered_map_item_t {
	void* key;
	size_t key_size;
	void* value;
	struct _istd_unordered_map_item_t* next;
} __istd_unordered_map_item;

typedef struct {
	__istd_unordered_map_item** items;
	size_t capacity;
	size_t type_size;
	istd_pfn_hash_function hash_function;
	istd_allocator allocator;
} _istd_unordered_map;

istd_unordered_map __istd_unordered_map_create(
	const size_t type_size,
	const size_t capacity,
	istd_pfn_hash_function hash_function,
	istd_allocator* allocator
) {
	istd_allocator alloc = istd_check_allocator(allocator);

	_istd_unordered_map* map = alloc.malloc(sizeof(_istd_unordered_map));

	if (map == istd_nullptr) 
		return istd_nullptr;

	size_t items_size = capacity * sizeof(__istd_unordered_map_item*);
	map->items = alloc.malloc(items_size);

	if (map->items == istd_nullptr) {
		alloc.free(map);
		return istd_nullhnd;
	}

	map->capacity = capacity;
	map->type_size = type_size;
	map->hash_function = hash_function;
	map->allocator = alloc;

	for (size_t i = 0; i < capacity; i++) 
		map->items[i] = istd_nullptr;

	return (istd_unordered_map)map;
}

static istd_force_inline void __istd_free_item(
	_istd_unordered_map* map,
	__istd_unordered_map_item* item
) {
	map->allocator.free(item->key);
	map->allocator.free(item->value);
	map->allocator.free(item);
}

static __istd_unordered_map_item* __istd_create_item(
	_istd_unordered_map* map,
	const void* key,
	size_t key_size,
	const void* value
) {
	__istd_unordered_map_item* item = map->allocator.malloc(sizeof(__istd_unordered_map_item));

	if (item == istd_nullptr) 
		return istd_nullptr;

	item->key = map->allocator.malloc(key_size);

	if (item->key == istd_nullptr) {
		map->allocator.free(item);
		return istd_nullptr;
	}

	item->value = map->allocator.malloc(map->type_size);

	if (item->value == istd_nullptr) {
		map->allocator.free(item->key);
		map->allocator.free(item);
		return istd_nullptr;
	}

	item->key_size = key_size;
	item->next = istd_nullptr;

	memcpy(item->key, key, key_size); 
	memcpy(item->value, value, map->type_size);

	return item;
}

istd_result istd_unordered_map_insert(
	istd_unordered_map map,
	const void* key,
	size_t key_size,
	const void* value
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;
	
	__istd_unordered_map_item* item = __istd_create_item(_map, key, key_size, value);

	if (item == istd_nullptr) {

		return ISTD_RESULT_ALLOCATION_FAILED;
	}

	size_t index = _map->hash_function(key, key_size) % _map->capacity;

	// Empty slot
	if (_map->items[index] == istd_nullptr) 
		_map->items[index] = item;
	// Collision
	else 
		// MSVC and both produce warnings when trying to cast to (struct __istd_unordered_map_item_t*) and setting next to it.
		// Setting but casting to void does not produce this error. 
		_map->items[index]->next = (void*)item;

	return ISTD_RESULT_SUCCESS;
}

istd_result istd_unordered_map_erase(
	istd_unordered_map map,
	const void* key,
	size_t key_size
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;

	size_t index = _map->hash_function(key, key_size) % _map->capacity;

	__istd_unordered_map_item* item = _map->items[index];
	__istd_unordered_map_item* prev = istd_nullptr;

	while (item != istd_nullptr) {
		if (item->key == istd_nullptr	|| 
			item->value == istd_nullptr || 
			memcmp(item->key, key, key_size) != 0
		) {
			prev = item;
			item = (__istd_unordered_map_item*)item->next;
			continue;
		}

		// The item is the head
		if (prev == istd_nullptr) 
			_map->items[index] = (__istd_unordered_map_item*)item->next;
		// The item is not the head
		else
			prev->next = item->next;

		__istd_free_item(_map, item);

		return ISTD_RESULT_SUCCESS;
	}

	return ISTD_RESULT_NOT_FOUND;
}

void* __istd_unordered_map_search(
	istd_unordered_map map,
	const void* key,
	const size_t key_size
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;

	size_t index = _map->hash_function(key, key_size) % _map->capacity;

	__istd_unordered_map_item* item = _map->items[index];

	if (item == istd_nullptr)
		return istd_nullptr;

	while (item != istd_nullptr) {
		// I added this check because address sanitizer would flag a buffer overflow if memcmp would read after the buf2.
		if (item->key_size > key_size || item->key_size < key_size) {
			item = (__istd_unordered_map_item*)item->next;
			continue;
		}

		if (memcmp(item->key, key, key_size) == 0)
			return item->value;

		item = (__istd_unordered_map_item*)item->next;
	}

	return istd_nullptr;
}

size_t istd_unordered_map_capacity(
	istd_unordered_map map
) {
	return ((_istd_unordered_map*)map)->capacity;
}

istd_result istd_unordered_map_free(
	istd_unordered_map map
) {
	_istd_unordered_map* _map = (_istd_unordered_map*)map;
	
	if (_map == istd_nullptr)
		return ISTD_RESULT_PARAMETER_NULL;

	for (size_t i = 0; i < _map->capacity; i++) {
		__istd_unordered_map_item* item = _map->items[i];

		if (item == istd_nullptr)
			continue;

		__istd_unordered_map_item* tmp = istd_nullptr;

		while (item != istd_nullptr) {
			tmp = item;

			item = (__istd_unordered_map_item*)item->next;

			__istd_free_item(_map, tmp);
		}

	}

	_map->allocator.free(_map->items);
	_map->allocator.free(_map);

	return ISTD_RESULT_SUCCESS;
}
