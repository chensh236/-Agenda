#include <sstream>
#include "Date.hpp"
#include <iostream>
#include <cstring>
using namespace std;
  /**
  * @brief default constructor
  */
  Date::Date(){
    m_year = 0;
    m_month =0;
    m_day = 0;
    m_hour = 0;
    m_minute =0;



}

  /**
  * @brief constructor with arguments
  */
  Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute):m_year(t_year),m_month(t_month),m_day(t_day),m_hour(t_hour),m_minute(t_minute){}

  /**
  * @brief constructor with a string
  */
  Date::Date(const std::string &dateString){
    m_year = 0;
    m_month =0;
    m_day = 0;
    m_hour = 0;
    m_minute =0;

    if (dateString.size()!= 16)
    {
      return;
    }
    if (!(dateString[4] == '-' && dateString[7] == '-' && dateString[10] == '/' && dateString[13] == ':'))
    {
      return;
    }

    for (int i = 0; i < dateString.size(); ++i)
    {
      if (i == 4 || i == 7 || i == 10 || i == 13)
      {
        continue;
      }
      if (!(dateString[i] >= '0' && dateString[i] <= '9')) return;
    }
    m_year = (dateString[0]-48) * 1000+ (dateString[1]-48) * 100 + (dateString[2]-48) * 10 + (dateString[3]-48);
    m_month = (dateString[5]-48) * 10 + (dateString[6]-48);
    m_day = (dateString[8]-48) * 10 + (dateString[9]-48);
    m_hour = (dateString[11]-48) * 10 + (dateString[12]-48);
    m_minute = (dateString[14]-48) * 10 + (dateString[15]-48);
      
  
    return;
      }
  /**
  * @brief return the year of a Date
  * @return   a integer indicate the year of a date
  */
  int Date::getYear(void) const{
    return m_year;
  }

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void Date::setYear(const int t_year){
    m_year = t_year;
  }

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int Date::getMonth(void) const{
    return m_month;
  }

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void Date::setMonth(const int t_month){
    m_month = t_month;
  }

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int Date::getDay(void) const{
    return m_day;
  }

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void Date::setDay(const int t_day){
    m_day = t_day;
  }

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int Date::getHour(void) const{
    return m_hour;
  }

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void Date::setHour(const int t_hour){
    m_hour = t_hour;
  }

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int Date::getMinute(void) const{
    return m_minute;
  }

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void Date::setMinute(const int t_minute){
    m_minute = t_minute;
  }

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
  bool Date::isValid(const Date &t_date){
    if (!(t_date.getYear()>=1000 && t_date.getYear()<=9999))
    {
      return false;
    }
    if (!(t_date.getMonth()>=1 && t_date.getMonth()<=12))
    {
      return false;
    }
    if (!(t_date.getHour()>=0 && t_date.getHour()<=23))
    {
      return false;
    }
    if (!(t_date.getMinute()>=0 && t_date.getMinute()<=59))
    {
      return false;
    }

    if (t_date.getMonth()!=2)
    {
      switch(t_date.getMonth()){
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:
          if(t_date.getDay() < 1 || t_date.getDay() > 31) return false;
          break;
        case 4:case 6:case 9:case 11:
          if(t_date.getDay() < 1 || t_date.getDay() > 30) return false;
          break;
      }
    }
    else {
        if ((t_date.getYear() % 100 != 0 && t_date.getYear() % 4 == 0 )|| t_date.getYear() % 400 == 0)
        {
          if(t_date.getDay() < 1 || t_date.getDay() > 29) return false;
        }
        else {
          if(t_date.getDay() < 1 || t_date.getDay() > 28) return false;
        }
    }
    return true;
  }

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  Date Date::stringToDate(const std::string &t_dateString){
    if (t_dateString.size()!= 16)
    {
     Date tmp("0000-00-00/00:00");
      return tmp;
    }
    if (!(t_dateString[4] == '-' && t_dateString[7] == '-' && t_dateString[10] == '/' && t_dateString[13] == ':'))
    {
     Date tmp("0000-00-00/00:00");
      return tmp;
    }
    Date tmp(t_dateString);
    return tmp;
  }

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  std::string Date::dateToString(const Date &t_date){
   
    std::stringstream ss;
  
  bool flag = isValid(t_date);
  if(!flag){
  ss<<"0000-00-00/00:00";
  return ss.str();
  }
    ss<<t_date.getYear()<<"-";
    if (t_date.getMonth() < 10)
    {
      ss<<"0";
    }

    ss<<t_date.getMonth()<<"-";
if (t_date.getDay() < 10)
    {
      ss<<"0";
    }
    ss<<t_date.getDay()<<"/";

if (t_date.getHour() < 10)
    {
      ss<<"0";
    }
    ss<<t_date.getHour()<<":";
if (t_date.getMinute() < 10)
    {
      ss<<"0";
    }
    ss<<t_date.getMinute();
    return ss.str();
  }

  /**
  *  @brief overload the assign operator
  */
  Date & Date::operator=(const Date &t_date){
    setYear(t_date.getYear());
    setMonth(t_date.getMonth());
    setDay(t_date.getDay());
    setHour(t_date.getHour());
    setMinute(t_date.getMinute());
    return *this;
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const{
    if (m_year == t_date.m_year && m_month == t_date.m_month && m_day == t_date.m_day && m_hour == t_date.m_hour && m_minute == t_date.m_minute)
    {
      return true;
    }
    return false;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const{
    if (m_year > t_date.m_year)
    {
return true;
    }
    else if(m_year == t_date.m_year){

    if (m_month > t_date.m_month)
    {
return true;
    }
    else if(m_month == t_date.m_month){
    if (m_day > t_date.m_day)
    {
return true;
    }
    else if(m_day == t_date.m_day){
  if (m_hour > t_date.m_hour)
    {
return true;
    }
    else if(m_hour == t_date.m_hour){
    if (m_minute > t_date.m_minute)
    {
return true;
    }
    else return false;



    }
    else return false;


  }
    else return false;
   


    }
    else return false;



    }
    else return false;
  }
    

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const{
      if (m_year < t_date.m_year)
    {
return true;
    }
    else if(m_year == t_date.m_year){

    if (m_month < t_date.m_month)
    {
return true;
    }
    else if(m_month == t_date.m_month){
    if (m_day < t_date.m_day)
    {
return true;
    }
    else if(m_day == t_date.m_day){
  if (m_hour <t_date.m_hour)
    {
return true;
    }
    else if(m_hour == t_date.m_hour){
    if (m_minute < t_date.m_minute)
    {
return true;
    }
    else return false;



    }
    else return false;


  }
    else return false;
   


    }
    else return false;



    }
    else return false;
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const{
    if (*this < t_date)
    {
      return false;
    }
    return true;
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const{
     if (*this > t_date)
    {
      return false;
    }
    return true;
  }

