/*
 * client.C
 *
 *  Created on: 10.11.2021
 *      Author: Anastasia Ekeshev
 *      		Andre Tabeling
 *      		Jana Plenter
 */

#include <cstdio>
#include <string>
#include <iostream>

#include <unistd.h> 					//contains various constants

#include <cstdlib> 						// this includes functions regarding memory allocation
#include <cerrno> 						//It defines macros for reporting and retrieving error conditions through error codes
#include <ctime>

#include <unistd.h> 					//contains various constants
#include <sys/types.h> 					//contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> 					// defines in_addr structure
#include <sys/socket.h> 				// for socket creation
#include <netinet/in.h> 				//contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK3.H"

using namespace TASK3;

using namespace std;

TCPclient c;
	string host = "localhost";
	string start = "start";
	string spiel;
	string shoot;
	char a[] = {"shoot(10,y)"};			// Ausnahme: x = 10
	char b[] = {"shoot(x,10)"};			// Ausnahme y = 10
	char e[] = {"shoot(10,10)"};		// Ausnahme x = 10, y = 10;
	char d[] = {"shoot(x,y)"};			// normale Antwort
	char sp[] = {"spiel"};
	char st[] = {"start"};
	char x;
	char y;
	int x1 = 0;
	int y1 = 0;
	int j1 = 0; 						//zaehler durchlaeufe auf verschiedene Welten Strategie 1
	int j2 = 0; 						//zaehler durchlaeufe auf verschiedene Welten Strategie 2
	int j3 = 0; 						//zaehler durchlaeufe auf verschiedene Welten Strategie 3
	int j4 = 0; 						//zaehler durchlaeufe auf verschiedene Welten Strategie 4
	int r1 = 0;							//zaehler durchlaeufe pro Welt Strategie 1
	int r2 = 0;							//zaehler durchlaeufe pro Welt Strategie 2
	int r3 = 0;							//zaehler durchlaeufe pro Welt Strategie 3
	int r4 = 0;							//zaehler durchlaeufe pro Welt Strategie 4
	int strat;
	int reci;
	int laps;


int strategie1(int laps1){
	srand(time(NULL));
	j1 = 0;

	do{

		start = st;						//Zeichenkette "start"
		c.sendData(start);
		r1 = 0;

		do{
			spiel= sp; 					// Zeichenkette "Spiel"

			x1 = (rand() % 10) +1;		// Zuweisung von den Werten für die Schusse
			y1 = (rand() % 10) +1;		// Werte zwischen 1 und 10

			if (x1 == 10){				// Ausnahme x = 10
				y = y1 + '0';			// y Wert wird in Zeichen umgewandelt und
				a[9] = y;				// y Wert wird in die Zeichenkette "shoot(10,y)" eingebracht
				shoot = a;				// Zuweisung des Schusses
			}
			if (y1 == 10){				// Ausnahme y = 10, ähnlich wie bei x = 10

				x = x1 + '0';
				b[6] = x;
				shoot = b;
			}
			if ((x1 == 10) && (y1 == 10))
			{shoot = e;}
			if((x1<10)&&(y1<10)){
				x = x1 + '0';
				y = y1 + '0';
				d[6] = x;				// Einbringung der y und x Werte in die Zeichenkette shoot(x,y)
				d[8] = y;
				shoot = d;
			}

			r1++;						// Zählung der Spielzüge
			c.sendData(shoot);			// client sendet den Schuss
			shoot = c.receive(25);  	// Antwort von dem Server (shoot = 1, 2, 3 oder 4
			c.sendData(spiel); 			// client fragt das Spielfeld ab
			spiel = c.receive(25); 		// server sendet das SPi

			}while(shoot!="4");

		j1++;
		cout<< "Strategie 1 Anzahl durchlaeufe " << r1 << endl;

	}while(j1<laps1);

	return r1;
}

int strategie2(int laps2){
	srand(time(NULL));
	j2 = 0;



	do{
		start =st;
		c.sendData(start);
		r2 = 0;
		int Feld [10][10] = {0};

		do{
			x1 = ((rand() % 10)) ;  		// Werte für die Schusse zwischen 0 und 9. Ohne +1, weil das angelegte Feld bei [0][0] anfängt
			y1 = ((rand() % 10)) ;
			spiel= sp;
			if (Feld[x1][y1] == 0){	 		// Wenn an der Stelle x,y 0 eingetragen ist, soll an dieser STelle eine 1 eingetragen werden
				Feld[x1][y1] = 1;			// (Feld ist besetzt)

				x1 = x1 + 1;				// +1, um die Koordinaten für den Schuss senden zu können
				y1 = y1 + 1;
				if ((x1 == 10) && (y1 == 10))
				{shoot = e;
				}

				if (x1 == 10){
					y = y1 + '0';
					a[9] = y;
					shoot = a;
				}
				if (y1 == 10){

					x = x1 + '0';
					b[6] = x;
					shoot = b;
				}
				if((x1<10)&&(y1<10)){
					x = x1 + '0';
					y = y1 + '0';
					d[6] = x;
					d[8] = y;
					shoot = d;
				}

				r2++;

				c.sendData(shoot);
				shoot = c.receive(25);
				c.sendData(spiel);
				spiel = c.receive(25);
			}

		}while(shoot!="4");

		j2++;
		cout<<"strategie 2 durchlauefe: "<<r2<<endl;

	}while(j2<laps2);


	return r2;
}


int strategie3(int laps3){
	srand(time(NULL));
	j3 = 0;

	do{
		shoot = "0";
		start =st;
		c.sendData(start);
		r3 = 0;

		int Feld [10][10] = {0};

		for(int k = 0; k<10; k++) {

				for( int l=0; l<10; l++) {
					if (shoot != "4"){
					spiel= sp;

			x1 = k;  							// Werte für die Schusse zwischen 0 und 9. Ohne +1, weil das angelegte Feld bei [0][0] anfängt
			y1 = l;

			if (Feld[x1][y1] == 0){	 			// Wenn an der Stelle x,y 0 eingetragen ist, soll an dieser STelle eine 1 eingetragen werden
				Feld[x1][y1] = 1;
												// (Feld ist besetzt)

				x1 = x1 + 1;					// +1, um die Koordinaten für den Schuss senden zu können
				y1 = y1 + 1;

				if (x1 == 10){
					y = y1 + '0';
					a[9] = y;
					shoot = a;
				}
				if (y1 == 10){

					x = x1 + '0';
					b[6] = x;
					shoot = b;
				}
				if ((x1 == 10) && (y1 == 10))
				{
					shoot = e;
				}

				if((x1<10)&&(y1<10)){
					x = x1 + '0';
					y = y1 + '0';
					d[6] = x;
					d[8] = y;
					shoot = d;
				}
			}
				r3++;

				c.sendData(shoot);
				shoot = c.receive(25);
				c.sendData(spiel);
				spiel = c.receive(25);
					}
				}
		}

		j3++;
		cout<< "Strategie 3 Anzahl durchlaeufe " << r3<< endl;


	}while(j3<laps3);

		return r3;
}


int strategie4(int laps4){
	srand(time(NULL));
	j4 = 0;

	do{
		shoot = "0";
		start =st;
		c.sendData(start);
		r4 = 0;

		int Feld [10][10] = {0};

		for(int k = 0; k<10; k++) {
				for( int l=0; l<10; l++) {
					if (shoot != "4"){
					spiel= sp;

			x1 = l;  							// Werte für die Schusse zwischen 0 und 9. Ohne +1, weil das angelegte Feld bei [0][0] anfängt
			y1 = k;

			if (Feld[x1][y1] == 0){	 			// Wenn an der Stelle x,y 0 eingetragen ist, soll an dieser STelle eine 1 eingetragen werden
				Feld[x1][y1] = 1;
												// (Feld ist besetzt)

				x1 = x1 + 1;					// +1, um die Koordinaten für den Schuss senden zu können
				y1 = y1 + 1;

				if (x1 == 10){
					y = y1 + '0';
					a[9] = y;
					shoot = a;
				}
				if (y1 == 10){

					x = x1 + '0';
					b[6] = x;
					shoot = b;
				}
				if ((x1 == 10) && (y1 == 10))
				{shoot = e;}
				if((x1<10)&&(y1<10)){
					x = x1 + '0';
					y = y1 + '0';
					d[6] = x;
					d[8] = y;
					shoot = d;
				}
			}

				r4++;






				c.sendData(shoot);
				shoot = c.receive(25);
				c.sendData(spiel);
				spiel = c.receive(25);

					}
				}
		}

		j4++;
		cout<< "Strategie 4 Anzahl durchlaeufe " << r4 << endl;

	}while(j4<laps4);

		return r4;
}


int main() {
	c.conn(host , 2022);						//connect to host

	cout << "Bitte waehlen sie eine strategie von 1-4: " << endl;
	cin >> strat;

	cout << "Wie viele Runden soll gespilet werden? " << endl;
	cin >> laps;

	switch (strat){

		case 1:
			strategie1(laps);
			break;
		case 2:
			strategie2(laps);
			break;
		case 3:
			strategie3(laps);
			break;
		case 4:
			strategie4(laps);
			break;
		default :
			cout <<"problem bei der Eingabe"<< endl;

	}


}
