#include "Header.h"
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]) {
  cout << "Input file is " << argv[1] << "\n";
  ifstream inFile(argv[1], ios::in);
  if ( !inFile ) {
    cerr << "File could not be opened: " << argv[1] << "\n";
  }
  char *tokenPtr;
  char *fileName;

  tokenPtr = strtok( argv[1], "/");
  while (tokenPtr != NULL ) {
    fileName = tokenPtr;
    //  cout << fileName << endl;
    tokenPtr = strtok(NULL, "/");
  }
  
  char iName[5];

  iName[0] = fileName[0];
  iName[1] = fileName[1];
  iName[2] = fileName[2];
  iName[3] = fileName[3];
  iName[4] = '\0';

  //  cout << "Final iName: "<< fileName << endl;
  
  Header head(&inFile, iName);

  
  return 0;

}