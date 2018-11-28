package model;

import java.util.Objects;

/**
 * A booking for a seat. The information stored in a booking object includes the
 * number of the booked seat, the customer who made the booking, the price
 * category and the price of the booking.
 * <p>
 * To favor code safety, booking objects are immutable: all field values are
 * specified at construction time and cannot be modified later on.
 * <p>
 * <i>Note to {@code DataAccess} implementors: </i> <br>
 * As an option, a booking can be identified by an ID - a positive {@code int}
 * value - specified at construction time. It is the responsibility of the
 * caller to ensure that IDs are unique across all bookings. If you use this
 * feature, make sure <b>all</b> {@code Booking} objects have an ID:
 * {@code Booking} objects with and without an ID cannot be mixed.
 *
 * @author Jean-Michel Busca
 */
public class Booking {

  //
  // INSTANCE FIELDS
  //
  private final int id;

  private final int seat;
  private final String customer;
  private final int category;
  private final float price;

  //
  // CONSTRUCTORS
  //
  /**
   * Constructs a new booking object with the specified ID, seat, customer,
   * category and price.
   *
   * @param id the unique ID of the booking
   * @param seat the booked seat
   * @param customer the customer who made the booking
   * @param category the price category
   * @param price the price
   */
  public Booking(int id, int seat, String customer, int category, float price) {
    if (id < 0) {
      throw new IllegalArgumentException("id cannot be negative");
    }
    this.id = id;
    this.seat = seat;
    this.customer = customer;
    this.category = category;
    this.price = price;
  }

  /**
   * Constructs a new booking object with the specified seat, customer,
   * category, price and an ID set to {@code -1}.
   *
   * @param seat the booked seat
   * @param customer the customer who made the booking
   * @param category the price category
   * @param price the price
   */
  public Booking(int seat, String customer, int category, float price) {
    this.id = -1;
    this.seat = seat;
    this.customer = customer;
    this.category = category;
    this.price = price;
  }

  private void init() {

  }

//
  // GETTERS
  //
  @Override
  public String toString() {
    // ID is used
    if (id >= 0) {
      return "Booking{" + "id=" + id + ", seat #" + seat + ", " + customer
          + ", category #" + category + ", $" + price + '}';
    }
    // ID i not used
    return "Booking{seat #" + seat + ", " + customer
        + ", category #" + category + ", $" + price + '}';
  }

  /**
   * Returns the ID of the booking.
   *
   * @return the ID of the booking
   */
  public int getId() {
    return id;
  }

  /**
   * Returns the booked seat.
   *
   * @return the booked seat
   */
  public int getSeat() {
    return seat;
  }

  /**
   * Returns the customer who made the booking.
   *
   * @return the customer who made the booking
   */
  public String getCustomer() {
    return customer;
  }

  /**
   * Returns the price category of the booking.
   *
   * @return the price category of the booking
   */
  public int getCategory() {
    return category;
  }

  /**
   * Returns the price of the booking.
   *
   * @return the price of the booking
   */
  public float getPrice() {
    return price;
  }

  //
  // IDENTITY
  //
  @Override
  public int hashCode() {
    // ID is used
    if (id >= 0) {
      int hash = 3;
      hash = 23 * hash + this.id;
      return hash;
    }
    // ID is not used
    int hash = 7;
    hash = 29 * hash + this.seat;
    hash = 29 * hash + Objects.hashCode(this.customer);
    hash = 29 * hash + this.category;
    hash = 29 * hash + Float.floatToIntBits(this.price);
    return hash;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) {
      return true;
    }
    if (obj == null) {
      return false;
    }
    if (getClass() != obj.getClass()) {
      return false;
    }
    final Booking other = (Booking) obj;
    // check that both objects have the same ID policy
    if (id < 0 && other.id >= 0 || id >= 0 && other.id < 0) {
      throw new RuntimeException("Booking: cannot mix ID policies");
    }
    // ID is used
    if (id >= 0) {
      if (this.id != other.id) {
        return false;
      }
      return true;
    }
    // ID is not used
    if (this.seat != other.seat) {
      return false;
    }
    if (this.category != other.category) {
      return false;
    }
    if (Float.floatToIntBits(this.price) != Float.floatToIntBits(other.price)) {
      return false;
    }
    if (!Objects.equals(this.customer, other.customer)) {
      return false;
    }
    return true;
  }

}
