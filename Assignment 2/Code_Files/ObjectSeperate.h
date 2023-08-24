#pragma once
#include "Header.h"

//---------------------------Function Definitions---------------------------//
template <typename data>
void InsertConnected(Image<data>&, Image<data>&, Queue<Pixel<int>>&, Pixel<int>);

template <typename data>
void ExpandHighlight(Image<data>&, Pixel<int>, Mat&);

template <typename data>
void ExtractObject(Image<data>&, bool&, Mat&);

template <typename data>
string SeperateObjects(Image<data>&);



//------------------------------Implementations------------------------------//

//Extracted image: Marks all 8 connected Pixels by setting them = 255 in Object
//Original Image: Enqueues the locations of the neighbouring pixels with value = 255
//				  Sets those locations = 0 in actual image in order to avoid repeatition
template <typename data>
void InsertConnected(Image<data>& Img, Image<data>& Mark, Queue<Pixel<int>>& Que, Pixel<int> Centre)
{
	int row = Centre.row, col = Centre.col;


	if (col - 1 > 0)
		if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == 0)
		{
			Que.Enqueue({ row , col - 1 });
			Mark.Array[row][col - 1] = 255;
		}

	if (col + 1 < Img.Cols)
		if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == 0)
		{
			Que.Enqueue({ row , col + 1 });
			Mark.Array[row][col + 1] = 255;
		}

	row--;
	if (row > 0)
	{
		if (Img.Array[row][col] == 255 && Mark.Array[row][col] == 0)
		{
			Que.Enqueue({ row , col });
			Mark.Array[row][col] = 255;
		}

		if (col - 1 > 0)
			if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == 0)
			{
				Que.Enqueue({ row , col - 1 });
				Mark.Array[row][col - 1] = 255;
			}

		if (col + 1 < Img.Cols)
			if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == 0)
			{
				Que.Enqueue({ row , col + 1 });
				Mark.Array[row][col + 1] = 255;
			}
	}

	row += 2;
	if (row < Img.Rows)
	{
		if (Img.Array[row][col] == 255 && Mark.Array[row][col] == 0)
		{
			Que.Enqueue({ row , col });
			Mark.Array[row][col] = 255;
		}

		if (col - 1 > 0)
			if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == 0)
			{
				Que.Enqueue({ row , col - 1 });
				Mark.Array[row][col - 1] = 255;
			}

		if (col + 1 < Img.Cols)
			if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == 0)
			{
				Que.Enqueue({ row , col + 1 });
				Mark.Array[row][col + 1] = 255;
			}
	}
}

//Enqueues Starting Pixel Location(x, y coordinates)
//Sends Value to InsertConnected that checks all 8 neighbouring pixels
//Dequeues a location and sets that pixel in original image = 0
//Loops untill the queue is not empty
template <typename data>
void ExpandHighlight(Image<data>& Img, Pixel<int> Centre, Mat& Object)
{
	Queue<Pixel<int>> Que;
	Image<data> ImageCopy(Img.Rows, Img.Cols);

	Que.Enqueue(Centre);
	while (!Que.IsEmpty())
	{
		Centre = Que.Peek();
		InsertConnected(Img, ImageCopy, Que, Centre);
		Que.Dequeue();
		ImageCopy.Array[Centre.row][Centre.col] = 255;
		Img.Array[Centre.row][Centre.col] = 0;
	}

	Centre.row = Centre.col = 0;
	ImageCopy.ConvertImage(Object);
}

//Detects starting Pixel with Value = 255
//Sends that Location to Exprand Function
template <typename data>
void ExtractObject(Image<data>& Img, bool& Found, Mat& Object)
{
	for (int i = 0; i < Img.Rows; i++)
		for (int j = 0; j < Img.Cols; j++)
			if (Img.Array[i][j] == 255)
			{
				Found = true;
				ExpandHighlight(Img, { i , j }, Object);
				return;
			}
}

//Loops till all the distinct objects in image have not been extracted
template <typename data>
string SeperateObjects(Image<data>& Img)
{
	Mat Object;
	char ImageCount = '0';
	string str = "Images/Res0.png";
	bool ObjectFound = true;

	while (ObjectFound)
	{
		ObjectFound = false;
		ExtractObject(Img, ObjectFound, Object);
		str[10] = ImageCount;
		if (ObjectFound)
			imwrite(str, Object);
		ImageCount++;
	}
	str = (ImageCount-1);
	return str;
}




//template <typename data>
//void InsertConnected(Image<data>& Img, Image<bool>& Mark, Queue<Pixel<int>>& Que, Pixel<int> Centre);
//{
//	int row = Centre.row, col = Centre.col;
//
//	if (row - 1 > 0)
//	{
//		if (Img.Array[row - 1][col] == 255 && Mark.Array[row - 1][col] == false)
//			//Que.Enqueue({ row - 1 , col });
//		{
//			Que.Enqueue({ row - 1 , col });
//			Mark.Array[row - 1][ col] = true;
//		}
//
//		if (col - 1 > 0)
//			if (Img.Array[row - 1][col - 1] == 255 && Mark.Array[row - 1][col - 1] == false)
//				//Que.Enqueue({ row - 1 , col - 1 });
//			{
//				Que.Enqueue({ row - 1 , col-1 });
//				Mark.Array[row - 1][ col-1] = true;
//			}
//
//		if (col + 1 < Img.Cols)
//			if (Img.Array[row - 1][col + 1] == 255 && Mark.Array[row - 1][col + 1] == false)
//				//Que.Enqueue({ row - 1 , col + 1 });
//			{
//				Que.Enqueue({ row - 1 , col+1 });
//				Mark.Array[row - 1][ col+1] = true;
//			}
//	}
//
//	if (col - 1 > 0)
//		if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == false)
//			//Que.Enqueue({ row , col - 1 });
//		{
//			Que.Enqueue({ row , col-1 });
//			Mark.Array[row ][ col-1] = true;
//		}
//
//	if (col + 1 < Img.Cols)
//		if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == false)
//			//Que.Enqueue({ row , col + 1 });
//		{
//			Que.Enqueue({ row , col+1 });
//			Mark.Array[row ][ col+1] = true;
//		}
//
//	if (row + 1 <Img.Rows)
//	{
//		if (Img.Array[row + 1][col] == 255 && Mark.Array[row + 1][col] == false)
//		//	Que.Enqueue({ row + 1 , col });
//		{
//			Que.Enqueue({ row + 1 , col });
//			Mark.Array[row + 1][ col] = true;
//		}
//
//		if (col - 1 > 0)
//			if (Img.Array[row + 1][col - 1] == 255 && Mark.Array[row + 1][col - 1] == false)
//			//	Que.Enqueue({ row + 1 , col - 1 });
//			{
//				Que.Enqueue({ row + 1 , col-1 });
//				Mark.Array[row + 1][ col-1] = true;
//			}
//
//		if (col + 1 < Img.Cols)
//			if (Img.Array[row + 1][col + 1] == 255 && Mark.Array[row + 1][col + 1] == false)
//				//Que.Enqueue({ row + 1 , col + 1 });
//			{
//				Que.Enqueue({ row + 1 , col+1 });
//				Mark.Array[row + 1][ col+1] = true;
//			}
//	}
//}

//template <typename data>
//void InsertConnected(Image<data>& Img, Image<data>& Mark, Queue<Pixel<int>>& Que, Pixel<int> Centre)
//{
//	int row = Centre.row, col = Centre.col;
//
//
//	if (col - 1 > 0)
//		if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == 0)
//		{
//			Que.Enqueue({ row , col - 1 });
//			Mark.Array[row][col - 1] = 255;
//		}
//
//	if (col + 1 < Img.Cols)
//		if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == 0)
//		{
//			Que.Enqueue({ row , col + 1 });
//			Mark.Array[row][col + 1] = 255;
//		}
//
//	row--;
//	if (row > 0)
//	{
//		if (Img.Array[row][col] == 255 && Mark.Array[row][col] == 0)
//		{
//			Que.Enqueue({ row , col });
//			Mark.Array[row][col] = 255;
//		}
//
//		if (col - 1 > 0)
//			if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == 0)
//			{
//				Que.Enqueue({ row , col - 1 });
//				Mark.Array[row][col - 1] = 255;
//			}
//
//		if (col + 1 < Img.Cols)
//			if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == 0)
//			{
//				Que.Enqueue({ row , col + 1 });
//				Mark.Array[row][col + 1] = 255;
//			}
//	}
//
//	row += 2;
//	if (row < Img.Rows)
//	{
//		if (Img.Array[row][col] == 255 && Mark.Array[row][col] == 0)
//		{
//			Que.Enqueue({ row , col });
//			Mark.Array[row][col] = 255;
//		}
//
//		if (col - 1 > 0)
//			if (Img.Array[row][col - 1] == 255 && Mark.Array[row][col - 1] == 0)
//			{
//				Que.Enqueue({ row , col - 1 });
//				Mark.Array[row][col - 1] = 255;
//			}
//
//		if (col + 1 < Img.Cols)
//			if (Img.Array[row][col + 1] == 255 && Mark.Array[row][col + 1] == 0)
//			{
//				Que.Enqueue({ row , col + 1 });
//				Mark.Array[row][col + 1] = 255;
//			}
//	}
//}
//
//Mat temp;
//
//template <typename data>
////void ExpandHighlight(Image<data>& Img , Image<bool>& Mark , Pixel<int> Centre)
//void ExpandHighlight(Image<data>& Img , Pixel<int> Centre)
//{
//	Queue<Pixel<int>> Que;
//	Image<data> ImageCopy(Img.Rows , Img.Cols);
//
//	Que.Enqueue(Centre);
//	while (!Que.IsEmpty())
//	{
//		Centre = Que.Peek();
//		//InsertConnected(Img, Mark, Que, Centre);
//		InsertConnected(Img, ImageCopy, Que, Centre);
//		Que.Dequeue();
//		ImageCopy.Array[Centre.row][Centre.col] = 255;
//		Img.Array[Centre.row][Centre.col] = 0;
//		//Mark.Array[Centre.row][Centre.col] = true;
//	}
//
//	Centre.row = Centre.col = 0;
//	ImageCopy.ConvertImage(temp);
//
//}
//
//template <typename data>
////void ExtractObject(Image<data>& Img, Image<bool>& Mark, bool& Found)
//void ExtractObject(Image<data>& Img, bool& Found)
//{
//	for(int i=0 ; i<Img.Rows;i++)
//		for(int j=0 ; j<Img.Cols;j++)
//			if (Img.Array[i][j] == 255)
//			{
//				Found = true;
//				//ExpandHighlight(Img, Mark, { i , j });
//				ExpandHighlight(Img, { i , j });
//				return;
//			}
//}
//
////void InitBool(Image<bool>& Mark)
////{
////	for (int i = 0; i < Mark.Rows; i++)
////		for (int j = 0; j < Mark.Cols; j++)
////			Mark.Array[i][j] = false;
////}
//
//template <typename data>
//string SeperateObjects(Image<data>& Img)
//{
//	char ImageCount = '0';
//	string str = "C:/A2Resources/Images/Res0.png";
//	bool ObjectFound = true;
//	//Image<bool> LabelCopy(Img.Rows ,Img.Cols);
//
//	while (ObjectFound)
//	{
//		ObjectFound = false;
//		//InitArray(LabelCopy.Array, LabelCopy.Rows, LabelCopy.Cols, false);
//		//InitArray(ImgCopy)
//		//InitBool(LabelCopy);
//		//ExtractObject(Img, LabelCopy, ObjectFound);
//		ExtractObject(Img, ObjectFound);
//		str[25] = char(ImageCount);
//		if (ObjectFound)
//			 imwrite(str, temp);
//		ImageCount++;
//	}
//	return ""+ImageCount;
//}