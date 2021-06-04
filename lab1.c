#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define create_arr_double(r) create_arr(r, print_value_double, Printarr, input_value_double, input_arr, BubbleSortDouble, SQRDouble, MapDouble, ConcatenationDouble, DoubleWhere)

#define create_arr_complex(r) create_arr(r, print_value_complex, Printarr, input_value_complex, input_arr, BubbleSortComplex, SQRComplex, MapComplex, ConcatenationComplex, ComplexWhere)

typedef struct Arr
{
    void **values;

    int count;

    void *(*print_value)(void *, int);

    void *(*print)(void *);

    void *(*input_value)(void *, int);

    void *(*input)(void *);

    void *(*sort)(void *example);

    void *(*SQR)(void *);

    void *(*map)(void *);

    void *(*concat)(void *, void *);

    void *(*where)(void *);
} Arr;

void *SQRDouble(void *example);

void *SQRComplex(void *example);

void *print_value_complex(void *a, int r);

void *print_value_double(void *a, int r);

void *Printarr(void *a);

void *ConcatenationDouble(void *a, void *b);

void *ConcatenationComplex(void *a, void *b);

void *create_double();

void *create_complex();

void *input_value_double(void *a, int r);

void *input_value_complex(void *a, int r);

void *input_arr(void *a);

void *BubbleSortDouble(void *example);

void *MapDouble(struct Arr *example, void *(*SQR)(void *));

void *MapComplex(struct Arr *example, void *(*SQR)(void *));

void *create_arr(int r, void *print_value, void *print, void *input_value, void *input, void *sort, void *SQR, void *map, void *concat, void *where);

int bul_complex(double complex v);

int bul_double(double v);

void *DoubleWhere(void *a);

void *ComplexWhere(void *a);

void *BubbleSortComplex(void *example);

void *SQRDouble(void *example)
{
    double a = *(double *)example;
    *(double *)example = a * a;
    return (void *)(example);
}

void *SQRComplex(void *example)
{
    double complex a = *(double complex *)example;
    *(double complex *)example = a * a;
    return (void *)(example);
}

void *print_value_complex(void *a, int r)
{
    Arr *m = (Arr *)a;
    double complex v = *(double complex *)(*m).values[r];
    if (cimag(v) < 0)
    {
        printf("%.1f - %.1f*I", creal(v), fabs(cimag(v)));
    }
    else
    {
        printf("%.1f + %.1f*I", creal(v), cimag(v));
    }
    return NULL;
}

void *print_value_double(void *a, int r)
{
    Arr *m = (Arr *)a;
    printf("%.1lf ", *(double *)(*m).values[r]);
}

void *Printarr(void *a)
{
    Arr *m = (Arr *)a;
    for (int i = 0; i < (*m).count; i++)
    {
        (*m).print_value(m, i);
    }
    printf("\n");
    return NULL;
}

int bul_complex(double complex v)
{
    if (cimag(v) == creal(v))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int bul_double(double v)
{
    if ((int)v % 2 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void *DoubleWhere(void *a)
{
    int sizeofRes = 0;
    Arr *m = (Arr *)a;
    for (int i = 0; i < (*m).count; ++i)
    {
        if (bul_double(*(double *)(*m).values[i]) == 1)
            sizeofRes++;
    }
    if (sizeofRes == 0)
    {
        return 0;
    }
    struct Arr *Res;
    Res = create_arr_double(sizeofRes);
    int index = 0;
    for (int i = 0; i < (*m).count; i++)
    {
        if (bul_double(*(double *)(*m).values[i]) == 1)
        {
            *(double *)(*Res).values[index] = *(double *)(*m).values[i];
            index++;
        }
    }
    return Res;
}

void *ComplexWhere(void *a)
{
    int sizeofRes = 0;
    Arr *m = (Arr *)a;
    for (int i = 0; i < (*m).count; ++i)
    {
        if (bul_complex(*(double complex *)(*m).values[i]) == 1)
            sizeofRes++;
    }
    if (sizeofRes == 0)
    {
        return 0;
    }
    struct Arr *Res;
    Res = create_arr_complex(sizeofRes);
    int index = 0;
    for (int i = 0; i < (*m).count; i++)
    {
        if (bul_complex(*(double complex *)(*m).values[i]) == 1)
        {
            *(double complex *)(*Res).values[index] = *(double complex *)(*m).values[i];
            index++;
        }
    }
    return Res;
}

void *ConcatenationDouble(void *a, void *b)
{
    Arr *first = (Arr *)a;
    Arr *second = (Arr *)b;
    struct Arr *Res;
    Res = create_arr_double((*first).count + (*second).count);
    int index = 0;
    for (int i = 0; i < (*first).count; ++i)
    {
        *(double *)((*Res).values[i]) = *(double *)((*first).values[i]);
        index++;
    }
    for (int i = 0; i < (*second).count; ++i)
    {
        *(double *)((*Res).values[index]) = *(double *)((*second).values[i]);
        index++;
    }
    return Res;
}

void *ConcatenationComplex(void *a, void *b)
{
    Arr *first = (Arr *)a;
    Arr *second = (Arr *)b;
    struct Arr *Res;
    Res = create_complex();
    int index = 0;
    for (int i = 0; i < (*first).count; ++i)
    {
        *(double complex *)((*Res).values[i]) = *(double complex *)((*first).values[i]);
        index++;
    }
    for (int i = 0; i < (*second).count; ++i)
    {
        *(double complex *)((*Res).values[index]) = *(double complex *)((*second).values[i]);
        index++;
    }
    return Res;
}

void *input_value_double(void *a, int r)
{
    Arr *m = (Arr *)a;
    scanf("%lf", (double *)((*m).values[r]));
    return m;
}

void *input_value_complex(void *a, int r)
{
    Arr *m = (Arr *)a;
    double d1, d2;
    scanf("%lf%lf", &d1, &d2);
    *(double complex *)((*m).values[r]) = d1 + d2 * I;
    return m;
}

void *input_arr(void *a)
{
    Arr *m = (Arr *)a;
    printf("vvedite elementi: ");
    for (int i = 0; i < (*m).count; i++)
    {
        m = (*m).input_value(m, i);
    }
    return m;
}

void *MapDouble(struct Arr *example, void *(*SQR)(void *))
{
    Arr *m = (Arr *)example;
    for (int i = 0; i < example->count; ++i)
    {
        *(double *)((*m).values[i]) = *(double *)(SQRDouble((*m).values[i]));
    }
    return m;
}

void *MapComplex(struct Arr *example, void *(*SQR)(void *))
{
    Arr *m = (Arr *)example;
    for (int i = 0; i < example->count; ++i)
    {
        *(double *)((*m).values[i]) = *(double *)(SQRDouble((*m).values[i]));
    }
    return m;
}

void *BubbleSortDouble(void *example)
{
    Arr *m = (Arr *)example;
    int count = (*m).count;
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count; ++j)
        {
            if ((*(double *)((*m).values[i])) <= (*(double *)((*m).values[j])))
            {
                int t = *(double *)((*m).values[i]);
                *(double *)((*m).values[i]) = *(double *)((*m).values[j]);
                *(double *)((*m).values[j]) = t;
            }
        }
    }
    return m;
}

void *BubbleSortComplex(void *example)
{
    printf("eror, net sortirovki for complex");
    return example;
}

void *create_arr(int r, void *print_value, void *print, void *input_value, void *input, void *sort, void *SQR, void *map, void *concat, void *where)
{
    Arr *m = malloc(sizeof(Arr));
    (*m).count = *(int *)malloc(sizeof(int));
    (*m).count = r;
    (*m).values = (void **)malloc(sizeof(void *) * r);
    for (int i = 0; i < r; i++)
    {
        (*m).values[i] = (void *)malloc(sizeof(void *));
    }
    (*m).print_value = print_value;
    (*m).print = print;
    (*m).input_value = input_value;
    (*m).input = input;
    (*m).sort = sort;
    (*m).map = map;
    (*m).SQR = SQR;
    (*m).concat = concat;
    (*m).where = where;
    return m;
}

void *create_double()
{
    int r;
    printf("kolichestvo elementov: ");
    scanf("%d", &r);
    while (r < 1)
    {
        printf("Enter a positive chislo!\n kolichestvo elementov: ");
        scanf("%d", &r);
    }
    Arr *m = create_arr_double(r);
    return (*m).input(m);
}

void *create_complex()
{
    int r;
    printf("kolichestvo elementov: ");
    scanf("%d", &r);
    while (r < 1)
    {
        printf("Enter a positive integer!\nkolichestvo elementov: ");
        scanf("%d", &r);
    }
    Arr *m = create_arr_complex(r);
    printf("Enter two numbers separated by a space!");
    return (*m).input(m);
}

int main()
{
    printf("Select the type of massiv:\n1 - double\n2 - complex\n");
    int s1 = 0;
    Arr *m;
    while ((s1 < 1) || (s1 > 2))
    {
        scanf("%d", &s1);
        switch (s1)
        {
        case 1:
        {
            m = create_double();
            break;
        }
        case 2:
        {
            m = create_complex();
            break;
        }
        default:
        {
            printf("Enter a number from the list!\n");
            break;
        }
        }
    }
    int s2 = 0, r, c;
    Arr *m1;
    while (s2 != 6)
    {
        printf("\nYour arr:\n");
        (*m).print(m);
        printf("\n");
        printf("Select the action with arr:\n1 - input new arr\n2 - sortirovka\n3 - map\n4 - Concatenation\n5 - where\n6 - exit\n");
        scanf("%d", &s2);
        switch (s2)
        {
        case 1:
        {
            if (s1 == 1)
                m = create_double();
            if (s1 == 2)
                m = create_complex();
            break;
        }
        case 2:
        {
            m = (*m).sort(m);
            break;
        }
        case 3:
        {
            m = (*m).map(m);
            break;
        }
        case 4:
        {
            if (s1 == 1)
                m1 = create_double();
            if (s1 == 2)
                m1 = create_complex();
            m = (*m).concat(m, m1);
            break;
        }
        case 5:
        {
            m = (*m).where(m);
            break;
        }
        case 6:
        {
            break;
        }
        default:
        {
            printf("Enter a number from the list!\n");
            break;
        }
        }
    }
    return 0;
}