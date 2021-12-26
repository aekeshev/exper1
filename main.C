//============================================================================
// Name        : INF3_Prak.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>


#include "TASK3.H"


using namespace std;
using namespace TASK3;



int main(){
	// Probe für Strategie 2
	int brett[10][10] = { 0 };
	int x1 = 0;
	int y1 = 0;
	brett[x1][y1] = 0;

	for(int i=0; i<10; i++) {
						 //Schleife fuer Spalten, X-Achse
						for( int j=0; j<10; j++) {
							printf("%d ", brett[i][j]);
						}
					printf("\n");
					}
	printf("\n");

int m =0;

	do{
		int x1 = (rand() % 10+1) ;		// Zuweisung von den Werten für die Schusse
		int y1 = (rand() % 10+1) ;

		if (brett[x1][y1] == 0){
				// Werte zwischen 1 und 10
		          // Feld besetzt
			brett[x1][y1] = 1;
					int a, b;

						// Schleife fuer Zeilen, Y-Achse
						for(a=0; a<10; a++) {
							// Schleife fuer Spalten, X-Achse
							for(b=0; b<10; b++) {
								printf("%d ", brett[a][b]);
							}
							printf("\n");
						}
						printf("\n");
						printf("%d",m);
						printf("\n");
						m++;

	}

	else{continue;}
	}while (m<100);


    return 0;

}





