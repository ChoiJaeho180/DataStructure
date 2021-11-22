#include <iostream>
#include <vector>

using uint = unsigned int;

class MyHashMap
{
	std::vector<int> data;

public:
	MyHashMap(size_t n);
	
	void insert(uint value);
	
	bool find(uint value);

	void erase(uint value);
	
};