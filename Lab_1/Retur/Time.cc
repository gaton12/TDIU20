// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include "Time.h"


using namespace std;

//TODO: Det ni ska kasta vid felaktig tid är ett std::exception.
//Ni ska inte fånga detta utan det gör CHECK_THROWS i huvudprogrammet.*

//TODO: Ni checkar om tiden är felaktig på flera ställen. Detta är kodupprepning.
//Gör istället en funktion som löser detta åt er och använd den på dessa ställen i koden.*

bool Time::checkTime(int const& HH, int const& MM, int const& SS ) const{
  if(HH >= 24 || MM >= 60 || SS >= 60){
    return true;
  }
  return false;
}

Time::Time(int HH, int MM, int SS): Hour{HH}, Minute{MM}, Second{SS}
{

    if(checkTime(HH,MM,SS)){
      throw invalid_argument{"Invalid Time"};
    }

}

Time::Time(): Hour{}, Minute{}, Second{}
{}

Time::Time(string TS): Hour{}, Minute{}, Second{}
  {
    string TMP{};
    int HH{};
    int MM{};
    int SS{};

    stringstream buffer;
    buffer << TS;
    getline(buffer, TMP, ':');
    HH = stoi(TMP);


    getline(buffer, TMP, ':');
    MM = stoi(TMP);


    getline(buffer, TMP, ':');
    SS = stoi(TMP);

    if(checkTime(HH,MM,SS)){
      throw invalid_argument{"Invalid Time"};
    }

    Hour=HH;
    Minute=MM;
    Second=SS;

}

bool Time::is_am() const{

if (Hour < 12){
  return true;
}

  return false;
}
int Time::hour(){

  return Hour;
}

int Time::minute(){

  return Minute;
}
int Time::second(){

  return Second;
}

string Time::to_string(bool AM_PM) const{

  stringstream buffer;
  string TMP;

  int TMP_H{Hour};

  if (AM_PM == true){
    if (Hour >= 12) {
      if (Hour > 12) {
        TMP_H += -12;
      }
      buffer << setw(2) << setfill('0') << TMP_H << ':' << setw(2) << setfill('0') << Minute << ':' << setw(2) << setfill('0') << Second << " pm";
    } else {
      buffer << setw(2) << setfill('0') << TMP_H << ':' << setw(2) << setfill('0') << Minute << ':' << setw(2) << setfill('0') << Second << " am";
    }
  } else {
    buffer << setw(2) << setfill('0') << TMP_H << ':' << setw(2) << setfill('0') << Minute << ':' << setw(2) << setfill('0') << Second;
  }
  TMP=buffer.str();
  return TMP;

}

Time::operator string() const {
  return to_string();

}


ostream& operator<<(ostream & lhs, Time const& rhs){
  lhs << rhs.to_string();
  return lhs;
}

Time Time::operator+ (int const n){

  Time TMP_TIME{*this};
  int TMP;

  TMP = (((Hour*3600)+(Minute*60)+(Second)+n)%(24*3600));

  TMP_TIME.Hour = TMP/3600;
  if(TMP_TIME.Hour == 24){TMP_TIME.Hour = 0;};

  TMP_TIME.Minute = (TMP%3600) / 60;
  TMP_TIME.Second = (TMP % 3600)%60;

  return TMP_TIME;

}

//TODO: er - operator ser inte ut att fungera för större tal.
//Testa t.ex. t-86400*10 *

//Kommentar: Använd bättre variabelnamn. *
Time Time::operator- (int const n){

  int TMPSeconds = n;
  if (TMPSeconds>(3600*24)) {
    TMPSeconds =  n % 24;
  }
  Time TMP_TIME{*this};
  int TMP;

  TMP = ((Hour*3600)+(Minute*60)+(Second));

  for (int i = 0; i < TMPSeconds; i++){
    TMP = TMP-1;
  }
  if (TMP < 0) {
    TMP = (3600*24)+TMP;
  }

  TMP_TIME.Hour = TMP/3600;
  TMP_TIME.Minute = (TMP%3600) / 60;
  TMP_TIME.Second = (TMP % 3600)%60;

  return TMP_TIME;
}

Time& Time::operator++(){

  (*this) = (*this) + 1;

  return *this;

}

Time& Time::operator--(){

  (*this) = (*this) - 1;

  return *this;

}

Time Time::operator++(int){

  Time tmp{*this};
  (*this) = (*this) + 1;

  return tmp;

}

Time Time::operator--(int){

  Time tmp{*this};
  (*this) = (*this) - 1;

  return tmp;

}

bool Time::operator==(Time const& rhs) const{

  if (Hour==rhs.Hour && Minute==rhs.Minute && Second==rhs.Second){
    return true;
  }
  return false;
}

bool Time::operator<(Time const& rhs)const{

  if (Hour<=rhs.Hour){
    return true;
  }

  if(Hour<=rhs.Hour && Minute<=rhs.Minute){
    return true;
  }

  if(Hour<=rhs.Hour && Minute<=rhs.Minute && Second<rhs.Second){
    return true;
  }

  return false;
}

bool Time::operator>(Time const& rhs)const{

  if ((*this)<(rhs)){
  return false;
  }
  return true;
}

bool Time::operator!=(Time const& rhs)const{

  if ((*this)==(rhs)){
  return false;
  }
  return true;

}

bool Time::operator>=(Time const& rhs)const{

  if ((*this)>(rhs) || (*this)==(rhs)){
  return true;
  }
  return false;

}

bool Time::operator<=(Time const& rhs)const{

  if ((*this)<(rhs) || (*this)==(rhs)){
  return true;
  }
  return false;

}

std::istream& operator>>(std::istream & lhs, Time & rhs){

  int HH{rhs.Hour};
  int MM{rhs.Minute};
  int SS{rhs.Second};
  char TMP{};


  lhs >> HH >> TMP >> MM >> TMP >> SS;



  if(HH >= 24 || MM >= 60 || SS >= 60){
    lhs.setstate(std::ios_base::failbit);
  }
  else{
    rhs.Hour = HH;
    rhs.Minute = MM;
    rhs.Second = SS;
  }
  return lhs;

}
