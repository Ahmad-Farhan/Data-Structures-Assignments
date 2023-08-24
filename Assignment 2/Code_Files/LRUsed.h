#pragma once
#include"Header.h"
#include"sstream"

const string NumToStr(int num)
{
	stringstream ss;
	ss << num;
	string strNum = ss.str();
	return strNum;

	//string str;
	//while (num > 0)
	//{
	//	str += (num % 10 + 48);
	//	num /= 10;
	//}
	//return RevString(str);
}

const int StrToNum(const string& str)
{
	//return stoi(str);
	bool neg = false;
	int res = 0, i = 0;

	if (str[0] == '-') 
		{ i++; neg = true; }
	for (;i < str.length(); i++)
		res = (res * 10) + (str[i] - 48);
	
	if (neg) return res * (-1);
	else return res;
}

void BubbleSort(Priority*& P , const int size)
{
	Priority temp;
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
			if (P[i].priority < P[j].priority)
			{
				temp = P[i];
				P[i] = P[j];
				P[j] = temp;
			}
}

const int ExtractPData(Stack<char>& CharStack)
{
	string str = "";
	while (CharStack.Peek() != '|')
		str += CharStack.PopR();

	return StrToNum(RevString(str));
}


const int Tokenize(Stack<char>& CharStack)
{
	char ch;
	string token;
	bool TagOpen = false, PTagFound = false;
	while (!CharStack.IsEmpty())
	{
		ch = CharStack.PopR();

		if (ch == '|' && TagOpen == false)
		{
			token = ch;
			TagOpen = true;
		}
		else if (ch == '|' && TagOpen == true)
		{
			token += ch;
			TagOpen = false;

			//token = RevString(token);
			if (CompareStr(RevString(token), "|\\priorty|"))
				return ExtractPData(CharStack);
			token = "";
		}
		else token += ch;
	}
	return 0;
}

const int ExtractPriority(const string& Path)
{
	char ch;
	Stack<char> CharStack;
	ifstream file(Path, ios::in);

	while (!file.eof())
	{
		file >> ch;
		CharStack.Push(ch);
	}
	file.close();
	CharStack.Pop();

	return (Tokenize(CharStack));
}

void SetPriority(Priority*& P, string& Path, string& FileName, const int& TotalFiles)
{
	string File;
	ifstream Test;
	P = new Priority[TotalFiles];

	for (int FileNum = 0; FileNum < TotalFiles; FileNum++)
	{
		FileName[5] = (FileNum + 49);

		File = Path + FileName;
		Test.open(File, ios::in);
		if (!Test.is_open())
			cout << "Error : " << Path << " Not Found" << endl;
		else
		{
			Test.close();
			P[FileNum].FileName = FileName;
			P[FileNum].priority = ExtractPriority(File);
		}
	}
	BubbleSort(P, TotalFiles);
}

string LeastRecentlyUsed(Priority*& Files, const int size, const int QMax)
{
	int Hits = 0, Faults = 0;
	Queue<int> Que(QMax);

	for (int i = 0; i < size; i++)
	{
		if (Que.Search(Files[i].priority))
		{
			Hits++;
			Que.Enqueue(Que.Remove(Files[i].priority));
		}
		else
		{
			Faults++;
			Que.Enqueue(Files[i].priority);
		}
	}

	return "LRU Results : Total Hits : " + NumToStr(Hits) + ", Total Faults : " + NumToStr(Faults) + '\n';
}