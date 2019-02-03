// [[Rcpp::plugins(cpp14)]]
#include <RcppCommon.h>

RCPP_EXPOSED_CLASS(MyClass);

#include <Rcpp.h>

class MyClass {
  public:
    MyClass(int x): value_(x) {}
    int get() const {return value_;}
  private:
    int value_;
};

inline int pass_by_value(MyClass x) {return x.get();}
inline int pass_by_refconst(const MyClass& x) {return x.get();}
inline int pass_by_pointer(MyClass* x) {return x->get();}

RCPP_MODULE(test) {
  Rcpp::class_<MyClass>("MyClass")
    .constructor<int>()
    .const_method("get", &MyClass::get)
  ;

  Rcpp::function("pass_by_value", &pass_by_value);
  Rcpp::function("pass_by_refconst", &pass_by_refconst);
  Rcpp::function("pass_by_pointer", &pass_by_pointer);
}

// [[Rcpp::export]]
int len(const std::vector<std::string>& args) {
    return args.size();
}
