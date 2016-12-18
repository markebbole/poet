# poet

poet is a programming language whose programs are poems.

### how it works
#### loops and if statements
a while loop is defined through the use of alliteration at the beginning of a line.
the first word must have its first two letters in reverse alphabetical order.
the rest of the line is an expression. The last word of the line defines an opening rhyme token. 
The end of the loop occurs at the next line whose last word rhymes with this rhyme token.

If statements are the same as while loops in structure, but the first word must have its first two letters IN alphabetical order.

#### Assignments to variables
An assignment begins with any word that occurs in a line that is not a loop or an if statement. The name of the variable is the first two consonants in the first word, and the expression that should be assigned to it is the rest of the line.


#### expressions
An expression can be: a binary operator, an variable, or an integer constant.

##### Binary operators
An operator is a 2-syllable word which starts with the letters a,b,c,d,e,f,g,h,i, or j, which correspond to:
+, -, *, /, >, >=, <, <=, ==, and % respectively
The rest of the line after a binary operator contains the operands

##### Integers
An integer is a sequence of one-syllable words. If the first two letters of a word are in alphabetical order,
then the 'count' for the word is the number of letters in it. Otherwise, the 'count' is abs(# vowels - # consonants).

A sequence of such words form the digits of an integer constant. For example,

my name is fred

evaluates to 2024, since my=2, name=0, is=2, fred=4.

##### variables
A variable lookup is just a 2-syllable word that doesn't begin with a-j. The first two consonants in such a word are the variable name.



