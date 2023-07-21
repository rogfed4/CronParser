#include "../hdr/parse.h"
#include "../hdr/util.h"
#include<iostream>
using namespace std;

std::vector<int> parseRange(std::string& range, int type, std::string& err)
{

    int lower_bound = rangeMap[type].first;
    int upper_bound = rangeMap[type].second;
    std::vector<int> resultValues;

    if (range.find('-') != std::string::npos)
    {
        int start, end;
        std::string rangeStartStr = range.substr(0, range.find('-'));
        std::string rangeEndStr = range.substr(range.find('-') + 1);
        if(rangeStartStr=="" || rangeEndStr==""){
            err="Invalid Input: " + range + " " + getConstantString(type) + " Not a valid range";
            return {};
        } 
        if (!validate(rangeStartStr, type, err) || !validate(rangeEndStr, type, err)) {
            return {};  // Return empty vector if range values are invalid
        }

        start = std::stoi(rangeStartStr);
        end = std::stoi(rangeEndStr);


        if (start >end)
        {
            err="Invalid Input: " + range + " " + getConstantString(type) + " Not a valid range";
            return{};    
        }
        else
        {
            // Range is within the valid range, add values directly
            for (int i = start; i <= end; ++i)
            {
                resultValues.push_back(i % (lower_bound + upper_bound + 1));
            }
        }
    }
    else
    {
        if (range == "*")
        {
            // Wildcard, add all values within the valid range
            for (int i = lower_bound; i <= upper_bound; ++i)
            {
                resultValues.push_back(i);
            }
        }
        else
        {
            if (!validate(range, type, err)) {
                return {};  // Return empty vector if single value is invalid
            }

            int value = std::stoi(range);
            
            resultValues.push_back(value);
        }
    }

    return resultValues;
}

std::vector<int> parseStepRange(std::string& range, int type, std::string& err)
{
    int lower_bound = rangeMap[type].first;
    int upper_bound = rangeMap[type].second;
    std::vector<int> resultValues;

    // Extract the range and step from the input string
    std::string rangeWithoutStep = range.substr(0, range.find('/'));
    std::string stepStr = range.substr(range.find('/') + 1);

    // Validate the step value
    if(!validateStepValue(stepStr, type, err)) {
        return {};  // Return empty vector if step value is invalid
    }
    int step = std::stoi(stepStr);

    // Parse the range part of the input
    std::vector<int> rangeValues = parseRange(rangeWithoutStep, type, err);


    // Handle the case where the range is a single value or wildcard
    if (rangeWithoutStep.find('-') == std::string::npos && rangeWithoutStep != "*" && !rangeValues.empty()) {
        // Add values incrementally from the starting range value
        for (int value = rangeValues[0] + 1; value <= upper_bound; value++) {
            rangeValues.push_back(value);
        }
    }

    // Select values from the range based on the step
    for (int i = 0; i < rangeValues.size(); i += step) {
        resultValues.push_back(rangeValues[i]);
    }

    return resultValues;
}

std::string parseGeneral(const std::string& input, int type, string& err)
{
    //string input;
    //std::transform(input1.begin(), input1.end(), std::back_inserter(input),[](unsigned char c) { return std::tolower(c); });
    std::vector<int> curParsedValues;
    std::istringstream iss(input);
    std::string token;
    if(type==DAY_OF_MONTH) {
            // update end value for day of month based on the month value
            updateEndValueForDayOfMonth();   
        }
    while (std::getline(iss, token, ','))
    {
        if (token.find('/') != std::string::npos)
        {
            std::vector<int> stepRange = parseStepRange(token, type, err);
            if(err.length()!=0)
                return "";
            curParsedValues.insert(curParsedValues.end(), stepRange.begin(), stepRange.end());
        }
        else
        {
            std::vector<int> range = parseRange(token, type, err);
            if(err.length()!=0) {
                return "";
            }
                
            curParsedValues.insert(curParsedValues.end(), range.begin(), range.end());
        }
    }
    return convertOutputToString(curParsedValues);
}

string Parser::parse_input(std::string input)
{
    initRangeMap();
    stringstream ss(input);
    const char delimiter = ' ';
    vector<string> vec;

    string data, minute, hours, day_of_month, month, day_of_week, command;
    while (getline(ss, data, delimiter))
    {
        vec.push_back(data);
    }

    int sz = vec.size();
    if (sz != 6)
    {
        return "Invalid input \n";
    }
    string err = "";
    swap(vec[2], vec[3]);
    vector<string> outputValues;
    int i=0;
    while (i < 5)
    {
        string parsedOutput = parseGeneral(vec[i], i, err);
        if(err.length()!=0)
            return err;
        outputMap[i] = parsedOutput;
        outputValues.push_back(getOutputString(i)+ parsedOutput);
        i++;
    }
    while(i<sz){
        command+=vec[i];
        i++;
    }
    outputMap[i] = command;
    outputValues.push_back(getOutputString(i-1) + command);
    string ans = generateOutputString(outputValues);
    return ans;
    
}

