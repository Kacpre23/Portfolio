package ui;

import ui.data.Data;
import ui.logic.Student;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.lang.String;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import java.util.ArrayList;
import java.util.Vector;

class DataYear extends AbstractTableModel {

    public Data data;
    ArrayList<Object[]> studentData;
    private final String[] columnsNamesYear;
    String dzialaj;

    public DataYear(String wybrane) {
        columnsNamesYear = new String[]{"Imie", "Nazwisko", "Rok urodzenia", "Ilosc punktow", "Stan studenta"};
        studentData=new ArrayList<>();
        data = new Data(wybrane);
        dzialaj = wybrane;
    }



    void getStudentData() {
        studentData = new ArrayList<>();
        if (dzialaj.equals("year")) {
            Vector<Student> found = data.returnYearConteiner().getClass2().getListaStudentow();
            for(Student student : found) {
                Object[] students = {student.imie, student.nazwisko, student.rokUrodzenia, student.iloscPunktow, student.stanStudenta};
                studentData.add(students);
            }
        } else {
            Vector<Student> found = data.returnClassConteiner().getClass2(dzialaj).getListaStudentow();
            for(Student student : found) {
                Object[] students = {student.imie, student.nazwisko, student.rokUrodzenia, student.iloscPunktow, student.stanStudenta};
                studentData.add(students);
            }
        }

    }

    public String getColumnName(int col) {
        return columnsNamesYear[col];
    }

    @Override
    public int getRowCount() {
        return studentData.size();
    }

    @Override
    public int getColumnCount() {
        return columnsNamesYear.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return studentData.get(rowIndex)[columnIndex];
    }
}

public class Year implements ActionListener {
    Vector<Student> studentConteiner;
    String selectedOption = "null";
    String selectedStudent;
    private final DataYear dataYear;
    private JPanel rootPanel;
    private JComboBox chooseOperation;
    private JTextField search;
    private JTable studentData;
    private JButton wyjścieButton;
    private JPanel Choose;
    private JPanel Title;
    private JPanel Table;
    private JButton zatwierdzButton;
    private JPanel Exit;

    String wybranaGrupa;

    void setWybranaGrupa(String wybor) {
        wybranaGrupa = wybor;
    }
    int rozmiarGrupy;
    String wybranaGrupaDo;
    void setOption (String choice) {
        selectedOption = choice;
    }

    public Year(String selectedGroup, int rozmiar) {
        rozmiarGrupy = rozmiar;
        wybranaGrupaDo = selectedGroup;
        dataYear = new DataYear(selectedGroup);
        createTable(selectedGroup);
        createOperation();
        createSearch();
        createZatwierdzButton();
        createExitButton();

    }


    public JPanel getRootPanel() {
        return rootPanel;
    }


    private void  createTable(String chosenGroup) {
        setWybranaGrupa(chosenGroup);

       if (chosenGroup.equals("year")) {
            dataYear.data.returnYearConteiner().getClass2().getListaStudentow();
        } else {
           dataYear.data.returnClassConteiner().getClass2(chosenGroup, rozmiarGrupy).getListaStudentow();
        }

        studentData.setModel(dataYear);
        TableColumnModel columns = studentData.getColumnModel(); //tablica kolumn
        columns.getColumn(0).setMinWidth(1);
        DefaultTableCellRenderer centerRenderer = new DefaultTableCellRenderer();
        centerRenderer.setHorizontalAlignment(JLabel.CENTER);
        columns.getColumn(1).setCellRenderer(centerRenderer);
        columns.getColumn(2).setCellRenderer(centerRenderer);
        columns.getColumn(3).setCellRenderer(centerRenderer);
        studentData.setAutoCreateRowSorter(true);

        show();
    }

    void show() {
        dataYear.studentData.clear();
        dataYear.getStudentData();
        //studentData.setModel(dataYear);

    }

    private void createOperation() {
        chooseOperation.setModel(new DefaultComboBoxModel(new String[] {"Wybor operacji","Dodaj studenta", "Usun studenta", "Dodaj punkty", "Usuń punkty", "Sprawdz obecnosc"}));
        chooseOperation.addItemListener(new ItemListener() {

            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.SELECTED) {
                    String selected = (String) chooseOperation.getSelectedItem();
                    setOption(selected); //Ustawianie wybranej opcji!
                }
            }
        });
    }

    private void createSearch() { search.addActionListener(this); }
    private void createExitButton() {
        wyjścieButton.addActionListener(this);
    }

    private void createZatwierdzButton() {
        zatwierdzButton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        if (source == wyjścieButton) {
            System.exit(0);
        } else if (source == search) {
            String found = search.getText().toUpperCase();
            if(wybranaGrupa.equals("year")) {
                dataYear.data.searchPartialYear(found);
                studentData.setModel(new DefaultTableModel());
                show();
                studentData.setModel(dataYear);
            } else {
                dataYear.data.searchPartial2(wybranaGrupa, found);
                studentData.setModel(new DefaultTableModel());
                show();
                studentData.setModel(dataYear);
            }


        } else if(source == zatwierdzButton) {
            if (selectedOption.equals("Dodaj studenta")) {
                String imie = JOptionPane.showInputDialog(null, "Podaj imię studenta:", "Wprowadź imię studenta", JOptionPane.INFORMATION_MESSAGE);
                String nazwisko= JOptionPane.showInputDialog(null, "Podaj nazwisko studenta:", "Wprowadź nazwisko studenta", JOptionPane.INFORMATION_MESSAGE);
                String rokUrodzenia = JOptionPane.showInputDialog(null, "Podaj rok urodzenia studenta:", "Wprowadź rok urodzenia studenta", JOptionPane.INFORMATION_MESSAGE);

                int rok = Integer.parseInt(rokUrodzenia);
                if (wybranaGrupa.equals("year")) {
                    dataYear.data.returnYearConteiner().getClass2().addStudent(imie, nazwisko, rok);
                } else {
                    dataYear.data.returnClassConteiner().getClass2(wybranaGrupa).addStudent(imie, nazwisko, rok);
                }

                studentData.setModel(new DefaultTableModel());
                show();
                studentData.setModel(dataYear);

            } else if (selectedOption.equals("Usun studenta")) {
                int Row = studentData.getSelectedRow();
                if (Row == -1) {
                    JOptionPane.showMessageDialog(null, "Student nie został wybrany!", "Błąd", JOptionPane.WARNING_MESSAGE);
                } else {
                    Object id = studentData.getValueAt(Row, 1);
                    selectedStudent = id.toString();
                    if (wybranaGrupa.equals("year")) {
                        dataYear.data.deleteStudentYear(selectedStudent);
                    } else {
                        dataYear.data.deleteStudent(wybranaGrupa, selectedStudent);
                    }

                    studentData.setModel(new DefaultTableModel());
                    show();
                    studentData.setModel(dataYear);
                }
            } else if (selectedOption.equals("Sprawdz obecnosc"))  {
                int Row = studentData.getSelectedRow();
                if (Row == -1) {
                    JOptionPane.showMessageDialog(null, "Student nie został wybrany!", "Błąd", JOptionPane.WARNING_MESSAGE);
                } else {
                    String zmianaStanu;
                    int a = JOptionPane.showConfirmDialog(null,"Czy wybrany student jest obecny?","Obecność na zajęciach",JOptionPane.YES_NO_CANCEL_OPTION);
                    System.out.println(a);
                    if (a == 0) {
                        zmianaStanu = "Tak";
                    } else if (a == 1) {
                        zmianaStanu = "Nie";
                    } else {
                        zmianaStanu = "Chory";
                    }
                    Object id = studentData.getValueAt(Row, 1);
                    selectedStudent = id.toString();
                    System.out.println(selectedStudent);
                    if(wybranaGrupa.equals("year")) {
                        dataYear.data.checkPresentYear(selectedStudent, zmianaStanu);
                    } else {
                        dataYear.data.checkPresent(wybranaGrupa, selectedStudent, zmianaStanu);

                    }
                    studentData.setModel(new DefaultTableModel());
                    show();
                    studentData.setModel(dataYear);
                }
            }  else if (selectedOption.equals("Dodaj punkty")) {
                int Row = studentData.getSelectedRow();
                if (Row == -1) {
                    JOptionPane.showMessageDialog(null, "Student nie został wybrany!", "Błąd", JOptionPane.WARNING_MESSAGE);
                } else {

                    JFrame frame = new JFrame("Zmiana liczby punktow");
                    String value = JOptionPane.showInputDialog(
                            frame,
                            "Wprowadz punkty",
                            "Zmiana liczby punktow",
                            JOptionPane.INFORMATION_MESSAGE
                    );

                    if (value.isEmpty()) {
                        JOptionPane.showMessageDialog(null, "Nie wprowadzono punktów!", "Błąd", JOptionPane.WARNING_MESSAGE);
                    } else {
                        double points = Double.parseDouble(value);
                        System.out.println(points);

                        Object id = studentData.getValueAt(Row, 1);
                        selectedStudent = id.toString();
                        if(wybranaGrupa.equals("year")) {
                            dataYear.data.changePointsYear(selectedStudent, "Dodaj", points );
                        } else {
                            dataYear.data.changePoints(wybranaGrupa,selectedStudent, "Dodaj", points );

                        }
                        studentData.setModel(new DefaultTableModel());
                        show();
                        studentData.setModel(dataYear);
                    }

                }

            }  else if (selectedOption.equals("Usuń punkty")) {
                int Row = studentData.getSelectedRow();
                if (Row == -1) {
                    JOptionPane.showMessageDialog(null, "Student nie został wybrany!", "Błąd", JOptionPane.WARNING_MESSAGE);
                } else {

                    JFrame frame = new JFrame("Zmiana liczby punktow");
                    String value = JOptionPane.showInputDialog(
                            frame,
                            "Wprowadz punkty",
                            "Zmiana liczby punktow",
                            JOptionPane.INFORMATION_MESSAGE
                    );

                    if (value.isEmpty()) {
                        JOptionPane.showMessageDialog(null, "Nie wprowadzono punktów!", "Błąd", JOptionPane.WARNING_MESSAGE);
                    } else {
                        double points = Double.parseDouble(value);


                        Object id = studentData.getValueAt(Row, 1);
                        selectedStudent = id.toString();
                        if(wybranaGrupa.equals("year")) {
                            dataYear.data.changePointsYear(selectedStudent, "Usun", points );
                            dataYear.data.getMinusYear();

                        } else {
                            dataYear.data.changePoints(wybranaGrupa,selectedStudent, "Usun", points );
                            dataYear.data.getMinus(wybranaGrupa);
                        }
                        studentData.setModel(new DefaultTableModel());
                        show();
                        studentData.setModel(dataYear);
                    }

                }

            } else if (selectedOption.equals("null") || selectedOption.equals("Wybor operacji")){
                JOptionPane.showMessageDialog(null, "Nie wybrano operacji!", "Błąd", JOptionPane.WARNING_MESSAGE);
            }
        }
}
}
