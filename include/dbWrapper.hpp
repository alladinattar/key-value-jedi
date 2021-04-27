// Copyright 2021 Rinat Mukaev <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <assert.h>

#include <utility>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include "iostream"
#include "rocksdb/db.h"
#include "ThreadPool.h"
#include "hashData.hpp"
class rocksdbWrapper {
 private:
  int columnSize_;
  int familyNum_;
  std::string path_;
  rocksdb::DB* db_;
  std::vector<std::string> families_;
  rocksMapHasher& hasherObj_;
  std::map<std::string, std::map<std::string,std::string>> mapa_;
 public:
  rocksdbWrapper(int columns, int family, std::string path, rocksMapHasher& hasher)
      : columnSize_(columns), familyNum_(family), path_(std::move(path)), hasherObj_(hasher) {}
  rocksdbWrapper(std::map<std::string, std::map<std::string,std::string>> mapa, std::string path, rocksMapHasher& hasher): columnSize_(0), familyNum_(mapa.size()), path_(path), hasherObj_(hasher),mapa_(mapa){};
  void createOutputDatabase();
  std::vector<std::string> getFamilyNum();
  void createDatabase();
  void createDatabase(std::map<std::string, std::map<std::string,std::string>> mapa);
  void getFamiliesFromBD();
  void pushData();
  void migrateDataToMap(/*boost::log::trivial::severity_level logLevel*/);
  ~rocksdbWrapper() { delete db_;}
};

#endif  // INCLUDE_HEADER_HPP_
