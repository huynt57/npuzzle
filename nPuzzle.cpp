/** 
*   University of Engineering and Technology
*	
*	AI Assignment 
*   Student: Nguyen The Huy
*   Class: K57CA
*   
*   Program: nPuzzle
*   Desciption: This program uses A-star algorithm to solve nPuzlle problems
*   with 3 heuristic functions (see below for more details)      
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>

#define FOR(i,a,b) for( int i=(a),_b=(b);i<=_b;i++)
#define DOW(i,b,a) for( int i=(b),_a=(a);i>=_a;i--)

#define maxn 20/* Define the init size of board */

using namespace std;

int size; /* Size of board*/
int h;/* Which heuristic function will be choose to solve problem*/
int stateGenerated;/* Number of state generated*/

/* 
 *  Struct:  State
 *  Description:  A puzzle state with properties: g, heu, and board 
 *  see below for more details
 */
struct State {
    int g; //the number from init state to current state
    int board[maxn][maxn]; //Store the numbers in a state

/* 
 *  Function:  findPosOfBlankTitle
 *  Description:  Find the coordinates of blank tile in a state
 */
    void findPosOfBlankTitle(int &x, int &y) {

        FOR(i, 0, size - 1) {

            FOR(j, 0, size - 1) {
                if (board[i][j] == 0) {
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }
/* 
 *  End of function:  findPosOfBlankTitle 
 */
 
 /* 
 *  Function:  swap
 *  Description:  Swap between blank tile and a specific tile
 */
 
    void swap(State &nextState, int &x_blank, int &y_blank, int &x_new_pos, int &y_new_pos) {
        nextState.board[x_blank][y_blank] = nextState.board[x_new_pos][y_new_pos];
        nextState.board[x_new_pos][y_new_pos] = 0;
        nextState.g++;

    }
/* 
 *  End of function:  swap 
 */

/* 
 *  Function:  moveTheBlankTile
 *  Description:  move the blank title to 4 directions. Return false if cannot 
 *	move, true if success
 */
    bool moveTheBlankTile(State &nextState, int move) {
        int x_blank; //x of blank title
        int y_blank; //y of blank title
        int x_new_pos;
        int y_new_pos;
        nextState.findPosOfBlankTitle(x_blank, y_blank);
        /*try to move
        1 - move up
        -1 = move down
        2 - move right
        -2 move left
         */
        switch (move) {
            case 1:
                x_new_pos = x_blank - 1; 
                y_new_pos = y_blank;
                break;
            case -1:
                x_new_pos = x_blank + 1;
                y_new_pos = y_blank;
                break;
            case 2:
                y_new_pos = y_blank + 1;
                x_new_pos = x_blank;
                break;
            case -2:
                y_new_pos = y_blank - 1;
                x_new_pos = x_blank;
                break;
            case 0:
                return false;
        }
        if (x_new_pos < 0 || y_new_pos < 0 || x_new_pos >= size || y_new_pos >= size) {
            return false;
        } else {
            swap(nextState, x_blank, y_blank, x_new_pos, y_new_pos);
        }
        return true;
    }
/* 
 *  End of function:  moveTheBlankTile 
 */
};
/* 
 *  End of struct:  state 
 */

State goalState;	// Store goal State
State initState; 	// Store init State

/* 
 *  Struct:  compareTwoStateInSet
 *  Description:  compare two state to use data structure set in C++. 
 */
struct compareTwoStateInSet {
    bool operator() (const State &state1, const State &state2) const {
       FOR(i, 0, size - 1) {
            FOR(j, 0, size - 1) {
                if (state1.board[i][j] > state2.board[i][j]) {
                    return false;
                } else if (state1.board[i][j] < state2.board[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }
};
/* 
 *  End of struct:  compareTwoState 
 */
 
/* 
 *  Function:  compareState
 *  Description:  compare two state. Return true if the same board, false in 
 *	others
 */ 
bool compareState(State &state1, State &state2) {
    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            if (state1.board[i][j] != state2.board[i][j]) {
                return false;
            }
        }
    }
    return true;
}
/* 
 *  End of function:  compareState 
 */

/* 
 *  Function:  findNumberInGoalState
 *  Description:  Find a specific number in goal state
 */ 
void findNumberInGoalState(int number, int &x, int &y) {
    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            if (goalState.board[i][j] == number) {
                x = i;
                y = j;
                return;
            }
        }
    }
}
/* 
 *  End of function:  findNumberInGoalState 
 */
 
/* 
 *  Function:  h1
 *  Description:  Calculate heuristic = the number of misplaced tiles
 */
int h1(State nextState) {
    int h = 0;
    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            if ((nextState.board[i][j] != goalState.board[i][j]) && nextState.board[i][j] != 0) {
                h++;
            }
        }
    }
    return h;
}
/* 
 *  End of function:  h1
 */

/* 
 *  Function:  h2
 *  Description:  Calculate heuristic = the sum of the distances of the tiles
 *  from their goal positions
 */
int h2(State nextState) {
    int h = 0;
    int x, y; //toa do se duoc gan cho o trong goal state
    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            if (nextState.board[i][j] != 0) {
                findNumberInGoalState(nextState.board[i][j], x, y);
                h += abs(x - i) + abs(y - j);
            }
        }
    }
    return h;
}
/* 
 *  End of function:  h2
 */

/* 
 *  Function:  h3
 *  Description:  Calculate heuristic = the flying distance
 */
int h3(State nextState) {
    int h = 0;
    int x, y; //toa do se duoc gan cho o trong goal state
    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            if (nextState.board[i][j] != 0) {
                findNumberInGoalState(nextState.board[i][j], x, y);
                h += sqrt(pow((x - i), 2) + pow((y - i), 2));
            }
        }
    }
    return h;
}
/* 
 *  End of function:  h3
 */
 
/* 
 *  Function:  chooseHeuristic
 *  Description:  Choose the heuristic function from input h
 */

int chooseHeuristic(int h, State state) {
    switch (h) {
        case 1:
            return h1(state);
        case 2:
            return h2(state);
        case 3:
            return h3(state);
    }
}
/* 
 *  End of function:  chooseHeuristic
 */
 
/* 
 *  Struct:  comparePathCost
 *  Description:  Compare f = g + h of two state for data structure priority queue
 *	in c++. If same f, we compare h because less h means better
 */ 
struct comparePathCost {
    bool operator()(const State &state1, const State &state2) const {
        if (state1.g + chooseHeuristic(h, state1) == state2.g + chooseHeuristic(h, state2)){
         	return (state1.g < state2.g);//compare g is better than recalculate h
    	} else {
        	return (state1.g + chooseHeuristic(h, state1) > state2.g + chooseHeuristic(h, state2));
     	}
    }
};
/* 
 *  End of struct:  comparePathCost
 */
 
set<State, compareTwoStateInSet> checkDuplicateState; // a set to store generated state and check duplicate state
priority_queue<State, vector<State>, comparePathCost> bestCost; //priority queue to find out the best path cost of states

/* 
 *  Function:  input
 *  Description:  Read size of npuzzle, heuristic function, goal and init state
 */
void input() {
    cin >> size;
    cin >> h;

    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            cin >> initState.board[i][j];
        }
    }

    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1) {
            cin >> goalState.board[i][j];
        }
    }
}
/* 
 *  End of funtion:  input
 */

/* 
 *  Function:  makeNextState
 *  Description:  make next state of a state by move the blank tile. Also check the
 *	duplicate state: if no duplicate, insert to set and priority queue
 */
void makeNextState(State nextState, int move) {
    if (nextState.moveTheBlankTile(nextState, move)) {
        const bool is_in = checkDuplicateState.find(nextState) != checkDuplicateState.end();
        if (!is_in) {
            checkDuplicateState.insert(nextState);
            bestCost.push(nextState);
            stateGenerated++;
        }
    }
}
/* 
 *  End of funtion:  makeNextState
 */

/* 
 *  Function:  addInitState
 *  Description:  Add init state to set and priority queue
 */
void addInitState() {
    checkDuplicateState.insert(initState);
    bestCost.push(initState);
}
/* 
 *  End of funtion:  addInitState
 */
 
/* 
 *  Function:  checkInitState
 *  Description:  Check if initState
 */
bool checkInitState() {
	vector <int> check;
	
	int inverse = 0;
	int x_blank = 0;
	int y_blank = 0;
	
	initState.findPosOfBlankTitle(x_blank, y_blank);
	
	FOR(i, 0, size-1) {
		FOR(j, 0, size-1) {
			check.push_back(initState.board[i][j]);
		}
	}
	
	FOR(i,0, check.size()) {
		FOR(j, i+1, check.size()-1) {
			if(check[j] > check[i]) 	inverse++;
		}
	}
	
	if(size%2!=0) {
		if (inverse%2==0) {
			return true;
		}
	} else {
		if (inverse%2==0 && x_blank%2==0) return true;
		else if (inverse%2==1&&x_blank%2==0) return true;
	}
	return false;		
}

/* 
 *  Function:  addAllNextState
 *  Description:  make next state in 4 directions
 */
void addAllNextState(State &nextState) {
    FOR(i, -2, 2) {
        makeNextState(nextState, i);
    }
}
/* 
 *  End of funtion:  addAllNextState
 */

/* 
 *  Function:  solve
 *  Description:  solve npuzzle problem by A* search
 */
int solve() {
    addInitState();
   // if(checkInitState()) {
	    while (!bestCost.empty()) {
	        State current = bestCost.top();
	        bestCost.pop();
	        if (compareState(current, goalState)) {
	            return current.g;
	        } else {
	            addAllNextState(current);
	        }
	    }
//	}
    return -1;
}
/* 
 *  End of funtion:  solve
 */

/* 
 *  Function:  output
 *  Description:  Print out the number of state generated
 */
void output() {
	cout << stateGenerated;
}
/* 
 *  End of funtion:  output
 */

/* 
 *  Function:  main
 *  Description:  Run above function
 */
int main() {
    freopen("nPuzzle.inp", "r", stdin);
    freopen("nPuzzle.out", "w", stdout);
    input(); 
    cout << solve() << " ";
    output();
    return 0;
}
/* 
 *  End of funtion:  main
 */

