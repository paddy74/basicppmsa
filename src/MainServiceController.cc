#include <cppmsa/MainServiceController.h>


namespace cppmsa
{

void MainServiceController::handleGet(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::GET));
}

void MainServiceController::handlePut(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::PUT));
}

void MainServiceController::handlePost(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::POST));
}

void MainServiceController::handlePatch(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::PATCH));
}

void MainServiceController::handleDelete(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::DEL));
}

void MainServiceController::handleHead(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::HEAD));
}

void MainServiceController::handleOptions(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::OPTIONS));
}

void MainServiceController::handleTrace(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::TRCE));
}

void MainServiceController::handleConnect(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::CONNECT));
}

void MainServiceController::handleMerge(web::http::http_request message)
{
    message.reply(web::http::status_codes::NotImplemented, responseNotImpl(web::http::methods::MERGE));
}


}
