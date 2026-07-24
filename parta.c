#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
 
    if (argc < 2) {
        printf("USAGE: parta FILEIN\n");
        return 1;
    }
 
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("ERROR: %s not found\n", argv[1]);
        return 2;
    }
 
    const char* names[] = {"Upper", "Lower", "Number", "Space", "Other"};
    int count[5] = {0};
 
    ssize_t n;
    while ((n = read(fd, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            unsigned char c = (unsigned char)buffer[i];
            if (isupper(c))      count[0]++;
            else if (islower(c)) count[1]++;
            else if (isdigit(c)) count[2]++;
            else if (isspace(c)) count[3]++;
            else                 count[4]++;
        }
    }
    close(fd);
 
    for (int i = 0; i < 5; i++) printf("%s,%d\n", names[i], count[i]);
    return 0;
}
