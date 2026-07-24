#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    int pipe_fds[2];
    if (pipe(pipe_fds) < 0) {
        printf("ERROR: could not create pipe\n");
        return 2;
    }

    int pipe_read_fd = pipe_fds[0];
    int pipe_write_fd = pipe_fds[1];

    pid_t pid = fork();
    if (pid < 0) {
        printf("ERROR: could not fork\n");
        return 3;
    }

    if (pid > 0) {
        close(pipe_read_fd);
        dup2(pipe_write_fd, STDOUT_FILENO);
        close(pipe_write_fd);

        char* parta_args[] = {"./parta", argv[1], NULL};
        execv("./parta", parta_args);

        fprintf(stderr, "ERROR: could not exec ./parta\n");
        return 4;
    } else {
        close(pipe_write_fd);
        dup2(pipe_read_fd, STDIN_FILENO);
        close(pipe_read_fd);

        char* sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
        execvp("sort", sort_args);

        fprintf(stderr, "ERROR: could not exec sort\n");
        return 5;
    }

    return 0;
}
