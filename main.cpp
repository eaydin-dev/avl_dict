#include <iostream>
#include "Dictionary.h"

using namespace std;
int main() {

    Dictionary<int, int> dict;
    dict.insert(1, 1);
    dict.insert(4, 4);
    dict.insert(13, 13);
    dict.insert(5, 5);
    dict.insert(8, 8);
    dict.insert(21, 21);
    dict.insert(7, 7);

    cout << "AVL tree of a dictionary(key-value): " << endl;
    dict.display();
    cout << "---------------------------------" << endl << endl;

    int * result = dict.find(13);
    assert(*result == 13);
    cout << "dict.find(13) -> " << (*result) << endl;
    cout << "---------------------------------" << endl << endl;

    int beforeSize = dict.size();
    dict.remove(21);
    assert(dict.size() == (--beforeSize));
    cout << "Tree after dict.remove(21):" << endl;
    dict.display();
    cout << "---------------------------------" << endl << endl;

    dict.remove(5);
    assert(dict.size() == (--beforeSize));
    cout << "Tree after dict.remove(5):" << endl;
    dict.display();
    cout << "---------------------------------" << endl << endl;

    dict.remove(55);
    assert(dict.size() == beforeSize);
    cout << "Tree after dict.remove(55):" << endl;
    dict.display();
    cout << "---------------------------------" << endl << endl;

    dict.insert(1, 123);
    assert(beforeSize == dict.size());
    cout << "Before and after sizes of the dictionary for 'dict.insert(1, 123)' call: " << beforeSize << " and " << dict.size() << endl;
    cout << "---------------------------------" << endl << endl;

    Dictionary<int, int> copiedDict(dict);
    assert(dict.size() == copiedDict.size());
    assert(dict.height() == copiedDict.height());
    cout << "AVL tree of another dictionary that uses copy constructor with above dictionary: " << endl;
    cout << "(different insertion order may produce different tree (but same dictionary))" << endl;
    copiedDict.display();
    cout << "---------------------------------" << endl << endl;

    Dictionary<int, int> someDict;
    someDict = dict;
    assert(dict.size() == someDict.size());
    assert(dict.height() == someDict.height());
    cout << "AVL tree of another dictionary that uses assignment operator with above dictionary: " << endl;
    cout << "(different insertion order may produce different tree (but same dictionary))" << endl;
    someDict.display();
    cout << "---------------------------------" << endl << endl;

    cout << "In order traversal: ";
    dict.traverseInOrder();
    cout << endl;

    cout << "Pre order traversal: ";
    dict.traversePreOrder();
    cout << endl;

    cout << "Post order traversal: ";
    dict.traversePostOrder();
    cout << endl;

    return 0;
}