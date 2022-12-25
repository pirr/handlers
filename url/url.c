#include <stdio.h>

#include "url.h"

Url *
get_url(char *url_string, size_t size)
{
    if (size <= MIN_PROTOCOL_SIZE + 2) {
        fprintf(stderr, "Url should have protocol and host at least\n");
        return NULL;
    }

    Url *url;
    char data[2] = "\0";

    if ((url = (Url *) malloc(sizeof(Url))) == NULL) {
        fprintf(stderr, "Can't allocate Url\n");
        return NULL;
    }

    if ((url->protocol = buffer_alloc(MIN_PROTOCOL_SIZE)) == NULL) {
        fprintf(stderr, "Url protocol allocation error\n");
        free_url(&url);
        return NULL;
    }

    url->host = NULL;
    url->path = NULL;
    
    while(*url_string != ':') {
        data[0] = *url_string;
        if (buffer_append(url->protocol, data, 1) == -1) {
            fprintf(stderr, "Url protocol append error\n");
            free_url(&url);
            return NULL;
        }
        url_string++;
    }

    if (strcmp(url->protocol->content, "http") != 0 & strcmp(url->protocol->content, "https") != 0) {
        fprintf(stderr, "Use unknown protocol: %s\n", url->protocol->content);
        free_url(&url);
        return NULL;
    }


    while(*url_string == '/' || *url_string == ':')
        url_string++;

    size_t s = size - url->protocol->bytes_used;

    if ((url->host = buffer_alloc(s)) == NULL) {
        fprintf(stderr, "Url host allocate error\n");
        free_url(&url);
        return NULL;
    }

    while((*url_string != '/') && (*url_string != '\0')) {
        data[0] = *url_string;
        if (buffer_append(url->host, data, 1) == -1) {
            fprintf(stderr, "Url host append error\n");
            free_url(&url);
            return NULL;
        }
        url_string++;
    }
    
    s -= url->host->bytes_used;

    while(*url_string == '/')
        url_string++;

    if (*url_string != '\0') {
        if ((url->path = buffer_alloc(s)) == NULL) {
            fprintf(stderr, "Url path alloc error\n");
            free_url(&url);
            return NULL;
        }
    }

    while(*url_string != '\0') {
        data[0] = *url_string;
        if ((buffer_append(url->path, data, 1) == -1)) {
            fprintf(stderr, "Url path append error\n");
            free_url(&url);
            return NULL;
        }
        url_string++;
    }

    return url;
}

void
free_url(Url **url)
{
    if ((*url)->host != NULL)
        bufer_free(&(*url)->host);
    
    if ((*url)->path != NULL)
        bufer_free(&(*url)->path);
    
    if ((*url)->protocol != NULL)
        bufer_free(&(*url)->protocol);

    free(*url);
    
    *url = NULL;
}
