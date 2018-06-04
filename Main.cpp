#include <iostream>
#include <string>
#include <typeinfo>

#include "Cmd.h"
#include "Table.h"
#include "Flight.h"
#include "Passanger.h"
#include "Plane.h"

#include "Vector.hpp"


using namespace std;

vector<Flight*> Flight::flights = {};
vector<Passanger*> Passanger::passangers = {};
vector<Plane*> Plane::planes = {};

Table Table::TFlights = Table("Flights", Flight::serialize, Flight::factory);
Table Table::TPassangers = Table("Passangers", Passanger::serialize, Passanger::factory);
Table Table::TPlanes = Table("Planes", Plane::serialize, Plane::factory);

int main() {
  cout << endl << "Type `help` for help." << endl << endl;

  while(true) {
    cout << "$> ";
    string cmd;
    getline(cin, cmd);

    if(cmd.length() == 0) continue;
    if(cmd == "exit") break;
    new Cmd(cmd);
  }

  cout << endl;

  return 0;
}
