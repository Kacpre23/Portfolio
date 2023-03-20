package ui.logic;

public class StudentCondition {
    public enum Answer {
        Tak(true),
        //tak(true),
        //t(true),
        T(true),
        Nie(false),
       // nie(false),
        N(false),
        //n(false),
        Yes(true),
       // yes(true),
        Y(true),
        //y(true),
        No(false);

        private boolean value;

        Answer(boolean b) { //konstruktor domyślny
            this.value = b;
        }

        public boolean getAnswer() {
            return value;
        }

    }
    public String toString(String in) {
        try { //jeśli warunek nie zostanie spelniony : (brakuje true, albo false), tworzymy nowy wyjątek (przy pomocy klasy wyjatki)
            return check(in) ? "Obecny/Odrabiajacy" : "Nieobecny";
        } catch (UnknownAnswerException e) {
            return "Chory";
        }
    }

    boolean check(String in) throws UnknownAnswerException {
        for (Answer odp : Answer.values()){ //jesli nie ma takiej odpowiedzi (YES, NO), tworzy nowy wyjatek
            if(odp.toString().equalsIgnoreCase(in)) {
                //System.out.print(odp.getAnswer());
                return odp.getAnswer();
            }
        }
        throw new UnknownAnswerException();
    }

}
