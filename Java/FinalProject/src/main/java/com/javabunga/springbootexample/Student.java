package com.javabunga.springbootexample;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    private Long id;
    public String imie;
    public String nazwisko;
    public String stanStudenta;

    public int rokUrodzenia;
    public double iloscPunktow;


    // avoid this "No default constructor for entity"
    public Student() {
    }

    public Student(Long id, String imie, String nazwisko, String stanStudenta, int rokUrodzenia, double iloscPunktow) {
        this.id = id;
        this.imie = imie.toUpperCase();
        this.nazwisko = nazwisko.toUpperCase();
        this.stanStudenta = stanStudenta;
        this.rokUrodzenia = rokUrodzenia;
        this.iloscPunktow = iloscPunktow;
    }

    public Student(String imie, String nazwisko, String stanStudenta, int rokUrodzenia, double iloscPunktow) {
        this.imie = imie.toUpperCase();
        this.nazwisko = nazwisko.toUpperCase();
        this.stanStudenta = stanStudenta;
        this.rokUrodzenia = rokUrodzenia;
        this.iloscPunktow = iloscPunktow;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return imie;
    }

    public void setName(String name) {
        this.imie = name;
    }

    public String getSurname() {
        return nazwisko;
    }

    public void setSurname(String surname) {
        this.nazwisko = surname;
    }

    public void setYear(int year) {
        this.rokUrodzenia = year;
    }
    public int getYear() {
        return rokUrodzenia;
    }
    public double getPoints() {
        return iloscPunktow;
    }

    public void setPoints(double points) {
        this.iloscPunktow = points;
    }


    public static boolean compareTo(String daneDoPorownania, String daneWGrupach) { //zwraca true - jeśli zgadzają się i false, jeśli nie
        return daneDoPorownania.equals(daneWGrupach);
    }
}
