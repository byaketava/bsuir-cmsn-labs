#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <getopt.h>
#include <locale.h>
#include <stdbool.h>

typedef struct {
    bool show_links;
    bool show_dirs;
    bool show_files;
    bool sort_output;
} parameters;

void dirwalk(char *path, parameters params) {
    struct stat info;
    if (lstat(path, &info) == -1)
        printf("Error: %s: %s\n", path, strerror(errno));

    if ((params.show_dirs && S_ISDIR(info.st_mode)) ||
        (params.show_files && S_ISREG(info.st_mode)) ||
        (params.show_links && S_ISLNK(info.st_mode)))
        printf("%s\n", path);

    if (S_ISDIR(info.st_mode)) {
        DIR *dir = opendir(path);
        if (dir == NULL) {
            printf("Error while opening %s: %s\n", path, strerror(errno));
            return;
        }

        struct dirent **entries;
        int count = scandir(path, &entries, NULL, params.sort_output ? alphasort : NULL);

        if (count < 0)
            printf("Error while scan dir %s: %s", path, strerror(errno));

        for (int i = 0; i < count; i++) {
            struct dirent *entry = entries[i];
            free(entries[i]);

            if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
                continue;

            char childPath[256];
            strcpy(childPath, path);
            strcat(childPath, "/");
            strcat(childPath, entry->d_name);

            dirwalk(childPath, params);
        }
        closedir(dir);
    }
}

int main(int argc, char *argv[]) {
    char *path = ".";
    parameters params = {0};

    int opt;
    while ((opt = getopt(argc, argv, "ldfs")) != EOF) {
        switch (opt) {
            case 'l':
                params.show_links = true;
            break;
            case 'd':
                params.show_dirs = true;
            break;
            case 'f':
                params.show_files = true;
            break;
            case 's':
                params.sort_output = true;
            break;
            default:
                printf("incorrect option: %c\n", opt);
            exit(EXIT_FAILURE);;
        }
    }

    if (!params.show_dirs & !params.show_files && !params.show_links) {
        params.show_dirs = true;
        params.show_files = true;
        params.show_links = true;
    }

    if (optind < argc)
        path = argv[optind];

    dirwalk(path, params);

    return 0;
}