/* 
 *   University of Engineering and Technology
 *	
 *	 AI Assignment 
 *   Student: Nguyen Duy Kien
 *   Class: K57CA
 *   
 *   Program: nPuzzle
 *   Desciption: This program uses A* algorithm to solve nPuzlle problems
 *   with 3 heuristic functions (see below for more details)      
 */

#include <iostream>
#include <set>
#include <fstream>
#include <math.h>
#include <queue>
#include <vector>
using namespace std;

/*
 * Struct: State is data structure which stores properties of state
 * along with function of state
 */
struct State{
	int depth;// depth of current state from initial state
	int f_function;// computes f - path cost of A* algorithm
	int state[5][5];// store current state
	int nPuzzle;// store size of state array
	
/* 
 *  Function:  Constructor
 *  Description: to set depth and f function of new states to 0
 */
	State(){
		depth = 0;
		f_function = 0;
	}
/* 
 *  End of function:  Constructor
 */
 
/* 
 *  Function: checkMove
 *  Description: to check whether the blank space in a state can move left(1), right(0), down(3) or up(4)
 */	
	bool checkMove(int type){
		for(int i=0; i<nPuzzle; i++)
			for(int j=0; j<nPuzzle; j++){
				if(type == 0){
					if(state[i][j]==0 && i<nPuzzle-1) return true;
					else if(state[i][j]==0 && i==nPuzzle-1) return false;
				} else if(type == 1){
					if(state[i][j]==0 && i>0) return true;
					else if(state[i][j]==0 && i==0) return false;
				} else if(type == 2){
					if(state[i][j]==0 && j>0) return true;
					else if(state[i][j]==0 && j==0) return false;
				} else if(type == 3){
					if(state[i][j]==0 && j<nPuzzle-1) return true;
					else if(state[i][j]==0 && j==nPuzzle-1) return false;
				}
			}
	}
/* 
 *  End of function: checkMove
 */
 
/* 
 *  Function: copyState
 *  Description: to copy state array in a given instance of State Struct to a given array
 */	
	void copyState(int state1[][5]){
		for(int i=0; i<nPuzzle; i++)
			for(int j=0; j<nPuzzle; j++){
				this->state[i][j]=state1[i][j];
			}
	}
/* 
 *  End of function: copyState
 */
};

/* 
 *  Function: move
 *  Description: to operate function to move the blank space to left, right, down or up if check return true
 */	
void move(State &state1,int type){
	state1.depth++;
	
	for(int i=0; i<state1.nPuzzle; i++)
		for(int j=0; j<state1.nPuzzle; j++){
			if(type == 0){
				if(!state1.checkMove(0)) return;
				if(state1.state[i][j]==0 && i<state1.nPuzzle-1){
					swap(state1.state[i][j], state1.state[i+1][j]);
					return;
				}
			} else if(type == 1){
				if(!state1.checkMove(1)) return;
				if(state1.state[i][j]==0 && i>0){
					swap(state1.state[i][j], state1.state[i-1][j]);
					return;
				}
			} else if(type == 2){
				if(!state1.checkMove(2)) return;
				if(state1.state[i][j]==0 && j>0){
					swap(state1.state[i][j], state1.state[i][j-1]);
					return;
				}
			} else if(type == 3){
				if(!state1.checkMove(3)) return;
				if(state1.state[i][j]==0 && j<state1.nPuzzle-1){
					swap(state1.state[i][j], state1.state[i][j+1]);
					return;
				}
			}
		}
}
/* 
 *  End of function: move
 */
 
/* 
 *  Function: checkState
 *  Description: to check whether two given instances of State Struct contain the same state array
 */	
bool checkState(const State &state1, const State &state2){
	for(int i=0; i<state1.nPuzzle; i++)
		for(int j=0; j<state1.nPuzzle; j++){
			if(state1.state[i][j]!=state2.state[i][j]) return false;
		}
	
	return true;
}
/* 
 *  End of function: checkState
 */
 
/* 
 *  Function: copy
 *  Description: to copy properties of an instance of State Struct to another one
 */	
void copy(State &state1,const State &state2){
	for(int i=0; i<state2.nPuzzle; i++)
		for(int j=0; j<state2.nPuzzle; j++){
			state1.state[i][j]=state2.state[i][j];
		}
		
	state1.depth = state2.depth;
	state1.nPuzzle = state2.nPuzzle;
	state1.f_function = state2.f_function;
}
/* 
 *  End of function: copy
 */
 
/* 
 *  Function: read_file
 *  Description: to read input from file
 */	
void read_file(int input[][5], int output[][5], int &heu_type, int &nPuzzle){
	int n, m;
	ifstream f_in("nPuzzle.inp");
	
	if(f_in){
		f_in >> n;f_in >> m;
		heu_type = m; nPuzzle = n;
		
		for(int i=0; i<nPuzzle; i++)
			for(int j=0; j<nPuzzle; j++)
				f_in >> input[i][j];
			
		
				
		for(int i=0; i<nPuzzle; i++)
			for(int j=0; j<nPuzzle; j++)
				f_in >> output[i][j];
		
		f_in.close();
	}else{
		cout<< "File's not found!\n";
	}
}
/* 
 *  End of function: read_file
 */
 
/* 
 *  Struct:  compState
 *  Description: to compare states to store it in binary search tree
 */
struct compState{
	bool operator()(const State &state1, const State &state2) const{
		for(int i=0; i<state1.nPuzzle;i++)
			for(int j=0;j<state1.nPuzzle;j++){
				if(state1.state[i][j] > state2.state[i][j]) return true;
				else if(state1.state[i][j] < state2.state[i][j]) return false;
			}
		
		return false;
	}
};
/* 
 *  End of struct: compState
 */

/* 
 *  Struct:  compPathCost
 *  Description: to compare f - path cost of states to decide which state is expanded first
 */
struct compPathCost{
	bool operator()(const State &state1, const State &state2) const{
		if(state1.f_function > state2.f_function) return true;
		else if(state1.f_function == state2.f_function){
			return(state1.depth < state2.depth);
		} else return false;
	}
};
/* 
 *  End of struct: compPathCost
 */

/* 
 *  Function: print_file
 *  Description: to print outputs
 */	
void print_file(int optimalMoves, int generatedStates){
	ofstream f_out("nPuzzle.out");
	
	f_out<<optimalMoves<<" "<<generatedStates<<endl;
}

void print_file(){
	ofstream f_out("nPuzzle.out");
	
	f_out<<"-1"<<endl;
}
/* 
 *  End of function: print_file
 */

/* 
 *  Function: heuristic function - manhattan_distance
 *  Description: to compute manhattan_distance from a specific state to output
 */	
int manhattan_distance(int input[][5], int output[][5], int nPuzzle){
	int result = 0;
	int x_in, y_in, x_out, y_out;
	int in[nPuzzle*nPuzzle], out[nPuzzle*nPuzzle];
	
	for(int i=0; i<nPuzzle; i++)
		for(int j=0; j<nPuzzle; j++){
			in[input[i][j]] = i*10 + j;
			out[output[i][j]] = i*10 + j;
		}
		
	for(int i=1; i<(nPuzzle*nPuzzle); i++){
		y_in = in[i]%10;
		x_in = (in[i]-y_in)/10;
		y_out = out[i]%10;
		x_out = (out[i]-y_out)/10;
		result = result + abs(x_out-x_in)+ abs(y_out-y_in);
	}
	
	return result;
}
/* 
 *  End of function: manhattan_distance
 */

/* 
 *  Function: heuristic function - number_misplace
 *  Description: to compute the number of misplace titles between a specific state and output
 */	
int number_misplace(int input[][5], int output[][5], int nPuzzle){
	int result = 0;
	
	for(int i=0; i<nPuzzle; i++)
		for(int j=0; j<nPuzzle; j++)
			if(input[i][j]!=output[i][j]&&input[i][j]!=0) result++;
			
	return result;
}
/* 
 *  End of function: number_misplace
 */

/* 
 *  Function: heuristic function - mis_column_row
 *  Description: to compute the number of miss column and row of titles between a specific state and output
 */	
int mis_column_row(int input[][5], int output[][5], int nPuzzle){
	int result = 0;	
	int x_in, y_in, x_out, y_out;
	int in[nPuzzle*nPuzzle], out[nPuzzle*nPuzzle];
	
	for(int i=0; i<nPuzzle; i++)
		for(int j=0; j<nPuzzle; j++){
			in[input[i][j]] = i*10 + j;
			out[output[i][j]] = i*10 + j;
		}
		
	for(int i=1; i<(nPuzzle*nPuzzle); i++){
		y_in = in[i]%10;
		x_in = (in[i]-y_in)/10;
		y_out = out[i]%10;
		x_out = (out[i]-y_out)/10;
		if(y_in==y_out&&x_in!=x_out) result = result + 1;
		else if(y_in!=y_out&&x_in==x_out) result = result + 1;
		else if(y_in!=y_out&&x_in!=x_out) result = result + 2;
	}
	
	return result;
}
/* 
 *  End of function: mis_column_row
 */

priority_queue<State, vector<State>, compPathCost> L; // a heap to store generated states to decide which state should be expanded next
set<State, compState> S; // a binary search tree to store generated states to check and avoid repeated states

/* 
 *  Function: generatedMoves
 *  Description: to generate a given state depended on move_type (left, right, up or down), check repeated state and store a generated state to L and S
 */	
void generatedMoves(State &choice, int input[][5], int output[][5], int nPuzzle, int move_type, int heu_type, int &count){
	State expand;											 			     
	copy(expand, choice);
	
	if(choice.checkMove(move_type)){
		move(expand, move_type);
		if(S.find(expand)!=S.end()&&S.find(expand)->depth<=expand.depth) return;
		else if(S.find(expand)!=S.end()&&S.find(expand)->depth>expand.depth){
			S.erase(S.find(expand));
			switch(heu_type){
				case 2 : expand.f_function = expand.depth + manhattan_distance(expand.state, output, nPuzzle); break;
				case 1 : expand.f_function = expand.depth + number_misplace(expand.state, output, nPuzzle); break;
				case 3 : expand.f_function = expand.depth + mis_column_row(expand.state, output, nPuzzle); break;
			}
			S.insert(expand);
			L.push(expand);
			count++;
		} else{
			switch(heu_type){
				case 2 : expand.f_function = expand.depth + manhattan_distance(expand.state, output, nPuzzle); break;
				case 1 : expand.f_function = expand.depth + number_misplace(expand.state, output, nPuzzle); break;
				case 3 : expand.f_function = expand.depth + mis_column_row(expand.state, output, nPuzzle); break;
			}
			S.insert(expand);
			L.push(expand);
			count++;
		}
	}
}
/* 
 *  End of function: generatedMoves
 */

/* 
 *  Function: generator
 *  Description: to generate a given state and store all of generated states of that state to L, S ,count the number of generated states and save to count variable
 */	
int generator(State &choice, int heu_type, int input[][5], int output[][5], int nPuzzle){
	int count = 0;														 				 
	
	for(int i=0;i<4;i++)
		generatedMoves(choice, input, output, nPuzzle, i, heu_type, count);
	
	return count;
}
/* 
 *  End of function: generator
 */
 
/* 
 *  Function: A_star
 *  Description: to implement A* algorithm which use input, output and type of heuristic function to compute all of generated states and optimal path cost
 */	
void A_star(int input[][5], int output[][5], int &optimalMoves, int &generatedStates, int heu_type, int nPuzzle){
	State in;in.nPuzzle=nPuzzle;in.copyState(input); 															 
	State out;out.nPuzzle=nPuzzle;out.copyState(output);
	
	generator(in, heu_type,input, output, nPuzzle);
	S.insert(in);
	
	do{
		State expand; copy(expand,L.top());
		L.pop();
		if(checkState(expand, out)){
			optimalMoves = expand.depth;
			return;
		}
		generatedStates += generator(expand, heu_type, input, output, nPuzzle);
	}while(!L.empty());
}
/* 
 *  End of function: A_star
 */

/* 
 *  Function: countPermutation
 *  Description: to count the number of swap of input to be output
 */	
void countPermutation(int nPuzzle, int input[], int output[], bool check[], int position, int store, int &count){	
	for(int i=0; i<nPuzzle*nPuzzle; i++){
		if(output[i] == input[position]){
			count++;
			check[i] = true;
			if(i!=store)
				countPermutation(nPuzzle, input, output, check, i, store, count);
			else{
				count--;
				return;
			}
		}
	}
}
/* 
 *  End of function: countPermutation
 */

/* 
 *  Function: ableToSolve
 *  Description: to check whether input puzzle can be solve or not
 */	
bool ableToSovle(int nPuzzle, int input[][5], int output[][5]){
	int countP = 0, distance, m;
	int a[nPuzzle*nPuzzle], b[nPuzzle*nPuzzle];
	bool c[nPuzzle*nPuzzle];
	int y_in, x_in, y_out, x_out;
	
	for(int i=0; i<nPuzzle; i++)
		for(int j=0;j<nPuzzle;j++){
			a[i*nPuzzle+j] = input[i][j];
			b[i*nPuzzle+j] = output[i][j];
			c[i*nPuzzle+j] = false;
		}
	
	for(int i=0; i<nPuzzle*nPuzzle; i++){
		if(!c[i]) countPermutation(nPuzzle, a, b, c, i, i, countP);
	}
	
	for(int i=0; i<nPuzzle; i++)
		for(int j=0; j<nPuzzle; j++)
			if(output[i][j]==0){
				for(int h=0; h<nPuzzle; h++)
					for(int k=0; k<nPuzzle; k++)
						if(input[h][k]==0){
							distance = abs(h-i)+abs(k-j);
							break;
						}
			}
			
	m = distance + countP;
	
	return (m%2==0);
}
/* 
 *  End of function: ableToSovle
 */

/* 
 *  Function: main
 */	
int main(void){
	int input[5][5], output[5][5];
	int heu_type, nPuzzle, optimalMoves = 0,generatedStates = 0;
	
	read_file(input, output, heu_type, nPuzzle);
	
	if(ableToSovle(nPuzzle, input, output)){
		A_star(input, output, optimalMoves, generatedStates, heu_type, nPuzzle);
		
		print_file(optimalMoves, generatedStates);
	} else print_file();
	
	return 0;
}
/* 
 *  End of function: main
 */
