#include<iostream>
#include<string>

#ifndef LIST
#define LIST

using namespace std;
typedef string keyType;
typedef int valType;

class List{
private:
  struct Node{
    keyType key;
    valType val;
    Node* next;
    Node* prev;
    Node(keyType k, valType v);
  };

  Node* front;
  Node* back;
  //Node* beforeCursor;
  //Node* afterCursor;
  Node* cursor;
  int pos_cursor;
  int num_elements;

public:  
  List();
  List(const List& L);
  ~List();

  //access

  int length();
  valType Front();
  valType Back();
  string current();
  valType currentVal();
  string currentKey();
  int position();
  keyType keyinPos(int p);
  //valType peekNext() const;
  //valType peekPrev() const;

  //manipulation

  void clear();
  void moveFront();
  void moveBack();
  void moveNext();
  void movePrev();
  void insertAfter(keyType k, valType v);
  void insertBefore(keyType k, valType v);
  void setValue(valType v);
  bool keyinList(keyType k);
  void gotoKey(keyType k);
  void organizedList();
  //void setAfter(valType x);
  //void setBefore(valType);
  //void eraseAfter();
  //void eraseBefore();
  //int findNext(valType);
  std::string to_string();
  //overload

  friend std::ostream& operator<<(std::ostream& stream, List& L);
};
#endif