/*
 * Metodología de la Programación: Boston2
 * Curso 2024/2025
 */

/** 
 * @file   CrimeSet.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio
 */

#include <iostream>
#include <string>
#include <fstream>

#include "CrimeSet.h"

using namespace std;

const std::string CrimeSet::MAGIC_STRING_T="MP-CRIME-T-1.0";

string FormatAsComment(const string &comment, char commentCharacter){
    size_t start = 0, end;
    string formatedComment;
    if (comment.size() > 0) { // If comment has at least one character
        while ((end = comment.find('\n', start)) != std::string::npos) {
            formatedComment += commentCharacter + comment.substr(start, end - start) + "\n";
            start = end + 1;
        }
        if(start<comment.size()){ // This happens when last line of comment does not have \n
            formatedComment += commentCharacter + comment.substr(start, comment.size() - start) + "\n";
        }
    }
    return formatedComment;
}

CrimeSet::CrimeSet()
    :_nCrimes(0) {}

int CrimeSet::getSize() const {
    return _nCrimes;
}

int CrimeSet::getCapacity() const {
    return DIM_VECTOR_CRIMES;
}

std::string CrimeSet::getComment() const {
    return _comment;
}

void CrimeSet::setComment(const std::string &text) {
    
    const char NEWLINE = '\n';
    
    int i = text.length() - 1;
    
    if (i >= 0){
        if (text.at(i) == NEWLINE)
            _comment = text;
        else
            _comment = text.append(1,NEWLINE);
    }
    else
        _comment = text;
}

std::string CrimeSet::toString() const {
    
    string result = to_string(_nCrimes)+ "\n";
    
    for (int i=0; i < _nCrimes; i++) {
        
        result += _crimes[i].toString() + "\n";
    }
    
    return result;
}

void CrimeSet::clear() {
    _nCrimes = 0;
    _comment.clear();
}

bool CrimeSet::append(const Crime &crime) {
    
    bool isAppended = false;
    
    bool isFound = false;
    int i=0;

    while (i < _nCrimes && !isFound) {

        if (crime.IsSameCrime(_crimes[i]))
            isFound = true;
        else
            i++;
    }

    if (!isFound) {
        
        if (_nCrimes == DIM_VECTOR_CRIMES)
        throw std::out_of_range(
            std::string("void CrimeSet::append(Crime crime) : ") +
            "the array of Crimes is full of capacity");
        
        _crimes[_nCrimes] = crime;
        _nCrimes++;

        isAppended = true;
    }
    
    return isAppended;
}

Crime &CrimeSet::at(int pos) {
    
    if (pos < 0 || pos >= _nCrimes)
        throw std::out_of_range(
            std::string("void CrimeSet::at(int pos) : ") +
            "position is not valid");
           
    return (_crimes[pos]);
}

const Crime &CrimeSet::at(int pos) const {

    if (pos < 0 || pos >= _nCrimes)
        throw std::out_of_range(
            std::string("void CrimeSet::at(int pos) : ") +
            "position is not valid");
           
    return (_crimes[pos]);
}


int CrimeSet::findCrime(const Crime & crime, int initialPos, int finalPos) const {
    
    bool isFound = false;
    int i = initialPos;
    
    while (i <= finalPos && !isFound) {
        
        if (_crimes[i].getId() == crime.getId())
            isFound = true;
        else
            i++;
        
    } 
    int result = -1;
    
    if (isFound)
        result = i;
    
    return result;
}

int CrimeSet::findCrime(const Crime & crime) const {
    
    int pos = findCrime(crime, 0, _nCrimes-1);
    return (pos);
}

void CrimeSet::load(const std::string &fileName){
    
    clear();
    string str_crime;
    ifstream file(fileName);
    if (file) {
        getline(file, str_crime);
        
        if (str_crime == MAGIC_STRING_T) {
            readComments(file);
            getline(file, str_crime); // number of crimes
            int n = stoi(str_crime);
            _nCrimes = 0;
            if (n >= 0) {
                for (int i=0; i < n && _nCrimes < DIM_VECTOR_CRIMES; i++) {
                    getline(file, str_crime);
                    if (!file){
                        throw std::ios_base::failure(
                            std::string("void CrimeSet::load(string fileName) : ") +
                            "file cannot be opened or an error has occured");
                    }
                    else{
                        append(Crime(str_crime));
                    }
                }

                
            }
            else
                throw std::out_of_range(
                        std::string("void CrimeSet::load(string fileName) : ") +
                        "the given number of crimes is negative)");
        }
        else
            throw std::invalid_argument(
                        std::string("void CrimeSet::load(string fileName) : ") +
                        "the given magic string is invalid)");
            
    }
    else 
        throw std::ios_base::failure(
                        std::string("void CrimeSet::load(string fileName) : ") +
                        "file cannot be opened or an error has occured");
    file.close();
}

void CrimeSet::save(const std::string & fileName) {
    
    ofstream file(fileName);
    if (file) {
        
        file << MAGIC_STRING_T << "\n";
        saveComments(file);
        file << _nCrimes << "\n";
        
        for (int i=0; i < _nCrimes; i++) {
            
            file << _crimes[i].toString() << "\n";
            if (!file)
                throw std::ios_base::failure(
                        std::string("void CrimeSet::save(string fileName) : ") +
                        "file cannot be opened or an error has occured");
        }
        
        
    }
    else 
        throw std::ios_base::failure(
                        std::string("void CrimeSet::save(string fileName) : ") +
                        "file cannot be opened or an error has occured");
    
    file.close();
}

void CrimeSet::join(const CrimeSet & crimeSet) {
    
    for (int i=0; i < crimeSet._nCrimes; i++) {
        
        if (findCrime(crimeSet._crimes[i]) == -1) {
            _comment = crimeSet._comment;
            append(crimeSet._crimes[i]);
        }
        
    }
    
}

void CrimeSet::normalize() {
    for (int i=0; i < _nCrimes; i++)
        _crimes[i].normalize();
}

void CrimeSet::computeHistogram(int dataField, int histogram[]) {
    const int MODE_WEEK  = 0;
    const int MODE_HOURS = 1;
    const int MAX_CAP    = 24;
    
    InitializeArrayInts(histogram, MAX_CAP);
    
    switch (dataField) {
        case MODE_WEEK: // days of the week
            for (int i = 0; i < _nCrimes; i++)
                histogram[_crimes[i].getDateTime().weekDay()]++;
            
            break;
        case MODE_HOURS: // hours of the day
            for (int i = 0; i < _nCrimes; i++)
                histogram[_crimes[i].getDateTime().hour()]++;
            break;
            
        default: // not valid data field
            throw std::out_of_range(
            std::string("void Crime::ComputeHistogramArrayCrimes(Crime crimes[],"
                        "int dataField, int histogram[]) : ") +
                        "histogram datField not valid.");
    }
}

CrimeSet CrimeSet::selectWhereEQ(const std::string &field, const std::string &value) const {
    
    CrimeSet crimeset;
    for (int i = 0; i < _nCrimes; i++) {
        if (_crimes[i].getField(field) == value) {
            crimeset.append(_crimes[i]);
        }
    }
    
    return crimeset;
}

CrimeSet CrimeSet::selectValidLocation() const {
    const string APPEND_COMMENT = "Restricted to valid Coordinates";
    
    CrimeSet crimeset;
    crimeset._comment = _comment;
    for (int i=0; i<_nCrimes ; i++) {
        
        if (_crimes[i].getLocation().isValid()) 
            crimeset.append(_crimes[i]);
    }
    crimeset._comment.append(APPEND_COMMENT + "\n");

    
    return crimeset;
}

void CrimeSet::sort() {
    
    for (int left = 0 ; left < _nCrimes ; left++) {
        
        // Calculates the minimum between "left" and "_nCrimes"-1
        
        Crime min = _crimes[left]; // Minimum crime's value
        int pos_min = left; // Minimum crime's position
        
        pos_min = PosMinArrayCrimes(_crimes, left, _nCrimes - 1);
        min = _crimes[pos_min];
        
        // Swap values in left and pos_min positions.
        SwapElementsArrayCrimes(_crimes, _nCrimes, left, pos_min);
    }
}

void CrimeSet::readComments(std::istream &inputStream) {
    
    string str;
    
    while (inputStream.peek() == '#') { // hashtags
               
        getline(inputStream, str);

        str.erase(0, 1);
        _comment.append(str + "\n");
    }
}

void CrimeSet::saveComments(std::ostream &outputStream) {
    
    outputStream << FormatAsComment(_comment, '#');
}

void InitializeArrayInts(int array[], int size) {
    for (int i=0; i<size; i++)
        array[i]=0;
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

void SwapElementsArrayCrimes(Crime array[], int nElements, int first, int second) {
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

int PosMinArrayCrimes(Crime array[], int initialPos, int finalPos) {
    // Set the first value as the min value.
    
    Crime min = array[initialPos];
    int posMin = initialPos;
    
    // If there is another value smaller than the real min, then, update
    // min with the new minimum.
    
    for (int pos = initialPos; pos <= finalPos ; pos++) {
        
        
        if (min.IsSmaller(array[pos])) {
            min = array[pos];
            posMin = pos;
        }
    }
    if (initialPos > finalPos) posMin = -1;
    
    return posMin;
}
