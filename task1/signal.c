#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Обробник сигналів
void signal_handler(int signo) {
    if (signo == SIGINT) {
        printf("Захоплено сигнал SIGINT\n");
    } else if (signo == SIGTERM) {
        printf("Захоплено сигнал SIGTERM\n");
    } else if (signo == SIGUSR1) {
        printf("Захоплено сигнал SIGUSR1 - завершення роботи\n");
        exit(0);
    }
}

int main() {
    // Встановлення обробників сигналів
    signal(SIGINT, signal_handler);  
    signal(SIGTERM, signal_handler); 
    signal(SIGUSR1, signal_handler); 

    // Відновлення стандартної поведінки для SIGPROF
    signal(SIGPROF, SIG_DFL);

    // Ігнорування SIGHUP
    signal(SIGHUP, SIG_IGN);

    printf("Програма запущена. Очікування сигналів...\n");

    while (1) {
        pause();  
    }
    return 0;
}