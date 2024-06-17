#pragma once


#include <memory>
#include <string>
#include <vector>


#include "LevelDBStore.h"


class PostManager {
public:
  static std::unique_ptr<PostManager> create(const std::string& dbPath);


  // Create a new post
  std::string createPost(const std::string& content);


  // Retrieve a post by ID
  std::shared_ptr<Post> getPost(const std::string& id);


  // Add a comment to a post
  void addComment(const std::string& postId, const std::string& content);


private:
  std::unique_ptr<LevelDBStore> store_;
  std::string generatePostId(); // Helper function for generating unique IDs
};