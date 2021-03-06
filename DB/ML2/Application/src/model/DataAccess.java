package model;

import java.sql.Connection;
import java.sql.DriverManager; // Necessary to make connection to DB
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.ListIterator;

/**
 * Provides a generic booking application with high-level methods to access its
 * data store, where the booking information is persisted. The class also hides
 * to the application the implementation of the data store (whether a Relational
 * DBMS, XML files, Excel sheets, etc.) and the complex machinery required to
 * access it (SQL statements, XQuery calls, specific API, etc.).
 * <p>
 * The booking information includes:
 * <ul>
 * <li> A collection of seats (whether theater seats, plane seats, etc.)
 * available for booking. Each seat is uniquely identified by a number in the
 * range {@code [1, seatCount]}. For the sake of simplicity, there is no notion
 * of row and column, as in a theater or a plane: seats are considered
 * <i>adjoining</i> if they bear consecutive numbers.
 * <li> A price list including various categories. For the sake of simplicity,
 * (a) the price of a seat only depends on the customer, e.g. adult, child,
 * retired, etc., not on the location of the seat as in a theater, (b) each
 * price category is uniquely identified by an integer in the range
 * {@code [0, categoryCount)}, e.g. {@code 0}=adult, {@code 1}=child,
 * {@code 2}=retired. (Strings or symbolic constants, like Java {@code enum}s,
 * are not used.)
 * </ul>
 * <p>
 * A typical booking scenario involves the following steps:
 * <ol>
 * <li> The customer books one or more seats, specifying the number of seats
 * requested in each price category with
 * {@link #bookSeats(String, List, boolean)}. He/She lets the system select the
 * seats to book from the currently-available seats.
 * <li> Alternatively, the customer can check the currently-available seats with
 * {@link #getAvailableSeats(boolean)} and then specify the number of the seats
 * he/she wants to book in each price category with
 * {@link #bookSeats(String, List)}.
 * <li> Later on, the customer can change his/her mind and cancel with
 * {@link #cancelBookings(List)} one or more of the bookings he/she previously
 * made.
 * <li> At any time, the customer can check the bookings he/she currently has
 * with {@link #getBookings(String)}.
 * <li> The customer can repeat the above steps any number of times.
 * </ol>
 * <p>
 * The constructor and the methods of this class all throw a
 * {@link DataAccessException} when an unrecoverable error occurs, e.g. the
 * connection to the data store is lost. The methods of this class never return
 * {@code null}. If the return type of a method is {@code List<Item>} and there
 * is no item to return, the method returns the empty list rather than
 * {@code null}.
 * <p>
 * <i>Notes to implementors: </i>
 * <ol>
 * <li> <b>Do not</b> modify the interface of the classes in the {@code model}
 * package. If you do so, the test programs will not compile. Also, remember
 * that the exceptions that a method throws are part of the method's interface.
 * <li> The test programs will abort whenever a {@code DataAccessException} is
 * thrown: make sure your code throws a {@code DataAccessException} only when a
 * severe (i.e. unrecoverable) error occurs.
 * <li> {@code JDBC} often reports constraint violations by throwing an
 * {@code SQLException}: if a constraint violation is intended, make sure your
 * your code does not report it as a {@code DataAccessException}.
 * <li> The implementation of this class must withstand failures (whether
 * client, network of server failures) as well as concurrent accesses to the
 * data store through multiple {@code DataAccess} objects.
 * </ol>
 *
 * @author Jean-Michel Busca
 */
public class DataAccess implements AutoCloseable {

  private Connection connection;

  /**
   * Creates a new {@code DataAccess} object that interacts with the specified
   * data store, using the specified login and the specified password. Each
   * object maintains a dedicated connection to the data store until the
   * {@link close} method is called.
   *
   * @param url the URL of the data store to connect to
   * @param login the (application) login to use
   * @param password the password
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public DataAccess(String url, String login, String password) throws
      DataAccessException {
    // TODO
    // Open an sql connection using provided url, login and password
    try {
        connection = DriverManager.getConnection(url, login, password);
    } catch (SQLException e) {
        throw new DataAccessException(e);
    }
  }

  /**
   * Initializes the data store according to the specified number of seats and
   * the specified price list. If the data store is already initialized or if it
   * already contains bookings when this method is called, it is reset and
   * initialized again from scratch. When the method completes, the state of the
   * data store is as follows: all the seats are available for booking, no
   * booking is made.
   * <p>
   * <i>Note to implementors: </i>
   * <ol>
   * <li>All the information provided by the parameters must be persisted in the
   * data store. (It must not be kept in Java instance or class attributes.) To
   * enforce this, the data store will be initialized by running the
   * {@code DataStoreInit} program, and then tested by running the
   * {@code SingleUserTest} and {@code MultiUserTest} programs.
   * <li><b>Do not use</b> the statements {@code drop database ...} and
   * {@code create database ...} in this method, as the test program might not
   * have sufficient privileges to execute them. Use the statements {@code drop table
   * ...} and {@code create table ...} instead.
   * <li>The schema of the database (in the sense of "set of tables") is left
   * unspecified. You can select any schema that fulfills the requirements of
   * the {@code DataAccess} methods.
   * </ol>
   *
   * @param seatCount the total number of seats available for booking
   * @param priceList the price for each price category
   *
   * @return {@code true} if the data store was initialized successfully and
   * {@code false} otherwise
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public boolean initDataStore(int seatCount, List<Float> priceList)
      throws DataAccessException {
    
    // TODO
    /*
    Scheme used for the database :
    table Bookings
        seatNumber : int
        customerName : String
        priceCategory : int
        
        If customerName is null, then the seat is free to be
        booked
        The priceCategories are initiated to -1
    
    table priceList
        ID : int
        price : float
    
        * numeros 0-x are price categories.
    */
    String query = null;
    try {
        Statement statement = connection.createStatement();
    
        // We start by dropping all of the tables to reinit the database
        try {

            statement.executeUpdate("drop table Seats;");
            statement.executeUpdate("drop table priceList;");
        } catch (SQLException e) {
            System.err.print("Failed to drop the tables ");
            System.err.println(", going on...");
        }
        // Create the tables
        // Table Bookings
        statement.executeUpdate("CREATE TABLE Seats ("
                + "seatN int, "
                + "customer varchar(255), "
                + "priceCategory int );");
        // Table data
        statement.executeUpdate("CREATE TABLE priceList("
                + "ID int, "
                + "price float);");
        
        PreparedStatement insertion = connection.prepareStatement(
            "INSERT INTO priceList (ID, price) VALUES (?, ?);");
     
        // Insertion of the price categories
        for(int i=0; i < priceList.size(); i++) {
            insertion.setInt(1, i);
            insertion.setFloat(2, priceList.get(i));
            insertion.executeUpdate();
        }
        
        insertion = connection.prepareStatement(
            "INSERT INTO Seats(seatN, customer, priceCategory) "
                    + "VALUES (?, ?, ?);");
        // At the start, none of the seats are booked
        insertion.setString(2, null);
        insertion.setInt(3, -1);
        
        for(int i=1; i <= seatCount; i++) {
            insertion.setInt(1, i);
            insertion.executeUpdate();
        }
        
        return true;
    } catch (SQLException e) {
        System.err.println(query + ": " + e);
        return false;
    }
  }

  /**
   * Returns the price list.
   * <p>
   * <i>Note to implementors: </i>  <br> The method must return the price list
   * persisted in the data store.
   *
   * @return the price list
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public List<Float> getPriceList() throws DataAccessException {
    // TODO
    String query = "SELECT * FROM priceList";
    List<Float> priceList = new ArrayList<>();
    
    try {
        Statement statement = connection.createStatement();
        try {
            ResultSet queryResult = statement.executeQuery(query);
            
            // Interpretation of the results
            while(queryResult.next()) {
                priceList.add(queryResult.getFloat(2));
            }
        } catch(SQLException e) {
            System.err.print("Problem with " + query + ", " + e);
            return Collections.EMPTY_LIST; // Java equivalent of return false
                                           // for an empty list
        }
    
        return priceList;
    } catch(SQLException e) {
        throw new DataAccessException(e);
    }
  }

  /**
   * Returns the available seats in the specified mode. Two modes are provided:
   * <i>stable</i> or not. If the stable mode is selected, the returned seats
   * are guaranteed to remain available until one of the {@code bookSeats}
   * methods is called on this data access object. If the stable mode is not
   * selected, the returned seats might have been booked by another user when
   * one of these methods is called. Regardless of the mode, the available seats
   * are returned in ascending order of number.
   * <p>
   * <i>Note to implementors: </i> <br> The stable mode is defined as an
   * exercise. It cannot be used in a production application as this would
   * prevent all other users from retrieving the available seats until the
   * current user decides which seats to book.
   *
   * @param stable {@code true} to select the stable mode and {@code false}
   * otherwise
   *
   * @return the available seats in ascending order or the empty list if no seat
   * is available
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public List<Integer> getAvailableSeats(boolean stable) throws
      DataAccessException {
    // TODO
    /*
    This is a simple read query with a singular condition.
    
    However we need to lock the database if stable is used
    */
    String query = "SELECT * FROM Seats WHERE customer IS NULL";
    List<Integer> availableSeats = new ArrayList<>();
    
    try {
        Statement statement = connection.createStatement();
        
        try {
            // Start a transaction if we gave stable
            if(stable) {
                connection.setAutoCommit(false);
            }
            ResultSet queryResult = statement.executeQuery(query);
            
            // We put the result into the output List
            while(queryResult.next()) {
                availableSeats.add(queryResult.getInt(1));
            }
            
            return availableSeats;
        } catch(SQLException e) {
            System.err.print("Problem with " + query + ", " + e);
            return Collections.EMPTY_LIST;
        }
    } catch(SQLException e) {
        throw new DataAccessException(e);
    }
  }

  /**
   * Books the specified number of seats for the specified customer in the
   * specified mode. The number of seats to book is specified for each price
   * category. Two modes are provided: <i>adjoining</i> or not. If the adjoining
   * mode is selected, the method guarantees that the booked seats are
   * adjoining. If the adjoining mode is not selected, the returned seats might
   * be apart. Regardless of the mode, the bookings are returned in ascending
   * order of seat number.
   * <p>
   * If the specified customer already has bookings, the adjoining mode only
   * applies to the new bookings: The method will not try to select seats
   * adjoining to already-booked seats by the same customer.
   * <p>
   * The method executes in an all-or-nothing fashion: if there are not enough
   * available seats left or if the seats are not adjoining while the adjoining
   * mode is selected, then no seat is booked.
   *
   * @param customer the customer who makes the booking
   * @param counts the count of seats to book for each price category:
   * counts.get(i) is the count of seats to book in category #i
   * @param adjoining {@code true} to select the adjoining mode and
   * {@code false} otherwise
   *
   * @return the list of bookings if the booking was successful or the empty
   * list otherwise
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public List<Booking> bookSeats(String customer, List<Integer> counts,
      boolean adjoining) throws DataAccessException {
    // TODO
    // We loog for all the seats we want to reserve, and we create bookings
    // accordingly
    List<Booking>  bookingsMade = generateBookings(counts, adjoining, customer);
    
    // Now we just need to modify the database to inlcude the seats reserved this
    // way
    try {
        PreparedStatement update = connection.prepareStatement(
                "UPDATE Seats "
                + "SET customer = ?, priceCategory = ? "
                + "WHERE seatN = ?;");
        
        update.setString(1, customer);
        for(Booking booking : bookingsMade) {
            update.setInt(2, booking.getCategory());
            update.setInt(3, booking.getSeat());
            update.executeUpdate();
        }
        
        // Once we have updated all of the seats, we commit the transaction
        connection.setAutoCommit(true);
        
        return bookingsMade;
    } 
    catch(SQLException e) {
        System.err.print("Problem with seat booking" + ", " + e);
        return Collections.EMPTY_LIST;
    }
  }

  /**
   * Books the specified seats for the specified customer. The seats to book are
   * specified for each price category.
   * <p>
   * The method executes in an all-or-nothing fashion: if one of the specified
   * seats cannot be booked because it is not available, then none of them is
   * booked.
   *
   * @param customer the customer who makes the booking
   * @param seatss the list of seats to book in each price category:
   * seatss.get(i) is the list of seats to book in category #i
   *
   * @return the list of the bookings made by this method call or the empty list
   * if no booking was made
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public List<Booking> bookSeats(String customer, List<List<Integer>> seatss)
      throws DataAccessException {
    // TODO
    // Return value
    List<Booking> bookedSeats = new ArrayList<>();
    
    try {
        connection.setAutoCommit(false);
        // We get the list of prices
        List<Float> priceList = getPriceList();
        
        int updateResult;
       
        // This statement will only execute if it is on a seat that is empty
        PreparedStatement update = connection.prepareStatement(
                "UPDATE Seats "
                    + "SET customer = ?, priceCategory = ? "
                    + "WHERE seatN = ? AND customer IS NULL");
        update.setString(1, customer);
        // We loop through the list of seats. First loop is categories
        for(int categ=0; categ < seatss.size(); categ++) {
            // Second row is seat number
            for(int seat : seatss.get(categ)) {
                update.setInt(2, categ);
                update.setInt(3, seat);
                if(update.executeUpdate() == 0) {
                    // If the update didn't affect any seat, it means the seat
                    // was already taken, and we need to roll back the changes
                    System.err.println("Seat " + seat + " was already taken.");
                    System.err.println("Rolling back booking...");
                    connection.rollback();
                    connection.setAutoCommit(true);
                    return Collections.EMPTY_LIST;
                }
                
                Booking booking = new Booking(seat, customer, categ, priceList.get(categ));
                bookedSeats.add(booking);
            }
        }
        
        connection.setAutoCommit(true);
        return bookedSeats;
    } catch(SQLException e) {
        System.err.println("Could not finish booking. Aborting...");
        System.err.println(e);
        try {
            connection.rollback();
            connection.setAutoCommit(true);
        } catch(SQLException f) {
            throw new DataAccessException(f);
        }
        return Collections.EMPTY_LIST;
    }
  }

  /**
   * Returns the current bookings of the specified customer. If no customer is
   * specified, the method returns the current bookings of all the customers.
   *
   * @param customer the customer whose bookings must be returned or the empty
   * string {@code ""} if all the bookings must be returned
   *
   * @return the list of the bookings of the specified customer or the empty
   * list if the specified customer does not have any booking
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public List<Booking> getBookings(String customer) throws DataAccessException {
    // TODO
    // Return variable
    List<Booking> bookedSeats = new ArrayList<>();
    List<Float> priceList = getPriceList();
    
    try {
        // We use a prepared statement to help protect against SQL injections
        PreparedStatement statement;
        if(customer != null){
            statement = connection.prepareStatement(
                    "SELECT seatN, customer, priceCategory FROM Seats "
                        + "WHERE customer = ?");
            
            statement.setString(1, customer);
        } else {
            statement = connection.prepareStatement(
                    "SELECT seatN, customer, priceCategory FROM Seats "
                        + "WHERE customer IS NOT NULL");
        }
        // Execute the query and gain access to its result
        ResultSet resultSet = statement.executeQuery();
        
        // Loop through the results to add them to our 
        while(resultSet.next()) {
            Booking booking = new Booking(resultSet.getInt(1),
                    resultSet.getString(2), resultSet.getInt(3),
                    priceList.get(resultSet.getInt(3)));
            
            bookedSeats.add(booking);
        }
        
        return bookedSeats;
    } catch(SQLException e) {
        System.err.println("Problem with SQL query for bookings");
        return Collections.EMPTY_LIST;
    }
  }

  /**
   * Cancel the specified bookings. The method checks against the data store
   * that each of the specified bookings is valid, i.e. it is assigned to the
   * specified customer, for the specified price category.
   * <p>
   * The method executes in an all-or-nothing fashion: if one of the specified
   * bookings cannot be canceled because it is not valid, then none of them is
   * canceled.
   *
   * @param bookings the bookings to cancel
   *
   * @return {@code true} if all the bookings were canceled and {@code false}
   * otherwise
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  public boolean cancelBookings(List<Booking> bookings) throws DataAccessException {
    // TODO
    try {
        connection.setAutoCommit(false);
        PreparedStatement statement = connection.prepareStatement(
                "UPDATE Seats "
                    + "SET customer = NULL, priceCategory = -1 "
                    + "WHERE customer = ? AND seatN = ?");
        
        for(Booking booking : bookings) {
            statement.setString(1, booking.getCustomer());
            statement.setInt(2, booking.getSeat());
            
            // Make sure the update has an effect
            if(statement.executeUpdate() == 0) {
                System.err.println("One of the booking provided is invalid");
                System.err.println("Rolling back...");
                connection.rollback();
                connection.setAutoCommit(true);
                return false;
            }
        }
        // We finished looping through the list without mistake, so we commit and return
        connection.setAutoCommit(true);
        return true;
        
    } catch(SQLException e) {
        System.err.println("Problem while trying to delete bookings.");
        System.err.println(e);
        System.err.println("Aborting...");
        
        try {
            connection.setAutoCommit(true);
        } catch(SQLException f) {
            throw new DataAccessException(f);
        }
        return false;
    }
  }

  /**
   * Closes this data access object. This closes the underlying connection to
   * the data store and releases all related resources. The application must
   * call this method when it is done using this data access object.
   *
   * @throws DataAccessException if an unrecoverable error occurs
   */
  @Override
  public void close() throws DataAccessException {
    // TODO
    try {
        connection.close();
    } catch(SQLException e) {
        throw new DataAccessException("Could not properly close the connection " + e);
    } 
  }
  
    private List<Booking> generateBookings(
            List<Integer> counts, boolean adjoining, String customer) 
            throws DataAccessException {
        // Return variable
        List<Booking> bookingList = new ArrayList<>();
        
        // Find the total number of seats we need
        int total = 0;
        for(int i : counts) {
            total += i;
        }
        
        /* Get the list of prices */
        List<Float> priceList = getPriceList();
        System.out.print("List of prices : ");
        for(Float price : priceList) {
            System.out.print(price + " ");
        }
        /* Get a list of free seats */
        List<Integer> availableSeats = getAvailableSeats(true);

        List<Integer> seatList = new ArrayList<>();
        for(int available : availableSeats) {
            // We loop through the possible seats
            // If we are looking for adjoining seats, we must discard the list
            // if this new seat is not adjoining
            if(seatList.size() >= 1){
                if(available > seatList.get(seatList.size() - 1) + 1 && adjoining) {
                seatList.clear();
                }
            }
            seatList.add(available);
        }
        // We check the list is big enough
        if(seatList.size() < total) {
            System.err.print("There was not enough seats available to satisfy the demand");
            System.err.println("Operation aborted ");
            return Collections.EMPTY_LIST;
        }

        // Generate a list of bookings for the seat list that we made
        ListIterator seat = seatList.listIterator(0);
        for(int categ = 0; categ < counts.size(); categ++) {
            for(int i=0; i < counts.get(categ); i++) {
                Booking booking = new Booking((int)seat.next(), customer, categ, priceList.get(categ));
                bookingList.add(booking);
            }
        }
            
        
        
        return bookingList;
    }
}
