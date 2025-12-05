package hello.hellospring.repository;

import hello.hellospring.domain.Member;

import java.util.List;
import java.util.Optional;

public interface MemberRepository {
  Member save(Member member); //회원 저장

  Optional<Member> findById(Long id); //아이디로 회원 찾기 null을 Optional로 처리한다함

  Optional<Member> findByName(String name); // 이름으로 회원 찾기

  List<Member> findAll();
}
