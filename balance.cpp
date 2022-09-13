
#include "balance.h"
#include "loading_code.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

using namespace std;

vector<vector<Container>> solution (ROW, vector<Container> (COLUMN, Container()));
bool balanced = true;


bool compareContainerLight (Container i, Container j) { //light to heaviest
    return (i.weight < j.weight);
}

void new_manifest () {
    QFile file ("C:/Users/pacow/OneDrive/Desktop/OUTBOUND.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    cout << weights.size() << endl;

    for (int i = 7; i >= 0; --i) {
        cout << "i is: " << i << endl;
        for (int j = 0; j < COLUMN; ++j) {
            cout << "j is: " << j << endl;
            out << "[0" << abs(i-8) << ",";
            cout << "here" << endl;
            if (j < 9) {
                out << "0" << j+1;
            } else {
                out << j+1;
            }
            out << "], {";
            if (answer.state[i][j].weight >= 10000) {
                out << answer.state[i][j].weight;
            } else if (answer.state[i][j].weight >= 1000) {
                out << "0" << answer.state[i][j].weight;
            } else if (answer.state[i][j].weight >= 100) {
                out << "00" << answer.state[i][j].weight;
            } else if (answer.state[i][j].weight >= 10) {
                out << "000" << answer.state[i][j].weight;
            } else if (answer.state[i][j].weight >= 1) {
                out << "0000" << answer.state[i][j].weight;
            } else {
                out << "00000";
            }
            out << "}," << QString::fromStdString(answer.state[i][j].name) << "\n";
        }
    }
    cout << "finished" << endl;
    weights.clear();
}

bool operator<(const Node& n1, const Node& n2) { //Overloads < operator in the priority queue
        return n1.fn >= n2.fn;
}
bool compareContainer (Container i, Container j) { //heavy to lightest
    return (i.weight > j.weight);
}

int firstInCol(const Node& node, int column) { //returns row of the top container in each column
    for (int i = 0; i < ROW; ++i) {
        if (node.state[i][column].weight > 0) {
            return i;
        }
    }

    return -1; //empty column
}

int findTop(const Node& node, int column) {
    for (int i = 0; i < ROW; ++i) {
        if (node.state[i][column].weight > 0 || node.state[i][column].weight == -1) {
            return i - 1; //returns -1 if there is no room on that column
        }
    }
    return ROW-1; //return the bottom row because the whole column was empty
}

int weightL (Node node) {
    int weight = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN/2; ++j) {
            if (node.state[i][j].weight > 0) {
                weight += node.state[i][j].weight;
            }
        }
    }

    return weight;
}

int weightR (Node node) {
    int weight = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = COLUMN/2; j < COLUMN; ++j) {
            if (node.state[i][j].weight > 0) {
                weight += node.state[i][j].weight;
            }
        }
    }

    return weight;
}

int Misplaced (Node& node) {
    vector<Container> containers;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (solution[i][j].weight > 0) {
                Container temp = solution[i][j];
                temp.sRow = i;
                temp.sColumn = j;
                containers.push_back(temp);
            }
        }
    }

    int heuristic = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if ((node.state[i][j].weight > 0) && node.state[i][j].weight != solution[i][j].weight) {
                for (unsigned long long h = 0; h < containers.size(); ++h) {
                    if (containers.at(h).weight == node.state[i][j].weight) {
                        heuristic += abs(j - containers.at(h).sColumn) + abs(i - containers.at(h).sRow);
                    }
                }
            }
        }
    }

    return heuristic;
}

bool goalCheck(Node& top) { //Compares puzzle state in node to that of the goal puzzle state
    int left = weightL(top);
    int right = weightR(top);

    int total = left + right;
    int lower = total/2 - (total * .10)/4;
    int upper = total/2 + (total * .10)/4;

    if ((left >= lower) && (left <= upper) && (right >= lower) && (right <= upper)) {
        top.gn += top.lastRow + 1 + top.lastColumn ;
        top.cost.push_back(make_pair(top.lastRow+1, top.lastColumn));
        top.position.push_back(make_pair(top.lastRow, top.lastColumn));
        top.position.push_back(make_pair(-1, -1));
        top.fn = top.gn + top.hn;
        return true;
    } else {
        return false;
    }
}

bool goalCheck2(Node& node) {
   for (int i = 0; i < ROW; ++i) {
       for (int j = 0; j < COLUMN; ++j) {
           if (node.state[i][j].weight != solution[i][j].weight) {
               return false;
           }
       }
   }

    node.gn += node.lastRow + 1 + node.lastColumn ;
    node.fn = node.gn + node.hn;
   return true;
}



Node searchG(vector<vector<Container>> state, int option, vector<Container>& offload, vector<Container>& onloadList) { //MAIN DRIVER FUNCTION that searches for the solution of the puzzle
    QQList* openList = new QQList(); //Make pointer to priority queue made up of Nodes
    vector<Node> closedList;

    Node first = Node(state); //Initiate the first/root Node with the grid of the ship at the start
    first.hn = 0;
    first.gn = 0;
    first.onload = onloadList;

    if (Balanceable(state)) {
        first.balanceable = true;
    } else {
        makeSolution(state);
        first.balanceable = false;
    }
    openList->queue.push(first);
    int iter = 0;

    while (true){
        ++iter;
        if (openList->queue.empty()) { //Check if queue is empty
            cout << "failure" << endl;
            return Node(-1); //failure
        }

        Node top = openList->queue.top(); //Record front node
        closedList.push_back(top);
        openList->queue.pop(); //Remove front node

        if (option == 1) { //balancing
            if (Balanceable(state)) {
                if (goalCheck(top)) { //Check if the Node at the front of the queue has the puzzle goal state
                    cout << "here" << endl;
                    return top;
                }
            } else {
                if (goalCheck2(top)) {
                    cout << "here" << endl;
                    return top;
                }
            }


        } else { //loading/unloading
            if (top.onload.empty() && pinkEmpty(top) && offloading_goal(top, offload)) { //TODO: ADD A STACKED AREA EMPTY CHECK
                cout << "check solution" << endl;
                return top;
            }

            if (offloading_goal(top,offload) && !pinkEmpty(top) && option == 2) {
                //cout << "Almost done" << endl;
                //return top;
                openList = new QQList();
            }

            /*if (top.gn > 30 && top.fn > 30) {
                return top;
            }*/
        }
        //cout << "expanding" << endl;
        expand(openList, closedList, offload, top, option); //Expand the front node recorded above
    }
}

bool pinkEmpty (Node& node) {
    for (int i = ROW; i < ROW + 2; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (node.state[i][j].weight != 0) {
                return false;
            }
        }
    }

    return true;
}

int Deficit(Node node) { //heuristic
    int heuristic = 0;
    int left = weightL(node);
    int right = weightR(node);
    int upper = ((left + right) * .10)/4 + (left+right)/2;
    int lower = (left+right)/2 - ((left + right) * .10)/4;
    //int deficit = -1;

    int emptyCol = -1;
    int weight = 0;

    vector<Container> containers;
    if (left > right) { //get the weights of the left side, find deficit of right side;
        weight = right;
        for (int i = 0; i < ROW; ++i) { //Find all the containers/weights on the left side
            for (int j = 0; j < COLUMN/2; ++j) {
                if (node.state[i][j].weight > 0) {
                    containers.push_back(node.state[i][j]);
                }
            }
        }
        //find the first empty column on the right side(filling up the right side) closest to the middle
        for (int i = 0; i < ROW; ++i) {
            for (int j = COLUMN/2; j < COLUMN; ++j) {
                if (node.state[i][j].weight == 0) {
                    emptyCol = j;
                    goto end;
                }
            }
        }

    } else { //get the weights of the right side, find deficit of left side
        weight = left;
        for (int i = 0; i < ROW; ++i) { //Find all the containers/weights on the right side
            for (int j = COLUMN/2; j < COLUMN; ++j) {
                if (node.state[i][j].weight > 0) {
                    containers.push_back(node.state[i][j]);
                }
            }
        }
        //find the first empty column on the left side(filling up the left side) closest to the middle
        for (int i = 0; i < ROW; ++i) {
            for (int j = COLUMN/2 - 1; j >= 0; --j) {
                if (node.state[i][j].weight == 0) {
                    emptyCol = j;
                    goto end; //break
                }
            }
        }
    }
    end:
    sort(containers.begin(), containers.end(), compareContainer); //sort from heaviest to lightest
    for (unsigned long long i = 0; i < containers.size(); ++i) {
        if ((containers.at(i).weight + weight <= upper)) {
            weight += containers.at(i).weight;
            heuristic += abs(containers.at(i).column - emptyCol);
        }

        if (weight >= lower && weight <= upper) {
            break;
        }
    }

    return heuristic;
}

int verticalDiff(Node& node, int row, int column, int oldRow, int oldColumn) { //first set to second set
    int next = abs(column - oldColumn);
    bool middle = false;

    //going up. Find tallest column. save the row in where the highest is at
    int tallest = 100;
    int inbetween = abs(column-oldColumn) - 1; //number of columns inbetween
    if (column < oldColumn) {
        for (int i = 0; i < ROW; ++i) {
            for (int j = oldColumn - 1; j > column; --j) {
                if (node.state[i][j].weight > 0 && i < tallest) {
                    tallest = i;
                    middle = true;
                }
            }
        }
    } else {
        for (int i = 0; i < ROW; ++i) {
            for (int j = oldColumn + 1; j < column; ++j) {
                if (node.state[i][j].weight > 0 && i < tallest) {
                    tallest = i;
                    middle = true;
                }
            }
        }
    }

    int up = -1;
    if (tallest == oldRow) {
        if (middle) {
            up = 1;
        } else {
            up = 0;
        }
    } else if (tallest < oldRow) { //tallest is taller than what we're moving
        up = abs(tallest - oldRow) + 1;
    } else { //tallest is lower than what we're moving
        up = 0;
        return abs(oldRow - row);//just moving down
    }

    int down = abs(row - (tallest - 1)); //NOTE: this may need to be not abs for it to work idk
    if (next == 1) { //columns are next to each other
        if (row != oldRow) {
            return abs(row - oldRow);
        } else {
            return 0;
        }
    }

    return up + down;
}

int Remove (Node& node, vector<Container>& offload) {
    int heuristic = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            for (unsigned long long a = 0; a < offload.size(); ++a) {
                if (offload.at(a).name == node.state[i][j].name) {
                    heuristic += i + j + 1;
                }
            }
        }
    }

    return heuristic;
}

void moveTo (QQList* open, vector<Node>& closed, vector<Container>& offload, Node& node, int row, int column, int option) {
    //debugging stuff
   // cout << "here" << endl;


    if (row == -3) { //find if it's top or bot pink row
        //cout << "row is -3" << endl;
        if (node.state[ROW][column].name == " UNUSED") { //for the bot pink row
            row = ROW;
        } else { //for the bot pink row
            row = ROW + 1;
        }
    }


    //cout << "Moving " << node.state[node.rowPicked][node.columnPicked].name << " to " << row << "." << column << endl;
    //cout << "ERROR CHECKING: " << oldrow << "." << oldcol << " VS. " << row << "." << column << endl;

    Node temp = node;
    Container empty;
    empty.weight = 0;
    empty.name = " UNUSED";

    //cout << "Moving " << node.state[node.rowPicked][node.columnPicked].name << "(" << node.rowPicked << ", " << node.columnPicked << ")" << " to " << row << "." << column << endl;
    //OutputGrid(node.state, 2);

    string movement;
    //cout << "error" << endl;
    if (row == -1) {
        movement = "Offloading a container " + node.state[node.rowPicked][node.columnPicked].name + " (" + to_string(node.rowPicked) + "," + to_string(node.columnPicked) + ")" + " to -1, -1";
    } else if (node.rowPicked == -2) {
        movement = "Onloading a container " + temp.onload.back().name + " from (-1,-1) to " + to_string(row) + "." + to_string(column);
    } else {
        movement = "Moving " + node.state[node.rowPicked][node.columnPicked].name + "(" + to_string(node.rowPicked) + ", " + to_string(node.columnPicked) + ")" + " to " + to_string(row) + "." + to_string(column);
    }

    temp.moveSet.push_back(movement);
    //cout << "move" << endl;
    //temp.movesT.push_back(make_pair(node.rowPicked, node.columnPicked));
    //temp.movesT.push_back(make_pair(row, column));

    if (row != -1 && column != -1 && node.rowPicked != -2 && node.columnPicked != -2 && row < ROW) { //may need to change back to row != -1 and column != -1
        //cout << "fatal error" << endl;
        Container tempCont = temp.state[temp.rowPicked][temp.columnPicked];
        temp.state[row][column] = tempCont;
        temp.state[temp.rowPicked][temp.columnPicked] = empty;

        temp.moveSet.push_back(temp.state[temp.rowPicked][temp.columnPicked].name);
        temp.position.push_back(make_pair(temp.rowPicked, temp.columnPicked));
        temp.position.push_back(make_pair(row, column));

        if (temp.rowPicked >= ROW) { //if we are moving FROM THE PINK to a place on the ship
            if (temp.rowPicked == ROW) { //moving a container from the first layer of pink onto the ship
                if (row >= ROW) { //we are moving FROM the pink TO the pink
                    temp.gn += abs(temp.rowPicked - row) + abs(column - temp.columnPicked);
                    temp.cost.push_back(make_pair(abs(temp.rowPicked-row), abs(column - temp.columnPicked)));
                } else { //we are moving FROM the pink to the ship
                    //cout << "should be here" << endl;
                    temp.gn += row + 1 + abs(temp.columnPicked - column);
                    temp.cost.push_back(make_pair(row+1, abs(column - temp.columnPicked)));
                }
            } else if (temp.rowPicked == ROW+1 ) { //moving a container from the second layer of the pink onto the ship
                if (row >= ROW) { //we are moving FROM the pink TO the pink
                   temp.gn += abs(temp.rowPicked - row) + abs(column - temp.columnPicked);
                   temp.cost.push_back(make_pair(abs(temp.rowPicked-row), abs(column - temp.columnPicked)));
                } else { //we are moving FROM the pink TO the ship
                    temp.gn += row + 2 + abs(temp.columnPicked - column);
                    temp.cost.push_back(make_pair(row + 2, abs(column - temp.columnPicked)));
                }
            }

            if (offloading_goal(temp, offload) && !pinkEmpty(temp)) {
                //cout << "empty" << endl;
                temp.onlyPink = true;
            }

            if (offloading_goal(temp, offload) && temp.onload.empty() && pinkEmpty(temp)) {
                cout << "got here" << endl;
                temp.gn += column + row + 1;

                   temp.moveSet.push_back(temp.state[row][column].name);
                temp.position.push_back(make_pair(row, column));
                temp.position.push_back(make_pair(-1, -1));
                temp.cost.push_back(make_pair(row + 1, column));
            }
        } else { //moving FROM NORMAL GRID on the ship
            int tempmove = verticalDiff(node, row, column, node.rowPicked, node.columnPicked);
            int tempmove2 = abs(column - temp.columnPicked);

            //temp.costMoves.push_back(tempmove2 + tempmove);
            temp.cost.push_back(make_pair(tempmove, tempmove2));
            //temp.hCost.push_back(tempmove2);
            //temp.vCost.push_back(tempmove);
            temp.gn += tempmove2 + tempmove;
        }
        temp.picked = false;
        temp.rowPicked = row; //this is not very unecessary
        temp.columnPicked = column; //this is very necessary for speed
        //temp.state[row][column].row = row; //this may be unnecessary
        //temp.state[row][column].column = column; //this may be unnecessary

        temp.lastRow = row;
        temp.lastColumn = column;
    }
    //cout << "here" << endl;
    if (temp.rowPicked == -2 && temp.columnPicked == -2) { //onloading a container

        temp.position.push_back(make_pair(-1, -1));
        temp.position.push_back(make_pair(row, column));

        temp.state[row][column] = temp.onload.back();
        temp.moveSet.push_back(temp.state[row][column].name);
        temp.onload.pop_back();

        temp.gn += column + row + 1; //cost to move to spot
        temp.gn += 2; //cost to grab container
        temp.cost.push_back(make_pair(row + 1, column));
        if (temp.onload.empty() && offloading_goal(temp, offload)) {
            temp.gn += column + row + 1;

            temp.position.push_back(make_pair(row, column));
            temp.position.push_back(make_pair(-1, -1));
            temp.cost.push_back(make_pair(row + 1, column));
        }

        temp.picked = false;
        temp.lastRow = row;
        temp.lastColumn = column;
        //cout << "finished onload" << endl;
    }
    //cout << "here2" << endl;
        //node < ROW so that a container from the pink is not picked up and removed off the boat
        //only use pink rows to move containers out of the way, so containers in the pink dont' need to be moved off the ship
    if (option == 2 && row == -1 && column == -1 && node.rowPicked < ROW) { //find the gn of moving to the pink virtual cell and remove the container
        temp.state[temp.rowPicked][temp.columnPicked] = empty;
        temp.gn += temp.rowPicked + temp.columnPicked + 1; //cost of moving container to pink slot
        temp.gn += 2; //cost of removing container from ship

        temp.position.push_back(make_pair(temp.rowPicked, temp.columnPicked));
        temp.position.push_back(make_pair(-1, -1));
        temp.cost.push_back(make_pair(temp.rowPicked + 1, temp.columnPicked));

        //temp.vCost.push_back(temp.rowPicked + 1);
        //temp.hCost.push_back(temp.columnPicked);

        temp.picked = false;
        temp.lastRow = -1;
        temp.lastColumn = 0;
        temp.columnPicked = 0;
        //temp.rowPicked = -1;
        //temp.lastColumn = 0;
    }
    //cout << "here3" << endl;

    if (row >= ROW && temp.rowPicked != -2) { //move the container to the 1st or 2nd row of pink; MOVING TO THE PINK
        //cout << temp.rowPicked << "." << temp.columnPicked << endl;
        //cout << "IN HERE REEEEEEE" << endl;
        Container tempCont = temp.state[temp.rowPicked][temp.columnPicked]; //the container we are going to move is in temp
        temp.position.push_back(make_pair(temp.rowPicked, temp.columnPicked));
        temp.moveSet.push_back(tempCont.name);
        //cout << "here6" << endl;
        //move the container to its new spot
        if (temp.state[ROW+1][column].name == " UNUSED" && temp.state[ROW][column].name != " UNUSED") { //the container we are going to move is going to the top pink row
            //cout << "ONE" << endl;
            tempCont.row = ROW+1;
            tempCont.column = column;
            temp.state[ROW+1][column] = tempCont;
            temp.lastRow = ROW+1;
            temp.lastColumn = column;

            temp.position.push_back(make_pair(ROW+1, column));
            if (temp.rowPicked >= ROW) { //we are moving TO the pink FROM the pink
                //cout << "moving from pink to the pink" << endl;
                temp.gn += abs(temp.rowPicked - row) + abs(column - temp.columnPicked);
                temp.cost.push_back(make_pair(abs(temp.rowPicked-row), abs(column - temp.columnPicked)));
            } else {
               /* cout << "moving from the ship to the pink" << endl;
                cout << "vertical: " << temp.rowPicked + 2 << endl;;
                cout << "horizontal: " << abs(temp.columnPicked - column) << endl; */
                temp.gn += abs(temp.columnPicked - column) + temp.rowPicked + 2;
                temp.cost.push_back(make_pair(temp.rowPicked+2, abs(column - temp.columnPicked)));
            }
            temp.state[temp.rowPicked][temp.columnPicked] = empty;
            temp.rowPicked = ROW+1;
            temp.columnPicked = column;
        } else { //the container we are going to move is moving to the bottom pink row
            //cout << "TWO" << endl;
            tempCont.row = ROW;
            tempCont.column = column;
            temp.state[ROW][column] = tempCont;
            temp.lastRow = ROW;
            temp.lastColumn = column;

            temp.position.push_back(make_pair(ROW, column));
            if (temp.rowPicked >= ROW) { //we are moving TO the pink FROM the pink
                temp.gn += abs(temp.rowPicked - row) + abs(column - temp.columnPicked);
                temp.cost.push_back(make_pair(abs(temp.rowPicked-row), abs(column - temp.columnPicked)));
            } else {
                temp.gn += abs(temp.columnPicked - column) + temp.rowPicked + 1;
                temp.cost.push_back(make_pair(temp.rowPicked + 1, abs(column - temp.columnPicked)));
            }
            temp.state[temp.rowPicked][temp.columnPicked] = empty;
            temp.rowPicked = ROW;
            temp.columnPicked = column;
        }
         //empty out the old spot we just moved it from
        //cout << "Grid after movement: " << endl;
        //OutputGrid(temp.state, 2); cout << endl;
        temp.picked = false; //update that we just moved it and now it should be blue arrows expanded

    }
    //cout << "here4" << endl;

    if (temp.balanceable && option == 1) {
        temp.hn = Deficit(temp); //balancing a ship that can be balanced
        //cout << "Moved " << temp.state[row][column].name << " from " << oldrow << "." << oldcol << " to " << row << "." << column << endl;
        //OutputGrid(temp.state, 1);
        //cout << "hn is: " << temp.hn << endl;
        //cout << "gn: " << temp.gn << endl << endl;
        //cout << temp.hn << endl;
        //cout << endl;
    } else if (!temp.balanceable && option == 1) {
        temp.hn = Misplaced(temp); //balancing a ship that cannot be balanced
    }

    if (option == 2) {
        temp.hn = Remove(temp, offload); //offloading containers from a ship
        if (offloading_goal(temp, offload) && !pinkEmpty(temp)) {
        //if (temp.onlyPink) {
            //cout << "empty" << endl;
            //temp.hn = emptyPinkHeur(temp);
            //cout << "hn is now: " << temp.hn << endl;
            //OutputGrid(temp.state, 2);
            //cout << endl;
            //temp.hn = emptyPinkHeur(temp);
        } else if (offloading_goal(temp, offload) && !pinkEmpty(temp)) {
            //temp.hn += emptyPinkHeur(temp);
            //cout << "NOT" << endl;
        }
    }
    //cout << "Cost of movement: " << temp.gn - oldgn << endl;
    //temp.costMoves.push_back(temp.gn - oldgn); //NOTE: May need this idk
    //cout << "Grid after moving" << endl;
    //NOTE: May need to add a heuristic to ships that are done with their service but still need to move containers in pink rows
    temp.fn = temp.gn + temp.hn;
    //cout << "fn: " << temp.fn << endl << endl;


    if (offloading_goal(temp, offload) && !pinkEmpty(temp)) {
        temp.onlyPink = true;
        //if (temp.onlyPink) {
            //cout << "empty" << endl;
            //temp.hn = emptyPinkHeur(temp);
            //cout << "hn is now: " << temp.hn << endl;
            //OutputGrid(temp.state, 2);
            //cout << endl;
            //temp.hn = emptyPinkHeur(temp);
            //temp.fn = temp.gn + temp.hn;
    }
    //cout << "fn: " << temp.fn << endl;
    //cout << "gn: " << temp.gn << endl;
    //cout << "hn: " << temp.hn << endl << endl;

    temp.picked = false;

    if (offloading_goal(node, offload) && !pinkEmpty(node)) {
        cout << "new fn: " << temp.fn << endl;
        cout << "hn: " << temp.hn << endl;
    }

    open->queue.push(temp);
    return;
}

int emptyPinkHeur(Node& node) {
    int heuristic = 0;
    for (int i = ROW; i < ROW + 2; ++i) {
        for (int j = 0;j < COLUMN; ++j) {
            if (node.state[i][j].name != " UNUSED") {
                if (i == ROW) {
                    heuristic += 2;
                } else {
                    heuristic += 3;
                }
            }
        }
    }

    return heuristic;
}




bool checkOffload (Node& node, vector<Container>& offload) {
    for (unsigned long long i = 0; i < offload.size(); ++i) {
        if (offload.at(i).name == node.state[node.rowPicked][node.columnPicked].name) {
            return true;
        }
    }

    return false;
}


void expand (QQList* open, vector<Node>& closed, vector<Container>& offload, Node node, int option) {
        if (node.picked) { //expand into red arrows, meaning move the picked node to the top of each column
            for (int i = 0; i < COLUMN; ++i) { //i is each column
                if (i != node.columnPicked) { //stop some duplicating from occuring
                    if (findTop(node, i) != -1) { //-1 if the column is full, so container cannot be moved here
                        //move to columns that aren't full
                        moveTo(open, closed, offload, node, findTop(node, i), i, option);
                    } else { //the column at i is full, try moving to the pink rows
                        if (!offloading_goal(node, offload)/* && !pinkEmpty(node)*/) {
                            moveTo(open, closed, offload, node, -3, i, option);
                        }
                        //moveTo(open, closed, offload, node, -3, i, option); //-3 to signal that we need to try moving to the pink rows
                    }
                }
            }
            if (option == 2 && node.columnPicked != -2) { //offloading something to the pink cell
                if (checkOffload(node, offload)) {
                    moveTo(open, closed, offload, node, -1, -1, option);
                }
            }
        } else { //expand into blue arrows/picking a container to move/move crane to new container it will pick up
            /*cout << "blue arrow expansion on node with fn: " << node.fn << endl;
            cout << "Grid looks like: \n";
            OutputGrid(node.state, 2);  */
            for (int i = 0; i < COLUMN; ++i) { //Branching factor is the number of columns. Pick which container to pick up and push to the queue
                //cout << "i is: " << i << endl;
                Node temp = node;
                int row = firstInCol(temp, i);
                //cout << "row: " << row << endl;
                //cout << "columnpicked: " << temp.columnPicked << endl;
                if (row != -1 && i != temp.columnPicked) { //empty column if -1 //&& i != temp.columnPicked
                    //cout << "Blue arrow picked: " << temp.state[row][i].name << endl;
                    if (row == 0 && node.state[ROW][i].name != " UNUSED" && option == 2) { //if the container is on the top and there is pink above it, pick above it
                        //cout << "test" << endl;
                        //check if there is something above pink container bottom slot
                        if (node.state[ROW+1][i].name != " UNUSED") {//pink slot to pick is the top pink row
                            //cout << "BAD STUFF" << endl;
                            temp.rowPicked = ROW + 1;
                            temp.columnPicked = i;

                            temp.position.push_back(make_pair(temp.lastRow, temp.lastColumn));
                            temp.position.push_back(make_pair(ROW+1, i));
                            temp.picked = true;
                            if (temp.lastRow == ROW) { //moving from bot pink row to top row

                                temp.gn += abs(temp.columnPicked - i) + 1;
                                temp.cost.push_back(make_pair(1, abs(temp.columnPicked-i)));
                            } else if (temp.lastRow == ROW + 1) { //moving from pink top row to top pink row
                                temp.gn += abs(temp.columnPicked - i);
                                temp.cost.push_back(make_pair(0, abs(temp.columnPicked-i)));
                            } else { //regular movement from somewhere to top pink row
                                if (temp.lastRow == -1) { //-1 -1 spot to drop off a container from ship
                                    temp.gn += abs(temp.lastColumn) + 1;
                                    temp.cost.push_back(make_pair(1, temp.lastColumn));
                                } else {
                                    temp.gn += abs(temp.lastColumn - i) + temp.lastRow + 2;
                                    temp.cost.push_back(make_pair(temp.lastRow+2, abs(temp.lastColumn-i)));
                                }
                            }
                            //cout << "actual name is: " << node.state[ROW+1][i].name << endl;
                            open->queue.push(temp);
                        } else if (node.state[ROW][i].name != " UNUSED") { //pink slot to pick is the first pink row
                            //cout << "GOOD STUFF" << endl;
                            temp.rowPicked = ROW;
                            temp.columnPicked = i;

                            temp.position.push_back(make_pair(temp.lastRow, temp.lastColumn));
                            temp.position.push_back(make_pair(ROW, i));
                            temp.picked = true;
                            if (temp.lastRow == ROW) { //moving from pink first row to pink first row
                                //cout << "MOVEMENT" << endl;
                                temp.gn += abs(temp.columnPicked - i);
                                temp.cost.push_back(make_pair(0, abs(temp.columnPicked-i)));
                            } else if (temp.lastRow == ROW + 1) { //moving from pink first row to second pink row
                                //cout << "MOVEMENT2" << endl;
                                temp.gn += abs(temp.columnPicked - i) + 1;
                                temp.cost.push_back(make_pair(1, abs(temp.columnPicked-i)));
                            } else { //regular movement from somwhere to first pink row
                                if (temp.lastRow == -1) { //last thing dropped off was off the ship
                                    //cout << "MOVEMENT ";
                                    temp.gn += abs(temp.lastColumn - i);
                                    temp.cost.push_back(make_pair(0, abs(temp.lastColumn-i)));
                                } else {
                                    temp.gn += abs(temp.lastColumn - i) + temp.lastRow + 1;
                                    temp.cost.push_back(make_pair(temp.lastRow+1, abs(temp.lastColumn-i)));
                                }
                            }
                            //cout << "actual name is: " << node.state[ROW][i].name << endl;
                            temp.fn = temp.hn + temp.gn; //SOMETHING NEDW
                            open->queue.push(temp);
                        }
                    } else if (!offloading_goal(temp, offload) || option == 1) {// && !pinkEmpty(node)/*!temp.onlyPink*/) {
                        //cout << "picking a blue that is not from the pink rows" << endl;
                        // Below code is for when a blue arrow goes to a container on the ship, accounts for when
                        //the cane just dropped a container off from the pink row
                        temp.rowPicked = row;
                        temp.columnPicked = i;

                        temp.position.push_back(make_pair(temp.lastRow, temp.lastColumn));
                        temp.position.push_back(make_pair(row, i));
                        temp.picked = true;
                        if (temp.lastRow == ROW && option == 2) { //bot pink row
                            //cout << "gn i think right here" << endl;
                            temp.gn += row + abs(temp.lastColumn - i) + 1;
                            temp.cost.push_back(make_pair(row + 1, abs(temp.lastColumn-i)));
                        } else if (temp.lastRow == ROW + 1 && option == 2) { //top pink row
                            temp.gn += row + 2 + abs(temp.lastColumn - i);
                            temp.cost.push_back(make_pair(row+2, abs(temp.lastColumn-i)));
                        } else if (temp.lastRow == -1 && option == 2) {
                            temp.gn += i + row + 1;
                            temp.cost.push_back(make_pair(row+1, i));
                        } else {
                            temp.gn += abs(temp.lastColumn - i) + verticalDiff(temp, row, i, temp.lastRow, temp.lastColumn); //cost of crane movement
                            temp.cost.push_back(make_pair(verticalDiff(temp, row, i, temp.lastRow, temp.lastColumn), abs(temp.lastColumn-i)));
                        }
                        open->queue.push(temp);
                    }
                }
            }

            if (!node.onload.empty()) { //try onloading stuff
                    //cout << "onload" << endl;
                    Node temp = node;
                    temp.rowPicked = -2; //-2 to signal that we are onloading something
                    temp.columnPicked = -2;

                    temp.position.push_back(make_pair(-1, -1));
                    temp.position.push_back(make_pair(temp.lastRow, temp.lastColumn));
                    temp.picked = true;
                    temp.gn += temp.lastColumn + temp.lastRow + 1;
                    temp.cost.push_back(make_pair(temp.lastRow+1, temp.lastColumn));
                    open->queue.push(temp);
                }
        }
    return;
}



void read_manifest (vector<vector<Container>>& ship , vector<Container>& weights) {
    ifstream manifest ("manifest_case4.txt"); //Populate the grid with containers
    char buffer[11]; //Size of string that is before the weight
    char buffer3[3];
    char buff_char;
    string weight_string;
    string name;

    int row = 0;
    for (int i = ROW-1; i > -1; --i) {
        ++row;
        for (int j = 0; j < COLUMN; ++j) {
            //Store the position in each Container object
            ship[i][j].row = row;
            ship[i][j].column = j+1;

            manifest.read(buffer, sizeof(buffer) - 1); //Gets rid of all the the characters before the weight
            for (int h = 0; h < 5; ++h) { //This loop will get the five digit weight string and store it in weight_string
                manifest.get(buff_char);
                weight_string += buff_char;
            }
            manifest.read(buffer3, sizeof(buffer3) - 1); //Gets rid of the characters before the name of the container(could be NAN or UNUSED)
            getline(manifest, name); //Gets the name and stores it in the string name
            //Name and weight have been read from manifest, now will store the information in the Contianer class for that slot
            ship[i][j].name = name; //assign name
            if (name == " NAN") {
                ship[i][j].weight = -1;
            } else {
                ship[i][j].weight = stoi(weight_string); //assign weight
            }
            if (ship[i][j].weight != 0) { //If there is a container then add it to the list of containers for balancing
                weights.push_back(ship[i][j]);
            }
            weight_string = "";
            }
    }
            manifest.close();
}

void OutputGrid (vector<vector<Container>>& ship, int option) {
    //option 1 is weight, option 2 is name, option 3 is position
    for (unsigned long long i = 0; i < ship.size(); ++i) {
        for (unsigned long long j = 0; j < ship.at(0).size(); ++j) {
            if (option == 1) {
                cout << ship[i][j].weight << " ";
            } else if (option == 2) {
                cout << ship[i][j].name << " ";
            } else if (option == 3) {
                cout << ship[i][j].row << "." << ship[i][j].column << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void OutputList (const vector<Container>& weights) {
    for (unsigned long long i = 0; i < weights.size(); ++i) {
        Container temp = weights.at(i);
        cout << temp.name << " " << temp.weight << " " << temp.row << "." << temp.column << endl;
    }
}

bool Balanceable (vector<vector<Container>>& ship) {
    vector<Container> containers;
    Node node = Node(ship);

    int left = weightL(node);
    int right = weightR(node);

    int total = left + right;
    int lower = total/2 - (total * .10)/4;
    int upper = total/2 + (total * .10)/4;

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (ship[i][j].weight > 0) {
                containers.push_back(ship[i][j]);
            }
        }
    }
    sort(containers.begin(), containers.end(), compareContainer); //sort from heaviest to lightest
    int totalWeight = 0;
    for (unsigned long long i = 0; i < containers.size(); ++i) {
        if ((containers.at(i).weight + totalWeight <= upper)) {
            totalWeight += containers.at(i).weight;
        }
    }

    if (totalWeight >= lower && totalWeight <= upper) {
        return true;
    } else {
        return false;
    }
}

void makeSolution(vector<vector<Container>>& ship) {
    vector<Container> containers;
    Container nan;
    nan.weight = -1;
    nan.name = " NAN";

    Container unused;
    unused.weight = 0;
    unused.name = " UNUSED";

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (ship[i][j].weight > 0) {
                containers.push_back(ship[i][j]);
            }

            if (ship[i][j].weight == -1) {
                solution[i][j] = nan;
            }

            if (ship[i][j].weight == 0) {
                solution[i][j] = unused;
            }
        }
    }
    sort(containers.begin(), containers.end(), compareContainerLight); //sort from lightest  to heaviest
    for (int i = ROW - 1; i >= 0; --i) {
        for (int j = 0; j < COLUMN/2; ++j) {
            solution[i][COLUMN/2 - 1 - j] = containers.back(); //left side
            containers.pop_back();
            if (containers.empty()) {
                goto finish;
            }
            solution[i][COLUMN/2 + j] = containers.back(); //right side
            containers.pop_back();
            if (containers.empty()) {
                goto finish;
            }
        }
    }

    finish:

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (solution[i][j].weight == 0) {
                solution[i][j] = unused;
            }
        }
    }

    return;
}
