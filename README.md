# wildcard-search
Wildcard search in C++

Algorithm Overview 

1. Scan the Dataset & create a dictionary of lists to generate the InvertedIndex.

2. Generate all valid permutations of the words & generate the PermuteTermIndex. Also maintain a sorted set of Permuted terms & a dictionary mapping permuted terms to the original word.

3. For finding all the valid documents related to a query let's say f\*e ,transfrom the query to e$f*.

4. Look for all the permute terms of which e$f is a prefix. This can be done efficiently since a sorted set of Permute terms has been maintained. There is also a mapping of Permute terms to original words. Using InvertedIndex get all the valid documents.  
