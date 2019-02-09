package primes;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;

/**
 * Computes prime numbers efficiently by leveraging all the available CPUs. The
 * main method of this class is {@link computePrimes}.
 * <p>
 * <i>Note to implementors:</i> You can add to this class any field, method or
 * nested class you need to implement {@code computePrimes}.
 *
 * @author Jean-Michel Busca
 */
public class PrimeComputer{
   //1 variables
   private static int nb_processor  = Runtime.getRuntime().availableProcessors();
   
   //2 Thread subclass
   static public class MyThread extends Thread {
       private long max;
       private int nThread;
       private int threadID;
       private ArrayList<Long> result;
       // Constructr of OUR thread
       MyThread(long max, int nThread, int threadID, ArrayList<Long> result){
           this.max = max;
           this.nThread = nThread;
           this.threadID = threadID;
           this.result = result;
       }
       //Our thread task
       @Override
       public void run() {
           for(long i=8*threadID+3; i < max; i+=8*nThread) {
               for(long j=i; j<i+8; j+=2) {
                    if(PrimeComputerTester.isPrime(j)) {
                        result.add(j);
                    }
               }
           }
       }
   }
  /**
   * Efficiently computes prime numbers up to the specified upper bound
   * (excluded).
   * <p>
   * <i>Note to implementors:</i>
   * <ul>
   * <li> <b>Do not alter</b> the interface of this method; if you do, the test
   * program will not work.
   * <li> Before returning, the method must release all the resources it
   * allocated, in particular threads - whether daemon or not.
   * <li> The method must use the {@link PrimeComputerTester#isPrime} method or
   * one of the two allowed variations (see the lab paper).
   * <li> The method is declared to return an {@code Iterable} object - which is
   * less restrictive than {@code List} or {@code Collection} - not to constrain
   * the implementation.
   * </ul>
   *
   * @param max the upper bound of primes
   *
   * @return an {@code Iterable} object over the list of primes;
   * {@code Iterator.next()} returns the primes in ascending order.
   */
  public static Iterable<Long> computePrimes(long max) {
    // TODO
    // 0 Variable declarations
    // threadTable contains a list of all the thread we are going to use
    ArrayList<MyThread> threadTable = new ArrayList<>();
    // Table of tables that will get the results of each thread
    ArrayList<ArrayList<Long>> results = new ArrayList<>();
    // Return variable
    ArrayList<Long> retour = new ArrayList<>();
    // Variable to hold the number of found prime numbers
    long totalPrimes = 0;
    // Variables that will allow us to concatenate the table of results in one
    // table
    long[] position = new long[nb_processor];
    
    // Creation of the right amount of threads
    for(int i=0; i < nb_processor; i++) {
        ArrayList<Long> result = new ArrayList<>();
        results.add(result);
        threadTable.add(new MyThread(max, nb_processor, i, result));
        
        // Initialize position
        position[i] = 0;
        
        threadTable.get(i).start();
    }
    
    for(int i=0; i < nb_processor; i++) {
        try {
            threadTable.get(i).join();
        }
        catch(InterruptedException e) {
            System.err.println(e);
        }
        totalPrimes += results.get(i).size();
    }
    retour.add(2l);
    for(int i=0; i < nb_processor; i++) {
        retour.addAll(results.get(i));
        Collections.sort(retour);
    }
    return retour;
  }
}
