#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include "vector_fd.h"

static void encapacity(VectorFD *vfd)
{
    if (vfd->counter >= vfd->max_counter) {

        int *fds = (int*)calloc(vfd->counter + 5, sizeof(int));
        assert(fds != NULL);

        memcpy(fds, vfd->fd, sizeof(int) * vfd->counter);
        free(vfd->fd);

        vfd->fd = fds;
        vfd->max_counter += 5;
    }
}

static int indexof(VectorFD *vfd, int fd)
{
    assert(vfd != NULL);

    int index = 0;
    for (; index < vfd->counter; index++) {
        if (vfd->fd[index] == fd)
            return index;
    }

    return -1;
}

VectorFD*   create_vector_fd()
{
    VectorFD *vfd = (VectorFD*)calloc(1, sizeof(VectorFD));
    assert(vfd != NULL);

    vfd->fd = (int*)calloc(5, sizeof(int));
    assert(vfd->fd != NULL);

    vfd->counter = 0;
    vfd->max_counter = 5;
    return vfd;
}

void    destroy_vectot_fd(VectorFD *vfd)
{
    assert(vfd != NULL);
    free(vfd->fd);
    free(vfd);
}

int     get_fd(VectorFD *vfd, int index)
{
    assert(vfd != NULL);

    if (index < 0 || index > vfd->counter - 1)
        return 0;
    return vfd->fd[index];
}

void    remove_fd(VectorFD *vfd, int fd)
{
    assert(vfd != NULL);

    int index = indexof(vfd, fd);

    if (index == -1)
    {
        return;
    }
    else
    {
        int  i = index;
        for (; i < vfd->counter - 1; i++)
            vfd->fd[i] = vfd->fd[i++];
        vfd->counter -= 1;
    }
}

void    add_fd(VectorFD *vfd, int fd)
{
    assert(vfd != NULL);

    encapacity(vfd);

    vfd->fd[vfd->counter++] = fd;
}

