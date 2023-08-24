#pragma once
#include "Support.h"

template <typename data>
void Display(data*& Array, const int size)
{
	for (int i = 0; i < size; i++)
		cout << Array[i] << "  ";

}

template <typename data>
void DetermineInitialKMeans(data*& Array ,const int NumberOfKMeans)
{
	int mid = 256 / (NumberOfKMeans*2) , input = mid;

	//Array[0] = 50;
	//Array[1] = 200;
	for (int i = 0; i < NumberOfKMeans && mid <= 255; i++, input += (mid*2))
		Array[i] = input;
}

template <typename data>
float CalculateAverage(data* & Array, int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++)
		sum += Array[i];

	return sum / size;
}

template <typename data>
void MakeClusters(const Image<data>& Img, KMeanAverage<float>*& KMean, float*& Centroids, const int NoOfCentroids)
{
	float Midpoint = CalculateAverage(Centroids, NoOfCentroids);

	//Display(Centroids, 2);
	//cout << "  " << Midpoint << endl << endl;

	for (int i = 0; i < Img.Rows; i++)
		for (int j = 0; j < Img.Cols; j++)
			if (Img.Array[i][j] <= Midpoint)
				KMean[0].AddElement(Img.Array[i][j]);
			else
				KMean[1].AddElement(Img.Array[i][j]);
}

template <typename data>
void UpdateCentroids(KMeanAverage<float>*& KMean, float*& Centroids, const int NoOfCentroids, bool& Change)
{
	float temp;
	for (int i = 0; i < NoOfCentroids; i++)
	{
		temp = KMean[i].CalAverage();
		if (int(temp) != int(Centroids[i]))
		{
			Centroids[i] = temp;
			Change = true;
		}
	}
}

template <typename data>
void ApplyMasking(const Image<data>& OriginalImg, Image<data>& KCLImage, float*& Centroids, const int KMeans)
{
	float mid = CalculateAverage(Centroids , KMeans);

	for (int i = 0; i < OriginalImg.Rows; i++)
		for (int j = 0; j < OriginalImg.Cols; j++)
			if(OriginalImg.Array[i][j] <= mid)
				KCLImage.Array[i][j] = 255;
			else
				KCLImage.Array[i][j] = 0;
}

template <typename data>
void ClearExtra(Image<data>& Img)
{
	for (int i = 0; i < Img.Rows; i++)
		for (int j = Img.Cols - 5; j >= 0; j--)
			if (Img.Array[i][j] == 255)
				Img.Array[i][j] = 0;
			else
				break;

	for (int i = 0; i < Img.Rows; i++)
		for (int j = 0; j < Img.Cols; j++)
			if (Img.Array[i][j] == 255)
				Img.Array[i][j] = 0;
			else
				break;

	for (int i = 0; i < Img.Cols; i++)
		for (int j = 0; j < Img.Rows; j++)
			if (Img.Array[j][i] == 255)
				Img.Array[j][i] = 0;
			else
				break;

	for (int i = 0; i < Img.Cols; i++)
		for (int j = Img.Rows-1; j >= 0; j--)
			if (Img.Array[j][i] == 255)
				Img.Array[j][i] = 0;
			else
				break;
}

template <typename data>
void ApplyKClustering(const Image<data>& Img, Image<data>& KCImage, const int NoOfKMeans)
{
	bool Change = false;
	float* Centroids = new float[NoOfKMeans];
	DetermineInitialKMeans(Centroids, NoOfKMeans);
	KMeanAverage<float>* KMean = new KMeanAverage<float>[NoOfKMeans];

	do {
		Change = false;
		MakeClusters(Img, KMean, Centroids, NoOfKMeans);
		UpdateCentroids<data>(KMean, Centroids, NoOfKMeans, Change);

		for (int i = 0; i < NoOfKMeans; i++)
			KMean[i].Clear();

	} while (Change);

	ApplyMasking(Img, KCImage, Centroids, NoOfKMeans);
	ClearExtra(KCImage);
	ConvertImage(KCImage);
}