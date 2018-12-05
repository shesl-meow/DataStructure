#include <iostream>
using namespace std;
struct block {
  bool IsMetal;
  bool IsWater;
};
void setWater(block **graph, int i, int j, int n, bool **IsVisited) {
  graph[i][j].IsWater = true;
  IsVisited[i][j] = true;
  if (i > 0) {
    if (!graph[i - 1][j].IsMetal && !IsVisited[i - 1][j]) {
      setWater(graph, i - 1, j, n, IsVisited);
    }
  }
  if (i < n + 1) {
    if (!graph[i + 1][j].IsMetal && !IsVisited[i + 1][j]) {
      setWater(graph, i + 1, j, n, IsVisited);
    }
  }
  if (j > 0) {
    if (!graph[i][j - 1].IsMetal && !IsVisited[i][j - 1]) {
      setWater(graph, i, j - 1, n, IsVisited);
    }
  }
  if (j < n + 1) {
    if (!graph[i][j + 1].IsMetal && !IsVisited[i][j + 1]) {
      setWater(graph, i, j + 1, n, IsVisited);
    }
  }
}

void SetW(block **graph, int i, int j, int n) {
  bool **IsVisited;
  IsVisited = new bool *[n + 2];
  for (int i = 0; i < n + 2; i++) {
    IsVisited[i] = new bool[n + 2];
    for (int j = 0; j < n + 2; j++) {
      IsVisited[i][j] = false;
    }
  }
  setWater(graph, i, j, n, IsVisited);
  delete IsVisited;
}

bool traverse(block **graph, int n) {
  bool done = true;
  int up, down, left, right;
  up = down = left = right = 0;
  // judge & melt.
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      if (graph[i][j].IsMetal) {
        done = false;
        int count = 0;
        count = (graph[i - 1][j].IsWater ? 1 : 0) +
                (graph[i + 1][j].IsWater ? 1 : 0) +
                (graph[i][j - 1].IsWater ? 1 : 0) +
                (graph[i][j + 1].IsWater ? 1 : 0);

        if (count >= 2) {
          graph[i][j].IsMetal = false;
          // graph[i][j].IsWater = true;
        }
      }
    }
  }
  if (done) return true;
  SetW(graph, 0, 0, n);
  return false;
}

int main() {
  int n;
  cin >> n;
  // initialize
  block **graph;
  graph = new block *[n + 2];
  for (int i = 0; i < n + 2; i++) {
    graph[i] = new block[n + 2];
  }
  char input;
  for (int i = 0; i < n + 2; i++) {
    for (int j = 0; j < n + 2; j++) {
      graph[i][j].IsMetal = graph[i][j].IsWater = false;
    }
  }
  // load data
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      cin >> input;
      if (input == '#') {
        graph[i][j].IsMetal = true;
        graph[i][j].IsWater = false;
      }
    }
  }
  SetW(graph, 0, 0, n);
  int time = 0;
  do {
    time++;
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    for (int i = 1; i < n + 1; i++) {
      for (int j = 1; j < n + 1; j++) {
        if (graph[i][j].IsMetal) {
          cout << "#";
        } else {
          cout << "_";
        }
      }
      cout << endl;
    }
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
  } while (!traverse(graph, n));
  cout << time - 1;
  return 0;
}
