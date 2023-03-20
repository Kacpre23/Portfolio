package ui.logic;


import javax.swing.*;
import java.util.*;

public class ClassContainer {
    public Map<String, Class> wszystkiegrupy = new HashMap<>();
   public Map<String, Class> grupy = new HashMap<>();
    public Map<String, Class> pomocWyszukajGrupe = new HashMap<>();

    Student student = new Student("name", "surname", "Nieokreslony", 0, 10);
    public ClassContainer(Map<String,Class> grupy) {
        this.grupy = grupy;
        this.wszystkiegrupy = this.grupy;
    }

    public Map<String, Class> addClass(String nazwa, int ilosc, Vector<Student> listaStudentow) {
        grupy.put(nazwa, new Class(nazwa, ilosc, listaStudentow));
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
    public  Class getClass2(String nazwa) {
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

    public  Class getClass2(String nazwa, int rozmiar) {
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
            if (!nazwa.equals("")) JOptionPane.showMessageDialog(null, "Grupa nie została znaleziona!", "Błąd", JOptionPane.WARNING_MESSAGE);
            return wszystkiegrupy;
        }
    }


    public Map<String, Class> getMap() {
        return grupy;
    }

    public Map<String, Class> removeClass(String nazwaGrupy) {
        grupy.remove(nazwaGrupy);
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
    void summary() {
        for (Class grupa : grupy.values()) {
            System.out.print("\nNazwa grupy to: " + grupa.nazwaGrupy +  "\tProcentowe zapelnienie: "
                    + (((float)grupa.getSize()/(float)grupa.maksymalnaIloscStudentow) * 100) + "%");
            grupa.summary();
        }
    }


}
