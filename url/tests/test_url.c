#include <assert.h>
#include "../url.h"

int
main()
{
    char *url_string = "http//example.com/";
    Url *url = get_url(url_string, strlen(url_string));
    assert(strcmp(url->protocol->content, "http") == 0);
    assert(strcmp(url->host->content, "example.com") == 0);
    free(url);
    assert(url == NULL);
}
