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

### traits_class
---
특성정보(traits) 클래스는 컴파일 도중에 어떤 주어진 타입의 정보를 얻을 수 있게 하는 객체를 지칭하는 개념이다.

특성정보는 C++에 미리 정의된 문법구조도, 키워드도 아니다.
그냥 C++ 프로그래머들이 관용적으로 사용하는 구현 기법이다.

특성정보는 관례적으로 아래와 같은 항목들을 충족해야 한다.

1) 일반적으로 특성정보는 구조체로 구현하나, 이를 특성정보(traits) 클래스라 부른다.

2) 특성정보는 기본제공 타입에 대해서 쓸 수 있어야 한다.

즉, advance 함수는 포인터(IterT)와 int(DistT)를 받아서 호출될 때도 제대로 동작할 수 있어야 한다.
이를 위해, 표준적인 특성정보를 기본 템플릿과 여러 기본 타입에 대한 부분 특수화 버전의 템플릿을 요구한다.


### allocator
---
표준 라이브러리의 컨테이너는 메모리 관리를 위해 사용자가 직접 allocator를 지정하지 않으면 std::allocator<T>를 기본 값으로 사용한다.
일반적으로 동적 메모리 관리는 new와 delete 사용하는 것이 편하고 효율적이지만 컨테이너를 직접 구현하여 사용하는 경우 std::allocator<T>를 사용하면 표준 라이브러리와 유사한 인터페이스를 구현하기 용이하다.

std::allocator<T> 구성과 사용 방법은 간단하다. 객체를 정의하고 원하는 크기로 allocate 한 후 사용한다. 요소가 기본자료형이 아닌 경우 std::destroy를 이용하여 각 요소의 소멸자를 호출한다. 그리고 마지막으로 deallocate를 하면 된다. (allocate -> construct -> destroy -> deallocate)

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

### Map
---
map은 STL 내부에서는 Red-Black 트리로 구현되어 있어 탐색과 삽입/삭제 모두 O(logN)의 시간복잡도를 보장하고 있다.
map 내부에서 정렬은 템플릿 인자로 들어오는 Compare 객체에 의해 일어나게 된다.
Compare 객체는 맵 자체의 초기화와 함께 초기화되는데, 기본적으로 less로 초기화된다.

#### map의 속성
Associative -> 맵에 들어있는 원소는 container에 저장된 원소의 절대적 메모리 주소가 아닌 key에 의해 참조됨.

Ordered -> 맵 내부의 원소는 항상 Compare 함수가 지정한 규칙에 의해 key에 따라 정렬되어있음. 삽입이나 삭제가 일어나더라도 이 순서는 유지되어야 함.

Map -> 각 value는 반드시 key에 map 되어있음. 

unique key -> key는 반드시 컨테이너 내부에서 유일한 값이어야 함.

Allocator-aware -> 내부의 저장공간의 동적 할당과 반환을 위해 Allocator를 사용함.

### Red-Black Tree 속성
---
1. 모든 노드는 Red 혹은 Black
2. 루트 노드는 Black

nil 노드란?
- 존재하지 않음을 의미하는 노드
- 자녀가 없을 때 자녀를 nil 노드로 표기
- 값이 있는 노드와 동등하게 취급
- RB 트리에서 leaf 노드는 nil 노드

3. 모든 nil 노드는 Black
4. Red의 자녀들은 Black or Red가 연속적으로 존재할 수 없다.
5. 임의의 노드에서 자손 nil 노드들까지 가는 경로들의 black 수는 같다. (자기 자신은 카운트에서 제외)

#### 노드 x의 Black height 
노드 x에서 임의의 자손 nil노드까지 내려가는 경로에서의 black 수 (자기 자신은 카운트에서 제외)
5번 속성을 만족해야 성립하는 개념

RB 트리가 5번 속성을 만족하고 있고 두 자녀가 같은 색을 가질 때 부모와 두 자녀의 색을 바꿔줘도 5번 속성은 여전히 만족한다. 

- RB트리는 어떻게 균형을 잡는가?
삽입/삭제 시 주로 4번, 5번을 위반하며 이들을 해결하려고 구조를 바꾸다 보면 자연스럽게 트리의 균형이 잡히게 된다.

### Red-Black Tree 삽입 overview
--- 
- 삽입 방법
0. 삽입 전 RB트리의 속성 만족한 상태
1. 삽입 방식은 일반적인 BST와 동일
2. 삽입 후 RB트리 위반 여부 확인
3. RB트리 속성을 위반했다면 재조정
4. RB트리 속성을 다시 만족

삽입하는 노드는 항상 red이다.

red 삽입 후 2번 속성을 위반 했을 때 -> 루트 노드를 Black으로 바꿔준다.

- 왜 새로 삽입하는 노드는 Red인가?
삽입 후에도 5번 속성을 만족하기 위해서이다.

- case 1.
삽입된 Red 노드의 부모도 Red & 삼촌(=부모의 형제)도 Red라면 => 부모와 삼촌을 black으로 바꾸고 할아버지를 Red로 바꾼뒤 할아버지에서 다시 확인을 시작한다.

- case 2.
삽입된 Red 노드가 부모의 오른쪽* 자녀 & 부모도 Red고 할아버지의 왼쪽* 자녀 & 삼촌(=부모의 형제)은 black이라면 => 부모를 기준으로 왼쪽*으로 회전한 뒤 case3 방식으로 해결
(오른쪽과 왼쪽을 모두 바꾸면 동일하게 성립한다.)
- case 3. 
삽입된 Red 노드가 부모의 왼쪽* 자녀 & 부모도 Red고 할아버지의 왼쪽* 자녀 & 삼촌(=부모의 형제)은 black이라면 => 부모와 할아버지의 색을 바꾼 후 할아버지 기준으로 오른쪽*으로 회전한다.
(오른쪽과 왼쪽을 모두 바꾸면 동일하게 성립한다.)

### Red-Black Tree 삭제 overview
--- 
0. 삭제 전 RB 트리 속성 만족한 상태
1. 삭제 방식은 일반적인 BST와 동일
2. 삭제 후 RB 트리 속성 위반 여부 확인
3. RB 트리 속성을 위반했다면 재조정
4. RB 트리 속성을 다시 만족

- 속성 위반 여부 확인
RB트리에서 노드를 삭제할 때 어떤 색이 삭제되는지가 속성 위반 여부를 확인할 때 매우 중요

삭제하려는 노드의 자녀가 없거나 하나라면 삭제되는 색 = 삭제되는 노드의 색 (여기에서 nil은 자녀가 아님)
삭제하려는 노드의 자녀가 둘이라면 삭제되는 색 = 삭제되는 노드의 successor의 색

* 삭제되는 색이 Red라면 어떠한 속성도 위반하지 않는다.
* 삭제되는 색이 Black이라면 2번, 4번, 5번 속성을 위반할 수 있다.

- 2번 위반 해결하기
: 루트노드를 Black으로 바꾸면 된다.

- 5번 위반 해결하기
: 5번 속성을 다시 만족시키기 위해 삭제된 색의 위치를 대체한 노드에 extra black을 부여한다.
extra black은 black 수를 카운트 할 때 하나의 black으로 카운트 된다.
doubly black : extra black이 부여된 black 노드 (blakc 두개로 카운트)
red-and-black : extra black이 부여된 red 노드 (black 하나로 카운트)

extra black 부여 후 red-and-black 해결하기
: red-and-black을 black으로 바꾸면 해결

extra black 부여 후 doubly black 해결하기
: 총 4가지의 case로 분류된다. 네 가지 case로 분류할 때의 기준은 doubly black의 형제의 색과 그 형제의 자녀들의 색이다.

1. doubly black의 형제가 red 일때
: doubly black의 형제를 black으로 만든 후 case 2, 3, 4 중에 하나로 해결
(부모와 형제의 색을 바꾸고 부모를 기준으로 왼쪽으로 회전한 뒤 doubly black을 기준으로 case 2, 3, 4중에 하나로 해결)

2. doubly black의 형제가 black & 그 형제의 두 자녀 모두 black일 때
: doubly black과 그 형제의 black을 모아서 부모에게 전달해서 부모가 extra black을 해결하도록 위임한다.

3. doubly black의 오른쪽 형제가 black & 그 형제의 왼쪽 자녀가 red & 그 형제의 오른쪽 자녀는 black일 때
: doubly black의 형제의 오른쪽 자녀가 red가 되게 만들어서 이후엔 case.4를 적용하여 해결

4. doubly black의 오른쪽 형제가 black & 그 형제의 오른쪽 자녀가 red일 때
: 형제의 오른쪽 자녀의 red를 doubly black 위로 옮기고 옮긴 red로 extra black을 전달해서 red-and-black으로 만들면 red-and-black을 black으로 바꿔서 해결
(오른쪽 형제는 부모의 색으로, 오른쪽 형제의 오른쪽 자녀와 부모를 black으로 바꾼 후에 부모를 기준으로 왼쪽으로 회전하면 해결) * 오른쪽을 왼쪽으로 바꿔도 성립

### RB 트리의 시간복잡도
---
||avg|worst|
|---|---|---|
|insert| O(logN) | O(logN) |
|delete| O(logN) | O(logN) |
|search| O(logN) | O(logN) |

BST의 경우 worst일 때 O(N)

### AVL Tree VS RB Tree
||Red-Black 트리|AVL 트리|
|:---:|:---:|:---:|
|bst| yes | yes |
|삽입/삭제/검색 시간복잡도| worst = O(logN) | worst = O(logN) |
|삽입/삭제 성능| AVL 트리에 비해 빠르다 | Red-Black 트리에 비해 느리다 (규칙 엄격) |
|검색 성능| AVL 트리에 비해 느리다 | Red-Black 트리에 비해 빠르다 |
|균형 잡는 방식| red-black 트리 속성 만족 | balance factor {-1, 0 ,1} 되도록 |
|응용 사례| linux kernel 내부, Java TreeMap, c++ std::map | dictionary, 한번 만들어 놓으면 삽입/삭제가 거의 없이 검색이 대부분인 상황에 사용 |


### reference
---
https://cplusplus.com/reference/vector/vector/
https://www.youtube.com/watch?v=2MdsebfJOyM&t=1s
https://foufou.tistory.com/entry/ftcontainers-5-Red-Black-Tree-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0