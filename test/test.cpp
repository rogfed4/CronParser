#include <string>
#include <iostream>
#include "../hdr/parse.h"
using namespace std;
void generateOutput(vector<string> values, string type, string &res)
{
    res += type;
    for (int i = 0; i < values.size(); i++)
    {
        if (i == values.size() - 1)
            res += values[i];
        else
            res += values[i] + " ";
    }
    res += "\n";
}

void generateOutputFromMap(unordered_map<string, vector<string> > outputMap, string &output)
{
     //generateOutput in order
    generateOutput(outputMap["minute"], "minute        ", output);
    generateOutput(outputMap["hours"], "hour          ", output);
    generateOutput(outputMap["DayofMonth"], "day of month  ", output);
    generateOutput(outputMap["Month"], "month         ", output);
    generateOutput(outputMap["DayofWeek"], "day of week   ", output);
    generateOutput(outputMap["command"], "command       ", output); 
}

void test_1()
{
    unordered_map<string, vector<string>> outputMap;
    outputMap["minute"] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
                           "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27",
                           "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
                           "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53",
                           "54", "55", "56", "57", "58", "59"};
    outputMap["hours"] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
                          "15", "16", "17", "18", "19", "20", "21", "22", "23"};
    outputMap["DayofMonth"] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
                               "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27",
                               "28", "29", "30", "31"};
    outputMap["Month"] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
    outputMap["DayofWeek"] = {"1", "2", "3", "4", "5", "6", "7"};
    outputMap["command"] = {"user"};

    string expectedOutput = "";
    generateOutputFromMap(outputMap, expectedOutput);
    expectedOutput = expectedOutput.substr(0, expectedOutput.size() - 1);

    string res = "";

    try
    {
        Parser parser("* * * * * user");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << "Test case failed" << endl;
        return;
    }

    if (res != expectedOutput)
    {
        cout << "Test failed" << endl;
        cout << "Expected Output: " << expectedOutput << endl;
        cout << "Actual Output: " << res << endl;
        
        return;
    }

    cout << "Test_1 is passed" << endl;
}

void test_2()
{
    //map of type to values
    unordered_map<string, vector<string> > outputMap;
    outputMap["minute"] = {"0", "15", "30", "45"};
    outputMap["hours"] = {"0"};
    outputMap["DayofMonth"] = {"1", "15"};
    outputMap["Month"] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11","12"};
    outputMap["DayofWeek"] = {"1", "2", "3", "4", "5"};
    outputMap["command"] = {"/usr/bin/find"};
    // generate output from the map
    string output = "";
    //function to generate output from the map
    generateOutputFromMap(outputMap, output);
    output = output.substr(0, output.size() - 1);
    string expectedOutput= output;
    string res="";
    
    try
    {
        Parser parser("*/15 0 1,15 * 1-5 /usr/bin/find");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << "Test case 2 failed" << endl;
        return;
    }

    if (res != expectedOutput)
    {
        cout << output << endl;
        cout << output.length() << endl;
        cout << res << endl;
        // print length
        cout << res.length() << endl;        
        cout << "Test_2 is not passed;\n";
        return;
    }
    cout << "Test_2 is passed;\n";
}

void test_3()
{
    unordered_map<string, vector<string>> outputMap;
    outputMap["minute"] = {"1", "2", "3"};
    outputMap["hours"] = {"7", "8"};
    outputMap["DayofMonth"] = {"21", "22", "23", "24", "25"};
    outputMap["Month"] = {"11", "12"};
    outputMap["DayofWeek"] = {"1", "2", "3", "4", "5", "6", "7"};
    outputMap["command"] = {"usr/gofind"};
    // generate output from the map
    string output = "";
    //function to generate output from the map
    generateOutputFromMap(outputMap, output);
    output = output.substr(0, output.size() - 1);
    string expectedOutput= output;
    string res="";
    try
    {
        Parser parser("1-3 7-8 21-25 11-12 1-7 usr/gofind");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }

    if (res != expectedOutput)
    {
        cout << "Test_3 is not passed;\n";
        return;
    }
    cout << "Test_3 is passed;\n";
}


void test_6()
{
    string res, output = "Invalid input \n";
    try
    {
        Parser parser("1,2 Cron");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
    if (res != output)
    {
        cout << "Test_6 is not passed;\n";
        return;
    }
    cout << "Test_6 is passed;\n";
}

void test_7()
{
    string res, output = "Invalid input \n";
    try
    {
        Parser parser("1,2 */2 * * 1-4 /usr/bin/find /usr/bin/parse");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
    if (res != output)
    {
        cout << "Test_7 is not passed;\n";
        return;
    }
    cout << "Test_7 is passed;\n";
}

void test_8()
{
    string res, output = "Invalid input \n";
    try
    {
        Parser parser("");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
    if (res != output)
    {
        cout << "Test_8 is not passed;\n";
        return;
    }
    cout << "Test_8 is passed;\n";
}

void test_10()
{
    unordered_map<string, vector<string>> outputMap;
    outputMap["minute"] = { "1","4","6","7","10", "13", "16","19","22","25","27",
                           "30","33","36","40","42","44","46","48","50","52",
                           "54","55","56","58"};
    outputMap["hours"] = {"0","3","6","9","12","15","18","21"};
    outputMap["DayofMonth"] = {"2","4", "21","23", "25", "27","29","31"};
    outputMap["Month"] = {"1", "3","7", "9", "11"};
    outputMap["DayofWeek"] = {"1", "3", "5","7"};
    outputMap["command"] = {"/usr/bin/find"};
    string expectedOutput = "";
    generateOutputFromMap(outputMap, expectedOutput);
    expectedOutput = expectedOutput.substr(0, expectedOutput.size() - 1);

    string res = "";

    try
    {
        Parser parser("6,52-25/3,27-38/3,40/2 */3 21-5/2 7-3/2 1/2 /usr/bin/find");
        res = parser.result;
    }
    catch (const std::exception &e)
    {
        cout << "Test case failed" << endl;
        return;
    }

    if (res != expectedOutput)
    {
        cout << "Test failed" << endl;
        cout << "Expected Output: " << expectedOutput << endl;
        cout << "Actual Output: " << res << endl;
        
        return;
    }

    cout << "Test_10 is passed" << endl;
}



int main()
{
    test_1();
    test_2();
    test_3();
    test_6();
    test_7();
    test_8();
    test_10();
    
}