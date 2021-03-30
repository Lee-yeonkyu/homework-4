#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  /* Method Declaration */
int** create_matrix(int row, int col); //�Է¹��� row�� col�� �̿��� matrix�� ���� �޸� �Ҵ��� �Ѵ�.
void print_matrix(int** matrix, int row, int col); // ����� ����ϴ� �Լ�.
int free_matrix(int** matrix, int row, int col); // ����� �����޸��Ҵ��� �������ִ� �Լ�.
int fill_data(int** matrix, int row, int col);  // ����� ���� ä���ִ� �Լ�.
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // ����� ���� �����ִ� �Լ�.
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // matrix_a���� matrix_b�� ���ִ� �Լ�.
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // ��ġ�Լ��� ����� �Լ�.
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);// �� �迭�� ���� ����ϴ� �Լ�.

int main()
{

	char command; // �����ų �Լ��� �Է¹��� ���ڿ��� ������ ����.
	printf("[----- [�̿���]  [2018038038] -----]\n");

	int row, col; //��, ���� ������ ����.
	srand(time(NULL)); // srand�Լ��ȿ� time�Լ��� ����� �׻� �ٸ����� seed������ ������ ��´�.

	printf("Input row and col : ");
	fflush(stdout);
	scanf("%d %d", &row, &col); // row, col�� �Է¹޴´�.
	int** matrix_a = create_matrix(row, col); // create_matrix�Լ��� ���� matrix_a�� row,col�� �´� ���� �޸� �Ҵ�.
	int** matrix_b = create_matrix(row, col); // create_matrix�Լ��� ���� matrix_b�� row,col�� �´� ���� �޸� �Ҵ�.
	int** matrix_a_t = create_matrix(col, row); //create_matrix�Լ��� ���� matrix_a_t�� row,col�� �´� ���� �޸� �Ҵ�.

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { return -1; } //matrix_a �̳� matrix_b ���� ������� -1�� �������ش�.

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
		scanf(" %c", &command); //command���� �Է¹޴´�.

		switch (command) {
		case 'z': case 'Z': // command���� z�� Z�� ���
			printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col); // fill_data�� �̿��� matrix_a�� ���ڸ� ä�� �ִ´�.
			fill_data(matrix_b, row, col); // fill_data�� �̿��� matrix_b�� ���ڸ� ä�� �ִ´�.
			break;
		case 'p': case 'P': // command���� p�� P�� ���
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // matrix_a�� ����Ѵ�.
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // matrix_b�� ����Ѵ�.
			break;
		case 'a': case 'A': // command���� a�� A�� ���
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // matrix_a�� matrix_b�� ���Ѵ�.
			break;
		case 's': case 'S': // command���� s�� S�� ���
			printf("Subtract two matrices \n");
			subtraction_matrix(matrix_a, matrix_b, row, col); // matrix_a�� matrix_b�� ����.
			break;
		case 't': case 'T': // command���� t�� T�� ���
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a����� ��ġ�� matrix_a_t ��ġ��ķ� �����.
			print_matrix(matrix_a_t, col, row); // ��ġ��� matrix_a_t �� ����Ѵ�.
			break;
		case 'm': case 'M': // command���� m�� M�� ���
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a����� ��ġ�� matrix_a_t ��ġ��ķ� �����.
			multiply_matrix(matrix_a, matrix_a_t, row, col); //matrix_a�� matrix_a_t�� ���� ���� ����Ѵ�.
			break;
		case 'q': case 'Q': // command���� q�� Q�� ���
			printf("Free all matrices..\n");
			free_matrix(matrix_a_t, col, row); // matrix_a_t�� �����޸��Ҵ��� Ǯ���ش�.
			free_matrix(matrix_a, row, col); // matrix_a�� �����޸��Ҵ��� Ǯ���ش�.
			free_matrix(matrix_b, row, col); // matrix_b�� �����޸��Ҵ��� Ǯ���ش�.
			break;
		default: // �ٸ� ���� �Է��ҽÿ� �����϶�� �޼����� ����ϰ� �ݺ��Ѵ�.
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');  // q�� Q�� �Է¹����� �ݺ������� �����ȴ�.

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //�Է¹��� row�� col�� �̿��� matrix�� ���� �޸� �Ҵ��� �Ѵ�.
{
	int i;

	if (row <= 0 || col <= 0) { // row�� col�� ������ NULL���� ������ ������ ���ش�.
		printf("Check the sizes of row and col!\n");
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); // matrix�� ���� ������ row��ŭ ���� �޸� �Ҵ��Ѵ�.
	for (i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * col); // matrix�� ���� ������ col��ŭ ���� �޸� �Ҵ��Ѵ�.
	}
	if (matrix == NULL) { // �Ҵ�� matrix�� NULL�̸� NULL���� �����Ѵ�.
		printf("matrix is NULL");
		return NULL;
	}

	return matrix; // �������� ����� matrix���� �����Ѵ�.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // ����� ����ϴ� �Լ�.
{
	int i, j;
	for (i = 0; i < row; i++) { //  �ݺ������� i�� row���� ����������
				for (j = 0; j < col; j++) //j�� col���� ���������� �۵��ǰ� ������ matrix�� ��� ���� ����Ѵ�.
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // ����� �����޸��Ҵ��� �������ִ� �Լ�.
{
	int i;
	if (matrix == NULL) { return -1; } // matrix�� ���̸� -1�� ���ϰ����� ������ ǥ���Ѵ�.

	for (i = 0; i < row; i++) // row�� ũ��(���� ũ�⸸ŭ �ݺ�)
		free(matrix[i]); // 2���� �迭�� ���� ���� �޸� �Ҵ� ����
	free(matrix); // 2���� �迭�� ���ΰ��� �޸� �Ҵ� ����

	return 1; // ���� ����.
}

/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // ����� ���� ä���ִ� �Լ�.
{
	int i, j;
	if (matrix == NULL) { return -1; } // matrix�� ���̸� ������ ���� -1�� ����
	for (i = 0; i < row; i++) // ���ΰ�����ŭ �ݺ�
		for (j = 0; j < col; j++) // ���ΰ��� ��ŭ �ݺ�.
			matrix[i][j] = rand() % 20; // matrix�� �����Ŀ� 0~19�� ������ �������� �־��ش�.
	return 1; // ���� ����.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // ����� ���� �����ִ� �Լ�.
{
	int i, j;
	if (matrix_a == NULL || matrix_b == NULL) { return -1; } // matrix_a�� matrix_b�� �Լ��� NULL���̸� ������ -1 ����.
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
			printf("%d\t", matrix_a[i][j] + matrix_b[i][j]);
		printf("\n");
	}
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a���� matrix_b�� ���ִ� �Լ�.
{
	int i, j;
	if (matrix_a == NULL || matrix_b == NULL) { return -1; } // matrix_a���� matrix_b���� NULL���̸� ������ -1 ����.
	for (i = 0; i < row; i++) { // ���ΰ��� ��ŭ �ݺ�
		for (j = 0; j < col; j++) // ���ΰ��� ��ŭ �ݺ�.
			printf("%d\t", matrix_a[i][j] - matrix_b[i][j]);
		printf("\n");
	}
	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // ��ġ�Լ��� ����� �Լ�.
{
	int i, j;
	for (i = 0; i < row; i++) { //�迭�� ���� ���� ��ŭ �ݺ�.
		for (j = 0; j < col; j++) //�迭�� ���� ���� ��ŭ �ݺ�.
			matrix_t[i][j] = matrix[j][i]; //
	}
	printf("\n");
	if(matrix== NULL ||matrix_t == NULL){return -1;} // matrix ���� matrix_t���� NULL���̸� ������ -1 ����.
	return 1;
}
/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // �� �迭�� ���� ����ϴ� �Լ�.
{
	int i, j, k;
	int sum = 0;
	int** matrix_sum = create_matrix(row, row); // �� �迭�� ���� ���� �Է¹��� �迭�� �������ش�.

	if (matrix_a == NULL || matrix_t == NULL || matrix_sum == NULL) { return -1; } // �迭���� NULL���̸� ������ -1�� �������ش�.

	for (i = 0; i < row; i++) { // matrix_sum�� ���ΰ�����ŭ �ݺ�
		for (j = 0; j < row; j++) { // matrix_sum�� ���ΰ�����ŭ �ݺ�
			for (k = 0; k < col; k++)
				sum += matrix_a[i][k] * matrix_t[k][j];// a����� i���� ���ҵ�� j�� ���ҵ��� k���� ���� ��� ���� sum�� �ִ´�.
			matrix_sum[i][j] = sum; //sum�� �ӽ������ ���� matrix_sum�� �迭�� �ִ´�.
			sum = 0; // ����� ���� sum�� �ٽ� 0���� �ٲ۴�.
		}

	}
	print_matrix(matrix_sum, row, row); // ������� ���� ���� ����ִ� ����� ����Ѵ�.
	printf("\n");

	return 1; // ���� ����.
}

