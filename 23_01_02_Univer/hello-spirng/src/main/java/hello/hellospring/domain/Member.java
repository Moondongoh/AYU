package hello.hellospring.domain;

import jakarta.persistence.*;

@Entity
public class Member {

  @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
  private Long id; //시스템이 저장하는 아이디 데이터 구분용

  private String name;//just 이름

  //alt + insert 후 Getter and Setter
  public Long getId() {
    return id;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }
}
