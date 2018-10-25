# Lab 4

## Part 1
+ When we run cat text1 > text2, the contents of the file
text1 are read by cat and written text2.

### Program
The program we wrote for this part, called fileToFile.c,
starts by opening the 2 files, text1 in readmode and text2
in write mode.
Then we run dup2 to connect text2 to the standard output.
From this point, anything that we write into the standard
output will be written onto text2.
Then we make a loop to output each character of text1 
to standard output.

## Part 2
+ These 2 functions use a linux pipe. The standard output
of the function on the left of the " | " symbol is directed
to the standard input of the function on the right.

### Program
This program is similar to running `ps aux | more` in a 
Linux BaSH command prompt.

## Part 3
This code runs the read function on the standard input,
after setting it to be open in non blocking reading.
When used this way, the function read returns error 11,
resource temporarily unavailable.
There isn't any visble difference when commenting or
uncommenting the fcntl line.
