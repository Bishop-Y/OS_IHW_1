#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


int is_palindrome(char *str, int start, int end) {
    while (start < end) {
        if (tolower(str[start]) != tolower(str[end])) {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

void find_palindromes(char *str) {
    int i, j, k;
    int len = strlen(str);
    char *result = str;

    for (i = 0, k = 0; i < len; i++) {
        while (!isalpha(str[i]) && i < len) {
            i++;
        }
        j = i + 1;
        while (isalpha(str[j]) && j < len) {
            j++;
        }
        if (is_palindrome(str, i, j - 1)) {
            if (k > 0) {
                result[k++] = ' ';
            }
            while (i < j) {
                result[k++] = str[i++];
            }
        }
        i = j;
    }
    result[k] = '\0';
}

const int buffer = 5000;
const int max_read = 10;
const char *first_channel = "pipe1.fifo";
const char *second_channel = "pipe2.fifo";

int main(int argc, char *argv[]) {
    int fd_12, fd_23, size;
    char string[buffer];

    mknod(first_channel, S_IFIFO | 0666, 0);
    mknod(second_channel, S_IFIFO | 0666, 0);

    ssize_t read_bytes;
    ssize_t total_counter = 0;
    char *help_string;

    fd_12 = open(first_channel, O_RDONLY);
    if (fd_12 < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    do {
        // Считывание из первого канала
        read_bytes = read(fd_12, help_string, max_read);
        if (read_bytes == -1) {
            printf("Can\'t read from fd_12\n");
            exit(-1);
        }
        help_string[read_bytes] = '\0';
        strcat(string, help_string);
        total_counter += read_bytes;
        help_string[total_counter] = '\0';
    } while (read_bytes == max_read);

    if (close(fd_12) < 0) {
        printf("parent: Can\'t close writing side of FIFO\n");
        exit(-1);
    }

    find_palindromes(string); // вызываем функцию, которая решает поставленную задачу

    fd_23 = open(second_channel, O_WRONLY);
    if (fd_23 < 0) {
        printf("Can\'t open FIFO-2 for writting\n");
        exit(-1);
    }

    size = write(fd_23, string, buffer); // записываем во второй канал

    if (size != buffer) {
        printf("Can\'t write all string to FIFO\n (size = %d)", size);
        exit(-1);
    }
    if (close(fd_23) < 0) {
        printf("parent: Can\'t close FIFO\n");
        exit(-1);
    }
    return 0;
}
