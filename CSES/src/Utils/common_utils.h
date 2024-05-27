#pragma once

  //https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function?page=1&tab=votes#tab-top
  
  template<typename T>
  concept has_toString = requires(const T & t) {
    t.toString();
  };