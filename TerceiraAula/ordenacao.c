#include <stdio.h>
#include <stdlib.h>

// Funções de ordenação (selection sort, bubble sort e merge sort)

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int n;

    // Pedir ao usuário para inserir o número de elementos
    printf("Digite o número de elementos: ");
    scanf("%d", &n);

    int arr[n];

    // Pedir ao usuário para inserir os números
    printf("Digite os %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Escolher o tipo de ordenação (Selection Sort, Bubble Sort ou Merge Sort)
    int choice;
    printf("Escolha o algoritmo de ordenação:\n");
    printf("1. Selection Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Merge Sort\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            selection_sort(arr, n);
            break;
        case 2:
            bubble_sort(arr, n);
            break;
        case 3:
            merge_sort(arr, 0, n - 1);
            break;
        default:
            printf("Escolha inválida!\n");
            return 1;
    }

    // Mostrar os números ordenados
    printf("Números ordenados: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
