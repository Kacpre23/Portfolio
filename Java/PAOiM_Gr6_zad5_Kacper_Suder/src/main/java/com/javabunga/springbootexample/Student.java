package com.javabunga.springbootexample;

public class Student {
    private int id;
    public String imie;
    public String nazwisko;
    public String stanStudenta;

    public int rokUrodzenia;
    public double iloscPunktow;


    public Student(int id, String imie, String nazwisko, String stanStudenta, int rokUrodzenia, double iloscPunktow) {
        this.id = id;
        this.imie = imie.toUpperCase();
        this.nazwisko = nazwisko.toUpperCase();
        this.stanStudenta = stanStudenta;
        this.rokUrodzenia = rokUrodzenia;
        this.iloscPunktow = iloscPunktow;
    }

    public int getId() {
        return id;
    }

/*
    public void setId(int id) {
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
*/


    public static boolean compareTo(String daneDoPorownania, String daneWGrupach) { //zwraca true - jeśli zgadzają się i false, jeśli nie
        return daneDoPorownania.equals(daneWGrupach);
    }
}
