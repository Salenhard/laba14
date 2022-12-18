#include <iostream>
#include "Graph.h"
#include "VertexIterator.h"
using namespace std;

template <class T>
void Warshall(Graph<T>& G) {
    VertexIterator<T> vi(G), vj(G);
    int i, j, k;
    int WSM[MAXGRAPHSIZE][MAXGRAPHSIZE];
    int n = G.NumberOfVertices();

    for (vi.Reset(), i = 0; !vi.EndOfList(); vi.Next(), i++)
        for (vj.Reset(), j = 0; !vj.EndOfList(); vj.Next(), j++)
            if (i == j)
                WSM[i][i] = 1;
            else
                WSM[i][j] = G.GetWeight(vi.Data(), vj.Data());
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                WSM[i][j] != WSM[i][k] && WSM[k][j];

    for (vi.Reset(), i = 0; !vi.EndOfList(); vi.Next(), i++) {

        cout << vi.Data() << ": ";
        for (j = 0; j < n; j++)
            cout << WSM[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    setlocale(0, "ru");
    Graph<char>G;
    G.InsertVertex('A');
    G.InsertVertex('B');
    G.InsertVertex('C');
    G.InsertVertex('D');
    G.InsertVertex('E');
    G.InsertEdge('A', 'B', 1);
    G.InsertEdge('A', 'C', 1);
    G.InsertEdge('A', 'D', 1);
    cout << "Матрица достижимости:" << endl;
    Warshall(G);
}
