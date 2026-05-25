/*
 * Metodología de la Programación: Boston1
 * Curso 2024/2025
 */

/** 
 * @file   main.cpp
 * @author Casasola Guerrero, Daniel
 * @author Castro García, Sergio  
 */

#include <string>
#include <iostream>

#include "DateTime.h"
#include "Crime.h"
#include "ArrayCrimesFunctions.h"

using namespace std;

/**
 * The purpose of this program is to read a set of data on crimes committed 
 * in the city of Boston, showing some statistics about them.
 * This program first reads from the standard input a name and a value for one of
 * the fields of a Crime (this will be used later to select the crimes with
 * that field equals to the provided value).
 * Then it reads an integer number n to define the number of Crime objects to
 * read.
 * Thereafter, it reads n Crime objects, normalizing and storing each one
 * in the array inputCrimes only if the ID of the normalized crime is not 
 * unknown and there is not already a crime in the array inputCrimes with the 
 * same ID (the array cannot contains two crimes with the same ID).
 * Be careful that the number of crimes inserted in the array does not exceed 
 * its capacity.
 * Next, the program shows in the standard output all the Crimes in the array
 * Hereafter, it computes and shows the histograms by day of the week and
 * by hour of the day.
 * Subsequently, it computes and shows the maximum cumulative number of crimes 
 * in a week day and the maximum cumulative number of crimes in a  day hour.
 * Finally the program computes, sorts and shows an array with those Crimes 
 * that verify the condition that the previously provided field is equals to 
 * the given value.
 * Be careful to show the output as in the below example.
 * 
 * Running example:
 * > dist/Debug/GNU-Linux/boston1 < data/crimes22.b1in
Records read: 22
20 crimes with valid and non-repeated ID: 
0,225520077,3126,UNKNOWN,WARRANT ARREST - OUTSIDE OF BOSTON WARRANT,D14,786,0,2022-02-02 00:00:00,WASHINGTON ST,42.343082,-71.141724
2,222201764,724,UNKNOWN,AUTO THEFT,C6,200,0,2022-01-09 00:00:00,W BROADWAY,42.341286,-71.054680
3,222201559,301,UNKNOWN,ROBBERY,D4,UNKNOWN,0,2022-03-05 13:00:00,ALBANY ST,42.333183,-71.073936
4,222111641,619,UNKNOWN,LARCENY ALL OTHERS,D14,778,0,2022-02-14 12:30:00,WASHINGTON ST,42.349056,-71.150497
5,222107076,3126,UNKNOWN,WARRANT ARREST - OUTSIDE OF BOSTON WARRANT,D4,UNKNOWN,0,2022-03-11 10:45:00,MASSACHUSETTS AVE & ALBANY ST BOSTON  MA 02118 UNI,42.333500,-71.073509
6,22209348,801,UNKNOWN,ASSAULT - SIMPLE,C6,235,0,2022-02-08 22:37:00,DORCHESTER AVE,42.321373,-71.056793
7,222073971,611,UNKNOWN,LARCENY PICK-POCKET,A1,77,0,2022-02-27 10:07:00,NEW SUDBURY ST,42.361839,-71.059769
8,222072974,619,UNKNOWN,LARCENY ALL OTHERS,C6,186,0,2022-01-14 15:20:00,ALLSTATE ROAD,181.000000,181.000000
9,222055138,3201,UNKNOWN,PROPERTY - LOST/ MISSING,E13,574,0,2022-01-23 13:15:00,WASHINGTON ST,42.309719,-71.104294
10,222045598,2610,UNKNOWN,TRESPASSING,B2,280,0,2022-01-21 12:30:00,DUDLEY ST,42.328728,-71.083824
11,222040102,3410,UNKNOWN,TOWED MOTOR VEHICLE,E13,569,0,2022-02-11 00:00:00,STEDMAN ST,42.304298,-71.107262
12,22203312,540,UNKNOWN,BURGLARY - COMMERICAL,A1,UNKNOWN,0,2022-01-16 01:40:00,LINCOLN STREET,181.000000,181.000000
13,222027001,2670,UNKNOWN,HARASSMENT/ CRIMINAL HARASSMENT,E5,559,0,2022-02-20 04:00:00,WASHINGTON ST,42.284718,-71.129990
14,222021808,3114,UNKNOWN,INVESTIGATE PROPERTY,D4,624,0,2022-03-29 00:00:00,BOYLSTON ST,181.000000,181.000000
15,222021807,3115,UNKNOWN,INVESTIGATE PERSON,D4,UNKNOWN,0,2022-03-29 03:27:00,W SPRINGFIELD ST,42.339302,-71.079124
16,222021806,3115,UNKNOWN,INVESTIGATE PERSON,B3,444,0,2022-03-29 01:35:00,BLUE HILL AVE,42.295765,-71.087563
17,222021803,1402,UNKNOWN,VANDALISM,B2,UNKNOWN,0,2022-03-29 02:00:00,NORFOLK AVE,42.327137,-71.072182
18,222021802,3006,UNKNOWN,SICK/INJURED/MEDICAL - PERSON,C11,UNKNOWN,0,2022-03-29 02:03:00,DORCHESTER AVE,42.313225,-71.057152
19,222021800,3108,UNKNOWN,FIRE REPORT,A7,UNKNOWN,0,2022-03-29 00:36:00,MERIDIAN ST,42.379017,-71.039207
21,222111640,619,UNKNOWN,LARCENY ALL OTHERS,D14,778,0,2022-02-14 12:30:00,WASHINGTON ST,42.349056,-71.150497

Histogram by day of the week:
SUNDAY 5
MONDAY 2
TUESDAY 7
WEDNESDAY 1
THURSDAY 0
FRIDAY 4
SATURDAY 1

Histogram by hour of the day:
0 5
1 2
2 2
3 1
4 1
5 0
6 0
7 0
8 0
9 0
10 2
11 0
12 3
13 2
14 0
15 1
16 0
17 0
18 0
19 0
20 0
21 0
22 1
23 0

Maximum cumulative number of crimes in a week day: 7
Day of maximum cumulative number of crimes in a week day: TUESDAY
Maximum cumulative number of crimes in a day hour: 5
Hour of maximum cumulative number of crimes in a day hour: 0

Sorted list of selected crimes where Code=619:
8,222072974,619,UNKNOWN,LARCENY ALL OTHERS,C6,186,0,2022-01-14 15:20:00,ALLSTATE ROAD,181.000000,181.000000
21,222111640,619,UNKNOWN,LARCENY ALL OTHERS,D14,778,0,2022-02-14 12:30:00,WASHINGTON ST,42.349056,-71.150497
4,222111641,619,UNKNOWN,LARCENY ALL OTHERS,D14,778,0,2022-02-14 12:30:00,WASHINGTON ST,42.349056,-71.150497
 */
int main(int argc, char* argv[]) {
    Crime crime;
    const int DIM_ARRAY = 200; // capacity of the two arrays of crimes
    Crime inputCrimes[DIM_ARRAY] = {crime}; // array of crimes read from the standard input 
    Crime selectedCrimes[DIM_ARRAY] = {crime}; // array of crimes that verify a given condition
 
    int frequencyByDay[7] = {0}; // array to save the cumulative number of crimes (histogram) for every week day
    int frequencyByHour[24] = {0}; // array to save the cumulative number of crimes (histogram) for every hour

    // Read a name and a value for one of the fields of a Crime 
    string field_name;
    string field_value;
    cin >> field_name;
    cin >> field_value;
    cin.ignore();
    // Remember to take off the character \n at the end of previous value
    
    // Read number n to define the number of Crime objects
    int n = 0;
    cin >> n;
    cin.ignore();
    // Remember to take off the character \n after previous number 
   
    // Loop to read n Crime objects
    // Read a Crime object, normalize and insert it in the array
    //     if its ID is not unknown and there is not any crime 
    //     in the array with identical ID
    int used = 0; // number of crimes inserted in the array
    int read = 0; // number of crimes read from the standard input
    string UNKNOWN_VALUE = "UNKNOWN";
    string s = "";
    while (used < DIM_ARRAY && read < n) {
        getline(cin, s);
        Crime read_crime (s);
        Normalize(read_crime);
        
        bool repeated_id = false;
        for (int i=0; i < used; i++) { // loop for checking if there is a crime 
                                       // with identical ID
            if (read_crime.getId() == inputCrimes[i].getId()) repeated_id = true; 
        }
        
        // inserts the crime object in the array if the conditions are met
        if (!read_crime.isIDUnknown() && (repeated_id == false)){
            
            inputCrimes[used] = read_crime;
            used++;
            
        }  
        read++;
    }
    
   
    
    cout << "Records read: " << n << endl;
    cout << used << " crimes with valid and non-repeated ID: " << endl;
    // Show all the Crimes in the array
    for (int i=0; i < used; i++) {
        
        cout << inputCrimes[i].toString() << endl;
    }
    
    // Compute the histograms by day of the week and
    //    by hour of the day.
    ComputeHistogramArrayCrimes(inputCrimes, used, 0, frequencyByDay);
    ComputeHistogramArrayCrimes(inputCrimes, used, 1, frequencyByHour);
            
    // Show the histograms by day of the week and
    //    by hour of the day.
    cout << "\nHistogram by day of the week:";
    PrintHistogramArrayCrimes(0, frequencyByDay);
    

    cout << endl << "\nHistogram by hour of the day:";
    PrintHistogramArrayCrimes(1, frequencyByHour);

    // Compute the maximum cumulative number of crimes in a week day 
    //    and the maximum cumulative number of crimes in a day hour.
    int max_value_crimes_day = 0;
    int pos_max_value_crimes_day = 0;
    ComputeMaxPosArrayInts(frequencyByDay, 7, max_value_crimes_day,
                                                    pos_max_value_crimes_day);
    int max_value_crimes_hour, pos_max_value_crimes_hour = 0;
    ComputeMaxPosArrayInts(frequencyByHour, 24, max_value_crimes_hour, 
                                                    pos_max_value_crimes_hour);
   
    // Show the maximum cumulative number of crimes in a week day 
    //    and the maximum cumulative number of crimes in a  day hour.
    cout << endl << "\nMaximum cumulative number of crimes in a week day: " 
            << max_value_crimes_day << endl;
    cout << "Day of maximum cumulative number of crimes in a week day: "  
            << DateTime::dayName(pos_max_value_crimes_day) << endl;
    cout << "Maximum cumulative number of crimes in a day hour: " 
            << max_value_crimes_hour << endl;
    cout << "Hour of maximum cumulative number of crimes in a day hour: "  
            << pos_max_value_crimes_hour << endl;
    
    // Compute and sort an array with those Crimes 
    //    that verify the condition that the read field is equals to 
    //    the given value.
    int selected = 0; // number of crimes selected for the array
    SelectWhereEQArrayCrimes(inputCrimes, used, field_name, field_value,  
        selectedCrimes, selected);
    SortArrayCrimes(selectedCrimes, selected);
    
    cout << "\nSorted list of selected crimes where " << field_name << "=" << 
        field_value << ":" << endl<<endl;
    
    // Show the array content
    PrintArrayCrimes(selectedCrimes, selected);
    
    return 0;
    
}
