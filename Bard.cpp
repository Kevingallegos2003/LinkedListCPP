#include<iostream>
#include<fstream>
#include<string>
#include"List.h"

using namespace std;

int main(int argc, char* argv[]){
  ifstream in;
  ifstream shake;
  ofstream out;

  if(argc != 3){
    cerr<<"Error, invalid amount of arguments"<<endl;
  }
  in.open(argv[1]);
  if(!in.is_open()){
    cerr<<"Unable to open: "<<argv[1]<<endl;
  }
  out.open(argv[2]);
  if(!out.is_open()){
    cerr<<"Unable to open: "<<argv[2]<<endl;
  }
  shake.open("shakespeare-cleaned5.txt");//shakespeare-cleaned5.txt
  if(!shake.is_open()){
    cerr<<"Unable to open: test.txt"<<endl;//error message shouldnt popup anyways
  }
  int lines = 0;
  string s;
  string inputL;
  string Pinput;
  size_t LEN;//Inputs desired length of word
  int RANK;//input's desired rank of word being LEN length
  List L;
  getline(in, inputL);//if first line "60 3" for ex, inputL is a string"60 3" seperate and convert these to int
  while(!in.eof()){
    //getline(in, inputL);
    //cout<<inputL<<endl;
    LEN = atoi((inputL.substr(0,inputL.find(' '))).c_str());  //grabs first num in inputL and uses it for loop
    RANK = atoi((inputL.substr(inputL.find(' '),-1).c_str()));//grabs second num in inputL and uses it for loop
    //cout<<x<<endl;
    //cout<<y<<endl;
    while(getline(shake,s)){//iterate through lines in shakespeare file
      //cout<<"first word in loop s "<<s<<endl;
      if(s.length() == LEN){//is length of shakespeare word equal to (LEN) length desired, grabbed from inputL
        if(L.keyinList(s) == false){L.insertAfter(s, 1);}//is it in the list already? no? add it
        else{
          L.gotoKey(s);//it is list, find the node and update the node to have +1 in its value
          L.setValue(L.currentVal() + 1);
        }
      }
      lines++;//debugging variable, remove this var later
    }
    if(L.length() != 0){//did the loop actually find words of desired LEN length?
      L.organizedList();//atrocious organzing func that is very likely flawed but it does its job for tested situations
      out<<L.keyinPos(RANK)<<endl;//now that list is organized grab the one in index RANK since input file wants that one
      //cout<<L<<endl;
    }
    else{out<<"-"<<endl;}//doesnt exsist? cool just give output "-"
    //cout<<"words in list for "<<LEN<<" letter words"<<endl<<L;
    L.clear();//clear list to avoid issues reusing it in loop
    Pinput = inputL;//garbage delete this debugging stuff
    getline(in, inputL);//everytime this is run it grabs a new line from input, ex"2 0"
    //cout<<"lines read from shake "<<lines<<endl;
    //cout<<"shake eof = "<<shake.eof()<<endl;
    lines = 0;
    shake.clear();//VERY IMPORTANT, moves the shakespeare file back up to iterate through words for next loop
    shake.seekg(0,shake.beg);//above wont work without this func
  }

  L.clear();
  in.close();
  shake.close();
  out.close(); 
}

/*
int main(){
  List L;
  L.insertAfter("mom",20);
  L.insertAfter("dad",23);
  L.insertAfter("dbd", 23);
  L.insertAfter("baby",1);
  cout<<L;
  L.moveBack();
  L.setValue(999);
  L.organized();
  cout<<L;
  L.moveFront();
  cout<<L.keyinList("mom")<<endl;
  cout<<L.keyinList("urmom")<<endl;
  L.moveFront();
  L.gotoKey("dad");
  cout<<L.current()<<endl;
  cout<<L.keyinPos(0)<<endl;
  cout<<L.keyinPos(1)<<endl;
  cout<<L.keyinPos(2)<<endl;
  cout<<L.keyinPos(3)<<endl;
  cout<<L.keyinPos(4)<<endl;
  cout<<L.keyinPos(-4)<<endl;
}
*/
