# 16-interpolationSearch
# result 1 image
![interpolation search {result 1 image}](https://github.com/user-attachments/assets/41dfb641-4cad-4aab-a588-c742e534b59c)
# result 2 image
![interpolation search {result 2 image}](https://github.com/user-attachments/assets/9e30b242-c4b0-4898-b61f-b02b5da99d06)
# result 3 image
![interpolation search {result 3 image}](https://github.com/user-attachments/assets/206c6448-5387-4411-b139-b7875c0ba3bb)

# 평균 비교 횟수
1. Binary Search는 정렬된 배열에서 값을 찾을 때마다 범위를 절반으로 나누며, 최악의 경우에는 O(log n)번의 비교가 필요합니다. 1000번의 Binary Search를 수행한 평균 비교 횟수는 약 9~10번 정도입니다.

2. Interpolation Search는 Binary Search와 유사하지만, 키의 위치를 추정하는 과정에서 배열의 값 분포를 활용합니다. 배열이 균일하게 분포된 경우, 이 방식은 훨씬 더 효율적일 수 있습니다. 1000번의 Interpolation Search를 수행한 평균 비교 횟수는 Binary Search보다 적게 나오며, 약 4~6번 정도입니다.

# Interpolation Search가 Binary Search보다 적게 비교하는 이유를 설명
1. Binary Search는 비교 횟수와 시간 복잡도가 매우 효율적이지만, 데이터가 고르게 분포되어 있지 않으면 최악의 경우에도 좋은 성능을 보장하지 못합니다.
   
3. Interpolation Search는 배열이 균등하게 분포된 경우 비교 횟수를 대폭 줄일 수 있어 더 효율적일 수 있습니다. 그러나 배열이 매우 비균등한 분포를 가질 경우에는 성능이 떨어질 수 있습니다
