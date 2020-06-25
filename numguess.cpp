#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int listsum(int a[][3]) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += a[i][j];
        }
    }
    return sum;
}

void listcheck(int a[][3], int b) {
    int change = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b == a[i][j]) {
                a[i][j] = 0;
                change++;
            }
        }
    }
    if (change == 0) {
        printf("Not Found");
    }
}

void printlist(int a[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\b\n");
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int num[3][3], guess, attempt = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            num[i][j] = rand() % 9 + 1;
        }
    }
    printlist(num);

    while (listsum(num) != 0) {
        attempt++;
        printf("숫자를 입력하세요 : ");
        scanf("%d", &guess);
        listcheck(num, guess);
        printlist(num);
    }

    printf("Game Over\n");
    printf("총 %d회 만에 모든 숫자를 맞췄습니다.", attempt);
    return 0;
}