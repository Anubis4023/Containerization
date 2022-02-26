#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Container {
    public: 
        string name;
        int weight = 0;
        int row = 0;
        int column = 0;
};

void read_manifest (vector<vector<Container>>& ship, vector<Container>& weights);
void OutputGrid (vector<vector<Container>>& ship, int option);
void OutputList (const vector<Container>& weights);


int main () {
    Container emptyContainer;
    vector<vector<Container>> ship (8, vector<Container> (12, emptyContainer)); //Make empty ship grid
    vector<Container> weights; //Make list for containers on the ship
    //OutputGrid(ship); //Check that grid is empty
    read_manifest(ship, weights);
    //OutputGrid(ship, 1);
    //OutputGrid(ship, 2);  
    //OutputGrid(ship, 3);
    OutputList(weights);


}


void read_manifest (vector<vector<Container>>& ship , vector<Container>& weights) {
    ifstream manifest ("manifest_case4.txt"); //Populate the grid with containers
    char buffer[11]; //Size of string that is before the weight
    char buffer3[3];
    char buff_char;
    string weight_string;
    string name;

    int row = 0;
    for (int i = 7; i > -1; --i) {
        ++row;
        for (int j = 0; j < 12; ++j) {
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
            ship[i][j].weight = stoi(weight_string); //assign weight
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
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 12; ++j) {
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
}

void OutputList (const vector<Container>& weights) {
    for (int i = 0; i < weights.size(); ++i) {
        Container temp = weights.at(i);
        cout << temp.name << " " << temp.weight << " " << temp.row << "." << temp.column << endl;
    }
}