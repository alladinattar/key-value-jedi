#include "hashData.hpp"

#include "iostream"
#include "picosha2.h"


#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>




void rocksMapHasher::hashStorage(std::string familyName,
                                 std::map<std::string, std::string> kvStorage/*, boost::log::trivial::severity_level logLevel*/) {

  std::map<std::string, std::string> hashed;
  for (auto const& kv : kvStorage) {
    std::string hash_hex_str;
    picosha2::hash256_hex_string(kv.first + kv.second, hash_hex_str);
    hashed[kv.first] = hash_hex_str;

    //BOOST_LOG_TRIVIAL(severity_level) << "Family "<<familyName<<"->" <<kv.first<<"  hashed";
  }
  mutex.lock();
  hashedMap_[familyName] = hashed;
  hashed.clear();
  mutex.unlock();
}

void rocksMapHasher::startHashing(
    std::string familyName, std::map<std::string, std::string> kvStorage/* boost::log::trivial::severity_level logLevel*/) {
  familyPool_.enqueue([this, familyName, kvStorage/*, logLevel*/]() {
    this->hashStorage(familyName, kvStorage/*, logLevel*/);
  });
}
