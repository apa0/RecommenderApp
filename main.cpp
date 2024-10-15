//Angie Diaz 
//CPSC 1020
//Project 4: Reccomendation System App
//File: main.cpp
//4/20/24
//Time: ~25 hours
//Desc: Main program that is menu based and outputs when prompted by the user different things depending on the commands

#include "Recommend.h"
using namespace std; 

int main(int argc, char* argv[]) {

    //input validation for command line
    if (argc!=2) {
        cerr<<"Incorrect number of arguments. Exiting.";
        exit(0);
    }
    
    //instantiating Reccomend object based on file sent
    Recommend program_user(argv[1]);
    string command, requested_user; 
   
    do {
        //waiting for user to enter command to start program 
        getline(cin, command);
        if (command=="averages") {
            //calling function to compute bookavgs
            cout<<endl;
            program_user.printAverages(); 

        } else if (command=="books") {
            cout<<endl; 
            program_user.printBooks(); 

        } else if (command=="debug") {
            DEBUG=!DEBUG; 

        } else if (command=="dotprod") {
            if (program_user.checkRecommender(requested_user)) {
                program_user.printDotProducts(requested_user);
            } else {
                cout<<"Invalid dot prod recommender requested. Try again.\n";
            }
            

        }else if (command=="file") {
            program_user.printFancyRatings(); 

        } else if (command=="menu") {
            cout<<endl<<endl;
            cout<<"BOOK RECOMMENDATION SYSTEM MENU"<<endl;
            cout<<"==============================="<<endl;
            cout<<"averages - display average ratings for each book"<<endl;
            cout<<"books - display books in alphabetical order"<<endl;
            cout<<"debug - toggles debugging outputs"<<endl;
            cout<<"dotprod - display current dot products"<<endl;
            cout<<"file - fancy display of file data "<<endl;
            cout<<"menu - display this menu"<<endl;
            cout<<"names - display recommender names"<<endl;
            cout<<"ratings - display recommender rating"<<endl;
            cout<<"recommend <name> - display book recommendations based upon recommender <name>"<<endl;
            cout<<"sim - display current similarities"<<endl;
            cout<<"simavg - display averages for current similarities"<<endl;
            cout<<"quit - exits the program"<<endl; 
            cout<<endl;

        } else if (command=="names") {
            cout<<endl;
            program_user.printNames(); 

        } else if (command.find("recommend ")==0) {
            //taking the name person has requested and entering it into variable
            requested_user=command.substr(10);
            //making sure requested name exists in file before trying to compute rec
            if (program_user.checkRecommender(requested_user)) {
                program_user.computeRecommendation(requested_user);
                //printing out recommendation
                program_user.printRecommendation(requested_user);
            } else {
                cout<<"Invalid name, try again.";
            }
            
        } else if (command=="sim") {
            program_user.printSimilarList(requested_user); 

        } else if (command=="simavg") { 
            program_user.printSimAvg(requested_user);
        } else if(command=="ratings") {
            program_user.printRecommendationRatings();
        }
    } while (command!="quit");





    return 0;

}