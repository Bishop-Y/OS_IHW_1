#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    const int buffer = 5000;
    const char *first_channel = "first_channel.fifo";
    const char *second_channel = "second_channel.fifo";

    (void) umask(0);

    if (argc != 3) {
        printf("Run the program with 2 arguments\n \"./program.exe input.txt output.txt\"\n");
        return 0;
    }

    int fd_12, fd_23, size;
    char string[buffer];

    mknod(first_channel, S_IFIFO | 0666, 0);
    mknod(second_channel, S_IFIFO | 0666, 0);

    // Первый процесс - считать из файла и направить во второй процесс
    int input = open(argv[1], O_RDONLY, 0666);

    if (input < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }

    read(input, string, buffer);

    if (close(input) < 0) {
        printf("Can\'t close file\n");
    }

    fd_12 = open(first_channel, O_WRONLY);
    if (fd_12 < 0) {
        printf("Can\'t open FIFO for writing\n");
        exit(-1);
    }

    size = write(fd_12, string, buffer); // записываем в первый канал

    if (size != buffer) {
        printf("Can\'t write all string to FIFO\n");
        exit(-1);
    }
    if (close(fd_12) < 0) {
        printf("parent: Can\'t close writing side of FIFO\n");
        exit(-1);
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