# wordle
c++ wordle and my wordle solving algorithms

This is my first solo project so I know it doesn't follow best coding practices. I am still proud of it.

This project is a recreation of the NYT game wordle, some algorithms which attempt to solve them with the least number of guesses, and a file with each starting word rated from best to worst.

You can find the rated words in the efficientSorted.txt file. Words in the rated-and-sorted.txt file are from an earlier version where all 14,855 words were possible answers, which is not how wordle works. Although the allowed guesses number 14,855, the allowed answers come from a pool of about 3,000 words. ./SGS and ./tarse both account for this. The scale is base 2 logarithmic, so a word rating of 5 is twice as good as a 4 which is twice as good as a 3, etc. The best word according to my algorithm is tarse, which is also the NYT wordle bot's top choice, so I am relatively confident that my ratings are correct. Also the worst words are xviii and zhuzh. I highly recommend checking your favorite starting word against my file.

Executing ./wordle lets you play the game. G means green, Y means yellow, and N means grey.

Executing ./tarse (recommended) will begin you with the word tarse because it is the best starter, and you can choose from there (idk how to optomize so the time complexity is n^2, so assuming this was necessary for quick output). If you want to play a game without using the first word tarse, ./SGS is what you'll use. The second recommended word may take several minutes to calculate though.

I have not explicitly calculated the average number of guesses my algorithm takes yet, though I would guess that the average is under 4 because it has answered 2/3 of the wordles since I coded it in just 3 moves, and the other in 4. The most I have ever seen it take is 5.

Essentially, my algorithms rate the word based on how many words any given return value will eliminate on average. i.e. if the word is slant and you guess tarse, you get back Y Y N N Y, and any words which do not work with that are purged from the pool of possible answers.