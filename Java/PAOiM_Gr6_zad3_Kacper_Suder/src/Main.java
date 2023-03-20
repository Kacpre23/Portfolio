import ui.MainUI; //zaimportowanie maina do GUI
import ui.Menu;

import javax.swing.*;
import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() { //Tworzenie GUI
            @Override
            public void run() { //Uruchomienie GUI
                createGUI(); //metoda

            }
        });



     /*  Map<String,Class> grupy = new HashMap<>();
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

        MainUI.grupyUI = getMap(pom);
        //pom.findEmpty();m
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
        //pom.summary();*/

    }
    public static Map<String, Object> getMap(Object bean) {
        try {
            Map<String, Object> map = new HashMap<>();
            Arrays.asList(Introspector.getBeanInfo(bean.getClass(), Object.class)
                            .getPropertyDescriptors())
                    .stream()
                    // filter out properties with setters only
                    .filter(pd -> Objects.nonNull(pd.getReadMethod()))
                    .forEach(pd -> { // invoke method to get value
                        try {
                            Object value = pd.getReadMethod().invoke(bean);
                            if (value != null) {
                                map.put(pd.getName(), value);
                            }
                        } catch (Exception e) {
                            // add proper error handling here
                        }
                    });
            return map;
        } catch (IntrospectionException e) {
            // and here, too
            return Collections.emptyMap();
        }
    }
    private static void createGUI() {
        Menu ui = new Menu(); //stworzenie GUI. UI - user interface
        JPanel root = ui.getRootPanel(); //panel administratora
        JFrame frame = new JFrame("Dziennik elektryczny"); //ramka do wyświetlania GUI
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //operacja zamykania
        frame.setContentPane(root);//dodanie panelu głównego do ramki
        frame.pack();
        frame.setLocationRelativeTo(null); //wyśrodkowanie interfejsu użytkownika
        frame.setVisible(true);//pokazanie intefejsu użytkownika
    }
}