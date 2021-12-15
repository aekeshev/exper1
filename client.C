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

int main() {
	srand(time(NULL));
		TCPclient c;
		string host = "localhost";
		 string start = "start";
		 string spiel = "spiel";
		 string shoot;
		 int x1,y1;
		 int i = 0;





		//connect to host
		c.conn(host , 2022);
			cout << "client sends:" << start << endl;
			c.sendData(start);
			start = c.receive(25);
			cout << "got response:" << start << endl;

			do{

					i++;
						x1 = (rand() % 10)+1;
						y1 =( rand() % 10) +1;
						if (x1 = 10)
						{
							char a[] = {"shoot(10,y)"};
							char y = y1 + '0';
							a[9] = y;
							string shoot = a;
						}
						else if (y1 = 10)
						{
							char a[] = {"shoot(x,10)"};
							char x = x1 + '0';
							a[6] = x;
							string shoot = a;
						}
						else
						{
						char a[] = {"shoot(x,y)"};
								 char x = x1 + '0';
								 char y = y1 + '0';
								 a[6] = x;
								 a[8] = y;
								 string shoot = a;
						}

								 cout << "client sends:" << shoot << endl;
								 			c.sendData(shoot);
								 			shoot = c.receive(25);
								 			cout << "got response:" << shoot << endl;
								 			cout << "client sends:" << spiel << endl;
								 			c.sendData(spiel);
								 			spiel = c.receive(25);
								 			cout << "got response:" << spiel << endl;
								 			sleep(1);
					}while(i < 100);
			//while(res != TASK3::GAME_OVER);


	}



/*
 * 14.12
 * srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2025);

	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);
		/*
 */
