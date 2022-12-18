#pragma once
#include "SeqList.h"
#include "SeqListIterator.h"
#include <stack>
#include "PQueue.h"
const int MAXGRAPHSIZE = 25;

template<class T>
class VertexIterator;
template<class T>
class Graph
{

private:
	SeqList<T> vertexList;
	int edge[MAXGRAPHSIZE][MAXGRAPHSIZE];
	int graphsize;
	int FindVertex(SeqList<T>& L, const T& vertex);
	int GetVertexPos(const T& vertex);

public:
	// конструктор
	Graph();

	// методы тестирования графа
	int GraphEmpty() const;
	int GraphFull() const;

	// методы обработки данных
	int NumberOfVertices() const;
	int NumberOfEdges() const;
	int GetWeight(const T& vertex1, const T& vertex2);
	SeqList<T>& GetNeighbors(const T& vertex);

	// методы модифицкации графа
	void InsertVertex(const T& vertex);
	void InsertEdge(const T& vertex1, const T& vertex2,const int &weight);
	void DeleteVertex(const T& vertex);
	void DeleteEdge(const T& vertex1, const T& vertex2);

	// утилиты
	void ReadGraph(const char* filename);
	int MinimumPath(const T& sVertex, const T& eVertex);
	SeqList<T>& DepthFirstSerch(const T& beginVertex);
	SeqList<T>& BreadthFirstSearch(const T& beginVertex);

	// итератор для обхода вершин
	friend class VertexIterator<T>;
};
template<class T>
int Graph<T>::FindVertex(SeqList<T>& L, const T& vertex) {
	return L.Find(vertex);
}

// конструктор
template<class T>
Graph<T>::Graph() : vertexList() {
	for (int i = 0; i < MAXGRAPHSIZE; i++)
		for (int j = 0; j < MAXGRAPHSIZE; j++)
			edge[i][j] = 0;
	graphsize = 0;
}

template<class T>
int Graph<T>::GetVertexPos(const T& vertex) {
	SeqListIterator<T> liter(vertexList);
	int pos = 0;
	while (!liter.EndOfList() && liter.Data() != vertex) {
		pos++;
		liter.Next();
	}
	return pos;
}

template<class T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) {
	int i = GetVertexPos(vertex1);
	int j = GetVertexPos(vertex2);
		if (edge[i][j] > 0)
		return edge[i][j];
	else 
		return 0;
}

template<class T>
SeqList<T>& Graph<T>::GetNeighbors(const T& vertex) {
	SeqList<T>* L;
	SeqListIterator<T> viter(vertexList);

	L = new SeqList<T>;
	int pos = GetVertexPos(vertex);
	if (pos == -1) {
		cerr << "GetNeighbors: такой вершины нет в графе." << endl;
		return *L;
	}
	for (int i = 0; i < graphsize; i++) {
		if (edge[pos][i] > 0)
			L->Insert(viter.Data());
		viter.Next();
	}
	return *L;
}

template<class T>
void Graph<T>::DeleteVertex(const T& vertex) {
	int pos = GetVertexPos(vertex);
	int row, col;

	if (pos == -1) {
		cerr << "DeleteVertex: у вершиные нет графы" << endl;
		return;
	}
	vertexList.Delete(vertex);
	graphsize--;
	for (row = 0; row < pos; row++)
		for (col = pos + 1; col < graphsize; col++)
			edge[row][col - 1] = edge[row][col];
	for (row = pos+1; row < graphsize; row++)
		for (col = pos + 1; col < graphsize; col++)
			edge[row-1][col - 1] = edge[row][col];
	for (row = pos+1; row < graphsize; row++)
		for (col = 0; col < pos; col++)
			edge[row-1][col] = edge[row][col];
}

template <class T>
SeqList<T>& Graph<T>::DepthFirstSerch(const T& beginVertex) {
	stack<T> S;

	SeqList<T>* L, adjL;
	SeqListIterator<T> iteradjL(adjL);
	T vertex;

	L = new SeqList<T>;
	S.push(beginVertex);

	while (!S.empty()) {
		vertex = S.top();
        S.pop();
		if (!FindVertex(*L, vertex)) {
			(*L).Insert(vertex);
			adjL = GetNeighbors(vertex);
			iteradjL.SetList(adjL);

			for (iteradjL.Reset(); !iteradjL.EndOfList(); iteradjL.Next())
				if (!FindVertex(*L, iteradjL.Data()))
					S.push(iteradjL.Data());
		}
	}
	return *L;
}

template<class T>
struct PathInfo
{
	T startV, endV;
	int cost;
};

template<class T>
int operator <= (const PathInfo<T>& a, const PathInfo<T> b)
{
	return a.cost <= b.cost;
}

template <class T>
int Graph<T>::MinimumPath(const T& sVertex, const T& eVertex) {
	PQueue<PathInfo<T>> PQ(MAXGRAPHSIZE);
	PathInfo<T> pathData;
	SeqList<T> L, adjL;
	SeqListIterator<T> adjLiter(adjL);
	T sv, ev;
	int mincost;

	pathData.startV = sVertex;
	pathData.endV = sVertex;
	pathData.cost = 0;
	PQ.insert(pathData);

	while (!PQ.empty()) {
		pathData = PQ.del();
		ev = pathData.endV;
		mincost = pathData.cost;

		if (ev == eVertex)
			break;
		if (!FindVertex(L, ev)) {
			L.Insert(ev);
			sv = ev;
			adjL = GetNeighbors(sv);
			adjLiter.SetList(adjL);
			for (adjLiter.Reset(); !adjLiter.EndOfList(); adjLiter.Next()) {
				ev = adjLiter.Data();
				if (!FindVertex(L, ev)) {
					pathData.startV = sv;
					pathData.endV = ev;
					pathData.cost = mincost + GetWeight(sv, ev);
					PQ.insert(pathData);
				}
			}
		}
	}
	if (ev == eVertex)
		return mincost;
	else
		return -1;
}
template<class T>
int Graph<T>::GraphEmpty() const {
	return graphsize == 0;
}

template<class T>
int Graph<T>::GraphFull() const {
	return graphsize == MAXGRAPHSIZE;
}
template<class T>
int Graph<T>::NumberOfVertices() const {
	return graphsize;
}
template<class T>
int Graph<T>::NumberOfEdges() const {
	int numOfEdges = 0;
	for (int i = 0; i < MAXGRAPHSIZE; i++)
		for (int j = i; j < MAXGRAPHSIZE; j++)
			if (edge[i][j] > 0)
				numOfEdges++;
	return numOfEdges;
}

template<class T>
void Graph<T>::InsertVertex(const T& vertex) {
	vertexList.Insert(vertex);
	graphsize++;
}
template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2,const int& weight) {
	if (vertex1 != vertex2) {
		int i = GetVertexPos(vertex1);
		int j = GetVertexPos(vertex2);
		edge[i][j] = weight;
		edge[j][i] = weight;
	}
	else {
		cerr << "Not good!";
		exit(1);
	}
}

template <class T>
void Graph<T>::DeleteEdge(const T& vertex1, const T& vertex2) {
	if (vertex1 != nullptr && vertex2 != nullptr && vertexList.Find(vertex1) && vertexList.Find(vertex2))
	{
		int i = GetVertexPos(vertex1);
		int j = GetVertexPos(vertex2);
		edge[i][j] = 0;
	}
}
// что?
template <class T>
void Graph<T>::ReadGraph(const char* filename) {
}
// что?
template <class T>
SeqList<T>& Graph<T>::BreadthFirstSearch(const T& beginVertex) {

}