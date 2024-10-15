#include "Recommend.h"
#include <iostream>
#include <fstream>
#include <iomanip>

/*
 * RecommendTester 1 tests:
 * 	- string constructor
 * 	- getBookCount
 * 	- getRecommenderCount
 */

using namespace std;

// case1: test string constructor with ratings_small.dat
void case1(){
	Recommend r("ratings_small.dat");
  cout << r.getBookCount() << endl;
}

// case2: test string constructor with ratings_large.dat
void case2(){
	Recommend r("ratings_large.dat");
	cout << r.getBookCount() << endl;
}

// case3: test printNames with ratings_small.dat
void case3(){
	Recommend r("ratings_small.dat");
	r.printNames();
}

// case4: test printNames with ratings_large.dat
void case4(){
	Recommend r("ratings_large.dat");
	r.printNames();
}

// case5: test printBooks with ratings_small.dat
void case5(){
	Recommend r("ratings_small.dat");
  r.printBooks();
}

// case6: test printBooks with ratings_large.dat
void case6(){
	Recommend r("ratings_large.dat");
  r.printBooks();
}


// case7: test printRecommendationRatings with ratings_small.dat
void case7(){
	Recommend r("ratings_small.dat");
	r.printRecommendationRatings();
}

// case8: test printRecommendationRatings with ratings_large.dat
void case8(){
	Recommend r("ratings_large.dat");
	r.printRecommendationRatings();
}

// case9: test printFancyRatings with ratings_small.dat
void case9(){
	Recommend r("ratings_small.dat");
	r.printFancyRatings();
}

// case10: test printFancyRatings with ratings_large.dat
void case10(){
	Recommend r("ratings_large.dat");
	r.printFancyRatings();
}
// case11: testGetBookCount on ratings_large.dat
void case11(){
	Recommend r("ratings_small.dat");  //BOTH CALLING LARGE.DAT
	cout << r.getRecommenderCount() << endl;
}

// case12: testGetBookCount on ratings_large.dat
void case12(){
	Recommend r("ratings_large.dat");
	cout << r.getRecommenderCount() << endl;
}

int main(int argc, char* argv[]){
	int option = 0;

	if (argc!=2){
		cerr << "usage: RecommendTester1 option" << endl;
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
