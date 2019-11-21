#include <msabase/MainServiceController.hpp>

namespace msabase
{
/* Public class methods */

/**
 * @brief Handle HTTP GET requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleGet(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::GET));
}

/**
 * @brief Handle HTTP PUT requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handlePut(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::PUT));
}

/**
 * @brief Handle HTTP POST requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handlePost(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::POST));
}

/**
 * @brief Handle HTTP PATCH requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handlePatch(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::PATCH));
}

/**
 * @brief Handle HTTP DELETE requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleDelete(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::DEL));
}

/**
 * @brief Handle HTTP HEAD requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleHead(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::HEAD));
}

/**
 * @brief Handle HTTP OPTIONS requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleOptions(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::OPTIONS));
}

/**
 * @brief Handle HTTP TRACE requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleTrace(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::TRCE));
}

/**
 * @brief Handle HTTP CONNECT requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleConnect(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::CONNECT));
}

/**
 * @brief Handle HTTP MERGE requests.
 *
 * @param message The HTTP message.
 */
void MainServiceController::handleMerge(web::http::http_request message)
{
    message.reply(
        web::http::status_codes::NotImplemented,
        this->responseNotImpl(web::http::methods::MERGE));
}

/**
 * @brief Initialize REST operation handlers
 *
 */
void MainServiceController::initRestOpHandlers()
{
    this->_listener.support(  // GET
        web::http::methods::GET,
        std::bind(
            &MainServiceController::handleGet, this, std::placeholders::_1));
    this->_listener.support(  // PUT
        web::http::methods::PUT,
        std::bind(
            &MainServiceController::handlePut, this, std::placeholders::_1));
    this->_listener.support(  // POST
        web::http::methods::POST,
        std::bind(
            &MainServiceController::handlePost, this, std::placeholders::_1));
    this->_listener.support(  // PATCH
        web::http::methods::PATCH,
        std::bind(
            &MainServiceController::handlePatch, this, std::placeholders::_1));
    this->_listener.support(  // DEL
        web::http::methods::DEL, std::bind(
                                     &MainServiceController::handleDelete,
                                     this, std::placeholders::_1));
    this->_listener.support(  // HEAD
        web::http::methods::HEAD,
        std::bind(
            &MainServiceController::handleHead, this, std::placeholders::_1));
    this->_listener.support(  // OPTIONS
        web::http::methods::OPTIONS, std::bind(
                                         &MainServiceController::handleOptions,
                                         this, std::placeholders::_1));
    this->_listener.support(  // TRACE
        web::http::methods::TRCE,
        std::bind(
            &MainServiceController::handleTrace, this, std::placeholders::_1));
    this->_listener.support(  // CONNECT
        web::http::methods::CONNECT, std::bind(
                                         &MainServiceController::handleConnect,
                                         this, std::placeholders::_1));
    this->_listener.support(  // MERGE
        web::http::methods::MERGE,
        std::bind(
            &MainServiceController::handleMerge, this, std::placeholders::_1));
}

/* Protected class methods */

web::json::value MainServiceController::responseNotImpl(
    web::http::method const & method) const
{
    auto response = web::json::value::object();
    response["serviceName"] = web::json::value::string("CppMSA");
    response["http_method"] = web::json::value::string(method);

    return response;
}

}  // namespace msabase
