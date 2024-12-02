#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp)) 

int compareCount = 0; // �� Ƚ���� �����ϴ� ����

// �迭�� ó�� 20���� ������ 20���� ���Ҹ� ����ϴ� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    // �迭�� ó�� 20�� ���� ���
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    // �迭�� ������ 20�� ���� ���
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// SIZE��ŭ�� ������ ���� ���� �迭�� �����ϴ� �Լ�
void generateRandomArray(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 10000; // 0~9999 ������ ���� �� ����
    }
}

// QuickSort���� ������ ����ϴ� �Լ�
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left; // ���� ������ ����
    high = right + 1; // ������ ������ ����
    pivot = list[left]; // �ǹ��� ù ��° ���ҷ� ����
    do {
        do {
            low++; // low�� �ǹ����� ū ���� ���� ������ ����
        } while (low <= right && list[low] < pivot);
        do {
            high--; // high�� �ǹ����� ���� ���� ���� ������ ����
        } while (high >= left && list[high] > pivot);
        if (low < high) {
            SWAP(list[low], list[high], temp); // ���� ��ȯ
        }
    } while (low < high); // low�� high�� �������� ������ �ݺ�

    SWAP(list[left], list[high], temp); // �ǹ��� high ���� ��ȯ
    return high; // ���ο� �ǹ��� �ε����� ��ȯ
}

// QuickSort�� �����ϴ� �Լ�
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // ����
        QuickSort(list, left, q - 1); // ���� �κ� ��� ����
        QuickSort(list, q + 1, right); // ������ �κ� ��� ����
    }
}

// QuickSort�� �� Ƚ���� �����ϴ� �Լ�
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // �� Ƚ�� �ʱ�ȭ
    QuickSort(array, 0, SIZE - 1); // QuickSort ����
}

// ���� Ž���� �����ϴ� �Լ�
int search_binary2(int array[], int key, int low, int high) {
    int middle;
    while (low <= high) {
        middle = (low + high) / 2; // �߰� �ε��� ���
        compareCount++; // �� Ƚ�� ����
        if (key == array[middle]) {
            return middle; // Ű�� ã���� �ε��� ��ȯ
            compareCount++; // (�� �ڵ�� ������� ����, �ʿ� ����)
        }
        else if (key > array[middle]) low = middle + 1; // Ű�� �߰������� ũ�� ������ ���� Ž��
        else high = middle - 1; // Ű�� �߰������� ������ ���� ���� Ž��
    }
    return -1; // Ű�� ������ -1 ��ȯ
}

// ���� Ž���� ��� �� Ƚ���� ���ϴ� �Լ�
double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompareCount = 0; // �� �� Ƚ���� ������ ����
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; // ������ ��ǥ �� ����
        compareCount = 0; // �� Ƚ�� �ʱ�ȭ
        search_binary2(array, target, 0, SIZE - 1); // ���� Ž�� ����
        totalCompareCount += compareCount; // �� Ƚ�� �ջ�
    }
    return (double)totalCompareCount / 1000; // ��� �� Ƚ�� ��ȯ
}

// ���� Ž���� ��� �� Ƚ���� ���ϴ� �Լ�
double getAverageInterpolationSearchCompareCount(int array[]) {
    int totalCompareCount = 0; // �� �� Ƚ���� ������ ����
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; // ������ ��ǥ �� ����
        compareCount = 0; // �� Ƚ�� �ʱ�ȭ
        interpol_search(array, target, SIZE); // ���� Ž�� ����
        totalCompareCount += compareCount; // �� Ƚ�� �ջ�
    }
    return (double)totalCompareCount / 1000; // ��� �� Ƚ�� ��ȯ
}

// ���� Ž���� �����ϴ� �Լ�
int interpol_search(int array[], int key, int n) {
    int low, high, j;

    low = 0; // ���� �ε���
    high = n - 1; // �� �ε���
    while ((array[high] >= key) && (key > array[low])) { // key�� �迭�� ���� ���� ���� ���� ����
        j = ((float)(key - array[low]) / (array[high] - array[low]) // ���� ������ �̿��� j ���
            * (high - low)) + low;
        compareCount++; // �� Ƚ�� ����
        if (key > array[j]) {
            low = j + 1; // key�� �� ũ�� low�� j+1�� ����
        }
        else if (key < array[j]) {
            high = j - 1; // key�� �� ������ high�� j-1�� ����
        }
        else low = j; // key�� ã���� low�� j�� ����
    }
    compareCount++; // ������ �� Ƚ�� ����
    if (array[low] == key) return(low);  // Ű�� ã���� �ε��� ��ȯ
    else return -1;  // Ű�� ã�� ���ϸ� -1 ��ȯ
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �ʱ�ȭ

    int array[SIZE]; // �迭 ����

    generateRandomArray(array); // ���� �迭 ����

    QuickSort(array, 0, SIZE - 1); // QuickSort�� �迭 ����
    printArray(array); // ���ĵ� �迭 ���

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0; 
}
