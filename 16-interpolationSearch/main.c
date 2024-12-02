#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp)) 

int compareCount = 0; // 비교 횟수를 추적하는 변수

// 배열의 처음 20개와 마지막 20개의 원소를 출력하는 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    // 배열의 처음 20개 원소 출력
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    // 배열의 마지막 20개 원소 출력
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// SIZE만큼의 랜덤한 값을 갖는 배열을 생성하는 함수
void generateRandomArray(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 10000; // 0~9999 사이의 랜덤 값 생성
    }
}

// QuickSort에서 분할을 담당하는 함수
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left; // 왼쪽 끝부터 시작
    high = right + 1; // 오른쪽 끝부터 시작
    pivot = list[left]; // 피벗을 첫 번째 원소로 설정
    do {
        do {
            low++; // low는 피벗보다 큰 값이 나올 때까지 증가
        } while (low <= right && list[low] < pivot);
        do {
            high--; // high는 피벗보다 작은 값이 나올 때까지 감소
        } while (high >= left && list[high] > pivot);
        if (low < high) {
            SWAP(list[low], list[high], temp); // 원소 교환
        }
    } while (low < high); // low와 high가 교차하지 않으면 반복

    SWAP(list[left], list[high], temp); // 피벗과 high 원소 교환
    return high; // 새로운 피벗의 인덱스를 반환
}

// QuickSort를 실행하는 함수
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // 분할
        QuickSort(list, left, q - 1); // 왼쪽 부분 재귀 정렬
        QuickSort(list, q + 1, right); // 오른쪽 부분 재귀 정렬
    }
}

// QuickSort의 비교 횟수를 측정하는 함수
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // 비교 횟수 초기화
    QuickSort(array, 0, SIZE - 1); // QuickSort 실행
}

// 이진 탐색을 실행하는 함수
int search_binary2(int array[], int key, int low, int high) {
    int middle;
    while (low <= high) {
        middle = (low + high) / 2; // 중간 인덱스 계산
        compareCount++; // 비교 횟수 증가
        if (key == array[middle]) {
            return middle; // 키를 찾으면 인덱스 반환
            compareCount++; // (이 코드는 실행되지 않음, 필요 없음)
        }
        else if (key > array[middle]) low = middle + 1; // 키가 중간값보다 크면 오른쪽 절반 탐색
        else high = middle - 1; // 키가 중간값보다 작으면 왼쪽 절반 탐색
    }
    return -1; // 키가 없으면 -1 반환
}

// 이진 탐색의 평균 비교 횟수를 구하는 함수
double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompareCount = 0; // 총 비교 횟수를 저장할 변수
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; // 랜덤한 목표 값 설정
        compareCount = 0; // 비교 횟수 초기화
        search_binary2(array, target, 0, SIZE - 1); // 이진 탐색 실행
        totalCompareCount += compareCount; // 비교 횟수 합산
    }
    return (double)totalCompareCount / 1000; // 평균 비교 횟수 반환
}

// 보간 탐색의 평균 비교 횟수를 구하는 함수
double getAverageInterpolationSearchCompareCount(int array[]) {
    int totalCompareCount = 0; // 총 비교 횟수를 저장할 변수
    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE]; // 랜덤한 목표 값 설정
        compareCount = 0; // 비교 횟수 초기화
        interpol_search(array, target, SIZE); // 보간 탐색 실행
        totalCompareCount += compareCount; // 비교 횟수 합산
    }
    return (double)totalCompareCount / 1000; // 평균 비교 횟수 반환
}

// 보간 탐색을 실행하는 함수
int interpol_search(int array[], int key, int n) {
    int low, high, j;

    low = 0; // 시작 인덱스
    high = n - 1; // 끝 인덱스
    while ((array[high] >= key) && (key > array[low])) { // key가 배열의 범위 내에 있을 때만 실행
        j = ((float)(key - array[low]) / (array[high] - array[low]) // 보간 공식을 이용해 j 계산
            * (high - low)) + low;
        compareCount++; // 비교 횟수 증가
        if (key > array[j]) {
            low = j + 1; // key가 더 크면 low를 j+1로 설정
        }
        else if (key < array[j]) {
            high = j - 1; // key가 더 작으면 high를 j-1로 설정
        }
        else low = j; // key를 찾으면 low를 j로 설정
    }
    compareCount++; // 마지막 비교 횟수 증가
    if (array[low] == key) return(low);  // 키를 찾으면 인덱스 반환
    else return -1;  // 키를 찾지 못하면 -1 반환
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 난수 초기화

    int array[SIZE]; // 배열 선언

    generateRandomArray(array); // 랜덤 배열 생성

    QuickSort(array, 0, SIZE - 1); // QuickSort로 배열 정렬
    printArray(array); // 정렬된 배열 출력

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));

    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0; 
}
