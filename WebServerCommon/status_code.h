/*
Copyright 2018 Jesse Laning
*/

#pragma once
#include <string>
#include "lib_utils.h"
namespace webserver {
namespace http {
namespace response {
class LIBEXPORT StatusCode {
 public:
  enum : int {
    // 1xx: Informational - Request received, continuing process
    CONTINUE = 100,
    SWITCHING_PROTOCOLS = 101,
    // 2xx: Success - The action was successfully received, understood, and
    // accepted
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NON_AUTHORITATIVE_INFORMATION = 203,
    NO_CONTENT = 204,
    RESET_CONTENT = 205,
    PARTIAL_CONTENT = 206,
    // 3xx: Redirection - Further action must be taken in order to complete the
    // request
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    SEE_OTHER = 303,
    NOT_MODIFIED = 304,
    USE_PROXY = 305,
    TEMPORARY_REDIRECT = 307,
    // 4xx: Client Error - The request contains bad syntax or cannot be
    // fulfilled
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    PAYMENT_REQUIRED = 402,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    NOT_ACCEPTABLE = 406,
    PROXY_AUTHENTICATION_REQUIRED = 407,
    REQUEST_TIMEOUT = 408,
    CONFLICT = 409,
    GONE = 410,
    LENGTH_REQUIRED = 411,
    PRECONDITION_FAILED = 412,
    REQUEST_ENTITY_TOO_LARGE = 413,
    REQUEST_URI_TOO_LARGE = 414,
    UNSUPPORTED_MEDIA_TYPE = 415,
    REQUEST_RANGE_NOT_SATISFIABLE = 416,
    EXPECTATION_FAILED = 417,
    // 5xx: Server Error - The server failed to fulfill an apparently valid
    // request
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIMEOUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505
  };

  static std::string getString(int code);
  static void insert(int code, const std::string& str);

 private:
  StatusCode() = delete;
};
}  // namespace response
}  // namespace http
}  // namespace webserver
