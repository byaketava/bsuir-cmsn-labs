#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "types.h"
#include "fs.h"

int main(int argc, char *argv[])
{
    int i, n, fsfd;
    char *addr;
    struct dinode *dip;
    struct superblock *sb;
    struct dirent *de;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: sample fs.img ...\n");
        exit(1);
    }

    fsfd = open(argv[1], O_RDONLY);
    if (fsfd < 0)
    {
        perror(argv[1]);
        exit(1);
    }

    addr = mmap(NULL, BSIZE * 102400, PROT_READ, MAP_PRIVATE, fsfd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap failed");
        exit(1);
    }

    sb = (struct superblock *) (addr + 1 * BSIZE);
    printf("fs size %d, no. of blocks %d, no. of inodes %d \n", sb->nblocks * BSIZE,
           sb->nblocks, sb->ninodes);

    dip = (struct dinode *) (addr + IBLOCK((uint) 0) * BSIZE);
    printf("begin addr %p, begin inode %p , offset %ld \n", addr,
           dip, (char *) dip - addr);


    printf("Root inode  size %d links %d type %d \n",
           dip[ROOTINO].size, dip[ROOTINO].nlink, dip[ROOTINO].type);

    de = (struct dirent *) (addr + (dip[ROOTINO].addrs[0]) * BSIZE);

    n = dip[ROOTINO].size / sizeof(struct dirent);
    for (i = 0; i < n; i++, de++)
    {
        printf(" inum %d, name %s ", de->inum, de->name);
        printf("inode  size %d links %d type %d \n",
               dip[de->inum].size, dip[de->inum].nlink, dip[de->inum].type);
    }
    exit(0);
}