/*
 * Metodología de la Programación
 * Curso 2024/2025
 */

/** 
 * @file:  CrimeCounter.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio
 * Created on September 24, 2024, 3:19 PM
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "CrimeCounter.h"
using namespace std;


/**
 * DEFAULT_COORD_BOTTOMLEFT is set to the bottom left corner of the Boston area
 */
const Coordinates CrimeCounter::DEFAULT_COORD_BOTTOMLEFT(42.207760,-71.178673);  

/**
 * DEFAULT_COORD_TOPRIGHT is set to the top right corner of the Boston area
 */
const Coordinates CrimeCounter::DEFAULT_COORD_TOPRIGHT(42.395042,-70.953728);  


CrimeCounter::CrimeCounter(int nRows, int nColumns, const Coordinates & bottomLeftCoord, 
            const Coordinates & topRightCoord) {
    
    if (nRows > 0 && nColumns > 0 && bottomLeftCoord.isValid() && topRightCoord.isValid()) {
    _nRows = nRows;
    _nCols = nColumns;
    _bottomLeftCoord = bottomLeftCoord;
    _topRightCoord = topRightCoord;
    _frequency = allocateMatrixFrequencies(_nRows, _nCols);
    clear();
    }
    else {
        _nRows = 0;
        _nCols = 0;
        _frequency = nullptr;
        throw std::invalid_argument(
                        std::string("CrimeCounter::CrimeCounter"
                        "(int nRows, int nColumns, Coordinates  bottomLeftCoord, "
                        "Coordinates  topRightCoord) : ") +
                        "the given magic string is invalid)");
    }
}

CrimeCounter::CrimeCounter(const CrimeCounter & orig){
    
    _frequency = allocateMatrixFrequencies(orig._nRows, orig._nCols);
    copy(orig);
}

CrimeCounter::~CrimeCounter(){
    
    deallocateMatrixFrequencies();
}

CrimeCounter &CrimeCounter::operator=(const CrimeCounter & orig){
    
    if (&orig != this) {
        deallocateMatrixFrequencies();
        cerr << "Hola" << endl;
        _frequency = allocateMatrixFrequencies(orig._nRows, orig._nCols);

        copy(orig);
    }
    return *this;
}

int CrimeCounter::getNumRows() const {
    
    return (_nRows);
}

int CrimeCounter::getNumCols() const {
    
    return (_nCols);
}

Coordinates CrimeCounter::getLeftLocation() const {
    
    return(_bottomLeftCoord);
}

Coordinates CrimeCounter::getRightLocation() const {
    
    return (_topRightCoord);
}

std::string CrimeCounter::toString() const {
    
    string rowsLines;
    
    for (int i=0; i<_nRows; i++){
        for (int j=0; j<_nCols-1; j++){
            rowsLines += to_string(_frequency[i][j]) + " ";
        }
    }
    rowsLines += to_string(_frequency[_nRows-1][_nCols-1]);
    
    return (to_string(_nRows) + " " + to_string(_nCols) + "\n" + 
            _bottomLeftCoord.toString() + "\n" + _topRightCoord.toString() +
            rowsLines + "\n");
}

int CrimeCounter::getMaxFrequency() const {
    
    int max = -1; // First maximum, values are always positive
    for (int f=0; f < _nRows; f++)
        for (int c=0; c < _nCols; c++)
            if (_frequency[f][c] > max) max = _frequency[f][c];
    
    return max;
}

int CrimeCounter::getTotalLocated() const {
    
    int totalLocated = 0;
    
    for (int i=0; i < _nRows; i++) {
        for (int j=0; j < _nCols; j++){
            totalLocated += _frequency[i][j];
        }
    }
    
    return totalLocated;
}

void CrimeCounter::clear() {
    
    for (int i=0; i < _nRows; i++)
        for (int j=0; j < _nCols; j++)
            _frequency[i][j] = 0;
}

void CrimeCounter::increaseFrequency(const Crime &crime, int frequency) {
    
    Coordinates location = crime.getLocation();
    if (location.isValid() && location.isInsideArea(_bottomLeftCoord,
                                                    _topRightCoord)) {
        int row, col;
        getRowColumn(location, row, col);
        
        if (frequency == 0)
            frequency = 1;
        
        _frequency[row][col] += frequency;
    }
}

void CrimeCounter::calculateFrequencies(const CrimeSet &crimes) {
    clear();
    for (int i = 0; i < crimes.getSize(); i++) increaseFrequency(crimes[i], 1);
}

int & CrimeCounter::operator()(int row, int column) const {
    return _frequency[row][column];
}

void CrimeCounter::saveAsPPMTextImage(const std::string &fileName, 
        const ColorPalette &palette, const std::string &comment) const{
    
    const int MAX_COLOR           = 255;
    const string FORMAT           = "P3";
    const string SEPARATOR_FIELDS = "\n";
    const string SEPARATOR        = " ";
    
    ofstream file(fileName);
    
    if (file) {
        
        int colorIndex = 0;
        
        // Compute maxFrequency as the maximum frequency in the frequency matrix
        int maxFrequency = getMaxFrequency();
        // Save heading and comments into the ppm file
        file << FORMAT + SEPARATOR_FIELDS;
        file << comment;
        file << _nCols << SEPARATOR << _nRows << SEPARATOR_FIELDS 
             << MAX_COLOR << SEPARATOR_FIELDS;
        // For every cell in the frequency matrix
        for (int i=0; i < _nRows; i++ ){
            for (int j=0; j < _nCols; j++) {
                colorIndex = GetIndexPalette(palette, 
                      log(_frequency[i][j]+1), log(maxFrequency+1));
                // Save into the ppm file the RGB components of the color at 
                //the position colorIndex of the palette
                file << palette.getColor(colorIndex).toString() << SEPARATOR;
                                
                if (!file) {
                    file.close();
                    throw std::ios_base::failure(
                        std::string("void CrimeCounter::saveAsPPMTextImage" 
                                    "(const string &fileName, const " 
                                    "ColorPalette &palette, const std::string "
                                    "&comment) : ") + "file cannot be opened "
                                    "or an error has occured");
                }
            }
        }            
    }
    else{
        file.close();
        throw std::ios_base::failure(
                        std::string("void CrimeCounter::saveAsPPMTextImage" 
                                    "(const string &fileName, const " 
                                    "ColorPalette &palette, const std::string "
                                    "&comment) : ") + "file cannot be opened "
                                    "or an error has occured");
    }
    file.close();
}

void CrimeCounter::getRowColumn(const Coordinates &coordinates, int& row, 
        int& column) const {
    if (!coordinates.isValid() || 
            !coordinates.isInsideArea(_bottomLeftCoord, _topRightCoord)) {
        throw std::invalid_argument(
            string("void CrimeCounter::getRowColumn((const Coordinates &loc, int& row, int& column) const: ") +
            coordinates.toString() + " is not a valid location or is outside the target area");
    }
    Coordinates targetArea = this->_bottomLeftCoord.length(this->_topRightCoord);
    float cellHeight = targetArea.getLatitude()/_nRows;
    float cellWidth = targetArea.getLongitude()/_nCols;
    Coordinates delta = _bottomLeftCoord.length(coordinates);
    
    row = _nRows - (delta.getLatitude() / cellHeight);
    column = (delta.getLongitude() / cellWidth);
    if (row == _nRows) row = _nRows-1;
    if (column == _nCols) column = _nCols-1;
}

int** CrimeCounter::allocateMatrixFrequencies(int nRows, int nCols) {
    
    int **m;
    m = new int*[nRows];
    m[0] = new int[nRows*nCols];
//cerr << "Filas: " << nRows << ", columnas: " << nCols << endl;
    for (int i=1; i<nRows;++i)
        m[i] = m[i-1]+nCols;
    
    return m;
}

void CrimeCounter::deallocateMatrixFrequencies() {
        
    delete[] _frequency[0];
    delete[] _frequency;
}

void CrimeCounter::copy(const CrimeCounter &orig) {
    _nRows = orig._nRows;
    _nCols = orig._nCols;
    _bottomLeftCoord = orig._bottomLeftCoord;
    _topRightCoord = orig._topRightCoord;
    for (int i=0; i<_nRows; i++){
        for (int j=0; j<_nCols; j++) {
            _frequency[i][j] = orig._frequency[i][j];
        }
    }
}

// External functions
int GetIndexPalette(const ColorPalette &palette, float frequency, float maxFrequency) {
    return frequency == maxFrequency ? palette.getNumColors() - 1 : 
        frequency * palette.getNumColors() / maxFrequency;
}

