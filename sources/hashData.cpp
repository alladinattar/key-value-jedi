#include "hashData.hpp"

#include "iostream"
#include "picosha2.h"



#include <boost/log/trivial.hpp>




void rocksMapHasher::hashStorage(std::string familyName,
                                 std::map<std::string, std::string> kvStorage, std::string logLevel) {

  std::map<std::string, std::string> hashed;
  for (auto const& kv : kvStorage) {
    std::string hash_hex_str;
    picosha2::hash256_hex_string(kv.first + kv.second, hash_hex_str);
    hashed[kv.first] = hash_hex_str;

    BOOST_LOG_TRIVIAL(logLevel.) << "Family "<<familyName<<"->" <<kv.first<<"  hashed";
  }
  hashedMap_[familyName] = hashed;
  hashed.clear();
}

void rocksMapHasher::startHashing(
    std::string familyName, std::map<std::string, std::string> kvStorage, std::string logLevel) {
  familyPool_.enqueue([this, familyName, kvStorage]() {
    this->hashStorage(familyName, kvStorage, logLevel);
  });
}
