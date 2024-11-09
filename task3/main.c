#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Флаг для синхронізації процесів
volatile sig_atomic_t flag = 0;

// Обробник сигналу SIGUSR1
void handler(int signum) {
    flag = 1;  
}

int main() {
    pid_t pid;
    
    signal(SIGUSR1, handler);
    
    if ((pid = fork()) == 0) {
        // Дочірній процес
        for (int i = 0; i < 10; i++) {
            while (flag == 0);  
            printf("Дочірній процес: Повідомлення %d\n", i + 1);
            flag = 0;  
            kill(getppid(), SIGUSR1);  
        }
    } else if (pid > 0) {
        // Батьківський процес
        for (int i = 0; i < 10; i++) {
            printf("Батьківський процес: Повідомлення %d\n", i + 1);
            kill(pid, SIGUSR1);  
            while (flag == 0);  
            flag = 0;  
        }
    } else {
        perror("fork");
        return 1;
    }
    
    return 0;
}