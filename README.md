# ft_containers
42 Seoul 5 circle subject

### Iterator의 종류 
---
1. 입력 반복자(input iterator)

2. 출력 반복자(output iterator)

3. 순방향 반복자(forward iterator)

4. 양방향 반복자(bidirectional iterator)

5. 임의 접근 반복자(random access iterator)

이렇게 다양한 반복자를 사용하는 이유는 알고리즘의 적용 조건을 제한하기 위해서입니다.

즉, 양방향 반복자는 임의 접근 반복자에 기초하는 알고리즘은 사용할 수 없지만, 자신보다 하위 계층의 반복자에 기초하는 알고리즘은 사용할 수 있습니다.