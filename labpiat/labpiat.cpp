#include <iostream>
#include <fstream>

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    TreeNode* insertNode(TreeNode* node, int key) {
        if (node == nullptr) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }

        return node;
    }

    int getHeight(const TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    void printInOrder(TreeNode* node, std::ostream& out) const {
        if (node) {
            printInOrder(node->left, out);
            out << node->key << " ";
            printInOrder(node->right, out);
        }
    }

    void printPreOrder(TreeNode* node, std::ostream& out) const {
        if (node) {
            out << node->key << " ";
            printPreOrder(node->left, out);
            printPreOrder(node->right, out);
        }
    }

    void printPostOrder(TreeNode* node, std::ostream& out) const {
        if (node) {
            printPostOrder(node->left, out);
            printPostOrder(node->right, out);
            out << node->key << " ";
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void insert(int key) {
        root = insertNode(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) const {
        TreeNode* current = root;
        while (current != nullptr) {
            if (key == current->key) {
                return true;
            }
            else if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return false;
    }

    void printInOrder(std::ostream& out) const {
        printInOrder(root, out);
        out << std::endl;
    }

    void printPreOrder(std::ostream& out) const {
        printPreOrder(root, out);
        out << std::endl;
    }

    void printPostOrder(std::ostream& out) const {
        printPostOrder(root, out);
        out << std::endl;
    }

    void findVerticesWithDifferentHeight(std::ostream& out) const {
        findVerticesWithDifferentHeight(root, out);
        out << std::endl;
    }

    TreeNode* getRoot() const {
        return root;
    }

private:
    void findVerticesWithDifferentHeight(TreeNode* node, std::ostream& out) const {
        if (node) {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);

            if (leftHeight != rightHeight) {
                out << "Key: " << node->key << ", Left Height: " << leftHeight << ", Right Height: " << rightHeight << std::endl;
            }

            findVerticesWithDifferentHeight(node->left, out);
            findVerticesWithDifferentHeight(node->right, out);
        }
    }
};

void printTreeStructure(const TreeNode* node, int level = 0) {
    if (node != nullptr) {
        printTreeStructure(node->right, level + 1);

        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }

        std::cout << node->key << std::endl;

        printTreeStructure(node->left, level + 1);
    }
}

int main() {
    const char* filePath = "C:\\Users\\Dell\\OneDrive\\Documents\\tree_data.txt.txt";
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return 1;
    }

    BinaryTree tree;

    // Read data from file and build the tree
    int value;
    while (inputFile >> value) {
        tree.insert(value);
    }

    inputFile.close();

    // Perform operations
    std::cout << "In-Order Traversal:" << std::endl;
    tree.printInOrder(std::cout);

    std::cout << "Pre-Order Traversal:" << std::endl;
    tree.printPreOrder(std::cout);

    std::cout << "Post-Order Traversal:" << std::endl;
    tree.printPostOrder(std::cout);

    std::cout << "Finding vertices with different subtree heights:" << std::endl;
    tree.findVerticesWithDifferentHeight(std::cout);

    std::cout << "Binary Tree Structure:" << std::endl;
    printTreeStructure(tree.getRoot());

    return 0;
}
