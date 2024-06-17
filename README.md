Post-Comments Service - README


This project implements a Post-Comments Service allowing users to create posts and add comments to them.


Setting Up and Running the Application


Prerequisites:


* C++ compiler (e.g., GCC, Clang)
*  [cpprestsdk](https://github.com/microsoft/cpprestsdk) - HTTP library
*  [LevelDB](https://github.com/google/leveldb) - Embedded key-value store (for persistence)


Installation:


1. Follow the installation instructions for cpprestsdk based on the operating system.
2. For persistent data storage, install LevelDB and link it to your project.


Building the Project:


Open terminal and navigate to the project directory. Use a build system like CMake or compile directly with the necessary libraries linked.


Running the Server:


Execute the compiled server binary.


Default Configuration:


1.The server listens on port `8080`.
2.The data store  is located at `posts.db`


API Endpoints


1.POST /posts:Create a new post with a JSON request body containing a `content` field.
2.GET /posts/:id: Retrieve a post by ID.
3.POST /posts/:id/comments: Add a comment to a post with a JSON request body   containing a `content` field.


Response Format:


The server responds with JSON following the HTTP status code conventions. Responses include error messages and relevant data for successful operations.


Architecture


The application uses a simple client-server architecture:


1.Client: Sends HTTP requests to the server for creating posts, retrieving posts, and adding         comments.
2.Server:Processes requests, interacts with the data store , and sends JSON responses.


The server leverages the following components:


cpprestsdk:Provides a C++ library for handling HTTP requests and responses.
PostManager:Manages Post objects, handles creation, retrieval, and comment addition.
Data Store:
*      In-memory storage (default) for simple testing.
*      LevelDB for persistent data storage in production environments.


Dependencies and Choices


cpprestsdk: Chosen for its ease of use and cross-platform compatibility for building cross-platform REST APIs.
Data Storage:
* In-memory storage is suitable for simple testing and development.
* LevelDB is chosen as a lightweight embedded key-value store for persistent data storage   in production environments. 


Future Improvements


*  Implement user authentication and authorization mechanisms.
*  Explore more complex data models for posts and comments.
