# OS_IHW_1
## Епифанов Артём Михайлович, БПИ 217, вариант 29.
## Работа выполнена на 9 баллов.
## Условие задачи:
* Разработать программу, которая ищет в ASCII-строке слова — палиндромы и формирует из них новую строку, в которой слова разделяются пробелами. Слова состоят из букв. Все остальные
символы являются разделителями слов.


---- 

# 4 балла:

### 1. Приведено решение задачи на C: <br>
> [4_grade.c](https://github.com/Bishop-Y/OS_IHW_1/blob/main/4_grade/4_grade.c)
### 2. Запуск программы:
Компиляция:
> * gcc -o 4_grade.exe 4_grade.c <br>

Запуск:
> * ./4_grade.exe input1.txt output1.txt <br>

### 3. Схема:
> * Первый процесс (родитель второго): читает текстовые данные из заданного файла и через неименованный канал 1
> передает их второму процессу. </br></br>
> * Второй процесс (ребёнок первого и родитель третьего): осуществляет обработку полученных из канала 1 данных в
> соответствии с заданием и передаёт результат обработки через неименованный канал 2 третьему
> процессу. </br></br>
> * Третий процесс (ребёнок второго): осуществляет вывод полученных из канала 2 данных в заданный файл вывода. </br>
<br>

----

# 5 баллов:

### 1. Приведено решение задачи на C:

> [5_grade.c](https://github.com/Bishop-Y/OS_IHW_1/tree/main/5_grade/5_grade.c)

### 2. Запуск программы:
Компиляция:
> * gcc -o 5_grade.exe 5_grade.c <br>

Запуск:
> * ./5_grade.exe input1.txt output1.txt <br>

### 3. Схема:

> * Первый процесс (родитель второго): читает текстовые данные из заданного файла и через именованный канал (pipe1.fifo) передает их второму процессу. </br></br>
> * Второй процесс (ребёнок первого и родитель третьего): осуществляет обработку полученных из именованного канала (pipe1.fifo) данных в соответствии с заданием и передаёт результат обработки через именованный канал (pipe2.fifo) третьему процессу. </br></br>
> * Третий процесс (ребёнок второго): осуществляет вывод полученных из канала (pipe2.fifo) данных в заданный файл вывода. </br>
----

# 6 баллов:

### 1. Приведено решение задачи на C:

> * [6_grade.c](https://github.com/Bishop-Y/OS_IHW_1/tree/main/6_grade/6_grade.c)

### 2. Запуск программы:
Компиляция:
> * gcc -o 6_grade.exe 6_grade.c <br>

Запуск:
> * ./6_grade.exe input1.txt output1.txt <br>

### 3. Схема:

> * Первый процесс (родитель второго): читает текстовые данные из заданного файла и через неименованный канал 1 передает их второму процессу. </br></br>
> * Второй процесс (ребёнок первого): осуществляет обработку данных в соответствии с заданием и передаёт результат обработки через неименованный канал 2 обратно первому процессу. </br></br>
> * Первый процесс: висит, пока второй процесс (ребёнок) не запишет что-либо во второй канал, затем он считает данные из второго канала и запишет их в заданный файл вывода.
---- 

# Отчёт 7 баллов:

### 1. Приведено решение задачи на C:

> * [7_grade.c](https://github.com/Bishop-Y/OS_IHW_1/tree/main/7_grade/7_grade.c)

### 2. Запуск программы:
Компиляция:
> * gcc -o 7_grade.exe 7_grade.c <br>

Запуск:
> * ./7_grade.exe input1.txt output1.txt <br>

### 3. Схема решаемой задачи:

> * Первый процесс (родитель второго): читает текстовые данные из заданного файла и через именованный канал (pipe1.fifo) передаёт их второму процессу. </br></br>
> * Второй процесс (ребёнок первого): осуществляет обработку полученных из канала (pipe1.fifo) данных в соответствии с заданием и передаёт результат обработки через именованный канал (pipe2.fifo) обратно первому процессу. </br></br>
> * Первый процесс: висит, пока второй процесс (его ребёнок)  не запишет что-либо во второй канал (pipe2.fifo), затем он считает данные из второго канала (pipe2.fifo) и запишет их в заданный файл вывода.
---- 

# 8 баллов:

### 1. Приведено решение задачи на C:

> * [8_grade_main.c](https://github.com/Bishop-Y/OS_IHW_1/blob/main/8_grade/8_grade_main.c) <br>
> * [8_grade_add.c](https://github.com/Bishop-Y/OS_IHW_1/blob/main/8_grade/8_grade_add.c)

### 2. Запуск программы:
Компиляция:
> * gcc -o 8_grade_main.exe 8_grade_main.c <br>
> * gcc -o 8_grade_add.exe 8_grade_add.c <br>

Запуск (в любом порядке):
> * ./8_grade_main.exe input1.txt output1.txt <br>
> * ./8_grade_add.exe <br>

### 3. Схема:

> * Первый процесс (в файле 8_grade_main.c): читает текстовые данные из заданного файла и через именованный канал (pipe1.fifo) передает их второму процессу. </br></br>
> * Второй процесс (в файле 8_grade_add.c): осуществляет обработку полученных из канала (pipe1.fifo) данных в соответствии с заданием и передаёт результат обработки через именованный канал (pipe2.fifo) обратно первому процессу. </br></br>
> * Первый процесс: ждёт, пока второй незвисимый процесс не запишет что-то во второй канал (pipe2.fifo), затем он считает данные из второго канала (pipe2.fifo) и запишет их в заданный файл вывода.
----

# Отчёт 9 баллов:

### 1. Приведено решение задачи на C:

> * [9_grade_main.c](https://github.com/Bishop-Y/OS_IHW_1/blob/main/9_grade/9_grade_main.c) <br>
> * [9_grade_add.c](https://github.com/Bishop-Y/OS_IHW_1/blob/main/9_grade/9_grade_add.c)

### 2. Запуск программы:
Компиляция:
> * gcc -o 9_grade_main.exe 9_grade_main.c <br>
> * gcc -o 9_grade_add.exe 9_grade_add.c <br>

Запуск (в любом порядке):
> * ./9_grade_main.exe input1.txt output1.txt <br>
> * ./9_grade_add.exe <br>

### 3. Схема :

> * Первый процесс (в файле 9_grade_main.c): читает текстовые данные из заданного файла и через именованный канал (pipe1.fifo) порционно по 20 символов передает их второму процессу. </br></br>
> * Второй процесс (в файле 9_grade_add.c)(отдельном терминале): по частям получает данные по 10 символов из канала (pipe1.fifo) и сразу же обрабатывает порции в соответствии с заданием и после полной обработки передаёт результат обработки через именованный канал (pipe2.fifo) обратно первому процессу. </br></br>
> * Первый процесс: ждёт, пока второй незвисимый процесс не запишет что-то во второй канал (pipe2.fifo), затем он считает данные из второго канала (pipe2.fifo) и запишет их в заданный файл вывода.
