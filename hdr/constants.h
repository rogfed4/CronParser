#pragma once
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


// define constants for Minute, Hour, Month, Day of Month, Day of Week as int
const int MINUTE = 0;
const int HOUR = 1;
const int MONTH = 2;
const int DAY_OF_MONTH = 3;
const int DAY_OF_WEEK = 4;
const int COMMNAD = 5;

const std::vector<int> daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// utility function to return a string for the above int constants
string getConstantString(int constant)
{
    switch (constant)
    {
        case MINUTE:
            return "minute        ";
        case HOUR:
            return "hour          ";
        case MONTH:
            return "month         ";
        case DAY_OF_MONTH:
            return "day of month  ";
        case DAY_OF_WEEK:
            return "day of week   ";
        case COMMNAD:
            return "command       ";
        default:
            return "";
    }
}

