/*
 * Metodología de la Programación: Boston2
 * Curso 2024/2025
 */

/** 
 * @file   Crime.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio
 */

#include "Crime.h"
#include <cctype>

using namespace std;

/*
 * Initialization of the static string that contains the value assigned to any 
 * string field (string) which is found empty in the data of a Crime
 */
const std::string Crime::UNKNOWN_VALUE = "UNKNOWN";

/*
 * Initialization of the static string that contain the default value for the
 * DateTime field in a Crime 
 */
const string Crime::DATETIME_DEFAULT = "2017-01-20 02:00:00";

/* 
 * Initialization of the static string with the default values for every field in 
 * a Crime
 */
const string Crime::CRIME_DEFAULT("0," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," +
        UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE + "," + UNKNOWN_VALUE +
        "," + ((std::string)"1") + "," + Crime::DATETIME_DEFAULT + "," +
        UNKNOWN_VALUE + ",181,181");

Crime::Crime() {
    set(CRIME_DEFAULT);
}

Crime::Crime(const string &line) {
    set(line);
}

int Crime::getCounter() const {
    return _counter;
}

std::string Crime::getId() const {
    return _id;
}

std::string Crime::getCode() const {
    return _code;
}

std::string Crime::getGroup() const {
    return _group;
}

std::string Crime::getDescription() const {
    return _description;
}

std::string Crime::getDistrict() const {
    return _district;
}

std::string Crime::getStreet() const {
    return _street;
}

std::string Crime::getAreaReport() const {
    return _areaReport;
}

bool Crime::isShooting() const {
    return _shooting;
}

DateTime Crime::getDateTime() const {
    return _dateTime;
}

Coordinates Crime::getLocation() const {
    return _location;
}

bool Crime::isIDUnknown() const {
    return (_id == UNKNOWN_VALUE);
}

std::string Crime::toString() const {
    return (to_string(_counter) + "," + _id + "," + _code + "," + _group + "," 
        + _description + "," + _district + "," + _areaReport + "," 
        + to_string(_shooting) + "," + _dateTime.toString() + "," + _street + "," 
        + _location.toString());
}

void Crime::setCounter(int c) {
    _counter = c;
}

void Crime::setId(const std::string &id) {
    string trimmedId = id;
    Trim(trimmedId);
    
    if (trimmedId.size()==0)
        throw std::invalid_argument(
            std::string("void Crime::setId(const std::string &id) : ") +
            "id is empty");
    this->_id = trimmedId;
}

void Crime::setCode(const std::string &code) {
    _code = code;
    Trim(_code);
    Capitalize(_code);
}

void Crime::setGroup(const std::string &group) {
    _group = group;
    Trim(_group);
    Capitalize(_group);
}

void Crime::setDescription(const std::string &description) {
    _description = description;
    Trim(_description);
    Capitalize(_description);
}

void Crime::setDistrict(const std::string &district) {
    _district = district;
    Trim(_district);
    Capitalize(_district);
}

void Crime::setAreaReport(const std::string &areaReport) {
    _areaReport = areaReport;
    Trim(_areaReport);
    Capitalize(_areaReport);
}

void Crime::setStreet(const std::string &street) {
    _street = street;
    Trim(_street);
    Capitalize(_street);
}

void Crime::setShooting(bool shooting) {
    _shooting = shooting;
}

void Crime::setDateTime(const string & time) {
    _dateTime = time;
}

void Crime::setLocation(const Coordinates & coordinates) {
    _location = Coordinates(coordinates.getLatitude(), coordinates.getLongitude());
}

void Crime::set(const std::string & line) {
    const int NFIELDS = 11;
    string data = "";        //piece of data detached from line;
    size_t pos = 0;
    size_t posn = 0;   // aux for the beginning of the fields

    for (int nfield = 0; nfield < NFIELDS - 1 && posn != string::npos; nfield++) {
        posn = line.find(',', pos); // beginning of the next field
        data = line.substr(pos, posn - pos);
        pos = posn + 1;

        switch (nfield) {
            case 0: // counter
                setCounter(stoi(data));
                break;
            case 1: // ID
                setId(data);
                break;
            case 2: // code
                setCode(data);
                break;
            case 3: // group
                setGroup(data);
                break;
            case 4: // desc
                setDescription(data);
                break;
            case 5: // District alphaNumeric
                setDistrict(data);
                break;
            case 6: // areaReport
                setAreaReport(data);
                break;
            case 7: // shooting
                setShooting(stoi(data));
                break;
            case 8: // date time
                setDateTime(data);
                break;
            case 9: // street
                setStreet(data); 
                break;
        }
     
    }
    
    // location
    data = line.substr(pos, line.length() - pos + 1);
    int pos_separator = data.find(',', 0); // position where the separator between latitude and longitude is 

    string str_latitude = data.substr(0, pos_separator); // part of the 'data' string that contains the latitude
    string str_longitude = 
        data.substr(pos_separator + 1, data.length()-1 - pos_separator); // part of the 'data' string that contains the longitude
    Coordinates coord(stof(str_latitude), stof(str_longitude));
    setLocation(coord);
    
    normalize();
   
} //end of set()

void Trim(string & myString) {
    
    bool is_space = true;
    int len = myString.length(); 
    int i = 0;
    while (i< len && is_space) {
        if (!isspace(myString.at(i))) is_space = false;
        i++;
    }

    if (is_space == false) {

        size_t pos_first_char = myString.find_first_not_of(" ");
        size_t pos_last_char = myString.find_last_not_of(" ");
        int n_values = pos_last_char - pos_first_char + 1;

        myString = myString.substr(pos_first_char, n_values);
    }
    else // is_space == true
        myString == "";    
    
}

void Capitalize(string & myString) {

    int str_len = myString.length();

    for (int i=0; i < str_len; i++) {
        
        myString.at(i) = toupper(myString.at(i));
    }
}

void Normalize(Crime & crime) {
    
    crime.normalize();
                
}

string Crime::getField(const std::string & field) const {

    string str_field; // string with the value of the provided field
    const int NUM_FIELDS = 11;
    const string fields[NUM_FIELDS] {"Counter", "ID", "Code", "Group",
                                     "Description", "District", "Area",
                                     "Street", "Shooting", "DateTime",
                                     "Location"};
    
    int i = 0;
    bool found = (fields[i] == field);
    
    while (i < NUM_FIELDS && !found) {
        i++;
        found = (fields[i] == field);
    }
    
    if (!found) {
        throw std::invalid_argument(std::string("void Crime::getField(const std::string & field) const : ") +
                                    "label of the field is not valid");
    }
    else {
        switch(i) {
            case 0:
                str_field = to_string(_counter);
                break;
            case 1:
                str_field = _id;
                break;
            case 2:
                str_field = _code;
                break;
            case 3:
                str_field = _group;
                break;
            case 4:
                str_field = _description;
                break;
            case 5:
                str_field = _district;
                break;
            case 6:
                str_field = _areaReport;
                break;
            case 7:
                str_field = _street;
                break;
            case 8:
                str_field = to_string(_shooting);
                break;
            case 9:
                str_field = _dateTime.toString();
                break;
            case 10:
                str_field = _location.toString();
                break;
        }
    }
    return str_field;
}

void Crime::normalize() {

    // code
    Trim(_code);
    Capitalize(_code);

    // group
    Trim(_group);
    Capitalize(_group);

    // desc
    Trim(_description);
    Capitalize(_description);

    // District alphaNumeric
    Trim(_district);
    Capitalize(_district);

    // area report 
    Trim(_areaReport);
    Capitalize(_areaReport);

    // street
    Trim(_street);
    Capitalize(_street);
}

bool Crime::IsSmaller (const Crime & compare) const {
    
    bool smaller=true;
    if (_dateTime < compare._dateTime)
        smaller=false;
    else
        if (_dateTime > compare._dateTime)
            smaller=true;
        else {
            // smaller=IsAphabeticallySmall(compare);
            smaller=(_id > compare._id);
        }
    return smaller;
}

bool Crime::IsSameCrime (const Crime &crime) const {
    
    return (_id == crime._id && _dateTime == crime._dateTime);
}
