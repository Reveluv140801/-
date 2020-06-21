#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 256

int main() {
	int num, price = 0;
	scanf("%d", &num);
	int* road = (int*)malloc(sizeof(int*) * (num - 1));
	int* oil = (int*)malloc(sizeof(int*) * num);

	for (int i = 0; i < num - 1; i++) {
		scanf("%d", &road[i]);
	}

	for (int j = 0; j < num; j++) {
		scanf("%d", &oil[j]);
	}
	int least = oil[0];

	for (int k = 0; k < num - 1; k++) {
		if (oil[k] < least) {
			least = oil[k];
		}
		price += least * road[k];
	}

	printf("%d", price);

	free(road);
	free(oil);

	return 0;
}