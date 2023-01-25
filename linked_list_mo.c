#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {		// ����ü ArrayListType ����
	int no;				// insert ++;
	int size;		    // create �����ؼ� ���� �޸� �Ҵ�
	int *array;			// create �Լ����� �迭�� �����ϱ� ���� ������ ��
}ArrayListType;

void error(const char* message) {						//���� �� �� �Լ� ȣ��
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void create(ArrayListType* L){							// �迭�� ũ�� �Է��Ͽ� ���� �޸� �Ҵ�, �迭 �޸� ũ�� �����ψe ������
	printf("�迭�� ũ�⸦ �Է��ϼ��� : "); scanf("%d", &L->size);
	L -> array = (int *)malloc(L->size * sizeof(int));
}

element get_entry(ArrayListType* L, int pos) {			//pos�� �޾Ƽ� ��ġ�� ���� �� �� ���� �Լ�
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];								// [pos]
}

void init(ArrayListType* L) {							// ArrayListType �ʱ�ȭ�ϴ� �Լ�
	L->no = 0;
}

void insert (ArrayListType *L, int pos, element item) {		// ArrayListType ����ü�� �ּҸ� �ް�, ���� �����͸� ���� ��ġ�� �޴� �Լ�
	if (!is_full(L) && (pos >= 0) && (pos <= L->no)) {		// ���� : ������ �޸𸮰� ���� �� ����, ��ġ(pos)�� 0 �̻�, ��ġ�� ����(no)���� �۰ų� ���ƾ���
		for (int i = (L->no - 1); i >= pos; i--)			// ���������� �����͸� ���������� ����
			L->array[i + 1] = L->array[i];					// �迭 ������ �����ϸ�, ���� ���� ���������� ���������� �ֱ�
		L->array[pos] = item;								// �迭�� ���ϴ� ��ġ�� ��(item)�� ����
		L->no++;											// �����Ͱ� 1���� �þ����, no(����)�� + 1
	}
}

void insert_last(ArrayListType *L, element item) {		// �迭�� ������ �κп� �� �ִ� �Լ�
	if (L->no >= L->size) {							    // ����ü ����Ʈ�� ������ �Ѱ����� ��
		error("����Ʈ �����÷ο�\n");					// ������ �Է� ����
	}
	L->array[L->no++] = item;							// �迭�� ��� ��ġ�� ����(no)�� ���� ���� ��, +1�� �߰�
}

int is_empty(ArrayListType* L) {		//�迭�� ������� �ÿ� ����ϴ� �Լ�
	return L->no == 0;					// �迭�� ������ 0
}

int is_full(ArrayListType* L) {			// �迭�� �����Ͱ� ���� �� ���� �� ����ϴ� �Լ�
	return L->no == L->size;			// �迭�� ������ ũ�⸦ �Է��� ��ŭ �� ����
}

element delete(ArrayListType *L, int pos) { // pos ��ġ�� �����Ͱ� �����ϴ� �Լ�
	element item;

	if (pos < 0 || pos >= L->no) {				//��ġ pos�� �����ų� pos�� ���� no���� ũ�ų� ���� �� ���� ���
		error("��ġ ����");
	}
	item = L->array[pos];						// item���� ���ϴ� �迭�� ��ġ�� ����
	for (int i = pos; i < (L->no - 1); i++)		// i = 0���� ; (no(4) -1)���� ; i++ , i = 0 1 2 // 3�� �ݺ�
		L->array[i] = L->array[i + 1];			// (i + 1)�� ���� i �� �������ν� ������ �� ���� 
	L->no--;									// 1���� ���������ϱ� ���� no--
	return item; // 
}

void print_list(ArrayListType* L) {		// ArrayListType�� �迭�� ���� ���� ����ϴ� �Լ�
	int i;
	for (i = 0; i < L->no; i++)			// i=0���� ; no(����)���� ; i + 1
		printf("%d->", L->array[i]);	// �迭�� ���� [0]���� ���
	printf("\n");						// for �ݺ��� ������ ���� �ٹٲٱ� ���
}

int main(void) { // 10�� �ִ� ����Ʈ -> 20�� �ִ� ����Ʈ -> 30�� �ִ� ����Ʈ -> �� ���� 40�� �ְ� -> 0��°(ù��°) �׸� ����
	ArrayListType list;							// ����ü ArrayListTYpe list ����
	create(&list);							   // �迭�� ũ�⸦ ���ϴ� �Լ� ȣ��
	init(&list); // ����ü list �ʱ�ȭ �Լ�
	insert(&list, 0, 10); print_list(&list);   // 10 ->
	insert(&list, 0, 20); print_list(&list);   // 20 -> 10 ->
	insert(&list, 0, 30); print_list(&list);   // 30 -> 20 -> 10 ->
	insert_last(&list, 40); print_list(&list); // 30 -> 20 -> 10 -> 40 ->
	delete(&list, 0); print_list(&list);	   // 20 -> 10 -> 40 ->
	return 0;
}