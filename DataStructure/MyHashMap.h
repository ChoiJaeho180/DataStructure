#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using uint = unsigned int;

class MyHashMap
{
	std::vector<std::list<int>> data;

public:
	MyHashMap(size_t n);
	
	void insert(uint value);
	
	bool find(uint value);

	void erase(uint value);
	
};