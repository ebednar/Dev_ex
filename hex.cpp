#include <iostream>
#include <vector>

using namespace std;

enum class Color {BLUE, RED}; // enumeration for players' colors

struct node // node of graph
{
	int x, y; // coords
	int cost; // cost for path
};
struct point
{
	int i, j;
};
class Hex
{
private:
	int size; // size of board
	int g_size; // size * size
	char** board; // pointer to board
	char** board_AI; // board for AI evals
	Color player; // player color
	bool is_AI;
	bool first_player;
public:
	Hex(int size = 5, bool AI = false, bool first_player = true)
	:size(size), is_AI(AI), first_player(first_player) // game constructor
	{
		g_size = size * size;
		// allocate memory for board
		board = new char*[size]; // main board
		board_AI = new char*[size]; // board for AI calculations
		for (int i = 0; i < size; ++i)
		{
			board[i] = new char[size];
			board_AI[i] = new char[size];
		}
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				board[i][j] = '.'; // fill board with '.' char
		if (first_player == true)
			player = Color::BLUE;
		else
			player = Color::RED;
	}
	~Hex() // destructor
	{
		for (int i = 0; i < size; ++i)
		{
			delete(board[i]); // free memory for each pointer on board lines
			delete(board_AI[i]);
		}
		delete(board); // free memory for pointer on pointers
		delete(board_AI);
	}
	string get_color() // get color of current player
	{
		if (player == Color::RED)
			return ("Red");
		return ("Blue");
	}
	void	print_board()  // print board on console with ASCII symbols
	{
		int i;
		for (i = 0; i < size - 1; ++i)
		{
			cout << i + 1;
			for (int j = 0; j < 2 * i; j++)
				cout << ' ';
			for (int j = 0; j < size - 1; ++j)
				cout << board[i][j] << " - ";
			cout << board[i][size - 1] << endl;
			for (int j = 0; j < 2 * i + 2; j++)
				cout << ' ';
			for (int j = 0; j < size - 1; ++j)
				cout << "\\ / ";
			cout << '\\';
			cout << endl;
		}
		cout << i + 1;
		for (int j = 0; j < 2 * i; j++)
				cout << ' ';
		for (int j = 0; j < size - 1; ++j)
				cout << board[i][j] << " - ";
			cout << board[i][size - 1] << endl;
	}
	void	print_board(char** board)  // print board on console with ASCII symbols
	{
		int i;
		for (i = 0; i < size - 1; ++i)
		{
			cout << i + 1;
			for (int j = 0; j < 2 * i; j++)
				cout << ' ';
			for (int j = 0; j < size - 1; ++j)
				cout << board[i][j] << " - ";
			cout << board[i][size - 1] << endl;
			for (int j = 0; j < 2 * i + 2; j++)
				cout << ' ';
			for (int j = 0; j < size - 1; ++j)
				cout << "\\ / ";
			cout << '\\';
			cout << endl;
		}
		cout << i + 1;
		for (int j = 0; j < 2 * i; j++)
				cout << ' ';
		for (int j = 0; j < size - 1; ++j)
				cout << board[i][j] << " - ";
			cout << board[i][size - 1] << endl;
	}
	void place() // place player's char on board
	{
		int i, j;
		string color = get_color();
		cout << color + " player, your move:" << endl;
		if (is_AI && player == Color::RED) // turn of AI
			{
				AI_place();
				player = Color::BLUE;
			}
		else
		{
			cin >> i >> j;
			if (i == -1 && j == -1) // special command to end the game
				exit(0);
			i--;
			j--;
			if (i >= 0 && j >= 0 && i < size && j < size && board[i][j] == '.') // test for valid place
			{
				if (!is_AI && player == Color::RED)
				{
					board[i][j] = 'X';
					check_end(Color::RED);
					player = Color::BLUE;
				}
				else
				{
					board[i][j] = 'O';
					check_end(Color::BLUE);
					player = Color::RED;
				}	
			}
			else
				cout << "Wrong turn!" << endl;
		}
	}
	void check_end(Color player) // check if game over
	{
		bool path = false;
		char c;
		if (player == Color::RED) // check red player's win conditions
		{
			c = 'X';
			for (int i = 0; i < size; i++)
				if(board[0][i] == c)
					for (int j = 0; j < size; j++)
						if (board[size - 1][j] == c)
							path = findPath({0, i}, {size - 1, j}, c, board);
		}
		else // check blue player's win conditions
		{
			c = 'O';
			for (int i = 0; i < size; i++)
				if(board[i][0] == c)
					for (int j = 0; j < size; j++)
						if (board[j][size - 1] == c)
							path = findPath({i, 0}, {j, size - 1}, c, board);
		}
		if (path) // game over
		{
			print_board();
			if (player == Color::RED)
				cout << "Red player Win!" << endl;
			else
				cout << "Blue player Win!" << endl;
			exit(0);
		}
	}
	void AI_place() // AI's move
	{
		int best_x, best_y; // current best move
		int best_move = 0; // initial win's ratio

		cout << "AI time!" << endl;
		for (int i = 0; i < size; i++) // look for all possible moves
			for (int j = 0; j < size; j++)
				if (board[i][j] == '.')
				{
					int eval = AI_eval(i, j);
					if (best_move < eval) // if win's ration is greater
					{
						best_move = eval;
						best_x = i;
						best_y = j;
					}
				}
		board[best_x][best_y] = 'X';
		check_end(Color::RED); // check if game over
	}
private:
	bool AI_check_end() // check if AI wins on this trial
	{
		bool path = false;
		char c = 'X';
		for (int i = 0; i < size; i++)
			if(board_AI[0][i] == c)
				for (int j = 0; j < size; j++)
					if (board_AI[size - 1][j] == c)
					{
						path = findPath({0, i}, {size - 1, j}, c, board_AI); // search path
						//print_board(board_AI);
						if (path)
							return true; // win
					}				
		return false; // loose
	}
	int AI_eval(int x, int y) // evaluate win's ratio of (x, y) turn
	{
		vector<point> empty_points;
		int vec_size, wins = 0;
		int trial = 0;
		player = Color::RED;
		board[x][y] = player == Color::BLUE ? 'O' : 'X';
		// cout << "\n\n";
		// print_board();
		while (trial < 1000) // number of trials
		{
			player = Color::RED;
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
				{
					board_AI[i][j] = board[i][j];
					if (board_AI[i][j] == '.')
						empty_points.push_back({i, j}); // fill vector of possible moves
				}
			vec_size = empty_points.size();
			while (vec_size > 0) // untill the board is full
			{
				player = player == Color::BLUE ? Color::RED : Color::BLUE;
				int k = rand() % vec_size; // randomly choose possible move
				point turn = empty_points[k];
				empty_points.erase(empty_points.begin() + k); // erase this move
				board_AI[turn.i][turn.j] = player == Color::BLUE ? 'O' : 'X';
				vec_size--;
			}
			wins += AI_check_end(); // calculate number of wins for this turn
			trial++;
		}
		board[x][y] = '.';
		//cout << "wins: " << wins << endl;
		return wins;
	}
	bool isValid(int x, int y) // check if hex is inside the board
	{
        if (x < 0 || y < 0 || x >= size || y >= size)
                return false;
        return true;
    }
	bool findPath(node node1, node node2, char c, char** board) // algorithm to find path between board edges for win condition
	{
		int  c_size = 0;
		int** values = new int*[size]; // node values
		bool** close = new bool*[size]; // close set
		vector<node> open; // open set
		for (int i = 0; i < size; i++)
		{
			values[i] = new int[size];
			close[i] = new bool[size];
		}
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
			{
				close[i][j] = false;
				values[i][j] = 10000; // initial values of nodes
			}
		open.push_back(node1); // add first node to open set
		values[node1.x][node1.y] = 0; // initial value of start node
		node current;
		while (c_size < g_size)
		{
			current = open.back(); // take node from open set
			open.pop_back(); // erase taken node from open set
			int x = current.x;
			int y = current.y;
			close[x][y] = true; // add current node to close set
			c_size++;
			for (int newX = -1; newX <= 1; newX++) // look for neighbor hexs
			{
                for (int newY = -1; newY <= 1; newY++) 
				{
					if (newX == -1 && newY == -1)
						continue;
					if (newX == 1 && newY == 1)
						continue;
					node tmp = {x + newX, y + newY};
					if ((newX != 0 || newY != 0) && isValid(tmp.x, tmp.y)) // check if hex is valid
					{
						if (board[tmp.x][tmp.y] == c && !close[tmp.x][tmp.y] && values[tmp.x][tmp.y] == 10000) // choose next hex for open set
						{
							values[tmp.x][tmp.y] = values[x][y] + 1; // increase path value
							if (node2.x == tmp.x && node2.y == tmp.y) // check if it is the destination
								return true;
							else
								open.push_back(tmp); // else add to open set
						}
					}
				}
			}
			if (open.empty()) // if open set is empty then there is no path
				return false;
		}
		return false;
	}
};

int main()
{
	int size;
	bool AI, first_player;
	cout << "Enter the size of board (5 is minimum): ";
	cin >> size;
	cout << endl;
	if (size < 5)
		size = 5;
	cout << "Turn on the AI? 1 or 0 ";
	cin >> AI;
	cout << endl;
	if (AI)
	{
		cout << "Do you want to be first player? 1 or 0 ";
		cin >> first_player;
		cout << endl;
	}
	Hex* game = new Hex(size, AI, first_player); // create our game object
	srand(time(0)); // seed for random generator
	game->print_board(); // print it on console
	while(1)
	{
		game->place(); // turn of current player
		game->print_board(); // print board in console
	}
	return 0;
}