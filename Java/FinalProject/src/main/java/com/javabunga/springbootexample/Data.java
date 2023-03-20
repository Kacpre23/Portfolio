package com.javabunga.springbootexample;

import java.util.*;

public class Data {

     public Map<String, Class> grupy = new HashMap<>();
    public Map<String, Class> pomocnaGrupa = new HashMap<>();
    Map<String, Class> grupyYear = new HashMap<>();
     Vector<Student> listaStudentow2 = new Vector<>();
     ClassContainer pom = new ClassContainer(grupy);
    ClassContainer year = new ClassContainer(grupyYear);
    public Data() {
        getSomeRandomData();
        getSomeRandomDataYear();
    }
    public Data(String choose) {
        if (choose.equals("year")) getSomeRandomDataYear();
            getSomeRandomData();
    }
     void getSomeRandomData(){
        Student student = new Student("Jan", "Kowalski", "Nieokreslony",2003,  10.0);
        Student student2 = new Student("Kacper", "Suder", "Nieokreslony",2001,  10.0);
        Student student3 = new Student("Kamil", "Nowak", "Nieokreslony",2001,  10.0);
        Student student4 = new Student("Joanna", "Wozniak", "Nieokreslony",2001, 10.0);
        Student student5 = new Student("Weronika", "Poradzisz", "Nieokreslony",2001, 10.0);
        Student student6 = new Student("Adam", "Skowronek", "Nieokreslony",2001,  10.0);
        Class First = new Class("Pierwsza",6, new Vector<>());
        Class second = new Class("Druga",3,  new Vector<>());

        First.addStudent(student);
        First.addStudent(student2);
        First.addStudent(student3);
        First.addStudent(student4);

        second.addStudent(student5);
        second.addStudent(student6);

         pom.addClass(First.nazwaGrupy, First.maksymalnaIloscStudentow, First.listaStudentow);
         pom.addClass(second.nazwaGrupy, second.maksymalnaIloscStudentow ,second.listaStudentow);

    }

    void getSomeRandomDataYear() {
        Student student = new Student("Jan", "Kowalski", "Aktywny",2003, 10.0);
        Student student2 = new Student("Kacper", "Suder", "Aktywny",2001,  10.0);
        Student student3 = new Student("Kamil", "Nowak", "Aktywny",2001,  10.0);
        Student student4 = new Student("Joanna", "Wozniak", "Aktywny",2001,  10.0);
        Student student5 = new Student("Weronika", "Poradzisz", "Aktywny",2001, 10.0);
        Student student6 = new Student("Adam", "Skowronek", "Aktywny",2001,  10.0);

        Class Year = new Class("Rok",20,  new Vector<>());

        Year.addStudent(student);
        Year.addStudent(student2);
        Year.addStudent(student3);
        Year.addStudent(student4);
        Year.addStudent(student5);
        Year.addStudent(student6);

        year.addClass(Year.nazwaGrupy, 20, Year.listaStudentow);
    }


    public ClassContainer returnClassConteiner() {
        return pom;
    }

    public ClassContainer returnYearConteiner() {
        return year;
    }

    public ArrayList <String> getAllTable() {
         ArrayList<String> pomocna = new ArrayList<>();
        for (Class grupa : grupy.values()) {
            pomocna.add(grupa.nazwaGrupy);

        }
        return pomocna;
    }


    public void changePointsYear(String surname, String opera, double points) {
        year.getClass2().changePoints(surname, opera, points);
    }
    public void changePoints(String classa, String surname, String opera, double points) {
        pom.getClass2(classa).changePoints(surname, opera, points);
    }
   public void deleteClass(String className){
         pom.removeClass(className);

    }

    public void addClass(String className, int max) {
        pom.addClass(className, max, listaStudentow2);
        pomocnaGrupa = grupy;
    }

    public void deleteStudentYear(String surname) {
        year.getClass2().removeStudentYear(surname);
    }

    public void deleteStudent(String groupChoose,String surname) {
        pom.getClass2(groupChoose).removeStudentYear(surname);
    }
    public void getMinusYear() {
        year.getClass2().getStudent();
    }
    public void getMinus(String className) {
        pom.getClass2(className).getStudent();
    }
    public void searchClass(String className) {
        pom.getSearchClass(className);
    }
    public void searchPartialYear(String studentName ) {
        year.getClass2().getSearchStudents(studentName);
    }
    public void searchPartial2(String nazwaGrupy, String studentName ) {
        pom.getClass2(nazwaGrupy).getSearchStudents(studentName);
    }




   public int compare(Student o1, Student o2) {
        return (-1)*Double.compare(o1.iloscPunktow, o2.iloscPunktow);
    }


    void sortName(String className) {
        Vector <Student> group = pom.getClass(className).getListaStudentow();
    }

    public Vector<Student> searchPartial(String search, String className) {
        Vector<Student> studenci = new Vector<Student>();
        Vector <Student> group = pom.getClass(className).getListaStudentow();
        boolean a = false;
        boolean b = false;
        for (Student student : group) {
            a = student.nazwisko.contains(search);
            b = student.imie.contains(search);
            if (a == true || b == true) {
                studenci.add(student);
            }
        }
        return studenci;
    }
}

