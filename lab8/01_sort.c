#include <stdio.h>
#include <malloc.h>

void comb_sort(int * array, int size, FILE *file) 
{
    int interval = size;
    int swaps = 1;
    int i, j;
 
    while ( interval > 1 || swaps ) {
        interval = (int)(interval / 1.247f);
        if ( interval < 1 )
            interval = 1;
        swaps = 0;
        for ( i = 0; i < size - interval; ++i ) {
            j = i + interval;
            
            if ( array[i] > array[j] ) {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                swaps = 1;
                
                for (int k = 0; k < size; k++)
                {
                if (k != 0)
                fprintf(file, " ");
                fprintf(file, "%d", array[k]);
                }
                fprintf(file, "\n");
            }
        }
    }
}

void ShellSort(int * array, int size, FILE *file) 
{
    int i, j, step;
    int tmp;
    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++)
        {
            tmp = array[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < array[j - step])
                    array[j] = array[j - step];
                else
                    break;
            }
            array[j] = tmp;
            
            for (int k = 0; k < size; k++)
                {
                if (k != 0)
                fprintf(file, " ");
                fprintf(file, "%d", array[k]);
                }
                fprintf(file, "\n");
        }
        
}

int main()
{
    FILE *file;
    int *arr_comb_sort = (int*)malloc(sizeof(int)), *arr_ShellSort = (int*)malloc(sizeof(int)), size, i;
    double k;
    scanf("%lf", &k);
    size = k;
    arr_comb_sort = (int*)realloc(arr_comb_sort, size * sizeof(int));
    arr_ShellSort = (int*)realloc(arr_ShellSort, size * sizeof(int));

    for (i = 0; i < size; i++)
    {
        scanf("%lf", &k);
        arr_comb_sort[i] = k;
        arr_ShellSort[i] = k;
    }
    
    file = fopen("comb_sort.log", "w+");
    fclose(file);
    file = fopen("comb_sort.log", "w+");
    comb_sort(arr_comb_sort, size, file);
    fclose(file);


    file = fopen("ShellSort.log", "w+");
    fclose(file);
    file = fopen("ShellSort.log", "r+");
    ShellSort(arr_ShellSort, size, file);
    fclose(file);
    
    for (int k = 0; k < size; k++)
    {
        if (k != 0)
            printf(" ");
        printf("%d", arr_ShellSort[k]);
    }
    return 0;
}

