#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int** rotateMatrix90(int **a, int row, int col)
{
    int i,j;
    int **output;
    output = malloc(row * sizeof *output);
    for (i = 0; i < row; i++)
    {
        output[i] = malloc(col * sizeof *output[i]);
    }
    
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            output[i][col-1-j] = a[j][i];
        }
    }
    return output;
}

int** rotateMatrix270(int **a, int row, int col)
{
    int i,j;
    int **output;
    output = malloc(row * sizeof *output);
    for (i = 0; i < row; i++)
    {
        output[i] = malloc(col * sizeof *output[i]);
    }
    
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            output[row-1-i][j] = a[j][i];
        }
    }
    return output;
}

int** rotateMatrix180(int **a, int row, int col)
{
    int i,j;
    int **output;
    output = malloc(row * sizeof *output);
    for (i = 0; i < row; i++)
    {
        output[i] = malloc(col * sizeof *output[i]);
    }
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            output[row-1-i][col-1-j] = a[i][j];
        }
    }
    return output;
}


void printtofile(int **matrix, int row, int col, int greyscale, char num[])
{
    FILE *file;
    int i,j;
    file = fopen("output.txt","w");
    fprintf(file, "P2\n%d %d\n%d\n" ,col, row, greyscale);
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(matrix[i][j] < 10)
                fprintf(file, "%d  ", matrix[i][j]);
            else
                fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file,"\n");
    }
    char filename[30]= "output";
    strcat(filename, num);
    strcat(filename, ".pgm");
    rename("output.txt",filename);
    printf("File created called (%s)\n\n", filename);
    fclose(file);
}

int main()
{
    FILE *file;
    char version[3];
    int row, col, greyscale, i, j, num;
    int **matrix;
    char filename[30],newname[30];
label: printf("Enter the filename (Eg: sample.pgm):\n");
    scanf("%s",filename);
   
       
    int l=strlen(filename);
    for(i=0;i<l;i++)
      {
         if(filename[i]=='.')
         break;
         newname[i]=filename[i];
      }
      
    strcat(newname, ".txt");  
    rename(filename,newname);
    file = fopen(newname,"r");
if(file)///// check if file exists
{
    fscanf(file, "%s", version);
    fscanf(file, "%d", &col);
    fscanf(file, "%d", &row);
    fscanf(file, "%d", &greyscale);
    matrix = malloc(row * sizeof *matrix);
    for (i = 0; i < row; i++)
    {
        matrix[i] = malloc(col * sizeof *matrix[i]);
    }
    
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    
    rename(newname, filename);
    
    
    ////////////////MENU/////////////////////////
 redo:  printf("\nRotate image by:\n1. 90\n2. 180\n3. 270\n4. EXIT\n");
        scanf("%d", &num);
        switch(num)
        {
        case 1:
            matrix = rotateMatrix90(matrix, col, row);
            printtofile(matrix,col,row,greyscale, "90");
            break;
        case 2:
            matrix = rotateMatrix180(matrix, row, col);
            printtofile(matrix,row,col,greyscale, "180");
            break;
        case 3:
            matrix = rotateMatrix270(matrix, col, row);
            printtofile(matrix,col,row,greyscale, "270");
            break;
        case 4:
            exit(0);
            break;
        default:
        	printf("Re-enter a correct option.\n");
        	goto redo;
        	break;
        }
    for (i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    }///// close of catching error
    
    else
    {
    	printf("Error: File not present\n\n");
    	goto label;
    }
 
    return 0;
}
