#include "../buffer/buffer.h"

static const int MIN_PROTOCOL_SIZE = 4;

struct Url {
    Buffer *host;
    Buffer *path;
    Buffer *protocol;
};

typedef struct Url Url;

Url *get_url(char *url_string, size_t size);
void free_url(Url *url);
