# ft_containers
STL중 stack, vector, map, set container 구현


### Iterator의 종류 
---
1. 입력 반복자(input iterator)

2. 출력 반복자(output iterator)

3. 순방향 반복자(forward iterator)

4. 양방향 반복자(bidirectional iterator)

5. 임의 접근 반복자(random access iterator)

이렇게 다양한 반복자를 사용하는 이유는 알고리즘의 적용 조건을 제한하기 위해서다.

즉, 양방향 반복자는 임의 접근 반복자에 기초하는 알고리즘은 사용할 수 없지만, 자신보다 하위 계층의 반복자에 기초하는 알고리즘은 사용할 수 있다.

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

### type_traits 
---
템플릿 메타 함수 : 사실 함수는 아니지만 마치 함수 처럼 동작하는 탬플릿 클래스다. 이들이 메타 함수인 이유는 보통의 함수들은 값 에 대해 연산을 수행하지만, 메타 함수는 타입 에 대해 연산을 수행한다.

### 데이터 멤버를 가리키는 포인터 (Pointer to Data member) 
---
int T::* = 이는 T 의 int 멤버를 가리키는 포인터 라는 의미 (C++ 에서 데이터 멤버를 가리키는 포인터가 허용되는 것은 클래스와 공용체(union) 딱 두 가지)
```
#include <iostream>
#include <type_traits>

class A {
 public:
  int n;

  A(int n) : n(n) {}
};

int main() {
  int A::*p_n = &A::n;

  A a(4);
  std::cout << "a.n : " << a.n << std::endl;
  std::cout << "a.*p_n : " << a.*p_n << std::endl;
}
```
결과는 각각 동일하게 4를 출력한다. 위 p_n 은 A 의 int 멤버를 가리킬 수 있는 포인터를 의미합니다. 이 때 p_n 이 실제 존재하는 어떠한 객체의 int 멤버를 가리키는 것이 아니다.

### SFINAE (Substitution failure is not an error)
---
템플릿 함수를 사용 할 때, 컴파일러는 템플릿 인자의 타입들을 유추한 다음에, 템플릿 인자들을 해당 타입으로 치환하게 된다. 치환 오류는 컴파일 오류가 아니다 줄여서 SFINAE 라는 원칙 때문에, 템플릿 인자 치환 후에 만들어진 식이 문법적으로 맞지 않는다면, 컴파일 오류를 발생 시키는 대신 단순히 함수의 오버로딩 후보군에서 제외만 시키게 된다.

한 가지 중요한 점은, 컴파일러가 템플릿 인자 치환 시에 함수 내용 전체가 문법적으로 올바른지 확인하는 것이 아니다. 컴파일러는 단순히 함수의 인자들과 리턴 타입만이 문법적으로 올바른지를 확인한다. 따라서, 함수 내부에서 문법적으로 올바르지 않은 내용이 있더라도 오버로딩 후보군에 남아 있게 된다.

SFINAE 를 활용하게 된다면 원하지 않는 타입들에 대해서 오버로딩 후보군에서 제외할 수 있다. 

c++ 표준 문구
> 만일 템플릿 인자 치환이 올바르지 않는 타입이나 구문을 생성한다면 타입 유추는 실패합니다. 올바르지 않는 타입이나 구문이라 하면, 치환된 인자로 썼을 때 문법상 틀린 것을 의미 합니다. 이 때, 함수의 즉각적인 맥락(immediate context)의 타입이나 구문만이 고려되고, 여기에서 발생한 오류 만이 타입 유추를 실패시킬 수 있습니다. 그 이후에, 올바르지 않다고 여겨지는 여러가지 상황들을 확인하면서 (예컨대 클래스가 아닌 타입이나, void 의 레퍼런스를 생성한다든지 등등) 이를 오버로딩 후보 목록에서 제외시킵니다.

### enabel_if
---
enable_if 는 SFINAE 를 통해서 조건에 맞지 않는 함수들을 오버로딩 후보군에서 쉽게 뺄 수 있게 도와주는 간단한 템플릿 메타 함수이다.

Vector 생성 시 enable_if의 활용
```
template <typename T>
class vector {
 public:
  // element 가 num 개 들어있는 vector 를 만든다.
  vector(size_t num, const T& element);

  // 반복자 start 부터 end 까지로 벡터 생성
  template <typename Iterator>
  vector(Iterator start, Iterator end);
};
```
vector<int> v(10, 3); 이코드를 실행하면 반복자를 이용한 생성자가 호출된다. num 의 타입이 size_t이기 때문에 이와같은 일이 발생한다. size_t 는 부호가 없는 정수 타입이다. 문제는 v(10, 3) 을 했을 때 10 은 부호가 있는 정수이다. C++ 컴파일러는 이정도는 알아서 캐스팅 해줄 수 있지만, Iterator 를 int 로 오버로딩 한다면 v(10, 3) 를 완벽하게 매칭 시킬 수 있다. 따라서 결과적으로 우리의 예상과는 다르게 반복자를 이용한 생성자 호출이 선택된다. 이를 막기 위해 enabel_if를 사용하여 아래와 같은 생성자를 작성했다.  

```
vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
```

### void_t
---

