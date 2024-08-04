#include<iostream>
#include<cstring>
#include<string>
#include<stdexcept>
#include"List.h"
using namespace std;

List::Node::Node(keyType k, valType v){
  key = k;
  val = v;
  prev = nullptr;
  next = nullptr;
}

List::List(){
  front = nullptr;
  back = nullptr;
  cursor = nullptr;
 // beforeCursor = nullptr;
  //afterCursor = nullptr;
  pos_cursor = -1;
  num_elements = 0;

}

List::~List(){
  clear();
}

int List::length(){
  return num_elements;
}

valType List::Front(){
  return front->val;
}

string List::current(){
  string s;
  s.append(cursor->key + " : " + std::to_string(cursor->val));
  return s;
}

string List::currentKey(){
  string s;
  s.append(cursor->key);
  return s;
}

valType List::currentVal(){
  return cursor->val;
}

valType List::Back(){
  return back->val;
}

int List::position(){
  return pos_cursor;
}
//manipulate
void List::clear(){
  moveBack();
  //cout<<"this is now at: "<<position()<<endl;
  while (cursor != nullptr){
    //moveBack();
    Node* t = cursor;
    movePrev();
    delete t;
    num_elements--;
    //cout<<"length is: "<<length()<<endl;
  }
}

void List::moveFront(){
  if(length() == 0){return;}
  else{
    cursor = front;
    //beforeCursor = front->prev;
    //afterCursor = front->next;
    pos_cursor = 0;
  }
}

void List::moveBack(){
  if(length() == 0){return;}
  else{
    cursor = back;
    //beforeCursor = back->prev;
    //afterCursor = back->next;
    pos_cursor = length()-1;
  }
}

void List::moveNext(){
  if(length() == 0){return;}
  if(cursor->next == nullptr){
    cursor = nullptr;
    pos_cursor = -1;
    return;
  }
  pos_cursor++;
  cursor = cursor->next;
  //cout<<"cursor is now at: "<<current()<<endl;
}

void List::movePrev(){
  if(length() == 0){return;}
  if(cursor->prev == nullptr){
    cursor = nullptr;
    pos_cursor = -1;
    //cout<<"its null?? moveprev"<<endl;
    return;
  }
  pos_cursor--;
  cursor = cursor->prev;
}

void List::insertAfter(keyType k, valType v){
  Node* N = new Node(k,v);
  if( length() == 0){
    //cout<<"no nodes adding first!"<<endl;
    front = N;
    back = N;
    cursor = N;
    pos_cursor = 0;
    num_elements++;
  }
  else{
    if(cursor == nullptr){moveBack();}//incase cursor was reset to factory, automatically just insert at end of list
    if(cursor==back){
      back = N;
    }
    if(cursor->next != nullptr){cursor->next->prev = N;}
    //cursor->next->prev = N;
    N->prev = cursor;
    N->next = cursor->next;
    cursor->next = N;
    cursor = N;
    //pos_cursor++;
    num_elements++;
  }
}

void List::insertBefore(keyType k, valType v){
  Node* N = new Node(k,v);
  if( length() == 0){
    front = N;
    back = N;
    cursor = N;
    pos_cursor = 0;
    num_elements++;
  }
  else{
    if(cursor == nullptr){moveFront();}//incase cursor reseted to facotry just start inserting at front
    if(cursor==front){
      front = N;
    }
    if(cursor->prev != nullptr){cursor->prev->next = N;}
    N->prev = cursor->prev;
    N->next = cursor;
    cursor->prev = N;
    cursor = N;
    //pos_cursor;
    num_elements++;
  }

}

void List::setValue(valType v){
  if(cursor ==nullptr){return;}
  cursor->val = v;
}


void List::organizedList(){
  List M;
  keyType KEY = "NIL";
  valType BIG = 0;
  moveFront();
  while(length()!= M.length()){
    while(cursor != nullptr){
      if(BIG == currentVal() && currentVal() != 0){
        if(KEY > currentKey()){
          KEY = currentKey();
        }
      }
      else{ 
        if(BIG < currentVal()){
          BIG = currentVal();
          KEY = currentKey();
        }
      }
      moveNext();
    } 
    M.insertAfter(KEY,BIG);
    gotoKey(KEY);
    setValue(0);
    moveFront();
    BIG = 0;
  }
  clear();
  M.moveFront();
  while(M.position() != -1){
    insertAfter(M.currentKey(),M.currentVal());
    M.moveNext();
  }
  M.clear();  
}


bool List::keyinList(keyType k){//resets cursor pos!!!!!
  moveFront();
  while(position() != -1){
    if(k == cursor->key){
      return true;
    }
    moveNext();
  }
  return false;
}

void List::gotoKey(keyType k){//lowkey useless in certain situations, its already on that key anyways.......
  if(keyinList(k) == true){
    moveFront();
    while(k != cursor->key){
      moveNext();
    }
  }
}

keyType List::keyinPos(int p){
  if(abs(p) < length()){
    moveFront();
    while(position() != p){
      moveNext();
    }
    return currentKey();
  }
  else{return "-";}//return - if pos non exsistent
}

std::string List::to_string(){//remember after running this does not save previous cursor position!!!!
  std::string s;
  moveFront();//resets cursor back to front!
  //cout<<"front is :"<<L.Front()<<endl;
  Node* N = cursor;
  while(N != nullptr){
    s.append(N->key);
    s.append(" : ");
    s.append(std::to_string(N->val));
    s.append("\n");
    //cout<<s<<endl;
    N = N->next;
  }
  return s;
}

std::ostream& operator<<(std::ostream& stream, List& L){
  return stream << L.to_string();
}
