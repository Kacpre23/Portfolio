package ui.data;

import ui.logic.*;
import ui.logic.Class;

import java.util.*;

public class Data {

     public Map<String, Class> grupy = new HashMap<>();
    public Map<String, Class> pomocnaGrupa = new HashMap<>();
    Map<String, Class> grupyYear = new HashMap<>();
     Vector<Student> listaStudentow2 = new Vector<>();

     //Vector<Student> listaStudentowNaRoku = new Vector<>();
    Vector <Student> listaStudentowOgraniczona = new Vector<>();

    Scanner scan = new Scanner(System.in);

     ClassContainer pom = new ClassContainer(grupy);
    ClassContainer pomGr = new ClassContainer(grupy);
    ClassContainer year = new ClassContainer(grupyYear);
    Class Year = new Class("Rok",5,  new Vector<>());
    public Data() {
        getSomeRandomData();
        getSomeRandomDataYear();
    }
    public Data(String choose) {
        if (choose.equals("year")) getSomeRandomDataYear();
            getSomeRandomData();
    }
     void getSomeRandomData(){
        Student student = new Student("Jan", "Kowalski", "Nieokreslony",2003, 10);
        Student student2 = new Student("Kacper", "Suder", "Nieokreslony",2001, 10);
        Student student3 = new Student("Kamil", "Nowak", "Nieokreslony",2001, 10);
        Student student4 = new Student("Joanna", "Wozniak", "Nieokreslony",2001, 10);
        Student student5 = new Student("Weronika", "Poradzisz", "Nieokreslony",2001, 10);
        Student student6 = new Student("Adam", "Skowronek", "Nieokreslony",2001, 10);
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
        Student student = new Student("Jan", "Kowalski", "Aktywny",2003, 10);
        Student student2 = new Student("Kacper", "Suder", "Aktywny",2001, 10);
        Student student3 = new Student("Kamil", "Nowak", "Aktywny",2001, 10);
        Student student4 = new Student("Joanna", "Wozniak", "Aktywny",2001, 10);
        Student student5 = new Student("Weronika", "Poradzisz", "Aktywny",2001, 10);
        Student student6 = new Student("Adam", "Skowronek", "Aktywny",2001, 10);



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

    public void checkPresent(String grup, String surname, String stan) {
       pom.getClass2(grup).changeCondition(surname, stan);
    }

    public void checkPresentYear(String surname, String stan) {
        year.getClass(Year.nazwaGrupy).changeCondition(surname, stan);
    }

    public void changePointsYear(String surname, String opera, double points) {
        year.getClass(Year.nazwaGrupy).changePoints(surname, opera, points);
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
        year.getClass(Year.nazwaGrupy).removeStudentYear(surname);
    }

    public void deleteStudent(String groupChoose,String surname) {
        pom.getClass2(groupChoose).removeStudentYear(surname);
    }
    public void getMinusYear() {
        year.getClass(Year.nazwaGrupy).getStudent();
    }
    public void getMinus(String className) {
        pom.getClass2(className).getStudent();
    }
    public void searchClass(String className) {
        pom.getSearchClass(className);
    }
    public void searchPartialYear(String studentName ) {
        year.getClass(Year.nazwaGrupy).getSearchStudents(studentName);
    }
    public void searchPartial2(String nazwaGrupy, String studentName ) {
        pom.getClass2(nazwaGrupy).getSearchStudents(studentName);
    }

    private Vector<Student> sortByPoints(Vector<Student> group) {
        group.sort(this::compare);
        return group;
    }


    public int compare(Student o1, Student o2) {
        return (-1)*Double.compare(o1.iloscPunktow, o2.iloscPunktow);
    }


    void sortName(String className) {
        Vector <Student> group = pom.getClass(className).getListaStudentow();
    }

   /* public void searchPartialYear(String search) {
        Vector<Student> studenci = new Vector<Student>();
        Vector <Student> group = year.getClass("Rok").getListaStudentow();
        boolean a = false;
        boolean b = false;
        for (Student student : group) {
            a = student.nazwisko.contains(search);
            b = student.imie.contains(search);
            if (a == true || b == true) {
                studenci.add(student);
            }
            year.getClass("Rok").setListaStudentow(studenci);
          // return studenci;
        }
    }*/
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
