#include "Recommend.h"
using namespace std; 

int main(int argc, char* argv[]) {

    //input validation for command line
    if (argc!=2) {
        cerr<<"Incorrect number of arguments. Exiting.";
        exit(0);
    }

     Recommend program_user(argv[1]);

     
     program_user.computeRecommendation("Carlos");
     program_user.printSimilarList("Carlos");
     program_user.printSimAvg("Carlos");
     program_user.printRecommendation("Carlos");

     program_user.computeRecommendation("Bob");
     program_user.printRecommendation("Bob");
     program_user.printRecommendationRatings();

    





    return 0;
}