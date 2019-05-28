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
        Node* parent = nullptr;

        int height = 1;

    };
    Node* root = nullptr;
    int max(int a,int b){
        return ((a > b) ? a : b);
    }


    /* ==== PRIVATE METHOD OF CLASS ==== */

    bool insertHelper(const Key& k,const Info& i, Node* &n);

    void destroyHelper(Node* n);
    Node* removeHelper(const Key& k, Node* n);

    void displayHelper(Node* n, int space);

    Node* findMax(Node* n);
    Node* findMin(Node* n);
    Node* findByKey(Node*& n ,const Key& k);

    Node* copyDictionaryHelper(Node *n);
    bool compereHelper(Node* lhs, Node* rhs);

    int getBalance(Node* n);
    int getHeight(Node* n);
    int getSize(Node* n);
    int updateHeight(Node *&n);
    bool updateParent(Node *&n);
    void balanceTree(Node *&n);


    /* ====     ROTATING METHOD     ==== */


    void rRotate(Node* &n);
    void lRotate(Node* &n);
    void lrRotate(Node* &n);
    void rlRotate(Node* &n);

public:
    bool isEmpty() const;

    /* ==== CONSTRUCTORS, OPERATORSS ==== */

    Dictionary();
    Dictionary(const Dictionary<Key,Info>& otherAVL);
    ~Dictionary();

    Dictionary& operator=(const Dictionary<Key,Info>& other);
    bool operator==(const Dictionary &rhs);
    bool operator!=(const Dictionary &rhs);



    void copyDictionary(const Dictionary<Key,Info>& otherAVL);



    void insert(const Key &, const Info&);

    void display();
    void displayInfo(const Key&);

    void destroy();
    void removeByKey(const Key&);

    bool findByKey(const Key&);

    void update(const Key& old, const Key& newKey, const Info &i);
    int size();


    /* ====      OTHERS METHODS       ====*/
    void randomNodes(int);

    /* ====         ITERATOR        ==== */
    class Iterator {
    private:
        friend class Dictionary;
        Node *iter;
    public:
        Iterator():iter(nullptr) {}
        Iterator(Node* node):iter(node) {}
        Iterator(const Iterator& src) : iter(src.iter) {}
        ~Iterator() = default;
        Iterator& operator=(const Iterator& other);


        Iterator& operator++();
        Iterator operator++(int);
        Iterator operator+(int r);

        Iterator& operator--();
        Iterator operator--(int);
        Iterator operator-(int r);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

        Key& getKey();
        Info& getInfo();

    };
    Iterator begin();
    Iterator end();


    /* ====       Exceptions        ==== */
    class InvalidKey {
    public:
        void msg(){
            std::cout << "Invalid Key of Dictionary" << std::endl;
        }
    };
    class InvalidInfo {
    public:
        void msg(){
            std::cout << "Invalid Info of Dictionary" << std::endl;
        }
    };
};



/* ====   ====   ====   ====
 *      CONSTRUCTORS
 * ====   ====   ====   ====*/


template<typename Key, typename Info>
Dictionary<Key, Info>::Dictionary() {
    root = nullptr;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary() {
    destroy();
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::operator==(const Dictionary &rhs)  {
    return (this->compereHelper(this->root, rhs.root));
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::operator!=(const Dictionary &rhs)  {
    return !(this->compereHelper(this->root, rhs.root));
}

/* ====   ====   ====   ====
 *      BASIC METHOD
 * ====   ====   ====   ====*/


template<typename Key, typename Info>
bool Dictionary<Key, Info>::isEmpty() const {
    return (root == nullptr);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::getHeight(Dictionary<Key, Info>::Node *n) {
    return (n == nullptr ? 0 : n->height);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::updateHeight(Dictionary::Node *&n) {
    if(!n)
        return 0;
    else
        n->height =  1 + max(getHeight(n->left), getHeight(n->right));

    updateHeight(n->left);
    updateHeight(n->right);
    return n->height;
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::getBalance(Dictionary::Node *n) {
    return getHeight(n->left)- getHeight(n->right);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::balanceTree(Dictionary::Node *&n) {
    int balance = getBalance(n);
    if(balance >1) {
        if(n->left){
            if(getBalance(n->left)>=0)
                rRotate(n);
            else
                lrRotate(n);
        }
    }
    else if(balance < -1){
        if(n->right){
            if(getBalance(n->right) > 0)
                rlRotate(n);
            else
                lRotate(n);
        }
    }
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::getSize(Dictionary::Node *n) {
    if(!n)
        return 0;
    return 1 + getSize(n->left) + getSize(n->right);
}

template<typename Key, typename Info>
int Dictionary<Key, Info>::size() {
    if(root)
        return getSize(root);
    return 0;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::compereHelper(Dictionary::Node *lhs, Dictionary::Node *rhs) {
    if(lhs == rhs)
        return true;
    else if(!rhs || !lhs)
        return false;
    bool result = (lhs->key == rhs->key && lhs->info == rhs->info);
    return result && compereHelper(lhs->right, rhs->right) && compereHelper(lhs->left, rhs->left) ;
}

/* ====   ====   ====   ====
 *      COPYING METHOD
 * ====   ====   ====   ====*/

template<typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(const Dictionary<Key, Info> &otherAVL) {
    this->copyDictionary(otherAVL);
}

template<typename Key, typename Info>
Dictionary<Key, Info> &Dictionary<Key, Info>::operator=(const Dictionary<Key, Info> &other) {
    this->copyDictionary(other);
    return *this;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::copyDictionary(const Dictionary<Key, Info> &otherAVL){
    if(!isEmpty())
        destroy();
    if(*this == otherAVL)
        return;

    if(otherAVL.isEmpty())
        destroy();
    else{
        this->root = copyDictionaryHelper(otherAVL.root);
    }
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::copyDictionaryHelper(Dictionary<Key, Info>::Node *n){
    if(!n)
        return nullptr;

    Node *curr = new Node;
    curr->key = n->key;
    curr->info = n->info;
    curr->height = n->height;
    curr->parent = n->parent;

    curr->right = copyDictionaryHelper(n->right);
    curr->left = copyDictionaryHelper(n->left);
    return curr;
}





/* ====   ====   ====   ====
 *      ROTATING METHOD
 * ====   ====   ====   ====*/


template<typename Key, typename Info>
void Dictionary<Key, Info>::rRotate(Dictionary<Key, Info>::Node *&n){
    if(!n || !n->left)
        return;

    Node* temp = n->left;
    n->left = temp->right;

    temp->right = n;
    n = temp;

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

}


template<typename Key, typename Info>
void Dictionary<Key, Info>::lRotate(Dictionary::Node *&n) {
    if(!n || !n->right)
        return;

    Node* temp = n->right;
    n->right = temp->left;

    temp->left = n;
    n = temp;

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::lrRotate(Dictionary<Key, Info>::Node *&n) {
    Node* temp = n->left;
    lRotate(temp);
    n->left = temp;
    rRotate(n);

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::rlRotate(Dictionary<Key, Info>::Node *&n) {
    Node* temp = n->right;
    rRotate(temp);
    n->right = temp;
    lRotate(n);

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
}





/* ====   ====   ====   ====
 *      DISPLAYING METHOD
 * ====   ====   ====   ====*/

template<typename Key, typename Info>
void Dictionary<Key, Info>::displayHelper(Node* n, int space) {

    if(!n) {
        return;
    }
    space += 10;

    displayHelper(n->right, space);

    std::cout << "\n";
    for(int i = 0; i<space; i++){
        std::cout << " ";
    }
    if(n->parent)
        std::cout << n->key << "(" << getBalance(n) << " | " << n->height << " | " << n->parent->key << ')'  << std::endl;
    else
        std::cout << n->key << "(" << getBalance(n) << " | " << n->height << ')'  << std::endl;

    displayHelper(n->left, space);

}

template<typename Key, typename Info>
void Dictionary<Key, Info>::display() {
    if(isEmpty()){
        std::cerr << "\n[!] The dictionary is empty\n" << std::endl;
        return;
    }
    std::cout << "\n ==== Dictionary aka AVL Tree =====\n\n";

    displayHelper(root,0);
    std::cout << "\n\n\n\n\n";
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::displayInfo(const Key &k) {
    Node* temp = findByKey(root, k);
    if(temp)
        std::cout << "\nKey: "<< temp->key << "\nInfo: "<< temp->info  << "\nBalance: " << getBalance(temp) << "\nHeight: " << temp->height << "\nParent key: " << temp->parent->key << std::endl;
    std::cerr << "[!] Dictionary doesn't have Node with " << k << "\n";

}


/* ====   ====   ====   ====
 *      INSERTION METHODS
 * ====   ====   ====   ====*/
template<typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key &k, const Info &i) {
    this->insertHelper(k,i,root);

}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::insertHelper(const Key &k, const Info &i, Dictionary<Key, Info>::Node *&n){

    if(!n){
        Node* newNode = new Node;
        newNode->key = k;
        newNode->info = i;
        n = newNode;

        return true;
    }
    else if(k < n->key){
        this->insertHelper(k,i,n->left);
    }
    else if(k > n->key){
       this->insertHelper(k,i,n->right);
    }
    else{
        this->removeByKey(k);
        return true;
    }

    updateHeight(n);
    balanceTree(n);
    updateHeight(root);
    updateParent(root);

    return true;

}

/* ====   ====   ====   ====
 *      UPDATING METHODS
 * ====   ====   ====   ====*/
template<typename Key, typename Info>
void Dictionary<Key, Info>::update(const Key &old, const Key &newKey, const Info &i) {
    if(findByKey(old)){
        removeByKey(old);
        insert(newKey,i);
        return;

    }
    std::cerr << "[!] Dictionary doesn't have Node with " << old << "\n";

}

/* ====   ====   ====   ====
 *      REMOVING METHOD
 * ====   ====   ====   ====*/

template<typename Key, typename Info>
void Dictionary<Key, Info>::destroyHelper(Dictionary::Node *n) {
    if(n == nullptr)
        return;

    destroyHelper(n->left);
    destroyHelper(n->right);
    delete n;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::destroy() {
    destroyHelper(root);
    root = nullptr;

}

template<typename Key, typename Info>
typename Dictionary<Key,Info>::Node *Dictionary<Key, Info>::removeHelper(const Key &k, Dictionary::Node *n) {
    if(!n)
        return nullptr;
    if(k < n->key)
        n->left = removeHelper(k, n->left);
    else if(k > n->key)
        n->right = removeHelper(k, n->right);
    else{
        if(!n->left && !n->right){
            if(n == root){
                root = nullptr;

            }
            delete n;
            n = nullptr;
        }
        else if(!n->left){
            Node* temp = n->right;
            delete n;
            n = temp;
        }
        else if(!n->right){
            Node* temp = n->left;
            delete n;
            n = temp;
        }
        else{
            Node* temp = findMin(n->right);
            n->key = temp->key;
            n->info = temp->info;
            n->right = removeHelper(temp->key, n->right);
        }
    }
    if(!n)
        return n;

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    balanceTree(n);
    return n;
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::removeByKey(const Key &k) {
    if(!root)
        return;

    removeHelper(k, root);
    updateHeight(root);
    updateParent(root);
}

/* ====   ====   ====   ====
 *      FINDING METHOD
 * ====   ====   ====   ====*/
template<typename Key, typename Info>
typename  Dictionary<Key, Info>::Node *Dictionary<Key, Info>::findMax(Dictionary::Node *n) {
    Node* curr = n;
    while(curr->right){
        curr = curr->right;
    }

    return curr;
}
template<typename Key, typename Info>
typename  Dictionary<Key, Info>::Node *Dictionary<Key, Info>::findMin(Dictionary<Key, Info>::Node *n){
    Node* curr = n;
    while(curr->left){
        curr = curr->left;
    }

    return curr;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::findByKey(Dictionary::Node *&n, const Key &k) {
    if(!n)
        return nullptr;
     if(n->key == k)
         return n;
     else if(k < n->key)
         return findByKey(n->left, k);
     else
         return findByKey(n->right,k);

}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::findByKey(const Key &k) {
    Node* temp = findByKey(root, k);
    return (temp != nullptr);
}

/* ====   ====   ====   ====
 *      OTHER METHOD
 * ====   ====   ====   ====*/

template<typename Key, typename Info>
void Dictionary<Key, Info>::randomNodes(int number) {
    srand(time(nullptr));
    if (typeid(Key) == typeid(int) && typeid(Info) == typeid(int) && typeid(number) == typeid(int) && number > 0){
        while(size() < number){
            int randomKey = rand() % 30 + 1;
            int randomInfo = rand() % 30 + 1;
//            std::cout << randomKey << std::endl;
            if(!findByKey(randomKey))
                this->insert(randomKey, randomInfo);
        }
        return;
    }

    std::cerr << "[!] Only postive number of node can be generate. Key has to be integer!\n";

}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::updateParent(Dictionary::Node *&n) {
    if(!n){
        return true;
    }
    if(n->right){
        n->right->parent = n;
        updateParent(n->right);
    }
    if(n->left){
        n->left->parent = n;
        updateParent(n->left);
    }
    if(!n->right && !n->left){
        return true;
    }
    if(n == root){
        n->parent = nullptr;
    }



    return true;
}


/* ====   ====   ====   ====
 *      ITERATOR METHOD
 * ====   ====   ====   ====*/
template<typename Key, typename Info>
typename Dictionary<Key,Info>::Iterator Dictionary<Key, Info>::begin() {
    return findMin(root);
}

template<typename Key, typename Info>
typename Dictionary<Key,Info>::Iterator Dictionary<Key, Info>::end() {
    return findMax(root);
}

template<typename Key, typename Info>
Key &Dictionary<Key, Info>::Iterator::getKey() {
    if(iter)
        return iter->key;
    throw InvalidKey();

}

template<typename Key, typename Info>
Info &Dictionary<Key, Info>::Iterator::getInfo() {
    if(iter)
        return iter->info;
    throw InvalidInfo();
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator &Dictionary<Key, Info>::Iterator::operator++() {
    if(iter->right){
        iter = iter->right;
        while(iter->left){
            iter = iter->left;
        }
    }
    else{
        Node* temp = iter->parent;
        while(temp && iter==temp->right){
            iter =temp;
            temp = temp->parent;
        }
        iter = temp;

    }
    return *this;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator Dictionary<Key, Info>::Iterator::operator++(int) {
    Iterator temp(*this);
    ++(*this);
    return temp;
}

template<typename Key, typename Info>
typename Dictionary<Key,Info>::Iterator Dictionary<Key, Info>::Iterator::operator+(int r) {
    Iterator temp(this->iter);
    while( temp.iter != nullptr && r>0){
        temp++;
        r--;
    }
    return temp;
}


template<typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator& Dictionary<Key, Info>::Iterator::operator--() {
    if(iter->left){
        iter = iter->left;
        while(iter->right){
            iter = iter->right;
        }
    }
    else{
        Node* temp = iter->parent;
        while(temp->left == iter){
            iter = temp;
            iter = iter->parent;
        }
        if(temp->right == iter)
            iter = temp;
    }

    return *this;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator Dictionary<Key, Info>::Iterator::operator--(int) {
    Iterator temp(*this);
    --(*this);
    return temp;
}

template<typename Key, typename Info>
typename Dictionary<Key,Info>::Iterator Dictionary<Key, Info>::Iterator::operator-(int r) {
    Iterator temp(this->iter);
    while( temp.iter != nullptr && r>0){
        temp--;
        r--;
    }
    return temp;
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator &Dictionary<Key, Info>::Iterator::operator=(const Dictionary::Iterator &other) {
    this->iter = other.iter;
    return *this;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::operator==(const Dictionary::Iterator &other) const {
    return this->iter == other.iter;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::operator!=(const Dictionary::Iterator &other) const {
    return this->iter != other.iter;
}

#endif //LAB3_DICTIONARY_H
