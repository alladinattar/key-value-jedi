#include "hashData.hpp"
#include "iostream"
#include "picosha2.h"

std::map<std::string, std::map<std::string,std::string>> rocksMapHasher::hashStorage() {
  std::map<std::string, std::string> hashed;
  for (auto const& family : rocksMap_) {
    for (auto const& kv : family.second){
      std::string hash_hex_str;
      picosha2::hash256_hex_string(kv.first + kv.second, hash_hex_str);
      hashed[kv.first] = hash_hex_str;
    }
    hashedMap_[family.first] = hashed;
    hashed.clear();
  }
  return hashedMap_;


}