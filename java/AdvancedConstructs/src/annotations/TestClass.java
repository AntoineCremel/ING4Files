package annotations;

import java.util.List;

/**
 *
 * @author Jean-Michel Busca
 */

public class TestClass<E extends Comparable<E>> {

  private final Object[] elements;
  private int size;

  public static void main(){
      TestClass<Integer> intSequence = new TestClass<>();
      TestClass<Integer> intSequence2 = new TestClass<>();
      
      intSequence.add(1);
      intSequence2.add(2);
      System.out.println(intSequence.compareTo(intSequence2));
  }
  
  public TestClass() {
    elements = new Object[100];
    size = 0;
  }

  public void add(E element) {
    if (size >= elements.length) {
      throw new IllegalStateException();
    }
    elements[size] = element;
    size += 1;
  }

  public boolean remove(E element) {
    int i = 0;
    while (i < size && !elements[i].equals(element)) {
      i += 1;
    }
    if (i >= size) {
      return false;
    }
    size -= 1;
    while (i < size) {
      elements[i] = elements[i + 1];
    }
    return true;
  }

  public E get(int index) {
    if (index < 0 || index >= size) {
      throw new IllegalArgumentException();
    }
    return (E)elements[index];
  }
  
  public int compareTo(TestClass toCompare) {
      return elements[0].compareTo(toCompare.get(0));
  }
  
  public boolean removeAll(List<Object> toRemove){
      for (Object toRemove1 : toRemove) {
          for(int i=0; i < size; i++){
              if(toRemove1 == elements[i]){
                  elements[i] = null;
              }
          }
      }
      
      return true;
  }

}