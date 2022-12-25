#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "../url/url.h"

#define BUFFER_H "../buffer/buffer.h"
#ifndef BUFFER_H
#define BUFFER_H
#endif

enum HttpMethod {
    GET,
    POST,
};

static const char *HttpMethodsString[2] = {"GET", "POST"};
typedef enum HttpMethod HttpMethod;

struct Request {
    Buffer *headers;
    Url *url;
    Buffer *body;
    int timeout;
    HttpMethod method;
};

typedef struct Request Request;

struct Response {
    Request *request;
    Buffer *content;
    int status_code;
};

typedef struct Response Response;


Request *init_request(HttpMethod method, Url *url, Buffer *body, Buffer *headers, int timeout);
Response *make_request(Request *request);
void free_request(Request *request);
void free_response(Response *response);
