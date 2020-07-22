## Problem description
You have a number of envelopes with widths and heights given as a pair of integers **(w, h)**. 
One envelope can fit into another if and only if both the width and height of one envelope 
**is greater than** the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

## Note
Rotation is not allowed

## Example

**Input:**<br>

[ [ 5, 4 ], [ 6, 4 ], [ 6, 7 ], [ 2, 3 ] ]

**Output:**<br>

3

**Explanation:**

The maximum number of envelopes you can Russian doll is 3: <br>
    [ 2, 3 ] => [ 5, 4 ] => [ 6, 7 ]
