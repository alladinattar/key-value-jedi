// Copyright 2020 Your Name <your_email>

#include "dbWrapper.hpp"
#include "iostream"

void rocksdbWrapper::loadNewDB() {
  rocksdb::Options options;
  options.create_if_missing = true;
  //options.error_if_exists = true;
  rocksdb::Status status = rocksdb::DB::Open(options, path_, &db_);
  if (!status.ok()) std::cerr << status.ToString() << std::endl;
  std::string value;
  for (int i = 0; i < dbSize_; ++i) {
    status = db_->Put(rocksdb::WriteOptions(), "key" + std::to_string(i),
                     std::to_string(i));
    assert(status.ok());
    status = db_->Get(rocksdb::ReadOptions(), "key" + std::to_string(i), &value);
    assert(value == std::to_string(i));
  }
}

void rocksdbWrapper::migrateDataToMap(std::map<std::string,std::string>& kvStorage){
  rocksdb::Iterator* it = db_->NewIterator(rocksdb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    kvStorage[it->key().ToString()] = it->value().ToString();
  }
  assert(it->status().ok());  // check for any errors found during the scan
}
