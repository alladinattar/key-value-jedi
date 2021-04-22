
#include <map>
#include "picosha2.h"
#include "iostream"
#include "utility"
class hashData {
 private:
  std::map<std::string, std::string> storage_;
  std::map<std::string, std::string> hashStorage_;

 public:
  hashData(std::map<std::string, std::string>& kvStorage)
      : storage_(kvStorage) {}
  void hashStorage();
};