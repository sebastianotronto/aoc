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

For second part you can edit the file `dayNNb.cpp` and run `make btest`
and `make brun`.
