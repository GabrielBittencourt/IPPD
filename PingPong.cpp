// Gabriel Bittencourt
// PingPong.cpp


#include "stdafx.h"
#include <mpi.h>
#include <stdio.h>
#include <string.h>


const int MAX_STRING = 100;


int main(void) {

	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	for (int i = 0; i < 4; i++)
	{
		if (my_rank != 0)
		{
			sprintf_s(greeting, "The ball is with processor %d", my_rank);
			MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		}

		else
		{
			printf("The ball is with processor %d\n", my_rank);
			for (int q = 1; q < comm_sz; q++)
			{
				MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("%s\n", greeting);
			}
		}
	}
MPI_Finalize();
}
