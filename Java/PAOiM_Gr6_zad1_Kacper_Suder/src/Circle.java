import java.util.Scanner;

public class Circle extends Figure implements MyInterface {
    double r;

    public Circle(double r) {
        this.r = r;
    }

    @Override
    double calculateArea() {
        return (Math.PI * r * r);
    }

    @Override
    double calculatePerimeter() {
        return (2 * Math.PI * r);
    }

    @Override
    public void print() {
        int wybor;
        Scanner scan = new Scanner(System.in);
        while (true) {
            System.out.print("Prosze wybrac operacje, ktora ma zostac wykonana:\n\t 1) Oblicz obwod;\n\t 2) Oblicz pole;\n\t 3) Oblicz pole i obwod;\n\t 4) Zamknij program; \n");
            wybor = scan.nextInt();
            switch (wybor) {
                case 1 -> {
                    System.out.print("Obwod kola to: " + calculatePerimeter());
                    return;
                }
                case 2 -> {
                    System.out.print("Pole kola to: " + calculateArea());
                    return;
                }
                case 3 -> {
                    System.out.print("Obwod kola to: " + calculatePerimeter() + "\nPole kola to: " + calculateArea());
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

