#include "MyHashMap.h"
MyHashMap::MyHashMap(size_t n)
{
	data.resize(n);
}
void MyHashMap::insert(uint value)
{
	int n = data.size();
	data[value % n].push_back(value);
	std::cout << value << "을(를) 삽입했습니다." << std::endl;
}

bool MyHashMap::find(uint value)
{
	int n = data.size();
	auto& entries = data[value % n];
	return std::find(entries.begin(), entries.end(), value) != entries.end();
}

void MyHashMap::erase(uint value)
{
	int n = data.size();
	auto& entries = data[value % n];
	auto iter = std::find(entries.begin(), entries.end(), value);
	if (iter != entries.end())
	{
		entries.erase(iter);
		std::cout << value << "을(를) 삭제했습니다." << std::endl;
	}
}
