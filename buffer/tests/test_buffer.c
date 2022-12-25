#include <assert.h>
#include "../buffer.h"

int
main()
{
    Buffer *buf = buffer_alloc(10);
    assert(buf->bytes_used == 0);
    assert(buf->total_size == 10);

    int status = buffer_append(buf, "test", 4);
    assert(status == 0);

    status = buffer_append(buf, "--newtest", 9);
    assert(status == 0);
    assert(strcmp(buf->content, "test--newtest") == 0);
    assert(buf->bytes_used == 13);
    assert(buf->total_size == 13);
    assert(buf->content[13] == '\0');
    
    bufer_free(&buf);
    assert(buf == NULL);
}
