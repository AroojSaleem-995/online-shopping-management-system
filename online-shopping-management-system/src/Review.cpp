#include "Review.h" 
#include <iostream> 
#include <string>
int Review::getReviewID() const
{
return reviewID;
}
string Review::getComment() const
{
return comment;
}
int Review::getRating() const
{
return rating;
}
string Review::getAuthor() const
{
return author;
}
void Review::addReview(string comment, const int rating)
{
if (rating < 1 || rating > 5)
{
 
std::cout << "Invalid rating. Please provide a rating between 1 and 5." << std::endl; return;
}
this->comment = std::move(comment); 
this->rating = rating;

reviewID = static_cast<int>(time(nullptr) % 10000);
std::cout << "Review added successfully with ID: " << reviewID << std::endl;
}
void Review::displayReview() const
{
std::cout << "Review ID: " << reviewID << std::endl; 
std::cout << "Rating: ";
// Display stars for rating 
for (int i = 0; i < rating; i++)
{
std::cout << "★";
}
for (int i = rating; i < 5; i++)
{
std::cout << "☆";
}
std::cout << " (" << rating << "/5)" << std::endl; 
std::cout << "Comment: " << comment << std::endl; 
std::cout << "Author: " << author << std::endl;
}
