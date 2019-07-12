#include "Storage.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Path.hpp"
using namespace std;

std::shared_ptr<Storage> Storage::m_instance = nullptr;

  /**
  *   default constructor
  */
  Storage::Storage(){
    m_dirty = false;
    //cout<<"read"<<endl;
    readFromFile();
  }

  /**
  *   disallow the copy constructor and assign operator
  */
  

  /**
  *   read file content into memory
  *   @return if success, true will be retucfrned
  */
  bool Storage::readFromFile(void){
    m_meetingList.clear();
    m_userList.clear();
    ifstream ifs;
    Path pth;
    //const char *Path::meetingPath = "/tmp/meetings.csv";
//const char *Path::userPath = "/tmp/users.csv";
    ifs.open(pth.meetingPath);
    if(!ifs.is_open()) {
      
      return false;
    }
    while(!ifs.eof()){
      string str;
      getline(ifs,str);
      if (str.size()== 0)
      {
        continue;
      }
      int index = 0, start, end;
      if (index<str.size())
      {
        string sponsor,starttime,endtime,title;
        std::vector<std::string> participators;
        start = ++index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        sponsor = str.substr(start,end - start + 1);
          index+=3;
        start = index;
        while(str[index]!='\"'){
          while(str[index]!='&' && str[index]!='\"'){
          index++;
          }
          end = index - 1;
          participators.push_back(str.substr(start,end - start + 1));
          if (str[index]=='&' )
          {
            start = ++index;
          }
        }



          index+=3;
        start = index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        starttime = str.substr(start,end - start + 1);



          index+=3;
        start = index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        endtime = str.substr(start,end - start + 1);



          index+=3;
        start = index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        title = str.substr(start,end - start + 1);
        
        Date start(starttime);
        Date end(endtime);
        Meeting tmp(sponsor,participators,start,end,title);
        m_meetingList.push_back(tmp);
      }
    }
    ifs.close();
    ifs.open(pth.userPath);
    if(!ifs.is_open()) return false;
    while(!ifs.eof()){
      string str;
      getline(ifs,str);
      if (str.size()== 0)
      {
        continue;
      }
      int index = 0, start, end;
        string name,password,email,phone;

        start = ++index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        name = str.substr(start,end - start + 1);
        index+=3;
        start = index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        password = str.substr(start,end - start + 1);
          index+=3;
        start = index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        email = str.substr(start,end - start + 1);
          index+=3;
        start = index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        phone = str.substr(start,end - start + 1);
        User tmp(name,password,email,phone);
        m_userList.push_back(tmp);
      

    }
    ifs.close();

    return true;
  }

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
  bool Storage::writeToFile(void){
    ofstream ofs;
    Path pth;
    ofs.open(pth.userPath);
    if(!ofs.is_open()) return false;
    for (std::list<User>::iterator iter = m_userList.begin();iter != m_userList.end(); ++iter)
    {
        ofs<<"\""<<(*iter).getName()<<"\""<<","<<"\""<<(*iter).getPassword()<<"\""<<",";
        ofs<<"\""<<(*iter).getEmail()<<"\""<<","<<"\""<<(*iter).getPhone()<<"\"";
       std::list<User>::iterator diter = iter;
        diter++;
        if (diter!= m_userList.end())
    {
      ofs<<endl;
    }
    }
    ofs.close();
    ofs.open(pth.meetingPath);
    if(!ofs.is_open()) return false;
    for (std::list<Meeting>::iterator iter = m_meetingList.begin();iter != m_meetingList.end(); ++iter)
    {
      
        ofs<<"\""<<(*iter).getSponsor()<<"\""<<",";
        ofs<<"\"";
        for (int i = 0; i < (*iter).getParticipator().size(); ++i)
        {
          ofs<<(*iter).getParticipator()[i];
          if (i < (*iter).getParticipator().size() - 1)
          {
            ofs<<"&";
          }
        }
        ofs<<"\""<<","<<"\"";
        ofs<<Date::dateToString((*iter).getStartDate())<<"\""<<",";
        ofs<<"\"";
        ofs<<Date::dateToString((*iter).getEndDate())<<"\""<<","<<"\"";
        ofs<<(*iter).getTitle()<<"\"";
        std::list<Meeting>::iterator diter = iter;
        diter++;
        if (diter!= m_meetingList.end())
    {
      ofs<<endl;
    }
    }
    
    return true;


  }

  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
  std::shared_ptr<Storage> Storage::getInstance(void){
    if (m_instance == nullptr) m_instance.reset(new Storage);
    return m_instance;
  }

  /**
  *   destructor
  */
  Storage::~Storage(){
    sync();
  }

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
  void Storage::createUser(const User &t_user){
    m_userList.push_back(t_user);
    m_dirty = true;
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const{
    std::list<User> lis;
    for(std::list<User>::const_iterator iter = m_userList.begin(); iter != m_userList.end(); iter++)
  {

    if (filter(*iter))
    {
      lis.push_back(*iter);
    }
  }
  return lis;
  }

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher){


    int sum = 0;
    for (std::list<User>::iterator iter = m_userList.begin(); iter != m_userList.end(); ++iter)
    {
      if(filter(*iter)){
        switcher(*iter);
        ++sum;
        m_dirty = true;
      }
    }
    
    return sum;
  }

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int Storage::deleteUser(std::function<bool(const User &)> filter){
    int sum = 0;
    for (std::list<User>::iterator iter = m_userList.begin(); iter != m_userList.end();++iter){
      if (filter(*iter))
      {
        std::list<User>::iterator diter = iter;
        diter--;
        m_userList.erase(iter);
        sum++;
         m_dirty = true;
         iter = diter;
      }
      
    }
  
    return sum;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void Storage::createMeeting(const Meeting &t_meeting){
     m_dirty = true;
    m_meetingList.push_back(t_meeting);
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  std::list<Meeting> Storage::queryMeeting(
      std::function<bool(const Meeting &)> filter) const{
    std::list<Meeting> lis;
    for(std::list<Meeting>::const_iterator iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++)
  {
    if (filter(*iter))
    {
      lis.push_back(*iter);
    }
  }
  return lis;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher){ 
    int sum = 0;
    for (std::list<Meeting>::iterator iter = m_meetingList.begin(); iter != m_meetingList.end(); ++iter)
    {
      if(filter(*iter)){
          switcher(*iter);
          ++sum;
          m_dirty = true;
      }
    }
    return sum;
  }

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter){
    int sum = 0;
    for (std::list<Meeting>::iterator iter = m_meetingList.begin(); iter != m_meetingList.end();++iter){
      if (filter(*iter))
      {
        std::list<Meeting>::iterator diter = iter;
        diter--;
        m_meetingList.erase(iter);
        sum++;
        iter = diter;
         m_dirty = true;
      }
    }   
    return sum;
  }

  /**
  * sync with the file
  */
  bool Storage::sync(void){
    if (m_dirty == true)
    {
     m_dirty = false;
    return writeToFile();
    }
   return false;
 
  }
  