# Advent of Code 2024

This is my second year trying the AoC. This time I decided to take this
as an excuse to improve my C++ skills, so I'll use that instead of C.

As last year, my solutions are not commented, but feel free to send
me an email at sebastiano@tronto.net if you want to know how I solved
each problem!

## Template

This time I am trying to use a decent template for each day. Here are the
instructions in case you want to use it.

To start a new day run

```
$ ./init N
```

For example, to start day 7 you should run:

```
$ ./init.sh 7
```

and the script is going to create a folder `07` and copy some template
files there. Then you can copy the `input` file into that folder, edit
`dayNNa.cpp` and once your code is ready you can run

```
$ make arun
```

To run the first part with the downloaded input file. You can also use
`make atest` to take the input from standard input, so you can copy-paste
the test case into your terminal; press Ctrl-D to enter and EOF and
terminate the input.

*Note: I have been told that I should not check in the input files in my
public repository, so I have removed them. To run my solutions using the
Makefiles you should download your own input file and call it `input`.*

For second part you can edit the file `dayNNb.cpp` and run `make btest`
and `make brun`.

## Personal times

Note: New problems come out at 6am in my time zone. This year I often
(but not always) woke up a little earlier than 6am to start working on the
problem as soon as possible. Times longer than 3-4 hours mean that I could
not finish it before work, and I had to come back to it in the evening.

```
      --------Part 1--------   --------Part 2--------
Day       Time   Rank  Score       Time   Rank  Score
 25   00:54:10   4422      0   00:54:16   3269      0
 24   11:44:35  15839      0   18:35:30   8732      0
 23   00:18:38   2083      0   01:53:35   4086      0
 22   01:04:02   4637      0   02:51:45   4681      0
 21   02:19:57   1984      0   02:53:08   1143      0
 20   00:41:17   2132      0   01:07:13   1603      0
 19   00:24:23   3105      0   00:31:20   2456      0
 18   00:30:40   3511      0   00:34:02   2739      0
 17   00:29:54   2025      0   02:36:06   2128      0
 16   00:56:46   3612      0   03:34:41   5061      0
 15   02:08:45   7410      0   03:05:07   4474      0
 14   00:23:18   2528      0   02:35:21   6607      0
 13   00:22:24   2299      0   00:39:37   1593      0
 12   00:27:28   3133      0   06:45:37  10514      0
 11   00:46:47   9102      0   01:03:57   5013      0
 10   00:12:16   1480      0   00:14:06   1130      0
  9   00:14:06    962      0   00:34:43    888      0
  8   01:30:36   9024      0   01:48:47   8635      0
  7   01:43:27  10720      0   01:51:28   9649      0
  6   00:51:16   9051      0   01:20:33   5290      0
  5   01:20:49  12872      0   02:03:28  12064      0
  4   01:55:28  15951      0   02:07:56  13646      0
  3   01:37:48  19772      0   01:58:16  16711      0
  2   00:32:58  10110      0   00:48:07   7148      0
  1   03:23:24  19153      0   03:28:40  17929      0
```
