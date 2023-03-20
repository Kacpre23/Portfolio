package com.javabunga.springbootexample;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Data {
    private static final String COMMA = ",";
    private static final String DEFAULT_SEPARATOR = COMMA;
    private static final String DOUBLE_QUOTES = " ";
    private static final String EMBEDDED_DOUBLE_QUOTES = " ";
    private static final String NEW_LINE_UNIX = "\n";
    private static final String NEW_LINE_WINDOWS = "\r\n";


    private static final String CSV_FILE_NAME = "Studenci.csv";
    public Map<String, Class> grupy = new HashMap<>();
    public Map<String, Class> pomocnaGrupa = new HashMap<>();
    Map<String, Class> grupyYear = new HashMap<>();
     Vector<Student> listaStudentow2 = new Vector<>();
     ClassContainer pom = new ClassContainer(grupy);
    ClassContainer year = new ClassContainer(grupyYear);
    List<String[]> dataLines = new ArrayList<>();
    public Data() {
        getSomeRandomData();
        getSomeRandomDataYear();
    }
     void getSomeRandomData(){
        Student student = new Student(1, "Jan", "Kowalski", "Nieokreslony",2003,  15.0);
        Student student2 = new Student(2,"Kacper", "Suder", "Nieokreslony",2001,  10.0);
        Student student3 = new Student(3,"Kamil", "Nowak", "Nieokreslony",2001,  10.0);
        Student student4 = new Student(4,"Joanna", "Wozniak", "Nieokreslony",2001, 10.0);
        Student student5 = new Student(5,"Weronika", "Poradzisz", "Nieokreslony",2001, 10.0);
        Student student6 = new Student(6,"Adam", "Skowronek", "Nieokreslony",2001,  10.0);
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
        dataLines.add(new String[] {"ID", "IMIE", "NAZWISKO", "STAN", "ROK", "PUNKTY"});
        Student student = new Student(1,"Jan", "Kowalski", "Aktywny",2003, 20.0);
        dataLines.add(new String[] { "1","Jan", "Kowalski", "Aktywny","2003", "10.0"});
        Student student2 = new Student(2,"Kacper", "Suder", "Aktywny",2001,  10.0);
        dataLines.add(new String[] { "2","Kacper", "Suder", "Aktywny","2001", "10.0"});
        Student student3 = new Student(3,"Kamil", "Nowak", "Aktywny",2001,  15.0);
        dataLines.add(new String[] { "3","Kamil", "Nowak",  "Aktywny","2001", "10.0"});
        Student student4 = new Student(4,"Joanna", "Wozniak", "Aktywny",2001,  10.0);
        dataLines.add(new String[] { "4","Joanna", "Wozniak",  "Aktywny","2001", "10.0"});
        Student student5 = new Student(5,"Weronika", "Poradzisz", "Aktywny",2001, 18.0);
        dataLines.add(new String[] { "5", "Weronika", "Poradzisz", "Aktywny","2001", "10.0"});
        Student student6 = new Student(6,"Adam", "Skowronek", "Aktywny",2001,  10.0);
        dataLines.add(new String[] { "6","Adam", "Skowronek", "Aktywny","2001", "10.0"});

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


/*    public void changePointsYear(String surname, String opera, double points) {
        year.getClass2().changePoints(surname, opera, points);
    }
    public void changePoints(String classa, String surname, String opera, double points) {
        pom.getClass2(classa).changePoints(surname, opera, points);
    }*/
   public void deleteClass(String className){
         pom.removeClass(className);

    }

    public void addClass(String className, int max) {
        pom.addClass(className, max, listaStudentow2);
        pomocnaGrupa = grupy;
    }

    public Boolean deleteStudentYear(String surname) {
        boolean pom;
       pom = year.getClass2().removeStudentYear(surname);
        return pom;
    }

    public boolean deleteStudentYear(int id) {
       boolean pom;
        pom = year.getClass2().removeStudentYear(id);
        return pom;
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
        return Double.compare(o1.iloscPunktow, o2.iloscPunktow);
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

    public void addToList(Student student) {
        dataLines.add(new String[] { Integer.toString(student.getId()), student.imie, student.nazwisko, student.stanStudenta, Double.toString(student.iloscPunktow), Integer.toString(student.rokUrodzenia)});
    }

    public String convertToCsvFormat(final String[] line) {
        return convertToCsvFormat(line, DEFAULT_SEPARATOR);
    }

    public String convertToCsvFormat(final String[] line, final String separator) {
        return convertToCsvFormat(line, separator, true);
    }

    // if quote = true, all fields are enclosed in double quotes
    public String convertToCsvFormat(
            final String[] line,
            final String separator,
            final boolean quote) {

        return Stream.of(line)                              // convert String[] to stream
                .map(l -> formatCsvField(l, quote))         // format CSV field
                .collect(Collectors.joining(separator));    // join with a separator

    }

    // put your extra login here
    private String formatCsvField(final String field, final boolean quote) {

        String result = field;

        if (result.contains(COMMA)
                || result.contains(DOUBLE_QUOTES)
                || result.contains(NEW_LINE_UNIX)
                || result.contains(NEW_LINE_WINDOWS)) {

            // if field contains double quotes, replace it with two double quotes \"\"
            result = result.replace(DOUBLE_QUOTES, EMBEDDED_DOUBLE_QUOTES);

            // must wrap by or enclosed with double quotes
            result = DOUBLE_QUOTES + result + DOUBLE_QUOTES;

        } else {
            // should all fields enclosed in double quotes
            if (quote) {
                result = DOUBLE_QUOTES + result + DOUBLE_QUOTES;
            }
        }

        return result;

    }

    // a standard FileWriter, CSV is a normal text file
    public void writeToCsvFile() throws IOException {

        List<String> collect = dataLines.stream()
                .map(this::convertToCsvFormat)
                .collect(Collectors.toList());

        // CSV is a normal text file, need a writer
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(CSV_FILE_NAME))) {
            for (String line : collect) {
                bw.write(line);
                bw.newLine();
            }
        }

    }





}

