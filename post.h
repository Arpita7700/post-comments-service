#pragma once


#include <string>
#include <vector>


class Comment {
public:
  Comment(const std::string& content);
  std::string id;
  std::string content;
};


class Post {
public:
  Post(const std::string& content);
  void addComment(const Comment& comment);


  std::string id;
  std::string content;
  std::vector<Comment> comments;
};