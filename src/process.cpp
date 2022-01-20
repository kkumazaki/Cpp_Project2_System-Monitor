#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
//int Process::Pid() { return LinuxParser::Pids()[0]; }
//int Process::Pid() { return LinuxParser::Pids()[Process::index_]; }
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::CpuUtilization(Process::Pid()); }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Process::Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
//long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()) ; }
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(Process::Pid()) ; }// change after Feedback#2

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a) const { return true; }  // changed after Feedback#1: This causes a warning