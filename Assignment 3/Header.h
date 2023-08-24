#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include "General.h"
using namespace std;

const int StrToInt(const string& str)
{
	//return stoi(str);
	bool neg = false;
	int res = 0, i = 0;

	if (str[0] == '-')
	{
		i++; neg = true;
	}
	for (; i < str.length(); i++)
		res = (res * 10) + (str[i] - 48);

	if (neg) return res * (-1);
	else return res;
}

int CountVertices(string line, int& count)
{
	count = 0;
	for (int i = 0; line[i] != '\0'; i++)
		if (line[i] == ',')
			count++;
	return count;
}

void GenerateMatrix(int**& Array, const int size)
{
	Array = new int* [size];
	for (int i = 0; i < size; i++)
		Array[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			Array[i][j] = 0;
}
template <class data>
void GenerateArray(data*& Array, const int size)
{
	Array = new data[size];
}

string GetData(string line, int& index)
{
	string res;
	bool Quotation = false;

	if (index >= line.length())
		return "";
	while (line[index] == ' ' || line[index] == ',') index++;
	while (line[index] != '\0' && line[index] != '\n' && index < line.length())
	{
		if (line[index] == ',' && !Quotation) break;
		else if (line[index] == '\"' && !Quotation) Quotation = true;
		else if (line[index] == '\"' && Quotation) Quotation = false;
		else res += line[index];
		index++;
	}

	index++;
	return res;
}

int StrToInt(string& str)
{
	int res = 0;
	for (int i = 0; i < str.length(); i++)
		res = (res * 10) + (str[i] - 48);
	str = "";
	return res;
}

bool IsLetter(const char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == ' ');
}

int ClearLetters(const string& str)
{
	int index = 0;
	while (str[index] != '\0' && IsLetter(str[index++]));
	return index;
}

void ExtractData(const string& Dataline, int**& Array, const int index)
{
	int col = 0;
	string str;

	for (int i = ClearLetters(Dataline); Dataline[i] != '\0'; i++)
		if (Dataline[i] == ',')
			Array[index][col++] = StrToInt(str);
		else str += Dataline[i];

	Array[index][col] = StrToInt(str);
}
void DisplayArray(string* Array, const int size)
{
	for (int i = 0; i < size; i++)
		cout << Array[i] << " ";
	cout << endl;
}
void DisplayMatrix(int** Array, const int size)
{
	for (int i = 0; i < size; i++, cout << endl)
		for (int j = 0; j < size; j++)
			if (Array[i][j] < 10)
				cout << Array[i][j] << "   ";
			else if (Array[i][j] < 100)
				cout << Array[i][j] << "  ";
			else cout << Array[i][j] << " ";
}
void GenerateMap(string*& Arr, const int size)
{
	string Dataline;
	ifstream file("GraphData.csv", ios::in);

	getline(file, Dataline);
	for (int i = 0, index = 0; i < size; i++)
		Arr[i] = GetData(Dataline, index);
	file.close();
}

int** ReadFromFile()
{
	int** Array;
	int Vertices;
	string Dataline;
	ifstream file("GraphData.csv", ios::in);
	if (file.fail()) { cout << "Unable to Open File" << endl; return nullptr; }

	getline(file, Dataline);
	GenerateMatrix(Array, CountVertices(Dataline, Vertices));

	for (int index = 0; getline(file, Dataline); index++)
		ExtractData(Dataline, Array, index);

	file.close();
	//DisplayMatrix(Array, Vertices);
	//cout << "=================================================================================\n";
	return Array;
}
//
//class Graph;
//
//class GNode {
//public:
//	int idx;
//	int weight;
//
//	GNode(const int id = 0, const int w = 0) :idx(id), weight(w) {}
//	GNode(const GNode& Other) :idx(Other.idx), weight(Other.weight) {}
//	bool operator==(const GNode& Other) const
//	{
//		return this->idx == Other.idx;
//	}
//	bool operator<(const GNode& Other) const
//	{
//		return this->weight == Other.weight;
//	}
//	bool operator>(const GNode& Other) const
//	{
//		return this->weight == Other.weight;
//	}
//	bool operator>=(const GNode& Other) const
//	{
//		return this->weight == Other.weight;
//	}
//	friend class Graph;
//};
//
//class GEdge {
//	int src, dst;
//	int weight;
//public:
//	GEdge(const int s, const int d, const int w) : src(s), dst(d), weight(w) {}
//};
//
//class MinQueue {
//	int size;
//	LinkedList<GNode> queue;
//public:
//	MinQueue() { size = 0; }
//	void push(const GNode val)
//	{
//		size++;
//		queue.InsertSorted(val);
//	}
//	GNode pop()
//	{
//		size--;
//		if (!queue.IsEmpty()) return GNode(-1, -1);
//		GNode val = queue.Front();
//		queue.Delete();
//		return val;
//	}
//	void DecreaseKey(const GNode val)
//	{
//		queue.DeleteValue(val);
//		push(val);
//	}
//	bool IsEmpty()
//	{
//		return queue.IsEmpty();
//	}
//};
//
//class Visited {
//	bool* Visits;
//	const int Total;
//	void InitArr()
//	{
//		for (int i = 0; i < Total; i++)
//			Visits[i] = false;
//	}
//public:
//	Visited(const int Size) : Total(Size) { Visits = new bool[Size]; InitArr(); }
//	bool IsVisited(const int i) { return Visits[i]; }
//	void MarkVisited(const int i) { Visits[i] = true; }
//};
//
//class SPTSet {
//	GNode* MinDistance;
//	const int total;
//
//	void SortDistances()
//	{
//		GNode temp;
//		for(int i=0 ;i<total;i++)
//			for (int j = i; j < total; j++)
//			{
//				temp = MinDistance[i];
//				MinDistance[j] = MinDistance[i];
//				MinDistance[i] = temp;
//			}
//	}
//public:
//	SPTSet(const int size) : total(size)
//	{
//		MinDistance = new GNode[size];
//		for (int i = 0; i < size; i++)
//		{
//			MinDistance->idx = i;
//			MinDistance->weight = INT16_MAX;
//		}
//	}
//	friend class Graph;
//};
//
//class SPTMatrix {
//public:
//
//	int** Matrix;
//	const int size;
//	SPTMatrix(const int s) : size(s)
//	{
//		Matrix = new int* [size];
//		for (int i = 0; i < size; i++)
//		{
//			Matrix[i] = new int[size];
//			for (int j = 0; j < size; j++)
//				Matrix[i][j] == INT16_MAX;
//		}
//	}
//
//};
//
//class Graph{
//	int MaxVertices;
//	int Vertices;
//	LinkedList<GNode>** AdjList;
//	string* Map;
//
//	const int GetNodeIndex(const string str)
//	{
//		for (int i = 0; i < Vertices; i++)
//			if (Map[i] == str)
//				return i;
//		return (-1);
//	}
//public:
//	Graph(int** Array, int size, const int Max) :MaxVertices(Max)
//	{
//		Vertices = size;
//		Map = new string[MaxVertices];
//		GenerateArray(Map, MaxVertices);
//		GenerateMap(Map, Vertices);
//
//		AdjList = new LinkedList<GNode>*[Vertices];
//
//		for (int i = 0; i < size; i++)
//		{
//			AdjList[i] = new LinkedList<GNode>;
//			for (int j = 0; j < size; j++)
//				if (Array[i][j] != 0)
//					AdjList[i]->Insert(GNode(j, Array[i][j]));
//		}
//	}
//	void addNode(const string key)
//	{
//		AdjList[Vertices] = new LinkedList<GNode>;
//		Map[Vertices++] = key;
//	}
//	void deleteNode(const string key)
//	{
//		int index = GetNodeIndex(key);
//
//		for(int i=0  ;i<Vertices;i++)
//			AdjList[i]->DeleteValue(GNode(index));
//
//		Map[index] = "";
//		AdjList[index]->~LinkedList();
//		AdjList[index]->Head = nullptr;
//	}
//	void addEdge(const string src, const string dst, const int weight)
//	{
//		int srcIndex = GetNodeIndex(src), dstIndex = GetNodeIndex(dst);
//
//		if (srcIndex == -1) { cout << "Source Index Not in Graph" << endl; return; }
//		if (dstIndex == -1) { cout << "Destination Index Not in Graph" << endl; return; }
//		cout << Map[srcIndex] << Map[dstIndex] <<endl;
//		AdjList[srcIndex]->Insert(GNode(dstIndex, weight));
//		AdjList[dstIndex]->Insert(GNode(srcIndex, weight));
//	}
//	void deleteEdge(const string src, const string dst)
//	{
//		int srcIndex = GetNodeIndex(src), dstIndex = GetNodeIndex(dst);
//
//		AdjList[srcIndex]->DeleteValue(GNode(dstIndex));
//		AdjList[dstIndex]->DeleteValue(GNode(srcIndex));
//	}
//	void printGraph()
//	{
//		for (int i = 0; i < Vertices; i++)
//		{
//			cout << Map[i] << ": ";
//			if (!AdjList[i]->IsEmpty()) cout << "-> ";			
//			AdjList[i]->Display(Map, Vertices);
//		}
//	}
//	string printsingleLink(string str)
//	{
//		string res;
//		int index = GetNodeIndex(str);
//		if (index == -1) { return ""; }
//
//		res += str + ":";
//		res += AdjList[index]->MakeLinkLine(Map);
//		cout << res;
//		return res;
//	}
//	void shortestPathfromOnetoall(string curr)
//	{
//		int Start = GetNodeIndex(curr);
//		//SPTSet MinD(Vertices);
//		///MinD.MinDistance[Start] = 0;
//		//SPTMatrix MinDist(Vertices);
//
//		int* MinDist = new int[Vertices];
//		for (int i = 0; i < Vertices; i++)
//			MinDist[i] = INT16_MAX;
//		
//		Visited V(Vertices);
//
//		//MinQueue Que;
//		////Que.push(GNode(Start));
//		//for (int i = 0; i < Vertices; i++)
//		//	if (i == Start)
//		//		Que.push(GNode(Start));
//		//	else 
//		//		Que.push(GNode(i, INT16_MAX));
//			
//		int dist;
//		GNode temp;
//		LLNode<GNode>* links = AdjList[Start]->Head;
//		V.MarkVisited(Start);
//		MinDist[Start] = 0;
//
//		while (links != nullptr)
//		{
//			temp = links->Data;
//
//
//
//
//			links = links->Next;
//		}
//
//		//while (!V.)
//		//{
//		//	//temp = Que.pop();
//		//	V.MarkVisited(temp.idx);
//		//	links = AdjList[temp.idx]->Head;
//
//		//	while (links != nullptr)
//		//	{
//		//		dist = links->Data.weight;
//		//		if(!V.IsVisited(links->Data.idx))
//		//		{ 
//
//		//		}
//		//		links = links->Next;
//		//	}
//
//		//}
//	}
//};

class Graph;

//class GNode {
//public:
//	int idx;
//	int weight;
//
//	GNode(const int id = 0, const int w = 0) :idx(id), weight(w) {}
//	GNode(const GNode& Other) :idx(Other.idx), weight(Other.weight) {}
//	bool operator==(const GNode& Other) const
//	{
//		return this->idx == Other.idx;
//	}
//	bool operator<(const GNode& Other) const
//	{
//		return this->weight == Other.weight;
//	}
//	bool operator>(const GNode& Other) const
//	{
//		return this->weight == Other.weight;
//	}
//	bool operator>=(const GNode& Other) const
//	{
//		return this->weight == Other.weight;
//	}
//	friend class Graph;
//};
//
//class MinQueue {
//	int size;
//	LinkedList<GNode> queue;
//public:
//	MinQueue() { size = 0; }
//	void push(const GNode val)
//	{
//		size++;
//		queue.InsertSorted(val);
//	}
//	GNode pop()
//	{
//		size--;
//		if (!queue.IsEmpty()) return GNode(-1, -1);
//		GNode val = queue.Front();
//		queue.Delete();
//		return val;
//	}
//	void DecreaseKey(const GNode val)
//	{
//		queue.DeleteValue(val);
//		push(val);
//	}
//	bool IsEmpty()
//	{
//		return queue.IsEmpty();
//	}
//};
//
//class Visited {
//	bool* Visits;
//	const int Total;
//	void InitArr()
//	{
//		for (int i = 0; i < Total; i++)
//			Visits[i] = false;
//	}
//public:
//	Visited(const int Size) : Total(Size) { Visits = new bool[Size]; InitArr(); }
//	bool IsVisited(const int i) { return Visits[i]; }
//	void MarkVisited(const int i) { Visits[i] = true; }
//};

class Graph {
	int** AdjMatrix;
	int MaxVertices;
	int Vertices;
	string* Map;

	const int GetNodeIndex(const string str)
	{
		for (int i = 0; i < Vertices; i++)
			if (Map[i] == str)
				return i;
		return (-1);
	}
public:
	Graph(int**, const int , const int);
	bool IsEdge(const int, const int);
	void Print();


	void deleteNode(const string);
	void deleteEdge(const string, const string);
	void addNode(const string );
	void addEdge(const string, const string, const int);
	string printsingleLink(const string);
	void printGraph();
	void shortestPathfromalltoone(const string);
	void shortestPathfromOnetoall(const string);
	string ShortestRoutefrompair(const string, const string);
};

void InitMatrix(int**& Arr, const int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			Arr[i][j] = 0;
}


Graph::Graph(int** Array,const int c, const int Max)
{
	MaxVertices = Max;
	Vertices = c;
	Map = new string[MaxVertices];
	AdjMatrix = new int* [MaxVertices];
	for (int i = 0; i < MaxVertices; i++)
		AdjMatrix[i] = new int[MaxVertices];

	InitMatrix(AdjMatrix, MaxVertices);
	GenerateMap(Map, Vertices);

	for (int i = 0; i < Vertices; i++)
		for (int j = 0; j < Vertices; j++)
			AdjMatrix[i][j] = Array[i][j];
}

bool Graph::IsEdge(const int Src, const int Dst)
{
	if (Src > Vertices - 1 || Dst > Vertices - 1)
		return false;
	return (AdjMatrix[Src][Dst] != -1);
}

void Graph::Print()
{

	for (int i = 0; i < Vertices; i++, cout << endl)
		for (int j = 0; j < Vertices; j++)
			cout << AdjMatrix[i][j] << " ";

	cout << endl;
}

inline void Graph::addEdge(const string src, const string dst, const int w)
{
	int SrcIndex = GetNodeIndex(src), DstIndex = GetNodeIndex(dst);

	if (SrcIndex == -1) { cout << "Source Not in Graph" << endl; return; }
	if (DstIndex == -1) { cout << "Destination Not in Graph" << endl; return; }

	AdjMatrix[SrcIndex][DstIndex] = w;
	AdjMatrix[DstIndex][SrcIndex] = w;
}

inline string Graph::printsingleLink(const string src)
{
	bool start = false;
	string str = src + ":";
	int Index = GetNodeIndex(src);

	for (int i = 0; i < Vertices; i++)
		if (AdjMatrix[Index][i] != 0)
		{
			if (!start) { str += " "; start = true; }
			str += "-> " + Map[i];
		}
	return str;
}

inline void Graph::printGraph()
{
	for (int i = 0; i < Vertices; i++)
	{
		cout << Map[i] << ": ";
		for (int j = 0; j < Vertices; j++)
			if (AdjMatrix[i][j] != 0)
				cout << " -> " << Map[j];
		cout << endl;
	}
}

inline void Graph::deleteNode(const string str)
{
	int index = GetNodeIndex(str);
	for (int i = 0; i < Vertices; i++)
	{
			AdjMatrix[index][i] = 0;
			AdjMatrix[i][index] = 0;
	}
}

inline void Graph::deleteEdge(const string S, const string D)
{
	int Src = GetNodeIndex(S), Dst = GetNodeIndex(D);

	if (Src > Vertices - 1 || Dst > Vertices - 1) return;
	AdjMatrix[Src][Dst] = 0;
}

inline void Graph::addNode(const string str)
{
	if (Vertices >= MaxVertices)
	{cout << "Graph Capacity Full" << endl; return;}

	Map[Vertices] = str;
	Vertices++;
}

int miniDist(int VertexWVal[], bool visited[])
{
	int minimum = INT_MAX, idx;
	int CurrTotalNodes = -1;

	while (CurrTotalNodes++ < 25)
		if (visited[CurrTotalNodes] == false && VertexWVal[CurrTotalNodes] <= minimum)
		{
			minimum = VertexWVal[CurrTotalNodes];
			idx = CurrTotalNodes;
		}

	return idx;
}

void printPath(int* PredLink, int index, string* Vertex)
{
	if (PredLink[index] == -1)
		return;
	cout << Vertex[index] << " -> ";
	printPath(PredLink, PredLink[index], Vertex);
}

string PrintPairPath(int* PredLink, int index, string* vertix)
{
	if (PredLink[index] == -1) return "";
	else return vertix[index] + "-> " + PrintPairPath(PredLink, PredLink[index], vertix);
}

void DijkstraAlgo(int** graph, int Src, string* Maptable)
{
	int VertexWVal[25];
	bool visited[25];
	int path[25];

	for (int k = 0; k < 25; k++)
	{
		VertexWVal[k] = INT_MAX;
		visited[k] = false;
		path[k] = -1;
	}

	VertexWVal[Src] = 0;

	for (int k = 0; k < 25; k++)
	{
		int m = miniDist(VertexWVal, visited);
		visited[m] = true;

		for (int i = 0; i < 25; i++)
			if (!visited[i] && graph[m][i] && VertexWVal[m] != INT_MAX
				&& VertexWVal[m] + graph[m][i] < VertexWVal[i]) {
				VertexWVal[i] = VertexWVal[m] + graph[m][i];
				path[i] = m;
			}
	}

	for (int i = 0; i < 25; i++)
		if (path[i] == -1) 
			cout << "No path exists: " << endl;
		else
		{
			printPath(path, i, Maptable);
			cout << Maptable[Src] << endl << "Distance = " << VertexWVal[i] << endl;
		}
}

void DijkstraAlgoAll(int** graph, int Src, string* Maptable, int Dst)
{
	int VertexWVal[25];
	bool visited[25];
	int path[25];

	for (int i = 0; i < 25; i++)
	{
		VertexWVal[i] = INT_MAX;
		visited[i] = false;
		path[i] = -1;
	}

	VertexWVal[Src] = 0;
	for (int i = 0; i < 25; i++)
	{
		int m = miniDist(VertexWVal, visited);
		visited[m] = true;

		for (int j = 0; j < 25; j++) 
			if (!visited[j] && graph[m][j] && VertexWVal[m] != INT_MAX 
				&& VertexWVal[m] + graph[m][j] < VertexWVal[j]) {
				VertexWVal[j] = VertexWVal[m] + graph[m][j];
				path[j] = m;
			}
	}

	if (path[Dst] == -1) 
		cout << "No path exists: " << endl;
	else
	{
		printPath(path, Dst, Maptable);
		cout << Maptable[Src] << endl << "Distance = " << VertexWVal[Dst] << endl;
	}
}


string DijkstraAlgoPair(int** graph, int Src, string* Maptable, int Dst)
{
	int VertexWVal[25];
	bool visited[25];
	int path[25];

	for (int k = 0; k < 25; k++)
	{
		VertexWVal[k] = INT_MAX;
		visited[k] = false;
		path[k] = -1;
	}

	VertexWVal[Src] = 0;

	for (int k = 0; k < 25; k++)
	{
		int m = miniDist(VertexWVal, visited);
		visited[m] = true;
		for (int k = 0; k < 25; k++) 
			if (!visited[k] && graph[m][k] && VertexWVal[m] != INT_MAX
				&& VertexWVal[m] + graph[m][k] < VertexWVal[k]) {
				VertexWVal[k] = VertexWVal[m] + graph[m][k];
				path[k] = m;
			}
	}

	if (path[Dst] == -1)	return "No path exists:";
	else	return PrintPairPath(path, Dst, Maptable) + Maptable[Src];
}


inline void Graph::shortestPathfromOnetoall(const string Src)
{
	int SrcIndex = GetNodeIndex(Src);
	for (int i = 0; i < 25; i++) 
		DijkstraAlgoAll(AdjMatrix, i, Map, SrcIndex);
}

inline void Graph::shortestPathfromalltoone(const string Src)
{
	int SrcIndex = GetNodeIndex(Src);
	DijkstraAlgo(AdjMatrix, SrcIndex, Map);
}

inline string Graph::ShortestRoutefrompair(const string Src, const string Dst)
{
	int SrcIndex = GetNodeIndex(Src), DstIndex = GetNodeIndex(Dst);
	return DijkstraAlgoPair(AdjMatrix, DstIndex, Map, SrcIndex);
}