#include <bits/stdc++.h>
using namespace std;

struct node {
	pair<int, int> *state;
	node* parent;
};

map<pair<int, int>, bool> visited;

bool notPresent(int a, int b)
{
	if (visited.find({a, b}) == visited.end()) {
		visited[{a, b}] = false;
		return true;
	}
	return false;
}

#define INIT(a, b) temp = new pair<int, int>;\
        	       *temp = {a, b};\
                   curr_node = new node; \
			       curr_node->state = temp;\
			       curr_node->parent = upper;\
			       q.push(curr_node);

node* WaterJug(int Jug1, int Jug2, int target)
{
	queue<node*> q;
    node *upper = 0;
    node *curr_node;
	pair<int, int> *temp;
	bool solvable = false;
	
	INIT(0, 0)
	while(!q.empty()) {
		upper = q.front();
		q.pop();
		pair<int, int> curr = *(upper->state);
//		cout << curr.first << " " << curr.second << endl;
		visited[curr] = true;
		
		/* Target volume found in Jug */
		if (curr.first == target || curr.second == target) {
			solvable = true;
			if (curr.first == target && curr.second != 0)
			    { INIT(curr.first, 0) }
			else if (curr.second == target && curr.first != 0) 
			    { INIT(0, curr.second) }
			upper = curr_node;
			break;
		}
		
		/* Cases where jugs are filled */
		if (notPresent(Jug1, curr.second) && curr.first == 0)
			{ INIT(Jug1, curr.second) }
		if (notPresent(curr.first, Jug2) && curr.second == 0)
		    { INIT(curr.first, Jug2) }

        /* Cases where jugs are emptied */
		if (notPresent(0, curr.second) && curr.first != 0)
		    { INIT(0, curr.second) }
		if (notPresent(curr.first, 0) && curr.second != 0)
		    { INIT(curr.first, 0) }
		    
		/* Cases where liquid is poured from one jug to another */
		if (curr.first > 0 && (Jug2 - curr.second) <= curr.first && notPresent(curr.first - (Jug2 - curr.second), Jug2))
		    { INIT(curr.first - (Jug2 - curr.second), Jug2) }
		if (curr.second > 0 && (Jug1 - curr.first) <= curr.second && notPresent(Jug1, curr.second - (Jug1 - curr.first)))
			{ INIT(Jug1, curr.second - (Jug1 - curr.first)) }
        if (curr.first + curr.second <= Jug1 && notPresent(curr.first + curr.second, 0))
        	{ INIT(curr.first + curr.second, 0) }
		if (curr.first + curr.second <= Jug2 && notPresent(0, curr.first + curr.second))
			{ INIT(0, curr.first + curr.second) }
	}
	
	if (!solvable)
	    return NULL;
	else return upper;
}

void printSeq(node *result) {
	if (!result)
	    return;
	printSeq(result->parent);    
	cout << "(" << result->state->first << ", " << result->state->second << ")" << endl;
}

int main() {
	int Jug1, Jug2, target;
	cout << "Jug 1 Capacity (in L) : ";
	cin >> Jug1;
	cout << "Jug 2 Capacity (in L) : ";
	cin >> Jug2;
	cout << "Target (in L) : ";
	cin >> target;
	node *result = 0;
	if (target <= max(Jug1, Jug2))
	    result = WaterJug(Jug1, Jug2, target);
	if (result) {
	    cout << "Steps for measuring " << target << "L are -->\n";
		printSeq(result);
	}
	else cout << "NO SOLUTION !";
	return 0;
}
