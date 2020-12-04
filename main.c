#include <stdio.h>
#include <stdlib.h>

#define MSG_1 "Enter array capacity: "
#define MSG_2 "Wrong input\nEnter again: "
#define MSG_3 "Enter %d element: "
#define MSG_4 "Wrong input\n"
#define MSG_5 "Not enough memeory\n"
#define MSG_6 "Can't form an array with 0 elements"
#define MSG_7 "Fewer than two or zero extremities found\n"
#define MSG_8 "%ld and %ld elements are extremities\ndistance between them: %ld"

int read_array_size ();
void read_array_elements(int *counter, int N, int *array);
int *find_extremities (int N, int array[]);
int count_extremities(int N, int extremities[]);
void find_furthest_extremities(int N, int extremities[], int array[], int *start, int *end);

int main()
{
    int N, counter;

    N = read_array_size();

    if (N > 0){
        //counter = 0;
        //if(array != 0){
            int *array;
            read_array_elements(&counter, N, &array);

            int *extremities = find_extremities(N, array);

            counter = count_extremities(N, extremities);

            if (counter >= 2){
                int start, end;
                find_furthest_extremities(N, extremities, array, &start, &end);
                printf(MSG_8, start + 1, end + 1, end - start - 1);

            } else {
                printf(MSG_7);
            }

            free(array);
            free(extremities);
        //} else{
         //   printf(MSG_5);
        //}
    } else {
        printf(MSG_6);
    }
    return 0;
}

void find_furthest_extremities(int N, int extremities[], int array[], int *max_start, int *max_end)
{
    int max_dist = 0;
    int dist;

    for(int i = 1; i < N - 1; ++i)
        if (extremities[i] == 1){
            printf("\n");
            for (int j = i + 1; j < N; ++j){
                if (extremities[j] == 1){
                    dist = j - i;
                    if (dist > max_dist){
                        *max_start = i;
                        *max_end = j;
                        max_dist = dist;
                    }
                    break;
                }
            }
        }
    /*for(int i = N - 1; i > 0; --i)
        if (extremities[i] == 1){
            *end = &array[i];
            break;
        }*/
}


int count_extremities(int N, int extremities[])
{
    int counter = 0;
    for(int i = 1; i < N - 1; ++i)
        if (extremities[i] == 1)
            ++counter;
    return counter;
}

int *find_extremities (int N, int array[])
{
    int *found_extremities = NULL;
    found_extremities = (int *)calloc(N, sizeof(int));
    if (found_extremities != 0){
        for(int i = 1; i < N - 1; ++i){
            if(array[i] > array[i - 1] && array[i] > array[i + 1]){
                ++found_extremities[i];
            } else if(array[i] < array[i - 1] && array[i] < array[i + 1]){
                ++found_extremities[i];
            }
        }
    }
    return found_extremities;
}

void read_array_elements(int *counter, int N, int *array)
{

    int *array_new = NULL;
    array_new = (int *)malloc(N * sizeof(int));
    int num;
    while(*counter < N){
        printf(MSG_3, *counter + 1);
        if((scanf("%d", &num) == 1) && (getchar() == '\n')){
                array_new[(*counter)++] = num;
        } else{
            while(getchar() != '\n');
            printf(MSG_4);
        }
    }
    *array = array_new;
}


int read_array_size ()
{
    int num;
    printf(MSG_1);
    while (1){
        if((scanf("%d", &num) == 1) && (getchar() == '\n')){
            return num;
        } else{
            while(getchar() != '\n');
            printf(MSG_2);
        }
    }
}
