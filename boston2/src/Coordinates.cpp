/*
 * Metodología de la Programación: Boston2
 * Curso 2024/2025
 */

/** 
 * @file   Coordinates.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio
 */

#include "Coordinates.h"

const float Coordinates::INVALID_COORDINATE=181.0;

using namespace std;
using namespace std;


Coordinates::Coordinates(float latitude, float longitude): _latitude(INVALID_COORDINATE),
                                                           _longitude(INVALID_COORDINATE)
{
    if (latitude >= -INVALID_COORDINATE && latitude <= INVALID_COORDINATE)
        _latitude = latitude;
    if (longitude >= -INVALID_COORDINATE && longitude <= INVALID_COORDINATE)
        _longitude = longitude;
}

Coordinates::Coordinates(const std::string & coords) {
    const char DELIMITER   = ',';
    
    int i = 0;
    
    _latitude = ExtractNumberFirstOcurrence(coords);
    
    while (coords.at(i) != DELIMITER)
        i++;
    
    // Now that I have obtained and saved the first number, I delete the
    // part of the string that contains the first number to reuse the function
    // ExtractNUmberFirstOcurrence. That will return the second number (which
    // is the only number in the string from the i-position to the last.
    
    string longitude_str = coords;
    longitude_str.erase(0,i);
    
    _longitude = ExtractNumberFirstOcurrence(longitude_str);
}

float Coordinates::getLatitude() const {
    return _latitude;
}

float Coordinates::getLongitude() const {
    return _longitude;
}

bool Coordinates::isValid() const {
    
    const int MIN_LAT       = -90;
    const int MAX_LAT       = 90;
    const int MIN_LONGITUDE = -180;
    const int MAX_LONGITUDE = 180;
    
    return (_latitude >= MIN_LAT && _latitude <= MAX_LAT)
            && (_longitude >= MIN_LONGITUDE && _longitude <= MAX_LONGITUDE);
}

void Coordinates::set(float latitude, float longitude){
    setLatitude(latitude);
    setLongitude(longitude);
}

void Coordinates::setLatitude(float latitude) {
    if (latitude >= -INVALID_COORDINATE && latitude <= INVALID_COORDINATE)
        _latitude = latitude;
}

void Coordinates::setLongitude(float longitude) {
    if (longitude >= -INVALID_COORDINATE && longitude <= INVALID_COORDINATE)
        _longitude = longitude;
}

std::string Coordinates::toString() const {
    const string SEPARATOR = ",";
    
    return (to_string(_latitude) + SEPARATOR + to_string(_longitude));
}

Coordinates Coordinates::length(const Coordinates &second) const{
    return Coordinates(abs(_latitude - second._latitude), abs(_longitude - second._longitude));
}                        

bool Coordinates::isInsideArea(const Coordinates &bottomLeft, const Coordinates &topRight) const {
    return (_latitude >= bottomLeft._latitude && _latitude <= topRight._latitude
            && _longitude >= bottomLeft._longitude && _longitude <= topRight._longitude);
}

float ExtractNumberFirstOcurrence(const std::string & number_str) {
    
    const char DECIMAL     = '.';
    const char SIGN_SUBSTR = '-';
    const char SIGN_ADD    = '+';
    
    int i = 0;
    int length = number_str.length();
    
    while (!isdigit(number_str.at(i)) && number_str.at(i) != SIGN_SUBSTR && number_str.at(i) != SIGN_ADD)
        i++;
    
    // The bucle has finished beacuse it has found a digit, so the number starts
    // in the i-position.
    
    // n will be the number of digits of the number in the string.
    
    int n = 1;
    
    bool continue_working = true;
    
    // First of all, the bucle checks if the position is correct. Then, it
    // checks wether the character is valid or not.
    
    while ((i + n) < length && continue_working) {
        if (isdigit(number_str.at(i + n)) || number_str.at(i + n) == DECIMAL)
            n++;
        else
            continue_working = false;
    }
    
    // So I can extract the substring that contains the number.
    
    string result_str = number_str.substr(i,n);
    
    return stof(result_str);
}
