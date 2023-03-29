#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return 1;
    }
    FILE* fp = fopen(argv[1], "w+");
    if (!fp) {
        fprintf(stderr, "fopen(%s, w+) = %m\n", argv[1]);
        return 1;
    }
    fprintf(fp, "Hello World!");
    long fsize = ftell(fp);
    fflush(fp);
    fclose(fp);
    int fd = open(argv[1], O_RDONLY, 0);
    char* base = (char*)mmap(NULL, fsize, PROT_READ, MAP_SHARED|MAP_POPULATE, fd, 0);
    close(fd);
    if (MAP_FAILED == base) {
        fprintf(stderr, "mmap(%s, fsize=%ld) = %m\n", argv[1], fsize);
        return 1;
    }
    printf("file content: %s\n", base);
    printf("success\n");
    munmap(base, fsize);
    return 0;
}
