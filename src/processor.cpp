#include "processor.h"
#include "linux_parser.h"


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::string line;
  std::string key;
  std::string val1, val2, val3, val4, val5, val6, val7, val8, val9, val10;
  float idle, nonidle, utilization; 
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> val1 >> val2 >> val3 >> val4 >> val5 >> val6 >> val7 >> val8 >> val9 >> val10) {
        if (key == "cpu")
          idle = std::stof(val4 + val5); // idle = val4 (idle) + val5 (iowait)
          nonidle = std::stof(val1 + val2 + val3 + val6 + val7 + val8 + val9 + val10);
      }
    }
  }
  utilization = nonidle / (idle + nonidle);
  return utilization;
}