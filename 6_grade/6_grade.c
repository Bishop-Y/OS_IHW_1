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
    char string[buffer];
    if (argc != 3) {
        printf("Run the program with 2 arguments\n \"./program.exe input.txt output.txt\"\n");
        return 0;
    }

    int fd_12[2], fd_23[2], process_1, size;

    if (pipe(fd_12) < 0) { // создаём первый канал (для передачи из первого во второй процесс)
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    if (pipe(fd_23) < 0) { // создаём второй канал (для передачи из второго в третий процесс)
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    process_1 = fork(); // создаем первые два процесса
    if (process_1 < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (process_1 > 0) { // Первый процесс
        if (close(fd_12[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }

        int input = open(argv[1], O_RDONLY, 0666);

        if (input < 0) {
            printf("Can\'t open file\n");
            exit(-1);
        }

        read(input, string, buffer); // считываем из файла
        if (close(input) < 0) {
            printf("Can\'t close file\n");
        }

        size = write(fd_12[1], string, buffer); // записываем в первый канал

        if (size != buffer) {
            printf("Can\'t write all string to pipe\n (size = %d)", size);
            exit(-1);
        }

        if (close(fd_12[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }
    } else {  // второй процесс
        if (close(fd_12[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        size = read(fd_12[0], string, buffer); // считываем из первого канала
        if (size < 0) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        find_palindromes(string); // вызываем функцию, которая решает поставленную задачу

        if (close(fd_12[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n");
            exit(-1);
        }

        size = write(fd_23[1], string, buffer); // записываем во второй канал

        if(size != buffer){
            printf("Can\'t write all string to pipe\n (size = %d)",size);
            exit(-1);
        }
        if(close(fd_23[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        exit(0);
    } // первый процесс

    while(wait(NULL) > 0) {

    }

    if(close(fd_23[1]) < 0){
        printf("child: Can\'t close writing side of pipe\n");
        exit(-1);
    }

    size = read(fd_23[0], string, buffer);// считываем из второго канала
    if(size < 0){
        printf("Can\'t read string from pipe\n");
        exit(-1);
    }
    if(close(fd_23[0]) < 0){
        printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }
    int output = open(argv[2], O_WRONLY | O_CREAT, 0666);

    if(output < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }

    size = write(output, string, strlen(string));
    if(size != strlen(string)) {
        printf("Can\'t write all string\n");
        exit(-1);
    }

    if(close(output) < 0) {
        printf("Can\'t close file\n");
    }
    return 0;
}
