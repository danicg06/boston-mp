/*
 * Metodología de la Programación: Boston2
 * Curso 2024/2025
 */

/** 
 * @file   ArrayCrimeSetFunctions.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio
 */

#include <iostream>
#include "ArrayCrimeSetFunctions.h"

using namespace std;

void ReadArrayCrimeSet(std::istream &inputStream, CrimeSet * &arrayCrimeSet, 
        int & nCrimeSets) { 
    
    const string INVALID = "";
    
    
    do {
        
        string filename;
        getline(inputStream, filename);
        
        CrimeSet to_append;
        
        if (filename != INVALID) {
            to_append.load(filename);
            to_append.setComment("Fusion of the crm files whose names are in the file: " + filename);
            AppendCrimeArrayCrimeSet(arrayCrimeSet, nCrimeSets, to_append);
        }
        
    } while(inputStream);
}

void PrintArrayCrimeSet(CrimeSet * &arrayCrimeSet, int nCrimeSets) {
    for (int i = 0; i < nCrimeSets; i++)
        cout << arrayCrimeSet[i].toString();
}

CrimeSet * AllocateArrayCrimeSet(int nCrimeSets) {
    
    CrimeSet *array_crime_set = nullptr;
    
    if (nCrimeSets > 0)
        array_crime_set = new CrimeSet [nCrimeSets];
    
    return array_crime_set;
}

void DeallocateArrayCrimeSet(CrimeSet * &arrayCrimeSet) {
    delete [] arrayCrimeSet;
    arrayCrimeSet = nullptr;
}

void AppendCrimeArrayCrimeSet(CrimeSet * &arrayCrimeSet, int & nCrimeSets, 
        const CrimeSet & newCrimeSet) {
    CrimeSet *new_array = nullptr;
    new_array = AllocateArrayCrimeSet(nCrimeSets + 1);
    
    for (int i = 0; i < nCrimeSets; i++)
        new_array[i] = arrayCrimeSet[i];
    
    // Add the new element
    
    new_array[nCrimeSets++] = newCrimeSet;
    
    DeallocateArrayCrimeSet(arrayCrimeSet);
    arrayCrimeSet = new_array;
    
}