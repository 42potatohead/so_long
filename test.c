#include <stdio.h>

// Function to perform DFS
void dfs( char img[4][12], int x, int y, int prevClr, int newClr, int *exits, int *coins) {

    // printf("starting pos %d %d\n", x, y);
    // printf("starting value %c\n", img[x][y]);
    if (img[x][y] == 'F' || x == 4 || y == 11 || x == 0 || y == 0 || img[x][y] == '1')
        return;

    if(img[x][y] == 'E')
    {
        printf("found e\n");
        *(exits) +=1;
    }
    if(img[x][y] == 'C')
        *(coins) += 1;
    // Marking it as the new color
    img[x][y] = newClr;

    // Moving up, right, down and left one by one.
        dfs(img, x - 1, y, prevClr, newClr, exits, coins);
        dfs(img, x, y + 1, prevClr, newClr, exits, coins);
        dfs(img, x + 1, y, prevClr, newClr, exits, coins);
        dfs(img, x, y - 1, prevClr, newClr, exits, coins);
}

// FloodFill Function
void floodFill( char img[4][12], int x, int y, int newClr) {
    int prevClr = img[x][y];
    int exits=0;
    int coins=0;
    printf("prevClr %c \n", prevClr);
    if (prevClr == newClr)
        return;
    dfs(img, x, y, prevClr, newClr, &exits, &coins);
    printf("exits %d, coins %d\n", exits, coins);
}

// Driver code
int main() {
    // int img[3][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    char img[4][12] = {"111111111111", "100011C0E001", "10001100P001", "111111111111"};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%c ", img[i][j]);
        }
        printf("\n");
    }
     printf("\n");
      printf("\n");
       printf("\n");
    // Co-ordinate provided by the user
    int x = 2, y = 8;
    // New color that has to be filled
    char newClr = 'F';
    floodFill(img, x, y, newClr);

    // Printing the updated img
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%c ", img[i][j]);
        }
        printf("\n");
    }
    return 0;
}
