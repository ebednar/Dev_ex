#include <iostream>

using namespace std;

class graphObj
{
private:
	// graph parametrs
	int		size;
	int**	graph;
	float	density;
private:
	// function for random probability
	inline float prob() {return (rand() % 100) / 100.0f;}
	// "graph is connected" algorithm
	bool is_connected(int *graph[], int size)
	{
		int old_size = 0, c_size = 0;
		bool* close = new bool[size];
		bool* open = new bool[size];
		for (int i = 0; i < size; ++i)
			open[i] = close[i] = false;
		open[0] = true;
		while (c_size < size)
		{
			for (int i = 0; i < size; ++i)
			{
				old_size = c_size;
				if (open[i] && (close[i] == false))
				{
					close[i] = true;
					c_size++;
					for (int j = 0; j < size; ++j)
						open[j] = open[j] || graph[i][j];
				}
			}
			if (c_size == size) // connected
				return true;
			if (old_size == c_size) // disconnected
				return false;
		}
		return false;
	}
public:
	// constructor with size of graph and edge density as arguments
	graphObj(int size = 5, float density = 0.3):size(size), density(density)
	{
		graph = new int*[size];
		for (int i = 0; i < size; ++i)
			graph[i] = new int[size];
		for (int i = 0; i < size; ++i)
			for (int j = i; j < size; ++j)
				if (i == j)
					graph[i][j] = false; // no loops
				else if (prob() < density)
					graph[i][j] = graph[j][i] = rand() % 9 + 1; // random cost of edges 1..10
	};
	// print matrix of graph in console
	void printGraph()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
				cout << " " << graph[i][j];
			cout << endl; // new line
		}
	}
	// check if graph is connected or disconnected
	void checkConnection()
	{
		bool connect = is_connected(graph, size);
		if (connect)
			cout << "graph is connected" << endl;
		else
		{
			cout << "graph is disconnected" << endl;
			//exit(0);
		}
	}
	// find shortest path between two nodes
	int shortestPath(int node1, int node2)
	{
		int  c_size = 0;
		bool* close = new bool[size]; // close set
		bool* open = new bool[size]; // open set
		int* values = new int[size]; // value of each node
		for (int i = 0; i < size; ++i)
		{
			open[i] = close[i] = false;
			values[i] = 10000; // initial values of nodes
		}
		open[node1] = true;
		values[node1] = 0;
		int current = node1;
		while (c_size < size)
		{
			close[current] = true;
			c_size++;
			for (int i = 0; i < size; ++i) // check edges of current node
			{
				if (graph[current][i] != 0 && current != i && values[i] > values[current] + graph[current][i] && close[i] == false)
				{
					values[i] = values[current] + graph[current][i];
					open[i] = true;
				}
			}
			// choose new node from open set
			for (int i = 0; i < size; ++i)
			{
				if (open[i] == true && close[i] == false)
				{
					current = i;
					break ;
				}
			}
			// search for minimal value in open set
			for (int i = current; i < size; ++i)
			{
				if (open[i] == true && close[i] == false && values[i] < values[current])
					current = i;
			}
			if (current == node2) // shortest path is found
				break ;
		}
		cout << values[node2] << endl;
		return values[current];
	}
	void avShortestPath()
	{
		int node2;
		float result = 0.0f;
		int nb = 0;
		for (node2 = 1; node2 < size; ++node2) // check all paths from first node to others
		{
			nb++;
			result += shortestPath(0, node2);
		}
		result /= nb;
		// result
		cout << "average shortest path is " << result << endl;
	}
	// destructor
	~graphObj()
	{
		// free memory for each matrix line
		for (int i = 0; i < size; ++i)
			delete(graph[i]);
		// free main pointer
		delete(graph);
		cout << "graph is deleted" << endl;
	}
};

int main(void)
{
	srand(time(0));
	// create a graph with 50 nodes and 40% density
	graphObj* myGraph = new graphObj(10, 0.1f);
	// print matrix in console
	myGraph->printGraph();
	// check if graph is conneted
	myGraph->checkConnection();
	// if graph is connected
	// Dijkstra algorithm
	myGraph->shortestPath(0, 9);

	return 0;
}