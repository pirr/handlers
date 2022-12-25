#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "request.h"

Request *
init_request(HttpMethod method, Url *url, Buffer *body, Buffer *headers, int timeout)
{
    Request *request = (Request *) malloc(sizeof(Request));
    request->method = method;
    request->url = url;
    request->headers = headers;
    request->body = body;
    request->timeout = timeout;

    return request;
}

Response *
make_request(Request *request)
{
    int sockfd, rv, bytes_received;
    unsigned total_size;
    struct addrinfo hints, *servinfo, *p;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(request->url->host->content, request->url->protocol->content, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return NULL;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
        perror("client: socket");
        continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(sockfd);
        perror("client: connect");
        continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return NULL;
    }

    inet_ntop(p->ai_family, &(((struct sockaddr_in*)p->ai_addr)->sin_addr),
                s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    // Send the HTTP request
    const char *http_method_str = HttpMethodsString[request->method];
    unsigned request_str_len = strlen(http_method_str) + request->url->host->bytes_used + 25;
    char *request_str = (char *)malloc(request_str_len * sizeof(char));
    sprintf(request_str, "%s / HTTP/1.0\r\nHost: %s\r\n\r\n", http_method_str, request->url->host->content);
    send(sockfd, request_str, request_str_len, 0);
    free(request_str);

    // Read the response
    Response *response = (Response *) malloc(sizeof(Response));
    response->request = request;
    response->content = buffer_alloc(BUFSIZ * 2);
    char chunk[BUFSIZ];

    total_size = 0;
    while(1) {
        if((bytes_received = recv(sockfd, chunk, BUFSIZ, 0)) <= 0) {
            break;
        } else {
            total_size += bytes_received;
            buffer_append(response->content, chunk, bytes_received);
        }
    }
    
    close(sockfd);

    return response;
}

void
free_request(Request *request)
{
    if (request == NULL)
        return;
    
    if (request->url != NULL)
        free(request->url);

    if (request->body != NULL)
        free(request->body);

    if (request->headers != NULL)
        free(request->headers);

    free(request);

    request = NULL;
}
