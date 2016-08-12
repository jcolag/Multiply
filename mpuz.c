#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Generate a random number of a guaranteed specific length
 */
int number (int length) {
    int multiplier = 1,
        lead,
        rest,
        i;

    /* It's nonsensical to only request one digit or less */
    if (length < 2) {
        return (0);
    }

    /* Get the scale of the number, minus the first place */
    for (i = 1; i < length; i++) {
        multiplier *= 10;
    }

    /* Get the first digit separately to ensure the lead digit
     * is non-zero.  Since 0nm = nm, it's not a three-digit
     * number.
     */
    lead = rand() % 9 + 1;
    rest = rand() % multiplier;
    /* Put the parts together. */
    return (lead * multiplier + rest);
}

/*
 * Copies num into out as a formatted string, replacing
 * any still-unknown digits with the selected random
 * letters.
 * Returns the length of out, always 5.
 */
int subst (int num, char* out, char* letter) {
    int  i;

    sprintf(out, "%5d", num);
    for (i = 0; i < 10; i++) {
        if (isdigit(out[i])) {
            out[i] = letter[out[i] - '0'];
        }
    }

    return (strlen(out));
}

/* 
 * Prints a formatted line of the multiplication.
 */
int output (char* string, int length, int pad) {
    int  i,
    	 j,
         cont = 0;

	for (j = 0; j < pad; j++) {
		printf("\n");
	}
	
    for (i = 0; i < length; i++) {
		for (j = 0; j < pad; j++) {
			printf(" ");
		}
        printf("%c", string[i]);
        if (isalpha(string[i]) && string[i] != 'x') {
            cont = 1;
        }
    }

    printf("\n");
    return (cont);
}

/*
 * Main program, with command-line arguments.
 */
int main (int argc, char* argv[]) {
    int  multiplicand1,
         multiplicand2,
         intermediate1,
         intermediate2,
         product,
         guess,
         wrong,
         found,
         i,
         j,
         d = -1,
         pad = 0,
         length,
         show_intermediate = 0,
         option_index,
         still_args = 1;
    char letter[10],
         string[10],
         temp,
         c = 'Z',
         ch;
	static struct option long_options[] = {
	    { "help", no_argument, 0, 'h' },
		{ "use-padding", required_argument, 0, 'p' },
		{ "show-intermediate", no_argument, 0, 's' },
		{ 0, 0, 0, 0 }
	};

    /* Initialization */
    srand(time(NULL));
    do	{
        multiplicand1 = number(3);
        multiplicand2 = number(2);
        product = multiplicand1 * multiplicand2;
        intermediate1 = multiplicand1 * (multiplicand2 % 10);
        intermediate2 = multiplicand1 * (multiplicand2 / 10);
    } while ((product <= 10000) && (multiplicand2 % 10 > 1));
    
    while (still_args) {
    	c = getopt_long(argc, argv, "hp:s", long_options, &option_index);
    	switch (c) {
    	case -1:
    		still_args = 0;
    		break;
    	case 'h':
    		printf("Usage:\n\t%s [-hs] [-p X]\n", argv[0]);
    		printf("\n\t\t-h\tShow this help\n");
    		printf("\t\t-p <X>\tPad output by X spaces\n");
    		printf("\t\t-s\tShow intermediate products\n\n");
    		exit(0);
    		break;
    	case 'p':
    		if (!optarg) {
    			exit(-1);
    		}
    		
    		pad = atoi(optarg);
    		break;
    	case 's':
    		show_intermediate = 1;
    		break;
    	}
    }

    for (i = 0; i < 10; i++) {
        letter[i] = 'A' + i;
    }

    /* Shuffle the letter replacements */
    for (i = 0; i < 10; i++) {
        j = rand() % 10;
        temp = letter[j];
        letter[j] = letter[i];
        letter[i] = temp;
    }

    guess = 0;
    wrong = 0;
    while (1) {
        /* Print the current game state */
        found = 0;
        length = subst(multiplicand1, string, letter);
        found |= output(string, length, pad);
        length = subst(multiplicand2, string, letter);
        string[0] = 'x';
        found |= output(string, length, pad);
        output("-----", 5, pad);
        if (show_intermediate) {
	        length = subst(intermediate1, string, letter);
	        found |= output(string, length, pad);
	        length = subst(intermediate2, string, letter) + 1;
	        strcpy(string, string + 1);
	        string[5] = ' ';
	        found |= output(string, length, pad);
	        output("-----", 5, pad);
        }
        length = subst(product, string, letter);
        found |= output(string, length, pad);
        if (!found) {
            printf ("You won with %d wrong guesses of %d total.\n", wrong, guess);
            return (-wrong);
        }

        printf ("(%d guesses - %d wrong)\n", guess, wrong);
        printf("\n > ");
        ch = '\000';
        /* Get and validate input */
        while (ch != 0x0A) {
            ch = fgetc (stdin);
            if (isdigit (ch)) {
                d = ch - '0';
            }
            if (isalpha (ch)) {
                c = toupper (ch);
                if (c == 'Q') {
                	printf ("Exiting...\n");
                	exit (0);
                } else if (c == 'P') {
                	printf ("Numbers solved:  ");
                	for (i = 0; i < 10; i++) {
                		if (isdigit (letter[i])) {
                			printf ("%c ", letter[i]);
                		}
                	}
                	
                	printf ("\n");
                	continue;
                }
            }
        }

        found = 0;
        for (i = 0; i < 10; i++) {
            if (letter[i] == c) {
                found = 1;
            }
        }

        if (!found) {
            printf ("You have already solved for %c!\n", c);
        } else if (isdigit (letter[d])) {
            printf ("You've already placed a %d!\n", d);
        } else {
            printf ("%c = %d?  ", c, d);
            if (letter[d] == c) {
                printf ("Correct!\n");
                letter[d] = d + '0';
            } else {
                printf ("Try again!\n");
                ++ wrong;
            }
            ++ guess;
        }
    }

    return (0);
}

