#pragma once
#include <string>
//-------------------------------------------------------------------------------------------------
// MyVector 가 관리하는 오브젝트
//-------------------------------------------------------------------------------------------------

struct MyObject
{
    int _id = -1;
};

class MyVector
{
private:
    // 메모리에 할당된 용량의 크기입니다.
    int             _Capacity;

    // 유효한 요소들의 갯수입니다.
    int             _Size;

    // 요소들의 시작 주소를 가리키는 변수입니다.
    MyObject* _pMyObject;

    // Capacity default 값이며, 파라미터로 capacity 미전달 시 해당
    // 값으로 초기화됩니다.
    static const int DEFAULT_CAPACITY = 16;

    // Capacity 값이 부족할 시 해당 변수를 이용하여 증가합니다.
    static const int INCREASE_MULTIPLE_CAPACITY = 2;

    // int to string 변환 시 최대 문자열 길이입니다.
    static const int MAX_DIGIT_LENGTH = 12;

    // 숫자 타입니다. ex) 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    static const int NUMBER_TYPE = 10;

    // _pMyObject의 요소를 String으로 변환 시 요소 사이에
    // 추가되는 식별자 길이입니다.
    static const int STRING_IDENTIFIER_LENGTH = 3;

public:

    // Constructor.
    MyVector(int capacity = DEFAULT_CAPACITY);
    // Copy constructor.
    MyVector(const MyVector& other);

    // Assignment operator.
    MyVector& operator=(const MyVector& other);
    // Destructor.
    ~MyVector();

public:

    // Creates a new MyObject instance with the given ID, and appends it to the end of this vector.
    void                Add(int id);

    // Returns the first occurrence of MyObject instance with the given ID.
    // Returns nullptr if not found.
    MyObject* FindById(int MyObjectId) const;

    // Trims the capacity of this vector to current size.
    void                TrimToSize();

    // Returns the MyObject instance at the specified index.
    MyObject& operator[](size_t index);

    // Returns string representation of the vector.
    std::string         ToString() const;

    // Remove all MyObject instances with the given ID in this vector.
    void                RemoveAll(int MyObjectId);

    // Returns a newly allocated array of MyVector objects,
    // each of whose elements have the same "_id" value of the MyObject struct.
    // The 'numGroups' is an out parameter, and its value should be set to
    // the size of the MyVector array to be returned.
    MyVector* GroupById(int* numGroups);
private:

    //Capacity 값 변경 시 재할당합니다.
    //Add, TrimToSize 함수에서 사용됩니다.
    void                ReAllocation();

    // _pMyObject에 존재하는 Array Index를 제거합니다.
    void                RemoveAt(const int& Index);

    // _pMyObject값에 ID 값 존재 유무 체크합니다.
    bool                CheckExistObjectID(const MyVector& Element, const int& ID);

    // _pMyObject에 존재하는 ID 중복 값을 제외한 Count를 리턴합니다.
    int                 GetDistinctCount();

    // ID의 자료형인 int를 String으로 변환하여 리턴합니다.
    std::string         GetIDToString(const int& ID) const;
public:
    // Returns current capacity of this vector.
    inline int          GetCapacity() const { return _Capacity; }
    // Returns current size of this vector.
    inline int          GetSize() const { return _Size; }
    // Index를 이용하여 _pMyObject의 ID 값을 얻습니다.
    inline int          GetIndexToID(const int& Index) const { return GetSize() != 0 ? _pMyObject[Index]._id : -1; }

};