// Copyright 2021 Rinat Mukaev <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include "rocksdb/db.h"
#include <assert.h>

#include <utility>
#include "iostream"

class rocksdbWrapper{
 private:
  int dbSize_;
  std::string path_;
  rocksdb::DB* db_;

 public:
  rocksdbWrapper(int dbSize, std::string path): dbSize_(dbSize), path_(std::move(path)){}
  void loadNewDB();
  void openWithFamilies();
  void migrateDataToMap(std::map<std::string,std::string>& kvStorage);
  ~rocksdbWrapper(){}
};



#endif // INCLUDE_HEADER_HPP_
