/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <cstdio>
#include <string>
#include <iostream>

#include <unistd.h> //contains various constants

#include <cstdlib> // this includes functions regarding memory allocation
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime>

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK3.H"

using namespace TASK3;

using namespace std;

TCPclient c;
	string host = "localhost";
	string start = "start";
	string spiel;
	string shoot;
	string test;
	char a[] = {"shoot(10,y)"};		// Ausnahme: x = 10
	char b[] = {"shoot(x,10)"};		// Ausnahme y = 10
	char d[] = {"shoot(x,y)"};		// normale Antwort
	char sp[] = {"spiel"};			// Nachristen an den server
	char st[] = {"start"};
	char sh[] = {"shoot"};
	char x;
	char y;
	int x1 = 0;
	int y1 = 0;
	long int i = 0;
	int world =0;
	long int i2=0;
	int i3 =0;
	bool belegt;
	int x2;
	int y2;
	int n=0;
	string msg;


int strategie1(int laps1){

	int rounds=0;
	int j1=0;
	srand(time(NULL));




	do{
		start = "start";
		c.sendData(start);
		rounds =0;
		do{
			spiel= sp; // Zeichenkette "Spiel"

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
			if((x1<10)&&(y1<10)){
				x = x1 + '0';
				y = y1 + '0';
				d[6] = x;			// Einbringung der y und x Werte in die Zeichenkette shoot(x,y)
				d[8] = y;
				shoot = d;
			}

			rounds++;				// Zählung der Spielzüge

			// cout << "client sendet . :" << shoot << endl;

			c.sendData(shoot);		// client sendet den Schuss
			shoot = c.receive(25);  // Antwort von dem Server (shoot = 1, 2, 3 oder 4)

			//	cout << "Server Antwortet  :" << shoot << endl;
			//	cout << "client sendet :" << spiel << endl;

			c.sendData(spiel); // client fragt das Spielfeld ab
			spiel = c.receive(25); // server sendet das SPi
			//cout << "Server Antwortet  :" << spiel << endl;
			//sleep(1);
			//cout << "Schuss : " << i << endl;
			//cout << "Ergebniss : " << strat << endl;

			}while(shoot!="4");

		j1++;
		cout<< "Strategie 1 Anzahl durchlaeufe " << rounds << endl;

	}while(j1<laps1);



	return rounds;
}

int strategie2(int laps2){

	int rounds ;
	int j2=0;
	srand(time(NULL));



	do{
		start ="start";
		c.sendData(start);
		rounds=0;
		int Feld [10][10] = {0};

		do{
			x1 = ((rand() % 10)) ;  // Werte für die Schusse zwischen 0 und 9. Ohne +1, weil das angelegte Feld bei [0][0] anfängt
			y1 = ((rand() % 10)) ;
			spiel= sp;
			if (Feld[x1][y1] == 0){	 // Wenn an der Stelle x,y 0 eingetragen ist, soll an dieser STelle eine 1 eingetragen werden
				Feld[x1][y1] = 1;			// (Feld ist besetzt)

				x1 = x1 + 1;				// +1, um die Koordinaten für den Schuss senden zu können
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
				if((x1<10)&&(y1<10)){
					x = x1 + '0';
					y = y1 + '0';
					d[6] = x;
					d[8] = y;
					shoot = d;
				}

				rounds++;
				/*for(int i=0; i<10; i++) { 			// zur Veranschaulichung, kann später gelöscht werden

					for( int j=0; j<10; j++) {
						printf("%d ", Feld[i][j]);
						}
						printf("\n");
					}
				printf("\n");

				*/


				c.sendData(shoot);
				shoot = c.receive(25);

			//	cout << "Server Antwortet  :" << shoot << endl;
			//	cout << "client sendet :" << spiel << endl;

				c.sendData(spiel);
				spiel = c.receive(25);
			//cout << "Server Antwortet  :" << spiel << endl;
			//sleep(1);
			//cout << "Schuss : " << i << endl;
			//cout << "Ergebniss : " << strat << endl;



			}

		}while(shoot!="4");

		j2++;
		cout<<"strategie 2 durchlauefe: "<<rounds<<endl;

	}while(j2<laps2);


	return rounds;
}


int strategie3(int laps3){

	int rounds = 0;

	int j3=0;
	srand(time(NULL));

	do{
		start ="start";
		c.sendData(start);
		start = c.receive(25);
		cout << start <<endl;
		rounds=0;
		int Feld [10][10] = {0};

		do{
			x1 = ((rand() % 10)) ;  // Werte für die Schusse zwischen 0 und 9. Ohne +1, weil das angelegte Feld bei [0][0] anfängt
			y1 = ((rand() % 10)) ;
			spiel= sp;
			if (Feld[x1][y1] == 0){	 // Wenn an der Stelle x,y 0 eingetragen ist, soll an dieser STelle eine 1 eingetragen werden
						// (Feld ist besetzt)

				x1 = x1 + 1;				// +1, um die Koordinaten für den Schuss senden zu können
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
				if((x1<10)&&(y1<10)){
					x = x1 + '0';
					y = y1 + '0';
					d[6] = x;
					d[8] = y;
					shoot = d;
				}

				rounds++;
				/*for(int i=0; i<10; i++) { 			// zur Veranschaulichung, kann später gelöscht werden

					for( int j=0; j<10; j++) {
						printf("%d ", Feld[i][j]);
						}
						printf("\n");
					}
				printf("\n");

				*/


				c.sendData(shoot);
				shoot = c.receive(25);

			//	cout << "Server Antwortet  :" << shoot << endl;
			//	cout << "client sendet :" << spiel << endl;

				c.sendData(spiel);
				spiel = c.receive(25);
			//cout << "Server Antwortet  :" << spiel << endl;
			//sleep(1);
			//cout << "Schuss : " << i << endl;
			//cout << "Ergebniss : " << strat << endl;

				if (shoot == "1" || shoot == "2")
					{Feld[(x1-1)][(y1-1)] =2;}
					else
					{Feld[x1-1][y1-1] = 1;	}

			}
			else{
				continue;
			} // Wenn das Feld besetzt ist, soll fortgefahren werden und neue zufällige Zahlen generiert werden.

		}while(shoot!="4");


		j3++;
		cout<< "Strategie 3 Anzahl durchlaeufe " << rounds << endl;

	}while(j3<laps3);

		return rounds;
}




int main() {
	//connect to host
	c.conn(host , 2022);
	//cout << "client sendet:" << start << endl;

	int strat;
	int reci;
	int i2;
	int laps;

	cout << "Bitte waehlen sie eine strategie von 1-3: " << endl;
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

	default :
		cout <<"problem bei der Eingabe"<< endl;

	}








}
