/*
 * Metodología de la Programación: Boston1
 * Curso 2024/2025
 */

/** 
 * @file   ArrayCrimesFunctions.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio  
 */

#include "ArrayCrimesFunctions.h"

using namespace std;

void InitializeArrayInts(int array[], int size) {
    for (int i=0; i<size; i++)
        array[i]=0;
}

void ComputeMaxPosArrayInts(int array[], int size, int & max, int & posMax) {
    // Set the first value as the max value.
    max = array[0];
    posMax = 0;
    
    // If there is another value greater than the real max, then, update
    // max with the new maximum.
    
    for (int pos = 1; pos < size ; pos++) {
        if (array[pos] > max) {
            max = array[pos];
            posMax = pos;
        }
    }
}

void PrintHistogramArrayCrimes(int dataField, int histogram[]) {
    const int LONG_WEEK=7;
    const int LONG_DAY=24;
    switch (dataField) {
        case 0: // days of the week
            for (int i=0; i<LONG_WEEK; i++)
                cout << endl << DateTime::dayName(i) << " " << histogram[i];
            
            break;
        case 1: // hours of the day
            for (int i=0; i<LONG_DAY; i++)
                cout << endl << i << " " << histogram[i];
            break;
    }
}

void PrintArrayCrimes(Crime crimes[], int nCrimes) {
    for (int i = 0; i < nCrimes; i++)
        cout << crimes[i].toString() << endl;
}

int PosMinArrayCrimes(Crime array[], int initialPos, int finalPos) {
    // Set the first value as the min value.
    Crime min = array[initialPos];
    int posMin = initialPos;
    
    // If there is another value smaller than the real min, then, update
    // min with the new minimum.
    
    for (int pos = initialPos + 1; pos <= finalPos ; pos++) {
        if (min.IsSmaller(array[pos])) {
            min = array[pos];
            posMin = pos;
        }
    }
    return posMin;
}

void SwapElementsArrayCrimes(Crime array[], int nElements, int first,
        int second) {
    if (first < nElements && first >= 0 && second < nElements && second >= 0) {
        Crime tmp = array[first];
        array[first] = array[second];
        array[second] = tmp;
    }
    else // given positions not valid
        throw std::out_of_range(
            std::string("void Crime::SwapElementsArrayCrimes(Crime array[],"
                        "int nElements, int first, int second) : ") +
                        "given positions are not valid.");
}

void SortArrayCrimes(Crime array[], int nElements) {
    for (int left = 0 ; left < nElements ; left++) {
        
        // Calculates the minimum between "left" and "nElements"-1
        
        Crime min = array[left]; // Minimum crime's value
        int pos_min = left; // Minimum crime's position
        
        pos_min = PosMinArrayCrimes(array, left, nElements - 1);
        min = array[pos_min];
        
        // Swap values in left and pos_min positions.
        SwapElementsArrayCrimes (array, nElements, left, pos_min);
    }
}

int FindCrimeInArrayCrimes(Crime array[], Crime crime,
        int initialPos, int finalPos) {
    bool is_found = false;
    int i = initialPos;
    
    while (i <= finalPos && !is_found) {
        if (array[i].getId() == crime.getId())
            is_found = true;
        else
            i++;
    }
    
    if (!is_found)
        i = -1;
    
    return i;
}

void ComputeHistogramArrayCrimes(Crime crimes[], int nCrimes,
        int dataField, int histogram[]) {
    
    const int MODE_WEEK  = 0;
    const int MODE_HOURS = 1;
    const int MAX_CAP    = 24;
    InitializeArrayInts(histogram, MAX_CAP);
    switch (dataField) {
        case MODE_WEEK: // days of the week
            for (int i = 0; i < nCrimes; i++)
                histogram[crimes[i].getDateTime().weekDay()]++;
            
            break;
        case MODE_HOURS: // hours of the day
            for (int i = 0; i < nCrimes; i++)
                histogram[crimes[i].getDateTime().hour()]++;
            break;
            
        default: // not valid data field
            throw std::out_of_range(
            std::string("void Crime::ComputeHistogramArrayCrimes(Crime crimes[],"
                        "int dataField, int histogram[]) : ") +
                        "histogram datField not valid.");
    }
}

void SelectWhereEQArrayCrimes(Crime inputCrimes[], int inputCrimesSize, 
    string  field, string value, Crime outputCrimes[], 
    int & outputCrimesSize) {
    
    outputCrimesSize = 0;
    for (int i = 0; i < inputCrimesSize; i++) {
        if (inputCrimes[i].getField(field) == value) {
            outputCrimes[outputCrimesSize] = inputCrimes[i];
            outputCrimesSize++;
        }
    }
}
