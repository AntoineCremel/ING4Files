package test;

/**
 * A class recording statistics about unit tests, including: the number of tests
 * executed, the number of test passed, the "passed" mark and the "total" mark.
 * <p>
 * This class is thread-safe. Methods are synchronized on {@code this}.
 *
 * @author Jean-Michel Busca
 */
public class TestStats {

  private int testCount;
  private int passedCount;
  private double totalMark;
  private double passedMark;

  /**
   * Adds to these statistics the specified test with the specified execution
   * status and default weight of {@code 1.0}.
   *
   * @param test the description of the test
   * @param isPassed the execution status of the test
   */
  public synchronized void add(String test, boolean isPassed) {
    add(test, isPassed, 1.0f);
  }

  /**
   * Adds to theses statistics the specified test with the specified execution
   * status and the specified weight. In addition, the method print a success /
   * failed message on standard output.
   *
   * @param test the description of the test
   * @param isPassed the execution status of the test
   * @param weight the weight of the test
   */
  public synchronized void add(String test, boolean isPassed, double weight) {
    testCount += 1;
    totalMark += weight;
    System.out.print(test + ": ");
    if (isPassed) {
      passedCount += 1;
      passedMark += weight;
      System.out.println("ok");
    } else {
      System.out.println("FAILED");
    }
  }

  /**
   * Adds to these statistics the specified statistics.
   *
   * @param other the statistics to add
   */
  public synchronized void add(TestStats other) {
    testCount += other.testCount;
    passedCount += other.passedCount;
    totalMark += other.totalMark;
    passedMark += other.passedMark;
  }

  @Override
  public synchronized String toString() {
    if (testCount == 0) {
      return "no test performed";
    }
    String results = "total=" + testCount + ", ok=" + passedCount;
    results += ", mark=" + (passedMark / totalMark);
    return results;
  }

}
