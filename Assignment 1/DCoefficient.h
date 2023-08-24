#pragma once
#include "Support.h"

template <typename data>
double DiceCoefficient(Image<data>& GroundTruth, Image<data>& Detected)
{
	const int rows = GroundTruth.Rows, cols = GroundTruth.Cols;
	float TP = 0, FN = 0, FP = 0;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (GroundTruth.Array[i][j] != 0 && Detected.Array[i][j] != 0)
				TP++;
			else if (GroundTruth.Array[i][j] != 0 && Detected.Array[i][j] == 0)
				FN++;
			else if (GroundTruth.Array[i][j] == 0 && Detected.Array[i][j] != 0)
				FP++;
		}

	return (2 * TP) / (FN + (2 * TP) + FP);
}