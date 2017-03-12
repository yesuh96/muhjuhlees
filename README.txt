1. Describe how and what each group member contributed for the past two weeks.
 If you are solo, these points will be part of the next section.

Renee figured out that we needed to copy the board in order to find a score of a hypothetical move and wrote a 
function for it.  She wrote alot of doMove and also implemented minimax successfully.Hye Joon came up with the 
idea of implementing a weight array and tested for the weight array that is most successful. She also contributed 
with the constructor, doMove, debugging and brainstormed a way to make AI competitive. 

We both went to the TA office hours together. I would say that we were a great team and we both contributed our 
best efforts to making this AI. 

2. Document the improvements that your group made to your AI to make it tournament-worthy.
 Explain why you think your strategy(s) will work. Feel free to discuss any ideas were tried but didn't work out.

We tried to make it such that the AI will at first go for the corner pieces, but as the game nears its end, the AI will 
prioritize getting as many positions as possible. I realized the times that our player (muhjuhlees) lost to Simple
player, it was because even at the end our AI was prioritizing the corner pieces  over the total number of positions
 it could flip to our side. 

Since black player tends to assume a more offensive position( as the nature of it starting first) The weight array for 
a black player should be slightly different to the white player (at least at the beginning of the play). As the 
game progresses and the offensive/defensive positions kind of even out this will no longer be needed but we could
even try this approach and test which weight arrays are most advantageous for each position at the beginning and
implement it. 
