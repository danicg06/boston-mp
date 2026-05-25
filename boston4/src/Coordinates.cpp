/*
 * Metodología de la Programación
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


Coordinates::Coordinates(float latitude, float longitude): _latitude(INVALID_COORDINATE),
                                                           _longitude(INVALID_COORDINATE)
{
    if (latitude >= -INVALID_COORDINATE && latitude <= INVALID_COORDINATE)
        _latitude = latitude;
    if (longitude >= -INVALID_COORDINATE && longitude <= INVALID_COORDINATE)
        _longitude = longitude;
}

Coordinates::Coordinates(const std::string & coords) {
    // position where the separator between latitude and longitude is
    int pos_separator = coords.find(',', 0);
    
    // part of the string that contains the latitude
    _latitude = stof(coords.substr(0, pos_separator));
    
    // part of the string that contains the longitude
    _longitude = stof(coords.substr(pos_separator + 1
                      ,coords.length()-1 - pos_separator));
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

void Coordinates::setLatitude(float latitude) {
    
    //if (latitude >= -INVALID_COORDINATE && latitude <= INVALID_COORDINATE)
        _latitude = latitude;
}

void Coordinates::setLongitude(float longitude) {
    
    //if (longitude >= -INVALID_COORDINATE && longitude <= INVALID_COORDINATE)
        _longitude = longitude;
}

void Coordinates::set(float latitude, float longitude){
    setLatitude(latitude);
    setLongitude(longitude);
}

std::string Coordinates::toString() const {    
    return (to_string(_latitude) + ',' + to_string(_longitude));
}

Coordinates Coordinates::length(const Coordinates &second) const{
    return Coordinates(abs(_latitude - second._latitude), abs(_longitude - second._longitude));
}

bool Coordinates::isInsideArea(const Coordinates &bottomLeft, const Coordinates &topRight) const {
    return ((_latitude >= bottomLeft._latitude) && (_latitude <= topRight._latitude)
            && (_longitude >= bottomLeft._longitude) && (_longitude <= topRight._longitude));
}

std::ostream & operator<<(std::ostream & os, const Coordinates & obj){
    
    os << obj.toString();
    return os;
}

std::istream& operator>>(std::istream &is, Coordinates &obj) {
    
    is >> obj._latitude;
    is >> obj._longitude;
    return is;
}