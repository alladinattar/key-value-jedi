#ifndef INCLUDE_HTMLDOWNLOADER_HPP_
#define INCLUDE_HTMLDOWNLOADER_HPP_
#include <map>
#include "picosha2.h"
#include "iostream"
#include "utility"
#include "map"
#include "ThreadPool.h"

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include "boost/log/sources/severity_logger.hpp"


class rocksMapHasher{
 private:

  std::map<std::string, std::map<std::string,std::string>> rocksMap_;
  std::map<std::string, std::map<std::string,std::string>> hashedMap_;
  ThreadPool familyPool_;
 public:
  std::map<std::string, std::map<std::string,std::string>> getHashedMap(){return hashedMap_;}
  void startHashing(std::string fimilyName, std::map<std::string,std::string> kvStorage);
 explicit rocksMapHasher( int threadNum)
      :  familyPool_(threadNum) {}
  void hashStorage(std::string familyName, std::map<std::string, std::string> kvStorage);
};
#endif  // INCLUDE_HTMLDOWNLOADER_HPP_
