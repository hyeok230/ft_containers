# ft_containers
---
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

### 템플릿 메타 프로그래밍 (TMP)
---
Type(int, float,,,)은 어떠한 객체에 무엇을 저장하느냐를 지정하는데 사용해 왔지, 타입 자체가 어떠한 값을 가지지는 않았다. 하지만, 템플릿을 사용하면 객체를 생성하지 않더라도, 타입에 어떠한 값 을 부여할 수 있고, 또 그타입들을 가지고 연산 을 할 수 있다.

또한 타입은 반드시 컴파일 타임에 확정되어야 하므로, 컴파일 타임에 모든 연산이 끝난다. 이렇게 타입을 가지고 컴파일 타임에 생성되는 코드로 프로그래밍을 하는 것을 메타 프로그래밍(meta programming) 이라고 한다.

### allocator
---
표준 라이브러리의 컨테이너는 메모리 관리를 위해 사용자가 직접 allocator를 지정하지 않으면 std::allocator<T>를 기본 값으로 사용한다.
일반적으로 동적 메모리 관리는 new와 delete 사용하는 것이 편하고 효율적이지만 컨테이너를 직접 구현하여 사용하는 경우 std::allocator<T>를 사용하면 표준 라이브러리와 유사한 인터페이스를 구현하기 용이하다.

std::allocator<T> 구성과 사용 방법은 간단하다. 객체를 정의하고 원하는 크기로 allocate 한 후 사용한다. 요소가 기본자료형이 아닌 경우 std::destroy를 이용하여 각 요소의 소멸자를 호출한다. 그리고 마지막으로 deallocate를 하면 된다. (allocate -> destroy -> deallocate)

- allocate함수는 초기화되지 않은 메모리 공간을 할당하여 그 시작 주소를 반환하는 함수
- construct 함수는 지정된 값으로 초기화된 객체를 지정된 주소에 생성하는 함수
- destroy 함수는 객체를 소멸
- deallocate 함수는 메모리 공간을 해제하는 함수
