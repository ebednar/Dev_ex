#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;

class graphObj
{
private:
	// graph parametrs
	int		size;
	int**	graph; // graph matrix
	float	density;
	int		mstCost;
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
					graph[i][j] = 0; // no loops
				else if (prob() < density)
					graph[i][j] = graph[j][i] = rand() % 18 + 3; // random cost of edges 3..20
	};
	// constructor from file
	graphObj(std::string filepath)
	{
		ifstream data(filepath);
		istream_iterator<int> start(data), end;
		// creat vector and whrite file data in it
		vector<int> vec(start, end);
		size = vec[0]; // first number of file is size of graph
		cout << "size of graph - " << size << endl;
		// graph memory allocation
		graph = new int*[size];
		for (int i = 0; i < size; ++i)
			graph[i] = new int[size];
		for (int i = 0; i < size; ++i)
			for (int j = i; j < size; ++j)
				graph[i][j] = graph[j][i] = 0; // fill grpah by initial value
		// copy edges cost from vector into graph
		for (auto i = ++(vec.begin()); i != vec.end(); i += 3)
			graph[*i][*(i + 1)] = *(i + 2); // [i][j] = cost
	}
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
			exit(0);
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
	// Jarnik-Prim mst algorithm
	void mst()
	{
		int  c_size = 0;
		bool* close = new bool[size]; // close set
		bool* open = new bool[size]; // open set
		for (int i = 0; i < size; ++i)
			open[i] = close[i] = false;
		open[0] = true;
		int current = 0;
		int next;
		mstCost = 0;
		while (c_size < size - 1) // check if we found all nodes
		{
			close[current] = true; // add node to close set
			c_size++;
			int min = 1000; // initial cmin cost
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
					if (close[i] == false && open[j] == true && graph[j][i] != 0 && graph[j][i] < min) // search for less cost edge
					{
						next = i;
						current = j;
						min = graph[j][i];
					}
			}
			cout << "from " << current << " go to " << next << endl;
			mstCost += graph[current][next];
			open[next] = true; // add node to open set
			current = next;
		}
		cout << "MST cost = " << mstCost << endl;
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
	graphObj* myGraph = new graphObj("graph.data");
	// print matrix in console
	myGraph->printGraph();
	// check if graph is conneted and exit if not
	myGraph->checkConnection();
	// if graph is connected
	// build mst
	myGraph->mst();


	return 0;
}