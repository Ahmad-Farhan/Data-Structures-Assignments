#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace cv;
using namespace std;

template <typename data>
class Image {
public:
	data** Array;
	Mat dst;
	int Rows;
	int Cols;

	Image();
	Image(Mat&);
	Image(const int nrows, const int ncols);
	~Image();
};

template <typename data>
Image<data>::Image()
{
	Rows = (Cols = 0);
	Array = nullptr;
}

template <typename data>
Image<data>::Image(Mat& src)
{
	if (src.dataend == nullptr)
	{
		cout << "Error: Image Not Found" << endl;
		return;
	}

	src.convertTo(dst, CV_16UC1, 1, 0);

	Rows = src.rows;
	Cols = src.cols;

	Array = new data * [Rows];
	for (int i = 0; i < Rows; i++)
		Array[i] = new data[Cols];

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Array[i][j] = dst.at<data>(i, j);
}

template <typename data>
Image<data>::Image(const int nrows, const int ncols)
{
	Rows = nrows;
	Cols = ncols;

	Array = new data * [Rows];
	for (int i = 0; i < Rows; i++)
		Array[i] = new data[Cols];

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Array[i][j] = 0;
}

template <typename data>
Image<data>::~Image()
{
	for (int i = 0; i < Rows; i++)
		delete[] Array[i];

	delete[] Array;
	Array = nullptr;
}


template <typename data>
void WriteImage(Image<data>& Img)
{
	for (int i = 0; i < Img.Rows; i++)
	{
		for (int j = 0; j < Img.Cols; j++)
		{
			Img.dst.at<data>(i, j) = Img.Array[i][j];
			if (Img.Array[i][j] < 10)
				cout << "   " << Img.dst.at<data>(i, j); // .Array[i][j];
			else if (Img.Array[i][j] < 100)
				cout << "  " << Img.dst.at<data>(i, j);  // Img.Array[i][j];
			else
				cout << " " << Img.dst.at<data>(i, j); //Img.Array[i][j];
		}
		cout << endl;
	}
}

template <typename data>
void ConvertImage(Image<data>& Img)
{
	for (int i = 0; i < Img.Rows; i++)
		for (int j = 0; j < Img.Cols; j++)
			Img.dst.at<data>(i, j) = Img.Array[i][j];
}

//---------------------------------------//

template <typename data>
class KMeanAverage {
public:
	int total;
	data sum;

	KMeanAverage()
	{
		total = 0;
		sum = 0;
	}
	void AddElement(const data val)
	{
		sum += val;
		total++;
	}
	float CalAverage()
	{
		return float(sum) / float(total);
	}
	void Clear()
	{
		total = 0;
		sum = 0;
	}
};

//----------------Linked List------------------//

template <typename data>
class Vertex {
public:
	data Data;
	Vertex* Next;

	Vertex(data dataVal = 0, Vertex* next = nullptr)
	{
		Data = dataVal;
		Next = next;
	}
};

template <typename data>
class LinkedList {
public:
	Vertex<data>* Head;
	LinkedList<data>* NextList;

	LinkedList();
	void Insert(const data);
	void UniqueInsert(const data);
	void InsertAt(const data, const int);
	void Remove(int data);
	void RemoveValue(const data);
	bool Search(const int);
	int ValueAtIndex(const int);
	double CalAverage();
	void ClearList();
	int Length();
	void DisplayAsRLC();
	void DisplayList();
	void Display();
	~LinkedList();
};

template <typename data>
LinkedList<data>::LinkedList()
{
	Head = nullptr;
	NextList = nullptr;
}

template <typename data>
void LinkedList<data>::InsertAt(const data dataVal, const int index)
{
	Vertex<data>* Current = Head;
	if (Head == nullptr || index == 0)
		Insert(dataVal);
	else
	{
		for (int i = 1; Current->Next != nullptr && i < index; i++)
			Current = Current->Next;

		Vertex<data>* Post = Current->Next;
		Current->Next = new Vertex<data>(dataVal);
		Current->Next->Next = Post;
	}
}

template <typename data>
void LinkedList<data>::Insert(const data dataVal)
{
	Vertex<data>* Current = new Vertex<data>(dataVal);
	Current->Next = Head;
	Head = Current;
}

template<typename data>
inline void LinkedList<data>::DisplayAsRLC()
{
	Vertex<data>* curr = Head;

	if (curr == nullptr)
		cout << "No Run Length Code Detected" << endl;
	else
		while (curr != nullptr)
		{
			cout << curr->Data << "  ";

			if (curr->Data == -1)
				cout << "\n\n";

			curr = curr->Next;
		}
}

template<typename data>
inline void LinkedList<data>::UniqueInsert(const data val)
{
	if (Search(val))
		return;

	Vertex<data>* Current = new Vertex<data>(val);
	Current->Next = Head;
	Head = Current;
}

template <typename data>
void LinkedList<data>::Remove(const int index)
{
	Vertex<data>* Current = Head;
	for (int i = 1; i < index; i++)
		Current = Current->Next;

	if (Current == Head)
	{
		Head = Head->Next;
		delete Current;
		return;
	}

	Vertex<data>* Post = Current->Next;
	Current->Next = Post->Next;
	delete Post;
}

template <typename data>
void LinkedList<data>::RemoveValue(const data Value)
{
	Vertex<data>* Current = Head;
	for (int i = 0; Current->Next != nullptr; i++)
	{
		if (Current->Data == Value)
		{
			Current = Current->Next;
			Remove(i);
			i--;
		}
		else
			Current = Current->Next;
	}
}

template <typename data>
bool LinkedList<data>::Search(const int dataVal)
{
	Vertex<data>* Current = Head;
	while (Current != nullptr)
	{
		if (Current->Data == dataVal)
			return true;
		Current = Current->Next;
	}
	return false;
}

template <typename data>
int LinkedList<data>::ValueAtIndex(const int index)
{
	Vertex<data>* Current = Head;
	for (int i = 0; i < index && Current != nullptr; i++)
		Current = Current->Next;

	if (Current == nullptr)
	{
		cout << "Invalid Index" << endl;
		return (-1);
	}
	return Current->Data;
}

template<typename data>
inline double LinkedList<data>::CalAverage()
{
	if (Head == nullptr)
		return 0;

	double sum = 0, elements = 0;
	Vertex<data>* Curr = Head;
	for (elements = 0; Curr != nullptr; Curr = Curr->Next, elements++)
		sum += Curr->Data;

	return sum / elements;
}

template<typename data>
int RecursiveLength(Vertex<data>* Current)
{
	if (Current == nullptr)
		return 0;
	else
		return 1 + RecursiveLength(Current->Next);
}

template <typename data>
int LinkedList<data>::Length()
{
	Vertex<data>* Current = Head;
	return RecursiveLength(Current);
}

template<typename data>
inline void LinkedList<data>::DisplayList()
{
	if (Head == nullptr)
		return;

	Vertex<data>* Current = Head;
	for (; Current != nullptr; Current = Current->Next)
		cout << int(Current->Data) << " -> ";

	cout << "\b\b\b\b" << endl;
}

template <typename data>
void LinkedList<data>::Display()
{
	if (Head == nullptr)
		return;

	Vertex<data>* Current = Head;
	for (; Current != nullptr; Current = Current->Next)
		cout << int(Current->Data) << " ";

	cout << endl;
}

template<typename data>
inline void LinkedList<data>::ClearList()
{
	if (Head == nullptr)
		return;
	else if (Head->Next == nullptr)
		return;

	Vertex<data>* Current = Head->Next;
	Vertex<data>* temp;

	while (Current != nullptr)
	{
		temp = Current;
		Current = Current->Next;
		delete temp;
	}

	Head = nullptr;
}

template <typename data>
LinkedList<data>::~LinkedList()
{
	Vertex<data>* Current = Head;
	Vertex<data>* temp;

	while (Current != nullptr)
	{
		temp = Current;
		Current = Current->Next;
		delete temp;
	}

	Head = nullptr;
}

//-------------------------------------------------------------------------//
// A Linked list of Linked Lists
// The Vertices or Nodes are LinkedLists in and of themselves
// Essentially a 2D LinkedList
// Can indefinitely Insert Lists and Nodes within lists 
//-------------------------------------------------------------------------//

template <typename data>
class RootList {
public:
	LinkedList<data>* root;
	int length;

	RootList();
	void InsertNewLabel(data val);
	void InsertEquivalent(data val, data equiv);
	void DeleteList(LinkedList<data>*& del);
	int* FirstElementsArray();
	void Display();
	void Compress();
	~RootList();
};

template<typename data>
inline RootList<data>::RootList()
{
	root = nullptr;
	length = 0;
}

template<typename data>
inline void RootList<data>::InsertNewLabel(data val)
{
	LinkedList<data>* Curr = root;
	for (int i = 0; i < length && Curr->NextList != nullptr; i++)
		Curr = Curr->NextList;

	length++;
	if (root == nullptr)
	{
		root = new LinkedList<data>;
		root->Insert(val);
		return;
	}

	LinkedList<data>* temp = new LinkedList<data>;
	temp->Insert(val);
	Curr->NextList = temp;
}

template<typename data>
inline void RootList<data>::InsertEquivalent(data val, data equiv)
{
	if (root == nullptr)
	{
		InsertNewLabel(equiv);
		root->Insert(val);
		return;
	}
	LinkedList<data>* Curr = root;
	while (Curr != nullptr)
	{
		if (Curr->Search(equiv))
		{
			if (!Curr->Search(val))
				Curr->Insert(val);
			return;
		}
		Curr = Curr->NextList;
	}
}

template<typename data>
inline void RootList<data>::Display()
{
	LinkedList<data>* Curr = root;
	while (Curr != nullptr)
	{
		Curr->Display();
		Curr = Curr->NextList;
	}
	cout << "\n\n";
}

template <typename data>
void CombineLists(LinkedList<data>*& L1, LinkedList<data>* L2)
{
	Vertex<data>* Check = L2->Head;
	while (Check != nullptr)
	{
		if (!L1->Search(Check->Data))
			L1->Insert(Check->Data);
		Check = Check->Next;
	}
}

template <typename data>
bool RelatedLists(LinkedList<data>*& L1, LinkedList<data>*& L2)
{
	Vertex<data>* Check = L2->Head;
	while (Check != nullptr)
	{
		if (L1->Search(Check->Data))
			return true;
		Check = Check->Next;
	}
	return false;
}

template<typename data>
inline void RootList<data>::DeleteList(LinkedList<data>*& del)
{
	LinkedList<data>* Curr = root;
	if (Curr == nullptr)
		return;

	while (Curr->NextList != nullptr && Curr->NextList != del)
		Curr = Curr->NextList;

	if (Curr->NextList == nullptr)
		return;

	LinkedList<data>* temp = Curr->NextList->NextList;
	Curr->NextList->~LinkedList();
	Curr->NextList = temp;
}

template<typename data>
inline void RootList<data>::Compress()
{
	LinkedList<data>* Curr = root;
	LinkedList<data>* Check;
	while (Curr != nullptr)
	{
		Check = Curr->NextList;

		while (Check != nullptr)
			if (!RelatedLists(Curr, Check))
				Check = Check->NextList;
			else
			{
				CombineLists(Curr, Check);

				length--;
				DeleteList(Check);
			}
		Curr = Curr->NextList;
	}
}

template <typename data>
inline int* RootList<data>::FirstElementsArray()
{
	LinkedList<data>* Curr = root;
	int* Array = new int[length];
	for (int i = 0; i < length && Curr != nullptr; i++, Curr = Curr->NextList)
		Array[i] = int(Curr->ValueAtIndex(0));

	return Array;
}

template<typename data>
void RecursiveDelete(LinkedList<data>*& Curr)
{
	if (Curr == nullptr)
		return;

	RecursiveDelete(Curr->NextList);
	Curr->~LinkedList();
}

template<typename data>
inline RootList<data>::~RootList()
{
	RecursiveDelete(root);
	root = nullptr;
}

//-----------------------------------------//
//template <typename data>
//class LLArray {
//public:
//	LinkedList<int>* List;
//	int Size;
//
//	LLArray(int);
//	//LLArray(Image&);
//	void ConvertToRLC(Image<data>&);
//	Mat ConvertToImage(Image<data>&);
//	void ClearLLArray();
//	void Display();
//	~LLArray();
//};

template <typename data>
class LLArray {
public:
	LinkedList<int> List;

	LLArray();
	void ConvertToRLC(Image<data>&);
	void Display();
	~LLArray();
};