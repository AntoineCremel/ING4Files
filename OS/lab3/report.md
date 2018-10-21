#Report for lab3

##1. Implementation of the parallel computation
In this exercise, parallel computation was implemented using three
threads. The operation chosen to showcase thread computation was
`(1+2) * (3-4) + (5+6)`

To implement it, we created three threads, which were given the functions thread1, thread2 and thread3.

###Thread1
This first thread, the simplest of the bunch, computes 1+2, and stores
the result in a global int variable result.

###Thread2
This second thread is given a pointer to the first thread. It computes 3-4, then joins with the first thread to make the multiplication
between the 2 first operations and sotre it in the global variable.

Since we have to wait for the first operation to finish before we
combine this result with the other one, we don't need to use a mutex
to protect result.

###Thread3
This thread is given a pointer to the second thread. It computes 5+6,
then joins with the second thread to add the result of 5+6 to the
global variable.

Similarly to thread2, no mutex is required.

###Conclusion
Because of the nature of the operation, each thread has to wait for
the previous one to add its result to the total result. The
computation of the content of each parenthesis however is still
parallelised.

##2. Difference between the process and the thread versions.
The process version is obviously very different as it requires
creating a whole different process just to make a basic computation.
Since most of the inefficiency of processes lies in the overhead of
their creation, it seems like using threads would be a much better
alternative.

##3. Performance measurement
Performance measurement was conducted in two different ways :

* Using clock, to show how many clock ticks the execution took.
* Using getrusage, to get the CPU time

Based on clock ticks, the processes program is superior (around 550 clock ticks per execution against 1100 for the threads program).

Based on CPU time, the threads program performs better by a narrow marging (~2700 microseconds against ~2800 for the process program).

##4. I/O and context switches

### I/O
The program using processes stays consistently just above 150 page
faults serviced without I/O, and 0 page faults that required I/O.
This 0 is understandable because there is very little communication
between the processes in this program. The program using threads also had 0 page fault that required I/O activities, and stayed consistently
below 120 page faults that required no I/O.
This difference might be explained by the fact that since threads
duplicate the whole context they naturally have less page faults
ocuring.
### Context switches
Here the results are fairly consistent for the processes : 4 voluntary and 0 involuntary context switches aklist every single time. The threads program sometimes goes all the way down to voluntary context switches, but also sometimes goes up to 6 voluntary and 2 involuntary. This seems to indicate that the threads program needs only 3 context switches as opposed to the 4 of the process program, but that it is placed on a lower priority queue than the process program, which would explain the involuntary context switches that sometimes happen.