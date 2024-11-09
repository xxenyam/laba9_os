#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define NUM_SIGNALS 8 

// Обробник сигналу для дочірнього процесу
void handle_rt_signal(int sig, siginfo_t *info, void *context) {
    printf("Отримано сигнал: %d, Номер виклику: %d\n", sig, info->si_value.sival_int);
}

// Функція дочірнього процесу
void child_process() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_rt_signal;
    sigemptyset(&sa.sa_mask);

    for (int i = SIGRTMIN; i < SIGRTMIN + NUM_SIGNALS; ++i) {
        sigaction(i, &sa, NULL);
    }

    while (1) {
        pause(); 
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Помилка створення процесу");
        return 1;
    }

    if (pid == 0) {
        child_process();
    } else {
        // Батьківський процес
        sleep(1); 

        for (int i = 0; i < NUM_SIGNALS; ++i) {
            union sigval value;
            value.sival_int = i + 1; 

            if (sigqueue(pid, SIGRTMIN + i, value) == -1) {
                perror("Не вдалося надіслати сигнал");
            }

            sleep(1); 
        }

        kill(pid, SIGTERM);

        wait(NULL);
        printf("Батьківський процес завершено.\n");
    }

    return 0;
}