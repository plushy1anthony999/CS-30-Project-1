#include "Map.h"
#include <assert.h>

int main() {
	{
		Map map;
		map.insert("Anthony", 12);
		map.insert("Billy", 1);
		map.insert("Anthony", 11);

		ValueType value;
		assert(map.empty() == false && map.size() == 2 && map.get("Anthony", value) == true && value == 12);		
		assert(map.update("Bob", 11) == false && map.size() == 2);
		assert(map.update("Anthony", 100) == true && map.get("Anthony", value) == true && value == 100);
		assert(map.erase("Emily") == false && map.size() == 2);

		// value should remain unchanged after map.get() fails
		assert(map.erase("Anthony") == true && map.size() == 1 && map.get("Anthony", value) == false && value == 100); 

		assert(map.contains("Billy") && !map.contains("Anthony"));
		assert(map.insertOrUpdate("Billy", 999) == true && map.get("Billy", value) == true && value == 999);
		assert(map.insertOrUpdate("Anthony", 987) == true && map.get("Anthony", value) == true && value == 987);
		assert(map.insertOrUpdate("", 0) == true && map.size() == 3 && map.get("", value) == true && value == 0);

		for (int i = 0; i < map.size(); i++) {
			KeyType key;
			ValueType value;
			assert(map.get(i, key, value) == true);
		}
		KeyType key = "";
		assert(map.get(map.size(), key, value) == false && value == 0 && key == "");
		assert(map.get(-1, key, value) == false && value == 0 && key == "");

		Map map2;
		map.swap(map2);

		assert(map.empty() == true && map.get("Billy", value) == false);
		assert(
			map2.size() == 3 &&
			map2.get("Billy", value) == true && value == 999 &&
			map2.get("Anthony", value) == true && value == 987 &&
			map2.get("", value) == true && value == 0
		);
	}
	{
		Map m;
		m.insert("A", 10);
		m.insert("B", 44);
		m.insert("C", 10);
		std::string all;
		double total = 0;
		for (int n = 0; n < m.size(); n++)
		{
			std::string k;
			double v;
			m.get(n, k, v);
			all += k;
			total += v;
		}

		assert(
			all == "ABC" ||
			all == "ACB" ||
			all == "BAC" ||
			all == "BCA" ||
			all == "CAB" ||
			all == "CBA"
		);
		assert(total == 64);
	}
	{
		Map gpas;
		gpas.insert("Fred", 2.956);
		gpas.insert("Ethel", 3.538);
		double v;
		std::string k1;
		assert(gpas.get(1, k1, v) && (k1 == "Fred" || k1 == "Ethel"));
		std::string k2;
		assert(gpas.get(1, k2, v) && k2 == k1);
	}
	{
		Map gpas;
		gpas.insert("Fred", 2.956);
		assert(!gpas.contains(""));
		gpas.insert("Ethel", 3.538);
		gpas.insert("", 4.000);
		gpas.insert("Lucy", 2.956);
		assert(gpas.contains(""));
		gpas.erase("Fred");
		assert(gpas.size() == 3 && gpas.contains("Lucy") && gpas.contains("Ethel") &&
			gpas.contains(""));
	}
	{
		Map m1;
		m1.insert("Fred", 2.956);
		Map m2;
		m2.insert("Ethel", 3.538);
		m2.insert("Lucy", 2.956);
		m1.swap(m2);

		m1.dump();
		m2.dump();
		assert(
			m1.size() == 2 &&
			m1.contains("Ethel") &&
			m1.contains("Lucy") &&
			m2.size() == 1
			//m2.contains("Fred")
		);
	}
	{
		Map map1;
		map1.insert("Billy", 10);
		map1.insert("Anthony", 11);

		Map map2(map1);

		assert(map2.size() == 2 && map1.size() == 2);
		for (size_t i = 0; i < map1.size(); i++) {
			KeyType key;
			ValueType value;
			map1.get(i, key, value);
			
			assert(map2.contains(key));
		}
	}
	{
		Map map1;
		map1.insert("Billy", 10);
		map1.insert("Anthony", 11);

		Map map2;
		map2.insert("Emily", 100);
		map2.insert("", 1000);
		map2.insert("Bob", 1032);

		map1 = map2;

		assert(map1.size() == 3 && map2.size() == 3);
		for (size_t i = 0; i < map1.size(); i++) {
			KeyType key;
			ValueType value;
			map1.get(i, key, value);

			assert(map2.contains(key));
		}
	}

	return 0;
}