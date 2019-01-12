/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import static java.lang.annotation.RetentionPolicy.*;
import java.lang.annotation.Target;

/**
 *
 * @author korax
 */
@Target(ElementType.METHOD)
@Retention(value=RUNTIME)
public @interface TestSpec {
    int testName();
}
