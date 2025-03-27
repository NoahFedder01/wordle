# wordle
c++ wordle and my wordle solving algorithms

This project is a recreation of the NYT game wordle, algorithms which attempt to solve them best, and each starting word rated from best to worst.

You can find the rated words in the efficientSorted.txt file. The scale is base 2 logarithmic, so a 5 is twice as good as a 4 which is twice as good as a 3, etc. The best word according to my algorithm is tarse, which is also the NYT wordle bot's top choice, so I am relatively confident that my ratings are correct.

Executing ./wordle lets you play the game. G means green, Y means yellow, and N means grey.

Executing ./tarse (recommended) will begin you with the word tarse because it is the best starter, and you can choose from there (the time complexity is O(n^2), so this was necessary for quick output). If you want to play a game without using the first word tarse, ./SGS is what you'll use. The second recommended word may take several minutes to calculate though.

I have not explicitly calculated the average number of guesses my algorithm takes yet, though I would guess that the average is under 4 because it has answered 2/3 of the wordles since I coded it in just 3 moves, and the other in 4. The most I have ever seen it take is 5.

Essentially, my algorithms rate the word based on how many words any given return value will eliminate on average. i.e. if the word is slant and you guess tarse, you get back Y Y N N Y, and any words which do not work with that are purged from the pool of possible answers.