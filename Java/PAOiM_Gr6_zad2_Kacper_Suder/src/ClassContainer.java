import java.util.*;

public class ClassContainer {
    Map<String, Class > grupy = new HashMap<>();
    //Vector<Student> listaStudentow;
    Student student = new Student("name", "surname", "Nieokreslony", 0, 10);
    public ClassContainer(Map<String,Class> grupy) {
        this.grupy = grupy;
    }


    void addClass(String nazwa, int ilosc, Vector<Student> listaStudentow) {
        grupy.put(nazwa, new Class(nazwa, ilosc, listaStudentow));
    }

    void removeClass(String nazwaGrupy) {
        grupy.remove(nazwaGrupy);
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
    void summary() {
        for (Class grupa : grupy.values()) {
            System.out.print("\nNazwa grupy to: " + grupa.nazwaGrupy +  "\tProcentowe zapelnienie: "
                    + (((float)grupa.getSize()/(float)grupa.maksymalnaIloscStudentow) * 100) + "%");
            grupa.summary();
        }
    }


}
