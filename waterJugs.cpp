/*
 * Name: Joe Francesconi
 * Date Submitted: 4/25/2022
 * Lab Section: 005
 * Assignment Name: Using Breadth-First Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
  //Implement this function
  state current = make_pair(0, 0);
  const int A = 3;
  const int B = 4;

  state end = make_pair(A, B);

  while (current != end)
  {
    state next;
  
    //Fill Jug A
    next = make_pair(A, current.second);
    if (next != current)
    {
      pair<state, state> edge = make_pair(current, next);
      nbrs[current].push_back(next);
      edge_label[edge] = actions[0];
    }

    //Fill Jug B
    next = make_pair(current.first, B);
    if (next != current)
    {
      pair<state, state> edge = make_pair(current, next);
      nbrs[current].push_back(next);
      edge_label[edge] = actions[1];
    }

    //Empty Jug A
    next = make_pair(0, current.second);
    if (next != current)
    {
      pair<state, state> edge = make_pair(current, next);
      nbrs[current].push_back(next);
      edge_label[edge] = actions[2];
    }

    //Empty Jug B
    next = make_pair(current.first, 0);
    if (next != current)
    {
      pair<state, state> edge = make_pair(current, next);
      nbrs[current].push_back(next);
      edge_label[edge] = actions[3];
    }

    //Pour Jug A into Jug B
    int nA = current.first;
    int nB = current.second;
    if (current.second < B)
    {
      while (nA > 0 && nB < B)
      {
        nB++;
        nA--;
      }
      next = make_pair(nA, nB);
      if (next != current)
      {
        pair<state, state> edge = make_pair(current, next);
        nbrs[current].push_back(next);
        edge_label[edge] = actions[4];
      }
    }

    //Pour Jug B into Jug A
    nA = current.first;
    nB = current.second;
    if (current.first < A)
    {
      while (nA < A && nB > 0)
      {
        nA++;
        nB--;
      }
      next = make_pair(nA, nB);
      if (next != current)
      {
        pair<state, state> edge = make_pair(current, next);
        nbrs[current].push_back(next);
        edge_label[edge] = actions[5];
      }
    }
    if (current.second == B)
      current = make_pair(current.first + 1, 0);
    else
      current = make_pair(current.first, current.second + 1);
  }
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
