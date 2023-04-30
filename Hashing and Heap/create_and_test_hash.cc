// Rijad Kasumi (rijad.kasumi11@myhunter.cuny.edu)
// Date 07-11-2022
// CSCI 335 - Assignment 3
// Professor Anita Raja
// Create_and_test_hash.cc is modified to provide us with the The total number of elements in the table (N), the size of the table (T), the load factor (N/T), the total number of collisions (C), and the average number of collisions (C/N).
// This file checks if each word in the given files is in the hashtable, and if the words if found or not found the program will count how many probes it took to find if the word exists.

#include <fstream>
#include <iostream>
#include <string>
#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"


using namespace std;


// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) {
    hash_table.MakeEmpty();
    // to print out contains and to find the hashttable 
    // to parse through the files 
    ifstream words_File;
    words_File.open(words_filename);
    string read_Words;   // string to parse thru the words file
    while(getline(words_File, read_Words)){
        hash_table.Insert(read_Words);}
    size_t number_of_elements = hash_table.total_Number_Of_Elements(); // number of elements in the table
    size_t size_of_table = hash_table.size_Of_Table();   // size of the table 
    size_t collisions = hash_table.Collision();        // when collision occurs
    cout<<"number_of_elements: " <<number_of_elements<<endl;
    cout<<"size_of_table: "<<size_of_table<<endl;
    cout<<"load_factor: "<<(float)number_of_elements/(float)size_of_table<<endl;
    cout<<"collisions: "<<collisions<<endl;
    cout<<"avg_collisions: "<<(float)collisions/(float)number_of_elements<<endl;
    //output of number of elements, table size, load factor, total collisions and avg collisions
    cout<< endl;

    // parser to read the object from the query file 
    ifstream query_input_File;
    query_input_File.open(query_filename);
    string query_Line;     // string for the query file
    while(getline(query_input_File,query_Line)){
        hash_table.setCollision();
        //new position must be found in hashtable, so we collide until a position is found
        if(hash_table.Contains(query_Line))  //getCollisions + 1 finds total num of probes used
        cout << query_Line << " Found " << hash_table.Collision() + 1 << endl;        
        else 
        cout << query_Line << " Not_Found " << hash_table.Collision() + 1 << endl;
    }
    }
    
// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue); // string to integer
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename,
      			 query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
       // Uncomment below when you have implemented double hashing.
	HashTableDouble<string> double_probing_table;
	TestFunctionForHashTable(double_probing_table, words_filename,
				 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
