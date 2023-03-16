#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    const int buffer = 5000, max_read = 10;
    const char *first_channel = "pipe1.fifo";
    const char *second_channel = "pipe2.fifo";

    (void) umask(0);

    if (argc != 3) {
        printf("Run the program with 2 arguments\n \"./program.exe input.txt output.txt\"\n");
        return 0;
    }

    int fd_12, fd_23, size;
    char string[buffer] = {0};

    mknod(first_channel, S_IFIFO | 0666, 0);
    mknod(second_channel, S_IFIFO | 0666, 0);

    // Первый процесс - считать из файла и направить во второй процесс
    int input = open(argv[1], O_RDONLY, 0666);

    if (input < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }

    ssize_t read_bytes;
    char *help_string;

    fd_12 = open(first_channel, O_WRONLY);
    if (fd_12 < 0) {
        printf("Can\'t open FIFO for writting\n");
        exit(-1);
    }

    do {
        read_bytes = read(input, help_string, max_read);
        if (read_bytes == -1) {
            printf("Can\'t write this file\n");
            exit(-1);
        }

        help_string[read_bytes] = '\0';

        size = write(fd_12, help_string, max_read); // записываем в первый канал

        if (size != max_read) {
            printf("Can\'t write all string to FIFO\n");
            exit(-1);
        }
    } while (read_bytes == max_read);

    if (close(fd_12) < 0) {
        printf("parent: Can\'t close writing side of FIFO\n");
        exit(-1);
    }

    if (close(input) < 0) {
        printf("Can\'t close file\n");
    }

    fd_23 = open(second_channel, O_RDONLY);
    if (fd_23 < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    // Считываем результат выполнения функции из второго канала и записываем в файл

    size = read(fd_23, string, buffer);

    if (size < 0) {
        printf("Can\'t read string from FIFO\n");
        exit(-1);
    }

    if (close(fd_23) < 0) {
        printf("Can\'t close FIFO\n");
        exit(-1);
    }


    int output = open(argv[2], O_WRONLY | O_CREAT, 0666);

    if (output < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    size = write(output, string, strlen(string));

    if (size != strlen(string)) {
        printf("Can\'t write all string\n");
        exit(-1);
    }

    if (close(output) < 0) {
        printf("Can\'t close file\n");
    }

    unlink(first_channel);
    unlink(second_channel);

    return 0;
}