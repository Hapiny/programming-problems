## Problem description
Given two words **text1** and **text2**, find the minimum number of operations 
required to convert **text1** to **text2**.

You have the following 3 operations permitted on a text:

- Insert a character
- Delete a character
- Replace a character

## Example 1

**Input:**<br>
text1 = "horse", text2 = "ros"

**Output:**<br> 
3

**Explanation:**<br> 
horse -> rorse (replace 'h' with 'r')<br>
rorse -> rose (remove 'r')<br>
rose -> ros (remove 'e')

## Example 2

**Input:**<br>
text1 = "intention", text2 = "execution"

**Output:**<br> 
5

**Explanation:**<br>
intention -> inention (remove 't')<br>
inention -> enention (replace 'i' with 'e')<br>
enention -> exention (replace 'n' with 'x')<br>
exention -> exection (replace 'n' with 'c')<br>
exection -> execution (insert 'u')
