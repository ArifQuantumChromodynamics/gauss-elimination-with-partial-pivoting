#include <stdio.h>
#include <math.h>

// Function to print the augmented matrix
void printMat(float A[4][5]) {
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
}

// Function to swap two rows in the augmented matrix
void swapRows(float A[4][5], int row1, int row2) {
    for (int j = 0; j < 5; j++) {
        float temp = A[row1][j];
        A[row1][j] = A[row2][j];
        A[row2][j] = temp;
    }
}

// Function to perform partial pivoting
void partialPivot(float A[4][5], int startRow){
    for (int i = startRow; i < 4; i++) {
        int maxRow = i;
        for (int k = i + 1; k < 4; k++) {
            if (fabs(A[k][i]) > fabs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        if (maxRow != i) {
            swapRows(A, i, maxRow);
        }
    }
}

int main() {
	
	/* 
	This code is developed for finding the roots of a system of 4 simultaneous linear equations. The linear equations are in the follwoing form: Ax = B, where, 'A' is the coefficient matrix, 'B' is the constant matrix and 'x' contains variables. 
	*/
	
	//float A[4][4] = {{20.0, 9.0, 18.0, 1.0}, {20.0, 9.3, 19.0, 1.0}, {18.0, 10.0, 14.0, 1.0}, {20.0, 9.0, 19.4, 1.0}};
	//float B[4] = {7.1869, 7.1942, 7.1798, 7.1622};

	
	float A[4][4] = {{2.0, 3.0, 1.0, 4.0}, {4.0, 1.0, 2.0, 3.0}, {3.0, 2.0, 3.0, 1.0}, {1.0, 4.0, 4.0, 2.0}};
	float B[4] = {10.0, 12.0, 11.0, 13.0};

	float aug_mat[4][5];

    // Initialize the augmented matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            aug_mat[i][j] = A[i][j];
        }
        aug_mat[i][4] = B[i];
    }

    // Print the original augmented matrix
	printf("Original augmented matrix:\n");
	printMat(aug_mat);
	printf("\n");

	//Gauss Elimination with Partial Pivoting
	for (int a = 0; a < 3; a++){
		partialPivot(aug_mat, a);
		for (int b = a + 1; b < 4; b++){
			float factor = aug_mat[b][a] / aug_mat[a][a];
			for (int c = 0; c < 5; c++){
				aug_mat[b][c] -= factor * aug_mat[a][c];
			}
		}
	}
	printf("The Augmented Matrix, after performing gauss elimination:\n");
	printMat(aug_mat);
	printf("\n");

    // Perform back substitution
    float x[4];
    for (int i = 3; i >= 0; i--) {
        x[i] = aug_mat[i][4];
        for (int j = i + 1; j < 4; j++) {
            x[i] -= aug_mat[i][j] * x[j];
        }
        x[i] = x[i] / aug_mat[i][i];
    }

    // Print the solution
    printf("Solution:\n");
    for (int i = 0; i < 4; i++) {
        printf("x%d = %f\n", i + 1, x[i]);
    }

    return 0;
}