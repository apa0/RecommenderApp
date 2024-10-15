#include "Recommend.h"
#include <iostream>
#include <fstream>
#include <iomanip>

/*
 * RecommendTester 4 tests:
 */

using namespace std;

// case1: test printDotProducts for Kalid with ratings_small.dat
void case1(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Kalid");
	r.printDotProducts("Kalid");
}

// case2: test printDotProducts for Snoosh with ratings_large.dat
void case2(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Snoosh");
	r.printDotProducts("Snoosh");
}

// case3: test printSimilarList for Bob with ratings_small.dat
void case3(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Bob");
	r.printSimilarList("Bob");
}

// case4: test printSimilarList for Reuven with ratings_large.dat
void case4(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Reuven");
	r.printSimilarList("Reuven");
}

// case5: test printSimilarList for Bob with ratings_small.dat
void case5(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Bob");
	r.printSimAvg("Bob");
}

// case6: test printSimilarList for Reuven with ratings_large.dat
void case6(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Reuven");
	r.printSimAvg("Reuven");
}

// case7: test strDotProducts for Kalid with ratings_small.dat
void case7(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Kalid");
	cout << r.strAverages();
}

// case8: test strDotProducts for Snoosh with ratings_large.dat
void case8(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Snoosh");
	cout << r.strAverages();
}

// case9: test printSimilarList for Bob with ratings_small.dat
void case9(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Bob");
	cout << r.strSimilarList();
}

// case10: test strSimilarList for Reuven with ratings_large.dat
void case10(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Reuven");
	cout << r.strSimilarList();
}

// case11: test strSimAvg for Bob with ratings_small.dat
void case11(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Bob");
	cout << r.strSimAvg();
}

// case12: test strSimAvg for Reuven with ratings_large.dat
void case12(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Reuven");
	cout << r.strSimAvg();
}

int main(int argc, char* argv[]){
	int option = 0;

	if (argc!=2){
		cerr << "usage: RecommendTester2 option" << endl;
		exit(0);
	}
	else{
		option = atoi(argv[1]);
	}

	switch (option){
		case 1:
			case1();
			break;
		case 2:
			case2();
			break;
		case 3:
			case3();
			break;
		case 4:
			case4();
			break;
		case 5:
			case5();
			break;
		case 6:
			case6();
			break;
		case 7:
			case7();
			break;
		case 8:
			case8();
			break;
		case 9:
			case9();
			break;
		case 10:
			case10();
			break;
		case 11:
			case11();
			break;
		case 12:
			case12();
			break;

		default:
			cout << "default " << endl;
			break;
	} // end switch

	return 0;

} // end main
