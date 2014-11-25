/* 
 * University of Engineering and Technology 
 * Course AI Fall 2014 (INT3401 2)
 * Assignment 01
 * 
 * Student's name: 	Nguyen Van Giap
 * Student's code: 	12020110
 * Student's class: K57CA
 *
 * This program implements heuristic search algorithms in C++ to solve a simple 
 * game called the 15-puzzle(http://en.wikipedia.org/wiki/15_puzzle), 
 * 
 * A* search with repeated states avoidance are implemented using three admissible 
 * heuristics where each heuristics is implemented in a separate function: 
 * 		• h1 = the number of misplaced tiles 
 *		• h2 = (Manhattan distance) the sum of the distances of the tiles from 
 * 		  their goal positions 
 * 		• h3 = 
 *
 */

#include <iostream>
#include <cstdio>
#include <list>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <cstdlib>

#define MAX 1003
// typedef int State[MAX][MAX];

using namespace std;

int n, k;	
int number_optimal_moves = 0;
int number_generated_states = 0;

struct State
{
	int state[MAX][MAX];
	State* parent;
	pair<int, int> space_index;
	string code;
	int g_cost;
	int h_cost;
	int f_cost;
};

struct CompareState
{
	bool operator() (State* const & s1, State* const & s2) const
	{
		if (s1->f_cost < s2->f_cost) 
		{
			return true;
		} 
		else if (s1->f_cost == s2->f_cost) 
		{
			return s1->g_cost > s2->g_cost;
		}
		return false;
	}
};

State* initial = NULL;
State* goal = NULL;

// template<
//     class T,
//     class Container = std::vector<T>,
//     class Compare = std::less<typename Container::value_type>
// > class my_priority_queue : public std::priority_queue<T, Container, Compare>
// {
// public:
//     typedef typename
//         std::priority_queue<
//         T,
//         Container,
//         Compare>::container_type::const_iterator const_iterator;

//     const_iterator find(const T&val) const
//     {
//         auto first = this->c.cbegin();
//         auto last = this->c.cend();
//         while (first!=last) {
//             if (*first==val) return first;
//             ++first;
//         }
//         return last;
//     }
// };

void print_2d_array(State * s)
{
	cout << "g = " << s->g_cost << " h = "<< s->h_cost << endl;
	for (int i = 1; i <= n; ++i)
	{	
		for (int j = 1; j <= n; ++j)
		{
			cout << s->state[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/*
 * Read input file called "nPuzzle.inp" with format: 
 * The first line contains n and a number k representing the heuristics hk 
 * separated by a space. Subsequent lines contain the initial state and the 
 * goal state. There is an empty line separating the two states.
 *
 */
void read_input() 
{
	freopen("nPuzzle.inp", "r", stdin);	
	cin >> n >> k;
	initial = new State;
	goal = new State;	
	
	for (int i = 0; i <= n + 1; ++i)
	{
		for (int j = 0; j <= n + 1; ++j)
		{
			initial->state[i][j] = -1;
			goal->state[i][j] = -1;
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{			
			cin >> initial->state[i][j];			 
			if (initial->state[i][j] == 0)
			{
				initial->space_index = make_pair(i, j);
			}
			initial->code += initial->state[i][j] + '*';
		}
	}
	initial->parent = NULL;
	// string line;
	// while (getline(cin, line) && line != "") ;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin >> goal->state[i][j];
			if (goal->state[i][j] == 0)
			{
				goal->space_index = make_pair(i, j);
			}
			initial->code += initial->state[i][j] + '*';
		}
	}
}

int get_misplaced_tiles_cost(State* s)
{
	int heuristic_cost = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (s->state[i][j] != goal->state[i][j])
				heuristic_cost++;
		}
	}
	return heuristic_cost;
}

int get_manhattan_distance_cost(State* s) 
{
	return 0;
}

int get_heuristic_cost(int heuristic, State* state)
{
	switch (heuristic) {
		case 1:
			return get_misplaced_tiles_cost(state);
			break;
		case 2:
			return get_manhattan_distance_cost(state);
			break;
		default:
			return -1;
	}
}


// /*
//  * Solve the puzzle with A* algorithm using heuristic h1: the number of misplaced tiles
//  *
//  */
// int heuristic_misplaced_tile() 
// {

// }

// // h2: (Manhattan distance) the sum of the distances of the tiles from their 
// // goal positions
// int heuristic_manhattan_distance() 
// {

// }

void calculate_cost(State* s) 
{
	if (s->parent == NULL) 
	{
		s->g_cost = 0;
	}
	else 
	{
		s->g_cost = (s->parent)->g_cost + 1;
	}

	s->h_cost = get_heuristic_cost(k, s);
	s->f_cost = s->g_cost + s->h_cost;
}

bool is_final_state(State* s)
{
	return (s->h_cost == 0);
}

void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}

string generate_state_code(State* s) 
{
	string result = "";
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{ 
			char buf[10];
			itoa(s->state[i][j], buf, 10);
			string s(buf);
			result += s + "-";
		}
	}

	return result;
}

vector<State*> generate_next_states(State* current) 
{
	vector<State*> states;

	int directions[4][2] = {
		{-1, 0}, 	// up
 		{0, 1},		// right
 		{1, 0}, 	// down
 		{0, -1}		// left
 	};
 	
 	for (int i = 0; i < 4; ++i) 
 	{ 		
 		if ((current->state[current->space_index.first + directions[i][0]][current->space_index.second + directions[i][1]]) != -1)
 		{
 			State* s = new State;
 			// s.state = current.state;
 			// copy(&current->state[0][0], &current->state[0][0] + n * n, &s->state[0][0]); print_2d_array(s->state);
 			memcpy(s->state, current->state, sizeof(current->state)); 
 			swap(&s->state[current->space_index.first][current->space_index.second], 
 				&s->state[current->space_index.first + directions[i][0]][current->space_index.second + directions[i][1]]); 			

 			s->parent = current;
 			calculate_cost(s);
 			s->space_index.first = current->space_index.first + directions[i][0];
 			s->space_index.second = current->space_index.second + directions[i][1];
 			s->code = generate_state_code(s);
 
 			// print_2d_array(s->state);

 			states.push_back(s);
 		}
 	} 	

 	return states;
}

void solve_puzzle() {
	if ((k < 0) || (k > 3)) 
	{
		cout << "Wrong input format";
		return;
	}
	
	set<string> open_codes_set;
	set<State*, CompareState> open_set;
	map<string, State*> closed_set;
	vector<State*> next_states;

	State* current;
	// int number_generated_state = 0;

	calculate_cost(initial);
	open_set.insert(initial);
	open_codes_set.insert(initial->code);
	
	while(!open_set.empty()) 
	{
		number_optimal_moves++;

		set<State*>::iterator cur = open_set.begin();
		current = new State;
		memcpy(current, *cur, sizeof(*current));

		cout << "cur"; print_2d_array(current);

		open_set.erase(cur);
		open_codes_set.erase(open_codes_set.find(current->code));

		cout << "==open set \n";
		for (std::set<State*>::iterator it=open_set.begin(); it!=open_set.end(); ++it)
		{
			print_2d_array((*it));
		}
		cout << "open set ==\n";

		if (is_final_state(current))
		{
			break;
		}		

		next_states = generate_next_states(current); 

		if (next_states.size() > 0) 
		{
			State* closed_state;
            State* open_state;
            State* next_state;

			for (int i = 0; i < next_states.size(); ++i)
			{				
				closed_state = NULL;
            	open_state = NULL;
				next_state = next_states[i]; cout << "next state"; print_2d_array(next_state);
				set<string>::iterator it;
				if ((it = open_codes_set.find(next_state->code)) != open_codes_set.end())									
				{
					set<State*>::iterator os = open_set.find(next_state);
					open_state = *os;

					if (open_state->g_cost > next_state->g_cost)
					{		
						open_codes_set.erase(it);
						open_set.insert(next_state);
					}
					cout << "shit1";cout << "==after if open set1 \n";
									for (std::set<State*>::iterator it=open_set.begin(); it!=open_set.end(); ++it)
									{
										print_2d_array((*it));
									}
									
									cout << "after if open set ==\n";
				}	
				else 
				{
					map<string, State*>::iterator cs;
					// cout << "code = " << next_state->code << endl;
					for (std::map<string, State*>::iterator it=closed_set.begin(); it!=closed_set.end(); ++it)
						cout << "c = " << it->first << endl;
//					if (closed_set.begin()!= NULL) cout << closed_set.begin()->first << endl;
					cout << next_state->code;

					if ((cs = closed_set.find(next_state->code)) != closed_set.end())
					{
						cout << "shieeet";
						closed_state = (*cs).second;
						if (closed_state->g_cost > next_state->g_cost)
						{
							//closed_set.erase(cs);
							//closed_set[next_state->code] = new State;
							memcpy(closed_set[next_state->code], next_state, sizeof(*next_state));
						}
						cout << "shit2";	cout << "==after if closed set1 \n";
											for (std::map<string, State*>::iterator it=closed_set.begin(); it!=closed_set.end(); ++it)
											{
												print_2d_array((it->second));
											}
											
											cout << "after if closed set ==\n";
					} 					
				}

				if (open_state == NULL && closed_state == NULL)			
				{
					open_set.insert(next_state);
					open_codes_set.insert(next_state->code);
					cout << "==after if open set1 \n";
					for (std::set<State*>::iterator it=open_set.begin(); it!=open_set.end(); ++it)
					{
						print_2d_array((*it));
					}
					
					cout << "after if open set ==\n";
				}
			}

			
			State* tmp = new State;
			memcpy(tmp, current, sizeof(*current));
			closed_set.insert(pair<string, State*>(current->code, tmp));

			cout << "==after if closed set1 \n";
			for (std::map<string, State*>::iterator it=closed_set.begin(); it!=closed_set.end(); ++it)
			{
				// cout << (*it).first << endl;
				print_2d_array((it->second));
			}
			
			cout << "after if closed set ==\n";

			cout << "-----------------------------------\n";
		}
	}

	if (current != NULL && !is_final_state(current))
    {
        // No solution
        number_optimal_moves = -1;
    }

	delete current;
	closed_set.clear();
}

/* 
 * Output to a file called "nPuzzle.out" with the number of optimal moves
 * (or -1 if there is no solution) and the number of generated states separated
 * by a space.
 *
 */
void write_output() {
	// freopen("nPuzzle.out", "w", stdout);
	cout << number_optimal_moves << " " << number_generated_states;

	delete initial;
	delete goal;
}

int main() {	
//	clock_t t;
//	t = clock();	

	read_input();
	
	solve_puzzle();
	write_output();

//	t = clock() - t;
  //	printf ("\nIt took me %f seconds.\n", ((float)t)/CLOCKS_PER_SEC);
	return 0;
}
