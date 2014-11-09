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

using namespace std;

typedef pair<int, int> PII;
typedef unsigned long long ULL;
typedef long long LL;

int size;
int h;
int init[maxn][maxn];
int goal[maxn][maxn];
int moves;
vector <State> successor;
struct State {
	int g; //so buoc tu diem bat dau den trang trai
	int h; // ham danh gia
	int board[maxn][maxn]; //gia tri cua bang tai mot state
	
	void findPosOfBlankTitle(int &x, int &y) {
		FOR(i,0, size-1) {
			FOR(j, 0, size-1) {
				if(board[i][j] == 0) {
					x = i;
					y = j;
					break;
				}
			}
		}	
}

void swap(State &nextState, int &x_blank, int &y_blank, int &x_new_pos, int &y_new_pos) {
	nextState.board[x_blank][y_blank] = nextState.board[x_new_pos][y_new_pos];
	nextState.board[x_new_pos][y_new_pos] = 0;
		
}

bool moveTheBlankTitle(State &nextState, int move) {
	int x_blank; //x of blank title
	int y_blank; //y of blank title
	int x_new_pos;
	int y_new_pos;
	nextState.findPosOfBlankTitle(x_blank, y_blank);
	
	if (x_blank - 1 < 0 || y_blank - 1  < 0 || x_blank + 1 > size || y_blank + 1 > size) {
		return false;
	}
	
	/*try to move
	1 - move up
	-1 = move down
	2 - move right
	-2 move left
	*/
	switch(move) {
		case 1:
			x_new_pos = x_blank - 1;
			y_new_pos = y_blank;
			swap(nextState, x_blank, y_blank, x_new_pos, y_new_pos);			
		case -1:
			x_new_pos = x_blank + 1;
			y_new_pos = y_blank;
			swap(nextState, x_blank, y_blank, x_new_pos, y_new_pos);
		case 2:
			y_new_pos = y_blank+1;
			x_new_pos = x_blank;
			swap(nextState, x_blank, y_blank, x_new_pos, y_new_pos);
		case -2:
			y_new_pos = y_blank-1;
			x_new_pos = x_blank;
			swap(nextState, x_blank, y_blank, x_new_pos, y_new_pos);
	}
			
	return true;
	
}
};



void input() {
	cin >> size;
	cin >> h;
	FOR(i, 0, size-1) {
		FOR(j, 0, size-1) {
			cin >> init[i][j];
		}
	}
	
	FOR(i, 0, size-1) {
		FOR(j, 0, size-1) {
			cin >> goal[i][j];
		}
	}
}

void findNumberInGoalState(int number, int &x, int &y) {
	FOR(i, 0, size - 1) {
		FOR(j, 0, size - 1) {
			if(goal[i][j] == number) {
				x = i;
				y = j;
				break;
			}
		}
	}
}

void output()
{
	cout << "1";
}

void makeNextState(State &nextState, int move) {
	if(nextState.moveTheBlankTitle(nextState, move)) {
		successor.push_back(nextState);
	}	
}


//ham danh gia cac o khong o dung vi tri
int h1(State nextState) {
	int h;
	FOR(i, 0, size - 1) {
		FOR(j, 0, size - 1) {
			if((nextState.board[i][j] != goal[i][j]) && nextState.board[i][j] != 0) {
				h++;
			}
		}
	}
	return h;
}

//ham danh gia manhatan
int h2(State nextState) {
	int h;
	int x,y; //toa do se duoc gan cho o trong goal state
	FOR(i, 0, size - 1) {
		FOR(j, 0, size - 1) {
			if(nextState.board[i][j] != 0) {
				findNumberInGoalState(nextState.board[i][j], x, y);
				h += abs(x-i) + abs(y-j);
				break;
			}
		}
	}
	return h;	
}


//ham danh gia theo chim bay
int h3(State nextState) {
	int h;
	int x,y; //toa do se duoc gan cho o trong goal state
	FOR(i, 0, size - 1) {
		FOR(j, 0, size - 1) {
			if(nextState.board[i][j] != 0) {
				findNumberInGoalState(nextState.board[i][j], x, y);
				h += sqrt(pow((x-i),2)+pow((y-i),2));
				break;
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

void solve() {
	
}

int main() {
	freopen("nPuzzle.inp", "r", stdin);
  	freopen("nPuzzle.out", "w", stdout);
  	input();
  	output();
  
	return 0;
}
	
