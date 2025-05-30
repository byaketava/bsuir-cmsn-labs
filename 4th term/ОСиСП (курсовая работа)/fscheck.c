#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "types.h"
#include "fs.h"

#define DIR_ENTRY_PER_BLOCK (BSIZE / sizeof(struct dirent))
#define T_DIR   1   //For determining type of inode - Directory
#define T_FILE  2   //For determining type of inode - File
#define T_DEV   3   //For determining type of inode - Device

struct dinode *disk_inodes_arr = NULL;
struct superblock *super_block = NULL;
int *referenced_inodes_arr = NULL;

uint xint(uint x)
{
    uint indirect_block_addr = 0;
    char *a = (char *) &indirect_block_addr;
    a[0] = x;
    a[1] = x >> 8;
    a[2] = x >> 16;
    a[3] = x >> 24;
    return indirect_block_addr;
}

void rsect(int image_file_handler, uint sec, void *buf)
{
    if (lseek(image_file_handler, sec * 1024L, 0) != sec * 1024L)
    {
        perror("lseek");
        exit(1);
    }

    if (read(image_file_handler, buf, 1024) != 1024)
    {
        perror("read");
        exit(1);
    }
}

void get_dir_entries(uint block_number, char *mmap_address_space, uint *num_inodes)
{
    struct dirent *directory_entry = (struct dirent *) (mmap_address_space + block_number * BSIZE);
    int iterator = 0;
    for (iterator = 0; iterator < DIR_ENTRY_PER_BLOCK; iterator++, directory_entry++)
    {
        if ((strcmp(directory_entry->name, ".") == 0) || (strcmp(directory_entry->name, "..") == 0))
        {
            num_inodes[iterator] = 0;
            continue;
        }
        num_inodes[iterator] = directory_entry->inum;
    }
}

void is_inode_in_dir(int image_file_handler, char *mmap_address_space)
{
    int outer_iterator = 0;
    int inner_iterator = 0;

    for (outer_iterator = 0; outer_iterator < super_block->ninodes; outer_iterator++)
    {
        //If inode represents a directory.
        if (disk_inodes_arr[outer_iterator].type == T_DIR)
        {
            //Get number of entries
            int num_dir_entries = disk_inodes_arr[outer_iterator].size / sizeof(struct dirent);
            for (inner_iterator = 0; inner_iterator < NDIRECT; inner_iterator++)
            {
                if ((disk_inodes_arr[outer_iterator].addrs[inner_iterator] == 0) || (num_dir_entries <= 0))
                {
                    continue;
                }
                uint *num_inodes = (uint *) calloc(DIR_ENTRY_PER_BLOCK, sizeof(uint));
                if (num_inodes == NULL)
                {
                    perror("Memory allocation failed");
                    exit(1);
                }
                get_dir_entries(disk_inodes_arr[outer_iterator].addrs[inner_iterator], mmap_address_space, num_inodes);

                int temp_iterator = 0;
                for (temp_iterator = 0; temp_iterator < DIR_ENTRY_PER_BLOCK; temp_iterator++)
                {
                    if (num_inodes[temp_iterator] != 0)
                    {
                        referenced_inodes_arr[num_inodes[temp_iterator]]++;
                        num_dir_entries--;
                    }
                }
                free(num_inodes);
            }
            if (disk_inodes_arr[outer_iterator].addrs[NDIRECT] == 0)
            {
                continue;
            }
            uint indirect[NINDIRECT] = {0};
            rsect(image_file_handler, xint(disk_inodes_arr[outer_iterator].addrs[NDIRECT]), (char *) indirect);
            for (inner_iterator = 0; inner_iterator < NINDIRECT; inner_iterator++)
            {
                if ((indirect[inner_iterator] == 0) || (num_dir_entries <= 0))
                {
                    continue;
                }
                uint *num_inodes = (uint *) calloc(DIR_ENTRY_PER_BLOCK, sizeof(uint));
                if (num_inodes == NULL)
                {
                    perror("Memory allocation failed");
                    exit(1);
                }
                get_dir_entries(indirect[inner_iterator], mmap_address_space, num_inodes);

                int temp_iterator = 0;
                for (temp_iterator = 0; temp_iterator < DIR_ENTRY_PER_BLOCK; temp_iterator++)
                {
                    if (num_inodes[temp_iterator])
                    {
                        referenced_inodes_arr[num_inodes[temp_iterator]]++;
                        num_dir_entries--;
                    }
                }
                free(num_inodes);
            }
        }
    }
}

void check_rule_1(struct dinode *disk_inodes_arr, int iterator)
{
    if ((disk_inodes_arr[iterator].size < 0) || (disk_inodes_arr[iterator].type < T_DIR) ||
        (disk_inodes_arr[iterator].type > T_DEV))
    {
        fprintf(stderr, "ERROR: bad inode.\n");
        exit(1);
    }
}

void check_rule_2_direct(struct dinode *disk_inodes_arr, int outer_iterator, int inner_iterator)
{
    if ((disk_inodes_arr[outer_iterator].addrs[inner_iterator] < 0) ||
        (disk_inodes_arr[outer_iterator].addrs[inner_iterator] > super_block->nblocks))
    {
        fprintf(stderr, "ERROR: bad direct address in inode.\n");
        exit(1);
    }
}

void check_rule_2_indirect(int indirect_block_num)
{
    if ((indirect_block_num < 0) || (indirect_block_num > super_block->nblocks))
    {
        fprintf(stderr, "ERROR: bad indirect address in inode.\n");
        exit(1);
    }
}

void check_rule_3_for_size(int size)
{
    if (size <= 0)
    {
        fprintf(stderr, "ERROR: root directory does not exist.\n");
        exit(1);
    }
}

void check_rule_3_for_root_inode(int inode_num)
{
    if (inode_num != ROOTINO)
    {
        fprintf(stderr, "ERROR: root directory does not exist.\n");
        exit(1);
    }
}

int check_rule_4_for_present_dir_link(struct dirent *directory_entry,
                                      int outer_iterator, int reference_count)
{
    if (directory_entry->inum == outer_iterator)
    {
        reference_count++;
    } else
    {
        fprintf(stderr, "ERROR: directory not properly formatted.\n");
        exit(1);
    }
    return reference_count;
}

void check_rule_4_for_dir_type_and_format(short type, int reference_count)
{
    if ((type == T_DIR) && (reference_count != 2))
    {
        fprintf(stderr, "ERROR: directory not properly formatted.\n");
        exit(1);
    }
}

void check_rule_5(char *block_usage_bitmap, uint block_num)
{
    if (((block_usage_bitmap[block_num / 8]) & (0x1 << (block_num % 8))) == 0)
    {
        fprintf(stderr, "ERROR: address used by inode but marked free in bitmap.\n");
        exit(1);
    }
}

void check_rule_6(char *mmap_address_space, uint first_block, uint *used_blocks_arr)
{
    int interator = 0;
    for (interator = 0; interator < first_block + super_block->nblocks; interator++)
    {
        char *block_usage_bitmap = mmap_address_space + (BBLOCK(interator, super_block->ninodes)) * BSIZE;
        if (((block_usage_bitmap[interator / 8]) & (0x1 << (interator % 8))))
        {
            if (used_blocks_arr[interator] == 0)
            {
                fprintf(stderr, "ERROR: bitmap marks block in use but it is not in use.\n");
                exit(1);
            }
        }
    }
}

void check_rule_7(uint is_used)
{
    if (is_used == 1)
    {
        fprintf(stderr, "ERROR: direct address used more than once.\n");
        exit(1);
    }
}

void check_rule_8(uint is_used)
{
    if (is_used)
    {
        fprintf(stderr, "ERROR: indirect address used more than once.\n");
        exit(1);
    }
}

void check_rule_9(int is_used)
{
    if (is_used == 0)
    {
        fprintf(stderr, "ERROR: inode marked use but not found in a directory.\n");
        free(referenced_inodes_arr);
        exit(1);
    }
}

void check_rule_10(int is_used)
{
    if (is_used != 0)
    {
        fprintf(stderr, "ERROR: inode referred to in directory but marked free.\n");
        free(referenced_inodes_arr);
        exit(1);
    }
}

void check_rule_11(short type, int ref_inode_num, short nliks)
{
    //If the inode is a file. It should be referred for a total number of times same as its number of links. Else throw error. Rule-11: Referrence count is bad.
    if ((type == T_FILE) && (ref_inode_num != nliks))
    {
        fprintf(stderr, "ERROR: bad reference count for file.\n");
        free(referenced_inodes_arr);
        exit(1);
    }
}

void check_rule_12(short type, int ref_inode_num)
{
    if ((type == T_DIR) && (ref_inode_num > 1))
    {
        fprintf(stderr, "ERROR: directory appears more than once in file system.\n");
        free(referenced_inodes_arr);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int image_file_handler = 0;
    char *mmap_address_space = NULL;
    struct dirent *directory_entry = NULL;
    struct stat file_statistics;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: fscheck <file_system_image>\n");
        exit(1);
    }

    image_file_handler = open(argv[1], O_RDONLY);
    if (image_file_handler < 0)
    {
        fprintf(stderr, "Image not found.\n");
        exit(1);
    }

    fstat(image_file_handler, &file_statistics);

    mmap_address_space = mmap(NULL, file_statistics.st_size,
                              PROT_READ, MAP_PRIVATE, image_file_handler, 0);
    if (mmap_address_space == MAP_FAILED)
    {
        perror("Mmap failed");
        exit(1);
    }

    super_block = (struct superblock *) (mmap_address_space + BSIZE);
    uint fs_size = (super_block->nblocks * BSIZE);
    disk_inodes_arr = (struct dinode *) (mmap_address_space + IBLOCK((uint) 0) * BSIZE);

    int num_inodes = super_block->ninodes;
    int outer_iterator, inner_iterator;

    check_rule_3_for_size(disk_inodes_arr[ROOTINO].size);

    directory_entry = (struct dirent *) (mmap_address_space + (disk_inodes_arr[ROOTINO].addrs[0]) * BSIZE);
    int size = disk_inodes_arr[ROOTINO].size / sizeof(struct dirent);
    int reference_count = 0;

    for (outer_iterator = 0; outer_iterator < size; outer_iterator++)
    {
        if ((reference_count < 2) && ((strcmp(directory_entry->name, ".") == 0)
                                      || (strcmp(directory_entry->name, "..") == 0)))
        {
            check_rule_3_for_root_inode(directory_entry->inum);
            reference_count++;
        }
        directory_entry++;
    }

    uint used_blocks_arr[fs_size];
    uint first_block = BBLOCK(fs_size, super_block->ninodes) + 1;

    for (outer_iterator = 0; outer_iterator < fs_size; outer_iterator++)
    {
        used_blocks_arr[outer_iterator] = 0;
    }
    for (outer_iterator = 0; outer_iterator < first_block; outer_iterator++)
    {
        used_blocks_arr[outer_iterator] = 1;
    }
    for (outer_iterator = 0; outer_iterator < num_inodes; outer_iterator++)
    {
        if (disk_inodes_arr[outer_iterator].size == 0)
        {
            continue;
        }
        check_rule_1(disk_inodes_arr, outer_iterator);
        reference_count = 0;
        for (inner_iterator = 0; inner_iterator < NDIRECT; inner_iterator++)
        {
            if (disk_inodes_arr[outer_iterator].addrs[inner_iterator] == 0)
            {
                continue;
            }
            check_rule_2_direct(disk_inodes_arr, outer_iterator, inner_iterator);
            uint block_num = disk_inodes_arr[outer_iterator].addrs[inner_iterator];
            char *block_usage_bitmap = mmap_address_space + (BBLOCK(block_num, super_block->ninodes)) * BSIZE;

            check_rule_5(block_usage_bitmap, block_num);
            check_rule_7(used_blocks_arr[block_num]);
            used_blocks_arr[block_num] = 1;
            if (disk_inodes_arr[outer_iterator].type == T_DIR)
            {
                directory_entry = (struct dirent *) (mmap_address_space + block_num * BSIZE);
                int size = disk_inodes_arr[outer_iterator].size / sizeof(struct dirent);

                int temp_iterator = 0;
                for (temp_iterator = 0; temp_iterator < size; temp_iterator++, directory_entry++)
                {
                    if (reference_count < 2)
                    {
                        if (strcmp(directory_entry->name, ".") == 0)
                        {
                            reference_count = check_rule_4_for_present_dir_link(directory_entry, outer_iterator,
                                                                                reference_count);
                        } else if (strcmp(directory_entry->name, "..") == 0)
                        {
                            reference_count++;
                        }
                    }
                }
            }
        }
        check_rule_4_for_dir_type_and_format(disk_inodes_arr[outer_iterator].type, reference_count);

        if (disk_inodes_arr[outer_iterator].addrs[NDIRECT] == 0)
        {
            continue;
        }

        uint temp_inode_addr = disk_inodes_arr[outer_iterator].addrs[NDIRECT];
        if ((temp_inode_addr > 0) && (temp_inode_addr < fs_size))
        {
            used_blocks_arr[temp_inode_addr] = 1;
        }

        uint indirect[NINDIRECT] = {0};
        uint indirect_block_addr = xint(temp_inode_addr);
        rsect(image_file_handler, indirect_block_addr, (char *) indirect);

        for (inner_iterator = 0; inner_iterator < NINDIRECT; inner_iterator++)
        {
            uint indirect_block_num = indirect[inner_iterator];
            if (indirect_block_num == 0)
            {
                continue;
            }

            check_rule_2_indirect(indirect_block_num);
            char *block_usage_bitmap = mmap_address_space + (BBLOCK(indirect_block_num, super_block->ninodes)) * BSIZE;
            check_rule_5(block_usage_bitmap, indirect_block_num);
            check_rule_8(used_blocks_arr[indirect_block_num]);
            used_blocks_arr[indirect_block_num] = 1;
        }
    }

    check_rule_6(mmap_address_space, first_block, used_blocks_arr);
    referenced_inodes_arr = (int *) calloc(super_block->ninodes, sizeof(int));
    if (referenced_inodes_arr == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }

    is_inode_in_dir(image_file_handler, mmap_address_space);
    for (outer_iterator = 2; outer_iterator < super_block->ninodes; outer_iterator++)
    {
        if (disk_inodes_arr[outer_iterator].type == 0)
        {
            check_rule_10(referenced_inodes_arr[outer_iterator]);
            continue;
        }
        check_rule_9(referenced_inodes_arr[outer_iterator]);
        check_rule_11(disk_inodes_arr[outer_iterator].type,
                      referenced_inodes_arr[outer_iterator],
                      disk_inodes_arr[outer_iterator].nlink);
        check_rule_12(disk_inodes_arr[outer_iterator].type,
                      referenced_inodes_arr[outer_iterator]);
    }
    printf("All good\n");
    exit(0);
}