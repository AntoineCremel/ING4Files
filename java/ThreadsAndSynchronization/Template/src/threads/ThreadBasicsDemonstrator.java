package threads;

/**
 * Demonstrates the basic operation of threads.
 *
 * @author Jean-Michel Busca
 */
public class ThreadBasicsDemonstrator {

  public static void main(String[] args) {

    // Note: when the JVM initializes, it starts a non-daemon thread whose
    // purpose is to execute the main method of the class
    System.out.println("method main: run by " + Thread.currentThread());

    // start thread1 (which is an instance of the MyThread class)
    System.out.println("method main: starting thread1");
    Thread thread1 = new MyThread("thread1");
    thread1.start();

    // start thread2 (using an instance of the MyRunnable class)
    System.out.println("method main: starting thread2");
    Thread thread2 = new Thread(new MyRunnable(), "thread2");
    thread2.start();

    System.out.println("method main: done");

  }

}
