//Angie Diaz 
//CPSC 1020
//Project 4: Reccomendation System App
//File: Reccomendation.cpp
//4/20/24
//Time: ~25 hours 
//Desc: cpp file that contains definition of methods for Recommend class 

#include "Recommend.h"

using namespace std; 

bool DEBUG = false;

/*==========================================================================
 bool compareRatings(const pair<string, double>&, const pair<string, couble>&)) - a helper function to compare by rating and then
 book title - used by sort
===========================================================================*/
bool compareRatings(const pair<string, double>& a, const pair<string, double>& b) {
	//if ratings are equal, then compare the titles
	if (a.second==b.second) {
		//return T/F for titles in alphabetical order
		return a.first < b.first;
	}
	//return T/F if rating is bigger than next one
	return a.second>b.second;

}
/*==========================================================================
 Recommend(string)
 - constructor:
 - open file from file name passed in
 - read through file (2X), removing possible CR (Windows files)
 - create a set of books and produces a vector of books sorted in title order
 - build a recommender ratings map that shows the ratings for each recommendation
 note: if a recommender does not rate a given title then the rating should be 0
 call this ratings
 - compute the average rating for each book
 - call the book averages

 DEBUGGING NOTE: use LOTS of "if (DEBUG) cout ...." statements in this code
===========================================================================*/

Recommend::Recommend(string fn) {
	ifstream inputFile(fn);
	
	//set that will contain no duplicates, titles in order
	BOOK_TITLE bookTitle; 
	set<BOOK_TITLE>uniqueBookTitles;
	RECOMMENDER recommender; 
	string rating;

	if (inputFile.is_open()) {
		//reading in from file
		while (getline(inputFile, recommender) && getline(inputFile, bookTitle) && getline(inputFile, rating)) {
			//adding into set and removing potential '\r'
			bookTitle=removeCR(bookTitle);
			uniqueBookTitles.insert(bookTitle);
		}
		//printing contents of set after reading in 
		if (DEBUG) {
			cout<<"DEBUG: Contents of book set: "<<endl;
			for (const auto& element: uniqueBookTitles) {
				cout<<element<<endl; 
			}
			cout<<endl;
		} 
		inputFile.close();
	} else {
		cout<<"Unable to open file.";
	}

	//copying unique set contents into vector 
	books=BOOK_LIST(uniqueBookTitles.begin(), uniqueBookTitles.end());


	//checks to see new vector and size
	if (DEBUG) {
			cout<<"DEBUG: Size of bookList: "<<books.size()<<endl;
		} 
	
	
	//Reading in file again to extract recommender names and ratings 
	inputFile.open(fn);

	if (inputFile.is_open()) {
		while (getline(inputFile, recommender) && getline(inputFile, bookTitle) && getline(inputFile, rating)) {
			
			//removing possible CR 
			recommender=removeCR(recommender);
			bookTitle=removeCR(bookTitle);
			rating=removeCR(rating);

			//If recommender does not exist in map yet, add them and a vector of 0's 
			if (ratings.find(recommender)==ratings.end()) {
				ratings[recommender]=vector<double>(books.size(), 0.0);
				//adding reccomender to recommenders list 
				recommenders.push_back(recommender);
				//checking to make sure recommender was created and who
				if (DEBUG) {
					cout<<"DEBUG: "<<recommender<<" created and initialized to 0 vector."<<endl;
				}
			}
			//Finding index of book title read from file in bookList 
			auto it=find(books.begin(), books.end(), bookTitle); 
			if (it!=books.end()) {
				//Calculate index where book title was found in bookList
				int index=it-books.begin();
				//Add rating into the corresponding postion in vector 
				ratings[recommender][index]=stod(rating);
				if (DEBUG) {
					cout<<"DEBUG: Rating added to map."<<endl;
				}
			}
		}
		inputFile.close();
	} else {
		cout<<"Unable to open input file (2)"<<endl;
	}

	//sorting recommender names in alphabetical order
	sort(recommenders.begin(), recommenders.end());

	//printing out contents of map
	if (DEBUG) {
		cout<<"DEBUG: After sorting and adding in constructor.\n";
	}

	//calling function to compute averages 
	computeBookAverages();

}




/*==========================================================================
 computeRecommend(RECOMMENDER)
 - find the top 3 similar recommenders
 - find the highest rated books from the top 3 recommenders
 ===========================================================================*/

 void Recommend::computeRecommendation(RECOMMENDER r) {
	//resetting simList and simAvg to make sure I get correct nums 
	similarList.clear();
	simAvg.clear();

	//function to find top 3 similar recommenders
	computeSimilarities(r);
	
	//Making a copy of similarList only containing top 3 and sending it to simAvg
	BOOK_AVG_LIST topThreeSim;
	if (similarList.size() >= 3) {
    	topThreeSim = vector<pair<BOOK_TITLE, double>>(similarList.begin(), similarList.begin() + 3);
	}
	
	//calling function to find highest rated books from top 3 recommenders 
	computeSimAvg(topThreeSim);
 }


/*==========================================================================
 computeSimAvg(BOOK_AVG_LIST)
 - takes top 3 most similar names to recommender
 - averages the books that are non 0
 - returns best books in order
===========================================================================*/

void Recommend::computeSimAvg(BOOK_AVG_LIST top) {
	
	
	//creating new list same length as list of books + filled with 0s
	vector<double>averages(books.size(), 0);
	int index=0;

	//looping through this new list, at every index looping thru first 3 recommenders
	for (auto& a: averages) {
		
		double count=0.0;
		double sum=0.0;
		double avg=0.0;

		//using vector passed in to find each person's ratings for each book
		for (const auto& person: top) {
			//calling function to find the rating person gave for book at index
			sum+=getRecommenderBookRating(person.first, books[index]);
			//if double returned is not equal to zero, increase total count
			if (getRecommenderBookRating(person.first, books[index])!=0) {
				count++;
			}
			
			if (DEBUG) {
				cout<<"DEBUG: For book at index "<<index<<" and person: "<<person.first<<" the current sum and count is: "
					<<sum<<" "<<count<<endl;
			}
		}
		//won't divide by 0 
		if (count!=0) {
			avg=sum/count;
		}
		//replacing 0 with new avg 
		a=avg; 
		index++;

	}
	if (DEBUG) {
		cout<<"DEBUG: Average ratings for top 3 recommenders: "<<endl;
		for (const auto& avg: averages) {
			cout<<avg<<" ";
		}
		cout<<endl;
	}

	//creating a list of pairs (simAvg) that contains book title and average rating
	int position=0;
	for (const auto& b: averages) {
		simAvg.emplace_back(books[position], b);
		position++;
	}

	sort(simAvg.begin(), simAvg.end(), compareRatings);

	

}

/*==========================================================================
 computeBookAverages()
 - compute and store (using bookAverages) the average rating for each book
 from all non 0 ratings
 - sort by highest rating
===========================================================================*/
void Recommend::computeBookAverages() {  
	size_t index=0;

	//checking to make sure ratings is accessible 
	if (DEBUG) {
		if (ratings.empty()) {
		cout<<"DEBUG: The ratings map is empty and cannot be found."<<endl;
		} 
	}
	//for every book we will add that title into the vector
	for (const auto& book : books) {
		//need to calculate the total ratings for one book 
		double avg=0.0, count=0.0, sum=0.0;
		for (const auto& element : ratings) {
			//copying over vector of ratings 
			const vector<double>& ratingsOfPerson=element.second;
			double rate=0.0;
			if (index<ratingsOfPerson.size()) {
				rate=ratingsOfPerson[index];
			}
			//including rating if not equal to zero
			if (rate!=0) {
				sum+=rate;
				count++;
			}
		}
		if (count!=0) {
			avg=sum/count;
		}
		//adding book title and corresponding avg to vector
		bookAverages.emplace_back(book, avg);

		//move to next book title
		index++;
	}

	
	//sorting by highest rating or alphabetical order if tie 
	sort(bookAverages.begin(), bookAverages.end(), compareRatings);

	if (DEBUG) {
		cout<<"DEBUG:\n";
		cout<<"BOOK AVERAGES"<<endl;
		cout<<"============="<<endl;
		for (const auto& pair : bookAverages) {
			cout<<"DEBUG: "<<fixed<<setprecision(2)<<pair.first<<" "<<pair.second<<endl;
		}
	}

}
/*==========================================================================
 computeSimilarities(RECOMMENDER)
 - finds the most similar recommendations to the recommender using dot product
 - sort by highest rating
 ==========================================================================*/

 void Recommend::computeSimilarities(RECOMMENDER request) {
	if (DEBUG) {
		if (!checkRecommender(request)) {
			cout<<"DEBUG: Requested reccomender not found inside ratings map."<<endl;
		}
		if (recommenders.empty()) {
			cout<<"DEBUG: recommenders is empty.\n";
		}
	}
	//storing a copy of requested_user ratings 
	vector<double>requestRatings=ratings.at(request);

	for (const auto& element : ratings) {
		//will not count requested_user ratings
		double sim=0;
		if (request!=element.first) {
			
			//need to multiply and add every rating to requested_user rating
			for (size_t i=0; i<element.second.size(); i++) {
				//multiplying review, adding to similarity score
				sim+=element.second[i]*requestRatings[i];
				
			}
		//adding to similarList
		similarList.emplace_back(element.first, sim);
		} 
	}
	//sorting similarList
	sort(similarList.begin(), similarList.end(), compareRatings);

	

	if(DEBUG) {
		if (similarList.empty()) {
			cout<<"DEBUG: similar list is empty after loop."<<endl;
		}
		for (const auto& s : similarList) {
			cout<<"DEBUG: ";
			cout<<"[("<<s.first<<", "<<s.second<<")."<<endl;
		}

	}

 }

/*==========================================================================
 bool checkRecommender(RECOMMENDER) - given a recommender's name, return
 true if recommender has made ratings, otherwise return false
 ==========================================================================*/
bool Recommend::checkRecommender(RECOMMENDER r) {
	//setting iterator to the string sent in
	auto it=ratings.find(r);
	//going through ratings, if we go thru entire file then its not inside
	if(it!=ratings.end()) {
		return true;
	} else {
		return false;
	}
}
/*==========================================================================
 double getBookAverage(BOOK_TITLE) - return average rating from bookAverages
 for a given book
 ==========================================================================*/
double Recommend::getBookAverage(BOOK_TITLE b) {
	if (DEBUG) {
		if (bookAverages.empty()) {
			cout<<"DEBUG: bookAverages is empty.\n";
		}
	}

	for (const auto& pair : bookAverages) {
		if (pair.first==b) {
			return pair.second;
		}
	}
	
}
/*==========================================================================
 int getBookCount() - return the number of books
 ==========================================================================*/
int Recommend::getBookCount() {
	return books.size();
}
/*==========================================================================
 int getRecommenderCount() - return the number of recommenders in ratings
 ==========================================================================*/
 int Recommend::getRecommenderCount() {
	return ratings.size();
 }

/*==========================================================================
 int getBookIndex(BOOK_TITLE) - return the index of a given book title in
 the books vector
 ==========================================================================*/
int Recommend::getBookIndex(BOOK_TITLE book) {
	int index;
	index=0;
	for (const auto& element : books) {
		if (book==element) {
			return index;
		}
		index++;
	}
	
}
/*==========================================================================
 double getRecommenderBookRating(RECOMMENDER, BOOK_TITLE)
 - find the position of the title in books vector
 - find the recommender in ratings vector
 - return the recommender's rating for that title
	==========================================================================*/
double Recommend::getRecommenderBookRating(RECOMMENDER r, BOOK_TITLE t) {
	//first need to find position of title in books vector
	int foundIndex=getBookIndex(t);
	
	//next need to find recommender in ratings vector
	for (const auto& person : ratings) {
		//found recommender
		if (person.first==r) {
			//now in the vector stored in person.second, need to iterate until we get to position of book
			if (DEBUG) {
				cout<<"DEBUG: Here is the rating based on call to getRecommenderBookRating:"<<person.second[foundIndex]<<endl;
			}
			return person.second[foundIndex];
		}
	}
	if (DEBUG) {
		cout<<"Could not find match for reccomender in ratings map (getRecBookRating), returning -50\n";
	}
	

}

/*==========================================================================
	printDotProducts(RECOMMENDER) - display dot products for current recommender
 ==========================================================================*/
void Recommend::printDotProducts(RECOMMENDER request) {
	cout<<"DOT PRODUCTS FOR RECOMMENDER: "<<request<<"\n";
	cout<<"=============================="<<strDivider('=', request.length())<<"\n";
	//recreating process that is occuring in computeSimilarities
	const vector<double>& requestRating=ratings.at(request);
	for (const auto& elem : ratings) {
		
		if (request!=elem.first) {
			cout<<elem.first<<": ";
			//need to multiply and add every rating to requested_user rating
			double dotProduct=0.0;
			
			for (size_t i=0; i<elem.second.size(); i++) {
				//multiplying review, adding to similarity score
				dotProduct+=elem.second[i]*requestRating[i];
				cout<<fixed<<setprecision(0)<<requestRating[i]<<" * "<<elem.second[i]<<" + ";
			}
			cout<<" = "<<dotProduct<<endl;
		}
	}


}
/*==========================================================================
 string strAverages() - return a string of computeBookAverages
 formatted for display
 ==========================================================================*/
string Recommend::strAverages() {

	stringstream totalBookAvg; 
	for (const auto& pair : bookAverages) {
		totalBookAvg<<fixed<<setprecision(2)<<pair.first<<" "<<pair.second<<endl;
	}
	return totalBookAvg.str();
}

/*==========================================================================
 printAverages() - display the bookAverages using strAverages()
 ==========================================================================*/

 void Recommend::printAverages() {
	cout<<"BOOK AVERAGES\n"<<"============="<<endl<<strAverages();
 }

/*==========================================================================
 string strRecommendationRatings() - return a string of ratings as read in
 from the file
 ==========================================================================*/

 string Recommend::strRecommendationRatings() { 
	stringstream fileRatings;
	for (const auto& pair : ratings) {
		fileRatings<<pair.first<<": ";
		for (size_t i=0; i<pair.second.size(); i++) {
			//converting ratings to strings and storing 
			fileRatings<<fixed<<setprecision(0)<<pair.second[i]<<" ";
		}
		fileRatings<<endl;
	}
	return fileRatings.str(); 
	
 }

/*==========================================================================
 printRecommendationRatings - display ratings  (ONLY RATINGS OR ALSO NAME?)
 ==========================================================================*/
 void Recommend::printRecommendationRatings() {
	cout<<"RECOMMENDATION RATINGS\n";
	cout<<"======================\n";
	cout<<strBooks();
	cout<<strRecommendationRatings();
 }

/*==========================================================================
 string strSimilarList() - return a string of similarList
 ==========================================================================*/
 string Recommend:: strSimilarList() {
	//similarList is a vector of pairs <string, double>
	stringstream similar;
	for (size_t i=0; i<similarList.size(); i++) {
			similar<<fixed<<setprecision(2)<<similarList[i].second<<": "<<similarList[i].first<<endl;
		}
	return similar.str();


 }
	

/*==========================================================================
 printSimilarList(RECOMMENDER) - display similarList for given recommender
 ==========================================================================*/
 void Recommend::printSimilarList(RECOMMENDER r) {
	if (similarList.empty()) {
		cout<<"Request a recommendation."<<endl;
	} else {
		cout<<"SIMILARITIES LIST FOR: "<<r<<endl;
		//calling function to have correct num of = for name length
		cout<<"======================="<<strDivider('=', r.length())<<endl;
		//printingSimilarList
		cout<<strSimilarList();
	}

 }

/*==========================================================================
 string strSimAvg() - return a string of simAvg
 ==========================================================================*/
string Recommend:: strSimAvg() {
	stringstream sim; 
	for (const auto& pair: simAvg) {
			sim<<fixed<<setprecision(2)<<pair.second<<": "<<pair.first<<endl;
		}
	return sim.str();
}
/*==========================================================================
 printSimAvg(RECOMMENDER) - display simAvg for given recommender
 ==========================================================================*/
void Recommend::printSimAvg(RECOMMENDER r) {
	if (simAvg.empty()) {
		cout<<"Request a recommendation."<<endl;
	} else {
		cout<<"SIMILARITY AVERAGES FOR: "<<r<<endl;
		//calling function to have correct num of = for name length
		cout<<"========================="<<strDivider('=', r.length())<<endl;
		cout<<strSimAvg();
	}

}


/*==========================================================================
 string strFancyRatings() - return a fancy formatted string of ratings
 ==========================================================================*/
 string Recommend::strFancyRatings() {
	stringstream ss;
	//spacing before book titles
 	ss << right << setw(10) << ' ';
 	//printing book titles 
	for (string b : books) {
   	 	ss << setw(13) << b << " ";
 	}
 	ss << endl;
 	for (auto const &[person, ratings_row] : ratings) {
    	ss << right << setw(8) << person << ": ";
    	for (double rating : ratings_row) {
       		ss << right << setw(13) << rating << " ";
    	}
    	ss << endl;
 	}
 	return ss.str();

 }
             

/*==========================================================================
 printFancyRatings() - display a fancy formatted string of ratings
 ==========================================================================*/
void Recommend:: printFancyRatings() {
	cout<<"RECOMMENDATION BOOK RATINGS\n";
	cout<<"===========================\n";
	cout<<strFancyRatings();
}

/*==========================================================================
 string strRecommendation() - return a string of current recommendations
 ==========================================================================*/
 string Recommend::strRecommendation() {
	stringstream rec;
	for (const auto& pair: simAvg) {
		if (pair.second>0) {
			rec<<pair.first<<" "
			<<fixed<<setprecision(2)<<pair.second<<endl;
		}
	}
	return rec.str();

 }


/*==========================================================================
 string strBooks() - return a string of books
 ==========================================================================*/
string Recommend:: strBooks() {
	stringstream totalBooks;
	for (const auto& b: books) {
		totalBooks<<b<<" / ";
	}
	totalBooks<<endl;
	return totalBooks.str();

}

/*==========================================================================
 printBooks() - display books
 ==========================================================================*/
 
 void Recommend::printBooks() {
	if (DEBUG) {
		if (books.empty()) {
			cout<<"DEBUG: The book vector is empty."<<endl;
		}
	}
	cout<<"BOOKS: ";
	cout<<strBooks();

 }

/*==========================================================================
 string strNames() - return a string of recommender names
 ==========================================================================*/
string Recommend::strNames() {
	stringstream names;
	for (const auto& element : recommenders) {
		names<<element<<" / ";
	}
	names<<endl; 
	return names.str();
	//assuming this is refering to recommender names priv variable



}

/*==========================================================================
 printNames() - display recommender names
 ==========================================================================*/

 void Recommend::printNames() {
	if (DEBUG) {
		if (ratings.empty()) {
			cout<<"DEBUG: Ratings map in printNames is empty.\n";
		}
		if (recommenders.empty()) {
			cout<<"DEBUG: recommenders list is empty\n"; 
		}
	}
	cout<<"RECOMMENDERS: ";
	cout<<strNames();
 }

/*==========================================================================
 printRecommendation(RECOMMENDER) - display recommendations for current
 recommender (which is passed in)
 ==========================================================================*/
//in rubic: BOOK RECOMMENDATIONS BASED ON RECOMMENDER: name; in autograder: RECOMMENDATION WITH: name
 void Recommend:: printRecommendation(RECOMMENDER req) {
	cout<<"RECOMMENDATION WITH: "<<req<<endl;
	cout<<"====================="<<strDivider('=', req.length())<<endl;
	cout<<strRecommendation()<<endl;

 }

/*==========================================================================
 string removeCR(string) - remove ending CR from string
 ==========================================================================*/
string Recommend::removeCR(string str) {
	if(!str.empty() && str.back()=='\r') {
		if (DEBUG) {
			cout<<"DEBUG: String passed to removeCr has '/r' "<<endl;
		}
		str.pop_back();
	}
	return str; 

}
/*==========================================================================
 string strDivider(char, int) - create a string of char of length int
 ==========================================================================*/
string Recommend::strDivider(char c, int l) {
	//creating string of char and length sent in 
	string str(l, c);
	return str; 

}