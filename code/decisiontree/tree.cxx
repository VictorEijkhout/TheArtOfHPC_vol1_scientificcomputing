/****************************************************************
 ****
 **** This code is part of the book
 **** Introduction to High Performance Scientific Programming
 **** by Victor Eijkhout eijkhout@tacc.utexas.edu
 **** copyright 2010-2019
 ****
 ****************************************************************/

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

class Record {
private:
  std::vector<int> keyvalues;
  std::string description;
public:
  Record(int v1,int v2,std::string c)
    : description(c) {
    keyvalues.push_back(v1);
    keyvalues.push_back(v2);
  };
  int getkey(int i) const { return keyvalues.at(i); };
  std::string print() {
    std::string p = "(";
    for ( auto ik : keyvalues ) p += std::to_string(ik)+",";
    p += description; p += ")";
    return p;
  };
};

class RecordsTable {
private:
  std::vector<Record> table;
public:
  std::vector<Record> &gettable() { return table; };
  void push_back( Record r ) { table.push_back(r); };
  int size() const { return table.size(); };
  int min(int ik) {
    int themin = table[0].getkey(ik);
    for ( auto r : table )
      if (r.getkey(ik)<themin) themin = r.getkey(ik);
    return themin;
  };
  int max(int ik) {
    int themax = table[0].getkey(ik);
    for ( auto r : table )
      if (r.getkey(ik)>themax) themax = r.getkey(ik);
    return themax;
  };
  std::string print() {
    std::string p = "[";
    for (auto r : table) p += r.print();
    p += "]";
    return p;
  }
};

class DecisionTree {
private:
  RecordsTable table;
  int splitkey{-1},splitval;
  RecordsTable *left{nullptr},*right{nullptr};
  bool isleaf{true};
public:
  DecisionTree( RecordsTable t ) : table(t),isleaf(true) {
  };
  void split(int ik) {
    if (isleaf) {
      if (table.size()<=1)
	return;
      int themin = table.min(ik), themax = table.max(ik);
      splitval = (themin+themax)/2; splitkey = ik;
      left = new RecordsTable(); right = new RecordsTable();
      for ( auto r : table.gettable()) {
	if (r.getkey(ik)<splitval)
	  left->push_back(r);
	else
	  right->push_back(r);
      }
      isleaf = false;
    }
  };
  std::string print() {
    std::string p = "";
    if (isleaf) {
      p = table.print();
    } else {
      p += "["; p += left->print(); p += "-"+std::to_string(splitval)+"-"; p += right->print(); p += "]";
    }    
    return p;
  };
};

int main() {
  RecordsTable bigtable;
  bigtable.push_back( Record(20,160,"Miata") );
  bigtable.push_back( Record(22,100,"Rav4") );
  bigtable.push_back( Record(55,95,"Hummer") );
  bigtable.push_back( Record(60,150,"Tesla") );
  
  DecisionTree thetree(bigtable);
  std::cout << "Original tree: " << thetree.print() << std::endl;
  thetree.split(0);
  std::cout << "Split tree: " << thetree.print() << std::endl;

  return 0;
}
