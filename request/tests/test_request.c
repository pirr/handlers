#include <assert.h>

#include "../request.h"

int
main()
{
    char* url_str = "http://www.example.com";
    Url *url = get_url(url_str, strlen(url_str));
    Request *request = init_request(GET, url, NULL, NULL, 1);
    Response *response = make_request(request);
    // printf("Content: %s\n", response->content->content);
    char *first_line = "HTTP/1.0 200 OK";
    size_t i;
    for(i = 0; i < strlen(first_line); i++)
        assert(response->content->content[i] == first_line[i]);

    free_response(&response);
}
