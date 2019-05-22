//
// Created by wmarosek on 22.05.19.
//

#ifndef LAB3_DICTIONARY_H
#define LAB3_DICTIONARY_H

#include <time.h>
#include <typeinfo>

template<typename Key, typename Info>
class Dictionary {

    struct Node{
        Key key;
        Info info;

        Node* left = nullptr;
        Node* right = nullptr;

        int height;
        Node(Key key, Info info, int height) : key(key), info(info), height(height) {};

    };
    Node* root = nullptr;
    Node* newNode(const Key& k, const Info& i){
        Node* node = new Node(k,i,1);

        return node;
    }

    /* ==== PRIVATE METHOD OF CLASS ====
     * ====     AT LINE ...         ==== */

    void destroy(Node* n);
    Node* remove(const Key& k, Node* n);

    bool insert(const Key& k,const Info& i, Node* &n);

    void display(Node* n, int space);

    Node* findMax(Node* n);
    Node* findMin(Node* n);


    int getBalance(Node* n);
    int height(Node* n);

    /* ====     ROTATING METHOD     ====
     * ====     AT LINE ...         ==== */


    Node* rightRotate(Node* &n);
    Node* leftRotate(Node* &n);
    Node* doubleRightRotate(Node* &n);
    Node* doubleLeftRotate(Node* &n);

public:

    /* ==== CONSTRUCTORS, OPERATORSS ====
     * ====     AT LINE ...         ==== */

    Dictionary() = default;
    Dictionary(const Dictionary<Key,Info>& otherAVL) { *this = otherAVL; }
    ~Dictionary() { this->destroyTree(); }
    bool operator==(const Dictionary &rhs) const;
    bool operator!=(const Dictionary &rhs) const;


    /* ====       API METHODS       ====
     * ====     AT LINE ...         ==== */

    bool isEmpty() const;

    void insert(const Key &, const Info&);

    void display();
    void displayNode(const Key&);

    void destroyTree();
    void deleteNode(const Key&);

    int size();
    int height();

    /* ====      OTHERS METHODS       ====
     * ====     AT LINE ...         ==== */
    void randomNode(int);
    int max(int a,int b){
        return ((a > b) ? a : b);
    }

};



template<typename Key, typename Info>
void Dictionary<Key, Info>::destroy(Dictionary::Node *n) {
    if(n == nullptr)
        return;

    destroy(n->left);
    destroy(n->right);
    delete n;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::destroyTree() {
    destroy(root);
    root = nullptr;

}



/* ====   ====   ====   ====
 *      ROTATING METHOD
 * ====   ====   ====   ====*/


template<typename Key, typename Info>
typename Dictionary<Key,Info>::Node *Dictionary<Key, Info>::rightRotate(Dictionary::Node *&n) {
    Node* temp = n->left;
    Node* temp2 = temp->right;

    temp->right = n;
    n->left = temp2;

    n->height = max(height(n->left), height(n->right))+1;
    temp->height = max(height(temp->left), height(temp->right))+1;
    return temp;
}


template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::leftRotate(Dictionary::Node *&n) {
    Node* temp = n->right;
    Node* temp2 = temp->left;
    temp->left = n;
    n->right = temp2;

    n->height = max(height(n->left), height(n->right))+1;
    temp->height = max(height(temp->left), height(temp->right))+1;
    return temp;
}

template<typename Key, typename Info>
typename Dictionary<Key,Info>::Node *Dictionary<Key, Info>::doubleRightRotate(Dictionary::Node *&n) {
    n->left = singleLeftRotate(n->left);
    return singleRightRotate(n);
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::doubleLeftRotate(Dictionary::Node *&n) {
    n->right = singleRightRotate(n->right);
    return singleLeftRotate(n);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::height(Node* n) {
    return (n == nullptr ? 0 : n->height);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::getBalance(Dictionary::Node *n) {
    if(!n)
        return 0;

    return height(n->left)- height(n->right);
}

/* ====   ====   ====   ====
 *      DISPLAYING METHOD
 * ====   ====   ====   ====*/

template<typename Key, typename Info>
void Dictionary<Key, Info>::display(Node* n, int space) {

    if(!n) {
        return;
    }
    space += 10;

    display(n->right, space);

    std::cout << "\n";
    for(int i = 0; i<space; i++){
        std::cout << " ";
    }
    std::cout << n->key  << std::endl;

    display(n->left, space);

}

template<typename Key, typename Info>
void Dictionary<Key, Info>::display() {
    display(root,0);
}


/* ====   ====   ====   ====
 *      INSERTION METHODS
 * ====   ====   ====   ====*/
template<typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key &k, const Info &i) {
    this->insert(k,i,root);

}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::insert(const Key &k, const Info &i, Dictionary::Node* &n) {

    if(n == nullptr){
        n = this->newNode(k,i);
        return true;
    }

    if(k < n->key){
        this->insert(k,i,n->left);
    }
    else if(k > n->key){
       this->insert(k,i,n->right);
    }
    else{
        return false;
    }


    n->height = 1 + max(height(n->left), height(n->right));

    int balance = getBalance(n);
    if(balance>1 && k < n->left->key) {
        n = this->rightRotate(n);
        return true;

    }

    if(balance < -1 && k > n->right->key) {
        n = this->leftRotate(n);
        return true;
    }
    if(balance > 1 && k > n->left->key){
        n->left = this->leftRotate(n->left);
        n = this->rightRotate(n);
        return true;
    }
    if(balance < -1 && k > n->right->key){
        n->right = this->rightRotate(n->right);
        n = this->leftRotate(n);
        return true;
    }


    return false;
}

/* ====   ====   ====   ====
 *      BASIC METHOD
 * ====   ====   ====   ====*/
template<typename Key, typename Info>
bool Dictionary<Key, Info>::isEmpty() const {
    return (root == nullptr);
}

/* ====   ====   ====   ====
 *      OTHER METHOD
 * ====   ====   ====   ====*/

template<typename Key, typename Info>
void Dictionary<Key, Info>::randomNode(int number) {
    srand(time(nullptr));
    if (typeid(Key) == typeid(int) && typeid(Info) == typeid(int) && typeid(number) == typeid(int) && number > 0){
        for (int i = 0; i < number; i++){
            int randomKey = rand() % 30 + 1;
            int randomInfo = rand() % 30 + 1;
            this->insert(randomKey, randomInfo);
        }
        return;
    }

    std::cerr << "[!] Only postive number of node can be generate. Key has to be integer!\n";

}

#endif //LAB3_DICTIONARY_H
