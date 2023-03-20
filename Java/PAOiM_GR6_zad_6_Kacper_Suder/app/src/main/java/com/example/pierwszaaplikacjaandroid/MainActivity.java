package com.example.pierwszaaplikacjaandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.google.android.material.button.MaterialButton;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;

import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    TextView resultTextView, solutionTextView;
    //Tworzenie przycisków:
    MaterialButton buttonC, buttonBrackOpen, buttonBrackClose;
    MaterialButton buttonDivide, buttonMultiply, buttonPlus, buttonMinus, buttonEquals;
    //Numeryczne:
    MaterialButton button0, button1, button2, button3, button4, button5, button6, button7, button8,
            button9;
    MaterialButton buttonAC, buttonDot;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //przypisanie ID
        resultTextView = findViewById(R.id.result_textView);
        solutionTextView = findViewById(R.id.solution_textView);

        assignID(buttonC, R.id.button_c);
        assignID(buttonBrackOpen, R.id.button_open_bracket);
        assignID(buttonBrackClose, R.id.button_close_bracket);
        assignID(buttonDivide, R.id.button_devide);
        assignID(buttonMultiply, R.id.button_multiply);
        assignID(buttonPlus, R.id.button_plus);
        assignID(buttonMinus, R.id.button_minus);
        assignID(buttonEquals, R.id.button_equals);
        assignID(button0, R.id.button_zero);
        assignID(button1, R.id.button_1);
        assignID(button2, R.id.button_2);
        assignID(button3, R.id.button_3);
        assignID(button4, R.id.button_4);
        assignID(button5, R.id.button_5);
        assignID(button6, R.id.button_6);
        assignID(button7, R.id.button_7);
        assignID(button8, R.id.button_8);
        assignID(button9, R.id.button_9);
        assignID(buttonAC, R.id.button_ac);
        assignID(buttonDot, R.id.button_dot);

    }

    void assignID(MaterialButton button, int id) { //metoda do przypisania ID
        button = findViewById(id);
        button.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        MaterialButton button = (MaterialButton) view; //kliknięty przycisk
        //Stringi odp do tworzenia ciągów znaków
        String buttonText = button.getText().toString(); //konwersja na string, pobiera znak
        buttonText.replace(",", "."); //zamiana , na .
        String dataToCalculate = solutionTextView.getText().toString(); //tablica do sumowania, dodawany jest do niego znak z buttonText.
        dataToCalculate.replace(",", ".");


        if(buttonText.equals("=")) {
            String text = (String) resultTextView.getText();
            solutionTextView.setText(text.replace(",", "."));
            return;
        }

        if (buttonText.equals("AC")) { //logika przycisku AC
           solutionTextView.setText("");
           resultTextView.setText("0");
           return;
        }

        if(buttonText.equals("C")) {
           dataToCalculate = dataToCalculate.substring(0, dataToCalculate.length()-1); //bierzemy podłańcuch i usuwamy ostatni index
        } else {
            dataToCalculate = dataToCalculate + buttonText; //ciąg znaków (cyfry + znaki)
        }

        solutionTextView.setText(dataToCalculate.replace(",", "."));

        String finalResult = getResult(dataToCalculate.replace(",", "."));

        if(!finalResult.equals("Error")) { //jeżeli wynik nie jest błędem ustaw wynik
            resultTextView.setText(finalResult);
        }
    }

    String getResult(String data) {
        try {
            //skrypt i "kontekst" wykorzystywany do obliczenia, wykorzystywane z biblioteki:
            //'com.faendir.rhino:rhino-android:1.5.2'
            Context context = Context.enter(); //wprowadzony
            context.setOptimizationLevel(-1);
            Scriptable scriptable = context.initStandardObjects();
            DecimalFormat fc = new DecimalFormat("#####.##"); // dokładność liczb!
            double calc = (double) context.evaluateString(scriptable, data, "Javascript",
                    1, null);
            String finalResult = fc.format(calc); //wynik obliczeń zwracany jako string

            if(finalResult.endsWith(".0")) {
                finalResult = finalResult.replace(".0", ""); // jeżeli wynik kończy
                //się na .0, nie wyświetlaj tego
            }
            return finalResult;
        } catch (Exception e) {
            return "Error";
        }
    }
}