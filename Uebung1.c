// Uebung1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	int number;
	int multiplicity;
	
	printf("Insert a positive number: ");
	scanf("%i",&number);
	printf("\nThe prime factorization of %i is: \n",number);
	
	
	for (int i = 2; i <= number; i++)
	{
		multiplicity = 0;
		while (number % i == 0)
		{
			number = number / i;
			multiplicity++;
		}
		if (multiplicity != 0)
		  printf("%i ^ %i %s",i,multiplicity, (number!=1)? "* ": "");
	}
	printf("\n");

	return 0;
}

