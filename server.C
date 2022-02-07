/*
 * server.C
 *
 *  Created on: 10.11.2021
 *      Author: Anastasia Ekeshev
 *      		Andre Tabeling
 *      		Jana Plenter
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
	MyServer(int portNmb, int maxDataRecv): TCPserver(portNmb, maxDataRecv){w = new World;};		//neue adresse zuweisen
protected:
	string myResponse (string input);

	World *w; 																						//Zeiger auf die Instanz von world "adresse"

};


int main(){
	srand(time(nullptr));
	MyServer srv(2022,25);											//Kommunikationskanal
	srv.run();
}

string MyServer::myResponse (string input){

	int x,y,c;
	string res;

	if ( input.compare(0,5,"start") == 0){							//Nachricht von Client lesen prüfen ob die Nachricht verwertbar ist
		if(w==NULL){												//Prüfen ob bereits eine Spielwelt existiert
			w=new World;											//Neue Welt

		}else{
			delete w;												//alte Welt Löschen
			w=new World;											//Neue Welt
		}
		cout << "Neue Welt erstellt " << endl;
		return string ("Neue Welt");								//Nachricht an client
	}


	if ( input.compare(0,5,"shoot") == 0){							//Nachricht von Client lesen prüfen ob die Nachricht verwertbar ist
		sscanf(input.c_str() ,"shoot(%i,%i)", &x,&y);				//Koordinaten empfangen

		if((x<1)||(y<1)){											//Prüfen ob die Koordinaten im Spielfeld liegen
			res = string("ERROR. Falsche Parametereingabe. ");
			return res;												//Fehlermeldung zurück geben
		}
		if((x>10)||(y>10)){
			res = string("ERROR. Falsche Parametereingabe. ");		//Prüfen ob die Koordinaten im Spielfeld liegen
			return res;												//Fehlermeldung zurück geben
		}
		else{														//Koordinaten im Spielfeld
			c = w->shoot(x,y);    									//Zustand der beschossenen Koordinate abfragen
			res = c +'0';											//Zustand der beschossenen Koordinate für Client verständlich machen
			cout << "Ergebnis: " << res << endl;
			return res;												//Zustand an Client senden
		}
	}

	if (input.compare(0,5,"spiel") == 0){
					w->printBoard();								//Spielfeld ausgeben
					res = "Spielfeld";
					return res;										//Spielefeldausgabe an Client bestätigen
	}

	return string ("Error");										//Rückgabe wenn keine if / else Bedingung erfüllt wid


}


