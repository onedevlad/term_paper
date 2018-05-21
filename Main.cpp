#include <iostream>

#include "Cmd.h"
#include "Flight.h"
#include "Passanger.h"
#include "Plane.h"
#include "Renderer.h"
#include "Table.h"


using namespace std;

Table Table::TFlights = Table(Flight::serialize);
Table Table::TPassangers = Table(Passanger::serialize);
Table Table::TPlanes = Table(Plane::serialize);

int main() {
  cout << endl;

  cout << "Type `help` for help." << endl << endl;

  Flight::load();
  Passanger::load();
  Plane::load();

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
