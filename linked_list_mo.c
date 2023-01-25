#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {		// 구조체 ArrayListType 선언
	int no;				// insert ++;
	int size;		    // create 연결해서 동적 메모리 할당
	int *array;			// create 함수에서 배열을 연결하기 위해 포인터 씀
}ArrayListType;

void error(const char* message) {						//에러 날 시 함수 호출
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void create(ArrayListType* L){							// 배열의 크기 입력하여 동적 메모리 할당, 배열 메모리 크기 정의하늖 ㅏㅁ수
	printf("배열의 크기를 입력하세요 : "); scanf("%d", &L->size);
	L -> array = (int *)malloc(L->size * sizeof(int));
}

element get_entry(ArrayListType* L, int pos) {			//pos를 받아서 위치가 오류 날 때 쓰는 함수
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];								// [pos]
}

void init(ArrayListType* L) {							// ArrayListType 초기화하는 함수
	L->no = 0;
}

void insert (ArrayListType *L, int pos, element item) {		// ArrayListType 구조체의 주소를 받고, 값과 데이터를 넣을 위치를 받는 함수
	if (!is_full(L) && (pos >= 0) && (pos <= L->no)) {		// 조건 : 데이터 메모리가 가득 안 차고, 위치(pos)가 0 이상, 위치가 개수(no)보다 작거나 같아야함
		for (int i = (L->no - 1); i >= pos; i--)			// 끝에서부터 데이터를 순차적으로 넣음
			L->array[i + 1] = L->array[i];					// 배열 구조를 생각하면, 왼쪽 값을 오른쪽으로 순차적으로 넣기
		L->array[pos] = item;								// 배열의 원하는 위치에 값(item)을 넣음
		L->no++;											// 데이터값 1개가 늘어났으니, no(개수)도 + 1
	}
}

void insert_last(ArrayListType *L, element item) {		// 배열의 마지막 부분에 값 넣는 함수
	if (L->no >= L->size) {							    // 구조체 리스트의 데이터 한계점일 때
		error("리스트 오버플로우\n");					// 데이터 입력 에러
	}
	L->array[L->no++] = item;							// 배열의 요소 위치는 개수(no)의 값을 넣은 뒤, +1을 추가
}

int is_empty(ArrayListType* L) {		//배열이 비어있을 시에 출력하는 함수
	return L->no == 0;					// 배열의 개수가 0
}

int is_full(ArrayListType* L) {			// 배열에 데이터가 가득 차 있을 때 사용하는 함수
	return L->no == L->size;			// 배열의 개수가 크기를 입력한 만큼 차 있음
}

element delete(ArrayListType *L, int pos) { // pos 위치의 데이터값 삭제하는 함수
	element item;

	if (pos < 0 || pos >= L->no) {				//위치 pos가 음수거나 pos가 개수 no보다 크거나 같을 때 오류 출력
		error("위치 오류");
	}
	item = L->array[pos];						// item에는 원하는 배열의 위치로 선언
	for (int i = pos; i < (L->no - 1); i++)		// i = 0부터 ; (no(4) -1)까지 ; i++ , i = 0 1 2 // 3번 반복
		L->array[i] = L->array[i + 1];			// (i + 1)의 값을 i 에 넣음으로써 데이터 값 삭제 
	L->no--;									// 1개를 삭제했으니깐 개수 no--
	return item; // 
}

void print_list(ArrayListType* L) {		// ArrayListType의 배열에 넣은 값을 출력하는 함수
	int i;
	for (i = 0; i < L->no; i++)			// i=0부터 ; no(개수)까지 ; i + 1
		printf("%d->", L->array[i]);	// 배열의 값을 [0]부터 출력
	printf("\n");						// for 반복문 끝나고 나서 줄바꾸기 출력
}

int main(void) { // 10을 넣는 리스트 -> 20을 넣는 리스트 -> 30을 넣는 리스트 -> 맨 끝에 40을 넣고 -> 0번째(첫번째) 항목 삭제
	ArrayListType list;							// 구조체 ArrayListTYpe list 정의
	create(&list);							   // 배열의 크기를 구하는 함수 호출
	init(&list); // 구조체 list 초기화 함수
	insert(&list, 0, 10); print_list(&list);   // 10 ->
	insert(&list, 0, 20); print_list(&list);   // 20 -> 10 ->
	insert(&list, 0, 30); print_list(&list);   // 30 -> 20 -> 10 ->
	insert_last(&list, 40); print_list(&list); // 30 -> 20 -> 10 -> 40 ->
	delete(&list, 0); print_list(&list);	   // 20 -> 10 -> 40 ->
	return 0;
}