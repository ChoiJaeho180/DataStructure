#include "MyVector.h"

#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] p; (p)=nullptr;}}

MyVector::MyVector(int capacity) : _Capacity(capacity), _Size(0)
{
	_pMyObject = new MyObject[_Capacity];
}

MyVector::MyVector(const MyVector& other) : _Capacity(other.GetCapacity()), _Size(other.GetSize())
{
	// 해당 객체와 other의 pMyObject가 가리키는 
	// 메모리 영역이 겹치지 않기 위해 할당합니다.
	_pMyObject = new MyObject[_Capacity];
	for (int i = 0; i < _Size; i++)
	{
		_pMyObject[i]._id = other.GetIndexToID(i);
	}
}

MyVector::~MyVector()
{
	if (_Capacity == 0)
		return;
	SAFE_DELETE_ARRAY(_pMyObject);
}

MyVector& MyVector::operator=(const MyVector& other)
{
	if (this != &other)
	{
		// 기존 Capacity 값이 other Capacity 값과 다르다면?
		if (_Capacity != other.GetCapacity())
		{
			// 기존 pMyObject 해제 후 other pMyObject 크기만큼 재할당합니다.
			SAFE_DELETE_ARRAY(_pMyObject);
			_Capacity = other.GetCapacity();
			_pMyObject = new MyObject[_Capacity];
		}
		// other 객체 값으로 초기화합니다.
		_Size = other.GetSize();
		for (int i = 0; i < _Size; i++)
		{
			_pMyObject[i]._id = other.GetIndexToID(i);
		}
	}
	return (*this);
}

void MyVector::Add(int id)
{
	// 할당된 메모리 공간이 가득 찼다면?
	if (_Size >= _Capacity)
	{
		// 메모리를 새로 할당할 경우 _Capacity * 2를 재할당합니다.
		_Capacity = _Capacity * INCREASE_MULTIPLE_CAPACITY;
		ReAllocation();
	}
	_pMyObject[_Size++]._id = id;
}

MyObject* MyVector::FindById(int MyObjectId) const
{
	for (int i = 0; i < _Size; i++)
	{
		// MyObjectId에 해당하는 첫 번째 ID 요소 반환합니다.
		if (_pMyObject[i]._id == MyObjectId)
			return &(_pMyObject[i]);
	}
	// 없을 경우 nullptr 반환합니다.
	return nullptr;
}

void MyVector::TrimToSize()
{
	if (_Size >= _Capacity)
		return;
	_Capacity = _Size;
	ReAllocation();
}

MyObject& MyVector::operator[](size_t index)
{
	if (index >= 0 && _Size > (int)index)
		return _pMyObject[index];
	throw "잘못된 인덱스 참조하였습니다.";
}

std::string MyVector::ToString() const
{
	std::string result;
	for (int i = 0; i < _Size; i++)
	{
		result.append(GetIDToString(_pMyObject[i]._id));
		result.append(", ", STRING_IDENTIFIER_LENGTH);
	}

	if (result.empty() == false)
	{
		result[(result.length() - STRING_IDENTIFIER_LENGTH)] = 0;
	}
	return result;
}

void MyVector::RemoveAll(int MyObjectId)
{
	int Index = 0;
	while (true)
	{
		if (Index >= _Size)
			break;

		if (_pMyObject[Index]._id != MyObjectId)
		{
			Index++;
		}
		else
		{
			RemoveAt(Index);
		}
	}
}

MyVector* MyVector::GroupById(int* numGroups)
{
	// Group 갯수 업데이트합니다.
	(*numGroups) = GetDistinctCount();
	MyVector* pNewVector = new MyVector[(*numGroups)];

	for (int i = 0; i < _Size; i++)
	{
		for (int j = 0; j < (*numGroups); j++)
		{
			// pNewVector의 갯수가 0이거나,
			// 동일한 ID를 가지는 pNewVector(그룹)이 있다면?
			if (pNewVector[j].GetSize() == 0 ||
				_pMyObject[i]._id == pNewVector[j].GetIndexToID(0))
			{
				pNewVector[j].Add(_pMyObject[i]._id);
				break;
			}
		}
	}
	return pNewVector;
}

void MyVector::ReAllocation()
{
	//메모리 재할당
	MyObject* Destroy = _pMyObject;
	_pMyObject = new MyObject[_Capacity];
	for (int i = 0; i < _Size; i++)
	{
		_pMyObject[i] = Destroy[i];
	}
	SAFE_DELETE_ARRAY(Destroy);
}

void MyVector::RemoveAt(const int& Index)
{
	// Remove할 요소를 시작으로 오른쪽에서 왼쪽으로
	// 한칸씩 정렬합니다.
	for (int i = Index; i < (_Size - 1); i++)
	{
		_pMyObject[i] = _pMyObject[(i + 1)];
	}
	_Size--;
}

int MyVector::GetDistinctCount()
{
	MyVector Temp;
	for (int i = 0; i < _Size; i++)
	{
		//ID 값이 Temp 변수에 존재하지 않다면?
		if (CheckExistObjectID(Temp, _pMyObject[i]._id) == true)
			continue;
		Temp.Add(_pMyObject[i]._id);
	}
	return Temp.GetSize();
}

std::string MyVector::GetIDToString(const int& ID) const
{
	std::string result;
	const char* DigitToChar = "0123456789";

	char TempChar[MAX_DIGIT_LENGTH] = { 0 };
	int FillIndex = MAX_DIGIT_LENGTH;

	int TempNum = ID;
	bool bCheckNegativeNum = TempNum < 0;

	// ID 값이 0의 경우를 고려하여 선 명령문 실행, 후 조건 검사하는
	// do ~while 문 사용. 만약 while을 사용하면 조건 검사를 먼저하기
	// 때문에 0은 리턴 값에 포함되지 않습니다.
	do
	{
		TempChar[--FillIndex] = DigitToChar[(abs(TempNum % NUMBER_TYPE))];
		TempNum = (TempNum / NUMBER_TYPE);
	} while (TempNum);

	// ID 값이 Minus( - ) 값을 가질 경우
	if (bCheckNegativeNum == true)
	{
		TempChar[--FillIndex] = '-';
	}

	for (int i = FillIndex; i < MAX_DIGIT_LENGTH; i++)
	{
		result += TempChar[i];
	}
	return result;
}

bool MyVector::CheckExistObjectID(const MyVector& Element, const int& ID)
{
	bool bExist = false;
	for (int i = 0; i < Element.GetSize(); i++)
	{
		if (Element.GetIndexToID(i) != ID)
			continue;
		bExist = true;
		break;
	}
	return bExist;
}
