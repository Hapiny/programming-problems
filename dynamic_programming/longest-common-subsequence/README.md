## Problem description
Given two strings **text1** and **text2**, return the length of their longest common subsequence (LCS).

A subsequence of a string is a new string generated from the original string with some characters
(can be none) deleted without changing the relative order of the remaining characters. 
(eg, "ace" is a subsequence of "abcde" while "aec" is not). 
A common subsequence of two strings is a subsequence that is common to both strings.

## Note

If there is no common subsequence, return 0.


## Example 1

**Input:**<br>
text1 = "abcde", text2 = "ace" 

**Output:**<br>
Max length = 3<br>
Found LCS = "ace"

## Example 2

**Input:**<br>
text1 = "abc", text2 = "def" 

**Output:**<br>
Max length = 0<br>
Found LCS = there is no common subsequence
