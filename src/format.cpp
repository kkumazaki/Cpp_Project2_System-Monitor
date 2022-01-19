#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    //seconds = 10000; // test the code before implementing the input
    long hour = seconds/3600;
    long min = (seconds%3600)/60;
    long sec = seconds - hour*3600 - min*60;

    string time = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);
    return time; 
}