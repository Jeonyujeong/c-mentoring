# 포인터 
## 학습자료

https://docs.google.com/presentation/d/1wLIndEzqGKrotLZsU1l3zOEw9LEbhVyLp4zOwDXVnDY/edit?usp=sharing

## 문제 1
```
아래의 예제 실행 시 변수와 포인터 변수의 관계를 그림으로 그려서 설명해보자. 
또한 출력의 결과도 예상해보자.

int main(void) 
{
	int num = 10;
	int * ptr1 = &num;
	int * ptr2 = ptr1;

	(*ptr1)++;
	(*ptr2)++;
	printf(“%d \n”, num);
	return 0;
}
```

## 문제 2
```
int형 변수 num1과 num2를 선언과 동시에 각각 10과 20으로 초기화하고, int형 포인터 변수 ptr1과 ptr2를 선언하여 각각 num1과 num2를 가리키게 하자. 

그리고 이 상태에서 포인터 변수 ptr1과 ptr2를 이용해서 num1의 값을 10 증가시키고, num2의 값을 10 감소시키자.

이제 두 포인터 변수 ptr1과 ptr2가 가리키는 대상을 서로 바꾸자. 

즉, 포인터 변수 ptr1이 num2를 가리키게 하고, 포인터 변수 ptr2가 num1을 가리키게 하자. 

그리고 마지막으로 ptr1과 ptr2가 가리키는 변수에 저장된 값을 출력하자.
```
