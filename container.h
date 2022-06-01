extern int COLUMN;
#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include <queue>
#include <string>

using namespace std;

class Container {
    public:
        string name;
        int weight = 0;
        int row = 0;
        int column = 0;

        int sRow = 0;
        int sColumn =0;

        Container() {name = " UNUSED";}
        Container(string Name, int Weight) {
            weight = Weight;
            name = Name;
        }

};

class Node {
  public:
      int fn = 0;
      int hn = 0;
      int gn = 0;
      bool picked = false;
      bool balanceable = true;

      vector<string> moveSet;
      vector<pair<int, int>> position;
      vector<pair<int, int>> cost;

      vector<vector<Container>> state;
      int rowPicked = -1; //Where is the container that is going to be picked up and expanded into more nodes
      int columnPicked = -1;

      int lastRow = -1;
      int lastColumn = 0;

      vector<Container> onload;
      vector<vector<Container>> bay;
      bool onlyPink = false;

      Node () {
          bay.push_back(vector<Container> (COLUMN, Container()));
          bay.push_back(vector<Container> (COLUMN, Container()));
      }
      Node(vector<vector<Container>> userState) {state = userState;}
      Node(int F) {fn = F;}
};

class QQList {
public:
    priority_queue<Node> queue;
};

#endif // node2_h
