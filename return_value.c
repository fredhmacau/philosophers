#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void    *roll_dice()
{
    int value = (rand() % 6) + 1;
    printf("%d\n", value);
    return (void *) &value;
}

int main(int ac, char **av)
{
    pthread_t threads;
    int *res;
    srand(time(NULL));
    if (pthread_create(&threads, NULL, &roll_dice, NULL) != 0)
    {
        perror("Error in created threads\n");
        return (3);
    }
    if (pthread_join(threads, (void **) &res))
    {
        perror("Error init thread\n");
        return (4);
    }
    printf("Result: %d\n", *res);
    return (0);
}