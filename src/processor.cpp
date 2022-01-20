#include "processor.h"
#include "linux_parser.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::string line;
  std::string key;
  std::string val1, val2, val3, val4, val5, val6, val7, val8, val9, val10;
  float idle, nonidle, utilization; 
  //std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename); // change after Feedback#2
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> val1 >> val2 >> val3 >> val4 >> val5 >> val6 >> val7 >> val8 >> val9 >> val10) {
        //if (key == "cpu")
        if (key == "cpu"){ // change after Feedback#2
          //idle = std::stof(val4 + val5); // idle = val4 (idle) + val5 (iowait)
          idle = std::stof(val4) + std::stof(val5); // idle = val4 (idle) + val5 (iowait)
          nonidle = std::stof(val1) + std::stof(val2) + std::stof(val3) + std::stof(val6) + std::stof(val7) + std::stof(val8) + std::stof(val9) + std::stof(val10);
        } // change after Feedback#2
      }
    }
  }
  utilization = nonidle / (idle + nonidle);
  return utilization;
}