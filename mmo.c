#include <stdio.h>
#include <limits.h>

#define MAX 20
int m[MAX][MAX], s[MAX][MAX];
int p[MAX];

// Function to print optimal parenthesization
void printOptimalParenthesis(int i, int j) 
{
    if (i == j) 
    {
        printf("A%d", i);
    } 
    else 
    {
        printf("(");
        printOptimalParenthesis(i, s[i][j]);
        printOptimalParenthesis(s[i][j] + 1, j);
        printf(")");
    }
}

int main() 
{
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    int row, col;
    // Input matrix dimensions
    for (int i = 1; i <= n; i++) 
    {
        printf("Enter row and col size of A%d: ", i);
        scanf("%d %d", &row, &col);
        if (i == 1) 
        {
            p[0] = row;
            p[1] = col;
        } 
        else 
        {
            // Validate dimension compatibility
            if (p[i - 1] != row) 
            {
                printf("Error: Incompatible dimensions between A%d and A%d\n", i - 1, i);
                return 0;
            }
            p[i] = col;
        }
    }
    // Initialize m table
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    // Chain length L
    for (int L = 2; L <= n; L++)
    {
        for (int i = 1; i <= n - L + 1; i++) 
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    // Print M Table
    printf("\nM Table:\n");
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            if (i > j)
                printf("0 ");
            else
                printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    // Print S Table
    printf("\nS Table:\n");
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            printf("%d ", s[i][j]);
        }
        printf("\n");
    }
    // Print optimal parenthesization
    printf("\nOptimal parenthesization: ");
    printOptimalParenthesis(1, n);
    printf("\n");
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);
    return 0;
}
