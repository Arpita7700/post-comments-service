#pragma once


#include <string>


#include <leveldb/db.h>


class LevelDBStore {
public:
  LevelDBStore(const std::string& dbPath);


  // Store a key-value pair
  void Put(const std::string& key, const std::string& value);


  // Retrieve a value by key
  std::string Get(const std::string& key);
};