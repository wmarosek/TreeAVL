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
    try {
        Dictionary<int, int>::Iterator it;
        Dictionary<int, int> dict;
        std::cout << "\n\t ==== INSERTION TEST ====\n\n";
        std::cout << "[*] Printing dictionary created by randomNodes\n";


        dict.randomNodes(30);
        dict.insert(101, 1);
        if (dict.size() != 31 || dict.end().getKey() != 101) {
            correct = false;
        }
        dict.display();

        dict.destroy();
        if (dict.size() != 0) {
            correct = false;
        }
        dict.insert(1, 1);
        dict.insert(5, 1);
        dict.insert(3, 1);
        dict.insert(2, 1);
        dict.insert(9, 1);
        dict.insert(5, 1);
        dict.insert(11, 1);
        dict.insert(0, 1);
        if (dict.size() != 6 || dict.end().getKey() != 11 || dict.begin().getKey() != 0) {
            correct = false;
        }

        for (it = dict.begin(); it != (dict.end()-1); it++) {
            if (it.getKey() >= (++it).getKey())
                correct = false;
        }
        std::cout << "[*] Printing dictionary created by insertion method\n";
        dict.display();
        std::cout << "[*] Printing information of node with key 0\n";

        dict.displayInfo(0);

    }
    catch (Dictionary<int, int>::InvalidKey x) {
        x.msg();
        correct = false;
    }
    catch (Dictionary<int, int>::InvalidInfo x) {
        x.msg();
        correct = false;
    }
    result(correct);

}

void deletingTest() {
    bool correct = true;
    try {
        Dictionary<int, int>::Iterator it;
        Dictionary<int, int> dict;
        dict.destroy();
        std::cout << "\n\t ==== DELETING TEST ====\n\n";

        dict.insert(1, 1);
        dict.insert(5, 1);
        dict.insert(3, 1);
        dict.insert(2, 1);
        dict.insert(9, 1);
        dict.insert(11, 1);
        dict.insert(0, 1);

        if (dict.size() != 7 || dict.end().getKey() != 11 || dict.begin().getKey() != 0) {
            correct = false;
        }

        std::cout << "[*] Printing base dictionary\n";
        dict.display();

        dict.insert(5, 1);
        if (dict.size() != 6 || dict.end().getKey() != 11 || dict.begin().getKey() != 0) {
            correct = false;
        }
        for (it = dict.begin(); it != dict.end(); it++) {
            if (it.getKey() == 5)
                correct = false;
        }
        if((++it) == dict.end() && dict.end().getKey() == 5)
            correct = false;

        std::cout << "[*] Printing dictionary after inserting node with existing Key \n";
        dict.display();

        dict.removeByKey(3);
        dict.removeByKey(0);
        if (dict.size() != 4 || dict.end().getKey() != 11 || dict.begin().getKey() != 1) {
            correct = false;
        }

        std::cout << "[*] Printing dictionary after removing root node and the smallest \n";
        dict.display();

        /*
         * Case with removing the last existing node , by method removeByKey ,which is using in special case in insertion method.
         * Also we are checking valid work of destroy
         */
        dict.destroy();
        dict.display();

        dict.insert(1, 1);
        if (dict.size() != 1)
            correct = false;
        dict.insert(1, 1);
        if (dict.size() != 0)
            correct = false;
        dict.insert(2, 1);
        if (dict.size() != 1)
            correct = false;
    }
    catch (Dictionary<int, int>::InvalidKey x) {
        x.msg();
        correct = false;
    }
    catch (Dictionary<int, int>::InvalidInfo x) {
        x.msg();
        correct = false;
    }
    result(correct);


}


void sizeTest() {
    bool correct = true;
    std::cout << "\n\t ==== Size of Dictionary TEST ====\n\n";
    Dictionary<int,int> d;
    if(d.size()!=0)
        correct = false;
    d.randomNodes(30);
    if(d.size()!=30)
        correct = false;
    std::cout << "Size of Dictionary is equal: " << d.size() << "\n\n";

    std::cout << "[*] Clearing whole dictionary\n\n";
    d.destroy();
    std::cout << "Size of Dictionary is equal: " << d.size() << "\n\n";

    if(d.size()!=0)
        correct = false;

    result(correct);
}


void assigmentTest() {

    bool correct = true;
    Dictionary<int,int> d,d2,d3;

    std::cout << "\n\t ==== Assigment operator TEST ====\n\n";
    d.randomNodes(20);
    d2 = d;
    if(d!=d2)
        correct = false;


    std::cout << "[*] Printing orginal dictionary\n";
    d.display();
    std::cout << "[*] Printing copied dictionary\n";

    d2.display();

    d2.insert(5,5);
    if(d==d2)
        correct = false;

    std::cout << "[*] Printing copied from empty dictionary\n";
    d2 = d3;

    if(d2.size()!=0)
        correct = false;
    d2.display();

    result(correct);

}

void updateTest() {

    bool correct = true;
    try {
        Dictionary<int, int> d, d2, d3;

        std::cout << "\n\t ==== Upadate  TEST ====\n\n";
        d.insert(1, 1);
        d.insert(5, 1);
        d.insert(3, 1);
        d.insert(2, 1);
        d.insert(9, 1);
        d.insert(11, 1);
        d.insert(0, 1);
        std::cout << "[*] Printing orginal dictionary\n";
        d.display();

        d.update(11, 11, 6);
        if (d.end().getInfo() != 6)
            correct = false;

        d.update(11, 21, 100);
        if (d.end().getKey() != 21 && d.end().getInfo() != 100)
            correct = false;

        std::cout << "[*] Printing upadated dictionary\n";
        d.display();

        d.destroy();
        d.update(3, 3, 3);
        if (d.size() != 0)
            correct = false;

    }
    catch (Dictionary<int,int>::InvalidKey x){
        x.msg();
        correct = false;
    }
    catch (Dictionary<int,int>::InvalidInfo x){
        x.msg();
        correct = false;
    }
    result(correct);


}

void iteratorTest(){
    bool correct = true;
    try {

        Dictionary<int, int>::Iterator it;
        Dictionary<int, int> dict;
        dict.destroy();
        std::cout << "\n\t ==== ITERATOR TEST ====\n\n";

        dict.insert(1, 1);
        dict.insert(5, 1);
        dict.insert(3, 1);
        dict.insert(2, 1);
        dict.insert(9, 1);
        dict.insert(11, 1);
        dict.insert(0, 1);

        if (dict.size() != 7 || dict.end().getKey() != 11 || dict.begin().getKey() != 0) {
            correct = false;
        }

        std::cout << "[*] Printing base dictionary\n";
        dict.display();
        it = dict.begin();
        std::cout << it.getKey() << ' ';
        do {
            it++;
            std::cout << it.getKey() << ' ';

        } while (it != dict.end());
        std::cout << "\n";
        if (it.getKey() != 11)
            correct = false;




    }
    catch (Dictionary<int,int>::InvalidKey x){
        x.msg();
        correct = false;
    }
    catch (Dictionary<int,int>::InvalidInfo x){
        x.msg();
        correct = false;
    }
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
