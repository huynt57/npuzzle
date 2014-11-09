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

struct State {
	int g; //so buoc tu diem bat dau den trang trai
	int h; // ham danh gia
	int board[maxn][maxn]; //gia tri cua bang tai mot state
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
			}
		}
	}
	return h;	
}

int h3(State nextState) {
}

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
	
