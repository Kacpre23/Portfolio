package com.javabunga.springbootexample.web;

import com.javabunga.springbootexample.Class;
import com.javabunga.springbootexample.Data;
import com.javabunga.springbootexample.Student;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Map;

@RestController
public class HelloWorldController {
    Data data = new Data();

    @RequestMapping("/hello")
    public String sayHello(@RequestParam(value = "name") String name) {
        return "Hello " + name + "!";
    }

   @GetMapping("/year")
    public List <Student> studenciNaRoku(@RequestParam(value = "name", defaultValue = "Pierwsza") String name) {
       // if (students.isEmpty()) return () -> new StudentNotFoundException();
        return  data.returnYearConteiner().getClass2().listaStudentowYear;
        //StudentNotFoundException();
    }


    @GetMapping("/api/course")
    public Map<String, Class> grupy() {
       // Map<String, Class> classMap = data.returnClassConteiner().grupy;
        return data.returnClassConteiner().grupy;

    }
}
