package com.javabunga.springbootexample.error;

public class StudentNotFoundException extends RuntimeException {

    public StudentNotFoundException() {
        super("Studentow nie znaleziono : " + "\n ERROR: 404");
    }

}
