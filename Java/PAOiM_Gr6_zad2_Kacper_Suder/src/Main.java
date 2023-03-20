import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Vector;

public class Main {

    public static void main(String[] args) {
       Map<String,Class> grupy = new HashMap<>();
       StudentCondition condition = new StudentCondition();

       Vector<Student> listaStudentow = new Vector<>();
       Vector<Student> listaStudentow2 = new Vector<>();

       Scanner scan = new Scanner(System.in);
       Student student = new Student ("Jan", "Kowalski", "Nieokreslony",2003, 10);
       Student student2 = new Student ("Kacper", "Suder", "Nieokreslony",2001, 10);
       Student student3 = new Student ("Kamil", "Nowak", "Nieokreslony",2001, 10);

       Class First = new Class("Pierwsza",4, listaStudentow);
       Class second = new Class("Druga",3, listaStudentow2);

       ClassContainer pom = new ClassContainer(grupy);

       pom.addClass(First.nazwaGrupy, First.maksymalnaIloscStudentow, First.listaStudentow);
       pom.addClass(second.nazwaGrupy, second.maksymalnaIloscStudentow ,second.listaStudentow);
       First.addStudent(student);
       First.addStudent(student2);
       First.addStudent(student3);

       //pom.summary();
       //pom.findEmpty();
       //System.out.println("\nUsuwanie Klasy: ");
       //pom.removeClass("Druga");
       //System.out.print("\nUsunieto\n\n\n ");
       pom.summary();


       System.out.println("\n\n");
       //pom.findEmpty();

       //First.addToGroup(2);

        //First.summary();
        //First.checkingPresence();
        //First.summary();
        First.changePoints();
        First.summary();
        System.out.print("\nPodaj fragment imienia lub nazwiska studenta: ");
        String nameOrSurname =  scan.next();
        System.out.print("\nWyszukani studenci to: ");
        First.searchPartial(nameOrSurname.toUpperCase());
        //System.out.print("\nZlicznie po stanie: ");
        //System.out.print(First.countByCondition(condition));
        //First.sortByName();
        //First.summary();
        //System.out.println("Maxymalna liczba puntkow to: ");
        //First.max();
       // First.sortByPoints();
       // First.summary();
        //System.out.println("\n\n");
        //pom.summary();

    }

}