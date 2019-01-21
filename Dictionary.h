

#ifndef AVL_DICT_DICTIONARY_H
#define AVL_DICT_DICTIONARY_H

#include <iostream>

using namespace std;

// A node for the AVL tree.
template <typename Key, typename Info>
struct Element {
    Key key;
    Info info;
    Element<Key, Info> * left;
    Element<Key, Info> * right;
    int height;
};

template <typename Key, typename Info>
class Dictionary {

public:
    Dictionary() = default;

    // Copy constructor, adds all nodes of other dictionary to this dictionary recursively.
    Dictionary(const Dictionary& other) {
        this->addRecursive(other.root);
    }

    // Deletes all nodes recursively.
    ~Dictionary() {
        this->freeAll(this->root);
    }

    // Cleans this dictionary and insert all nodes of other dictionary to this one.
    void operator=(const Dictionary& other) {
        this->freeAll(this->root);
        this->addRecursive(other.root);
    }

    int size() {
        return this->_size;
    }

    Info* find(const Key& key) {
        Element<Key, Info> * node = this->get(this->root, key);
        if (node == NULL)
            return NULL;
        return &node->info;
    }

    int height() {
        return this->height(this->root);
    }

    void insert(const Key& key, const Info& info) {
        this->root = this->insert(this->root, key, info);
    }

    void remove(const Key& key) {
        this->root = this->remove(this->root, key);
    }

    void display() {
        cout << "Size: " << this->size() << " Height: " << this->height() << endl << endl;
        this->display(this->root, this->root, 1);
        cout << endl;
    }

    void traverseInOrder() {
        this->inorder(this->root);
    }

    void traversePreOrder() {
        this->preorder(this->root);
    }

    void traversePostOrder() {
        this->postorder(this->root);
    }

private:
    Element<Key, Info> * root = NULL;
    int _size = 0;

    // To insert a tree structure completely, we need to reach bottom of the tree and insert upwards.
    void addRecursive(Element<Key, Info> * root) {
        if (root != NULL) {
            if (root->left != NULL || root->right != NULL) {    // go deep if this node has children.
                addRecursive(root->left);
                addRecursive(root->right);
            }
            this->insert(root->key, root->info);    // then insert this node.
        }
    }

    // Since we are using pointers, we should reach exactly each pointer. Go all the way down and delete upwards.
    void freeAll(Element<Key, Info> * root) {
        if (root != NULL) {
            if (root->left != NULL) {
                if (root->left->left != NULL || root->left->right != NULL) {
                    freeAll(root->left->left);
                    freeAll(root->left->right);
                }
                free(root->left);
            }

            if (root->right != NULL) {
                if (root->right->left != NULL || root->right->right != NULL) {
                    freeAll(root->right->left);
                    freeAll(root->right->right);
                }
                free(root->right);
            }

            free(root);
        }
    }

    // Height difference between two sub-trees. To be used in rotations.
    int diff(Element<Key, Info> *temp){
        int left_height = height(temp->left);
        int right_height = height(temp->right);
        int diff = left_height - right_height;
        return diff;
    }

    // Right-right rotation.
    Element<Key, Info> *rr_rotation(Element<Key, Info> *parent){
        Element<Key, Info> *temp;

        temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;

        // Since we are keeping each node's height in itself, we should update these heights after a rotation.
        parent->height = 1 + (height(parent->left) > height(parent->right) ? height(parent->left) : height(parent->right));
        temp->height = 1 + (height(temp->left) > height(temp->right) ? height(temp->left) : height(temp->right));

        return temp;
    }

    // Left-left rotation.
    Element<Key, Info> *ll_rotation(Element<Key, Info> *parent){
        Element<Key, Info> *temp;

        temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;

        // Since we are keeping each node's height in itself, we should update these heights after a rotation.
        parent->height = 1 + (height(parent->left) > height(parent->right) ? height(parent->left) : height(parent->right));
        temp->height = 1 + (height(temp->left) > height(temp->right) ? height(temp->left) : height(temp->right));

        return temp;
    }

    // Left-right rotation.
    Element<Key, Info> *lr_rotation(Element<Key, Info> *parent){
        Element<Key, Info> *temp;

        temp = parent->left;
        parent->left = rr_rotation (temp);

        return ll_rotation (parent);
    }

    // Right-left rotation.
    Element<Key, Info> *rl_rotation(Element<Key, Info> *parent){
        Element<Key, Info> *temp;

        temp = parent->right;
        parent->right = ll_rotation (temp);

        return rr_rotation (parent);
    }

    // Balance the tree.
    Element<Key, Info> *balance(Element<Key, Info> *temp) {
        int _diff = diff(temp);
        if (_diff > 1) {
            if (diff(temp->left) > 0) {
                temp = ll_rotation(temp);
            } else {
                temp = lr_rotation(temp);
            }
        } else if (_diff < -1) {
            if (diff(temp->right) > 0) {
                temp = rl_rotation(temp);
            } else {
                temp = rr_rotation(temp);
            }
        }
        return temp;
    }

    // Traverse inorder.
    void inorder(Element<Key, Info> *tree){
        if (tree == NULL)
            return;
        inorder (tree->left);
        cout << "(" << tree->key << "-" << tree->info << ")  ";
        inorder (tree->right);
    }

    // Traverse preorder.
    void preorder(Element<Key, Info> *tree){
        if (tree == NULL)
            return;
        cout << "(" << tree->key << "-" << tree->info << ")  ";
        preorder (tree->left);
        preorder (tree->right);
    }

    // Traverse postorder.
    void postorder(Element<Key, Info> *tree){
        if (tree == NULL)
            return;
        postorder(tree ->left);
        postorder(tree ->right);
        cout << "(" << tree->key << "-" << tree->info << ")  ";
    }

    // Display the tree
    void display(Element<Key, Info> *root, Element<Key, Info> *ptr, int level) {
        if (ptr!= NULL) {
            display(root, ptr->right, level + 1);
            if (ptr == root)
                cout << "\nRoot >> ";
            for (int i = 0; i < level && ptr != root; i++)
                cout << "        ";

            cout << "(" << ptr->key << "-" << ptr->info << ")" << endl;
            display(root, ptr->left, level + 1);
        }
    }

    // Recursively searches the tree.
    Element<Key, Info> * get(Element<Key, Info> * root, const Key& key) {
        if (root == NULL)
            return NULL;
        else if (root->key == key)
            return root;
        else if (root->key > key)
            return get(root->left, key);
        else
            return get(root->right, key);
    }

    // Insert element into tree.
    Element<Key, Info> * insert(Element<Key, Info> * root, const Key& key, const Info& info){
        if (root == NULL) { // if this node is null, we can add new entry here.
            root = new Element<Key, Info>;
            root->info = info;
            root->key = key;
            root->left = NULL;
            root->right = NULL;
            root->height = 1;
            this->_size++;
        } else if (key == root->key)    // if keys are equal, don't do anything.
            return root;
        else if (key < root->key)   // if key is lower, skip right and search in left.
            root->left = insert(root->left, key, info);
        else if (key >= root->key)  // if key is higher, skip left and search in right.
            root->right = insert(root->right, key, info);

        // the height of the root should be updated because we just added a child.
        root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));
        root = balance(root);
        return root;
    }

    // Gets the minimum (which is most-left node) of the given tree. To be used in remove function.
    Element<Key, Info> * getMinNode(Element<Key, Info> * root) {
        Element<Key, Info> * temp = root;
        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // Finds and removes an item from given tree.
    Element<Key, Info> * remove(Element<Key, Info> * root, const Key& key) {
        if (root != NULL) {
            if (root->key > key)    // search in left.
                root->left = remove(root->left, key);
            else if (root->key < key)   // search in right.
                root->right = remove(root->right, key);
            else {  // we found the item.
                if (root->left != NULL && root->right != NULL) {    // if we have 2 childs
                    Element<Key, Info> * min = this->getMinNode(root->right);   // find right sub-tree's minimum node (which is the minimum node that is grater than this node).
                    root->key = min->key;   // switch contents of min-node and root.
                    root->info = min->info;
                    root->right = remove(root->right, min->key);   // then remove the min-node in our right sub-tree.
                }
                else {
                    Element<Key, Info> * temp = root->left != NULL ? root->left : root->right;
                    if (temp != NULL)   // if we have a child.
                        *root = *temp;  // just copy the content.
                    else {  // if we dont have child, just remove.
                        temp = root;
                        root = NULL;
                    }

                    free(temp); // free the physical space.
                    this->_size--;
                }
            }

            if (root == NULL)
                return root;

            // height should be updated after a removal operation.
            root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));
            root = balance(root);

            return root;
        }

        return NULL;
    }

    int height(Element<Key, Info> * node){
        return node == NULL ? 0 : node->height;
    }
};

#endif //AVL_DICT_DICTIONARY_H
