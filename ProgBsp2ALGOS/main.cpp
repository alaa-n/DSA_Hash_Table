#include "include.h"

int main(int argc, char* argv[]){
    if (argc < 2) {  // checking if argc is less than 2 to ensure that the user has provided the filename argument.
        cout << "Error: no file name provided.\n";
        return 1;
    }

    //---- EXECUTED IN ALL CASES, WHETHER ONE FILE NAME IS PASSED OR TWO ----------------------
    string filename1 = argv[1];
    treenode* root = createTreeFromFilename(filename1);
    printStats(root);
    cout << endl;

    //---- EXECUTED ONLY IN CASE TWO FILE NAMES ARE PASSED -------------------------------------
    if(argc > 2){
        string filename2 = argv[2];
        treenode* subtreeRoot = createTreeFromFilename(filename2);

        if (countNodes(subtreeRoot) == 1){
            checkNumber(root, subtreeRoot);
        } else {
            if(isSubtree(root, subtreeRoot)){
                cout << "Subtree found" << endl;
            } else {
                cout << "Subtree not found!" << endl;
            }
        }
    }

    return 0;
}
