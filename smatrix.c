#include<iostream>
#include<vector> 
#include<stdlib.h>   // srand rand
#include<sys/time.h>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

#define MAX 1024
int step_i=0;
vector<vector<int> > C(MAX, vector<int>(MAX, 0));
vector<vector<int> > B(MAX, vector<int>(MAX, 0));
vector<vector<int> > A(MAX, vector<int>(MAX, 0));

void show_matrix(vector<vector<int> > &M, int size);

void* multi(void * arg) {
	int core = step_i++;
	for(int i=core*MAX/8;i<(core+1)*MAX/8;i++) {
		for(int j=0;j<MAX;j++) {
			for(int k=0;k<MAX;k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
}

/*void multiply(vector<vector<int> > &A, vector<vector<int> > &B, int size) {
	vector<vector<int> > R(size, vector<int>(size, 0));
	
	struct timeval start, end;
	gettimeofday(&start, 0);
	
	for(int i=0;i<size;i++) {
		for(int j=0;j<size;j++) {
			R[i][j] = 0;
			for(int k=0;k<size;k++) {
				R[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	gettimeofday(&end, 0);
	int sec = end.tv_sec - start.tv_sec;
	int usec = end.tv_usec - start.tv_usec;
	printf("\nEclapsed time %f msec\n", sec*1000.0 + usec/1000.0);
	//show_matrix(R, size);

}*/
void show_matrix(vector<vector<int> > &M, int size) {
	for(int i=0;i<size;i++) {
		for(int j=0;j<size;j++) {
			cout<<M[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int main(int argc, char **argv) {
	// size of matrix
	//int n = atoi(argv[1]);
	
	//vector<vector<int> > A(n, vector<int>(n,0));
	//vector<vector<int> > B(n, vector<int>(n,0));
	for(int i=0;i<MAX;i++) {
		for(int j=0;j<MAX;j++) {
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	}
	//multiply(A, B, MAX);
	
	pthread_t threads[8];

	struct timeval start, end;
	gettimeofday(&start, 0);
	
	for(int i=0;i<8;i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}
	for(int i=0;i<8;i++) 
		pthread_join(threads[i], NULL);

	gettimeofday(&end, 0);
	int sec = end.tv_sec - start.tv_sec;
	int usec = end.tv_usec - start.tv_usec;
	printf("\nEclapsed time %f msec\n", sec*1000.0 + usec/1000.0);
	
	//show_matrix(C, MAX);
	//show_matrix(A, n);
	//show_matrix(B, n);
	
	//multiply(A, B, n);

	return 0;
}
