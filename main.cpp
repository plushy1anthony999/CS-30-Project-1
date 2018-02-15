#include "Map.h"
#include <assert.h>

int main() {
	{
		Map map;
		map.insert("Anthony", 12);
		map.insert("Billy", 1);
		map.insert("Anthony", 11);

		ValueType value;
		assert(map.size() == 2 && map.get("Anthony", value) == true && value == 12);
	}

	return 0;
}