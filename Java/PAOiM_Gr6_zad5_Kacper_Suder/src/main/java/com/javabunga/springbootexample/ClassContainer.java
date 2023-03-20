package com.javabunga.springbootexample;


import javax.swing.*;
import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ClassContainer {
    public Map<String, Class> wszystkiegrupy = new HashMap<>();
   public Map<String, Class> grupy = new HashMap<>();
    public Map<String, Class> pomocWyszukajGrupe = new HashMap<>();

    Student student = new Student(0, "Imie", "Nazwisko", "Aktywny", 0000,10.0);
    public ClassContainer(Map<String, Class> grupy) {
        this.grupy = grupy;
        this.wszystkiegrupy = this.grupy;
    }

    public Map<String, Class> addClass(String nazwa, int ilosc, Vector<Student> listaStudentow) {
        grupy.put(nazwa, new Class(nazwa, ilosc, listaStudentow));
        setGrupa(grupy);
        return grupy;
    }

    public Map<String, Class> addClass(Class newclass) {
        grupy.put(newclass.nazwaGrupy.toUpperCase(), newclass);
        setGrupa(grupy);
        return grupy;
    }

    public Class getClass(String nazwa) {
        for(Class grupa : grupy.values()) {
            if (grupa.nazwaGrupy.equals(nazwa)) {
                return grupa;
              }
        }
        return null;
    }

    public Class getClass2() {
        for(Class grupa : grupy.values()) {
            return grupa;
        }
        return null;
    }
    public Class getClass2(String nazwa) {
        for(Class grupa : grupy.values()) {
            if (grupa.nazwaGrupy.equals(nazwa)) {
                return grupa;
            }
        }
        grupy.put(nazwa, new Class(nazwa, 10, new Vector<>()));
        for(Class grupa : grupy.values()) {
            if (grupa.nazwaGrupy.equals(nazwa)) {
                return grupa;
            }
        }
        return null;
    }

    public Class getClass2(String nazwa, int rozmiar) {
        for(Class grupa : grupy.values()) {
            if (grupa.nazwaGrupy.equals(nazwa)) {
                return grupa;
            }
        }
        grupy.put(nazwa, new Class(nazwa, rozmiar, new Vector<>()));
        for(Class grupa : grupy.values()) {
            if (grupa.nazwaGrupy.equals(nazwa)) {
                return grupa;
            }
        }
        return null;
    }
    public String percentOfGroup(String nazwa) {
        pomocWyszukajGrupe.clear();
        String a = "false";
        for(Class grupa : wszystkiegrupy.values()) {
            if (grupa.nazwaGrupy.contains(nazwa)) {
                String percent;
                percent = (double)grupa.listaStudentowYear.size()/(grupa.maksymalnaIloscStudentow) * 100 + "%";
                a = percent;
                return percent;

            }
        }
        return a;
    }
    public  Map<String, Class> getSearchClass(String nazwa) {
        pomocWyszukajGrupe.clear();
        boolean a = false;
        for(Class grupa : wszystkiegrupy.values()) {
            if (grupa.nazwaGrupy.contains(nazwa)) {
                pomocWyszukajGrupe.put(grupa.nazwaGrupy, new Class(grupa.nazwaGrupy, grupa.maksymalnaIloscStudentow, grupa.listaStudentow));
                a = true;
            }
        }
        if (a == true)  {
            setGrupa(pomocWyszukajGrupe);
            return grupy;
        } else {
           return null;
        }
    }



    public Map<String, Class> removeClass(String nazwaGrupy) {
            int pom = grupy.size();
            grupy.remove(nazwaGrupy);
            if (pom == grupy.size()) return null;
            setGrupa(grupy);
            wszystkiegrupy = grupy;
            return grupy;
    }
    void setGrupa( Map<String, Class> nowaGrupa) {
        grupy = nowaGrupa;
    }

   void findEmpty() {
            Vector<Class> listaStudentow = new Vector<>();
           for(Class grupa : grupy.values()) {
                if(grupa.getSize()==0){
                    System.out.println("Grupa: " + grupa.nazwaGrupy + " jest pusta\n");
              }
        }
    }

    void pomoc() {
        System.out.print(grupy.values());
    }
  /*  void summary() {
        for (Class grupa : grupy.values()) {
            System.out.print("\nNazwa grupy to: " + grupa.nazwaGrupy +  "\tProcentowe zapelnienie: "
                    + (((float)grupa.getSize()/(float)grupa.maksymalnaIloscStudentow) * 100) + "%");
            grupa.summary();
        }
    }*/


}
