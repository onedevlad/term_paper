#include <iostream>
#include <vector>
#include <string>

#include "Table.h"
#include "Flight.h"
#include "Plane.h"
#include "Passanger.h"
#include "Cmd.h"

using namespace std;


Table Table::TFlights = Table(Flight::serialize);
Table Table::TPlanes = Table(Plane::serialize);
Table Table::TPassangers = Table(Passanger::serialize);

int main() {
  cout << endl;

  cout << "Type `help` for help." << endl << endl;

  // Flight::load();
  // Plane::load();
  // Passanger::load();

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
