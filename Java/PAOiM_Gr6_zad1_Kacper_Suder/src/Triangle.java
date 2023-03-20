import java.util.Scanner;

import static java.lang.Math.sqrt;

public class Triangle extends Figure implements MyInterface {
   // double h;
    double podstawa;
    double bok_b;
    double bok_c;

    public Triangle(double a, double b, double c) {
        this.podstawa = a;
        this.bok_b = b;
        this.bok_c = c;
    }

    @Override
    double calculateArea() {
        double obwod = calculatePerimeter();
        return ( sqrt (0.5 * obwod * (0.5 * obwod - podstawa) * (0.5 * obwod - bok_b) *(0.5 * obwod - bok_c) ) );
    }

    @Override
    double calculatePerimeter() {
        return (podstawa + bok_b + bok_c);
    }

    @Override
    public void print() {
        Scanner scan = new Scanner(System.in);
        int wybor;
            while (true) {
                System.out.print("Wybierz operacje, ktora ma zostac wykonana:\n\t 1) Oblicz obwod;\n\t 2) Oblicz pole;\n\t 3) Oblicz pole i obwod;\n\t 4) Zamknij program; \n");
                wybor = scan.nextInt();

                switch (wybor) {
                    case 1 -> {
                        System.out.print("Obwod trojkata to: " + calculatePerimeter());
                        return;
                    }
                    case 2 -> {
                        System.out.print("Pole trojkata to: " + calculateArea());
                        return;
                    }
                    case 3 -> {
                        System.out.print("Obwod trojkata to: " + calculatePerimeter() + "\nPole trojkata to: " + calculateArea());
                        return;
                    }
                    case 4 -> {
                        System.out.print("Zamykanie programu.");
                        return;
                    }
                    default -> System.out.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n");
                }

        }
    }

}
