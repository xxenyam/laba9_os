#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// Обробник сигналу для завершення очікування та виведення повідомлення
void alarm_handler(int signum) {
    // Нічого не робимо, просто перериваємо pause
}

int main(int argc, char *argv[]) {
    // Перевірка кількості аргументів
    if (argc < 3) {
        fprintf(stderr, "Використання: %s <час у секундах> <повідомлення>\n", argv[0]);
        return 1;
    }

    // Отримання інтервалу часу та повідомлення
    int seconds = atoi(argv[1]);
    char *message = argv[2];

    // Створення дочірнього процесу
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    // Дочірній процес: встановлення будильника та очікування
    if (pid == 0) {
        // Налаштовуємо обробник для сигналу SIGALRM
        signal(SIGALRM, alarm_handler);

        // Встановлення будильника на заданий час
        alarm(seconds);

        // Очікування завершення будильника
        pause();

        // Виведення повідомлення після спрацювання будильника
        printf("Будильник: %s\n", message);
        exit(0);
    }
    // Батьківський процес завершується
    return 0;
}