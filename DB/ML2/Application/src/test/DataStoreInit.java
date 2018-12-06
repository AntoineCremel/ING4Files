package test;

import java.util.Arrays;
import static java.util.Arrays.asList;
import java.util.Collections;
import java.util.List;
import model.DataAccess;
import model.DataAccessException;
import model.Booking;

/**
 * Program that initializes the data store before running the test programs.
 *
 * @author Jean-Michel Busca
 */
public class DataStoreInit {

  //
  // CONSTANTS
  //
  /**
   * Number of available seats in the initial state.
   */
  public static final int SEAT_COUNT = 5;
  /**
   * Price list.
   */
  public static final List<Float> PRICE_LIST = asList(100.0f, 50.0f, 75.0f);

  /**
   * Runs the program. The data store is initialized twice to make sure that
   * {@link DataAccess#initDataStore} works as expected.
   *
   * @param args the command line arguments: URL, login, password
   *
   * @throws DataAccessException for convenience (no try-catch needed)
   */
  public static void main(String[] args) throws DataAccessException {

    // check parameters
    if (args.length == 2) {
      args = Arrays.copyOf(args, 3);
      args[2] = "";
    }
    if (args.length != 3) {
      System.err.println("usage: DataStoreInit <url> <login> <password>");
      System.exit(1);
    }

    // create dao
    System.out.print("connecting to " + args[0] + " as " + args[1]);
    DataAccess dao = new DataAccess(args[0], args[1], args[2]);
    System.out.println("\rconnected to " + args[0]);

    // initialize the data store
    int seats = 2;
    System.out.print("creating a database with " + seats + " seats...");
    System.out.println("\b\b\b: " + dao.initDataStore(seats, asList(50.0f)));
    System.out.println("available seats: " + dao.getAvailableSeats(false));

    // initialize the data store again with the final settings
    seats = SEAT_COUNT;
    System.out.print("creating a database with " + seats + " seats...");
    System.out.println("\b\b\b: " + dao.initDataStore(seats, PRICE_LIST));
    System.out.println("available seats: " + dao.getAvailableSeats(false));
    
    // Part I added myself for my own tests
    System.out.println("Book for Bob");
    List<Booking> bookings1 = dao.bookSeats("Bob", asList(1, 1, 1), true);
    List<Booking> bookings = dao.getBookings(null);
    for(Booking booking : bookings) {
        System.out.println(booking.toString());
    }
    System.out.println("Test with Jacques");
    bookings = dao.bookSeats("Jaques", asList(Collections.EMPTY_LIST, asList(4)));
    bookings = dao.getBookings(null);
    for(Booking booking : bookings) {
        System.out.println(booking.toString());
    }
    System.out.println("Cancel bookings ");
    boolean cancelled = dao.cancelBookings(bookings1);
    if(cancelled)
        System.out.println("Cancelation effective");
    bookings = dao.getBookings(null);
    for(Booking booking : bookings) {
        System.out.println(booking.toString());
    }
    

    // close dao
    dao.close();
    System.out.println("done.");

  }

  // prevent javadoc from documenting the default constructor
  private DataStoreInit() {

  }

}
