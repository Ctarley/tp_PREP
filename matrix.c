#include "matrix.h"


Matrix* create_matrix_from_file(FILE* file)
{
	uint32_t cols = 0;
	uint32_t rows = 0;
	uint32_t n = 0; //number or rows in file. n != cols*rows (not always)

	rewind(file);
	if (fscanf(file, "%d\n%d\n", &rows, &cols) == EOF)
	{
		printf("Error if file format!\n");
	}

	Matrix* M = create_matrix(rows, cols);
	if (fscanf(file, "%d\n", &n) == EOF)
	{
		printf("Error if file format!\n");
	}

/*	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			M[i].row = i;
			M[i].col = j;
			M[i].val = 0;
			M[i].cols = cols;
			M[i].rows = rows;
		}
	}*/

	uint32_t row, col;
	double val;
	for(int i=0; i < n; i++)
	{
		if (fscanf(file, "%d %d %lf\n", &row, &col, &val) == EOF)
		{
			printf("Error if file format!\n");
		}
		/*M[i].row = row;
		M[i].col = col;
		M[i].val = val;
		M[i].cols = cols;
		M[i].rows = rows;*/
		set_elem(M, row, col, val);
	}
	
	return M;
}

Matrix* create_matrix(int row, int col)
{
	Matrix *ptr = NULL;
	ptr = (Matrix*)malloc(sizeof(Matrix));
	if (!ptr)
	{
		printf("Could not allocate memory for matrix!\n");
		return NULL;
	}
	ptr->elem = (Element*)malloc(row*col*sizeof(Element));
	if (!ptr->elem)
	{
		printf("Could not allocate memory for matrix elements!\n");
		return NULL;
	}


	ptr->rows = row;
	ptr->cols = col;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			ptr->elem[col*i+j].row = i;
			ptr->elem[col*i+j].col = j;
			ptr->elem[col*i+j].val = 0;
		}
	}
	return ptr;
}

int get_rows(Matrix* matrix)
{
	return matrix->rows;
}

int get_cols(Matrix* matrix)
{
	return matrix->cols;
}

double get_elem(Matrix* matrix, int row, int col)
{
	uint32_t cols = matrix[0].cols;
	uint32_t rows = matrix[0].rows;
	if ((col > cols) || (row > rows))
	{
		printf("Invalid index.\n");
		return 0.0;
	}
	return matrix->elem[(row)*cols+col].val;
}
void set_elem(Matrix* matrix, int row, int col, double val)
{
	uint32_t cols = matrix->cols;
	uint32_t rows = matrix->rows;
	if ((col > cols) || (row > rows))
	{
		printf("Invalid index.\n");
		return;
	}
	matrix->elem[(row)*cols+col].val = val;
}

void free_matrix(Matrix* matrix)
{
	// for (int i = 0; i < matrix->rows * matrix-> cols; ++i)
	// {
	// 	free
	// }
	free(matrix->elem);
	free(matrix);
}