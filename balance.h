#ifndef balance_h
#define balance_h
#include <iostream>
#include <fstream>

#include <cmath>
#include <algorithm>
#include "container.h"

//balancing service: functions and global variables
extern int ROW;
extern int COLUMN;
extern bool balanced;
extern Node answer;
extern vector<Container> weights;
//extern vector<vector<Container>> solution;

void read_manifest (vector<vector<Container>>& ship, vector<Container>& weights);
void OutputGrid (vector<vector<Container>>& ship, int option);
void OutputList (const vector<Container>& weights);

bool operator<(const Node& n1, const Node& n2);
bool compareContainer (Container i, Container j);

bool compareContainerLight (Container i, Container j);

void moveTo (QQList* open, vector<Node>& closed, Node& offload, int row, int column, int option);
bool equal (vector<vector<Container>> grid1, vector<vector<Container>> grid2);

bool goalCheck(Node&); //if it can be balanced
void expand (QQList*, vector<Node>&, vector<Container>&, Node, int); //Do the possible movements and expand the nodes
Node searchG(vector<vector<Container>>, int, vector<Container>&, vector<Container>&);

int firstInCol(const Node&, int); //Find the top container in the column
int findTop(const Node&, int); //Find where a container can be placed in the column

int Deficit (Node);
int Misplaced (Node&);
int weightR (Node);
int weightL (Node);
bool Balanceable(vector<vector<Container>>& ship);
void makeSolution(vector<vector<Container>>& ship);
bool goalCheck2(Node&); //if it cannot be balanced

void new_manifest();

#endif
