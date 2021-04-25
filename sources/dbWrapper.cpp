// Copyright 2020 Your Name <your_email>

#include "dbWrapper.hpp"
#include "iostream"



void rocksdbWrapper::openWithFamilies() {
  rocksdb::Options options;
  options.create_if_missing = true;
  rocksdb::DB* db;

  std::vector<rocksdb::ColumnFamilyDescriptor> column_families;
  // have to open default column family
  /*column_families.push_back(rocksdb::ColumnFamilyDescriptor(
      rocksdb::kDefaultColumnFamilyName, rocksdb::ColumnFamilyOptions()));
  // open the new one, too
  column_families.push_back(rocksdb::ColumnFamilyDescriptor(
      "family_1", rocksdb::ColumnFamilyOptions()));
  column_families.push_back(rocksdb::ColumnFamilyDescriptor(
      "family_2", rocksdb::ColumnFamilyOptions()));*/
  std::vector<rocksdb::ColumnFamilyHandle*> handles;
  rocksdb::Status s = rocksdb::DB::Open(rocksdb::DBOptions(), path_, column_families, &handles, &db);
  assert(s.ok());

  std::vector<std::string> families;
  db_->ListColumnFamilies(options,path_, &families);
  for (auto& family : families){
    std::cout<<family<<std::endl;

  }
}
void rocksdbWrapper::loadNewDB() {
  rocksdb::Options options;
  options.create_if_missing = true;
  options.error_if_exists = true;
  rocksdb::Status status = rocksdb::DB::Open(options, path_, &db_);
  if (!status.ok()) std::cerr << status.ToString() << std::endl;
  std::string value;

  rocksdb::ColumnFamilyHandle* cf;
  status = db_->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "family_1", &cf);
  assert(status.ok());
  db_->DestroyColumnFamilyHandle(cf);

  rocksdb::ColumnFamilyHandle* cf1;
  status = db_->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), "family_2", &cf1);
  assert(status.ok());
  db_->DestroyColumnFamilyHandle(cf1);

  delete db_;
  /*std::vector<std::string> families;
  db_->ListColumnFamilies(options,"/home/rinat/labs/databasa", &families);
  for (auto& family : families){
    std::cout<<family<<std::endl;

  }*/

  /*for (int i = 0; i < dbSize_; ++i) {
    status = db_->Put(rocksdb::WriteOptions(), "key" + std::to_string(i),
                     std::to_string(i));
    assert(status.ok());
    status = db_->Get(rocksdb::ReadOptions(), "key" + std::to_string(i), &value);
    assert(value == std::to_string(i));
  }
  */
}

void rocksdbWrapper::migrateDataToMap(std::map<std::string,std::string>& kvStorage){
  rocksdb::Iterator* it = db_->NewIterator(rocksdb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    kvStorage[it->key().ToString()] = it->value().ToString();
  }
  assert(it->status().ok());  // check for any errors found during the scan
}
