# algorithm

알고리즘 정리

## Edit Distance로 LCS 구하기

 * 이 방법은 검증되지 않은 방법이다.
 
 입력 문자열 A, B 두 개가 있다.
 이 문자열 A, B에 대한 rapidfuzz의 ratio함수의 반환값을 r로 하자.
 r값을 edit distance 형태로 바꾸려면 (100 - r) / 100 * (len(A) + len(B))를 통해 바꾸면 되며, 이 값을 score라고 하자
 `len(B) >= len(A)`라면, lcs의 값은 (len(A) + len(B) - score) / 2가 lcs값이 된다.
 
---
 
## 흥미로웠던 알고리즘들
 
### Meet In The Middle

 - https://technicolour.tistory.com/8
 - 무게가 각기 다른 N개의 물건을 최대 C의 무게를 담을 수 있는 가방에 넣는다고 할 때 넣을 수 있는 경우의 수는?
 - 반으로 나누어서 각각 계산하고, 부족한 부분들 채우기
