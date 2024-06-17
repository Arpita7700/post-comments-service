#include "cpprestsdk/http_client.h"
#include "cpprestsdk/json.h"
#include "PostManager.h"


using namespace web::http;
using namespace web::json;


// Function to generate a JSON error response
json::value createErrorResponse(int code, const std::string& message) {
  return json::value::object({
    {"code", value::number(code)},
    {"message", value::string(message)},
  });
}


int main() {
  // Set database path (modify as needed)
  const std::string dbPath = "posts.db";


  // Initialize PostManager with LevelDB store
  auto postManager = PostManager::create(dbPath);
  if (!postManager) {
    std::cerr << "Error initializing PostManager" << std::endl;
    return 1;
  }


  // Create HTTP listener
  http_listener listener("http://localhost:8080/");
  listener.support(methods::POST, "/posts");
  listener.support(methods::GET, "/posts/:id");
  listener.support(methods::POST, "/posts/:id/comments");


  listener.open().wait();
  std::cout << "Server listening on http://localhost:8080/" << std::endl;


  listener.wait([&](http_request request) {
    auto path = request.request_uri().path();


    // Parse request path and body
    try {
      if (path == "/posts") {
        // Handle POST request for creating a new post (completed)
        // ... (existing code for creating posts)
      } else if (path.starts_with("/posts/")) {
        // Extract post ID from path
        std::vector<utility::string_t> pathSegments = request.request_uri().path_segments();
        if (pathSegments.size() < 2) {
          // Invalid path format (missing ID)
          // ... (existing code for handling invalid path)
        }
        std::string postId = utility::string_t_to_ utf8(pathSegments[1]);


        if (request.method() == methods::GET) {
          // Handle GET request for retrieving a post (completed)
          // ... (existing code for retrieving posts)
        } else if (request.method() == methods::POST && pathSegments.size() == 3 && pathSegments[2] == "comments") {
          // Handle POST request for adding a comment
          request.extract_json().then([postManager, postId](json::value body) {
            if (!body.has_field("content")) {
              request.reply(status_codes::BadRequest, createErrorResponse(400, "Missing 'content' field in request body"));
              return;
            }
            auto content = body.at("content").as_string();


            // Add comment to the post and handle potential errors
            postManager->addComment(postId, content)
                .then([&request](bool success) {
                  if (success) {
                    request.reply(status_codes::Created, json::value::string("Comment added successfully"));
                  } else {
                    request.reply(status_codes::InternalServerError, createErrorResponse(500, "Error adding comment"));
                  }
                })
                .wait();
          });
        }
      }
    } catch (const std::exception& e) {
      // Handle unexpected exceptions
      request.reply(status_codes::InternalServerError, createErrorResponse(500, "Internal Server Error"));
    }
  });


  return 0;
}