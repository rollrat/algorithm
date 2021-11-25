# algorithm

알고리즘 정리

## Edit Distance로 LCS 구하기

 * 이 방법은 검증되지 않은 방법이다.
 
 입력 문자열 A, B 두 개가 있다.
 이 문자열 A, B에 대한 rapidfuzz의 ratio함수의 반환값을 r로 하자.
 r값을 edit distance 형태로 바꾸려면 (100 - r) / 100 * (len(A) + len(B))를 통해 바꾸면 되며, 이 값을 score라고 하자
 `len(B) >= len(A)`라면, lcs의 값은 (len(A) + len(B) - score) / 2가 lcs값이 된다.
 
## 트리 알고리즘 구현
 
### RB Tree
 
### BTree
 
### Inverse Tree
 
### Tree 최적화
 
## 그래프 알고리즘 구현
