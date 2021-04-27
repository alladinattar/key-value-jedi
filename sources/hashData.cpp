#include "hashData.hpp"

#include "iostream"
#include "picosha2.h"


#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>





void rocksMapHasher::hashStorage(std::string familyName,
                                 std::map<std::string, std::string> kvStorage) {


  std::map<std::string, std::string> hashed;
  for (auto const& kv : kvStorage) {
    std::string hash_hex_str;
    picosha2::hash256_hex_string(kv.first + kv.second, hash_hex_str);
    hashed[kv.first] = hash_hex_str;
  }
  hashedMap_[familyName] = hashed;
  BOOST_LOG_TRIVIAL(trace) << "Family "<<familyName<<" hashed";
  hashed.clear();
}

void rocksMapHasher::startHashing(
    std::string familyName, std::map<std::string, std::string> kvStorage) {
  familyPool_.enqueue([this, familyName, kvStorage]() {
    this->hashStorage(familyName, kvStorage);
  });
}
