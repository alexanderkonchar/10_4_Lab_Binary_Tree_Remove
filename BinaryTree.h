//
// Created by Alex on 4/3/23.
//

#ifndef INC_10_4_LAB_BINARY_TREE_REMOVE_BINARYTREE_H
#define INC_10_4_LAB_BINARY_TREE_REMOVE_BINARYTREE_H

#include <iostream>
#include <memory>

using namespace std;

template<typename T>
struct Node {
    explicit Node(T data) : data(data), left(nullptr), right(nullptr) {}

    T data;
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;
};

template<typename T>
class BTree {
public:
    BTree() : root(nullptr) {}

    BTree(const BTree<T> &);

    BTree<T> &operator=(const BTree<T> &);

    void insert(const T &item);

    void remove(const T &item);

    // findRightMostNode() is a helper method used in the remove() function.  It should normally be a private method,
    // but leave it public for testing purposes.
    // Given a tree and a node, it will find the right most node of the branch from the given node
    shared_ptr<Node<T>> findRightMostNode(shared_ptr<Node<T>> ptr);

    // findParent() is a helper method used in the remove() function. It should normally be a private method,
    // but leave it public for testing purposes.
    // Given a tree and a node, it will find the right the parent of the given node
    shared_ptr<Node<T>> findParent(shared_ptr<Node<T>> ptr);

    void preOrder();

    void inOrder();

    void postOrder();

    int nodeCount();

    int leavesCount();

// The find method will be given a value, and it will return the node that contains that particular value
// You might need an extra method to help with the recursion on this one much like the traversals
    shared_ptr<Node<T>> find(const T &item);

private:
    void preOrder(shared_ptr<Node<T>> ptr);

    void inOrder(shared_ptr<Node<T>> ptr);

    void postOrder(shared_ptr<Node<T>> ptr);

    void insert(const T &item, shared_ptr<Node<T>> ptr);

    shared_ptr<Node<T>> find(const T &item, shared_ptr<Node<T>> ptr);

    shared_ptr<Node<T>> findParent(const T &data, shared_ptr<Node<T>> ptr);

    void remove(const T &item, shared_ptr<Node<T>> ptr);

    int nodeCount(shared_ptr<Node<T>> ptr);

    int leavesCount(shared_ptr<Node<T>> ptr);

    shared_ptr<Node<T>> copyNode(shared_ptr<Node<T>> ptr);

    shared_ptr<Node<T>> root;
};

template<typename T>
BTree<T>::BTree(const BTree<T> &b) {
    root = copyNode(b.root);
}

template<typename T>
BTree<T> &BTree<T>::operator=(const BTree<T> &) {
    return BTree(*this);
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::copyNode(shared_ptr<Node<T>> ptr) {
    if (!ptr) return nullptr;
    auto ptrCopy = make_shared<Node<T>>(ptr->data);
    ptrCopy->left = copyNode(ptr->left);
    ptrCopy->right = copyNode(ptr->right);
    return ptrCopy;
}

template<typename T>
void BTree<T>::insert(const T &item) {
    if (!root) root = make_shared<Node<T>>(item);
    else insert(item, root);
}

template<typename T>
void BTree<T>::insert(const T &item, shared_ptr<Node<T>> ptr) {
    if (item < ptr->data) {     // Left Branch
        if (!ptr->left) ptr->left = make_shared<Node<T>>(item);
        else insert(item, ptr->left);
    } else {                    // Right Branch
        if (!ptr->right) ptr->right = make_shared<Node<T>>(item);
        else insert(item, ptr->right);
    }
}

template<typename T>
void BTree<T>::remove(const T &item) {
    remove(item, root);
}

template<typename T>
void BTree<T>::remove(const T &item, shared_ptr<Node<T>> ptr) {
    if (!ptr) return;
    else if (item > ptr->data) remove(item, ptr->right);
    else if (item < ptr->data) remove(item, ptr->left);
    else {
        if (!ptr->left) ptr = ptr->right;
        else if (!ptr->left) ptr = ptr->left;
        else {
            ptr->data = findRightMostNode(ptr->left)->data;
            remove(ptr->data);
        }
    }

    if (ptr) {
        if (item == ptr->data) {
            if (!ptr->left) {
                auto parent = findParent(ptr);
                if (parent->left->data == item) {
                    parent->left = ptr->right;
                } else if (parent->right->data == item) {
                    parent->right = ptr->right;
                }
            } else if (!ptr->right) {
                auto parent = findParent(ptr);
                if (parent->left->data == item) {
                    parent->left = ptr->left;
                } else if (parent->right->data == item) {
                    parent->right = ptr->left;
                }
            } else {
                auto rightMostNode = findRightMostNode(ptr->left);
                ptr->data = rightMostNode->data;
                remove(rightMostNode->data, rightMostNode);
            }
        } else if (item < ptr->data) remove(item, ptr->left);
        else remove(item, ptr->right);
    }
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::find(const T &item) {
    return find(item, root);
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::find(const T &item, shared_ptr<Node<T>> ptr) {
    if (ptr) {
        if (item == ptr->data) return ptr;
        else if (item < ptr->data) return find(item, ptr->left);
        else return find(item, ptr->right);
    }
    return nullptr;
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::findRightMostNode(shared_ptr<Node<T>> ptr) {
    if (!ptr) return nullptr;
    else if (!ptr->right) return ptr;
    return findRightMostNode(ptr->right);
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::findParent(shared_ptr<Node<T>> ptr) {
    return findParent(ptr->data, root);
}

template<typename T>
shared_ptr<Node<T>> BTree<T>::findParent(const T &data, shared_ptr<Node<T>> ptr) {
    if (ptr) {
        if (ptr->left) {
            if (data == ptr->left->data) return ptr;
            else if (data < ptr->data) return findParent(data, ptr->left);
        }
        if (ptr->right) {
            if (data == ptr->right->data) return ptr;
            else return findParent(data, ptr->right);
        }
    }
    return nullptr;
}

template<typename T>
void BTree<T>::preOrder() {
    preOrder(root);
}

template<typename T>
void BTree<T>::preOrder(shared_ptr<Node<T>> ptr) {
    if (ptr) {
        cout << ptr->data << " ";
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

template<typename T>
void BTree<T>::inOrder() {
    inOrder(root);
}

template<typename T>
void BTree<T>::inOrder(shared_ptr<Node<T>> ptr) {
    if (ptr) {
        preOrder(ptr->left);
        cout << ptr->data << " ";
        preOrder(ptr->right);
    }
}

template<typename T>
void BTree<T>::postOrder() {
    postOrder(root);
}

template<typename T>
void BTree<T>::postOrder(shared_ptr<Node<T>> ptr) {
    if (ptr) {
        preOrder(ptr->left);
        preOrder(ptr->right);
        cout << ptr->data << " ";
    }
}

template<typename T>
int BTree<T>::nodeCount() {
    return nodeCount(root);
}

template<typename T>
int BTree<T>::nodeCount(shared_ptr<Node<T>> ptr) {
    if (ptr) {
        return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
    }
    return 0;
}

template<typename T>
int BTree<T>::leavesCount() {
    return leavesCount(root);
}

template<typename T>
int BTree<T>::leavesCount(shared_ptr<Node<T>> ptr) {
    if (!ptr) return 0;
    else if (!ptr->left && !ptr->right) return 1;
    return leavesCount(ptr->left) + leavesCount(ptr->right);
}

#endif //INC_10_4_LAB_BINARY_TREE_REMOVE_BINARYTREE_H
