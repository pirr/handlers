#include <stdio.h>

#include "url.h"

Url *
get_url(char *url_string, size_t size)
{
    if (size <= MIN_PROTOCOL_SIZE + 2) {
        fprintf(stderr, "Url should have protocol and host at least");
        return NULL;
    }

    Url *url;
    char data[2] = "\0";


    if ((url = (Url *) malloc(sizeof(Url))) == NULL) {
        fprintf(stderr, "Can't allocate Url");
        return NULL;
    }

    if ((url->protocol = buffer_alloc(MIN_PROTOCOL_SIZE)) == NULL) {
        fprintf(stderr, "Url protocol allocation error");
        free_url(url);
        return NULL;
    }

    url->host = NULL;
    url->path = NULL;
    
    while(*url_string != '/') {
        data[0] = *url_string++;
        if (buffer_append(url->protocol, data, 1) == -1) {
            fprintf(stderr, "Url protocol append error");
            free_url(url);
            return NULL;
        }
    }

    if (strcmp(url->protocol->content, "http") != 0 & strcmp(url->protocol->content, "https") != 0) {
        fprintf(stderr, "Use unknown protocol: %s", url->protocol->content);
        free_url(url);
        return NULL;
    }

    size_t s = size - url->protocol->bytes_used;

    if ((url->host = buffer_alloc(s)) == NULL) {
        fprintf(stderr, "Url host allocate error");
        free_url(url);
        return NULL;
    }

    while(*url_string != '/' || *url_string != '\0') {
        data[0] = *url_string++;
        if (buffer_append(url->host, data, 1) == -1) {
            fprintf(stderr, "Url host append error");
            free_url(url);
            return NULL;
        }
    }
    
    s -= url->host->bytes_used;

    if (*++url_string != '\0')
        if ((url->path = buffer_alloc(s)) == NULL) {
            fprintf(stderr, "Url path alloc error");
            free_url(url);
            return NULL;
        }
    

    while(*url_string != '\0') {
        data[0] = *url_string++;
        if ((buffer_append(url->path, data, 1) == -1)) {
            fprintf(stderr, "Url path append error");
            free_url(url);
            return NULL;
        }
    }

    return url;
}

void
free_url(Url *url)
{
    if (url->host != NULL)
        free(url->host);
    
    if (url->path != NULL)
        free(url->path);
    
    if (url->protocol != NULL)
        free(url->protocol);

    free(url);
    
    url = NULL;
}
