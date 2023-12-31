// @Author nonamexishere

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void takePatterns (vector<int>& input, string& varName);

class Node{
    private:
        int data;
        Node *left;
        Node *right;
    public:
        Node(int data);
        void set_left(Node*);
        void set_right(Node*);
        void set_data(int);
        int get_data();
        Node* get_left();
        Node* get_right();
};

class BinaryTree{
    private:
        Node *root;
    public:
        BinaryTree();
        Node* buildTree(vector<int>& input1, vector<int>& input2, int choice);
        Node* buildTreeHelper(vector<int>& input1, vector<int>& input2, int choice, int input1Start, int input1End, int input2Start, int input2End);
        void insert(int data);
        void remove(int id);
        bool search(int id);
        int getHeight();
        void printToConsole(int);
        void printHelper(Node*, int);
        Node* get_root();
        void set_root(Node*);
        void deleteTree();
};

int main() {
    cout << "---------- CONVERT TO ----------\n";
    cout << "1 - INORDER\n";
    cout << "2 - PREORDER\n";
    cout << "3 - POSTORDER\n";

    int choice = -1;
    cout << "Choose the one you want to convert to: ";
    cin >> choice;
    while (choice < 1 || choice > 3) {
        cout << "Your number must be between 1 and 3\nYour choice: "; 
        cin >> choice;
    }
    
    vector<int> inorder;
    vector<int> preorder;
    vector<int> postorder;

    BinaryTree* bt = new BinaryTree();

    if (choice == 1) {
        string varName = "preorder";
        takePatterns(preorder, varName);
        varName = "postorder";
        takePatterns(postorder, varName);
        bt->set_root(bt->buildTree(preorder, postorder, choice));
    }
    else if (choice == 2) {
        string varName = "inorder";
        takePatterns(inorder, varName);
        varName = "postorder";
        takePatterns(postorder, varName);
        bt->set_root(bt->buildTree(inorder, postorder, choice));
    }
    else {
        string varName = "inorder";
        takePatterns(inorder, varName);
        varName = "preorder";
        takePatterns(preorder, varName);
        bt->set_root(bt->buildTree(inorder, preorder, choice));
    }

    if (bt->get_root() == nullptr) {
        cout << "Somethings went wrong!\n";
        return 1;
    }
    else {
        bt->printToConsole(choice);
    }
    bt->deleteTree();
    delete bt;
}

void takePatterns (vector<int>& input, string& varName) {
    string userInput;
    cout << "Write " << varName << " pattern (type 'exit' as last element to stop): ";
    while (true) {
        cin >> userInput;
        if (userInput == "exit") {
            break;
        }

        try {
            int value = stoi(userInput);
            input.push_back(value);
        } 
        catch (invalid_argument&) {
            cout << "Invalid input. Please enter a numeric value or 'exit' to stop.\n";
        }
    }
}


Node::Node(int data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}
void Node::set_left(Node* l) {
    this->left = l;
}
void Node::set_right(Node* r) {
    this->right = r;
}
void Node::set_data(int data) {
    this->data = data;
}
int Node::get_data() {
    return data;
}
Node* Node::get_left() {
    return left;
}
Node* Node::get_right() {
    return right;
}

BinaryTree::BinaryTree() {
    this->root = nullptr;
}
void BinaryTree::insert(int data) {
    // if root is null insert to the root
    if (root == nullptr) {
        root = new Node(data);
        return;
    }
    Node* current = root;
    while (true) {
        int currentId = current->get_data();
        int employeeId = data;
        // if new employee's id is lower than our current id check whether the left ptr is null
        // if left ptr is null set new employee there else set our current as our currents left
        if (employeeId < currentId) {
            if (current->get_left() == nullptr) {
                current->set_left(new Node(data));
                return;
            }
            current = current->get_left();
        }
        // if is higher apply alghoritm above for right ptr
        else if (employeeId > currentId) {
            if (current->get_right() == nullptr) {
                current->set_right(new Node(data));
                return;
            }
            current = current->get_right();
        }
        else {
            // if equal duplicate
            return;
        }
    }
}
void BinaryTree::remove(int id) {
    // if root is null which means there is no employee
    if (root == nullptr) {
        cout <<  "ERROR: There is no Employee\n";
        return;
    }
    Node* current = root;
    Node* parent = nullptr;
    
    // while id is not equal to current id keep searching
    while (current != nullptr && current->get_data() != id) {
        // we set parent as current node before changing current in order to be able to set it as a parent node
        parent = current;
        // if id is higher than the current id we set current as right node if lower we set current as left node
        if (id < current->get_data()) {
            current = current->get_left();
        }
        else if (id > current->get_data()) {
            current = current->get_right();
        }
    }
    // if the current is null after setting current as right or left this means id is not in tree
    if (current == nullptr) {
        cout << "ERROR: An invalid ID to delete\n";
        return;
    }
    // if the current is not null this means we found it
    // now there are four scenarios: current has no child, current has no left child, current has no right child, current has both child
    if (current->get_left() == nullptr && current->get_right() == nullptr) {
        // if parent is null this means the id we are looking for is in the root
        if (parent == nullptr) {
            root = nullptr;
        }
        // if current has no child we remove it
        else if (parent->get_left() == current) {
            parent->set_left(nullptr);
        }
        else if (parent->get_right() == current) {
            parent->set_right(nullptr);
        }
        delete current;
    }
    // if has no left child
    else if (current->get_left() == nullptr && current->get_right() != nullptr) {
        // if parent is null this means the id we are looking for is in the root
        if (parent == nullptr) {
            root = current->get_right();
        }
        // we change the location of current with current's right and delete current
        else if (parent->get_left() == current) {
            parent->set_left(current->get_right());
        }
        else if (parent->get_right() == current) {
            parent->set_right(current->get_right());
        }
        delete current;
    }
    // if has no right child
    else if (current->get_right() == nullptr && current->get_left() != nullptr) {
        // if parent is null this means the id we are looking for is in the root
        if (parent == nullptr) {
            root = current->get_left();
        }
        // we change the location of current with current's left and delete current
        else if (parent->get_left() == current) {
            parent->set_left(current->get_left());
        }
        else if (parent->get_right() == current) {
            parent->set_right(current->get_left());
        }
        delete current;
    }
    // if has both child :(
    else {
        Node* tmp = current->get_right();
        Node* tmpParent = current;
        // we are searching for the least bigger number of current
        while (tmp->get_left() != nullptr) {
            tmpParent = tmp;
            tmp = tmp->get_left();
        }
        // if tmp parent is equal to current which means current's right child has no left child
        if (tmpParent == current) {
            tmp->set_left(current->get_left());
            if (parent == nullptr) {
                root = tmp;
            }
            else if (parent->get_left() == current) {
                parent->set_left(tmp);
            }
            else if (parent->get_right() == current) {
                parent->set_right(tmp);
            }
            delete current;
        }
        // if tmp's right is not null which means the least bigger number's node has right child we are setting current employee as tmp employee and tmp parents left as tmp's right
        else if (tmp->get_right() != nullptr) {
            current->set_data(tmp->get_data());
            tmpParent->set_left(tmp->get_right());
            tmp->set_right(nullptr);
            delete tmp;
        }
        // if tmp's right is null which means the least bigger number's node has no right child we are setting current employee as tmp employee
        else {
            current->set_data(tmp->get_data());
            tmpParent->set_left(nullptr);
            delete tmp;
        }
    }
}
bool BinaryTree::search(int id) {
    Node* current = root;
    // while current is not null we search for id
    while (true) {
        // if current is null return nullptr which means id is not in the tree
        if (current == nullptr) {
            return false;
        }
        if (id < current->get_data()) {
            current = current->get_left();
        }
        else if (id > current->get_data()) {
            current = current->get_right();
        }
        else {
            return true;
        }
    }
    // we will not reach this point but in order not to get any warnings we return null
    return false;
}
int BinaryTree::getHeight() {
    // if tree is empty return 0
    if (!root) {
        return 0;
    }
    // create stack which holds Node and int pairs
    stack<pair<Node*, int>> heightStack;
    int maxHeight = 0;
    // push root and 1 to start to process, since root is not empty
    heightStack.push(pair<Node*, int>(root, 1));
    // while stack is not empty check left and right childs
    while (!heightStack.empty()) {
        Node* tmp = heightStack.top().first;
        int tmpHeight = heightStack.top().second;
        heightStack.pop();
        // check whether the current heightStack height is biggger or not
        maxHeight = max(maxHeight, tmpHeight);
        // push right node if there is a node in the right
        if (tmp->get_right()) {
            heightStack.push(pair<Node*, int>(tmp->get_right(), tmpHeight + 1));
        }
        // push left node if there is a node in the left
        if (tmp->get_left()) {
            heightStack.push(pair<Node*, int>(tmp->get_left(), tmpHeight + 1));
        }
    }
    return maxHeight;
}
void BinaryTree::printHelper(Node* tmp, int choice) {
    if (choice == 1) {
        if (tmp) {
            printHelper(tmp->get_left(), 1);
            cout << tmp->get_data() << ' ';
            printHelper(tmp->get_right(), 1);
        }
    }
    else if (choice == 2) {
        if (tmp) {
            cout << tmp->get_data() << ' ';
            printHelper(tmp->get_left(), 2);
            printHelper(tmp->get_right(), 2);
        }
    }
    else {
        if (tmp) {
            printHelper(tmp->get_left(), 3);
            printHelper(tmp->get_right(), 3);
            cout << tmp->get_data() << ' ';
        }
    }
}
void BinaryTree::printToConsole(int choice) {
    printHelper(root, choice);
}
Node* BinaryTree::get_root() {
    return root;
}
void BinaryTree::set_root(Node* root) {
    this->root = root;
}
void BinaryTree::deleteTree() {
    // if root null this means tree is already empty
    if (root == nullptr) {
        return;
    }
    // we create stack in order not to call function recursively
    stack<Node*> deleteStack;
    deleteStack.push(root);

    while (!deleteStack.empty()) {
        Node* current = deleteStack.top();
        deleteStack.pop();
        if (current->get_right()) {
            deleteStack.push(current->get_right());
        }
        if (current->get_left()) {
            deleteStack.push(current->get_left());
        }
        // delete node part
        delete current;
    }

    // we set root to null after deleting the tree
    root = nullptr; 
}

Node* BinaryTree::buildTree(vector<int>& input1, vector<int>& input2, int choice) {
    if (input1.empty() || input2.empty() || input1.size() != input2.size()) {
        return nullptr;
    }
    return buildTreeHelper(input1, input2, choice, 0, input1.size() - 1, 0, input2.size() - 1);
}
Node* BinaryTree::buildTreeHelper(vector<int>& input1, vector<int>& input2, int choice, int input1Start, int input1End, int input2Start, int input2End) {
    if (input1Start > input1End || input2Start > input2End) {
        return nullptr;
    }
    if (choice == 1) {
        Node* tmp = new Node(input1[input1Start]);
        if (input1Start == input1End) {
            return tmp;
        }
        int index = input2Start;
        while (input2[index] != input1[input1Start + 1]) {
            index++;
        }
        int treeSize = index - input2Start + 1;

        tmp->set_left(buildTreeHelper(input1, input2, 1, input1Start + 1, input1Start + treeSize, input2Start, index));

        tmp->set_right(buildTreeHelper(input1, input2, 1, input1Start + 1 + treeSize, input1End, index + 1, input2End - 1));

        return tmp;
    }
    else if (choice == 2) {
        int rootValue = input2[input2End];
        int index = input1Start;
        while (input1[index] != rootValue) {
            index++;
        }
        int treeSize = input1End - index;

        Node* tmp = new Node(rootValue);

        tmp->set_left(buildTreeHelper(input1, input2, 2, input1Start, index - 1, input2Start, input2End - 1 - treeSize));

        tmp->set_right(buildTreeHelper(input1, input2, 2, index + 1, input1End, input2End - treeSize, input2End - 1));

        return tmp;
    }
    else {
        int rootValue = input2[input2Start];
        int index = input1Start;
        while (input1[index] != rootValue) {
            index++;
        }
        int treeSize = index - input1Start;

        Node* root = new Node(rootValue);

        root->set_left(buildTreeHelper(input1, input2, 3, input1Start, index - 1, input2Start + 1, input2Start + treeSize));

        root->set_right(buildTreeHelper(input1, input2, 3, index + 1, input1End, input2Start + treeSize + 1, input2End));

        return root;
    }
}
