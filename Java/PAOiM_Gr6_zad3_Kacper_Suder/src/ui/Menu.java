package ui;

import javax.swing.*;
import javax.swing.plaf.basic.BasicButtonListener;
import javax.swing.table.AbstractTableModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Menu implements ActionListener {
    private JPanel WyborTabeli;
    private JButton studenciNaRokuButton;
    private JButton exitButton;
    private JButton grupyDziekańskieButton;
    private JPanel Przyciski;
    private JPanel Welcome;


    public Menu() {
        createStudenciNaRokuButton();
        createGrupyDziekanskieButton();
        createExitButton();
    }
    private void createStudenciNaRokuButton() {
        studenciNaRokuButton.addActionListener(this);
    }

    private void createGrupyDziekanskieButton() {
        grupyDziekańskieButton.addActionListener(this );
    }

    private void createExitButton() {
        exitButton.addActionListener(this);
    }
    public JPanel getRootPanel() {
        return WyborTabeli;
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        if (source == studenciNaRokuButton){
            Year ui = new Year("year", 10); //stworzenie GUI. UI - user interface
            JPanel root = ui.getRootPanel(); //panel administratora
            JFrame frame = new JFrame("Dziennik Elektorniczny - kierunek"); //ramka do wyświetlania GUI
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //operacja zamykania
            frame.setContentPane(root);//dodanie panelu głównego do ramki
            frame.pack();
            frame.setLocationRelativeTo(null); //wyśrodkowanie interfejsu użytkownika
            frame.setVisible(true);//pokazanie intefejsu użytkownika
        }else if (source == grupyDziekańskieButton) {
            MainUI ui = new MainUI(); //stworzenie GUI. UI - user interface
            JPanel root = ui.getRootPanel(); //panel administratora
            JFrame frame = new JFrame("Dziennik Elektorniczny - grupy dziekańskie"); //ramka do wyświetlania GUI
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //operacja zamykania
            frame.setContentPane(root);//dodanie panelu głównego do ramki
            frame.pack();
            frame.setLocationRelativeTo(null); //wyśrodkowanie interfejsu użytkownika
            frame.setVisible(true);//pokazanie intefejsu użytkownika
        } else if (source == exitButton) {
            System.exit(0);
        }

    }
}
