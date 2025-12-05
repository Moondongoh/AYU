package hello.hellospring.repository;

import hello.hellospring.domain.Member;
import org.springframework.stereotype.Repository;

import java.util.*;

//여기가 구현체
public class MemoryMemberRepository implements  MemberRepository {
  private  static Map<Long, Member> store = new HashMap<>();
  private  static  long sequensce = 0L;
  @Override
  //store에 넣기 전에 멤버에 id값을 세팅.
  public Member save(Member member) {
    member.setId(++sequensce);
    store.put(member.getId(), member);
    return member;
  }

  @Override
  public Optional<Member> findById(Long id) {
    return Optional.ofNullable(store.get(id));
  }

  @Override
  public Optional<Member> findByName(String name) {
      return store.values().stream()
            .filter(member -> member.getName().equals(name))
            .findAny();
  }

  @Override
  public List<Member> findAll() {
    return new ArrayList<>(store.values());
  }

  public void clearStore() {
      store.clear();
  }
}
