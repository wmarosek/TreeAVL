//
// Created by wmarosek on 22.05.19.
//

#ifndef LAB3_TESTS_H
#define LAB3_TESTS_H

#include "Dictionary.h"

void result(bool correct);
void conclusion();
static int number = 0;
static int valid  = 0;

//Normal and reverse printing list!
void printingTest();
//Adding by AVL rules and randomly
void insertionTest();
//Deleting by given Key, all AVL tree
void deletingTest();
//Size testing
void sizeTest();
//Assigment operator test
void assigmentTest();
//Overloading operator test
void overloadingTest();
//Update method test
void updateTest();


/*  ================================================

                	    TESTS

    ================================================ */


void printingTest(){
    bool correct = true;
    std::cout << "\n\t ==== PRINTING TEST ====\n\n";

    Dictionary<int,int> dict;

    std::cout << "[*] Printing normal list\n";

    dict.randomNodes(8);
    dict.display();
    if(dict.size()!=8)
        correct = false;

    std::cout << "[*] Printing clear list\n";
    dict.destroy();
    dict.display();
    if(dict.size()!=0)
        correct = false;

    //result of the test
    result(correct);


}

void insertionTest(){
    bool correct = true;
    Dictionary<int,int>::Iterator it;
    Dictionary<int,int> dict;
    std::cout << "\n\t ==== INSERTION TEST ====\n\n";
    std::cout << "[*] Printing dictionary created by randomNodes\n";


    dict.randomNodes(20);
    dict.insert(101,1);
    if(dict.size()!=21 || dict.end().getKey() != 101){
        correct = false;
    }
    dict.display();

    dict.destroy();
    if(dict.size()!=0){
        correct = false;
    }
    dict.insert(1,1);
    dict.insert(5,1);
    dict.insert(3,1);
    dict.insert(2,1);
    dict.insert(9,1);
    dict.insert(5,1);
    dict.insert(11,1);
    dict.insert(0,1);
    if(dict.size()!=6 || dict.end().getKey() != 11 || dict.begin().getKey()!=0){
        correct = false;
    }
    for(it = dict.begin(); ++it != dict.end(); it++){
        if(it.getKey() >= (++it).getKey())
            correct = false;
    }
    std::cout << "[*] Printing dictionary created by insertion method\n";
    dict.display();
    result(correct);

}

void deletingTest(){
    bool correct = true;
    Dictionary<int,int>::Iterator it;
    Dictionary<int,int> dict;
    dict.destroy();
    std::cout << "\n\t ==== INSERTION TEST ====\n\n";

    dict.insert(1,1);
    dict.insert(5,1);
    dict.insert(3,1);
    dict.insert(2,1);
    dict.insert(9,1);
    dict.insert(11,1);
    dict.insert(0,1);

    if(dict.size()!=7 || dict.end().getKey() != 11 || dict.begin().getKey()!=0){
        correct = false;
    }

    std::cout << "[*] Printing base dictionary\n";
    dict.display();

    dict.insert(5,1);
    if(dict.size()!=6 || dict.end().getKey() != 11 || dict.begin().getKey()!=0){
        correct = false;
    }
    for(it = dict.begin(); ++it != dict.end(); it++){
        if(it.getKey() == 5)
            correct = false;
    }

    std::cout << "[*] Printing dictionary after inserting node with existing Key \n";
    dict.display();

    dict.removeByKey(3);
    dict.removeByKey(0);
    if(dict.size()!=4 || dict.end().getKey() != 11 || dict.begin().getKey()!=1){
        correct = false;
    }

    std::cout << "[*] Printing dictionary after removing root node and the smallest \n";
    dict.display();

    /*
     * Case with removing the last existing node , by method removeByKey ,which is using in special case in insertion method.
     * Also we are checking valid work of destroy
     */
    dict.destroy();
    dict.insert(1,1);
    if(dict.size()!=1)
        correct = false;
    dict.insert(1,1);
    if(dict.size()!=0)
        correct = false;
    dict.insert(2,1);
    if(dict.size()!=1)
        correct = false;

    result(correct);


}


void result(bool correct){
    number++;
    if (correct)
    {
        std::cout << "[***] THE TEST RAN CORRECTLY! [***]\n";
        valid++;
        return;
    }
    std::cerr << "[!!!] THE TEST RAN INCORRECTLY [!!!]\n";
}

void conclusion(){
    std::cout << "\n\n ==== Conclusion of tests ====\n";
    std::cout << "\n[***] Test: " << number << "\n[***] Correct: " << valid << std::endl;
}

#endif //LAB3_TESTS_H
