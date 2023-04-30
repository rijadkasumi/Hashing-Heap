
# To test Part 1 and Part 2:
    make all
    ./create_and_test_hash words.txt query_words.txt quadratic
    ./create_and_test_hash words.txt query_words.txt linear
    ./create_and_test_hash words.txt query_words.txt double
    ./create_and_test_hash words.txt query_words.txt double 89
    make clean


# To test Part 3 :
    make all
    ./spell_check document1_short.txt wordsEn.txt
    ./spell_check document1.txt wordsEn.txt
    make clean
