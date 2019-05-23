#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define CHAIRS 5                /* number of seats for customers waiting. */
#define TRUE 1

sem_t customers;                /* customer number waiting for service.*/
sem_t barbers;                  /* number of barbers waiting for customers.*/
sem_t mutex;                    /* for mutual exclusion. */
int waiting = 0;                /* customers who are waiting. */

void cut_hair() {
    printf("The barber is cutting the client's hair\n");
    sleep(3);
}

void *barber(void *arg) {
    while(TRUE) {
        sem_wait(&customers);   /* go to sleep if the number of clients is 0.*/
        sem_wait(&mutex);       /* gets access to 'waiting'.*/
        waiting = waiting - 1;  /* decreases from a waiting client count because it will be serviced.*/
        sem_post(&barbers);     /* a barber is now ready to cut hair.*/
        sem_post(&mutex);       /* free 'waiting'. */
        cut_hair();             /* cuts hair. */
    }

    pthread_exit(NULL);
}

void *customer(void *arg) {
    sem_wait(&mutex);
    /*If the amount of waiting customers is less than 
    the amount of chairs means there is room to sit and wait.*/
    if(waiting < CHAIRS){     
        cout << "Customer arrived to cut hair" << endl;
        waiting = waiting + 1;  
        sem_post(&customers);   
        sem_post(&mutex);       
        sem_wait(&barbers);     
        cout << "The customer is having his hair cut" << endl;
    }

    else{ /*The barber is full and customer will not wait.*/
        sem_post(&mutex);       
        cout << "The customer gave up (the hall is very full)" << endl;
    }

    pthread_exit(NULL);
}




int main() {
    sem_init(&customers, TRUE, 0);
    sem_init(&barbers, TRUE, 0);
    sem_init(&mutex, TRUE, 1);

    pthread_t b, c;

    /* barber*/
    pthread_create(&b, NULL,barber, NULL);

    /* Undefined number of clients that will be created to go to the barbershop.*/
     while(TRUE) {
        pthread_create(&c, NULL, customer, NULL);
        sleep(1);
        cout << "customers waiting in the chairs: " << waiting << endl;
        sleep(1);

    }

    return 0;
}

/*
    Material used as support for understanding the problem and the code:
    http://ces33.blogspot.com/2009/05/o-problema-do-barbeiro-dorminhoco-com_07.html
    https://homepages.dcc.ufmg.br/~scampos/cursos/so/aulas/aula7.html
    http://www.ic.unicamp.br/~islene/mc514/barbeiro/barbeiro.pdf
    https://en.wikipedia.org/wiki/Sleeping_barber_problem

*/