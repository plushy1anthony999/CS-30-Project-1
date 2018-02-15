#include "Map.h"


Map::Map() : head(nullptr), numOfPairs(0) {}

int Map::size() const {
	return numOfPairs;
}

bool Map::empty() const {
	return (head == nullptr);
}

bool Map::insert(const KeyType & key, const ValueType & value) {
	Node * iterator = head;

	// Check to see if key already exists in the linked-list
	while (iterator != nullptr) {
		if (iterator->key == key)
			return false;
		else
			iterator = iterator->next;
	}

	// Key doesn't already exist in map, so insert it at start of linked-list
	head = new Node(key, value, head);
	numOfPairs++;
	return true;
}

bool Map::get(const KeyType & key, ValueType & value) const {
	Node * iterator = head;

	// Check to see if key exists in the linked-list
	while (iterator != nullptr) {
		if (iterator->key == key) {
			value = iterator->value;
			return true;
		}
		else
			iterator = iterator->next;
	}

	// key isn't in the linked-list
	return false;
}

Map::~Map()
{
}
