
#include <map>
#include "picosha2.h"
#include "iostream"
#include "utility"
#include "map"
class rocksMapHasher{
 private:
  std::map<std::string, std::map<std::string,std::string>> rocksMap_;
  std::map<std::string, std::map<std::string,std::string>> hashedMap_;
 public:
 rocksMapHasher(std::map<std::string, std::map<std::string,std::string>>& rocksMap)
      : rocksMap_(rocksMap) {}
  std::map<std::string, std::map<std::string,std::string>> hashStorage();
};