package ui.logic;

public class Student implements MyInterface, Comparable<Student> {

    // String condition;
    public String imie;
    public String nazwisko;
    public String stanStudenta;
    public int rokUrodzenia;
    public double iloscPunktow;


    public Student(String imie, String nazwisko, String stanStudenta, int rokUrodzenia, double iloscPunktow) {
        this.imie = imie.toUpperCase();
        this.nazwisko = nazwisko.toUpperCase();
        this.stanStudenta = stanStudenta;
        this.rokUrodzenia = rokUrodzenia;
        this.iloscPunktow = iloscPunktow;
    }

    public void setImie(String imie) {
        this.imie = imie.toUpperCase();
    }

    public void setNazwisko(String nazwisko) {
        this.nazwisko = nazwisko.toUpperCase();
    }

    public void setRokUrodzenia(int rokUrodzenia) {
        this.rokUrodzenia = rokUrodzenia;
    }

    public void setStanStudenta(String stanStudenta) {
        this.stanStudenta = stanStudenta;
    }

    @Override
    public void print() {
        System.out.print("\nDane Studenta: \n\tImie: " + imie);
        System.out.print("\n\tNazwisko studenta: " + nazwisko);
        System.out.print("\n\tRok urodzenia: " + rokUrodzenia);
        System.out.print("\n\tIlosc punktow: " + iloscPunktow);
        System.out.print("\n\tJego obecny stan to: " + stanStudenta);
    }

    public static boolean compareTo(String daneDoPorownania, String daneWGrupach) { //zwraca true - jeśli zgadzają się i false, jeśli nie
        return daneDoPorownania.equals(daneWGrupach);
    }

    @Override
    public int compareTo(Student o) {
        return 0;
    }


}
