#include <string>
#include <iomanip>// changed after Feedback#1 

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    //seconds = 10000; // test the code before implementing the input
    //long hour = seconds/3600;
    //long min = (seconds%3600)/60;
    //long sec = seconds - hour*3600 - min*60;
    long hours = seconds/3600;
    seconds = seconds % 3600; // changed after Feedback#1
    long minutes = seconds / 60; // changed after Feedback#1
    seconds = seconds % 60; // changed after Feedback#1

    //string time = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec); // Error#3: seconds become more than 60!

    // changed after Feedback#1  --> error
    //seconds.insert(0, 2 - hours.length(), '0');// changed after Feedback#1 
    //seconds.insert(0, 2 - minutes.length(), '0');// changed after Feedback#1
    //seconds.insert(0, 2 - seconds.length(), '0');// changed after Feedback#1
    //string time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds); 
 
    // changed after Feedback#1
    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << hours << ":" 
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return stream.str();

}