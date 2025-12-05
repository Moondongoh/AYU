package hello.hellospring.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class HomeController {
//localhost8080 호출하면 바로 여기로 접속
  @GetMapping("/")
  public String home() {
    return "home";
  }
}
