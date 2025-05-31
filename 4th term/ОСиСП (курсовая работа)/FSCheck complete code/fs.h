#pragma once

#define ROOTINO 2
#define BSIZE 1024

struct superblock
{
    uint ninodes;
    uint nblocks;
};

#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint))
#define MAXFILE (NDIRECT + NINDIRECT)

struct dinode
{
    short type;
    short major;
    short minor;
    short nlink;
    uint size;
    uint addrs[NDIRECT + 1];
};

#define IPB (BSIZE / sizeof(struct dinode))
#define IBLOCK(i) ((i) / IPB + 2)
#define BPB (BSIZE*8)
#define BBLOCK(b, ninodes) (b/BPB + (ninodes)/IPB + 3)
#define DIRSIZ 14

struct dirent
{
    ushort inum;
    char name[DIRSIZ];
};

