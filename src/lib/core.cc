#include "core.h"

#include <iostream>
using namespace std;

string is_type(int t_flag) {
  switch (t_flag) {
  case 0:
    return "i64";
  case 1:
    return "i32";
  case 2:
    return "i16";
  case 3:
    return "i8";
  case 4:
    return "f64";
  default:
    return "i64";
  }
}

string GET_VALUE(word w) {
  int t_flag = w.t_flag;
  if (is_type(t_flag) == "i64") {
    return to_string(w.value.INT);
  } else if (is_type(t_flag) == "i32") {
    return to_string(w.value.INT32);
  } else if (is_type(t_flag) == "i16") {
    return to_string(w.value.INT16);
  } else if (is_type(t_flag) == "i8") {
    return to_string(w.value.INT8);
  } else if (is_type(t_flag) == "f64") {
    return to_string(w.value.FLOAT);
  }
  return "";
}
