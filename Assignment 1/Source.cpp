#include "DCoefficient.h"
#include "CCLabelling.h"
#include "KClustering.h"
#include "RLCode.h"

//unsigned short Array[9][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//					{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},
//					{0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0},
//					{0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0},
//					{0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1},
//					{0,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0},
//					{0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1},
//					{0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1},
//					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
//};
//Mat res = Mat(9 , 16 , CV_UC1 , Array);

int main()
{
	Mat Colored = imread("C:/A1Resources/Original Images/IMD171.bmp", CV_16UC1);
	Mat Lesion = imread("C:/A1Resources/Ground Truths/IMD171_lesion.bmp",CV_16UC1);
	Mat Segment = imread("C:/A1Resources/Segmented Outputs/mIMD171.bmp",CV_16UC1);

	Image<unsigned short> ImgSeg(Segment), ImgCol(Colored),
		CCLImage(Segment) , KCImage(Colored), Les(Lesion);

	cout << "Dice Coefficients : " << endl
		<< "------------------------------------------" << endl;

	//Task 1 Control Code
	ApplyCCL<unsigned short>(ImgSeg, CCLImage);
	cout << "Connected Components Labelling : " << DiceCoefficient(Les, CCLImage) << endl;

	//Task 2 Control Code
	ApplyKClustering(ImgCol, KCImage, 2);
	cout << "K Mean Clustering : " << DiceCoefficient(Les, KCImage) << endl << endl;

	imwrite("C:/A1Resources/ResultCCL.bmp", CCLImage.dst);
	imwrite("C:/A1Resources/ResultKCL.bmp", KCImage.dst);
	imwrite("C:/A1Resources/ResultM.bmp", Segment);
	imwrite("C:/A1Resources/ResultN.bmp", Les.dst);


	//Task4 Control Commands
	//LLArray<unsigned short> List;
	//List.ConvertToRLC(Les);
	//List.Display();

	return 0;
}
