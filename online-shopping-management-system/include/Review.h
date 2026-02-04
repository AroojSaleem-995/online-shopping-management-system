#ifndef REVIEW_H 
#define REVIEW_H #include <string> using namespace std; 
class Review
{
int reviewID, rating; string comment; string author;
int productID; public:
Review() : reviewID(0), rating(0), productID(0) {}; 
Review(int id, string comment, int rating, string author): reviewID(id), comment(comment), rating(rating), author(author) {} int getReviewID() const;
string getComment() const; 
int getRating() const; 
string getAuthor() const;
void addReview(string comment, int rating); 
void displayReview() const;
};
#endif
