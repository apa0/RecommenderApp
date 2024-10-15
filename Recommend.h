//Angie Diaz 
//CPSC 1020
//Project 4: Reccomendation System App
//File: Reccomendation.cpp
//4/20/24
//Time: ~25 hours
//Desc: header file for project 4: Recommendation System App

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <utility> 
#include <iterator>
using namespace std;

/*=======================================================================
 use DEBUG to help you place lots of debugging cout statements and be able to turn them all off and back on as needed
 =======================================================================*/
extern bool DEBUG;

/*=======================================================================
  these defines will help make your code be more readable
	=======================================================================*/
#define BOOK_TITLE string
#define BOOK_LIST vector<BOOK_TITLE>
#define RECOMMENDER string
#define RECOMMENDER_LIST vector<RECOMMENDER>
#define RATINGS double
#define RECOMMENDER_RATINGS_MAP map<RECOMMENDER, vector<RATINGS>>
#define BOOK_AVG_LIST vector<pair<BOOK_TITLE, double>>

class Recommend {
private:
	BOOK_LIST books;                 // vector of the names of all the books known to your program, read in from a file
	RECOMMENDER_LIST recommenders;   // vector of recommender's names
	RECOMMENDER_RATINGS_MAP ratings; // map that contains all book recommendations for each recommender
	BOOK_AVG_LIST bookAverages;      // vector of books along with their rating average
	BOOK_AVG_LIST similarList;       // used to compute the top 3 ratings based on similarity among recommenders: use for computeSimilarities
	BOOK_AVG_LIST simAvg; // takes top 3 most similar recommenders, averages the books that are non 0: use for computeSimAvg
public:
	Recommend(string fn);
	void computeRecommendation(RECOMMENDER);
	void computeBookAverages();
	void computeSimilarities(RECOMMENDER);
	void computeSimAvg(BOOK_AVG_LIST);
	bool checkRecommender(RECOMMENDER);
  	int getBookCount();
  	int getRecommenderCount();
  	double getRecommenderBookRating(RECOMMENDER, BOOK_TITLE);
	int getBookIndex(BOOK_TITLE);
	double getBookAverage(BOOK_TITLE);
	void printDotProducts(RECOMMENDER);
	void printRecommendation(RECOMMENDER);
	string strRecommendation();
	void printAverages();
	string strAverages();
	void printRecommendationRatings();
	string strRecommendationRatings();
	void printSimilarList(RECOMMENDER);
	string strSimilarList();
	void printSimAvg(RECOMMENDER);
	string strSimAvg();
	void printFancyRatings();
	string strFancyRatings();
	string strBooks();
	void printBooks();
	string strNames();
	void printNames();
private:
	string removeCR(string);
	string strDivider(char, int);
};
