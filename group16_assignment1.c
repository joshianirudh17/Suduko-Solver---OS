#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include<math.h>


int board[36][36];

typedef struct 
{
    int row;
    int col;
    int (*board)[36];
    int val;
    int size;
} parameters;

void * check_r(void* p0);


void * check_c(void* p0);


void * check_s(void* p0);

pthread_t tr, tc, thread_1;



 
void read_grid_from_file(int size, char *ip_file, int grid[36][36]) {
	FILE *fp;
	int i, j;
	fp = fopen(ip_file, "r");
	for (i=0; i<size; i++) 
		for (j=0; j<size; j++) {
			fscanf(fp, "%d", &grid[i][j]);
	}
}

void print_grid(int size, int grid[36][36]) {
	int i, j;
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++)
			printf("%d\t", grid[i][j]);
		printf("\n");
	}
}
int solve(int board[36][36], int n)
{
	
	int i,j,k;
	
	for(i=0;i<n;i++)
    {
    	for(j=0;j<n;j++)
    	{	
    		if(board[i][j]==0)
    		{
    			for(k=1;k<=n;k++)
    			{
parameters * p0 = (parameters *) malloc(sizeof(parameters));
    p0->row = i;
    p0->col = j;
    p0->board = board;
    p0->val = k;
    p0->size = n;
    
   pthread_create(&tr, NULL,check_r , (void*)p0); 
   pthread_create(&tc,NULL, check_c ,(void*)p0);
   pthread_create(&thread_1,NULL, check_s ,(void*)p0);
	void *a, *b, *c;
	pthread_join(tr,&a);
	pthread_join(tc,&b);
	pthread_join(thread_1,&c);   			
    			
    			if(((int)a==1) && ((int)b==1) && ((int)c==1)){
    					
    					board[i][j]=k;
    					if(solve(board,n))
    					return 1;
    					else
    					board[i][j]=0;
    					
    				}
    			}
    			return 0;
    			
    		}
    		
    	}
    }
    
return 1;
}


    

int main(int argc, char *argv[])
{
	int grid[36][36], size;
	
	if (argc != 3) {
		printf("Usage: ./sudoku.out grid_size inputfile");
		exit(-1);
	}
	
	size = atoi(argv[1]);
	int n=size;
	read_grid_from_file(size, argv[2], grid);
	
    solve(grid,n);
    print_grid(n,grid);
    return 0;
}

void * check_r(void* p0){
 
 parameters * data = (parameters *) p0;
    int r = data->row;
    int c = data->col;
    int num= data->val;
    int size= data->size;
    int m;
    for(m=0;m<size;m++)
    {
    	if(data->board[r][m]==num )
    	{
		return (void*) 0;
    	}
    }
    
    return (void*)1;
    
}

void * check_c(void* p0){
 parameters * data = (parameters *) p0;
    int r = data->row;
    int c = data->col;
    int num= data->val;
    int size= data->size;
    //int board[36][36]= data->board;
    int m;    
    for(m=0;m<size;m++)
    {
    	if(data->board[m][c]==num )
    	{
    	    	return (void*) 0;
    	}
    }
    		return (void*) 1;
}

void * check_s(void *p0) {
 parameters * data = (parameters *) p0;
    
    int r = data->row;
    int c = data->col;
    int num= data->val;
    int size= data->size;
   // int board[36][36]= data->board;
    int m;

    int k = sqrt((double)(size));
        r=r-r%k;
    c=c-c%k;
    for (int p = 0; p < k; p++)
        for (int q = 0; q < k; q++)
            if (data->board[p + r][q + c] ==num)
               {
                return (void*)0;
                }
                
                return (void*)1;
}
