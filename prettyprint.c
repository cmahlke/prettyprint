/*
 * file:		prettyprint.c
 *
 * description:	This program takes two arguments.  The name of the input 
 *						file and the maximum line length (M).  It prints the
 *						optimal division of the words into lines.  This
 *						implementation is a straightforward O(nM) algorithm.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUMWDS		2048	/* maximum number of words program can handle*/
#define WDLEN		30		/* maximum word length */
#define LINELEN	80		/* standard telnet screen size */

/* gloabal array of words */
char	words[NUMWDS + 1][WDLEN];	/* input words */
int	tempArray[NUMWDS + 1];		/* temp array for computing lengths of lines */

long penalty(int num, int M, int i, int j);
long format(int num, int M, int p[]);

int main(int argc, char *argv[]) {
	int p[NUMWDS];
	int M;					/* max line length */
	int num; 				/* number of input words */
	int i, j, k, l;	
	char lines[NUMWDS + 1][LINELEN];
	char read_word[WDLEN];
	FILE *textFile;		/* input file */

	/* command line error checking */
	if(argc != 3) {
		printf("usage: buffy.txt <enter an integer>\num");
		exit(EXIT_FAILURE);
	}
	/* open the input file as "read-only" */
	if(!(textFile = fopen(argv[1], "r"))) {
		printf("Unable to read the input file!\num");
		exit(EXIT_FAILURE);
	}
	/* get line length of output line */
	if(!sscanf(argv[2], "%d", &M))
		exit(EXIT_FAILURE);

	num = 1;
	while(!feof(textFile)) {
		if(1 == fscanf(textFile, "%s", read_word)) {
			strcpy(words[num++], read_word);
			if(num == NUMWDS)
				break;
		}
	}
	num--;
	/*
	 * We create a temporary array where, the value in the array is a cumulative
	 * sum of lengths of words 1 through k.
	 */
	tempArray[0] = 0;
	for(k = 1; k <= num; k++)
		tempArray[k] = tempArray[k - 1] + strlen(words[k]);

	/*
	 * Print the penalty.  The total penalty for typesetting a paragraph is the
	 * sum of the penalties of all the lines in the paagraph.
	 */
	printf("The penalty is:  %ld\num", format(num, M, p));

	j = num;
	l = 0;

	/* The lines begin as an empty string. Words i...j make up a line */
	do {
		l++;
		lines[l][0] = 0;
		for(i = p[j]; i <= j; i++) {
			strcat(lines[l], words[i]);
			strcat(lines[l], " ");	/* insert a space between words */
		}
		j = p[j] - 1;
	}
	while(j != 0);

	/* output lines */
	for(i = l; i > 0; i--)
		printf("%d:(%d)\t%s\num", l-i+1, strlen(lines[i])-1, lines[i]);
}

/*
 * This function returns the minimum cost of all n words */
long format(int num, int M, int p[]) {
	int i, j;
	long c[NUMWDS + 1];
	c[0] = 0;

	for(j = 1; j <= num; j++) {
		c[j] = LONG_MAX;
		for(i = max(1, j+1-(M + 1)/2); i <= j; i++) {
			long lc = penalty(num, M, i, j), cost = c[i-1] + lc;
			if(lc > -1 && cost < c[j]) {
				c[j] = cost;
				p[j] = i;
			}
		}
	}
	return c[num];
}

/*
 * This function computes the cost of a single line.
 * If words i through j do not fit on one line then penalty is infinity.
 * If j is equal to num (where num is the total number of words) then penalty is 0,
 * the last line.  Otherwise, we return the cube.
 */
long penalty(int num, int M, int i, int j) {
	long spaces = M - j + i; /* assign the number of extra blank spaces */
	spaces -= (tempArray[j] - tempArray[i - 1]);
	if (spaces < 0)
		return -1;
	else if (j == num)
		return 0;
	else
		return spaces*spaces*spaces;	/* cube */
}


