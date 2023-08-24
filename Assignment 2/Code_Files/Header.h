#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;


//---------------General Use Functions---------------//
bool IsNumber(const char);
const string NumToStr(int num);
const int StrToNum(const string& str);
string RevString(const string& str);
bool CompareStr(const string& str1, const string& str2);
template <typename data>
void InitArray(data**& Array, const int Rows, const int Cols, const data def = NULL)
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Array[i][j] = def;
}


//================== Class Headers ===================//

//====================================================//
//				Mat Based Image Object		 		  //
//====================================================//
template <typename data>
class Image {
public:
	data** Array;
	int Rows;
	int Cols;

	Image();
	Image(Mat&);
	Image(Image&);
	void ConvertImage(Mat&);
	Image(const int nrows, const int ncols);
	~Image();
};

//====================================================//
//				LinkedList Based Stack		 		  //
//====================================================//
template <typename data>
struct Vertex {
	data Data;
	Vertex* Next;

	Vertex(const data val = 0, Vertex<data>* nex = nullptr)
	{
		Data = val;
		Next = nex;
	}
};

template <typename data>
class Stack {
public:
	Vertex<data>* Top;

	Stack();
	Stack(const Stack&);
	void Pop();
	bool IsEmpty();
	const int Size();
	const data PopR();
	const data  Peek();
	void DisplayStack();
	void Push(const data);
	const Vertex<data>* PeekV();
	~Stack();
};

//====================================================//
//				LinkedList Based Queue				  //
//====================================================//
template <typename data>
class Queue {
public:
	Vertex<data>* Front;
	Vertex<data>* Rear;
	const int MaxSize;
	int length;

	Queue(const int = -1);
	bool IsEmpty();
	void  Dequeue();
	const data Peek();
	void DisplayQueue();
	bool Search(const data);
	void Enqueue(const data);
	const Vertex<data>* PeekV();
	const data Remove(const data);
	~Queue();
};


//====================================================//
//				Image Pixel Location				  //
//====================================================//

template <typename data>
class Pixel {
public:
	data row;
	data col;

	Pixel(const data r = NULL, const data c = NULL)
	{
		row = r;
		col = c;
	}

	friend ostream& operator<<(ostream&, const Pixel<data>&);
};

template <typename data> 
ostream& operator<<(ostream& out, const Pixel<data>& P)
{
	out << P.row << "," << P.col << "  ";
	return out;
}

//------------ Class Implementation ------------//
// 
//==============================================//
//			Mat Based Image Object				//
//==============================================//


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

	Mat dst;
	src.convertTo(dst, CV_8UC1, 1, 0);

	Rows = src.rows;
	Cols = src.cols;

	Array = new data * [Rows];
	for (int i = 0; i < Rows; i++)
		Array[i] = new data[Cols];

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Array[i][j] = dst.at<data>(i, j);
}

template<typename data>
inline Image<data>::Image(Image& Other)
{
	Image(Other.Rows, Other.Cols);

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Array[i][j] = Other.Array[i][j];
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
void WriteMat(Mat& Img)
{
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			if (Img.at<data>(i, j) < 10)
				cout << "   " << Img.at<data>(i, j);
			else if (Img.at<data>(i, j) < 100)
				cout << "  " << Img.at<data>(i, j);
			else
				cout << " " << Img.at<data>(i, j);
		}
		cout << endl;
	}
}

template <typename data>
void WriteImage(Image<data>& Img)
{
	for (int i = 0; i < Img.Rows; i++)
	{
		for (int j = 0; j < Img.Cols; j++)
		{
			if (Img.Array[i][j] < 10)
				cout << "   " << int(Img.Array[i][j]);
			else if (Img.Array[i][j] < 100)
				cout << "  " << int(Img.Array[i][j]);
			else
				cout << " " << int(Img.Array[i][j]);
		}
		cout << endl;
	}
}

template <typename data>
void Image<data>::ConvertImage(Mat& Img)
{
	Img.~Mat();
	Img = Mat(Rows, Cols, CV_8UC1);

	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Img.at<data>(i, j) = Array[i][j];
}

//==============================================//
//	  Linked List Based Stack Implementation	//
//==============================================//
template<typename data>
inline Stack<data>::Stack()
{
	Top = nullptr;
}

template<typename data>
inline void RecursiveInsert(Stack<data>& S, Vertex<data>* curr)
{
	if (curr == nullptr)	return;
	RecursiveInsert(S, curr->Next);
	S.Push(curr->Data);
}

template<typename data>
inline Stack<data>::Stack(const Stack<data>& Other)
{
	Top = nullptr;
	Vertex<data>* curr = Other.Top;
	RecursiveInsert(*this, curr);
}

template<typename data>
inline void Stack<data>::Push(const data val)
{
	Vertex<data>* temp = new Vertex<data>(val, Top);
	Top = temp;
}

template<typename data>
inline void Stack<data>::Pop()
{
	if (IsEmpty())
		return;

	Vertex<data>* curr = Top;
	Top = Top->Next;
	delete curr;
}

template<typename data>
inline bool Stack<data>::IsEmpty()
{
	return Top == nullptr;
}

template<typename data>
inline const int Stack<data>::Size()
{
	int size;
	Vertex<data>* curr = Top;
	for (size = 0; curr != nullptr; size++, curr = curr->Next);
	return size;
}

template<typename data>
inline const Vertex<data>* Stack<data>::PeekV()
{
	return Top;
}

template<typename data>
inline const data Stack<data>::Peek()
{
	if (!IsEmpty())
		return Top->Data;
	return NULL;
}

template<typename data>
inline void Stack<data>::DisplayStack()
{
	Vertex <data>* temp = Top;
	while (temp != nullptr)
	{
		cout << temp->Data << "  ";
		temp = temp->Next;
	}
}

template<typename data>
inline const data Stack<data>::PopR()
{
	const data val = Peek();
	Pop();
	return val;
}

template<typename data>
inline Stack<data>::~Stack()
{
	Vertex<data>* temp;

	while (Top != nullptr)
	{
		temp = Top;
		Top = Top->Next;
		delete temp;
	}
}

//==============================================//
//	  Linked List Based Queue Implementation	//
//==============================================//

template<typename data>
inline Queue<data>::Queue(const int size) : MaxSize(size)
{
	length = 0;
	Front = Rear = nullptr;
}

template<typename data>
inline void Queue<data>::Enqueue(const data val)
{
	length++;
	Vertex<data>* temp = new Vertex<data>(val);
	if (IsEmpty())
	{
		Front = Rear = temp;
		return;
	}
	else if (length > MaxSize && MaxSize > 1)
		Dequeue();

	Rear->Next = temp;
	Rear = temp;
}

template<typename data>
inline void Queue<data>::Dequeue()
{
	if (IsEmpty())
		return;
	else if (Front == Rear)
	{
		delete Rear;
		length--;
		Front = Rear = nullptr;
		return;
	}

	Vertex<data>* temp = Front;
	Front = Front->Next;
	delete temp;
	length--;
}

template<typename data>
inline const Vertex<data>* Queue<data>::PeekV()
{
	return Front;
}

template<typename data>
inline const data Queue<data>::Remove(const data del)
{
	if (IsEmpty())
		return NULL;

	for (Vertex<data>* curr = Front; curr->Next != nullptr; curr = curr->Next)
		if (curr->Next->Data == del)
		{
			Vertex<data>* temp = curr->Next;
			data ret = temp->Data;
			curr->Next = curr->Next->Next;

			if (Rear->Data == ret)
				Rear = curr;

			delete temp;
			length--;
			return ret;
		}
	return NULL;
}

template<typename data>
inline const data Queue<data>::Peek()
{
	if (!IsEmpty())
		return Front->Data;
	return NULL;
}

template<typename data>
inline void Queue<data>::DisplayQueue()
{
	Vertex <data>* temp = Front;
	while (temp != nullptr)
	{
		cout << temp->Data << "  ";
		temp = temp->Next;
	}
}

template<typename data>
inline bool Queue<data>::Search(const data val)
{
	for (Vertex<data>* curr = Front; curr != nullptr; curr = curr->Next)
		if (curr->Data == val)
			return true;

	return false;
}

template<typename data>
inline bool Queue<data>::IsEmpty()
{
	return (Front == nullptr) && (Rear == nullptr);
}

template<typename data>
inline Queue<data>::~Queue()
{
	//Vertex<data>* temp;
	while (Front != nullptr)
		Dequeue();

	Front = Rear = nullptr;
}

//==============================================//
//				Priority Record Class			//
//==============================================//

class Priority {
public:
	int priority;
	string FileName;

	Priority(const int p = 0, string str = "") { priority = p; FileName = str; }
};