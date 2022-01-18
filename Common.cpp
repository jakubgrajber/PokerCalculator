//
//  Common.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 12/01/2022.
//

#include "Common.hpp"
using namespace::cmn;

void cmn::stageToDomain(Stage stage, int &start, int &stop){
    switch (stage) {
        case pocket:
            start = 0;
            stop = 1;
            break;
        case flop:
            start = 2;
            stop = 4;
            break;
        case turn:
            start = stop = 5;
            break;
        case river:
            start = stop = 6;
            break;
        default:
            break;
    }
}

void cmn::insertionSort(int (*arr)[2], int size, int comparingPosition){
    for(int i=1; i<size; i++){
        int j=i;
        int temp[2];
        temp[0]= arr[j][0];
        temp[1]= arr[j][1];
        
        while ((j>0) && (arr[j-1][comparingPosition]<temp[comparingPosition])){
            arr[j][0]=arr[j-1][0];
            arr[j][1]=arr[j-1][1];
            j--;
        }
        arr[j][0] = temp[0];
        arr[j][1] = temp[1];
    }
}
