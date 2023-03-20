import java.util.Scanner;

public class Prism extends Figure implements MyInterface {

    double wysokosc, bok, pole_podstawy, obwod;

    int wybor;
    Figure  p_podstawa;

    Scanner scan = new Scanner(System.in); //tworzenie nowego obiektu Scanner

    public Prism(double wysokosc, double bok, int wybor) { //konstruktor
        this.wysokosc = wysokosc;
        this.bok = bok;
        this.wybor = wybor;
    }

    public void setPole_podstawy(double pole_podstawy) { //setter ustawiajacy pole podstawy
        this.pole_podstawy = pole_podstawy;
    }


    public void setObwod(double obwod) { this.obwod = obwod; }

    @Override
    double calculateArea() {
        return (2 * pole_podstawy + obwod * wysokosc);
    }

    @Override
    double calculatePerimeter() {
        return (pole_podstawy * wysokosc);
    }

    @Override
    public void print() {
        while (true) {
            if (wybor == 1) {
                    p_podstawa = new Square(bok); // abstrakcyjna
                    setPole_podstawy(p_podstawa.calculateArea());
                    setObwod(p_podstawa.calculatePerimeter());
                    while (true) {
                        System.out.print("Wybierz operacje, ktora ma zostac wykonana:\n\t 1) Oblicz pole powierzchni;\n\t 2) Oblicz objetosc;\n\t 3) Oblicz pole powierzchni oraz objetosc;\n\t 4) Zamknij program; \n");
                        wybor = scan.nextInt();
                        switch (wybor) {
                            case 1 -> {
                                System.out.print("Pole powierzchni graniastoslupa prawidlowego wynosi: " + calculateArea());
                                return;
                            }
                            case 2 -> {
                                System.out.print("Objetosc graniastoslupa prawidlowego wynosi: " + calculatePerimeter());
                                return;
                            }
                            case 3 -> {
                                System.out.print("Pole powierzchni graniastoslupa prawidlowego wynosi: " + calculateArea() + " Objetosc graniastoslupa prawidlowego wynosi: " + calculatePerimeter());
                                return;
                            }
                            case 4 -> {
                                System.out.print("Zamykanie programu.");
                                return;
                            }
                            default -> System.out.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n\n");
                        }
                    }
                } else if (wybor == 2) {
                    p_podstawa = new Triangle(bok,bok, bok); // abstrakcyja
                    setPole_podstawy(p_podstawa.calculateArea());
                    setObwod(p_podstawa.calculatePerimeter());
                    while (true) {
                        System.out.print("Wybierz operacje, ktora ma zostac wykonana:\n\t 1) Oblicz pole powierzchni;\n\t 2) Oblicz objetosc;\n\t 3) Oblicz pole powierzchni oraz objetosc;\n\t 4) Zamknij program; \n");
                        wybor = scan.nextInt();
                        switch (wybor) {
                            case 1 -> {
                                System.out.print("Pole powierzchni graniastoslupa prawidlowego wynosi: " + calculateArea());
                                return;
                            }
                            case 2 -> {
                                System.out.print("Objetosc graniastoslupa prawidlowego wynosi: " + calculatePerimeter());
                                return;
                            }
                            case 3 -> {
                                System.out.print("Pole powierzchni graniastoslupa prawidlowego wynosi: " + calculateArea() + "\nObjetosc graniastoslupa prawidlowego wynosi: " + calculatePerimeter());
                                return;
                            }
                            case 4 -> {
                                System.out.print("Zamykanie programu.");
                                return;
                            }
                            default -> System.out.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n\n");
                        }
                    }
                } else {
                    System.out.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n");
               }
        }
    }
}

