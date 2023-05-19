#include <iostream>
#include <string>
#include <memory>
#include "BinaryTree.h"

using namespace std;

bool checkTest(const string &testName, bool condition);

bool checkTest(const string &testName, int whatItShouldBe, int whatItIs);

void testFindMethod(BTree<int>);

void testRightMostNodeSearch(BTree<int>);

void testFindParent(BTree<int>);

void deleteTest(BTree<int>);

BTree<int> populateTree();

int main() {

    BTree<int> myTree = populateTree();

    testFindMethod(myTree);
    testRightMostNodeSearch(myTree);
    testFindParent(myTree);
    deleteTest(myTree);
    system("pause");
    return 0;
}


BTree<int> populateTree() {
    BTree<int> myTree;
    int values[] = {37, 32, 73, 95, 42, 12, 0, 49, 98, 7, 27, 17, 47, 87, 77, 97, 67, 85, 15, 5, 35, 55, 65, 75, 25, 45,
                    3, 93, 83, 53, 63, 23, 13, 43, 33};
    int size = (sizeof(values) / sizeof(*values));

    for (int i = 0; i < size; i++) {
        myTree.insert(values[i]);
    }

    myTree.inOrder();
    cout << endl;

    return myTree;
}

void testFindMethod(BTree<int> myTree) {
    auto ptr = myTree.find(49);
    checkTest("Test 1: Find(49)", 49, ptr->data);
    ptr = myTree.find(200);
    checkTest("Test 2: Find(200)", ptr == nullptr);
}

void testRightMostNodeSearch(BTree<int> myTree) {
    auto ptr = myTree.find(49);
    auto ptrchild = myTree.findRightMostNode(ptr);

    checkTest("Test 3: RightNodeTest(49)", 67, ptrchild->data);
}

void testFindParent(BTree<int> myTree) {
    auto child1 = myTree.find(25);
    auto ptr1 = myTree.findParent(child1);
    checkTest("Test 4: Find parent Right", 17, ptr1->data);
    auto child2 = myTree.find(15);
    auto ptr2 = myTree.findParent(child2);
    checkTest("Test 5: Find parent Left", 17, ptr2->data);
}

void deleteTest(BTree<int> myTree) {
    myTree.remove(13);
    auto ptr = myTree.find(13);
    if (!checkTest("Test 5: Delete Leaf: 13", ptr == nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    myTree.remove(67);
    ptr = myTree.find(67);
    if (!checkTest("Test 6: Delete Node with Left Child: 67", ptr == nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    ptr = myTree.find(55);
    if (!checkTest("Test 7: Rest of tree still in tact", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }
    myTree.remove(42);
    ptr = myTree.find(42);
    if (!checkTest("Test 8: Delete Node with Right Child: 42", ptr == nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    ptr = myTree.find(55);
    if (!checkTest("Test 9: Rest of tree still in tact", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    myTree.remove(73);
    ptr = myTree.find(73);
    if (!checkTest("Test 10 Delete Node with two children: 73", ptr == nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    ptr = myTree.find(49);
    if (!checkTest("Test 11: Rest of left tree still in tact", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    ptr = myTree.find(95);
    if (!checkTest("Test 12: Rest of right tree still in tact", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    ptr = myTree.find(63);
    if (!checkTest("Test 13: Right most child still in tact", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    myTree.remove(37);
    ptr = myTree.find(37);
    if (!checkTest("Test 14 Delete root: 37", ptr == nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }

    ptr = myTree.find(32);
    if (!checkTest("Test 15 Left Children still present", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }
    ptr = myTree.find(95);
    if (!checkTest("Test 16 Right Children still present", ptr != nullptr)) {
        cout << "In Order: ";
        myTree.inOrder();
        cout << endl;
    }
}

//Helps with Testing
bool checkTest(const string &testName, int whatItShouldBe, int whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl
             << "   Output should have been " << whatItShouldBe << endl;
        return false;
    }
}

//Helps with Testing
bool checkTest(const string &testName, bool condition) {

    if (condition) {
        cout << "Passed " << testName << endl;
        return true;
    } else {
        cout << "***Failed test " << testName << " *** " << endl;
        return false;
    }

}
