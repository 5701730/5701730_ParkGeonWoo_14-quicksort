#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 

int comparisonCount = 0; // 비교 횟수
int moveCount = 0;       // 이동 횟수
int totalComparisons = 0;
int totalMoveCount = 0;  // 총 이동 횟수
int isFirst = 0;         // 첫 번째 출력d의 여부 확인


void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000; // 0~999 범위의 난수 생성
    }
}

// 배열 출력 함수 (40~60번째 값 출력)
void printIntermediate(int arr[]) {
    for (int i = 40; i < 60; i++) { // 40~59 인덱스 값 출력
        printf("%3d ", arr[i]);
    }
    printf("\n");
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", arr[i]);
        if ((i + 1) % 10 == 0); // 10개씩 출력
    }
    printf("\n");
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 피벗 배열의 마지막 값으로 설정
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisonCount++; // 비교 연산 
        if (arr[j] <= pivot) {
            i++;
            //스왑을 함
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            moveCount += 3; // 스왑 시 이동 3회증가
        }
    }
    // 피벗 자리 이동
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    moveCount += 3; 

    // 첫 번째 실행에서만 출력나오도록
    if (isFirst == 0 && low <= 60 && high >= 40) {
        printIntermediate(arr); // 40~60 인덱스 값 출력
    }

    return i + 1; // 다른 피벗인덱스로
}

//보너스 문제
void itrQuickSort(int arr[], int low, int high) {
    int stack[SIZE]; // 스택 배열
    int top = -1;

    
    stack[++top] = low;
    stack[++top] = high;

    // 스택이 빌 때까지 반복
    while (top >= 0) {
        high = stack[top--]; // 상위 값 팝
        low = stack[top--];  // 하위 값 팝

        int pi = partition(arr, low, high); // 파티션 수행

        
        if (low <= 40 && high >= 60 && isFirst == 0) {
            printIntermediate(arr); // 중간결괄르 출력함
        }

        // 피벗 기준 오른쪽 범위 푸시함
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }

        // 피벗 기준 왼쪽 범위 푸시함
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
    }

    // 정렬 완료 상태 출력 (첫 번째 실행에서만)
    if (isFirst == 0) {
        
        printIntermediate(arr); // 최종 정렬 상태 출력
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) { 
        generateRandomArray(array); 
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) { 
            printf("Quick Sort Run\n");
            
            itrQuickSort(array, 0, SIZE - 1);
            printf("Result\n");
            printArray(array, SIZE); 
            isFirst++;
        }
        else {
            itrQuickSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}

