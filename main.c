/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmacau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:07:08 by fmacau            #+#    #+#             */
/*   Updated: 2024/11/08 18:07:10 by fmacau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// the initial balance is 0
int mails = 0;
void *routine()
{
    int i  = 0;
    while (i < 1000000)
    {
        mails++;
        i++;
    }
}

int main(int ac, char **av)
{ 
    pthread_t   t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(t1, NULL) != 0)
    {
        return 3;
    }
    if (pthread_join(t2, NULL) != 0)
    {
        return 4;
    }
    printf("Number of mails: %d\n", mails);
    return (0);

}
