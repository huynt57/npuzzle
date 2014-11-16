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

#define maxn 100
#define bignum 1000000

using namespace std;

typedef pair<int, int> PII;
typedef unsigned long long ULL;
typedef long long LL;

int size;
int h;
int moves;

struct State {
    int g; //so buoc tu diem bat dau den trang trai
    int heu; // ham danh gia
    int board[maxn][maxn]; //gia tri cua bang tai mot state

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

    State() {
        g = 0;
        h = 1000000;
        memset(board, 0, sizeof (board[0][0]) * maxn * maxn);
    }

    void swap(State &nextState, int &x_blank, int &y_blank, int &x_new_pos, int &y_new_pos) {
        //	cout << "22";
        nextState.board[x_blank][y_blank] = nextState.board[x_new_pos][y_new_pos];
        nextState.board[x_new_pos][y_new_pos] = 0;
        nextState.g++;

    }

    bool moveTheBlankTitle(State &nextState, int move) {
        int x_blank; //x of blank title
        int y_blank; //y of blank title
        int x_new_pos;
        int y_new_pos;
        nextState.findPosOfBlankTitle(x_blank, y_blank);


        //if (x_blank - 1 < 0 || y_blank - 1  < 0 || x_blank + 1 > size || y_blank + 1 > size) {
        //		return false;

        /*try to move
//	}
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
        //cout << x_blank << " " << y_blank << endl;
        //cout << x_new_pos << " " << y_new_pos << endl;
        //	FOR(i, 0, size-1)
        //		FOR(j, 0, size-1) {
        //			cout << nextState.board[i][j];
        //		}
        //		cout << endl;
        if (x_new_pos < 0 || y_new_pos < 0 || x_new_pos >= size || y_new_pos >= size) {
            return false;
        } else {
            swap(nextState, x_blank, y_blank, x_new_pos, y_new_pos);
        }
        //FOR(i, 0, size-1)
        //		FOR(j, 0, size-1) {
        //			cout << nextState.board[i][j];
        //		}
        //		cout << endl;

        return true;
    }

};

State goalState;
State initState;

struct compareTwoState {

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
//ham danh gia cac o khong o dung vi tri

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

//ham danh gia manhatan

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


//ham danh gia theo chim bay

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
// hàm chon hàm danh gia

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

struct comparePathCost {

    bool operator()(const State &state1, const State &state2) const {
        return state1.g + chooseHeuristic(h, state1) > state2.g + chooseHeuristic(h, state2);
    }
};


vector <State> successor; //generated State

set<State, compareTwoState> checkDuplicateState;
set<State>::iterator cds;
priority_queue<State, vector<State>, comparePathCost> bestCost;

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

void printState(State state) {

    FOR(i, 0, size - 1) {
        FOR(j, 0, size - 1)
        cout << state.board[i][j] << " ";
        cout << endl;
    }
    cout << state.g << endl;
}

void printSet() {
    cout << "----------------\n";
    for (cds = checkDuplicateState.begin(); cds != checkDuplicateState.end(); ++cds) {
        printState(*cds);
    }
    cout << "----------------\n";
}

bool check2(State &s1, State s2) {

    FOR(i, 0, size - 1) {

        FOR(j, 0, size - 1) {
            if (s1.board[i][j] != s2.board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool check(State state) {
    for (cds = checkDuplicateState.begin(); cds != checkDuplicateState.end(); ++cds) {
        if (check2(state, *cds))
            return true;
    }
    return false;
}

void makeNextState(State nextState, int move) {
    //	printState(nextState);
    if (nextState.moveTheBlankTitle(nextState, move)) {

        const bool is_in = checkDuplicateState.find(nextState) != checkDuplicateState.end();
        //	bool is_in = check(nextState);
        //	cout << is_in << endl;
        if (!is_in) {
            //	cout << "2";
            //		printState(nextState);
            checkDuplicateState.insert(nextState);
            successor.push_back(nextState);
            bestCost.push(nextState);
        }
    }
}

void addInitState() {
    checkDuplicateState.insert(initState);
    successor.push_back(initState);
    bestCost.push(initState);
}

void addAllNextState(State &nextState) {
    //	printSet();
    //	printState(nextState);

    FOR(i, -2, 2) {
        makeNextState(nextState, i);
        //	cout << endl;
    }
    //	cout << endl;
}

int solve() {
    //cout << "2";
    addInitState();
    while (!bestCost.empty()) {
        //	cout << "2";
        State current = bestCost.top();
        bestCost.pop();
        if (compareState(current, goalState)) {
            cout << current.g << " ";
            return 0;
        } else {
            addAllNextState(current);
        }
    }
    return -1;
}

int main() {
    freopen("nPuzzle.inp", "r", stdin);
    freopen("nPuzzle.out", "w", stdout);
    input();
    solve();
    cout << checkDuplicateState.size();
    return 0;
}

