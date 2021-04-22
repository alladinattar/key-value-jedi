#include "hashData.hpp"
#include "iostream"
#include "picosha2.h"

void hashData::hashStorage() {
  for (std::map<std::string, std::string>::iterator it = storage_.begin();
       it != storage_.end(); ++it) {
    std::string hash_hex_str;
    std::string proimage = it->first + it->second;
    picosha2::hash256_hex_string((proimage), hash_hex_str);
    std::cout << hash_hex_str<< '\n';
  }

}