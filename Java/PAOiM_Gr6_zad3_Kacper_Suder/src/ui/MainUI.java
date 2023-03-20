package ui;

import ui.data.Data;
import ui.logic.Class;
import ui.logic.ClassContainer;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.ArrayList;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

class DataUse extends AbstractTableModel {
  public Data data;
    ArrayList<Object[]> groupData;
    ArrayList<String> classNames;
    private final String[] columnsNames;

    public DataUse() {
        columnsNames = new String[]{"Grupa", "Liczba studentow", "Limit miejsc", "Procentowe zapelnienie"};
        groupData=new ArrayList<>();
        data = new Data();
        classNames = new ArrayList<>();
    }

    void getGroupChoice() {
        Set<Map.Entry<String, Class>> entries = data.returnClassConteiner().getMap().entrySet();
        for(Map.Entry<String, Class> found : entries) {
            classNames.add(found.getValue().nazwaGrupy);
        }
    }

    void getGroupData() {
        groupData.clear();
        Set<Map.Entry<String, Class>> entries = data.returnClassConteiner().getMap().entrySet();
        for(Map.Entry<String, Class> found : entries) {
            String percent;
            percent = (double)found.getValue().getSize()/(found.getValue().maksymalnaIloscStudentow) * 100 + "%";
            Object[] classes = {found.getValue().nazwaGrupy, found.getValue().getSize(), found.getValue().maksymalnaIloscStudentow, percent};
            groupData.add(classes);
        }
    }

    public String getColumnName(int col) {
        return columnsNames[col];
    }

    @Override
    public int getRowCount() {
        return groupData.size();
    }

    @Override
    public int getColumnCount() {
        return columnsNames.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return groupData.get(rowIndex)[columnIndex];
    }
}

public class MainUI implements ActionListener {

    public Map<String, Object> groupsMap;
    ClassContainer groupsContainret;
    ArrayList<String> groupsNames;

    private final DataUse dataUse = new DataUse();
    private JPanel rootPanel;
    private JTable groupData;
    private JComboBox table;
    private JTextField search;
    private JButton exitButton;
    private JComboBox chooseOperation;
    private JButton executeButton;

    String selectedGroup = "year";
    String selectedOption = "null";
    int rozmiarGrupy;
    public String getSelectedGroup() {
        return selectedGroup;
    }

    public MainUI() {
        createTable();
        createChooseTable();
        createOperation();
        createWyjścieButton();
        createExecuteButton();
        createSearch();
    }


    void setGroup (String choice) {
        selectedGroup = choice;
    }
    void setOption (String choice) {
        selectedOption = choice;
    }


    void show() {
        dataUse.groupData.clear();
        dataUse.getGroupData();
        //groupData.setModel(dataUse);
    }

    public JPanel getRootPanel() {
        return rootPanel;
    }

    private void  createTable() {
        //groupsContainret = dataUse.data.returnClassConteiner();

        dataUse.data.returnClassConteiner();

        groupData.setModel(dataUse);
        TableColumnModel columns = groupData.getColumnModel(); //tablica kolumn
        columns.getColumn(0).setMinWidth(1);
        DefaultTableCellRenderer centerRenderer = new DefaultTableCellRenderer();
        centerRenderer.setHorizontalAlignment(JLabel.CENTER);
        columns.getColumn(1).setCellRenderer(centerRenderer);
        columns.getColumn(2).setCellRenderer(centerRenderer);
        columns.getColumn(3).setCellRenderer(centerRenderer);
        groupData.setAutoCreateRowSorter(true);
        groupData.setCellSelectionEnabled(true);
        show();
    }

    private void  createChooseTable() {
        groupsNames = dataUse.data.getAllTable();
        dataUse.data.getAllTable();
        table.addItem("Wybor grupy");
        for (String choice : groupsNames) {
            table.addItem(choice);
        }

        table.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.SELECTED) {
                    String selected = (String) table.getSelectedItem();
                    setGroup(selected);
                    }
                show();
            }
        });
    }

    private void  createOperation() {
        chooseOperation.setModel(new DefaultComboBoxModel(new String[] {"Wybor operacji", "Dodaj grupe", "Usun grupe", "Wyświetl grupe"}));
        chooseOperation.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent e) {
                if (e.getStateChange() == ItemEvent.SELECTED) {
                    String selected = (String) chooseOperation.getSelectedItem();
                    setOption(selected); //Ustawianie wybranej opcji!
                }
            }
        });
    }

    private void createSearch() { search.addActionListener(this);}

    private void createExecuteButton() {
        executeButton.addActionListener(this);
    }
    private void createWyjścieButton() {
        exitButton.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();

        if (source == search) {
            String found = search.getText().toUpperCase();
            dataUse.data.searchClass(found);
            groupData.setModel(new DefaultTableModel());
            show();
            groupData.setModel(dataUse);

        } else if (source == exitButton) {

            System.exit(0);

        } else if (source == executeButton) {

            if (selectedOption.equals("Dodaj grupe")) {

                String nazwaKlasy = JOptionPane.showInputDialog(null, "Podaj nazwę grupy:", "Wprowadź nazwę grupy", JOptionPane.INFORMATION_MESSAGE);
                String rozmiarPom = JOptionPane.showInputDialog(null, "Podaj limit osób w grupie:", "Wprowadź rozmiar grupy", JOptionPane.INFORMATION_MESSAGE);
                rozmiarGrupy = Integer.parseInt(rozmiarPom);
                dataUse.data.addClass(nazwaKlasy.toUpperCase(), rozmiarGrupy);
                groupData.setModel(new DefaultTableModel());
                show();
                groupData.setModel(dataUse);
                table.addItem(nazwaKlasy.toUpperCase());



            } else if (selectedOption.equals("Usun grupe")) {
                if (selectedGroup == "year" || selectedGroup == "Wybor grupy") {
                    JOptionPane.showMessageDialog(null, "Grupa nie została wybrana!", "Błąd", JOptionPane.WARNING_MESSAGE);
                } else {
                    dataUse.data.deleteClass(selectedGroup);
                    groupData.setModel(new DefaultTableModel());
                    show();
                    groupData.setModel(dataUse);
                    table.removeItem(selectedGroup);

                }
            } else if (selectedOption.equals("Wyświetl grupe")) {
                setGroup(selectedGroup);
                if (selectedGroup == "year" || selectedGroup == "Wybor grupy") {
                    JOptionPane.showMessageDialog(null, "Grupa nie została wybrana!", "Błąd", JOptionPane.WARNING_MESSAGE);
                } else {

                    Year ui = new Year(selectedGroup, rozmiarGrupy); //stworzenie GUI. UI - user interface
                    JPanel root = ui.getRootPanel(); //panel administratora
                    JFrame frame = new JFrame("Dziennik Elektorniczny - kierunek"); //ramka do wyświetlania GUI
                    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //operacja zamykania
                    frame.setContentPane(root);//dodanie panelu głównego do ramki
                    frame.pack();
                    frame.setLocationRelativeTo(null); //wyśrodkowanie interfejsu użytkownika
                    frame.setVisible(true);//pokazanie intefejsu użytkownika
                }
            } else if (selectedOption.equals("null") || selectedOption.equals("Wybor operacji")){
            JOptionPane.showMessageDialog(null, "Nie wybrano operacji!", "Błąd", JOptionPane.WARNING_MESSAGE);
        }
        }
    }
}
