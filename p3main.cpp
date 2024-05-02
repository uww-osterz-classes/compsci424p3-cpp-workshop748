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
#include<thread>       // get data from strings better than the C++ way
#include<mutex>
#include<vector>

using namespace std; // if you want to type out "std::" every time, delete this

/*
   If you want your variables and data structures for the banker's
   algorithm to have global scope, declare them here. This may make
   the rest of your program easier to write.

   Most software engineers say global variables are a Bad Idea (and
   they're usually correct!), but systems programmers do it all the
   time, so I'm allowing it here.
*/
int ind = 0;
vector<vector<int>>u;
vector<vector<int>> TheMax;
vector<bool>Finish;
vector<int>work;
vector<int>available;
vector<vector<int>>need;
vector<vector<int>>Allocation;


bool IsSafe(int n)
{
    int flag = 1;
    for (int i = 0; i <n; i++)
    {
        if (work[i] == 0)
        {
            flag = 0;
            //this program is not safe to run
            return false;
        }
    }
    if (flag == 1)
    {
        //safe to run 
        return true;
    }
    return false;//should not happen
}
void bankersAlgorithm(int n, int m)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < m; i++)
        {
            if (work[i] == 0)
            {
                int flag = 1;
                for (int j = 0; j < n; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    Finish[ind++] = i;
                    for (int j = 0; j < m; j++)
                    {
                        available[j] += Allocation[i][j];
                    }
                    work[i] = 1;
                }
            }

        }
    }
}

void request(int n,int m,int units,int resources,int processes)
{
    bankersAlgorithm(processes, resources);
    bool reqBool = IsSafe(n);
    if (reqBool == false)
    {
        cout << "this opperation is unsafe.";
    }
    else {
        if (units <= need[n][m])
        {
            if (units <= available[m])
            {
                available[m] = available[m] - units;
                Allocation[n][m] = Allocation[n][m] + units;
                need[n][m] = need[n][m] - units;
                bankersAlgorithm(processes,resources);
                reqBool = IsSafe(n);
                if (reqBool==false)
                {
                   
                    cout << "this operatingon is unsafe" << endl;
                    //this is the same formula for release
                    available[m] = available[m] + units;
                    Allocation[n][m] = Allocation[n][m] - units;
                    need[n][m] = need[n][m] + units;
                }
            }
            else {
                cout << "this opperation is unsafe";
            }

       }else {
                cout << "There was an error with your request" << endl;
            }
        
    }
    
}
//num_resources, num_processes
void  released(int n, int m, int units, int resources, int processes)
{
    bankersAlgorithm(processes, resources);
    bool reqBool = IsSafe(n);
    if (reqBool == false)
    {
        cout << "this opperation is unsafe.";
    }
    else {
        if (units <= need[n][m])
        {
            if (units <= available[m])
            {
                available[m] = available[m] + units;
                Allocation[n][m] = Allocation[n][m] - units;
                need[n][m] = need[n][m] + units;
                bankersAlgorithm(processes, resources);
                reqBool = IsSafe(n);
                if (reqBool == false)
                {

                    cout << "this operatingon is unsafe" << endl;
                    //this is the same formula for release
                    available[m] = available[m] - units;
                    Allocation[n][m] = Allocation[n][m] + units;
                    need[n][m] = need[n][m] - units;
                }
            }
            else {
                cout << "this opperation is unsafe";
            }

        }
        else {
            cout << "There was an error with your request" << endl;
        }

    }
}

void manualMode(int n, int m)
{
    string asking = "";
    int units=0, Resources=0, process=0;
    char regOrRel[20];
    cout<<" please spesify to request or relase or end"<<endl;
    while (getline(cin, asking))
    {
        if (asking != "end")
        {
            const char* fun = asking.c_str();
           sscanf(fun, "%s %d of %d for %d", regOrRel, &units, &Resources, &process);
            if (string(regOrRel) == "request")
            {
                if (units > 0 && units < TheMax[process][Resources])
                {
                    if (Resources > 0 && Resources < m - 1)
                    {
                        if (process > 0 && process < n - 1)
                        {
                            request(Resources, process, units, m, n);
                        }
                        else {
                            cout << "error";
                            break;
                        }
                    }
                    else {
                        cout << "error";
                        break;
                    }
                }
                else {
                    cout << "error";
                    break;
                }
            }
        }
        else if (string(regOrRel) == "released")
        {
            if (units > 0 && units < Allocation[process][Resources])
            {
                if (Resources > 0 && Resources < m - 1)
                {
                    if (process > 0 && process < n - 1)
                    {
                        released(Resources, process, units, m, n);
                    }
                    else
                    {
                        cout << "error";
                        break;
                    }
                }
                else
                {
                    cout << "error";
                    break;
                }
            }
            else
            {
                cout << "error";
                break;
            }
        }
        else
        {
            break;
        }

    }

}
int randNum()
{

}
void automode(int n, int m)
{


}

/*
  Arguments:
    argc: the number of command-line arguments, which should be >= 2
    argv[0]: the name of the executable file
    argv[1]: a C-string, either "manual" or "auto"
    argv[2]: a C-string containing the name of the setup file (and the
             path to the file, if it's not in the current directory)
*/
int main(int argc, char* argv[]) {
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
    int num_resources=0;
    int num_processes=0;


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
       
        getline(setup_file, line);
        
        getline(setup_file,line);
     
        //>> will grab a sequence of characters and do the right thing with it.
                //declaring the 2-D Array outside and declaring them as NUll
        //this is setting up the Available array        
        
       //should be getting the max
       cout<<line<<endl;
       for(int i = 0; i < num_resources; i++)
        {
            int theNumber;
            setup_file >> theNumber;
            
            available.push_back(theNumber);
            
        }
        for(int i =0;i<available.size();i++)
        {
            cout<<available.at(i)<<" ";
        }
       //this is not printing anything
       getline(setup_file,line);
       
        getline(setup_file,line);
       cout<<endl<<line<<endl;
        //set up the max array
        
       for(int i = 0; i < num_processes; i++)
        {
            vector<int>Temp;
           /** TheMax[i].resize(num_resources);
            Temp.resize(num_resources);*/
            for(int j =0;j<num_resources;j++){
                
                int num;
                setup_file>>num;
                Temp.push_back(num);
               // cout<<Temp[j]<<endl;
            }
            Temp.resize(num_resources);
          //  cout<<endl<<Temp.size()<<endl;
            TheMax.push_back(Temp);
        }
        for (size_t i = 0; i < TheMax.size(); ++i) 
        {
        for (size_t j = 0; j < TheMax[i].size(); ++j) {
            std::cout << TheMax[i][j] << " ";
        }
        std::cout << std::endl;
        }
        getline(setup_file, line);
        //sets up the Allocation array
        getline(setup_file,line);
       cout<<"Allocation"<<endl;
        for(int i = 0; i < num_processes; i++)
        {
            vector<int>Temp;
           
            for(int j =0;j<num_resources;j++){
                
                int num;
                setup_file>>num;
                Temp.push_back(num);
            }
            Temp.resize(num_resources);
          //  cout<<endl<<Temp.size()<<endl;
            Allocation.push_back(Temp);
        }

         for (size_t i = 0; i < Allocation.size(); ++i) {
        for (size_t j = 0; j < Allocation[i].size(); ++j) {
            std::cout << Allocation[i][j] << " ";
        }
        std::cout << std::endl;
         }
       // getline(setup_file,line);
        // 3. Use the rest of the setup file to initialize the data structures
        std::cout<<"End of reading file"<<endl;
        getline(setup_file,line);
        // Done reading the file, so close it
        setup_file.close();
    } 
    // end: if setup_file.is_open()
    cout<<"WORK"<<endl;
        for(int i =0;i<num_resources;i++)
        {
           //cout<<available[i]<<endl;
           // work[i]=available[i];
        work.push_back(available.at(i));
        }
        //work.resize(num_processes);
        //setting up the need fo the program.
       for(int i =0;i<work.size();i++)
       {
        cout<<work[i]<<" ";
       }
       cout<<endl<<"Need"<<endl;
        for (int i = 0; i < num_processes; i++)
        {
            vector<int> temp;
            for (int j = 0; j < num_resources; j++)
            {
               
                int num1 =TheMax.at(i).at(j);
                int num2 =Allocation.at(i).at(j);
                //need[i][j] = TheMax[i][j] - Allocation[i][j];
         
            int num3 = num1-num2;
            cout<<num3<<" "; 
            temp.push_back(num3);
            }
            temp.resize(num_resources);
            need.push_back(temp);
            cout<<endl;
            
        }

         need.resize(num_processes);
    // 4. Check initial conditions to ensure that the system is
    // beginning in a safe state: see "Check initial conditions"
    // in the Program 3 instructions
    for (int k = 0; k < num_processes; k++)
    {
        for (int i = 0; i < num_resources; i++)
        {
            
            if (work[i] == 0)
            {
                int flag = 1;
                for (int j = 0; j < num_processes; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    Finish[ind++] = i;
                    for (int j = 0; j < num_processes; j++)
                    {
                        available[j] += Allocation[i][j];
                    }
                    work[i] = 1;
                }
            }

        }
    }
    int flag = 1;
    bool safeOrNot = IsSafe(num_processes);
    if (safeOrNot == false)
    {
        cout<<"This opperation is unsafe.";
        return -1;
    }

    // 5. Go into either manual or automatic mode, depending on
    // the value of args[0]; you could implement these two modes
    // as separate methods within this class, as separate classes
    // with their own main methods, or as additional code within
    // this main method.
    
    string  mode = argv[1];
    if (mode == "manual" || mode == "Manual")
    {
        manualMode(num_resources, num_processes);
    }
    else if (mode == "auto" || mode == "Auto")
    {
       //enter automode 
    }
    else
    {
        cout << " Invalid node. Please try again by specifying 'manual' or 'automatic'";
        return 1;
    }
    return 0; // terminate normally
}