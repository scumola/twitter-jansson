twitter-jansson
===============

C program to parse the twitter stream and the gnip twitter stream.

Takes raw json from the stream on stdin and dumps out pipe-delimited data on stdout.

Extra efficient.  Written in C for maximum json-parsing performance!  :)

to build
========

```
gcc twitter-jansson.c -g -o twitter-jansson -ljansson -lm
gcc gnip-jansson.c -g -o gnip-jansson -ljansson -lm
```
