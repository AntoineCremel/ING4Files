package primes;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.TreeSet;
import java.util.function.Function;

/**
 * Tests the {@link PrimeComputer#computePrimes} method for correctness and
 * performance.
 *
 * @author Jean-Michel Busca
 */
public class PrimeComputerTester {

  /**
   * Main method of the test program.
   *
   * @param args the command line arguments: [max [#iteration]]
   */
  public static void main(String[] args) {

    // get test arguments
    long[] arguments = getArguments(args);

    // test getPrimes (reference test - sequential)
    TestResult reference
        = performTest("getPrimes", arguments, PrimeComputerTester::getPrimes);

    // test computePrimes (actual test - parallel)
    TestResult computation
        = performTest("computePrimes", arguments, PrimeComputer::computePrimes);

    // compare results
    compareResults(reference, computation);

  }

  /**
   * Checks whether the specified natural number is prime. The method uses a
   * basic sequential algorithm.
   *
   * @param number the natural number to check
   *
   * @return {@code true} if the specified number is prime and {@code false}
   * otherwise.
   */
  public static boolean isPrime(long number) {
    if (number < 0) {
      throw new IllegalArgumentException("number is not natural");
    }
    if (number < 2) {
      return false;
    }
    if (number == 2 || number == 3) {
      return true;
    }
    if (number % 2 == 0) {
      return false;
    }
    long limit = (long) Math.sqrt(number);
    for (long divisor = 3; divisor <= limit; divisor += 2) {
      if (number % divisor == 0) {
        return false;
      }
    }
    return true;
  }

  /**
   * Returns the list of primes up to the specified upper bound (excluded).
   *
   * @param max the upper bound of primes
   *
   * @return an {@code Iterable} object over the list of primes;
   * {@code Iterator.next()} returns the primes in ascending order.
   */
  private static Iterable<Long> getPrimes(long max) {
    List<Long> primes = new ArrayList<>();
    for (long candidate = 1; candidate < max; candidate += 1) {
      if (isPrime(candidate)) {
        primes.add(candidate);
      }
    }
    return primes;
  }

  //
  // UTILITY METHODS
  //
  private static long[] getArguments(String[] args) {

    // default values
    long max = 10_000_000;
    int iterations = 10;

    // check command line arguments
    try {

      if (args.length >= 1) {
        max = Long.parseLong(args[0]);
      }
      if (args.length >= 2) {
        iterations = Integer.parseInt(args[1]);
      }
      if (args.length >= 3) {
        throw new IllegalArgumentException("too many arguments");
      }

    } catch (IllegalArgumentException e) {
      System.err.println("usage: PrimeComputerTester [max [#iterations]]");
      System.exit(1);
    }

    // return final values
    return new long[]{max, iterations};

  }

  private static TestResult performTest(String description, long[] arguments,
      Function<Long, Iterable<Long>> method) {

    // set the test up
    long max = arguments[0];
    long iterations = arguments[1];
    System.out.println("testing " + description + "...");

    // perform the test
    long elapsed = System.currentTimeMillis();
    Iterable<Long> iterable = Collections.emptyList();
    for (int i = 0; i < iterations; i++) {
      System.out.println("- iteration #" + i);
      iterable = method.apply(max);
    }
    elapsed = System.currentTimeMillis() - elapsed;
    List<Long> primes = new ArrayList<>();
    iterable.forEach(p -> {
      primes.add(p);
    });

    // print and return test results
    System.out.println("#primes: " + primes.size());
    System.out.println("elapsed: " + elapsed + " ms");

    return new TestResult(primes, elapsed);

  }

  private static void compareResults(TestResult reference, TestResult computed) {

    // I- check correctness
    System.out.println("correctness:");
    List<Long> referencePrimes = reference.getPrimes();
    List<Long> computedPrimes = computed.getPrimes();

    // I.a- calculate precision and recall
    // determine false positives and false negatives
    List<Long> falsePositives = substract(computedPrimes, referencePrimes);
    List<Long> falseNegatives = substract(referencePrimes, computedPrimes);
    // calculate precision and recall
    int falsePosCount = falsePositives.size();
    int falseNegCount = falseNegatives.size();
    int truePosCount = computedPrimes.size() - falsePosCount;
    double precision = (1.0 * truePosCount) / (truePosCount + falsePosCount);
    double recall = (1.0 * truePosCount) / (truePosCount + falseNegCount);
    // print values
    System.out.print("- precision = " + ((int) (100 * precision)) + "%");
    System.out.println(", false positives = " + falsePositives);
    System.out.print("- recall = " + ((int) (100 * recall)) + "%");
    System.out.println(", false negatives = " + falseNegatives);

    // I.b- check whether primes are sorted
    double sortRate = sortRate(computedPrimes);
    System.out.println("- primes are sorted = " + ((int) (100 * sortRate)) + "%");

    // II- check performances
    System.out.println("performance:");
    double speedup = (1.0 * reference.getElapsed()) / computed.getElapsed();
    double maxSpeedup = Runtime.getRuntime().availableProcessors();
    double solutionSpeedup = maxSpeedup / 2; //  ESTIMATED
    System.out.println("- maximum theoretical speedup = " + maxSpeedup);
    System.out.println("- ESTIMATED solution speedup = " + solutionSpeedup);
    System.out.println("- actual speedup = " + speedup);

    // III- overall assessment
    double grade = 0.0;
    // correctness
    grade += 3 * (precision < 1.0 ? 0.0 : 1.0);
    grade += 3 * sortRate;
    // performance
    grade += 6 * speedup / solutionSpeedup;
    // everything depends on recall in the end
    grade *= recall;

    System.out.println("*ESTIMATED* grade = " + ((int) grade) + " / 12");

  }

  private static double sortRate(List<Long> list) {

    if (list.size() <= 1) {
      return 0.0;
    }

    int count = 1;
    for (int i = 0; i < list.size() - 1; i += 1) {
      if (list.get(i).compareTo(list.get(i + 1)) <= 0) {
        count += 1;
      }
    }

    return 1.0 * count / list.size();
  }

  private static <T> List<T> substract(Collection<T> collection1,
      Collection<T> collection2) {

    List<T> difference = new ArrayList<>();
    collection2 = new TreeSet<>(collection2); // to speed contains() up

    for (T element : collection1) {
      if (!collection2.contains(element)) {
        difference.add(element);
      }
    }

    return difference;
  }

  //
  // INNER CLASSES
  //
  private static class TestResult {

    private final List<Long> primes;
    private final long elapsed;

    public TestResult(List<Long> primes, long elapsed) {
      this.primes = primes;
      this.elapsed = elapsed;
    }

    public List<Long> getPrimes() {
      return primes;
    }

    public long getElapsed() {
      return elapsed;
    }

  }

}
