#include "Code_Files/Header.h"
#include "Code_Files/Parser.h"
#include "Code_Files/LRUsed.h"
#include "Code_Files/ObjectSeperate.h"

int main()
{
	Priority* P;
	fstream Test;
	int Startnum = 1,TotalFiles = 7;
	string Path = "Test_Files/", File = "Test-0.txt",
		Output = "Output_files/Result.txt", Filename;

	Test.open(Output, ios::out);
	if (!Test.is_open())
		cout << "Error : Unable to Create OutPut File" << endl;
	Test.close();

	for (int FileNum = Startnum; FileNum < Startnum+TotalFiles; FileNum++)
	{
		File[5] = (48 + FileNum);
		Filename = Path + File;

		Test.open(Filename, ios::in);
		if (!Test.is_open())
			cout << "Error : " << Filename << " Not Found" << endl;
		else
		{
			Test.close();
			ConsoleOutput(Parse(Filename, File), Output);
		}
	}
	SetPriority(P, Path, File, TotalFiles);
	ConsoleOutput(LeastRecentlyUsed(P, TotalFiles, 4), Output);

	return 0;
}
