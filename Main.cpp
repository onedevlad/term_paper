#include <iostream>

#include "Cmd.h"
#include "ExpressionBuilder.h"
#include "Flight.h"
#include "Passanger.h"
#include "Plane.h"
#include "Renderer.h"
#include "Utils.h"
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

  // vector<string> substitutions;
  // substitutions.push_back("BC9292929");
  // substitutions.push_back("Vlad");
  // substitutions.push_back("Trishch");
  // substitutions.push_back("SKT9903");
//
  // ExpressionBuilder expression = ExpressionBuilder(substitutions);
//
  // bool result = expression.parse("javascript ~ avasc");
  // cout << "Final: " << result << endl;


  cout << "Type `help` for help." << endl << endl;

  while(true) {
    cout << "$> ";
    string cmd;
    getline(cin, cmd);

    if(cmd.length() == 0) continue;
    if(cmd == "exit") break;
    Cmd::handler(cmd);
  }

  cout << endl;
  return 0;
}
