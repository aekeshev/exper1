/*
 * client.C
 *
 *  Created on: 10.11.2021
 *      Author: Anastasia Ekeshev
 *      		Andre Tabeling
 *      		Jana Plenter
 */

#include <iostream>
#include "SIMPLESOCKET.H"
#include "TASK3.H"

TCPclient c;
	string host = "localhost";
	string start = "start";
	string spiel;
	string shoot;
	char a[] = {"shoot(10,y)"};									// Ausnahme: x = 10
	char b[] = {"shoot(x,10)"};									// Ausnahme y = 10
	char e[] = {"shoot(10,10)"};								// Ausnahme x = 10, y = 10;
	char d[] = {"shoot(x,y)"};									// normale Antwort
	char sp[] = {"spiel"};
	char st[] = {"start"};
	char x;
	char y;
	int res2 = 0;
	int x1 = 0;
	int y1 = 0;
	int j1 = 0; 												//zaehler durchlaeufe auf verschiedene Welten Strategie 1
	int j2 = 0; 												//zaehler durchlaeufe auf verschiedene Welten Strategie 2
	int j3 = 0; 												//zaehler durchlaeufe auf verschiedene Welten Strategie 3
	int j4 = 0; 												//zaehler durchlaeufe auf verschiedene Welten Strategie 4
	int r1 = 0;													//zaehler durchlaeufe pro Welt Strategie 1
	int r2 = 0;													//zaehler durchlaeufe pro Welt Strategie 2
	int r3 = 0;													//zaehler durchlaeufe pro Welt Strategie 3
	int r4 = 0;													//zaehler durchlaeufe pro Welt Strategie 4
	int strat;
	int reci;
	int laps;
	int err;


int strategie1(int laps1){

	j1 = 0;														//Durchlaufzähler Spielwelten auf 0 Setzten

	do{

		start = st;												//Zeichenkette "start"
		c.sendData(start);										//"start" an server Senden
		start = c.receive(25);									//start den die Zeichenkette die der Server sendet übergeben
		r1 = 0;													//Durchlaufzähler Runden auf 0 Setzten

		do{
			spiel= sp; 											// Zeichenkette "Spiel"

			x1 = (rand() % 10) +1;								// Zuweisung von den Werten für die Schusse
			y1 = (rand() % 10) +1;								// Werte zwischen 1 und 10

			if (x1 == 10){											// Ausnahme x = 10
				y = y1 + '0';										// y Wert wird in Zeichen umgewandelt und
				a[9] = y;											// y Wert wird in die Zeichenkette "shoot(10,y)" gefügt
				shoot = a;											// Zuweisung des Schusses
			}
			if (y1 == 10){											// Ausnahme y = 10, ähnlich wie bei x = 10

				x = x1 + '0';
				b[6] = x;
				shoot = b;
			}
			if ((x1 == 10) && (y1 == 10)){							//Ausnahme y=10 und x=10
				shoot = e;
			}
			if((x1<10)&&(y1<10)){
				x = x1 + '0';
				y = y1 + '0';
				d[6] = x;											// Einbringung der y und x Werte in die Zeichenkette shoot(x,y)
				d[8] = y;
				shoot = d;
			}
			r1++;													// Zählung der Spielzüge
			c.sendData(shoot);										// client sendet den Schuss
			shoot = c.receive(25);  								// Antwort von dem Server (shoot = 1, 2, 3 oder 4
			c.sendData(spiel); 										// client fragt das Spielfeld ab
			spiel = c.receive(25); 									// server sendet das SPi





			}while(shoot!="4");											//Die do while Schleife wird solange durchlaufen bis der Server da zeichen "4" Sendet
																		//"4" Steht für Game Over und beduetet das alle Schiffe Zerstört sind
		j1++;															//Zählt wie viele Verschiedene Welten Durchgspielt werden
		cout << "Strategie 1 Anzahl Durchlaeufe " << r1 << endl;

	}while(j1<laps1);													//Die do while Shleife wird solange durchlaufen bis die anzahl an verschiedenen Welteen durchgespielt ist

	string msg = "BYEBYE";												//Server Mitteilen das das Spiel vorbei ist
	c.sendData(msg);
	msg = c.receive(25);

	return r1;															//rückabe der Rundenzahl
}

int strategie2(int laps2){
	j2 = 0;																//Durchlaufzähler Spielwelten auf 0 Setzten

	do{
		start = st;														//start die Zeichenkette "start" übergeben
		c.sendData(start);												//Zeichenkette an server senden
		start = c.receive(25);											//start den die Zeichenkette die der Server sendet übergeben
		r2 = 0;															//Durchlaufzähler Runden auf 0 Setzten

		int Feld [10][10] = {0};										// Feld Initialisieren

		do{

			x1 = ((rand() % 10)) ;  									// Werte für die Schuesse zwischen 0 und 9, da das angelegte Feld bei [0][0] anfängt
			y1 = ((rand() % 10)) ;
			spiel= sp;													// spiel die Zeichenkette "spiel" übergeben

			if (Feld[x1][y1] != 1){										// Prüft ob das Feld bereits belegt ist


				Feld[x1][y1] = 1; 										// Feld Belegt setzten
				x1 = x1 + 1;											// +1, um die Koordinaten für den Server verständlich zu machen.
				y1 = y1 + 1;

				if ((x1 == 10) && (y1 == 10)){							// Sonderfall x = 10 und y =10;
					shoot = e;											// shoot die Zeichekette "shoot(10,10) übergeben
				}

				if ((x1 == 10)&&(y1 !=10)){								// Sonderfall x = 10
					y = y1 + '0';										// y1 durch +'0' für den server verständlich machen und an y übergeben
					a[9] = y;											// das zehnte Zeichen in a durch das an y zuvor übergeben Zeichen ersetzten
					shoot = a;											// shoot die Zeichekette "shoot(10,y)" übergeben
				}

				if ((y1 == 10)&&(x1 !=10)){
					x = x1 + '0';										// x1 durch +'0' für den server verständlich machen und an x übergeben
					b[6] = x;											// das siebte Zeichen in b durch das an x zuvor übergeben Zeichen ersetzten
					shoot = b;											// shoot die Zeichekette "shoot(x,10)" übergeben
				}

				if ((x1<10)&&(y1<10)){
					x = x1 + '0';										// y1 durch +'0' für den server verständlich machen und an y übergeben
					y = y1 + '0';										// y1 durch +'0' für den server verständlich machen und an y übergeben
					d[6] = x;											// das siebte Zeichen in d durch das an x zuvor übergeben Zeichen ersetzten
					d[8] = y;											// das neunte Zeichen in d durch das an y zuvor übergeben Zeichen ersetzten
					shoot = d;											// shoot die Zeichekette "shoot(x,y)" übergeben
				}
				r2++;
				c.sendData(shoot);										//Koordinaten an Server Senden
				shoot = c.receive(25);									//Resultat des Schusses von Server zurück bekommen
				c.sendData(spiel);										//Befehl zur ausgabe des Spielfelds
				spiel = c.receive(25);									//Bestätigung der Ausgabe des Spielfelds
																		//Der Schuss wird erst gezählt wenn der Server Geatwortet hat

			}



		}while(shoot!="4");												//Die do while Schleife wird solange durchlaufen bis der Server da zeichen "4" Sendet
																		//"4" Steht für Game Over und beduetet das alle Schiffe Zerstört sind
		j2++;															//Zählt wie viele Verschiedene Welten Durchgspielt werden
		cout << "strategie 2 Durchlauefe: " << r2 << endl;


	}while(j2<laps2);													//Die do while Shleife wird solange durchlaufen bis die anzahl an verschiedenen Welteen durchgespielt ist

	string msg = "BYEBYE";												//Server Mitteilen das das Spiel vorbei ist
	c.sendData(msg);
	msg = c.receive(25);
	return r2;															//rückabe der Rundenzahl
}


int strategie3(int laps3){
	j3 = 0;																//Durchlaufzähler Spielwelten auf 0 Setzten

	do{
		shoot = "0";    												// Um Startfehler zu vermeiden wird shoot "0" gesetzt
		start = st;														//start die Zeichenkette "start" übergeben
		c.sendData(start);												//Zeichenkette an server senden
		start = c.receive(25);											//start den die Zeichenkette die der Server sendet übergeben
		r3 = 0;															//Durchlaufzähler Runden auf 0 Setzte

		int Feld [10][10] = {0};

		for(int k = 0; k<10; k++) {    									 // in dieser strategie wird von Linkls nach Recht jedes Feld nacheinander Zeilenweise Abgeschossen

			for( int l=0; l<10; l++) {
				if (shoot != "4"){
				spiel= sp;

				x1 = k;  												// Werte für die Schusse zwischen 0 und 9. Ohne +1, weil das angelegte Feld bei [0][0] anfängt
				y1 = l;

					if (Feld[x1][y1] == 0){	 							// Prüft ob das Feld frei ist
						Feld[x1][y1] = 1;								// Feld ist besetzt
						x1 = x1 + 1;									// +1, um die Koordinaten für den Schuss senden zu können
						y1 = y1 + 1;

						if ((y1 == 10)&&(x1 !=10)){
							x = x1 + '0';								// x1 durch +'0' für den server verständlich machen und an x übergeben
							b[6] = x;									// das siebte Zeichen in b durch das an x zuvor übergeben Zeichen ersetzten
							shoot = b;									// shoot die Zeichekette "shoot(x,10)" übergeben
						}

						if ((x1 == 10)&&(y1 !=10)){						// Sonderfall x = 10
							y = y1 + '0';								// y1 durch +'0' für den server verständlich machen und an y übergeben
							a[9] = y;									// das zehnte Zeichen in a durch das an y zuvor übergeben Zeichen ersetzten
							shoot = a;									// shoot die Zeichekette "shoot(10,y)" übergeben
						}

						if ((x1 == 10) && (y1 == 10)){					// Sonderfall x = 10 und y =10;
							shoot = e;									// shoot die Zeichekette "shoot(10,10) übergeben
						}

						if ((x1<10)&&(y1<10)){
							x = x1 + '0';								// y1 durch +'0' für den server verständlich machen und an y übergeben
							y = y1 + '0';								// y1 durch +'0' für den server verständlich machen und an y übergeben
							d[6] = x;									// das siebte Zeichen in d durch das an x zuvor übergeben Zeichen ersetzten
							d[8] = y;									// das neunte Zeichen in d durch das an y zuvor übergeben Zeichen ersetzten
							shoot = d;									// shoot die Zeichekette "shoot(x,y)" übergeben
						}
					}

					r3++;

					c.sendData(shoot);									//Koordinaten an Server Senden
					shoot = c.receive(25);								//Resultat des Schusses von Server zurück bekommen
					c.sendData(spiel);									//Befehl zur ausgabe des Spielfelds
					spiel = c.receive(25);								//Bestätigung der Ausgabe des Spielfelds
																		//Der Schuss wird erst gezählt wenn der Server Geatwortet hat
				}
			}
		}

		j3++;															//Zählt wie viele Verschiedene Welten Durchgspielt werden
		cout<< "Strategie 3 Anzahl Durchlaeufe " << r3<< endl;



	}while(j3<laps3);													//Die do while Shleife wird solange durchlaufen bis die anzahl an verschiedenen Welteen durchgespielt ist

	string msg = "BYEBYE";												//Server Mitteilen das das Spiel vorbei ist
	c.sendData(msg);
	msg = c.receive(25);
	return r3;															//rückabe der Rundenzahl
}


int strategie4(int laps4){
	j4 = 0;																//Durchlaufzähler Spielwelten auf 0 Setzten

	do{
		shoot = "0";    												// Um Startfehler zu vermeiden wird shoot "0" gesetzt
		start = st;														//start die Zeichenkette "start" übergeben
		c.sendData(start);												//Zeichenkette an server senden
		start = c.receive(25);											//start den die Zeichenkette die der Server sendet übergeben
		r4 = 0;															//Durchlaufzähler Runden auf 0 Setzte


		int Feld [10][10] = {0};

		for(int k = 0; k<10; k++) {              						// in dieser strategie wird von oben nach unten jedes Feld Spaltenweise Beschossen
			for( int l=0; l<10; l++) {
				if (shoot != "4"){
					spiel= sp;

					x1 = l;  											// Werte für die Schusse zwischen 0 und 9. Ohne +1, da das angelegte Feld bei [0][0] anfängt
					y1 = k;

					if (Feld[x1][y1] == 0){	 							// Prüft ob das Feld frei ist
						Feld[x1][y1] = 1;								// Feld ist besetzt
						x1 = x1 + 1;									// +1, um die Koordinaten für den Schuss senden zu können
						y1 = y1 + 1;


						if ((y1 == 10)&&(x1 !=10)){
							x = x1 + '0';								// x1 durch +'0' für den server verständlich machen und an x übergeben
							b[6] = x;									// das siebte Zeichen in b durch das an x zuvor übergeben Zeichen ersetzten
							shoot = b;									// shoot die Zeichekette "shoot(x,10)" übergeben
						}

						if ((x1 == 10)&&(y1 !=10)){						// Sonderfall x = 10
							y = y1 + '0';								// y1 durch +'0' für den server verständlich machen und an y übergeben
							a[9] = y;									// das zehnte Zeichen in a durch das an y zuvor übergeben Zeichen ersetzten
							shoot = a;									// shoot die Zeichekette "shoot(10,y)" übergeben
						}

						if ((x1 == 10) && (y1 == 10)){					// Sonderfall x = 10 und y =10;
							shoot = e;									// shoot die Zeichekette "shoot(10,10) übergeben
						}

						if ((x1<10)&&(y1<10)){
							x = x1 + '0';								// y1 durch +'0' für den server verständlich machen und an y übergeben
							y = y1 + '0';								// y1 durch +'0' für den server verständlich machen und an y übergeben
							d[6] = x;									// das siebte Zeichen in d durch das an x zuvor übergeben Zeichen ersetzten
							d[8] = y;									// das neunte Zeichen in d durch das an y zuvor übergeben Zeichen ersetzten
							shoot = d;									// shoot die Zeichekette "shoot(x,y)" übergeben
						}
					}

					r4++;

					c.sendData(shoot);									//Koordinaten an Server Senden
					shoot = c.receive(25);								//Resultat des Schusses von Server zurück bekommen
					c.sendData(spiel);									//Befehl zur ausgabe des Spielfelds
					spiel = c.receive(25);								//Bestätigung der Ausgabe des Spielfelds
																		//Der Schuss wird erst gezählt wenn der Server Geatwortet hat
				}
			}
		}


		j4++;
		cout<< "Strategie 4 Anzahl Durchlaeufe " << r4 << endl;

	}while(j4<laps4);													//Die do while Shleife wird solange durchlaufen bis die anzahl an verschiedenen Welteen durchgespielt ist

	string msg = "BYEBYE";												//Server Mitteilen das das Spiel vorbei ist
	c.sendData(msg);
	msg = c.receive(25);

		return r4;														//rückabe der Rundenzahl
}


int main(int argc, char * argv[]) {
	srand(time(NULL));
	c.conn(host , 2022);												//connect to host

	if(argc!=3){														//Prüft ob mehr maximal 2 Kommandozeilenparameter gegebn sind
		cout <<"Fehlende oder zu viele Kommandozeilenparameter" << endl;
		return 0;
	}

	sscanf(argv[1],"%i",&strat);										//Liest ein Welche Strategie gewählt wird
	sscanf(argv[2],"%i",&laps);											//Liest ein wie viele runden gespielt werden sollen

	cout << "Strategie: " << strat << " Runden: " << laps << endl;		//gibt das resultat aus

	switch (strat){														//Wählt die eingegeben Strategie

		case 1:
			strategie1(laps);											//Ruft startegie auf und übergibt die Rundenzahl
			break;
		case 2:
			strategie2(laps);											//Ruft startegie auf und übergibt die Rundenzahl
			break;
		case 3:
			strategie3(laps);											//Ruft startegie auf und übergibt die Rundenzahl
			break;
		case 4:
			strategie4(laps);											//Ruft startegie auf und übergibt die Rundenzahl
			break;
		default :														//Wird bei fehlerhafter eingabe ausgeführt
			cout <<"Problem bei der Eingabe"<< endl;

	}

}
