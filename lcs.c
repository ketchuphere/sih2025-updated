#include <stdio.h>
#include <string.h>

#define MAX 100

int max(int a, int b) 
{
    return (a > b) ? a : b;
}

// Function to print the LCS from the DP table
void printLCS(char X[], char Y[], int m, int n, int LCS_table[MAX][MAX]) 
{
    int index = LCS_table[m][n];
    char lcs[index + 1];
    lcs[index] = '\0'; // Null-terminate the LCS string
    int i = m, j = n;
    while (i > 0 && j > 0) 
    {
        if (X[i - 1] == Y[j - 1]) 
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } 
        else if (LCS_table[i - 1][j] > LCS_table[i][j - 1])
            i--;
        else
            j--;
    }
    printf("LCS: %s\n", lcs);
}

int main() 
{
    char X[MAX], Y[MAX];
    int LCS_table[MAX][MAX];
    printf("Enter the first string into an array: ");
    scanf("%s", X);
    printf("Enter the second string into an array: ");
    scanf("%s", Y);
    int m = strlen(X);
    int n = strlen(Y);
    // Build LCS_table
    for (int i = 0; i <= m; i++) 
    {
        for (int j = 0; j <= n; j++) 
        {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }

    printLCS(X, Y, m, n, LCS_table);

    printf("LCS Length: %d\n", LCS_table[m][n]);

    return 0;
}
