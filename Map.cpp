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

bool Map::update(const KeyType & key, const ValueType & value) {
	Node * iterator = head;

	// Check to see if key exists in the linked-list
	while (iterator != nullptr) {
		if (iterator->key == key) {
			iterator->value = value;
			return true;
		}
		else
			iterator = iterator->next;
	}

	// key isn't in the linked-list
	return false;
}

bool Map::insertOrUpdate(const KeyType & key, const ValueType & value) {
	Node * iterator = head;

	// Check to see if key exists in the linked-list
	while (iterator != nullptr) {
		if (iterator->key == key) {
			iterator->value = value;
			return true;
		}
		else
			iterator = iterator->next;
	}

	// key isn't in the linked-list
	return insert(key, value);
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

bool Map::erase(const KeyType & key) {
	if (head == nullptr)
		return false;

	Node * iterator = head;

	// Check if first node has the matching key
	if (iterator->key == key) {
		head = iterator->next;
		delete iterator;
		numOfPairs--;
		return true;
	}
	else {
		while (iterator->next != nullptr) {
			if (iterator->next->key == key) {
				Node * nodeToErase = iterator->next;
				iterator->next = iterator->next->next;
				delete nodeToErase;
				numOfPairs--;
				return true;
			}
			iterator = iterator->next;
		}
	}


	// key isn't in the linked-list
	return false;
}

bool Map::contains(const KeyType & key) const {
	Node * iterator = head;

	// Check to see if key exists in the linked-list
	while (iterator != nullptr) {
		if (iterator->key == key) 	
			return true;		
		else
			iterator = iterator->next;
	}

	// key isn't in the linked-list
	return false;
}

bool Map::get(int i, KeyType & key, ValueType & value) const {
	if (i < 0 || i >= numOfPairs)
		return false;

	Node * iterator = head;

	// Move iterator to the i-th Node
	for (int k = 0; iterator != nullptr && k < i; k++)
		iterator = iterator->next;

	key = iterator->key;
	value = iterator->value;
	return true;
}

void Map::swap(Map & other) {
	size_t numOfOldPairs = numOfPairs;
	KeyType * oldKeys = new KeyType[numOfOldPairs];
	ValueType * oldValues = new ValueType[numOfOldPairs];

	for (size_t i = 0; i < numOfOldPairs; i++)
		get(i, oldKeys[i], oldValues[i]);
	
	// Delete all Nodes
	for (size_t i = 0; i < numOfOldPairs; i++) {
		erase(oldKeys[i]);
	}

	// Copy over the other Map's Nodes to this Map
	for (size_t i = 0; i < other.numOfPairs; i++) {
		KeyType key;
		ValueType value;
		other.get(i, key, value);

		insert(key, value);
	}

	// Delete the other Map's Nodes
	while(other.size() > 0) {
		KeyType keyToErase;
		ValueType value;
		other.get(0, keyToErase, value);

		other.erase(keyToErase);
	}

	// Copy over this Map's old key/value pairs to the other Map
	for(size_t i = 0; i < numOfOldPairs; i++) 
		other.insert(oldKeys[i], oldValues[i]);
}

void Map::dump() const {
	for (size_t i = 0; i < numOfPairs; i++) {
		KeyType key;
		ValueType value;
		get(i, key, value);
		std::cerr << key << ": " << value << '\n';
	}
	std::cerr << '\n';
}

Map::Map(const Map & RHS) {
	// Copy RHS's Nodes over
	for (size_t i = 0; i < RHS.numOfPairs; i++) {
		KeyType key;
		ValueType value;
		RHS.get(i, key, value);

		insert(key, value);
	}
}

const Map & Map::operator = (const Map & RHS) {
	// Delete all LHS's Nodes
	while (numOfPairs > 0) {
		KeyType keyToErase;
		ValueType value;
		get(0, keyToErase, value);

		erase(keyToErase);
	}

	// Copy RHS's Nodes over
	for (size_t i = 0; i < RHS.numOfPairs; i++) {
		KeyType key;
		ValueType value;
		RHS.get(i, key, value);

		insert(key, value);
	}

	return *this;
}

Map::~Map() {
	Node * iterator = head;

	while (iterator != nullptr) {
		Node * nodeToDelete = iterator;
		iterator = iterator->next;
		delete nodeToDelete;
	}
}

