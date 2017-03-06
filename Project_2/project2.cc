
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector> //added by student
using namespace std;

int main (int argc, char* argv[])
{
    int task;
    string input;
    //char delimiter('#');
    vector<string> grammar;

    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);

    // TODO: Read the input grammar at this point from standard input
	//NOTE: "standard input" means you don't have to read from a file
	//Read until you hit ##
	
	/*while (getline(cin, input, delimiter) && (input != "##"))
	{
		grammar.push_back(input);
		getline(cin, input, delimiter);
	}*/
	do
	{
		getline(cin, input);
		grammar.push_back(input);
	} while(input != "##");
    /*
       Hint: You can modify and use the lexer from previous project
       to read the input. Note that there are only 4 token types needed
       for reading the input in this project.

       WARNING: You will need to modify lexer.cc and lexer.h to only
       support the tokens needed for this project if you are going to
       use the lexer.
     */

    switch (task) {
        case 1:
            // TODO: perform task 1.
            // For each terminal and non-terminal, deternmine number of grammar rules in which it appears
        cout << "This is task 1\n";
	//cout << "The input is: " << input << "\n"; 
	cout << "This is the grammar:\n";
	for (vector<string>::const_iterator i = grammar.begin(); i != grammar.end(); ++i)
	{
		cout << *i << "\n";
	}
	break;

        case 2:
            // TODO: perform task 2.
            // Determine useless symbols and remove them
            cout << "This is task 2\n";
            break;

        case 3:
            // TODO: perform task 3.
            // Calculate FIRST sets
            cout << "This is task 3\n";
            break;

        case 4:
            // TODO: perform task 4.
            // Calculate FOLLOW sets
            cout << "This is task 4\n";    
	break;

        case 5:
            // TODO: perform task 5.
            // Determine if the grammar has a predictive parser
            cout << "This is task 5\n";
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}

