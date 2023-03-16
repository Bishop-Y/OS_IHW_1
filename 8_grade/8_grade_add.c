#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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



int main(int argc, char *argv[]) {
    const int buffer = 5000;
    const char *first_channel = "first_channel.fifo";
    const char *second_channel = "second_channel.fifo";

    int fd_12, fd_23, size;
    char string[buffer];

    mknod(first_channel, S_IFIFO | 0666, 0);
    mknod(second_channel, S_IFIFO | 0666, 0);

    fd_12 = open(first_channel, O_RDONLY);

    if (fd_12 < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    // Считывание из первого канала
    size = read(fd_12, string, buffer);

    if (size < 0) {
        printf("Can\'t read string from FIFO\n");
        exit(-1);
    }

    find_palindromes(string); // вызываем функцию, которая решает поставленную задачу

    if (close(fd_12) < 0) {
        printf("child: Can\'t close FIFO\n");
        exit(-1);
    }

    fd_23 = open(second_channel, O_WRONLY);

    if (fd_23 < 0) {
        printf("Can\'t open FIFO for writing\n");
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