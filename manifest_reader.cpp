#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Container {
    public: 
        string name;
        int weight = 0;
};

void read_manifest (vector<vector<Container>>& ship);

void OutputGrid (vector<vector<Container>>& ship, int option) {
    //option 1 is weight, option 2 is name
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (option == 1) {
                cout << ship[i][j].weight << " ";
            } else if (option == 2) {
                cout << ship[i][j].name << " ";
            }
        }
        cout << endl;
    } 
}


int main () {
    Container emptyContainer;
    emptyContainer.weight = 0;
    vector<vector<Container>> ship (8, vector<Container> (12, emptyContainer)); //Make empty ship grid
    //OutputGrid(ship); //Check that grid is empty
    read_manifest(ship);
    OutputGrid(ship, 1);
    OutputGrid(ship, 2);


}

void read_manifest (vector<vector<Container>>& ship) {
    ifstream manifest ("manifest_case4.txt"); //Populate the grid with containers
    char buffer[11]; //Size of string that is before the weight
    char buffer3[3];
    char buff_char;
    string weight_string;
    string name;


    for (int i = 7; i > -1; --i) {
        for (int j = 0; j < 12; ++j) {
            manifest.read(buffer, sizeof(buffer) - 1);
            for (int h = 0; h < 5; ++h) {
                manifest.get(buff_char);
                weight_string += buff_char;
            }
            manifest.read(buffer3, sizeof(buffer3) - 1);
            getline(manifest, name);
            //Name and weight have been read from manifest, now will store the information in the Contianer class for that slot
            ship[i][j].name = name;
            ship[i][j].weight = stoi(weight_string);
            weight_string = "";
            }
    }
            manifest.close();
}