/****************
 * test program for pure virtual classes
 ****************/

class abstract {
public:
  virtual void apply() = 0;
};

class concrete : public abstract {
public:
  concrete() {};
  virtual void apply() {};
};

class has {
private:
  abstract applier;
public:
  has( abstract &applier )
    : applier(applier) {};
  void do() { applier.apply(); };
};

int main() {
  concrete applier;
  has doer( applier );
  return 1;
};


  
