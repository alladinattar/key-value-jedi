// Copyright 2021 Rinat Mukaev <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <assert.h>

#include <utility>

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
 public:
  rocksdbWrapper(int columns, int family, std::string path, rocksMapHasher& hasher)
      : columnSize_(columns), familyNum_(family), path_(std::move(path)), hasherObj_(hasher) {}
  int getFamilyNum();
  void createDatabase();
  void getFamiliesFromBD();
  void pushData();
  void migrateDataToMap();
  ~rocksdbWrapper() { delete db_;}
};

#endif  // INCLUDE_HEADER_HPP_
