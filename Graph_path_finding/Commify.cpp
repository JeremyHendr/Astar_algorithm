/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Commify.cpp file
* Contains method definition for the Commify class
*/

#include "Commify.h"

using namespace std;

// Constructor definition
Commify::Commify(int64_t v): value(v) {}


// Definition of the operator<< overload method
ostream& operator<<(ostream& os, const Commify& commify){
    /* Method to overload the << operator
     *
     * @param ostream& os, const Commify& commify
     * @return ostream&
     */

    // Convert the value to a string with comma formatting
    string result = to_string(commify.value);
    int insertPosition = result.length() - 3;

    // Insert the comma for the thousands
    result.insert(insertPosition, ",");

    // Send the formatted string to the output stream
    os << result;
    return os;

}
