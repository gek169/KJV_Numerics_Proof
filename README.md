
# Are the Numeric patterns in the KJV real?

Study of numerical patterns in the KJV versus other texts

There are patterns in the number of vowels, letters, consonants, and words in the KJV which are significant in evaluating whether or not it really comes from God.

For instance, the first and last verses of the KJV both have the same number of vowels, letters, and consonants. There are only a small number of verses that have this property, and one of them (2 Corinthians 10:9) actually alludes to the pattern by mentioning letters, and that even fits the context of the verse.

If patterns which are similar or identical could be found in other texts, ones which we did not believe had any spiritual significance, such as Alice in Wonderland, then it would be a good reason to believe that the patterns are simply random. If they do not appear in other texts, appearing in unusually and particularly in the KJV, then it would be good evidence that these are intentional and placed there by an intelligence, and it is unlikely to be the human author who did it.


That intelligence, of course, is believed to be the LORD  himself in the case of the Bible.

This repository contains the tools as well as some sample texts from the Gutenberg project collected from the Internet Archive to conduct analysis of secular texts 

# Methodology

Most books are not divided into chapters and verses the same way as the Bible. Chapters in other books are generally not like chapters in the Bible.

In order to do the comparison, we need to take a text and subdivide it into verses. These verses are what are then used to check for the presence of numeric patterns similar to the KJV.

## The texts used

A selection of texts of a variety of genres are used.

These are the texts chosen for this study:
Alice in Wonderland by Lewis Carroll
Federalist Papers 1-10
Memoires of Casanova by Jacques Casanova de Seingalt
The Ancient Life History of the Earth by Henry Alleyne Nicholson
The Interesting Narrative of the Life of Olaudah Equiano, Or Gustavus Vassa, The African Written By Himself
The Life of Mohammad The Prophet of Allah by Etienne Dinet and Sliman Ben Ibrahim
The Witness of the Stars by Ethelbert William Bullinger

The texts have been modified to remove indexes/biographies, copyright notices, authorship notices, etcetera that are at the beginning and end. Chapter notations and editorial marks such as the presence of an illustration were not removed as it is considered that they do not significantly affect the results for the purposes of this experiment.

## Versegen.c - Generate Verses from a text and check for verse letter frequency properties.

The entire text of the book is loaded into a single C-string. All non-alphanumeric characters are turned into spaces.

Numbers are preserved as words but they are not converted into language form (777 into seven hundred seventy seven, for example). It is a TODO to convert them.

The entire text is then subdivided into a massive array of words, each of which contains only alphanumeric characters.

Verses are then generated using that list of words.

Verses are randomly sized between 2 and about 100 words. The exact distribution of verse lengths is not replicated for the experiment, which might affect results.

After the verses are generated, the first and last are checked to see if they have the property that the Bible has. 

Verses 1611 and 777 are also checked.

Then, random number pairs are repeatedly generated and the corresponding verses checked to see if they contain the same number of vowels, letters, and consonants. Those verses are printed.

This is done 100,000 times.

At the very end, the number of vowel/letter correlations found is reported.

## Results for each book

Ten trials for each book are recorded:
```
ALICE IN WONDERLAND
        # of verse pairs found with         # of verse pairs found with
        the same number of letters          the same number of vowels and consonants
1:          187                             22
2:          248                             42
3:          217                             6
4:          259                             12
5:          315                             20
6:          247                             36
7:          198                             11
8:          256                             28
9:          231                             0
10:         221                             41

THE FEDERALIST PAPERS 1 THROUGH 10
1:          190                             30
2:          199                             21
3:          159                             12
4:          276                             28
5:          201                             15
6:          224                             24
7:          208                             19
8:          180                             20
9:          190                             19
10:         189                             21

TODO: Test the other books.

```
