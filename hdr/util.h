#pragma once
#include "parse.h"
#include "constants.h"
#include<iostream>
using namespace std;

unordered_map<string,vector<string> > invalidinputs;
unordered_map<int,string> intstringtime;

unordered_map<int,pair<int,int>> rangeMap;
// MINUTE, HOUR, DAY_OF_MONTH, MONTH, DAY_OF_WEEK
// 0-59, 0-23, 1-31, 1-12, 1-7
void initRangeMap(){
    rangeMap[MINUTE]=make_pair(0,59);
    rangeMap[HOUR]=make_pair(0,23);
    rangeMap[DAY_OF_MONTH]=make_pair(1,31);
    rangeMap[MONTH]=make_pair(1,12);
    rangeMap[DAY_OF_WEEK]=make_pair(1,7);
}

unordered_map<int, string>  outputMap;

bool validateStepValue(string val, int type, string &err) {
    // check if the value is a valid number
    for (char c : val)
    {
        if (!isdigit(c))
        {
            err = "Invalid Input: " + val + " " + getConstantString(type) + " step value should be numeric";
            return false;
        }
    }
    int step = stoi(val);
    if(step==0){
        err = "Invalid Input: " + val + " " + getConstantString(type) + " step value should greater than 0";
        return false;
    }
    // check if the value is in the range
    if (stoi(val) >= rangeMap[type].first && stoi(val) <= rangeMap[type].second)
    {
        return true;
    }
    else
    {
        err = "Invalid Input: " + val + " " + getConstantString(type) + " step value should be in range " + to_string(rangeMap[type].first) + "-" + to_string(rangeMap[type].second);
        return false;
    }
}

// validate minute if it's in range 0-59
bool validateMinute(string minute, string& err)
{
    // if any one of characters are not numeric, return err
    for (char c : minute)
    {
        if (!isdigit(c))
        {
            err = "Invalid Input: " + minute + " Minute should be in the format of 0-59";
            return false;
        }
    }
    // convert minute to int
    // check if minute is in range 0-59
    if (stoi(minute) >= 0 && stoi(minute) <= 59)
    {
        return true;
    }
    else
    {
        err = "Invalid Input: " + minute + " Minute should be in range 0-59";
        return false;
    }
}


// validate hour if it's in range 0-23
bool validateHour(string hour, string& err)
{
    // if any one of characters are not numeric, return err
    for (char c : hour)
    {
        if (!isdigit(c))
        {
            err = "Invalid Input: " + hour + " Hour should be in the format of 0-23";
            return false;
        }
    }
    // convert hour to int;
    // check if hour is in range 0-23
    if (stoi(hour) >= 0 && stoi(hour) <= 23)
    {
        return true;
    }
    else
    {
        err = "Invalid Input: " + hour + " Hour should be in range 0-23";
        return false;
    }
}

// validate month if it's in range 1-12
bool validateMonth(string& month, string& err)
{
   
    // if any one of characters are not numeric, return err
    for (char c : month)
    {
        if (!isdigit(c))
        {
            err = "Invalid Input: "+ month + " " + "Month should be given in format 1-12";
            return false;
        }
    }
    if(stoi(month) >= 1 && stoi(month) <= 12)
    {
        return true;
    }
    else
    {
        err = "Invalid Input: " + month + " " + "Month should be in range 1-12";
        return false;
    }
}

// validate day of month if it's in range 1-31
bool validateDayOfMonth(string day, string& err)
{
    // if any one of characters are not numeric, return err
    for (char c : day)
    {
        if (!isdigit(c))
        {
            err = "Invalid Input: " + day + " Day of month should be in the format of " + to_string(rangeMap[DAY_OF_MONTH].first) + "-" + to_string(rangeMap[DAY_OF_MONTH].second);
            return false;
        }
    }
    // convert day to int
    int dayInt = stoi(day);
    // check if day is in range start-end ranges
    if (dayInt >= rangeMap[DAY_OF_MONTH].first && dayInt <= rangeMap[DAY_OF_MONTH].second)
    {
        return true;
    }
    else
    {
        err = "Invalid Input: " + day + " DayofMonth should be in range " + to_string(rangeMap[DAY_OF_MONTH].first) + "-" + to_string(rangeMap[DAY_OF_MONTH].second);
        return false;
    }
}

// validate day of week if it's in range 1-7 or in the SUN-SAT
bool validateDayOfWeek(string& day, string& err)
{
    
    for (char c : day)
    {
        // if any one of characters are not numeric, return err
        if (!isdigit(c))
        {
            err = "Invalid Input: " +day + " Day of week should be in the format of 1-7 or SUN-SAT";
            return false;
        }
    }
    if(stoi(day) >= 1 && stoi(day) <= 7)
    {
        return true;
    }
    else
    {
        err = "Invalid Input: " + day + " Day of week should be in range 1-7 or SUN-SAT";
        return false;
    }
}



//validate function to call respective validation function based on type
bool validate(string& value, int type, string& err) {
    //switch case on type for month, hour, minute, day of week, day of month
    switch(type) {
        case MONTH: {
            if(!validateMonth(value, err)) {
                return false;
            }
            break;
        }
        case HOUR: {
            if(!validateHour(value, err)) {
                return false;
            }
            break;
        }
        case MINUTE: {
            if(!validateMinute(value, err)) {
                return false;
            }
            break;
        }
        case DAY_OF_WEEK: {
            if(!validateDayOfWeek(value, err)) {
                return false;
            }
            break;
        }
        case DAY_OF_MONTH: {
            if(!validateDayOfMonth(value, err)) {
                return false;
            }
            break;
        }
    }
    return true;
}


std::vector<int> removeDupAndSort(std::vector<int> &values){
    set<int> s;
    vector<int> uniqueVal;
    for(int i=0;i<values.size();i++)
        s.insert(values[i]);
    
    for(auto i:s)
        uniqueVal.push_back(i);
    
    return uniqueVal;
}


string convertOutputToString(vector<int>& curParsedValues) {
    // remove duplicate values and sort
    curParsedValues = removeDupAndSort(curParsedValues);
    std::ostringstream oss;
    for (size_t i = 0; i < curParsedValues.size(); ++i)
    {
        oss << curParsedValues[i];
        if (i != curParsedValues.size() - 1)
        {
            oss << ' ';
        }
    }
    return oss.str();
}


string generateOutputString(vector<string> outputValues)
{
    swap(outputValues[2], outputValues[3]);
    string res = "";
    for (int i = 0; i < outputValues.size(); i++)
    {
        res += outputValues[i];
        if (i != outputValues.size() - 1)
        {
            res += "\n";
        }
    }
    return res;
}


void updateEndValueForDayOfMonth() {
    // get string from outputMap[MONTH] and split it by space
    string month = outputMap[MONTH];
    std::istringstream iss(month);
    std::string token;
    std::vector<std::string> monthValues;
    while (std::getline(iss, token, ' '))
    {
        monthValues.push_back(token);
    }
    if(monthValues.size() == 1) {
        // get the max number of days in a month
        string monthValue = monthValues[0];
        int monthInt = stoi(monthValue);
        int maxDays = daysInMonth[monthInt];
        rangeMap[DAY_OF_MONTH].second = maxDays;
    }
}
