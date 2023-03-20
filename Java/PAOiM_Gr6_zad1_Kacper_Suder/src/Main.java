import java.util.Scanner;

public class Main { //klasy piszemy z dużej litery

    public static void main(String[] args) { //metody nazywamy z małej litery - main wymaga tablice args

        Scanner scan = new Scanner(System.in); //tworzenie nowego obiektu Scanner
        int wybor, przestrzen;
        double wysokosc;
        while (true) {
            for (;;) {
                System.out.println("Przy pomocy odpowiedniej cyfry, wybierz przestrzen: \n\t1) 2D; \n\t2) 3D; \n\t3) Zamknij program;\n");
                przestrzen = scan.nextInt();
                if (przestrzen == 1) {
                    System.out.println("Przy pomocy odpowiedniej cyfry, wybierz figure: \n\t1) Kolo; \n\t2) Kwadrat; \n\t3) Trojkat; \n\t4) Zamknij program;\n");
                    break;
                } else if (przestrzen == 2 ) {
                    System.out.println("Przy pomocy odpowiedniej cyfry, wybierz podstawe graniastoslupa: \n\t1) Kwadrat; \n\t2) Trojkat; \n\t3) Zamknij program;\n");
                    break;
                } else if (przestrzen == 3 ) {
                    System.out.print("Zamykanie programu.");
                    return;
                } else {
                    System.err.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n");
                }
            }

            while (true) {

                wybor = scan.nextInt();
                if (przestrzen == 2) {
                    wybor += 1;
                    if (wybor == 1) {
                        wybor = 5;
                    }
                }
                switch (wybor) {
                    case 1 -> {
                        while (true) {
                            System.out.print("Podaj promien kola: ");
                            double promien = scan.nextDouble();
                            if (promien <= 0) {
                                System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                            } else {
                                System.out.print("Poprawne dane\n");
                                    MyInterface myinterface_circle = new Circle(promien);
                                    myinterface_circle.print();
                                    return;
                            }
                        }
                    }
                    case 2 -> {
                        double bok;
                        while (true) {
                            System.out.print("Podaj bok kwadratu: ");
                            bok = scan.nextDouble();
                            if (bok <= 0) {
                                System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                               // Thread.sleep(200);
                            } else {
                                System.out.print("\nPoprawne dane\n\n");
                                if (przestrzen == 1) {
                                    MyInterface myinterface_square = new Square(bok);
                                    myinterface_square.print();
                                    return;
                                } else {
                                    while (true) {
                                        System.out.println("Podaj wysokosc graniastoslupu prawidlowego: ");
                                        wysokosc = scan.nextDouble();
                                        if (wysokosc <= 0) {
                                            System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                                            //Thread.sleep(200);
                                        } else {
                                            wybor -= 1;
                                            MyInterface myinterface_prism = new Prism(wysokosc, bok, wybor);
                                            myinterface_prism.print();
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    case 3 -> {
                        double dl_a, dl_b, dl_c;
                        while (true) {
                            if (przestrzen == 1) {
                                System.out.print("Podaj dlugosc podstawy trojkata: ");
                                dl_a = scan.nextDouble();
                                if (dl_a <= 0) {
                                    System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                                    // Thread.sleep(200);
                                } else {
                                    System.out.print("Podaj dlugosc drugiego boku trojkata: ");
                                    dl_b = scan.nextDouble();
                                    if (dl_b <= 0) {
                                        System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                                        //Thread.sleep(200);
                                    } else {
                                        System.out.print("Podaj dlugosc trzeciego boku trojkata: ");
                                        dl_c = scan.nextDouble();
                                        if (dl_c <= 0) {
                                            System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                                            //Thread.sleep(200);
                                        } else {
                                            if (dl_a >= dl_b + dl_c || dl_b >= dl_a + dl_c || dl_c >= dl_a + dl_b) {
                                                System.err.print("Niepoprawne dane, suma dwoch bokow mniejsza od trzeciego, prosze sprobowac ponownie\n");
                                                //Thread.sleep(200);
                                            } else {
                                                System.out.print("Poprawnie wprowadzono dane\n");
                                                MyInterface myinterface_triagle = new Triangle(dl_a, dl_b, dl_c);
                                                myinterface_triagle.print();
                                                return;
                                            }
                                        }
                                    }
                                }
                            } else {
                                double bok;
                                while (true) {
                                    System.out.print("Podaj dlugosc boku trojkata: ");
                                    bok = scan.nextDouble();
                                    if (bok <= 0) {
                                        System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                                    } else {
                                        System.out.print("\nPoprawne dane\n\n");
                                        System.out.println("Podaj wysokosc graniastoslupu prawidlowego: ");
                                        wysokosc = scan.nextDouble();
                                        if (wysokosc <= 0) {
                                            System.err.print("Niepoprawne dane, prosze sprobowac ponownie\n");
                                        } else {
                                            MyInterface myinterface_prism = new Prism(wysokosc, bok, wybor - 1);
                                            myinterface_prism.print();
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    case 4 -> {
                        System.out.print("Zamykanie programu.");
                        return;
                    }
                    default -> System.err.print("Wybrano nie poprawna opcje, prosze sprobowac ponownie. \n");
                }
            }
        }
    }
}

