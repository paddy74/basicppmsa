#pragma once

#include <cpprest/http_msg.h>

namespace basicppmsa::base::core
{
/**
 * @brief Provides an interface to implement handlers for each HTTP method
 *
 */
class Controller
{
public:
    virtual void handleGet(web::http::http_request message) = 0;
    virtual void handlePut(web::http::http_request message) = 0;
    virtual void handlePost(web::http::http_request message) = 0;
    virtual void handleDelete(web::http::http_request message) = 0;
    virtual void handlePatch(web::http::http_request messge) = 0;
    virtual void handleHead(web::http::http_request message) = 0;
    virtual void handleOptions(web::http::http_request message) = 0;
    virtual void handleTrace(web::http::http_request message) = 0;
    virtual void handleConnect(web::http::http_request message) = 0;
    virtual void handleMerge(web::http::http_request message) = 0;
};

}  // namespace basicppmsa::base::core
