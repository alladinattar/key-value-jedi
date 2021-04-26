// Copyright 2021 Rinat Mukaev <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <assert.h>

#include <utility>

#include "iostream"
#include "rocksdb/db.h"

class rocksdbWrapper {
 private:
  int columnSize_;
  int familyNum_;
  std::string path_;
  rocksdb::DB* db_;
  std::vector<std::string> families_;

 public:
  rocksdbWrapper(int columns, int family, std::string path)
      : columnSize_(columns), familyNum_(family), path_(std::move(path)) {}
  int getFamilyNum();
  void createDatabase();
  void getFamiliesFromBD();
  void pushData();
  void pullData();
  void migrateDataToMap(
      std::map<std::string, std::map<std::string, std::string>>&);
  ~rocksdbWrapper() {}
};

#endif  // INCLUDE_HEADER_HPP_
