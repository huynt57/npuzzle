#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <set>

#define for(i, a, b) for(int i=a; i<=b; i++)

typedef unsigned long long ll;
using namespace std;

struct state{
    int board[5][5], column, row, g, h, f, direction;
};

struct position{
    int column, row;
};

struct comparator{
    bool operator()(const state state1, const state state2){
        return !((state1.f < state2.f) or ((state1.f == state2.f) and (state1.h < state2.h)));
    }
};

int n, k, goal_board[5][5], init_board[5][5], count_state;
position ps[16];
priority_queue<state, vector<state>, comparator> state_queue;
set <ll> list_state;
ll final_state;
ifstream file_input("nPuzzle.inp.08");
ofstream file_output("out.txt");

void readfile();
ll convert_array_number(int a[5][5]);
void init();
void Astar();
void convert_array_state(int a[5][5], state *b, int c, int r, int g, int d);
bool check_position(int a, int b);
bool check_state(ll a);
bool is_final_state(ll a);
int heuristic(int a[5][5]);

int main(){
    readfile();
    init();
    Astar();
    file_output.close();
}

void readfile(){
    file_input >> n >> k;
    for(i, 1, n)
        for(j, 1, n)
            file_input >> init_board[i][j];
    for(i, 1, n)
        for(j, 1, n)
            file_input >> goal_board[i][j];
}

ll convert_array_number(int a[5][5]){
    ll result = 0, s1, s2 = 1;
    for(i, 1, n)
        for(j, 1, n){
            s1 = a[i][j];
            s1 = s1 * s2;
            result = result + s1;
            s2 = s2*n*n;
        }
    return result;
}

void init(){
    int c, r;
    state st;
    ll ss;
    for(i, 1, n)
        for(j, 1, n)
            if (init_board[i][j] == 0){
                r = i;
                c = j;
            }
    convert_array_state(init_board, &st, c, r, 0, -10);
    state_queue.push(st);
    count_state = 0;
    final_state = convert_array_number(goal_board);
    for(i, 1, n)
        for(j, 1, n){
            ps[goal_board[i][j]].row = i;
            ps[goal_board[i][j]].column = j;
        }
}

void Astar(){
    int i0[4] = {-1, 0, 1, 0};
    int j0[4] = {0, 1, 0, -1};
    int r, c, g, d;
    int current_board[5][5], b[5][5];
    while (!state_queue.empty()){
        state current_state = state_queue.top();
        state_queue.pop();
        for(i, 1, n)
            for(j, 1, n)
                current_board[i][j] = current_state.board[i][j];
        ll sstate = convert_array_number(current_board);
        if(!check_state(sstate))
            continue;
        list_state.insert(sstate);
        if(is_final_state(sstate)){
            file_output << current_state.g << " " << count_state << '\n';
            return;
        }
        r = current_state.row;
        c = current_state.column;
        g = current_state.g;
        d = current_state.direction;
        for(i, 0, 3)
            if ((abs(i-d) != 2) and (check_position(r+i0[i], c+j0[i]))){
                current_board[r][c] = current_board[r+i0[i]][c+j0[i]];
                current_board[r+i0[i]][c+j0[i]] = 0;
                state new_state;
                convert_array_state(current_board, &new_state, c+j0[i], r+i0[i], g+1, i);
                state_queue.push(new_state);
                count_state++;
                current_board[r+i0[i]][c+j0[i]] = current_board[r][c];
                current_board[r][c] = 0;
            }
    }
    file_output << -1;
}

void convert_array_state(int a[5][5], state *b, int c, int r, int g, int d){
    for(i, 1, n)
        for(j, 1, n)
            (*b).board[i][j] = a[i][j];
    (*b).column = c;
    (*b).row = r;
    (*b).g = g;
    (*b).h = heuristic(a);
    (*b).f = (*b).g + (*b).h;
    (*b).direction = d;
}

bool check_position(int a, int b){
    return (a >= 1) && (a <= n) && (b >= 1) && (b <= n);
}

bool check_state(ll a){
    return list_state.find(a) == list_state.end();
}

bool is_final_state(ll a){
    return a == final_state;
}

int heuristic(int a[5][5]){
    int count = 0;
    if (k == 1){
        for(i, 1, n)
            for(j, 1, n)
                if((a[i][j] != goal_board[i][j]) and (a[i][j] != 0))
                    count++;
    }
    else if (k == 2){
        for(i, 1, n)
            for(j, 1, n)
                if(a[i][j] != 0)
                    count = count + abs(i-ps[a[i][j]].row) + abs(j-ps[a[i][j]].column);
//                    count = count + (i!=ps[a[i][j]].row)?1:0 + (j!=ps[a[i][j]].column)?1:0;
    }
    return count;
}
