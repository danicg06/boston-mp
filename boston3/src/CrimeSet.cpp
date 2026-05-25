/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file  CrimeSet.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio
 */

#include "CrimeSet.h"

using namespace std;

const string CrimeSet::MAGIC_STRING_T="MP-CRIME-T-1.0";
const float  CrimeSet::GROWING_RATIO = 1.5;

CrimeSet::CrimeSet(int size): _nCrimes(0) {
    if (size >= 0) {
        if (size < INITIAL_CAPACITY)
            _capacity = INITIAL_CAPACITY;
        else
            _capacity = size;
        _crimes = allocateArrayCrime(_capacity);
    }
    else{
        _capacity = 0;
        _nCrimes = 0;
        _crimes = nullptr;
        
        throw std::out_of_range("CrimeSet::CrimeSet(int): invalid parameter size");
    }
}

CrimeSet::CrimeSet(const CrimeSet &orig) {
    _crimes = allocateArrayCrime(orig._capacity);
    copy(orig);
}

CrimeSet::~CrimeSet() {
    deallocateArrayCrime();
}

CrimeSet & CrimeSet::operator=(const CrimeSet &orig) {
    // Avoid errors if copying the same object
    if (&orig != this) {
        deallocateArrayCrime();
        _crimes = allocateArrayCrime(orig._capacity);
        _capacity = orig._capacity;
        copy(orig);
    }
    return *this;
}

int CrimeSet::getSize() const {
    return _nCrimes;
}

int CrimeSet::getCapacity() const {
    return _capacity;
}

std::string CrimeSet::getComment() const {
    return _comment;
}

void CrimeSet::setComment(const std::string & text) {
    const char SEPARATOR = '\n';
    int i = text.length() - 1;
    _comment = text;
    
    if (i >= 0) {    // If the string is not empty
        if (text.at(i) != SEPARATOR)  // If there is a SEPARATOR missing
            _comment += SEPARATOR;
    }
}

std::string CrimeSet::toString() const {
    const string SEPARATOR = "\n";
    string result = to_string(_nCrimes);
    
    for (int i=0; i < _nCrimes; i++)
        result += SEPARATOR + _crimes[i].toString();
    
    return result + SEPARATOR;
}

void CrimeSet::clear() {
    _nCrimes = 0;
    _comment.clear();
    
    deallocateArrayCrime();
    _crimes = allocateArrayCrime(INITIAL_CAPACITY);
}

Crime & CrimeSet::at(int pos) const {
    if (pos < 0 || pos >= _nCrimes)
        throw std::out_of_range(
            std::string("void CrimeSet::at(int pos) : ") +
            "position is not valid");
           
    return (_crimes[pos]);
}

void CrimeSet::load(const std::string &fileName){
    clear();
    ifstream file(fileName);
    if (file) {
        string str_crime;
        getline(file, str_crime);
        
        if (str_crime == MAGIC_STRING_T) {
            readComments(file);
            getline(file, str_crime); // number of crimes
            int n = stoi(str_crime);
            if (n >= 0) {
                // Read each crime in the file
                for (int i = 0; i < n; i++) {
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

void CrimeSet::append(const Crime & newCrime) {
    if (_nCrimes == _capacity) 
        reallocateArrayCrime();
    
    // Add the new element
    _crimes[_nCrimes++] = newCrime;
}

void CrimeSet::save(const std::string & fileName) const{
    const char SEPARATOR = '\n';
    ofstream file(fileName);
    if (file) {
        file << MAGIC_STRING_T << SEPARATOR;
        saveComments(file);
        file << _nCrimes << SEPARATOR;
        
        for (int i=0; i < _nCrimes; i++) {
            file << _crimes[i].toString() << SEPARATOR;
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

void CrimeSet::sort() {
    for (int left = 0 ; left < _nCrimes; left++) {
        // Calculates the minimum between "left" and "_nCrimes"-1
        Crime min = _crimes[left]; // Minimum crime's value
        int posMin = left; // Minimum crime's position
        
        posMin = posMinArrayCrimes(left, _nCrimes - 1);
        min = _crimes[posMin];
        
        // Swap values in left and posMin positions.
        swapElementsArrayCrimes(left, posMin);
    }
}

CrimeSet CrimeSet::selectWhereEQ(const std::string &field, const std::string &value) const{
    const string COMMENT = "Restricted to " + field + " = " + value + "\n";
    
    CrimeSet crimeset;
    crimeset._comment= _comment + COMMENT;
    
    for (int i = 0; i < _nCrimes; i++) {
        if (_crimes[i].getField(field) == value) {
            crimeset.append(_crimes[i]);
        }
    }
    return crimeset;
}

CrimeSet CrimeSet::selectValidLocation() const {
    const string COMMENT = "Restricted to valid Coordinates\n";
    
    CrimeSet crimeset;
    crimeset._comment = _comment + COMMENT;
    
    for (int i=0; i<_nCrimes ; i++) {
        if (_crimes[i].getLocation().isValid()) 
            crimeset.append(_crimes[i]);
    }
    
    return crimeset;
}

void CrimeSet::readComments(std::istream &inputStream) {
    const char DELIMITER    = '#';
    const string SEPARATOR  = "\n";
    
    string comment;
    while (inputStream.peek() == DELIMITER) { // hashtags
        getline(inputStream, comment);
        comment.erase(0, 1);
        _comment.append(comment + SEPARATOR);
    }
}

void CrimeSet::saveComments(std::ostream &outputStream) const{
    const char DELIMITER = '#';
    outputStream << FormatAsComment(_comment, DELIMITER);
}

int CrimeSet::findCrime(const Crime & crime, int initialPos, int finalPos) const {
    int result = -1;
    
    bool found = false;
    int i = initialPos;
    while (i <= finalPos && !found) {   // Search for a crime with the same ID in the array
        if (_crimes[i].getId() == crime.getId())
            found = true;
        else
            i++;
    }
    
    if (found)
        result = i;
    
    return result;
}

int CrimeSet::findCrime(const Crime & crime) const {
    return findCrime(crime, 0, _nCrimes-1);
}

int CrimeSet::posMinArrayCrimes(int initialPos, int finalPos) {
    // Set the first value as the min value
    Crime min = _crimes[initialPos];
    int posMin = initialPos;
    
    // If there is another value smaller than min, then update min with the
    // new minimum
    for (int pos = initialPos+1; pos <= finalPos ; pos++) {
        if (min.IsSmaller(_crimes[pos])) {
            min = _crimes[pos];
            posMin = pos;
        }
    }
    if (initialPos > finalPos) posMin = -1;
    
    return posMin;
}

void CrimeSet::swapElementsArrayCrimes(int first, int second) {
    if (first < _nCrimes && first >= 0 && second < _nCrimes && second >= 0) {
        Crime tmp = _crimes[first];
        _crimes[first] = _crimes[second];
        _crimes[second] = tmp;
    }
    else // given positions not valid
        throw std::out_of_range(
            std::string("void CrimeSet::SwapElementsArrayCrimes("
                        "int first, int second) : ") +
                        "given positions are not valid.");
}

string FormatAsComment(const string &comment, char commentCharacter) {
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

Crime * CrimeSet::allocateArrayCrime(int cap) {
    Crime *array_crime = nullptr;
    _capacity = 0;
    if (cap > 0) {
        array_crime = new Crime [cap];
        _capacity = cap;
    }
    
    return array_crime;
}

void CrimeSet::deallocateArrayCrime() {
    delete [] _crimes;
    _crimes = nullptr;
}

void CrimeSet::reallocateArrayCrime() {
    int newCapacity = ceil(_capacity*GROWING_RATIO);
    Crime *newArray = allocateArrayCrime(newCapacity);
    
    // Copy previous crimes
    for (int i = 0; i < _nCrimes; i++)
        newArray[i] = _crimes[i];
    
    deallocateArrayCrime();
    _crimes = newArray;
}

void CrimeSet::copy(const CrimeSet & orig) {
    // Copy the crimes in the array of the object provided to the implicit object
    for (int i=0; i < orig._nCrimes; i++)
        _crimes[i] = orig._crimes[i];
    
    _comment = orig._comment;
    _nCrimes = orig._nCrimes;
}