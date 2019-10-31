#include <iostream>
#include <cstdlib>
#include<stdlib.h>
#include<time.h>

using namespace std;

int main (void)
{

	int cantidad_de_vectores =100000;
	int tamanio_del_vector = 4;

	srand(time(NULL));
	
	for (int i = 0; i < cantidad_de_vectores; i++)
	{
		

		for(int j = 0; j < rand()%11 + 1; j++)
		{
			cout << "(" <<  rand()%101 << ", " << rand()%101 << ")"<< " ";
		}
		cout << endl;
	}
	
	return 0;
}
