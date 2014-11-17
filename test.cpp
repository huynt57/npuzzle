
#include <iostream>
#include <string.h>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <queue>
#include <vector>
using namespace std;


class State{
	public:
		int depth, f_function, **state, **parent_state, nPuzzle;
		string key;
		State();
		State(int **s, int &n);
		State move_left();
		State move_right();
		State move_down();
		State move_up();
		friend bool operator==(const State &state1, const State &state2);
		friend bool operator<(const State &state1, const State &state2);
		~State();
};

State::State(){
	state = NULL;
	depth = 0;
	parent_state = NULL;
	nPuzzle = 0;
	f_function = 0;
	key = "";
}

State::State(int **s, int &n){
	state = new int*[n];
			
	for(int i=0; i<n; i++){
		state[i] = new int[n];
		
		for(int j=0; j<n; j++){
			state[i][j]=s[i][j];
		}
	}
			
	depth = 0;
	parent_state = NULL;
	nPuzzle = n;
	f_function = 0;
}

State State::move_down(){
	State a(state, nPuzzle);
	
	a.depth++;
	a.parent_state = new int*[nPuzzle];
			
	for(int i=0; i<nPuzzle; i++){
		a.parent_state[i] = new int[nPuzzle];
		
		for(int j=0; j<nPuzzle; j++){
			a.parent_state[i][j]=a.state[i][j];
		}
	}
	
	for(int i=0; i<a.nPuzzle; i++)
		for(int j=0; j<a.nPuzzle; j++)
			if(a.state[i][j]==0 && i<a.nPuzzle-1){
				swap(a.state[i][j], a.state[i+1][j]);
				return a;
			}
			
	return a;
}

State State::move_up(){
	State a(state, nPuzzle);
	
	a.depth++;
	a.parent_state = new int*[nPuzzle];
			
	for(int i=0; i<nPuzzle; i++){
		a.parent_state[i] = new int[nPuzzle];
		
		for(int j=0; j<nPuzzle; j++){
			a.parent_state[i][j]=a.state[i][j];
		}
	}
	
	for(int i=0; i<a.nPuzzle; i++)
		for(int j=0; j<a.nPuzzle; j++)
			if(a.state[i][j]==0 && i>0){
				swap(a.state[i][j], a.state[i-1][j]);
				return a;
			}
			
	return a;
}

State State::move_left(){
	State a(state, nPuzzle);
	
	a.depth++;
	a.parent_state = new int*[nPuzzle];
			
	for(int i=0; i<nPuzzle; i++){
		a.parent_state[i] = new int[nPuzzle];
		
		for(int j=0; j<nPuzzle; j++){
			a.parent_state[i][j]=a.state[i][j];
		}
	}
	
	for(int i=0; i<a.nPuzzle; i++)
		for(int j=0; j<a.nPuzzle; j++)
			if(a.state[i][j]==0 && j>0){
				swap(a.state[i][j], a.state[i][j-1]);
				return a;
			}
			
	return a;
}

State State::move_right(){
	State a(state, nPuzzle);
	
	a.depth++;
	a.parent_state = new int*[nPuzzle];
			
	for(int i=0; i<nPuzzle; i++){
		a.parent_state[i] = new int[nPuzzle];
		
		for(int j=0; j<nPuzzle; j++){
			a.parent_state[i][j]=a.state[i][j];
		}
	}
	
	for(int i=0; i<a.nPuzzle; i++)
		for(int j=0; j<a.nPuzzle; j++)
			if(a.state[i][j]==0 && j<a.nPuzzle-1){
				swap(a.state[i][j], a.state[i][j+1]);
				return a;
			}
			
	return a;
}

bool operator==(const State &state1, const State &state2){
	for(int i=0; i<state1.nPuzzle; i++)
		for(int j=0; j<state1.nPuzzle; j++){
			if(state1.state[i][j]!=state2.state[i][j]) return false;
		}
		
	return true;
}

bool operator<(const State &state1, const State &state2){
	return(state1.f_function < state2.f_function);
}

State::~State(){
	delete state, parent_state;
}

void read_file(int **&input, int **&output, int &heu_type, int &nPuzzle){
	int n, m;
	ifstream f_in("nPuzzle.inp");
	
	if(f_in){
		f_in >> n;f_in >> m;
		heu_type = m; nPuzzle = n;
		input = new int*[nPuzzle];
		output = new int*[nPuzzle];
		
		for(int i=0; i<nPuzzle; i++){
			input[i] = new int[nPuzzle];
			
			for(int j=0; j<nPuzzle; j++){
				f_in >> input[i][j];
			}
		}
				
		for(int i=0; i<nPuzzle; i++){
			output[i] = new int[nPuzzle];
			
			for(int j=0; j<nPuzzle; j++){
				f_in >> output[i][j];
			}
		}
		
		f_in.close();
	}else{
		cout<< "File's not found!\n";
	}
}

struct compState{
	bool operator()(const State *state1, const State *state2) const{
		for(int i=0; i<state1->nPuzzle;i++)
			for(int j=0;j<state1->nPuzzle;j++){
				if(state1->state[i][j] < state2->state[i][j]) return true;
				else if(state1->state[i][j] > state2->state[i][j]) return false;
			}
		
		return false;
	}
};

struct compPathCost{
	bool operator()(const State &state1, const State &state2) const{
		return(state1.f_function > state2.f_function);
	}
};

int manhattan_distance(int **input, int **output, int nPuzzle){
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

int number_misplace(int **input, int **output, int nPuzzle){
	int result = 0;
	
	for(int i=0; i<nPuzzle; i++)
		for(int j=0; j<nPuzzle; j++)
			if(input[i][j]!=output[i][j]&&input[i][j]!=0) result = result + 1;
			
	return result;
}

int mis_column_row(int **input, int **output, int nPuzzle){
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

/*int generator(State &choice, priority_queue<State*, vector<State*>, compPathCost> &L, int heu_type, int **output, int nPuzzle){
	int count = 0;
	
	if(!(choice == choice.move_down())){
		State expand1 = choice.move_down();
		
		switch(heu_type){
			case 0 : expand1.f_function = expand1.depth + manhattan_distance(expand1.state, output, nPuzzle);
			case 1 : expand1.f_function = expand1.depth + number_misplace(expand1.state, output, nPuzzle);
			case 2 : expand1.f_function = expand1.depth + mis_column_row(expand1.state, output, nPuzzle);
		}
		
		L.push(&expand1);
		count++;
	}
	
	if(!(choice == choice.move_down())){
		State expand2 = choice.move_up();
		
		switch(heu_type){
			case 0 : expand2.f_function = expand2.depth + manhattan_distance(expand2.state, output, nPuzzle);
			case 1 : expand2.f_function = expand2.depth + number_misplace(expand2.state, output, nPuzzle);
			case 2 : expand2.f_function = expand2.depth + mis_column_row(expand2.state, output, nPuzzle);
		}
		
		L.push(&expand2);
		count++;
	}
	
	if(!(choice == choice.move_down())){
		State expand3 = choice.move_left();
		
		switch(heu_type){
			case 0 : expand3.f_function = expand3.depth + manhattan_distance(expand3.state, output, nPuzzle);
			case 1 : expand3.f_function = expand3.depth + number_misplace(expand3.state, output, nPuzzle);
			case 2 : expand3.f_function = expand3.depth + mis_column_row(expand3.state, output, nPuzzle);
		}
		
		L.push(&expand3);
		count++;
	}
	
	if(!(choice == choice.move_down())){
		State expand4 = choice.move_right();
	
		switch(heu_type){
			case 0 : expand4.f_function = expand4.depth + manhattan_distance(expand4.state, output, nPuzzle);
			case 1 : expand4.f_function = expand4.depth + number_misplace(expand4.state, output, nPuzzle);
			case 2 : expand4.f_function = expand4.depth + mis_column_row(expand4.state, output, nPuzzle);
		}
		
		L.push(&expand4);
		count++;
	}

	return count;
}

void A_star(priority_queue<State*, vector<State*>, compPathCost> L, set<State*, compState> S, int **input, int **output, int &optimalMoves, int &generatedStates, int heu_type, int nPuzzle){
	State in(input, nPuzzle);
	State out(output, nPuzzle);
	
	generator(in, L, heu_type, output, nPuzzle);
	S.insert(&in);
	
	L.top();
	
	//do{
		//if(S.find(L.top())==S.end()){
		//	State *expand = L.top();
		//	if(*expand == out){
		//		optimalMoves = expand->depth;
		//		return;
		//	}
		//	L.pop();
		//	generatedStates += generator(*expand, L, heu_type, output, nPuzzle);
		//	cout<<"1"<<endl;
		//}else L.pop();
	//}while(!L.empty());
}*/

int main(void){
	int **input, **output;
	int heu_type, nPuzzle, optimalMoves,generatedStates;
	
	read_file(input, output, heu_type, nPuzzle);
			
	priority_queue<State, vector<State>, compPathCost> L;
	set<State, compState> S;
	
	State a(input,nPuzzle);
	State b(output,nPuzzle);
	
	L.push(a);
	
	
		
	//State a(input,nPuzzle);
	/*State c(input,nPuzzle);
	State b(output,nPuzzle);
	
	a.f_function = 2;
	b.f_function = 3;
	
	L.push(&a);
	L.push(&b);
	
	s.insert(&a);
	
	
	State *expand = L.top();
	
	//if(s.find(expand)==s.end()) cout<<"yes";
	//else cout<<"no";
	
	if(*expand == a) cout<<"yes";
	else cout<<"no";
	
	for(int i=0; i<nPuzzle; i++){
		cout<<endl;
		for(int j=0; j<nPuzzle; j++)
			cout<<L.top()->state[i][j]<<" ";
		}*/
		
		//A_star(L,S,input,output,optimalMoves,generatedStates, heu_type, nPuzzle);
	
	
	//cout<< optimalMoves;
	
	
	return 0;
}

