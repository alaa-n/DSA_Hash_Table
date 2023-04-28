#ifndef PROGBSP2ALGOS_TREENODE_H
#define PROGBSP2ALGOS_TREENODE_H

#define FILE_PATH "/Users/alaa/CLionProjects/ProgBsp2ALGOS/"
using namespace std;
bool avl = true;
struct treenode{
    int value;
    treenode* left;
    treenode* right;
};

treenode* createNode(int value){
    treenode* result = new treenode;
    result->left = nullptr;
    result->right = nullptr;
    result->value = value;
    return result;
}
treenode* insert(int value, treenode* tree) {
    if (tree == nullptr) {
        tree = createNode(value);
    } else {
        if (value == tree->value) {
            // check if value is already in the tree, do not insert again
            return tree;
        } else if (value < tree->value) {
            tree->left = insert(value, tree->left);
        } else {
            tree->right = insert(value, tree->right);
        }
    }
    return tree;
}
treenode* createTreeFromFilename(string filename){
    string nameWPath = filename;
    string path = FILE_PATH;
    nameWPath = path + nameWPath + ".txt";
    ifstream file(nameWPath);
    if (!file) {
        cout << "Error: could not open file " << nameWPath << ".\n";
        return nullptr;
    }
    // read from the second file and add into subtree
    treenode* root = nullptr;
    int value;
    while (file >> value) {
        root = insert(value, root);
    }
    file.close();
    return root;
}
// B A L A N C E   &   A V L :
int height(treenode* tree) {
    // Calculate hight of each node to use in Balance Factor calculation
    if (tree == nullptr) {
        return 0;
    } else {
        int leftHeight = height(tree->left);
        int rightHeight = height(tree->right);
        // height is treeMax Niveau of all leaves +1
        return 1 + max(leftHeight, rightHeight);
    }
}
void checkBal(treenode* tree) {
    if (tree == nullptr) {
        return;
    }

    // Balance Factor defined as bal(k) = h(rechter Teilbaum) - h(linker Teilbaum)
    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);
    int bal = rightHeight - leftHeight;

    checkBal(tree->right);
    checkBal(tree->left);

    if (bal > 1 || bal < -1) {
        cout << "bal(" << tree->value << ") = " << bal << " (AVL violation!)" << endl;
        avl = false;
    } else {
        cout << "bal(" << tree->value << ") = " << bal << endl;
    }
}
void checkAVL(){
    if(avl){
        cout << "AVL: yes" << endl;
    } else {
        cout << "AVL: no" << endl;
    }
}
// S T A T I S T I C S :
int treeMin(treenode* tree){
    if (tree == nullptr) {
        // If the tree is empty, return a very large value that represents positive infinity
        return INT_MAX;
    } else {
        // Recursively calculate the minimum value in the left subtree
        int leftMin = treeMin(tree->left);

        // Recursively calculate the minimum value in the right subtree
        int rightMin = treeMin(tree->right);

        // Return the minimum of the current node's value, the left subtree's minimum value, and the right subtree's minimum value
        return min(tree->value, min(leftMin, rightMin));
    }
}
int treeMax(treenode* tree){
    if (tree == nullptr) {
        // If the tree is empty, return a very small value that represents negative infinity
        return INT_MIN;
    } else {
        // Recursively calculate the maximum value in the left subtree
        int leftMax = treeMax(tree->left);

        // Recursively calculate the maximum value in the right subtree
        int rightMax = treeMax(tree->right);

        // Return the maximum of the current node's value, the left subtree's maximum value, and the right subtree's maximum value
        return max(tree->value, max(leftMax, rightMax));
    }
}
int countNodes(treenode* tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        int leftCount = countNodes(tree->left);
        int rightCount = countNodes(tree->right);
        return 1 + leftCount + rightCount;
    }
}
double treeAvg(treenode* tree){
    if (tree == nullptr) {
        return 0.0;
    } else {
        // avg = sum/count -> umgeformt: sum = avg * count. This way we can find the sum using treeAvg recursively.
        double leftSum = treeAvg(tree->left) * countNodes(tree->left);
        double rightSum = treeAvg(tree->right) * countNodes(tree->right);

        // Return the average of the current node's value, the left subtree's sum, and the right subtree's sum
        return (tree->value + leftSum + rightSum) / countNodes(tree);
    }
}
void printStats(treenode* tree){
    checkBal(tree);
    checkAVL();
    cout << "treeMin: " << treeMin(tree) << ", treeMax: " << treeMax(tree) << ", treeAvg: " << treeAvg(tree) << endl;
}
// S E A R C H I N G :
bool includesNumber(treenode* tree, int value){
    if(tree == nullptr) return false;
    if(tree->value == value){
        return true;
    } else if(value < tree->value){
        return includesNumber(tree->left, value);
    } else {
        return includesNumber(tree->right, value);
    }
}
void printSubtree(treenode* tree, int value) {
    if (tree == nullptr) {
        return; // If the tree is empty, return
    } else if (tree->value == value) {
        // If the current node contains the value, print it and return
        cout << tree->value;
        return;
    } else if (value < tree->value) {
        // If the value is less than the current node's value,
        // print the current node's value and recursively search the left subtree
        cout << tree->value << ", ";
        printSubtree(tree->left, value);
    } else {
        // If the value is greater than the current node's value,
        // print the current node's value and recursively search the right subtree
        cout << tree->value << ", ";
        printSubtree(tree->right, value);
    }
}
void checkNumber(treenode* tree, treenode* subtree){
    if(includesNumber(tree, subtree->value)){
        cout << subtree->value << " found ";
        printSubtree(tree, subtree->value);
        cout << endl;
    } else {
        cout << subtree->value << " not found!" << endl;
    }
}
bool isSubtree(treenode* tree, treenode* subtree){
    if (subtree == nullptr) {
        // If the subtree is empty, it is a valid subtree
        return true;
    } else if (tree == nullptr) {
        // If the tree is empty but the subtree is not, it is not a valid subtree
        return false;
    } else if (tree->value == subtree->value) {
        // If the current nodes match, check if the left and right subtrees match
        return isSubtree(tree->left, subtree->left) && isSubtree(tree->right, subtree->right);
    } else {
        // Recursively search the left and right subtrees for the subtree
        return isSubtree(tree->left, subtree) || isSubtree(tree->right, subtree);
    }
}

// F O R   D E B U G G I N G :
void traverseInOrder(treenode* tree) {
    if (tree != nullptr) {
        traverseInOrder(tree->left);
        cout << tree->value << " ";
        traverseInOrder(tree->right);
    }
}
void printTree(treenode* tree){
    if(tree == nullptr){
        cout << "EMPTY" << endl;
        return;
    }
    cout << "value: " << tree->value << endl;
    cout << "Left: " << endl;
    printTree(tree->left);
    cout << "Right: " << endl;
    printTree(tree->right);
    cout << "done" << endl;
}


#endif //PROGBSP2ALGOS_TREENODE_H
