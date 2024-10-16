#include <iostream>

using namespace std;
int x;
int main() {
  int
    //x,
    data[10],
    *px;
    
  x = 3;
  cout << x << endl;
  
  //px = 17;	// doesn't work, can't assign numbers to pointers

  px = &x;
  
  *px = 17;
  cout << px << endl;
  cout << x << endl;
  
  px = new int;
  
  *px = -12;
  cout << px << endl;
  cout << *px << endl;

  delete px;
  
  px = new int[10];
  
  for (int i=0;i<10;i++)
    px[i] = i;
  
  for (int i=0;i<10;i++) {
    cout << *(px + i) << endl;
    cout << px[i] << endl;
  }
    
  delete[] px;
  
  return 0;
}

