#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    const char* input_filename = argv[1];
    const char* output_filename = argv[2];

    int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd < 0) {
        printf("ERROR: could not open %s\n", output_filename);
        return 2;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);

    printf("Category,Count\n");
    fflush(stdout);

    char* parta_args[] = {"./parta", (char*)input_filename, NULL};
    int eret = execv("./parta", parta_args);

    if (eret < 0) {
        fprintf(stderr, "ERROR: could not exec ./parta\n");
        return 3;
    }

    return 0;
}
