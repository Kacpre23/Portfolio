package com.javabunga.springbootexample.web;

import com.javabunga.springbootexample.Class;
import com.javabunga.springbootexample.Data;
import com.javabunga.springbootexample.Student;
import com.javabunga.springbootexample.error.DataNotFound;
import com.javabunga.springbootexample.error.StudentNotFoundException;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.Vector;

@RestController
public class HelloWorldController {
    Data data = new Data();

//Testowe
    @GetMapping("/hello")
    public String sayHello (@RequestParam(value = "name") String name) {
        return "Hello " + name + "!";
    }

//Wypisanie studentow na roku
   @GetMapping("/year")
    public List <Student> studenciNaRoku() {
       try {

           return data.returnYearConteiner().getClass2().listaStudentowYear;
       } catch (Exception e) {
           throw new DataNotFound();
       }
    }

//Wypisanie grup
    @GetMapping("/group")
    public Map<String, Class> grupy() {
        try {
        return data.returnClassConteiner().grupy;
        } catch (Exception e) {
            throw new DataNotFound();
        }
    }

//Zapis do Pliku
    @GetMapping("/year/csv")
    void zapisDoPliku() {
        try {
            data.writeToCsvFile();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

//Sortowanie

    @GetMapping("/year/sortname")
    Vector<Student> sortByName() {
        data.returnYearConteiner().getClass2().sortByName();
        return  data.returnYearConteiner().getClass2().listaStudentowYear;
    }

    @GetMapping("/year/sortsurname")
    public Vector<Student> sortBySurname() {
        data.returnYearConteiner().getClass2().sortBySurname();
        return  data.returnYearConteiner().getClass2().listaStudentowYear;
    }
    @GetMapping("/year/sortpoints")
    public Vector<Student> sortByPoints() {
        data.returnYearConteiner().getClass2().sortByPoints();
        return  data.returnYearConteiner().getClass2().listaStudentowYear;
    }
    @GetMapping("/year/sortid")
    public Vector<Student> sortById() {
        data.returnYearConteiner().getClass2().sortById();
        return  data.returnYearConteiner().getClass2().listaStudentowYear;
    }

//Dodaj Studenta
    @PostMapping("/year")
    public Student dodajStudenta(@RequestBody Student student) {
        Student pom = data.returnYearConteiner().getClass2().addStudent(student);
        data.addToList(pom);
        return pom;
    }
//Dodaj Punkty
    @PostMapping("/yearaddpoints/nazwisko/{name}/punkty/{points}")
    public void dodajPunkty(
            @PathVariable(value = "name", required=true) String name,
            @PathVariable(value = "points", required=true) Double points
    ) {
        Boolean pom;
        pom = data.returnYearConteiner().getClass2().changePointsAdd(name.toUpperCase(), points);
        if (pom == false) {
            throw new StudentNotFoundException();
        }
    }
//Usun Punkty
    @PostMapping("/yeartakepoints/nazwisko/{name}/punkty/{points}")
    public void usunPunkty(
            @PathVariable(value = "name", required=true) String name,
            @PathVariable(value = "points", required=true) Double points
    ) {
        Boolean pom;
        pom = data.returnYearConteiner().getClass2().changePointsRemove(name.toUpperCase(), points);
        if (pom == false) {
            throw new StudentNotFoundException();
        }
    }

//Dodanie grupy
    @PostMapping("/group")
    public Map<String, Class> dodajGrupe(@RequestBody Class newclass) {
        return data.returnClassConteiner().addClass(newclass);
    }

//Usuwanie Grupy
    @DeleteMapping("/group/{name}")
    public Map<String, Class> usunGrupe(@PathVariable(name = "name") String name) {
        if (null == data.returnClassConteiner().removeClass(name.toUpperCase())) {
            throw new StudentNotFoundException();
        } else {
            return data.returnClassConteiner().removeClass(name.toUpperCase());
        }
    }
//Wypisanie grupy
    @GetMapping("/groupname")
    public Map<String, Class> wypiszGrupe(@RequestParam(value = "name") String name){
        if (null ==  data.returnClassConteiner().getSearchClass(name.toUpperCase())) {
            throw new StudentNotFoundException();
        } else {
          return data.returnClassConteiner().getSearchClass(name.toUpperCase());
        }
    }
//Zapelnienie procentowe grupy
    @GetMapping("/grouppercent")
    public String zapelnienieGrupy(@RequestParam(value = "name") String name) {
        if(data.returnClassConteiner().percentOfGroup(name.toUpperCase()).equals("false")) {
            throw new StudentNotFoundException();
        } else {
            return "Zapelnienie procentowe grupy " + name.toUpperCase() + ": " + data.returnClassConteiner().percentOfGroup(name.toUpperCase());
        }

    }

//Usuwanie Studenta wedlug nazwiska

    @DeleteMapping("/year/name")
    public void usunStudentaPoNazwisku(@RequestParam(value = "name") String name) {
        Boolean pom;
        pom = data.deleteStudentYear(name.toUpperCase());
        if(pom == false) {
            throw new StudentNotFoundException();
        }
    }

 //Usuwanie studenta po ID
    @DeleteMapping("/year/{id}")
    public void usunStudenta(@PathVariable int id) {
        boolean pom;
        pom = data.deleteStudentYear(id);
        if(pom == false) {
            throw new StudentNotFoundException();
        }
    }


}
