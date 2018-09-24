#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include "vector_fd.h"

static void encapacity(VectorFD *vfd)
{
    if (vfd->counter >= vfd->max_counter) {
        int *fds =
            (int*)calloc(vfd->counter + 5, sizeof(int));
        assert(fds != NULL);

        memcpy(fds, vfd->fd, sizeof(int) * vfd->counter);
        free(vfd->fd);
        vfd->fd = fds;
        vfd->max_counter += 5;
    }
}

static int indexof(VectorFD *vfd, int fd)
{
    int i = 0;
    for (; i < vfd->counter; i++) {
        if (vfd->fd[i] == fd) return i;
    }

    return -1;
}

VectorFD *cerate_vector_fd(void)
{
    VectorFD *vfd = (VectorFD*)calloc(1, sizeof(VectorFD));
    assert(vfd != NULL);

    vfd->fd = (int*)calloc(5, sizeof(int));
    assert(vfd->fd != NULL);

    vfd->counter = 0;
    vfd->max_counter = 0;
}

void  destory_vector_fd(VectorFD *vfd)
{
    assert(vfd != NULL);
    free(vfd->fd);
    free(vfd);
}

int  get_fd(VectorFD *vfd, int index)
{
    assert(vfd != NULL);
    if (index < 0 || index > vfd->counter - 1)
        return 0;
    return vfd->fd[index];
}

void  remove_fd(VectorFD *vfd, int fd)
{
    assert(vfd != NULL);
    int index = indexof(vfd, fd);
    if (index == -1) return;
    int i = index;
    for (; i < vfd->counter - 1; i++) {
        vfd->fd[i] = vfd->fd[i + 1];
    }
    vfd->counter--;
}

void  add_fd(VectorFD *vfd, int fd)
{
    assert(vfd != NULL);
    encapacity(vfd);
    vfd->fd[vfd->counter++] = fd;
}