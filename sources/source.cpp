// Copyright 2020 Your Name <your_email>

#include <header.hpp>

#include "iostream"
#include "stdlib.h"

void storagePlaceholder(int dbSize, std::string path) {
  rocksdb::DB* db;
  rocksdb::Options options;
  options.create_if_missing = true;
  options.error_if_exists = true;
  rocksdb::Status status = rocksdb::DB::Open(options, path, &db);
  if (!status.ok()) std::cerr << status.ToString() << std::endl;
  std::string value;
  for (int i = 0; i < dbSize; ++i) {
    status = db->Put(rocksdb::WriteOptions(), "key" + std::to_string(i),
                     std::to_string(i));
    assert(status.ok());
    status = db->Get(rocksdb::ReadOptions(), "key" + std::to_string(i), &value);
    assert(status.ok());
    std::cout << "key" << i << "  " << value;
  }
  delete db;
}