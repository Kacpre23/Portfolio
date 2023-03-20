package com.javabunga.springbootexample.error;

import jakarta.servlet.http.HttpServletResponse;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ExceptionHandler;

import java.io.IOException;

public class StudentNotFoundException extends RuntimeException {

    @ExceptionHandler(NotFoundExceptionConteiner.class)
    public void springHandleNotFound(HttpServletResponse response) throws IOException {
        response.sendError(HttpStatus.NOT_FOUND.value());
    }

}
