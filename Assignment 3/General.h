#pragma once
#pragma once
#include <iostream>
using namespace std;

#define BasePath "GraphData.csv";
int V = 30;

//
//template <class data>
//class Array {
//public:
//	short int size;
//	const bool Sorted;
//	short int Index;
//	data* Arr;
//
//public:
//	Array(const short int, bool = true);
//
//	void Insert(const data);
//	bool Search(const data);
//	void CopyArr(Array<data>);
//	bool IsFull();
//	void ClearArray();
//	data& operator[](const int);
//	void operator=(const Array<data>&);
//
//	~Array();
//};
//
//template<class data>
//void InitArray(data* Arr, const int size, const data val = NULL)
//{
//	for (int i = 0; i < size; i++)
//		Arr[i] = val;
//}
//
//template <class data>
//data NIL(data dat)
//{
//	return -1;
//}
//
//template<class data>
//inline Array<data>::Array(const short int Len, bool Def) : size(Len), Sorted(Def)
//{
//	Index = -1;
//	Arr = new data[size];
//	InitArray(Arr, size, NIL(Arr[0]));
//}
//
//template <class data>
//void ShiftRight(data*& Arr, const int index, int size)
//{
//	for (int i = size - 1; i >= index; i++)
//		Arr[i] = Arr[i - 1];
//}
//
//template <class data>
//void InsertSorted(data*& Array, int index)
//{
//	data temp;
//	while (index > 0 && Array[index] < Array[index - 1])
//	{
//		temp = Array[index];
//		Array[index] = Array[index - 1];
//		Array[index - 1] = temp;
//		index--;
//	}
//}
//
//template<class data>
//inline void Array<data>::CopyArr(Array<data> Other)
//{
//	for (int i = 0; i < Other.Index; i++)
//		this->Arr[++Index] = Other[i];
//}
//
//template<class data>
//inline void Array<data>::Insert(const data val)
//{
//	if (IsFull())
//		return;
//
//	Arr[++Index] = val;
//	if (Sorted) InsertSorted(Arr, Index);
//}
//
//template<class data>
//void Shiftleft(data*& Array, int index, const int size)
//{
//	while (index < size)
//		Array[index] = Array[++index];
//	Array[index - 1] = NIL(Array[0]);
//}
//
//template<class data>
//inline bool Array<data>::Search(const data val)
//{
//	for (int i = 0; i <= Index && Arr[i] != NIL(Arr[i]); i++)
//		if (Arr[i] == val)
//			return true;
//	return false;
//}
//
//template<class data>
//inline bool Array<data>::IsFull()
//{
//	return (Index == size - 1);
//}
//
//template<class data>
//void Array<data>::ClearArray()
//{
//}
//
//template<class data>
//inline data& Array<data>::operator[](const int index)
//{
//	return Arr[index];
//}
//
//template<class data>
//void Array<data>::operator=(const Array<data>& Other)
//{
//	data Val;
//	this->~Array();
//	Array<data>* temp = new Array<data>(Other.size, Other.Sorted);
//
//	for (int i = 0; i < temp->size; i++)
//	{
//		Val = Other.Arr[i];
//		temp->Insert(Val);
//	}
//
//	this->Arr = temp->Arr;
//	this->size = temp->size;
//	this->Index = temp->Index;
//	//this->Sorted = temp->Sorted;
//	temp = nullptr;
//}
//
//template<class data>
//inline Array<data>::~Array()
//{
//	delete[] Arr;
//	Index = -1;
//	size = 0;
//}
//=================================================//

template <typename data>
class Queue {
	class QNode {
	public:
		data Data;
		QNode* Next;

		QNode(const data val, QNode* curr = nullptr)
		{
			Data = val;
			Next = curr;
		}
	};

private:
	QNode* Front;
	QNode* Rear;

public:

	typedef Queue<data>* QPtr;
	typedef QNode* QNPtr;

	Queue();
	void Display();
	bool IsEmpty();
	void  Dequeue();
	const data Peek();
	void Dequeue(data);
	void Enqueue(const data);
	~Queue();

};

template<typename data>
inline Queue<data>::Queue()
{
	Front = Rear = nullptr;
}

template<typename data>
inline void Queue<data>::Enqueue(const data val)
{
	QNode* curr = new QNode(val);
	if (IsEmpty())
	{
		Front = Rear = curr;
		return;
	}

	Rear->Next = curr;
	Rear = curr;
}

template<typename data>
inline void Queue<data>::Dequeue()
{
	if (IsEmpty())
		return;
	else if (Front == Rear)
	{
		delete Rear;
		Front = Rear = nullptr;
		return;
	}

	QNode* curr = Front;
	Front = Front->Next;
	delete curr;
}

template<typename data>
inline const data Queue<data>::Peek()
{
	if (!IsEmpty())
		return Front->Data;
	return NULL;
}

template<typename data>
inline void Queue<data>::Dequeue(data ResVar)
{
	ResVar = Front->Data;
	this->Dequeue();
}

template<typename data>
inline void Queue<data>::Display()
{
	for (QNode* curr = Front; curr != nullptr; curr = curr->Next)
		std::cout << curr->Data << "  ";
}

template<typename data>
inline bool Queue<data>::IsEmpty()
{
	return (Front == nullptr) && (Rear == nullptr);
}

template<typename data>
inline Queue<data>::~Queue()
{
	while (Front != nullptr)
		Dequeue();

	Front = Rear = nullptr;
}
//====================================================//

template <typename data>
struct LLNode {
	data Data;
	LLNode* Next;

	LLNode(data dataVal = 0, LLNode* next = nullptr) : Data(dataVal)
	{
		Next = next;
	}
	friend class Graph;
};

template <typename data>
class LinkedList {
	LLNode<data>* Head;
	LLNode<data>* Tail;

	int RecursiveLength(const LLNode<data>*);

public:
	typedef LLNode<data>* LLNptr;
	typedef LinkedList<data>* LLPtr;

	LinkedList();
	bool IsEmpty();
	const data Front();

	void Insert(const data);
	void InsertH(const data);
	void InsertAt(const data, const int);
	void InsertSorted(const data);
	void Delete();
	void DeleteAt(const int);
	void DeleteValue(const data);

	const int Length();
	bool Search(const data);
	string MakeLinkLine(string*&);
	const data ValueAt(const int);
	void Display(string*, const int);
	void Display();

	~LinkedList();

	friend class Graph;
};

template <typename data>
LinkedList<data>::LinkedList()
{
	Head = nullptr;
	Tail = nullptr;
}

template <typename data>
void LinkedList<data>::InsertAt(const data dataVal, const int index)
{
	LLNode<data>* Current = Head;
	if (Head == nullptr || index == 0)
		Insert(dataVal);
	else
	{
		for (int i = 1; Current->Next != nullptr && i < index; i++)
			Current = Current->Next;

		LLNode<data>* Post = Current->Next;
		Current->Next = new LLNode<data>(dataVal);
		Current->Next->Next = Post;
	}
}

template<typename data>
inline void LinkedList<data>::InsertSorted(const data val)
{
	if (Head == nullptr || Head->Data >= val) 
	{
		Head = new LLNode<data>(val, Head);
		Tail = Head->Next;
	}
	else 
	{
		LLNode<data>* Current = Head;
		while (Current->Next != nullptr && Current->Next->Data < val)
			Current = Current->Next;

		LLNode<data>* temp = new LLNode<data>(val);
		temp->Next = Current->Next;
		Current->Next = temp;
		if (temp->Next == nullptr)
			Tail = temp;
	}
}

template<typename data>
inline void LinkedList<data>::Delete()
{
	if (Head == nullptr) return;
	LLNode <data>*curr = Head;
	Head = Head->Next;
	delete Head;
}

template <typename data>
void LinkedList<data>::InsertH(const data dataVal)
{
	LLNode<data>* Current = new LLNode<data>(dataVal);
	Current->Next = Head;
	Head = Current;
}

template <typename data>
void LinkedList<data>::Insert(const data dataVal)
{
	if (Head == nullptr)
	{
		Head = new LLNode<data>(dataVal);
		Tail = Head;
		return;
	}
	Tail->Next = new LLNode<data>(dataVal);
	Tail = Tail->Next;
}

template <typename data>
void LinkedList<data>::DeleteAt(const int index)
{
	LLNode<data>* Current = Head;
	for (int i = 1; i < index; i++)
		Current = Current->Next;

	if (index == 0)
	{
		Head = Head->Next;
		delete Current;
		return;
	}

	LLNode<data>* Post = Current->Next;
	Current->Next = Post->Next;
	delete Post;
}

template <typename data>
void LinkedList<data>::DeleteValue(const data Value)
{
	if (Head == nullptr)
		return;

	LLNode<data>* Current = Head;
	if (Current->Data == Value)
	{
		Head = Head->Next;
		delete Current;
		return;
	}
	for (int i = 0; Current->Next != nullptr; i++)
		if (Current->Data == Value)
		{
			Current = Current->Next;
			DeleteAt(i);
			i--;
		}
		else
			Current = Current->Next;
}

template <typename data>
bool LinkedList<data>::Search(const data dataVal)
{
	LLNode<data>* Current = Head;
	while (Current != nullptr)
	{
		if (Current->Data == dataVal)
			return true;
		Current = Current->Next;
	}
	return false;
}

template<typename data>
inline string LinkedList<data>::MakeLinkLine(string*& Map)
{
	string str;
	if (Head == nullptr) return "";

	str += " -> ";
	LLNode<data>* Current = Head;
	for (int i = 0; Current != nullptr; i++)
	{
		str += Map[Current->Data.idx];
		Current = Current->Next;
		if (Current != nullptr)
			str += "-> ";
	}
	return str;
}

template<typename data>
inline bool LinkedList<data>::IsEmpty()
{
	return Head == nullptr;
}

template<typename data>
inline const data LinkedList<data>::Front()
{
	return Head->Data;
}

template <typename data>
const data LinkedList<data>::ValueAt(const int index)
{
	LLNode<data>* Current = Head;
	for (int i = 0; i < index && Current != nullptr; i++)
		Current = Current->Next;

	if (Current == nullptr)
		return (-1);

	return Current->Data;
}

template<typename data>
inline void LinkedList<data>::Display(string* Map, const int size)
{
	if (Head == nullptr)
	{	cout << endl;	return;}

	LLNode<data>* Current = Head;
	for (int i = 0; Current != nullptr; i++)
	{
		std::cout << Map[Current->Data.idx];
		Current = Current->Next;
		if (Current != nullptr)
			cout << "-> ";
	}
	cout << endl;
}

template<typename data>
int LinkedList<data>::RecursiveLength(const LLNode<data>* Current)
{
	if (Current == nullptr)
		return 0;
	else
		return RecursiveLength(Current->Next) + 1;
}

template <typename data>
const int LinkedList<data>::Length()
{
	return RecursiveLength(Head);
}

template <typename data>
void LinkedList<data>::Display()
{
	if (Head == nullptr)
		return;

	LLNode<data>* Current = Head;
	for (int i = 0; Current != nullptr; i++)
	{
		std::cout << Current->Data << "  ";
		Current = Current->Next;
	}
}

template <typename data>
LinkedList<data>::~LinkedList()
{
	if (Head == nullptr)
		return;
	LLNode<data>* Current = Head;

	while (Current->Next != nullptr)
	{
		while (Current->Next->Next != nullptr)
			Current = Current->Next;

		delete Current->Next;
		Current->Next = nullptr;
		Current = Head;
	}
	delete Head;
	Head = nullptr;
}