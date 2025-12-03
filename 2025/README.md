# Advent of Code 2025

Run with Python. Input is read from the file given as argument, or
from standard input if no argument is provided.

Example

`python 01/a.py 01/input.txt`

## Personal times

```
Day   -Part 1-   -Part 2-
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
