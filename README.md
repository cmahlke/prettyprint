prettyprint
===========

Suppose we want to print a paragraph neatly on a page. The paragraph consists of words of length l1,l2,…,ln.The maximum line length is M. (Assume li < M always.) We define a measure of neatness as follows. The extra space on a line (using one space between words) containing words li through lj  is 
M – j + i - ∑jk=1 l..

The penalty is the sum over all lines except the last of the cube of the extra space at the end of the line. This has been proven to be an effective heuristic for neatness in practice. We want to find a dynamic programming algorithm to determine the neatest way to print a paragraph. The algorithm prints an optimal division of words into lines. The output is the text split into lines appropriately, and the numerical value of the penalty. A word in this context is any contiguous sequence of characters not including blank spaces.

Efficient algorithm to compute the penalty:

Since each p(k) for 1 ≤ k < j will be available the time p(j) is computed, we calculate the values of the array p from index 1 to n.  We need a method for recording the optimal arrangement of words, so we store an array c, where c(k) is the I which led to the optimal p(k).  Compute the arrays for p and c, and the optimal cost will be p(n) and optimal solution will be found by working from the bottom up by printing words c(n) through n on the last line, and then words c(c(n)-1) through c(n) – 1 on the next line up, and so on.  I created a temporary array L[0, …, n], where L[i] is the cumulative sum of the lengths of words 1 through i:  L[i] = L[i – 1] + li ≡ ∑jk=1 l k .  In order to compute the penalty(i, j) we simply modify the formula: penalty(i, j) = (M – j + i – (L[j] - L[i – 1]))3 .  Since each value of p requires n calculations as each i is considered it runs in O(n2) time, and uses O(n) space for the arrays.

To prove a recursive definition of the value of the optimal solution:

We let p(j) be the optimal cost of printing words 1 through j.  If i is the index of the first word printed on the last line of an optima solution then p(j) = p(i-1) + penalty(i,j).  We do not know which i is optimal, so we recurse through: p(j) = min (p(i-1) + penalty(i,j)). 

