#include <stdio.h>
#include "record.h"

int main()
{
    int count;
    printf("Count (>=10): ");
    if (scanf("%d", &count) != 1 || count < 10)
    {
        printf("Wrong input\n");
        return 0;
    }
    FILE *fp = fopen("file", "wb");
    for (int i = 0; i < count; i++)
    {
        record temp = random_record();
        fwrite(&temp, sizeof(record), 1, fp);
    }
    fclose(fp);
    printf("Success.\n");
    return 0;
}