#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  /* Method Declaration */
int** create_matrix(int row, int col); //입력받은 row와 col을 이용해 matrix의 동적 메모리 할당을 한다.
void print_matrix(int** matrix, int row, int col); // 행렬을 출력하는 함수.
int free_matrix(int** matrix, int row, int col); // 행렬의 동적메모리할당을 해제해주는 함수.
int fill_data(int** matrix, int row, int col);  // 행렬의 값을 채워주는 함수.
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬을 서로 더해주는 함수.
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // matrix_a에서 matrix_b를 빼주는 함수.
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 전치함수를 만드는 함수.
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);// 두 배열의 곱을 출력하는 함수.

int main()
{

	char command; // 실행시킬 함수를 입력받을 문자열을 저장할 변수.
	printf("[----- [이연규]  [2018038038] -----]\n");

	int row, col; //행, 열의 정수형 변수.
	srand(time(NULL)); // srand함수안에 time함수를 사용해 항상 다른값을 seed값으로 난수를 얻는다.

	printf("Input row and col : ");
	fflush(stdout);
	scanf("%d %d", &row, &col); // row, col을 입력받는다.
	int** matrix_a = create_matrix(row, col); // create_matrix함수을 통해 matrix_a에 row,col에 맞는 동적 메모리 할당.
	int** matrix_b = create_matrix(row, col); // create_matrix함수을 통해 matrix_b에 row,col에 맞는 동적 메모리 할당.
	int** matrix_a_t = create_matrix(col, row); //create_matrix함수을 통해 matrix_a_t에 row,col에 맞는 동적 메모리 할당.

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { return -1; } //matrix_a 이나 matrix_b 값이 비었으면 -1을 리턴해준다.

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command); //command값을 입력받는다.

		switch (command) {
		case 'z': case 'Z': // command값이 z나 Z일 경우
			printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col); // fill_data를 이용해 matrix_a에 숫자를 채워 넣는다.
			fill_data(matrix_b, row, col); // fill_data를 이용해 matrix_b에 숫자를 채워 넣는다.
			break;
		case 'p': case 'P': // command값이 p나 P일 경우
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // matrix_a를 출력한다.
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // matrix_b를 출력한다.
			break;
		case 'a': case 'A': // command값이 a나 A일 경우
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // matrix_a와 matrix_b를 합한다.
			break;
		case 's': case 'S': // command값이 s나 S일 경우
			printf("Subtract two matrices \n");
			subtraction_matrix(matrix_a, matrix_b, row, col); // matrix_a에 matrix_b를 뺀다.
			break;
		case 't': case 'T': // command값이 t나 T일 경우
			printf("Transpose matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a행렬을 전치해 matrix_a_t 전치행렬로 만든다.
			print_matrix(matrix_a_t, col, row); // 전치행렬 matrix_a_t 를 출력한다.
			break;
		case 'm': case 'M': // command값이 m나 M일 경우
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a행렬을 전치해 matrix_a_t 전치행렬로 만든다.
			multiply_matrix(matrix_a, matrix_a_t, row, col); //matrix_a과 matrix_a_t를 곱한 값을 출력한다.
			break;
		case 'q': case 'Q': // command값이 q나 Q일 경우
			printf("Free all matrices..\n");
			free_matrix(matrix_a_t, col, row); // matrix_a_t의 동적메모리할당을 풀어준다.
			free_matrix(matrix_a, row, col); // matrix_a의 동적메모리할당을 풀어준다.
			free_matrix(matrix_b, row, col); // matrix_b의 동적메모리할당을 풀어준다.
			break;
		default: // 다른 값을 입력할시에 집중하라는 메세지를 출력하고 반복한다.
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');  // q나 Q를 입력받으면 반복문에서 해제된다.
	return 1;
}
int** create_matrix(int row, int col) //입력받은 row와 col을 이용해 matrix의 동적 메모리 할당을 한다.
{
	int i;

	if (row <= 0 || col <= 0) { // row나 col가 음수면 NULL값을 리턴해 오류를 없앤다.
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	int** matrix = (int**)malloc(sizeof(int*) * row); // matrix에 세로 공간을 row만큼 동적 메모리 할당한다.
	for (i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * col); // matrix에 가로 공간을 col만큼 동적 메모리 할당한다.
	}
	if (matrix == NULL) { // 할당된 matrix가 NULL이면 NULL값을 리턴한다.
		printf("matrix is NULL");
		return NULL;
		}
	return matrix; // 정상적인 결과로 matrix값을 리턴한다.
}
void print_matrix(int** matrix, int row, int col) // 행렬을 출력하는 함수.
{
	int i, j;
	for (i = 0; i < row; i++) { //  반복문에서 i는 row보다 작을때까지
				for (j = 0; j < col; j++) //j는 col보다 작을때까지 작동되게 실행해 matrix의 모든 값을 출력한다.
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}
int free_matrix(int** matrix, int row, int col) // 행렬의 동적메모리할당을 해제해주는 함수.
{
	int i;
	if (matrix == NULL) { return -1; } // matrix가 빈값이면 -1의 리턴값으로 오류를 표시한다.

	for (i = 0; i < row; i++) // row의 크기(세로 크기만큼 반복)
		free(matrix[i]); // 2차원 배열의 가로 공간 메모리 할당 해제
	free(matrix); // 2차원 배열의 세로공간 메모리 할당 해제

	return 1; // 정상값 리턴.
}
int fill_data(int** matrix, int row, int col) // 행렬의 값을 채워주는 함수.
{
	int i, j;
	if (matrix == NULL) { return -1; } // matrix가 빈값이면 비정상 실행 -1의 리턴
	for (i = 0; i < row; i++) // 세로공간만큼 반복
		for (j = 0; j < col; j++) // 가로공간 만큼 반복.
			matrix[i][j] = rand() % 20; // matrix의 모든행렬에 0~19의 정수를 무작위로 넣어준다.
	return 1; // 정상값 리턴.
}
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // 행렬을 서로 더해주는 함수.
{
	int i, j;
	if (matrix_a == NULL || matrix_b == NULL) { return -1; } // matrix_a와 matrix_b의 함수가 NULL값이면 비정상값 -1 리턴.
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
			printf("%d\t", matrix_a[i][j] + matrix_b[i][j]);
		printf("\n");
	}
	return 1;
}
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a에서 matrix_b를 빼주는 함수.
{
	int i, j;
	if (matrix_a == NULL || matrix_b == NULL) { return -1; } // matrix_a값과 matrix_b값이 NULL값이면 비정상값 -1 리턴.
	for (i = 0; i < row; i++) { // 세로공간 만큼 반복
		for (j = 0; j < col; j++) // 가로공간 만큼 반복.
			printf("%d\t", matrix_a[i][j] - matrix_b[i][j]);
		printf("\n");
	}
	return 1;
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // 전치함수를 만드는 함수.
{
	int i, j;
	for (i = 0; i < row; i++) //배열의 세로 공간 만큼 반복.
		for (j = 0; j < col; j++) //배열의 가로 공간 만큼 반복.
			matrix_t[i][j] = matrix[j][i];
	printf("\n");
	if(matrix== NULL ||matrix_t == NULL){return -1;} // matrix 값과 matrix_t값이 NULL값이면 비정상값 -1 리턴.
	return 1;
}
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // 두 배열의 곱을 출력하는 함수.
{
	int i, j, k;
	int sum = 0;
	int** matrix_sum = create_matrix(row, row); // 두 배열을 곱한 값을 입력받을 배열을 생성해준다.
	if (matrix_a == NULL || matrix_t == NULL || matrix_sum == NULL) { return -1; } // 배열들이 NULL값이면 오류로 -1을 선언해준다.
	for (i = 0; i < row; i++) { // matrix_sum의 세로공간만큼 반복
		for (j = 0; j < row; j++) { // matrix_sum의 가로공간만큼 반복
			for (k = 0; k < col; k++)
				sum += matrix_a[i][k] * matrix_t[k][j];// a행렬의 i행의 원소들과 j열 원소들을 k까지 곱한 모든 수를 sum에 넣는다.
			matrix_sum[i][j] = sum; //sum에 임시저장된 값을 matrix_sum의 배열에 넣는다.
			sum = 0; // 계산을 위해 sum을 다시 0으로 바꾼다.
		}
	}
	print_matrix(matrix_sum, row, row); // 두행렬을 곱한 값이 들어있는 행렬을 출력한다.
	printf("\n");
	return 1; // 정상값 리턴.
}

