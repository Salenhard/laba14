#include <iostream>
#include "Graph.h"
#include "VertexIterator.h"
using namespace std;
int main()
{

	setlocale(0, "ru");
	Graph<string> G;
	G.InsertVertex("Moscow");
	G.InsertVertex("Chita");
	G.InsertVertex("Ekaterinburg");
	G.InsertVertex("Novosibirsk");
	G.InsertEdge("Chita", "Ekaterinburg", 100);
	G.InsertEdge("Moscow", "Chita", 6000);
	G.InsertEdge("Ekaterinburg", "Novosibirsk", 2200);
	G.InsertEdge("Moscow", "Ekaterinburg", 4500);
	G.InsertEdge("Novosibirsk", "Moscow", 1500);
	G.InsertEdge("Novosibirsk", "Chita", 1400);
	string S;
	cout << "Вывать мин. расстояние при оправлении их ";
	cin >> S;

	VertexIterator<string> viter(G);
	for (viter.Reset(); !viter.EndOfList(); viter.Next()) {
		cout << "Минимальное расстояние от аэропорта " << S <<
			" до аэропорта " << viter.Data() << " = "
			<< G.MinimumPath(S, viter.Data()) << endl;
	}
}
