#pragma once
#include "Support.h"

//template<typename data>
//inline LLArray<data>::LLArray(int rows)
//{
//	Size = rows;
//	List = new LinkedList<int>[Size];
//}
//
//template<typename data>
//inline void LLArray<data>::ConvertToRLC(Image<data>& Img)
//{
//	List[0].InsertAt(-1, 2);
//	List[0].InsertAt(Img.Rows, 0);
//	List[0].InsertAt(Img.Cols, 1);
//
//	bool Started = false;
//
//	for (int i = 0; i < Img.Rows; i++)
//	{
//		List[i + 1].Insert(-1);
//		Started = false;
//
//		for (int j = Img.Cols - 1; j >= 0; j--)
//			if (Img.Array[i][j] != 0 && !Started)
//			{
//				List[i + 1].Insert(j);
//				Started = true;
//			}
//			else if (Started && Img.Array[i][j] == 0)
//			{
//				List[i + 1].Insert(j + 1);
//				Started = false;
//			}
//
//		if (Started)
//			List[i + 1].Insert(0);
//	}
//}
//
//template<typename data>
//inline Mat LLArray<data>::ConvertToImage(Image<data>& Img)
//{
//	if (Img.Array == nullptr)
//		return;
//	
//	LinkedList<data>* Curr = List[0];
//	
//	
//	//Img.Rows = Curr->Head;
//	Img.Cols = Curr->Head->Next;
//
//	//for (int i = 0; i < Img.Rows; i++)
//	//{
//
//
//}
//
//
//template<typename data>
//inline void LLArray<data>::Display()
//{
//	for (int i = 0; i < Size; i++, cout << "\n\n")
//		List[i].Display();
//
//	cout << "\n";
//}
//
//template<typename data>
//inline void LLArray<data>::ClearLLArray()
//{
//	for (int i = 0; i < Size; i++)
//		List[i].ClearList();
//}
//
//template<typename data>
//inline LLArray<data>::~LLArray()
//{
//	for (int i = 0; i < Size; i++)
//		List[i].~LinkedList();
//
//	List = nullptr;
//	Size = 0;
//}
//------------------------------------------------//
template<typename data>
inline LLArray<data>::LLArray()
{
	List.Head = nullptr;
}

template<typename data>
inline void LLArray<data>::ConvertToRLC(Image<data>& Img)
{
	bool Started = false;
	for (int i = Img.Rows-1; i >= 0 ; i--)
	{
		List.Insert(-1);
		Started = false;

		for (int j = Img.Cols - 1; j >= 0; j--)
			if (Img.Array[i][j] != 0 && !Started)
			{
				List.Insert(j);
				Started = true;
			}
			else if (Started && Img.Array[i][j] == 0)
			{
				List.Insert(j + 1);
				Started = false;
			}

		if (Started)
			List.Insert(0);
	}
	List.InsertAt(Img.Rows, 0);
	List.InsertAt(Img.Cols, 1);
	List.InsertAt(-1, 2);
}

template<typename data>
inline void LLArray<data>::Display()
{
	List.DisplayAsRLC();
}

template<typename data>
inline LLArray<data>::~LLArray()
{
	List.~LinkedList();
}