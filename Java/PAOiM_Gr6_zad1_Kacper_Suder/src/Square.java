import java.util.Scanner;

public class Square extends Figure implements MyInterface {
    double bok;
    Scanner scan = new Scanner(System.in); //tworzenie nowego obiektu Scanner

    @Override
    double calculateArea() {
        return (bok * bok);
    }

    @Override
    double calculatePerimeter() {
        return (4 * bok);
    }

    public Square(double bok) {
        this.bok = bok;
    }

    @Override
    public void print() {
        int wybor;
        while (true) { //petla wykonywana dopóki pom = 1 (przy pom = 0 koniec petli)
            System.out.print("Wybierz operacje, ktora ma zostac wykonana:\n\t 1) Oblicz obwod;\n\t 2) Oblicz pole;\n\t 3) Oblicz pole i obwod;\n\t 4) Zamknij program; \n");
            wybor = scan.nextInt();

            switch (wybor) {
                case 1 -> {
                    System.out.print("Obwod kwadratu to: " + calculatePerimeter());
                    return;
                }
                case 2 -> {
                    System.out.print("Pole kwadratu to: " + calculateArea());
                    return;
                }
                case 3 -> {
                    System.out.print("Obwod kwadratu to: " + calculatePerimeter() + "\nPole kwadratu to: " + calculateArea());
                    return;
                }
                case 4 -> {
                    System.out.print("Zamykanie programu.");
                    return;
                }
                default -> System.out.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n\n");
            }

        }
    }



}
