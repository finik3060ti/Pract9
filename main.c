#include <stdio.h>
#include "matrixfunc.h"

#define MAX_SIZE 10

/* Очистка остатка строки ввода */
void clear_line(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Ввод целого числа с приглашением.
   Возвращает 1 при успехе, 0 при конце файла. */
int ask_int(const char *prompt, int *value)
{
    int r;

    printf("%s", prompt);
    r = scanf("%d", value);
    while (r == 0) {
        printf("Ошибка: нужно ввести целое число.\n");
        clear_line();
        printf("%s", prompt);
        r = scanf("%d", value);
    }
    if (r == EOF)
        return 0;
    clear_line();
    return 1;
}

/* Пункт a: задать размеры. Возвращает 1 при успехе, 0 при конце файла. */
int set_size(int *strok, int *stolb)
{
    if (!ask_int("Строки: ", strok))
        return 0;
    while (*strok < 1 || *strok > MAX_SIZE) {
        printf("Ошибка: допустимо от 1 до %d.\n", MAX_SIZE);
        if (!ask_int("Строки: ", strok))
            return 0;
    }

    if (!ask_int("Столбцы: ", stolb))
        return 0;
    while (*stolb < 1 || *stolb > MAX_SIZE) {
        printf("Ошибка: допустимо от 1 до %d.\n", MAX_SIZE);
        if (!ask_int("Столбцы: ", stolb))
            return 0;
    }

    return 1;
}

/* Пункт b: заполнение. Возвращает 1 при успехе, 0 при конце файла. */
int fill_matrix(int *matptr, int strok, int stolb)
{
    int i, j;

    for (i = 0; i < strok; i++)
        for (j = 0; j < stolb; j++) {
            printf("Элемент [%d][%d]: ", i, j);
            if (!ask_int("", matptr + i * stolb + j))
                return 0;
        }
    return 1;
}

/* Пункт c: значения и адреса элементов */
void show_matrix(const int *matptr, int strok, int stolb)
{
    int i, j;

    printf("Значения:\n");
    for (i = 0; i < strok; i++) {
        for (j = 0; j < stolb; j++)
            printf("%8d ", *(matptr + i * stolb + j));
        printf("\n");
    }

    printf("Адреса элементов:\n");
    for (i = 0; i < strok; i++) {
        for (j = 0; j < stolb; j++)
            printf("%p ", (void *)(matptr + i * stolb + j));
        printf("\n");
    }
}

int main(void)
{
    int matrix[MAX_SIZE * MAX_SIZE];
    int strok = 0, stolb = 0;
    int size_set = 0, filled = 0;
    int running = 1;
    int r, k, m;
    long result;
    char choice;

    while (running) {
        printf("\na Задать размер матрицы (строки, столбцы)\n");
        printf("b Заполнить матрицу\n");
        printf("c Представление матрицы (значения, адреса элементов)\n");
        printf("d Сумма всех элементов матрицы\n");
        printf("e Сумма элементов в диапазоне значений k-m\n");
        printf("f Сумма элементов побочной диагонали\n");
        printf("g Выход\n");
        printf("Выберите пункт: ");

        r = scanf(" %c", &choice);
        if (r == EOF) {
            printf("\nКонец ввода. Выход.\n");
            break;
        }
        clear_line();

        if (choice >= 'c' && choice <= 'f' && !filled) {
            printf("Сначала задайте размер (a) и заполните матрицу (b).\n");
            continue;
        }

        switch (choice) {
        case 'a':
            if (!set_size(&strok, &stolb)) {
                running = 0;
                break;
            }
            size_set = 1;
            filled = 0;
            break;
        case 'b':
            if (!size_set) {
                printf("Сначала задайте размер матрицы (a).\n");
                break;
            }
            if (!fill_matrix(matrix, strok, stolb)) {
                running = 0;
                break;
            }
            filled = 1;
            break;
        case 'c':
            show_matrix(matrix, strok, stolb);
            break;
        case 'd':
            printf("Сумма всех элементов: %ld\n", sum_all(matrix, strok, stolb));
            break;
        case 'e':
            if (!ask_int("k: ", &k) || !ask_int("m: ", &m)) {
                running = 0;
                break;
            }
            printf("Сумма элементов в диапазоне: %ld\n",
                   sum_in_range(matrix, strok, stolb, k, m));
            break;
        case 'f':
            if (sum_secondary_diag(matrix, strok, stolb, &result) == 0)
                printf("Сумма побочной диагонали: %ld\n", result);
            else
                printf("Ошибка: матрица не квадратная.\n");
            break;
        case 'g':
            running = 0;
            break;
        default:
            printf("Неверный пункт меню.\n");
        }
    }

    return 0;
}