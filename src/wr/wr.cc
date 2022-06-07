#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  if (!argc) {
    cout << "usage: worms_wr <filename>" << endl;
    return 1;
  }
  string name(argv[1]);
  // Create a text string, which is used to output the text file
  string myText;

  // Read from the text file
  ifstream MyReadFile(name);

  // Use a while loop together with the getline() function to read the file line
  // by line
  while (getline(MyReadFile, myText)) {
    // Output the text from the file
    cout << myText << endl;
  }

  // Close the file
  MyReadFile.close();
}
