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

// case1: test computeRecommendation for "Kalid" with ratings_small.dat
void case1(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Kalid");
	r.printRecommendation("Kalid");
}

// case2: test computeRecommendation for "Carlos" with ratings_small.dat
void case2(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Carlos");
	r.printRecommendation("Carlos");
}

// case3: test computeRecommendation for "Snoosh" with ratings_large.dat
void case3(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Snoosh");
	r.printRecommendation("Snoosh");
}

// case4: test computeRecommendation for "James" with ratings_large.dat
void case4(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("James");
	r.printRecommendation("James");
}

// case5: test printAverages ratings_small.dat
void case5(){
	Recommend r("ratings_small.dat");
	r.printAverages(); 
}

// case6: test printAverages ratings_large.dat
void case6(){
	Recommend r("ratings_large.dat");
	r.printAverages(); 
}

// case7: test getRecommenderBookRating  for Bob/Animal Farm with ratings_small.dat
void case7(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Bob");
  cout << fixed << setprecision(2) << r.getRecommenderBookRating("Bob", "Animal Farm");
}

// case8: test getRecommenderBookRating  for Ben/Far North with ratings_large.dat
void case8(){
	Recommend r("ratings_large.dat");
	  cout << fixed << setprecision(2) << r.getRecommenderBookRating("Ben", "Far North");
}

// case9: test getBookIndex for Animal Farm on ratings_small.dat
void case9(){
	Recommend r("ratings_small.dat");
	  cout << fixed << setprecision(2) << r.getBookIndex("Animal Farm");
}

// case10: test getBookIndex for Ender's Game on ratings_large.dat
void case10(){
	Recommend r("ratings_large.dat");
	  cout << fixed << setprecision(2) << r.getBookIndex("Ender's Game");
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

		default:
			cout << "default " << endl;
			break;
	} // end switch

	return 0;

} // end main
