//import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;
import java.util.*;

import static java.lang.Math.abs;

public class Class implements MyComperator {
    String nazwaGrupy;
    int maksymalnaIloscStudentow;


    Vector <Student> listaStudentow = new Vector<>(maksymalnaIloscStudentow);

    Scanner scan = new Scanner(System.in);

    public Vector<Student> getListaStudentow() {
        return listaStudentow;
    }

    int getSize() {
        return  listaStudentow.size();
    }

    public Class(String nazwaGrupy, int maksymalnaIloscStudentow, Vector<Student> listaStudentow) {
        this.nazwaGrupy = nazwaGrupy.toUpperCase();
        this.maksymalnaIloscStudentow = maksymalnaIloscStudentow;
        this.listaStudentow = listaStudentow;
    }

    public Class(String nazwaGrupy, int maksymalnaIloscStudentow) {
        this.nazwaGrupy = nazwaGrupy;
        this.maksymalnaIloscStudentow = maksymalnaIloscStudentow;
    }

    void addToGroup(int iloscStudentowDoDodania) {
        for (int i = 0; i < iloscStudentowDoDodania; i++)
            addStudent();
    }

    void addPoints(Student student, double points) {
        student.iloscPunktow += points;
    }

    void addStudent() {
        //StudentCondition condition = new StudentCondition();
        if (maksymalnaIloscStudentow == listaStudentow.size()) {
            System.err.print("\nMaksymalna liczba studentow w grupie zostala osiagnieta!");
            return;
        }
        String fillingInFields;
        int SetteryearOfTheBirth;
        Student adding = new Student("name", "surname", "Nieokreslony", 0, 10);
        while(true) {
            System.out.print("Prosze podac imie studenta: ");
            fillingInFields = scan.next();
            adding.setImie(fillingInFields.toUpperCase());
            System.out.print("Prosze podac nazwisko studenta: ");
            fillingInFields = scan.next();
            adding.setNazwisko(fillingInFields.toUpperCase());
            boolean help_name = false, help_surname = false;
            for (Student student : listaStudentow) {
                help_name = Student.compareTo(adding.imie, student.imie);
                help_surname = Student.compareTo(adding.nazwisko, student.nazwisko);

            }
            if (help_name && help_surname) {
                System.err.print("Student o takim imieniu i nazwisku znajduje sie juz w bazie!\n");
                System.out.println("\n");
                scan.nextLine();
            } else {
                System.out.print("Prosze podac rok urodzenia studenta: ");
                SetteryearOfTheBirth = scan.nextInt();
                adding.setRokUrodzenia(SetteryearOfTheBirth);
                System.out.print("\nPoprawnie utworzono studenta\n");
                listaStudentow.add(adding);
                break;
            }
        }
    }

    void addStudent(Student student) {
        listaStudentow.add(student);
        System.out.print("\nPoprawnie dodano studenta\n");
    }

    void changePoints() {
        int points, choose;
        String surname;
        Student chosen;
        while(true) {
            System.out.print("\nProsze podac nazwisko studenta: ");
            surname = scan.next();
            chosen = search(surname.toUpperCase());
            if(chosen != null) {
                break;
            }
        }
        while(true) {
            System.out.print("\nZarzadzanie punktami: \n\t1) Dodaj punkty; \n\t2) Odejmij punkty;\n");
            choose = scan.nextInt();
            switch (choose) {
                case 1 -> {
                    System.out.print("Podaj ilosc punktow do dadania: ");
                    points = scan.nextInt();
                    addPoints(chosen, abs(points));
                    return;
                }
                case 2 -> {
                    System.out.print("Podaj ilosc punktow do usuniecia: ");
                    points = scan.nextInt();
                    removePoints(chosen, abs(points));
                    getStudent(getListaStudentow());
                    return;
                }
                default -> {
                    System.err.print("Niepoprawny wybor, sprobuj ponownie\n");
                    System.out.print("\n");
                }
            }
        }
    }

    void changeCondition(Student student, StudentCondition condition) {
        String decision;
        System.out.print("\nCzy student " + student.imie + " " + student.nazwisko + " jest obecny (Tak/Nie/Chory): ");
        decision = scan.next();
        student.stanStudenta = condition.toString(decision);

    }

    void checkingPresence() {
        StudentCondition condition = new StudentCondition();
        for (Student student : listaStudentow) {
            changeCondition(student, condition);
        }
    }

    void getStudent(Vector <Student> student){
        for (int i =0; i < student.size();  i++) {
            if(student.get(i).iloscPunktow <= 0 ) {
                System.out.print("\nUsunieto studenta o imieniu i nazwisku: " + student.get(i).imie
                        + " " +student.get(i).nazwisko + "\n");
                student.removeElementAt(i);
            }
        }
        System.out.print("\nObecnie brak studentow z zerowa liczba punktow");
    }

    void removePoints(Student student, double points) {
        student.iloscPunktow -= points;
    }

    Student search(String surname) {
        for (Student student : listaStudentow) {
            if (Student.compareTo(surname, student.nazwisko)) return student;
        }
            System.err.print("Brak podanego studenta w grupie\n");
            System.out.print("\n");
            return null;
    }

    Vector<Student> searchPartial(String personalData) {
        int pom = 0;
        boolean a = false;
        boolean b = false;
        Vector <Student> listaStudentowOgraniczona = new Vector<>(maksymalnaIloscStudentow);
        for (Student student : listaStudentow) {
            a = student.nazwisko.contains(personalData);
            b = student.imie.contains(personalData);
            if (a == true || b == true) {
                listaStudentowOgraniczona.add(student);
                //for (int i = 0; i < listaStudentowOgraniczona.size(); i++) {
                   // listaStudentowOgraniczona.get(i).print();
                    pom++;
                //}
            }

        }
        if (pom == 9) {
            System.out.println("Brak studentow o takich danych");
            return null;
        } else {
            System.out.println("\nZnaleziono studentow");
           for (int i = 0; i < listaStudentowOgraniczona.size(); i++) {
               listaStudentowOgraniczona.get(i).print();
           }
            return listaStudentowOgraniczona;
        }
    }

    int countByCondition (StudentCondition condition) {
        String decision;
        String state;
        System.out.println("\nCzy interesuje cie stan dla obecnych tego dnia studentow? ");
        decision = scan.next();
        state = condition.toString(decision);
        int count = 0;
        for (int i = 0; i < listaStudentow.size(); i ++) {
            if(listaStudentow.get(i).stanStudenta.equals(state)) count += 1;
        }
        return count;
    }

    void sortByName(){
        listaStudentow.sort(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.imie.compareTo(o2.imie);
            }
        });
    }

    void sortByPoints() {
        listaStudentow.sort(this::compare);
    }

    @Override
    public int compare(Student o1, Student o2) {
                return (-1)*Double.compare(o1.iloscPunktow, o2.iloscPunktow);
    }


    void max() {
        Student student = Collections.max(listaStudentow, new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return Double.compare(o1.iloscPunktow, o2.iloscPunktow);
            }
        });
        System.out.println(student.iloscPunktow);
        System.out.print("\nNajwieksza ilosc to: " + student.iloscPunktow);
        }
    public void summary() {
        System.out.print("\nNazwa grupy: " + nazwaGrupy);
        for (Student student : listaStudentow) { //wykonuje tyle ile jest studentow w liscie
            student.print();
        }
    }


}
