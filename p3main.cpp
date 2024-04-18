/* COMPSCI 424 Program 3
   Name:
   
   p3main.cpp: contains the main function for this program.

   This is a template. Feel free to edit any of these files, even
   these pre-written comments or my provided code. You can add any
   classes, methods, and data structures that you need to solve the
   problem and display your solution in the correct format.
*/

// You will probably need to add more #include directives.
// Remember: use <angle brackets> for standard C++ headers/libraries
// and "double quotes" for headers in the same directory as this file.
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // for sscanf because Dr. Oster likes the C way to
                  // get data from strings better than the C++ way
#include<vector>
#include<sstream>
using namespace std; // if you want to type out "std::" every time, delete this

/*
   If you want your variables and data structures for the banker's
   algorithm to have global scope, declare them here. This may make
   the rest of your program easier to write. 
   
   Most software engineers say global variables are a Bad Idea (and 
   they're usually correct!), but systems programmers do it all the
   time, so I'm allowing it here.
*/


/*
  Arguments:
    argc: the number of command-line arguments, which should be >= 2
    argv[0]: the name of the executable file
    argv[1]: a C-string, either "manual" or "auto"
    argv[2]: a C-string containing the name of the setup file (and the
             path to the file, if it's not in the current directory)
*/
int main (int argc, char *argv[]) {
    // To help you get started, the major steps for the main program
    // are shown here as comments. Feel free to add more comments to
    // help you understand your code, or for any reason. Also feel free
    // to edit this comment to be more helpful.

    // Code to test command-line processing. You can keep, modify, or
    // remove this code. It's not required.
    if (argc < 2) {
        cerr << argc << " command-line arguments provided, 2 expected; exiting." << endl;
        if (argc == 1) cerr << "argv[1] == " << argv[1] << endl;
        return 1; // non-zero return value indicates abnormal termination
    }

    cout << "Selected mode: " << argv[1] << endl;
    cout << "Setup file location: " << argv[2] << endl;

    // 1. Open the setup file using the path in argv[2]
    ifstream setup_file;
    string line;
    int num_resources;
    int num_processes;
    
    setup_file.open(argv[2], ios::in);
    if (setup_file.is_open()) {
        // 2. Get the number of resources and processes from the setup
        // file, and use this info to create the Banker's Algorithm
        // data structures
        setup_file >> num_resources;
        cout << num_resources << " resources" << endl;

        getline(setup_file, line); // skips the rest of the "resources" line
        
        setup_file >> num_processes;
        cout << num_processes << " processes" << endl;
        
        getline(setup_file, line); // skips the rest of the "processes" line
// I am currebtly unaware of the size of the incoming text file and I will be using a 2-D Vector to solve this problem
       
        int alloc [num_processes][num_resources];
        int max [num_processes][num_resources];
        
        cout<<"avaliable"<<endl;
        int avail[num_processes];
        getline(setup_file,line);
        while(line != "Max" )
        {
            getline(setup_file,line);
            istringstream iss(line);
             if(line == "Max")
            {
                break;
            }
        }
        cout<<"Max"<<endl;
        // Create the Banker's Algorithm data structures, in any
        // way you like as long as they have the correct size
        // (unfortunately, you might not be able to use sscanf for this...)
        getline(setup_file,line);
        while(line != "Allocation")
        {// ask if there is an easier way
            getline(setup_file,line);
            istringstream iss(line);
            //check if the line reads alocate
            if(line == "Allocation")
            {
                break;
            }
        }

        cout<<"Allocation"<<endl;
        getline(setup_file,line);
        while(!getline(setup_file,line))
        {
            getline(setup_file,line);
            istringstream iss (line);
        }
        // 3. Use the rest of the setup file to initialize the data structures


        // Done reading the file, so close it
        setup_file.close();
    } // end: if setup_file.is_open()

    // 4. Check initial conditions to ensure that the system is
    // beginning in a safe state: see "Check initial conditions"
    // in the Program 3 instructions

    // 5. Go into either manual or automatic mode, depending on
    // the value of args[0]; you could implement these two modes
    // as separate methods within this class, as separate classes
    // with their own main methods, or as additional code within
    // this main method.

    
    return 0; // terminate normally
}