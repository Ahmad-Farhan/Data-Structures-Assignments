#pragma once
#include "Support.h"

template <typename data>
const int CountNeighbours(const Image<data>& ResImg, int yindex, int xindex)
{
	int count = 0;
	if (xindex - 1 >= 0)
		if (int(ResImg.Array[yindex][xindex - 1]) != 0)
			count++;

	if (yindex - 1 >= 0)
	{
		if (int(ResImg.Array[yindex - 1][xindex]) != 0)
			count++;

		if (xindex - 1 >= 0)
			if (int(ResImg.Array[yindex - 1][xindex - 1]) != 0)
				count++;

		if (xindex + 1 < ResImg.Cols)
			if (int(ResImg.Array[yindex - 1][xindex + 1]) != 0)
				count++;
	}
	return count;
}

template <typename data>
void CopyNeighbourLabel(Image<data>& Img, data& ImgDestIndexVal, int row, int col)
{
	if (col - 1 >= 0)
		if (int(Img.Array[row][col - 1]) != 0)
		{
			ImgDestIndexVal = Img.Array[row][col - 1];
			return;
		}

	if (row - 1 >= 0)
	{
		if (Img.Array[row - 1][col] != 0)
		{
			ImgDestIndexVal = Img.Array[row - 1][col];
			return;
		}
		if (col - 1 >= 0)
		{
			if (Img.Array[row - 1][col - 1] != 0)
			{
				ImgDestIndexVal = Img.Array[row - 1][col - 1];
				return;
			}
		}
		if (col + 1 < Img.Cols)
		{
			if (Img.Array[row - 1][col + 1] != 0)
			{
				ImgDestIndexVal = Img.Array[row - 1][col + 1];
				return;
			}
		}
	}
}

template <typename data>
void AssignLabel(const Image<data>& Img, data& ImgDestIndexVal, int row, int col, RootList<data>& list)
{
	data Equivalent, Value;
	bool Assigned = false;
	if (col - 1 >= 0)
		if (Img.Array[row][col - 1] != 0 && !Assigned)
		{
			Assigned = true;
			Equivalent = ImgDestIndexVal = Img.Array[row][col - 1];
		}
	if (row - 1 >= 0)
	{
		if (Img.Array[row - 1][col] != 0)
		{
			Value = Img.Array[row - 1][col];
			if (!Assigned)
			{
				Assigned = true;
				Equivalent = ImgDestIndexVal = Value;
			}
			else
				list.InsertEquivalent(Equivalent, Value);
		}

		if (col - 1 >= 0)
		{
			if (Img.Array[row - 1][col - 1] != 0)
			{
				Value = Img.Array[row - 1][col - 1];
				if (!Assigned)
				{
					Assigned = true;
					Equivalent = ImgDestIndexVal = Value;
				}
				else
					list.InsertEquivalent(Equivalent, Value);
			}
		}
		if (col + 1 < Img.Cols)
		{
			if (Img.Array[row - 1][col + 1] != 0)
			{
				Value = Img.Array[row - 1][col + 1];
				if (!Assigned)
				{
					Assigned = true;
					Equivalent = ImgDestIndexVal = Value;
				}
				else
					list.InsertEquivalent(Equivalent, Value);
			}
		}
	}
}

template <typename data>
void DisplayArray(data* Array, int size)
{
	for (int i = 0; i < size; i++)
		cout << Array[i] << "  ";
	cout << endl;
}

template <typename data>
int FindMaxIndex(data*& Array, int size)
{
	int MaxIndex = 0;
	int Max = Array[MaxIndex];
	for (int i = 0; i < size; i++)
		if (int(Array[i]) > Max)
		{
			Max = int(Array[i]);
			MaxIndex = i;
		}
	return MaxIndex;
}

template <typename data>
void CheckLabelCount(const Image<data>& ImgCCL, int*& LabelArray, int length, int& Max)
{
	int* LabelCount = new int[length];
	for (int i = 0; i < length; i++)
		LabelCount[i] = 0;

	for (int i = 0; i < ImgCCL.Rows; i++)
		for (int j = 0; j < ImgCCL.Cols; j++)
			for (int k = 0; k < length; k++)
				if (int(ImgCCL.Array[i][j]) == LabelArray[k])
					++LabelCount[k];

	int MaxIndex = FindMaxIndex(LabelCount, length);
	Max = LabelArray[MaxIndex];
	delete[] LabelArray;
	delete[] LabelCount;
}

template <typename data>
void SingleLesionDetect(Image<data>& ImgCCL, RootList<data>& Labels)
{
	int MaxVal;
	int* LabelArray = Labels.FirstElementsArray();
	CheckLabelCount(ImgCCL, LabelArray, Labels.length, MaxVal);

	for (int i = 0; i < ImgCCL.dst.rows; i++)
		for (int j = 0; j < ImgCCL.dst.cols; j++)
			if (ImgCCL.Array[i][j] == MaxVal)
				ImgCCL.dst.at<data>(i,j) = ImgCCL.Array[i][j] = 255;
			else
				ImgCCL.dst.at<data>(i, j) = ImgCCL.Array[i][j] = 0;
}

template <typename data>
void ApplyingLabels(const Image<data>& Img, Image<data>& ImgCCL, RootList<data>& Labels)
{
	int LabelVal = 1, Neighs = 0;
	for (int i = 0; i < Img.Rows; i++)
		for (int j = 0; j < Img.Cols; j++)
			if (Img.Array[i][j] != 0)
			{
				Neighs = CountNeighbours(ImgCCL, i, j);
				if (Neighs == 0)
				{
					ImgCCL.Array[i][j] = ++LabelVal;
					Labels.InsertNewLabel(LabelVal);
				}
				else if (Neighs == 1)
					CopyNeighbourLabel(ImgCCL, ImgCCL.Array[i][j], i, j);
				else
					AssignLabel(ImgCCL, ImgCCL.Array[i][j], i, j, Labels);
			}
			else
				ImgCCL.Array[i][j] = Img.Array[i][j];
}

template <typename data>
data FirstLabel(data& Val, RootList<data>& List)
{
	LinkedList<data>* Curr = List.root;
	while (Curr != nullptr)
	{
		if (Curr->Search(Val))
		{
			Val = Curr->ValueAtIndex(0);
			return Val;
		}
		else
			Curr = Curr->NextList;
	}
}

template <typename data>
void MaskingLabels(Image<data>& Img, RootList<data>& List)
{
	data prev = Img.Array[0][0], prevVal = 0;
	for (int i = 0; i < Img.Rows; i++)
		for (int j = 0; j < Img.Cols; j++)
			if (Img.Array[i][j] == prev)
				Img.Array[i][j] = prevVal;
			else
			{
				prev = Img.Array[i][j];
				prevVal = FirstLabel(Img.Array[i][j], List);
			}
}

template <typename data>
int Connectivity(const Image<data>& Img, int rowVal, int colVal)
{
	int count = 0;
	if (rowVal - 1 >= 0)
	{
		if (Img.Array[rowVal - 1][colVal] != 0)
			count++;

		if (colVal - 1 >= 0)
			if (Img.Array[rowVal - 1][colVal - 1] != 0)
				count++;

		if (colVal + 1 < Img.Cols)
			if (Img.Array[rowVal - 1][colVal + 1] != 0)
				count++;
	}
	if (colVal - 1 >= 0)
		if (Img.Array[rowVal][colVal - 1] != 0)
			count++;

	if (colVal + 1 < Img.Cols)
		if (Img.Array[rowVal][colVal + 1] != 0)
			count++;

	if (rowVal + 1 < Img.Rows)
	{
		if (Img.Array[rowVal + 1][colVal] != 0)
			count++;

		if (colVal - 1 >= 0)
			if (Img.Array[rowVal + 1][colVal - 1] != 0)
				count++;

		if (colVal + 1 < Img.Cols)
			if (Img.Array[rowVal + 1][colVal + 1] != 0)
				count++;
	}
	return count;
}

template <typename data>
void Apply8Connectivity(Image<data>& Img)
{

	int neighs = 0, index = 0;
	for (int i = 0, k = Img.Cols - 1; i <= Img.Cols / 2; i++, k--)
		for (int j = 0; j < Img.Rows; j++, index = i)
			for (int count = 0; count < 2; count++, index = k)
				if (Img.Array[j][index] == 0)
				{
					//neighs = CountNeighbours(Img, i, j);
					neighs = Connectivity(Img, j, index);
					if (neighs >= 4)
						Img.Array[j][index] = 255;//Img.dst.at<data>(i, j) = 255;
				}


	for (int i = 0, k = Img.Rows - 1; i <= Img.Rows / 2; i++, k--)
		for (int j = 0; j < Img.Cols; j++, index = i)
			for (int count = 0; count < 2; count++, index = k)
				if (Img.Array[index][j] == 0)
				{
					//neighs = CountNeighbours(Img, i, j);
					neighs = Connectivity(Img, index, j);
					if (neighs >= 4)
						Img.Array[index][j] = 255;//Img.dst.at<data>(i, j) = 255;
				}
}

template <typename data>
void ApplyCCL(Image<data>& Img, Image<data>& ImgCCL)
{
	RootList<data> Labels;
	Apply8Connectivity(Img);						//O(n2)
	ApplyingLabels(Img, ImgCCL, Labels);
	Labels.Compress();
	MaskingLabels(ImgCCL, Labels);
	SingleLesionDetect(ImgCCL, Labels);
	ConvertImage(ImgCCL);
}