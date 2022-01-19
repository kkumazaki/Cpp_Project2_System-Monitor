#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
// Reference: https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
//            Total used memory = MemTotal - MemFree
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float memTotal, memFree, memUtil;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:")
          memTotal = std::stof(value);
        if (key == "MemFree:")
          memFree = std::stof(value);
      }
    }
  }
  memUtil = (memTotal - memFree)/memTotal;
  return memUtil;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string value;
  long upTime;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  upTime = std::stof(value);
  return upTime; 
}

// TODO: Read and return the number of jiffies for the system
// I don't use it
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// I don't use it
long LinuxParser::ActiveJiffies(int pid) { return 0; }

// TODO: Read and return the number of active jiffies for the system
// I don't use it
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
// I don't use it
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// reference1: https://man7.org/linux/man-pages/man5/proc.5.html
// reference2: https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
//vector<string> LinuxParser::CpuUtilization(int pid) {
float LinuxParser::CpuUtilization(int pid) {
  string line;
  string v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17;
  long totalTime, seconds;
  float cpuUtil;
  std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> v1>>v2>>v3>>v4>>v5>>v6>>v7>>v8>>v9>>v10>>v11>>v12>>v13>>v14>>v15>>v16>>v17;
  }
  totalTime = (stol(v14)+stol(v15)+stol(v16)+stol(v17)) / sysconf(_SC_CLK_TCK);
  seconds = LinuxParser::UpTime() - LinuxParser::UpTime(pid);
  cpuUtil = 100. * ((float)totalTime  / (float)seconds);

  return cpuUtil;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  int totalProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes")
          totalProcesses = std::stoi(value);
      }
    }
  }
  return totalProcesses;  
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  int runningProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running")
          runningProcesses = std::stoi(value);
      }
    }
  }
  return runningProcesses;  
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line, value;
  std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return value; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Vmsize:")
          return value;
      }
    }
  }
  return value; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:")
          return value;
      }
    }
  }
  return value; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, name, x, value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> x >> value) {
        if (value == LinuxParser::Uid(pid)) {
          return name;
        }
      }
    }
  }
  return name;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// reference: https://man7.org/linux/man-pages/man5/proc.5.html
long LinuxParser::UpTime(int pid) {
  string line;
  string v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22;
  long upTime;
  std::ifstream stream(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> v1>>v2>>v3>>v4>>v5>>v6>>v7>>v8>>v9>>v10>>v11>>v12>>v13>>v14>>v15>>v16>>v17>>v18>>v19>>v20>>v21>>v22;
  }
  upTime = stol(v22) / sysconf(_SC_CLK_TCK);
  return upTime; 
}
