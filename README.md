# RecommenderApp

Book Recommendation System

Overview
  This project implements a recommendation system that predicts book preferences for users based on their past ratings and the ratings of other recommenders. Inspired by systems like Amazon and Netflix, the program uses data-driven techniques to provide personalized recommendations.

Features
  Book Rating Analysis: Calculate average ratings for each book based on user input.
  Similarity-Based Recommendations: Suggest books using a similarity measure derived from the dot product of rating vectors.
  
Interactive Commands:
  View average book ratings (averages)
  List available books (books)
  Debugging tools for recommendation logic (debug, dotprod, similar, simavg)
  Display recommender names and ratings (names, ratings)
  Request book recommendations for a specific user (recommend <name>)
    
How It Works
  Data Input: The program reads a file containing user ratings in the format:
      Recommender name
      Book title
      Rating (integer between -5 and 5)
      Data Structures:
      Book List: Stores unique book titles.
      Recommender Ratings Map: A dictionary mapping users to their book ratings.

Recommendation Logic:
  Calculate the similarity between the requested user and other recommenders using dot products.
  Average ratings from the top three most similar recommenders to generate personalized suggestions.
  
Requirements
  C++ compiler (tested on SoC Linux machines)
  Input file with ratings (ratings_small.dat or ratings_large.dat)

How to Use
  Compile the program using the provided Makefile.
  Run the program with the ratings file as a command-line argument:
            ./recommender ratings_small.dat
Enter commands from the interactive menu to explore features or get recommendations.


Example Commands
        averages - Display average ratings for all books.
        books - Show a list of all books.
        recommend Kalid - Get book recommendations based on Kalid’s preferences.
Development Notes
      Debugging: Use commands like debug, dotprod, and similar for troubleshooting.
      Scalability: Start testing with ratings_small.dat before scaling to larger datasets.
      
License
This project was developed as part of a computer science course. All code adheres to academic integrity policies.

