/*
* Project: A_star algorithm
* Group: De Sue Léo - Hendrikse Jeremy - Ortstadt Julius
* Robo4 - 2024/2025
*
* Commify.h file
* Contains header definition for the Commify class
*/

#ifndef COMMIFY_H
#define COMMIFY_H

#include <iostream>
#include <cstdint>

using namespace std;

class Commify {
    public:
        explicit Commify(int64_t v);

        // Friend function to overload the << operator for formatted output
        friend ostream& operator<<(ostream& os, const Commify& commify);

    private:
        int64_t value;

};

#endif // COMMIFY_H
