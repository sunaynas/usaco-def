#include <bits/stdc++.h>

#include <iomanip>
#include <iostream>

using namespace std;

// finds an a iterator pointing to a to key and value in a multimap, given that
// key and value
template <class K, class V>
typename multimap<K, V>::const_iterator find_pair_in_multimap(
    const multimap<K, V>& map, const pair<K, V>& pair) {
  auto range = map.equal_range(pair.first);
  for (auto p = range.first; p != range.second; ++p)
    if (p->second == pair.second) return p;
  return map.end();
}

class NodePair {
 public:
  int v1;  // should be already family node
  int v2;  // should be external node
  // make sure que compare only checks external node for equality

  NodePair(int fam, int ex) {
    v1 = fam;
    v2 = ex;
  }
};

bool operator==(const NodePair& a, const NodePair& b) { return a.v2 == b.v2; }

// returns MIN COST and MAX COST of the MST- for the MST, what is the smallest
// edge, and what is the greatest edge? this function can be used without matrix

// bc ret has an initialized value, dont need to use it if you dont want matrix

// works best for dense graphs
// returns symmetric adjacency matrix (assumes undirected graph)

// improvements: bool directed, return as list bc MST is always sparse
pair<int, int> MSTmatrixCreator(vector<vector<int> >& adjmatrix,
                                vector<vector<int> >* retMSTmatrix = NULL) {
  int maxCost = -1;
  int minCost = INT_MAX;

  int n = adjmatrix.size();
  vector<int> neigh(n, 0);  // neighbors key = node id, value = weight
  set<int> remaining;
  // typedef pair<int, int> NodePair;

  multimap<int, NodePair> que;  // que key = weight value = node id //
                                // update value = pair of node id.
  if (retMSTmatrix) {
    retMSTmatrix->resize(n);
    (*retMSTmatrix)[0].resize(n);
    fill((*retMSTmatrix)[0].begin(), (*retMSTmatrix)[0].end(), -1);
  }
  for (int i = 1; i < n; i++) {
    if (retMSTmatrix) {
      (*retMSTmatrix)[i].resize(n);
      fill((*retMSTmatrix)[i].begin(), (*retMSTmatrix)[i].end(), -1);
    }
    remaining.insert(i);
    que.insert(pair<int, NodePair>(adjmatrix[0][i], NodePair(0, i)));
    neigh[i] = adjmatrix[0][i];
  }
  neigh[0] = -1;
  int lastAdded = 0;
  while (true) {
    if (remaining.size() == 0) return {minCost, maxCost};
    for (int itr : remaining) {
      if (adjmatrix[lastAdded][itr] < neigh[itr]) {
        // auto it = find_pair_in_multimap<int, int>(
        //     que, pair<int, int>(neigh[itr], itr));
        auto it = find_pair_in_multimap<int, NodePair>(
            que, pair<int, NodePair>(neigh[itr], NodePair(-1, itr)));
        que.erase(it);
        neigh[itr] = adjmatrix[lastAdded][itr];
        que.insert(pair<int, NodePair>(neigh[itr], NodePair(lastAdded, itr)));
      }
    }
    auto smallestEdge = que.begin();
    int smallestCost = smallestEdge->first;
    maxCost = max(maxCost, smallestCost);
    minCost = min(minCost, smallestCost);
    int smallestNeigh = smallestEdge->second.v2;
    // creates 1/2 filled matrix
    if (retMSTmatrix) {
      (*retMSTmatrix)[smallestEdge->second.v1][smallestEdge->second.v2] =
          smallestCost;
      (*retMSTmatrix)[smallestEdge->second.v2][smallestEdge->second.v1] =
          smallestCost;
    }
    remaining.erase(smallestNeigh);
    neigh[smallestNeigh] = -1;
    que.erase(que.begin());
    lastAdded = smallestNeigh;
  }
}

// create another function that works with sparce list

// dfs

// bfs