#ifndef MATRIXFUNC_H
#define MATRIXFUNC_H

/* Функция 5: сумма всех элементов матрицы */
long sum_all(const int *matptr, int strok, int stolb);

/* Функция 17: сумма элементов, значения которых лежат в диапазоне k-m
   (границы включаются; если k > m, границы меняются местами) */
long sum_in_range(const int *matptr, int strok, int stolb, int k, int m);

/* Функция 26: сумма элементов побочной диагонали.
   Результат записывается по указателю result.
   Возвращает 0 при успехе, -1 если матрица не квадратная. */
int sum_secondary_diag(const int *matptr, int strok, int stolb, long *result);

#endif