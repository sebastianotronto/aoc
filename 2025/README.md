# Advent of Code 2025

Run with Python. Input is read from the file given as argument, or
from standard input if no argument is provided.

Example

`python 01/a.py 01/input.txt`

## Personal times

```
Day   -Part 1-   -Part 2-
 10   00:27:43   11:51:51
  9   00:05:05   02:11:41
  8   00:29:14   00:33:02
  7   00:05:27   00:20:40
  6   00:13:38   01:49:24
  5   00:04:39   00:22:19
  4   00:25:36   00:27:49
  3   00:05:02   00:16:09
  2   00:10:36   00:11:55
  1   00:06:20   00:50:41
```

## Daily comments (spoilers!)

### Day 1: Secret Entrance

Part 1 was easy. Well, I misread the statement and got it wrong twice,
but that's on me.

Then I kept getting part 2 wrong, and I have no idea what I was doing wrong.
Sure, at first I made some mistakes related to landing on zero at the
end of a movement. But for at least 6-7 times I found a mistake, fixed,
my code would solve the example case correctly but my answer on the real
input was wrong. At some point I started rewriting the code in alternative
ways hoping to get a different answer, and one of those versions worked.
Still no idea why.

So in the end it took me more than 40 minutes to solve part 2. Great start!

### Day 1: Secret Entrance

I misread the statement for part 1 and I accidentally solved part 2 first.
I re-read the problem description, fixed my code, submitted it, and then
I just had to press `Ctrl+Z` (actually `u` on vi...) enough times to solve
part 2.

### Day 3: Lobby

My solution for part 1 is ad-hoc and not very good. I should have thought
about it a bit longer, the general solution isn't much harder to find.

For part 2 I used recursion with memorization (using Python's
`functools.cache`), which is fast enough. But later Chiara pointed
out to me that actually the solution is quite trivially greedy; I
implemented the greedy version in `b-alt.py`.

### Day 4: Printing Department

The first "map" problem of the year! This one was easy, but I
made a lot of mistakes in part 1. I decided to use the trick that
[Jared](https://guissmo.com) suggested a couple of years ago: extend the
map by 1 cell in all directions so you don't have to deal with indices
out of bounds.

For part 2 I decided to quickly code the dumb "repeat part 1 until no
rolls are removed" strategy and it worked.

### Day 5: Cafeteria

Part 2 required a little bit of thinking to handle overlaps correctly
- at first I wrote a solution that did not handle overlaps, then one
that can only handle single overlaps, and finally one that works in
every case. My final solution is quite straightforward.

### Day 6: Trash Compactor

Part 1 was easy, but I struggled with part 2.

I had to solve this while travelling, which did not help, but that was
not the main issue. The problem was that for whatever reason my script
did not copy the whitespaces correctly from the sample input in the web
page, so I was left wondering how the heck am I supposed to align the
numbers. After more than an hour and after changing train, I figured out
the error and I was able to solve this elementary school problem. Much
smart, very accomplishment.

This year so far the only problems that took me more than 30 minutes
are this and the first one, not exactly the hardest problems imaginable.

### Day 7: Laboratories

This was quite fun! For part 1, I iterate over the rows of the diagram
keeping a list of the position currently occupied by a tachyon. I use a
Python set to avoid duplicates. Part 2 is very similar, but the set is
changed to a map where the keys are the positions and the values are the
number of multiverses where a tachyon is in that position.  To update
this value for the current row, I sum the values of all tachyons that
end there from the previous row (that can be one or two tachyons).

I added a second solution for part 2 that does not use a map, but only
lists. This could be seen as a dynamic programming problem where the
iterative implementation is more intuitive than the recursive one.

### Day 8: Playground

This one required some optimization effort for part 2... unless one is
already familiar with [the algorithm
described](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)
in the problem statement, and I was from back in the days of competitive
programming. In the end it was mostly a matter of figuring out the correct
[data structure to represent the groups of joint
boxes](https://en.wikipedia.org/wiki/Disjoint-set_data_structure) (or
a matter of remembering how it is implemented, if one already knows it).

### Day 9: Movie Theater

For me this was the first challenging problem (at least excluding those
that were challenging because of mis-read the problem statement or
because of sneaky bugs).

Part 1 was easy as usual. For part 2 we go through every pair of
corners and we check if the rectangle between them is admissible. A
rectangle is admissible if none of the line segments that make up the
figure "breaks" it. Breaking a rectangle means that either the lines is
internal to it (and thus the points on one of the sides of the line are
invalid but inside the rectangle) or that the line overlaps (at least
in part) with one of the sides of the rectangle, and the exterior of
the figure is in the rectangle. To know which side of the line is the
interior and which is the exterior, I do some pre-processing to compute
if our border winds clockwise or counter-clockwise (using the [cross
product](https://en.wikipedia.org/wiki/Cross_product)).  It may be that
every input has clockwise-winding border, but it was not much work to
implement this pre-processing.

My implementation of the function that checks if a line breaks the
rectangle looks like a bunch of very smart Math, but don't think I am
smart enough to write it on the first try: first I wrote it in 4 separate
cases (line is vertical / horizontal, t is positive or negative) and
then I merged the cases together removing the duplication. And I did
not merge the cases together to look smart, I did it because it made
debugging easier (did you think my code worked on the first try? ahah).

This algorithm is O(n^3) and runs in about 6 seconds on my small laptop
(or in about 4 seconds on my desktop). I was not sure O(n^3) was enough,
and in fact I wasted a lot of time searching a quadratic or O(n^2log n)
solution before I focused on formalizing a cubic one. The problem is that
I did not have smaller inputs to try my code against, so I this solution
was too slow I did not have any way to check that it was at least correct.

EDIT (about 12h after solving part 2): apparently my algorithm is not
entirely correct. In particular, it can fail by selecting a rectangle
that is completely external to the figure and none of whose sides overlaps
any of the lines.

For example with this input:

```
101,51
101,0
0,0
0,2
1,2
1,1
100,1
100,50
99,50
99,51
101,51
```

The first version of my program return 4851 instead of 202. I added a
check for this case in `b-fixed.py`, hopefully it works in 100% of the
cases now.

### Day 10: Factory

Phew, this was a hard one!
(More details coming soon, for now read the code and the comments)
