#include <iostream>

#include "Cmd.h"
#include "Flight.h"
#include "Passanger.h"
#include "Plane.h"
#include "Renderer.h"
#include "Table.h"


using namespace std;

Table Table::TFlights = Table("Flights", Flight::serialize);
Table Table::TPassangers = Table("Passangers", Passanger::serialize);
Table Table::TPlanes = Table("Planes", Plane::serialize);

int main() {
  cout << endl;

  Flight::load();
  Passanger::load();
  Plane::load();

  cout << "Type `help` for help." << endl << endl;

  while(true) {
    cout << "$> ";
    string cmd;
    getline(cin, cmd);

    cout << endl;
    if(cmd == "exit") break;
    Cmd::handler(cmd);
    cout << endl;
  }

  cout << endl;
  return 0;
}
