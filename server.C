/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <iostream>
#include "SIMPLESOCKET.H"
#include "TASK3.H"
using namespace TASK3;
using namespace std;

class MyServer : public TCPserver{
public:
	MyServer(int portNmb, int maxDataRecv): TCPserver(portNmb, maxDataRecv){w=new World;};
protected:
	string myResponse (string input);

	World *w; //Zeiger


};


int main(){
	srand(time(nullptr));
	MyServer srv(2022,25);
	srv.run();
}

string MyServer::myResponse (string input){

	int x,y,c;
	string res;

	if ( input.compare(0,5,"start") == 0){
		if(w==NULL){
			w=new World;
		}else{
			delete w;
			w=new World;
		}
		return string ("Starten");
	}




	if ( input.compare(0,5,"shoot") == 0){
		// shoot(<int>,<int>), z.B: shoot(3,7)
		sscanf(input.c_str() ,"shoot(%i,%i)", &x,&y);

		if((x<1)||(y<1)){
			res = string("ERROR. Falsche Parametereingabe. ");
			return res;
		}
		if((x>10)||(y>10)){
			res = string("ERROR. Falsche Parametereingabe. ");
			return res;
				}
		else{

			c = w->shoot(x,y);
			cout << "Ergebnis: " << c << endl;

			res =  c+'0';

			return res;
		}
	}

		if (input.compare(0,5,"spiel") == 0){
					w->printBoard();
					res = string ("Schuss");
					return res;
		}


		return string ("Error");



	}


