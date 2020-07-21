//ofstream: Stream class to write on files
//ifstream: Stream class to read from files
//fstream:Stream class to both read and write from/to files.

//Importing the required libraries for the program
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include "md5.h"
#include<string>
#include <ctime>


using namespace std;

	//This function counts the total number of lines from input file
	int getNumOfLines(string filename){
			
	int number_of_lines = 0;
    string line;
    ifstream myfile(filename);

    while (getline(myfile, line))
        number_of_lines++;
	myfile.close();
	return number_of_lines;
	}
	
	// Two constant integers are defined to hold the number of lines which will later be used to define 2D array
	string PASSWORDFILE = "passwordFile.txt";
	const int TOTALDATA = getNumOfLines(PASSWORDFILE);
	const int FIELD = 3;
	
	// This function asks for username and password from user 
	//and stores them in a file along with randomly generated salt value and generated hash code
	// For Example: username salt hash
	void adduser(){
	string username;
	string password;
	string hash;
	ofstream file;
		
		int flag=1;
		file.open("passwordFile.txt", std::ios_base::app | std::ios_base::out);
	// do-while loop is used to let user add username and passwords as many times as they want
	do{
	cout<<"please enter your username: "<<endl;
	cin >> username;
	cout<<"please enter your password: "<<endl;
	cin >> password;
	
	//generating random 4 digit salt value
	//salt value is unique for every run and every user
	srand (time(NULL));
	string salt = to_string(1000 + rand () % 9000);
	
	hash = md5(salt + password);
	
	file << username << " " << salt << " " << hash << "\n" << endl;
	
	cout << "Do you want to enter more data? 1-Yes, 0-No" <<endl;
	cin>> flag;
	
	} while(flag!=0);
	file.close();
	}
						

	// This functions reads every value from password file and stores them in a 2D array 
	// User input is then checked with the element from array to verify a valid user
	void verifypwd(){
		
	string data[TOTALDATA][FIELD]; // 2d array to store all data from file
	ifstream fin("passwordFile.txt");
	for ( int i = 0; i <TOTALDATA ; i++ )
  {
    for ( int j = 0; j < FIELD; j++ )
    { 
      fin >> data[i][j];
    }
  }

  		string usern;
		string pwd;
		cout << "Please Enter Your Username: " <<endl;
		cin >> usern;
		cout << "Please Enter Your password: " <<endl;
		cin >> pwd;
		
		bool found = false;
		int i;
	for (i = 0; i<TOTALDATA; i++){
			if(data[i][0] == usern){
				found = true;
				break;
			}
		}
			if (found){
				string saltvalue = data[i][1];
				string checkhash = md5(saltvalue + pwd);
				if (checkhash == data[i][2]){
					cout<< "Valid login Credintial. Login Success..." <<endl;
				}else{
					cout << "Either Username or Password is Invalid." <<endl;
				}
			}else{
					cout << "Either Username or Password is Invalid." <<endl;
				}
		
	}
	
	
	// This function performs attack on provided username
	// First check if username exists on passwordfile then perform attack based on user selected Rainbow Table
	// If matching hash is found in rainbow table, password is cracked and displayed
	void attack(){
		
		string username;
		cout << "Welcome to Rainbow Table Attack." << endl;
		cout << "Please Enter a Username to perform attack:" <<endl;
		cin >> username;
		
	string data[TOTALDATA][FIELD]; // 2d array to store all data from file
	ifstream fin("passwordFile.txt");
	for ( int i = 0; i <TOTALDATA ; i++ )
  	{
    	for ( int j = 0; j < FIELD; j++ )
    	{ 
      	fin >> data[i][j];
    	}
  	}
  	
  	bool found = false;
  	int i;
  	string hash;
  	for (i = 0; i<TOTALDATA; i++){
			if(data[i][0] == username){
				found = true;
				hash = data[i][2];
				break;
			}
		}
		if(found){
			int select;
			cout << "Username Found!!! \n";
			cout << "Attack can be performed. Please select a Rainbow Table to peform attack: (1-3)" <<endl;
			cout << "1. Short Words Rainbow Table" << endl;
			cout << "2. Medium Words Rainbow Table" << endl;
			cout << "3. Long Words Rainbow Table" << endl;
			cin >> select;
			string RainbowFile;
				if (select == 1){
					RainbowFile = "ShortWordsRainbow.txt";
				}else if (select == 2){
					RainbowFile = "MediumWordsRainbow.txt";
				}else if (select == 3){
					RainbowFile = "LongWordsRainbow.txt";
				}else{
					cout << "Invalid Input. Closing the Attack." << endl;
				}
				
				cout << "Table Chosen. Starting Attack..." << endl;
				
				ifstream infile(RainbowFile);
				string filehash, filesalt;
				bool flag = false;
				string cracked;
				// clock function is used to compute the execution time of the attack
				int start_s=clock();
				while (infile >> filehash >> filesalt){
					if (filehash == hash){
						cracked = filesalt.erase(0, 4);						
						flag = true;
						break;
					}
				}
				
				if(flag){
					cout << "Matching hash Found. PASSWORD HAS BEEN CRACKED!!." << endl;
					cout << "PASSWORD IS: " << cracked << "\n" << endl;
					
				}else{
					cout << "Hash not found on the table." << endl;
				}
				int stop_s=clock();
				cout << "Time Taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << " Seconds \n"<< endl;
			
		}else{
			cout << "Invalid username. Username not found in database." <<endl;
		}
		
	}
		
	
	// Since the program is menu driven, this functions displays the menu and performs
	//actions based on user input
	void menu(){
		int choice;
		cout << "####################################################################" <<endl;
		cout << "Welcome to UNIX password Implementation System" <<endl;
		cout << "Please select what would you like to do today" <<endl;
		cout << "Press 1 to perform Task 1 : Adding a new user" <<endl;
		cout << "Press 2 to perform Task 2 : Verifying password" <<endl;
		cout << "Press 3 to perform Task 3 : Peform Rainbow table attack" <<endl;
		cout << "Press 0 to Quit the program" <<endl;
		cout << "####################################################################" <<endl;
		cin >> choice;
		if (choice == 0){
			exit(0);
		}else if (choice ==1){
			adduser();
			menu();
		}else if (choice ==2){
			verifypwd();
			menu();
		}else if (choice ==3){
			attack();
			menu();
		}else{
			cout << "Invalid Input. Please select between 0-4. Enter Again:"<<endl;
			menu();
		}
	}
	
	//Main function only calls for menu and exits when everything is processed
	int main(){
	
		menu();
	
	return 0;	

	}
	
