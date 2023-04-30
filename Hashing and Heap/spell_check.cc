// Rijad Kasumi (rijad.kasumi11@myhunter.cuny.edu)
// Date 07-11-2022
// CSCI 335 - Assignment 3
// Professor Anita Raja
// spell_check.cc: A simple spell checker.
// This program checks if the words is spell correct while using the doublehashing algorithm. 
// The program takes in two files where one is a test file which contains the words to be corrected and then checks if each of the files is in the dictionary. 
// If the word is not spelled correct the program will uses one of the cases until it finds the correct word and then print out the words if " is CORRECT" or " is INCORRECT", and the correction of the word
// Functions implemented - check_cases() - to check each Case : A - Adding one character in any possible position, B - Removing one character from the word, C - Swapping adjacent characters in the word
#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// Function to check the cases:
// Case A - Adding one character in any possible position
// Case B - Removing one character from the word
// Case C - Swapping adjacent characters in the word
// Hashtable uses double_hashing
void check_Cases(const HashTableDouble <string>& dictionary, const string words) {

 // Case A - Adding one character in any possible position
  string word_In_File = words; // to copy the words 
  for (size_t i =0; i<words.size()+1;i++){  // looping through every character in the string
  for( char j='a'; j<= 'z'; j++){  // looping through letters in the alphabet a-z
  word_In_File.insert(i,1,j);   // inserting a string in the position of the string word_In_File
  if(dictionary.Contains(word_In_File)){ // checks for new string in the word
  cout<<"** " <<words<<" -> " << word_In_File <<" ** case A" << endl; // Print out the correction with added letter, if there is 
              }
              word_In_File = words; //reset words back 
              }
            }

  // Case B - Removing one character from the word
  word_In_File= words;
  for(size_t i=0; i<words.size(); i++){ // looping through every character in the string
  word_In_File.erase(i,1); // to remove the elements from the string 
  if(dictionary.Contains(word_In_File)){ // checks for new string in the word
  cout<<"** " <<words<<" -> " << word_In_File <<" ** case B" << endl; // Print out the correction with the removed character, if there is 
            }
            word_In_File= words;  //
            }
  // Case C - Swapping adjacent characters in the word
  for(size_t i=0; i<words.size(); i++){
  string word_In_File= words;
  swap(word_In_File[i],word_In_File[i+1]);  // swap the current character and the adjacent of that char
  if(dictionary.Contains(word_In_File)){  // if the string swapped is found 
    cout<<"** " <<words<<" -> " << word_In_File <<" ** case C" << endl; // Print out the swapped string 
                }
              word_In_File= words; 
            }    
      }
  // Function that checks and converst all characters to lowercases
  // And if the strings are alphanumeric characters 
  // tolower() used to check if words are not lowercases
  // isalnum() used to check if words are alphanumeric
    string check_Words(string words){
    for(size_t i=0; i< words.size(); i++){ // loop thru all the words
    words[i]= tolower(words[i]);}  // to change characters to lower case first
    string word_In_File = words;  // to copy the string to modify 
    int size_Words = word_In_File.size();
     if(size_Words > 1 &&( !isalnum (word_In_File[size_Words-1]))){ // if not a alphanumeric erase moving back 1
         word_In_File.erase(size_Words-1,1); // to get rid of any letter that isn't alphanumeric
          words = word_In_File; // words eequal the string
      }
    else if(size_Words == 1 &&( !isalnum (word_In_File[0]))){ //when its equal to 1 and not alphanumeric erase letter
      word_In_File.erase(0,1);   // to get rid of any letter that isn't alphanumeric
      words = word_In_File;
    } 
      words = word_In_File;
    return words;  // return string words
}


// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  // Fill dictionary_hash.
  // parsing into the dictionary_file
  ifstream ddictionary_File;
  string dictionary_Words; // string to parse into words 
  ddictionary_File.open(dictionary_file);
    while(ddictionary_File >>dictionary_Words){
      dictionary_hash.Insert(dictionary_Words);}

  return dictionary_hash; //return hash string
 }

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary,
      const string &document_file) {
  // parse in document_file
  ifstream ddocument_File(document_file); 
  string ddocument_Words;

  while(ddocument_File >> ddocument_Words){
      string words = check_Words(ddocument_Words); // string words will check if the words are alphanumeric and lower

      if(dictionary.Contains(words)){   // if the words are lower and alphanumeric then is Correct
        cout << words << " is CORRECT" << endl;}
      else{   
        cout << words << " is INCORRECT" << endl;      // if the words are not lowercase and not aplhanumerc
        check_Cases(dictionary, words);               // Check the error case and implement the required case to correct the word
      }   
  }
}


// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}
      
// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}

