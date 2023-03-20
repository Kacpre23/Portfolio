package com.javabunga.springbootexample;//import java.util.Collections;

import javax.swing.*;
import java.util.Scanner;
import java.util.Vector;

import static java.lang.Math.abs;

public class Class  implements MyComperator {
    public String nazwaGrupy;
    public int maksymalnaIloscStudentow;
    Student blank = new Student("", "", "",000, 10.0);

    public Vector <Student> listaStudentow = new Vector<>(maksymalnaIloscStudentow);
    public Vector <Student> listaStudentowYear = new Vector<>(maksymalnaIloscStudentow);
    Scanner scan = new Scanner(System.in);

    public Vector<Student> getListaStudentow() {
        return listaStudentow;
    }
    public void setListaStudentow(Vector<Student> studenci)  { listaStudentow = studenci; }

    public int getSize() {
        return  listaStudentow.size();
    }
    public String getNazwaGrupy() {
        return nazwaGrupy;
    }
    public Class(){}

    public Class(String nazwaGrupy, int maksymalnaIloscStudentow, Vector<Student> listaStudentow) {
        this.nazwaGrupy = nazwaGrupy.toUpperCase();
        this.maksymalnaIloscStudentow = maksymalnaIloscStudentow;
        this.listaStudentow = listaStudentow;
        this.listaStudentowYear =  this.listaStudentow;
    }

    public Class(String nazwaGrupy, int maksymalnaIloscStudentow) {
        this.nazwaGrupy = nazwaGrupy;
        this.maksymalnaIloscStudentow = maksymalnaIloscStudentow;
    }


  void addPoints(Student student, double points) {
        student.iloscPunktow += points;
    }

    public void addStudent(String imie, String nazwisko, int rok) {
        if (maksymalnaIloscStudentow == listaStudentow.size()) {
            JOptionPane.showMessageDialog(null, "Osiągnięto limit grupy", "Błąd",JOptionPane.WARNING_MESSAGE);
            return;
        }

        Student adding = new Student(imie.toUpperCase(), nazwisko.toUpperCase(), "Nieokreslony", rok,  10.0);
            boolean help_surname = false;
            for (Student student : listaStudentow) {
                if (adding.nazwisko.equals(student.nazwisko)) {
                    help_surname = true;
                    JOptionPane.showMessageDialog(null, "Student o takim nazwisku znajduje sie juz w bazie!", "Błąd",JOptionPane.WARNING_MESSAGE);
                }
            }
            if (help_surname == false){
                listaStudentow.add(adding);
            }
    }

    public void addStudent(Student student) {
        listaStudentow.add(student);
        //System.out.print("\nPoprawnie dodano studenta\n");
    }
    public void addStudentYear(Student student) {
        listaStudentowYear.add(student);
        //System.out.print("\nPoprawnie dodano studenta\n");
    }


   public void changePoints(String surname, String wybor, double points) {
        for (Student student12 : listaStudentow) {
            if(student12.nazwisko.equals(surname)) {
                if(wybor.equals("Dodaj")) {
                    addPoints(student12, abs(points));
                } else {
                    removePoints(student12, abs(points));
                }
            }
        }
    }


    public double getStudentsNumber() {
        return listaStudentow.size();
    }

    public void getStudent(){

            for (int i = 0; i < listaStudentowYear.size(); i++) {
                if (listaStudentowYear.get(i).iloscPunktow <= 0)  {
                    JOptionPane.showMessageDialog(null, "Usunieto studenta o imieniu i nazwisku: " + listaStudentowYear.get(i).imie
                            + " " +listaStudentowYear.get(i).nazwisko, "Usuwanie", JOptionPane.WARNING_MESSAGE);
                    removeStudentYear(listaStudentowYear.get(i).nazwisko);
                }
            }


    }



public void removePoints(Student student, double points) {
       student.iloscPunktow -= points;
    }

    public void removeStudentYear(String personalData) {
        for (int i = 0; i < listaStudentowYear.size(); i++) {
            if (listaStudentowYear.get(i).nazwisko.equals(personalData)) {
                listaStudentowYear.removeElementAt(i);

            }
        }
        setListaStudentow(listaStudentowYear);
    }

   Student search(String surname) {
        for (Student student : listaStudentow) {
            if (Student.compareTo(surname, student.nazwisko)) return student;
        }
            System.err.print("Brak podanego studenta w grupie\n");
            System.out.print("\n");
            return null;
    }

    public void getSearchStudents(String personalData) {
        int pom = 0;
        boolean a = false;
        boolean b = false;
        Vector <Student> listaStudentowOgraniczona = new Vector<>(maksymalnaIloscStudentow);
        for (Student student : listaStudentowYear) {
            a = student.nazwisko.contains(personalData);
            b = student.imie.contains(personalData);
            if (a || b) {
                listaStudentowOgraniczona.add(student);
                    pom++;
            }
        }
        setListaStudentow(listaStudentowOgraniczona);
        if (pom == 0) {
            if (!personalData.equals("")) JOptionPane.showMessageDialog(null, "Brak studentow o takich danych", "Błąd", JOptionPane.WARNING_MESSAGE);
            setListaStudentow( listaStudentowYear);
        }
    }

    @Override
    public int compare(Student o1, Student o2) {
        return (-1)*Double.compare(o1.iloscPunktow, o2.iloscPunktow);
    }


 /*   void sortByName(){
        listaStudentow.sort(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.imie.compareTo(o2.imie);
            }
        });
    }*/

/*    public Vector<Student> sortByPoints(Vector<Student> unSort) {
        unSort.sort(this::compare);
        return unSort;
    }*/

   // @Override
   // public int compare(Student o1, Student o2) {
   //             return (-1)*Double.compare(o1.iloscPunktow, o2.iloscPunktow);
  //  }


   /* void max() {
        Student student = Collections.max(listaStudentow, new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return Double.compare(o1.iloscPunktow, o2.iloscPunktow);
            }
        });
        System.out.println(student.iloscPunktow);
        System.out.print("\nNajwieksza ilosc to: " + student.iloscPunktow);
        }*/
    /*public void summary() {
        System.out.print("\nNazwa grupy: " + nazwaGrupy);
        for (Student student : listaStudentow) { //wykonuje tyle ile jest studentow w liscie
            student.print();
        }
    }*/


}
