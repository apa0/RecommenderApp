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

// case1: test getBookAverage/Kalid/Cats with ratings_small.dat
void case1(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Kalid");
  cout << fixed << setprecision(2) << r.getBookAverage("Cats") << endl;
}

// case2: test getBookAverage/Kalid/Harry Potter with ratings_small.dat
void case2(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Kalid");
  cout << fixed << setprecision(2) << r.getBookAverage("Harry Potter") << endl;
}

// case3: test getBookAverage/Suelyn/Harry Potter with ratings_small.dat
void case3(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Suelyn");
  cout << fixed << setprecision(2) << r.getBookAverage("Harry Potter") << endl;
}

// case4: test getBookAverage/Suelyn/Cats with ratings_small.dat
void case4(){
	Recommend r("ratings_small.dat");
	r.computeRecommendation("Suelyn");
  cout << fixed << setprecision(2) << r.getBookAverage("Cats") << endl;
}

// case5: test getBookAverage/Andrew/Speak with ratings_large.dat
void case5(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Andrew");
  cout << fixed << setprecision(2) << r.getBookAverage("Speak") << endl;
}

// case6: test getBookAverage/Andrew/Life of Pi with ratings_large.dat
void case6(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Andrew");
  cout << fixed << setprecision(2) << r.getBookAverage("Life of Pi") << endl;
}

// case7: test getBookAverage/Nathan/Life of Pi with ratings_large.dat
void case7(){
	Recommend r("ratings_large.dat");
	r.computeRecommendation("Nathan");
  cout << fixed << setprecision(2) << r.getBookAverage("Life of Pi") << endl;
}

// case8: test checkRecommender
void case8(){
	Recommend r("ratings_small.dat");
  cout << r.checkRecommender("XXX") << "/" << r.checkRecommender("Bob") << endl;
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
		default:
			cout << "default " << endl;
			break;
	} // end switch

	return 0;

} // end main