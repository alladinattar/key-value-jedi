#ifndef INCLUDE_HTMLDOWNLOADER_HPP_
#define INCLUDE_HTMLDOWNLOADER_HPP_
#include <map>
#include "picosha2.h"
#include "iostream"
#include "utility"
#include "map"
#include "ThreadPool.h"

#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>

#include "mutex"
class rocksMapHasher{
 private:

  std::map<std::string, std::map<std::string,std::string>> rocksMap_;
  std::map<std::string, std::map<std::string,std::string>> hashedMap_;
  ThreadPool familyPool_;
  std::mutex mutex;
 public:
  std::map<std::string, std::map<std::string,std::string>> getHashedMap(){return hashedMap_;}
  void startHashing(std::string fimilyName, std::map<std::string,std::string> kvStorage, std::string logLevel);
 explicit rocksMapHasher( int threadNum)
      :  familyPool_(threadNum) {}
  void hashStorage(std::string familyName, std::map<std::string, std::string> kvStore,std::string logLevel);
};
#endif  // INCLUDE_HTMLDOWNLOADER_HPP_
