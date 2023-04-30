# Rijad Kasumi - rijad.kasumi11@myhunter.cuny.edu
# Date 08-11-2022
# Assignment 3
# CSCI 335 Software Analysis and Design 3
# The main focus of this program is hashing and heaps. It includes testing 3 hashing implementations : linear, quadratic and doublehashing. Also, to implement a spell checker which make sures that words are spelled right and if not, to correct the words.

# Feedback and difficulties I encountered working on this assignment #

# In part 1 of the program, I modified the provided file quadratic_probing.h and created the linear_probing.h and double_hashing.h files. In the quadratic_probing.h I implemented couple function which will help me to find the number of elemnents in the hashtable "total_Number_Of_Elements" which returns the current_size_ of elements, the size of the hash table "size_Of_Table()" which returns the size of the table,the total number of collisions "Collision()" which returns the number of collision, the average number of collisions and the load factor. I declared a variable for collision number_Of_Collision, which also will check for collision and this value will be iterated in while loop of findPos to count when collision ocurrs. All the functions created and modified are used in create_and_test_hash.cc file. To implement linear_probing.h I didn't encounter any difficultites. I copied the file quadratic probing and modified it to fit the linear probing. The most important modification was in findPos() where in linear probing we dont need the offset so I deleted that line of code and the rest of the functions stay the same as in quadratic_probing.h. In create_and_test_hash.cc I implemented a parses which will read a text file which has the list of words and another text file that has the words we are searching for. This was added in TestFunctionForHashTable() where the functions check if each words is in the hashtable and then prints out  " Found " and " Not_Found " and how many probes it took to find the word. A difficulty I encounterd doing this part was because I was getting the full points on grade scope and after going over it I realized that I was missing a space in " Found ", besides that I encourted some small errors but fixed them while going back to the book and the blackboard lectures slides.

# In part 2 of the program, I implemeted the double_hashing.h. The implementation of this file was similar to the quadratic probing just with a little modifications. The function to find and calucate the collisions are the same as in the other files. In this part I needed to modify the findPos() so the offset equals the second InternalHash()=> DoubleHash() which works as a second InternalHash() function with the formula given hash2 (x) = R – (x mod R). For the Rvalue I used the value 89 which is a Prime number and was also given on the prompt. After running create_and_tesh_hash.cc the output was correct and I didn't face many difficulites for this part.

# To test Part 1 and Part 2:
    make all
    ./create_and_test_hash words.txt query_words.txt quadratic
    ./create_and_test_hash words.txt query_words.txt linear
    ./create_and_test_hash words.txt query_words.txt double
    ./create_and_test_hash words.txt query_words.txt double 89
    make clean

# In part 3 of the program, I implemented a spell-checker in the spell_check.cc file while using the double_hashing algorithm. I implemented a function check_Cases() which will find the word and correct it based on the case required. The function will check if there is needed to add a characted in any position Case A - while looping thru the strings and letters on alphabet and then inserting the missing letter in the word and printing out the new corrected word with the required case. For Case B - while looping through every character and erasing the wrong placed letter and then printing out the new corrected word with the required case. And for Case C - while looping thru the strings and swaping the character and putting it in the right position and then printing out the corrected word with the case used. The second function added check_words() will use a string to check if every character in the word is first a lowercase character and then second to check if its a alphabetic letter and also to check that it is not a numeric. In this function we used to function from the library which helped us to check for lower cases - "tolower()" and the "isalnum()" function from the c++ libraries which helped us to check if the words are alphanumeric while looping thru the letters.SpellCheckers was also modified to read words and check if the files contains the words to be spell-checked and then correct them.The testSpellingWrapper() function act as a main while calling all the function implemented. I faced a few difficulties working on this part especially with the outputing because my function wouldn't properly work for all cases. My error was in my function to check the words because I wouldn't erase the proper numeric letter. Besised that I had some errors with the formating of the output until I went over the prompt again and realized that my output wasn't in the correct order as specified in the prompt.

# To test Part 3 :
    make all
    ./spell_check document1_short.txt wordsEn.txt
    ./spell_check document1.txt wordsEn.txt
    make clean
