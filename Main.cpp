#include <iostream>

#include "Flight.h"
#include "Renderer.h"
#include "Table.h"


using namespace std;


int main() {
  cout << endl;


  Flight::load();

  Table flights(Flight::serialize);
  flights.render();

  cout << endl;
  return 0;
}
