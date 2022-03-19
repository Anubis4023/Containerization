#ifndef LOADING_CODE_H
#define LOADING_CODE_H
#include "container.h"

//#include "node.h"
//#include "balance.h"
using namespace std;

extern int ROW;

//bool offloading_goal (Node&, vector<Container>&);
int Manhattan_loading (Node&);

bool offloading_goal (Node& grid, vector<Container>& offload) { //or keep track of which containers have been offloaded
// and then just check if the list of offloaded matches with what we wanted offloaded
    for (int i = 0; i < ROW+2; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            for (int h = 0; h < offload.size(); ++h) {
                if (grid.state[i][j].weight == offload.at(h).weight && grid.state[i][j].name == offload.at(h).name) {
                    return false;
                }
            }
        }
    }

    return true;
}

int Remove (Node&, vector<Container>& );

bool pinkEmpty (Node& node);
int emptyPinkHeur(Node& node);

#endif // LOADING_CODE_H
