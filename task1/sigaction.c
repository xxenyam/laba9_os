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
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Встановлення обробників сигналів
    sigaction(SIGINT, &sa, NULL);  
    sigaction(SIGTERM, &sa, NULL); 
    sigaction(SIGUSR1, &sa, NULL); 

    // Відновлення SIGPROF
    struct sigaction sa_default;
    sa_default.sa_handler = SIG_DFL;
    sigaction(SIGPROF, &sa_default, NULL);

    // Ігнорування SIGHUP
    struct sigaction sa_ignore;
    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGHUP, &sa_ignore, NULL);

    printf("Програма запущена. Очікування сигналів...\n");

    while (1) {
        pause();  
    }

    return 0;
}