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

void insertionTest();






void insertionTest(){
    std::cout << "\n\t ==== INSERTION TEST ====\n\n";
    std::cout << "[*] Printing normal list\n";

    Dictionary<int,int> dict;
    dict.insert(50,1);
    dict.insert(51,1);
    dict.insert(31,1);
    dict.insert(11,1);
    dict.insert(12,1);
    dict.insert(251,1);

    dict.insert(48,1);
    dict.display();

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
