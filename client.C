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
	char a[] = {"shoot(10,y)"};
	char b[] = {"shoot(x,10)"};
	char d[] = {"shoot(x,y)"};
	char sp[] = {"spiel"};
	char st[] = {"start"};
	char sh[] = {"shoot"};
	char x;
	char y;
	int x1,y1;
	long int i = 0;
	int world =0;
	long int i2=0;
	int i3 =0;
	bool belegt;
	int x2;
	int y2;
	int n=0;

int strategie1(){

	int rounds;
	srand(time(NULL));

	//connect to host
	c.conn(host , 2022);
	//cout << "client sendet:" << start << endl;
	c.sendData(start);
	start = c.receive(25);
	//cout << "Server antwortet :" << start << endl;

	do{
		spiel= sp;
		x1 = (rand() % 10) +1;
		y1 = (rand() % 10) +1;

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

		// cout << "client sendet . :" << shoot << endl;
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

		}while(shoot!="4");

	return rounds;
}

int main() {

	int strat=strategie1();

	cout << "Ergebniss Strategie : " << strat << endl;




}
