#include <iostream>

template <typename T, int N>
class BTreeNode {
public:
    bool isLeaf;                 // True if the node is a leaf
    int numKeys;                 // Current number of keys in the node
    T keys[N];                   // Array to store keys
    BTreeNode* children[N + 1];  // Array of child pointers

    BTreeNode(bool leaf) : isLeaf(leaf), numKeys(0) {
        for (int i = 0; i < N + 1; ++i) {
            children[i] = nullptr;
        }
    }

    ~BTreeNode() {
        for (int i = 0; i <= numKeys; ++i) {
            delete children[i];
        }
    }
};

template <typename T, int N>
class BTree {
private:
    BTreeNode<T, N>* root;

    // Split the child at the given index after insertion
    void splitChild(BTreeNode<T, N>* parent, int index) {
        BTreeNode<T, N>* fullChild = parent->children[index];
        BTreeNode<T, N>* newChild = new BTreeNode<T, N>(fullChild->isLeaf);

        int mid = N / 2;

        // Move second half of keys to the new child
        for (int i = mid + 1, j = 0; i < N; ++i, ++j) {
            newChild->keys[j] = fullChild->keys[i];
        }
        newChild->numKeys = N - mid - 1;
        fullChild->numKeys = mid;

        // Move children of fullChild if it's not a leaf
        if (!fullChild->isLeaf) {
            for (int i = mid + 1, j = 0; i <= N; ++i, ++j) {
                newChild->children[j] = fullChild->children[i];
                fullChild->children[i] = nullptr;
            }
        }

        // Insert the middle key into the parent
        for (int i = parent->numKeys; i > index; --i) {
            parent->keys[i] = parent->keys[i - 1];
            parent->children[i + 1] = parent->children[i];
        }

        parent->keys[index] = fullChild->keys[mid];
        parent->children[index + 1] = newChild;
        parent->numKeys++;
    }

    // Insert a key into a node and split after insertion if needed
    void insertAndSplit(BTreeNode<T, N>* node, const T& key) {
        int i = node->numKeys - 1;

        if (node->isLeaf) {
            // Insert the key into the correct position
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                --i;
            }
            node->keys[i + 1] = key;
            node->numKeys++;
        } else {
            // Find the correct child to insert the key
            while (i >= 0 && node->keys[i] > key) {
                --i;
            }
            ++i;

            // Recursively insert into the correct child
            insertAndSplit(node->children[i], key);

            // Split the child if it exceeds the maximum size (N keys)
            if (node->children[i]->numKeys == N) {
                splitChild(node, i);
            }
        }
    }

    // Recursive print function to display the tree level-wise
    void print(BTreeNode<T, N>* node, int level = 0) const {
        if (!node) return;

        // Indentation for the current level
        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }

        // Print all keys in the current node
        for (int i = 0; i < node->numKeys; ++i) {
            std::cout << node->keys[i];
            if (i != node->numKeys - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;

        // Recursively print children if the node is not a leaf
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; ++i) {
                print(node->children[i], level + 1);
            }
        }
    }

public:
    BTree() : root(nullptr) {}

    ~BTree() {
        delete root;
    }

    // Insert a new key into the B-tree
    void insert(const T& key) {
        if (!root) {
            root = new BTreeNode<T, N>(true);
            root->keys[0] = key;
            root->numKeys = 1;
        } else {
            insertAndSplit(root, key);

            // If the root exceeds the maximum size, split it
            if (root->numKeys == N) {
                BTreeNode<T, N>* newRoot = new BTreeNode<T, N>(false);
                newRoot->children[0] = root;
                splitChild(newRoot, 0);
                root = newRoot;
            }
        }
    }

    void print() const {
        print(root);
    }
};
