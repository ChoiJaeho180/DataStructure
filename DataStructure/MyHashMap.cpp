#include "MyHashMap.h"
MyHashMap::MyHashMap(size_t n)
{
	data = std::vector<int>(n, -1);
}

void MyHashMap::insert(uint value)
{
	int n = data.size();
	data[value % n] = value;
	std::cout << value << "을(를) 삽입했습니다." << std::endl;
}

bool MyHashMap::find(uint value)
{
	int n = data.size();
	return (data[value % n] == value);
}

void MyHashMap::erase(uint value)
{
	int n = data.size();
	if (data[value % n] == value)
	{
		data[value % n] = -1;
		std::cout << value << "을(를) 삭제했습니다." << std::endl;
	}
}
