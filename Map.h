#pragma once
#ifndef MAP_H
#define MAP_H

#include <string>

typedef std::string KeyType;
typedef double ValueType;

class Map {
	struct Node {
		KeyType key;
		ValueType value;
		Node * next;

		Node(KeyType key, ValueType value, Node * next = nullptr) : key(key), value(value) , next(next) {}
	};

	Node * head;
	int numOfPairs;

public:
	Map(); // Create an empty map (i.e., one with no key/value pairs)
	bool empty() const; // Return true if the map is empty, otherwise false
	int size() const; // Return the number of key/value pairs in the map.

	// If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map).
	bool insert(const KeyType & key, const ValueType & value);


	// If key is equal to a key currently in the map, set value to the
	// value in the map that that key maps to, and return true.  Otherwise,
	// make no change to the value parameter of this function and return
	// false.
	bool get(const KeyType & key, ValueType & value) const;

	virtual ~Map();
};


#endif // !MAP_H