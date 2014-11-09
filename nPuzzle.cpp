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

void output()
{
}

int h1() {
}

int h2() {
}

int h3() {
}

void solve() {
	
}

int main() {
	//freopen("nPuzzle.inp", "r", stdin);
  //freopen("nPuzzle.out", "w", stdout);
	return 0;
}
	
