#include "AgendaService.hpp"
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include "Date.hpp"
#include "User.hpp"
#include "Meeting.hpp"
#include "Storage.hpp"
#include "Myexception.hpp"
#include <iostream>
using namespace std;



  /**
   * constructor
   */
  AgendaService::AgendaService(){
   startAgenda();
     }

  /**
   * destructor
   */
  AgendaService::~AgendaService(){
   quitAgenda();
  }

  /**
   * check if the username match password
   * @param userName the username want to login
   * @param password the password user enter
   * @return if success, true will be returned
   */
  bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
   auto func = [userName,password](const User& user){
    return (user.getName() == userName && user.getPassword() == password);    
   };

    auto ulist = m_storage->queryUser(func);
    return (ulist.size() > 0);
  }

  /**
   * regist a user
   * @param userName new user's username
   * @param password new user's password
   * @param email new user's email
   * @param phone new user's phone
   * @return if success, true will be returned
   */
  bool AgendaService::userRegister(const std::string &userName, const std::string &password,
                    const std::string &email, const std::string &phone){
   auto func = [userName,password,email,phone](const User& user){
    if (user.getName() == userName)
    {
     return true;
    }
    return false;
    
   };
   auto plist = m_storage->queryUser(func);
   if (plist.size() > 0) return false;
    
    m_storage->createUser(User(userName,password,email,phone));
   return true;
  }

  /**
   * delete a user
   * @param userName user's username
   * @param password user's password
   * @return if success, true will be returned
   */
  bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
   auto func = [userName,password](const User& user){
    return (user.getName() == userName && user.getPassword() == password);
    };
   int count = m_storage->deleteUser(func);
   if (count <= 0) return false;    //delete the list of the name

 auto func2 = [userName](const Meeting& meeting){
    if (meeting.isParticipator(userName))
    {
     return true;
    }
    return false;
    
   };
   auto operate = [userName](Meeting& meeting){
    meeting.removeParticipator(userName);
   };
   int dcount = m_storage->updateMeeting(func2,operate);

   if (dcount > 0){
    auto deletemetg = [](const Meeting& meeting){
     auto plist = meeting.getParticipator();
     if(plist.size() == 0) return true;
     return false;
    };

    int size = m_storage->deleteMeeting(deletemetg);

   }
   //delete participator
   auto dsponsor = [userName](const Meeting& meeting){
    return (meeting.getSponsor() == userName);
   };
   int dspon = m_storage->deleteMeeting(dsponsor);
   return true;
  }

  /**
   * list all users from storage
   * @return a user list result
   */
  std::list<User> AgendaService::listAllUsers(void) const{
   auto func = [](const User& user){ 
     return true;
   };
   return m_storage->queryUser(func);
  }

  /**
   * create a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @param startData the meeting's start date
   * @param endData the meeting's end date
   * @return if success, true will be returned
   */
  bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator){
     Date start(startDate);
     Date end(endDate);
    if(!(Date::isValid(start) && Date::isValid(end))) throw MyException("inValid Date!");
    if (start >= end) throw MyException("Start date >= End date!");
    if(participator.empty())throw MyException("No participator!");
    //cout<<"dddd"<<endl;
    auto querytitle = [title](const Meeting& meeting){
    return (meeting.getTitle() == title);
   } ;
   if ((m_storage->queryMeeting(querytitle)).size() > 0)
   {
    throw MyException("Multiply title!");
   }
//cout<<"dddd"<<endl;
    vector<string> uservec;
    uservec.push_back(userName);
    for (int i = 0; i < participator.size(); ++i)
    {
     uservec.push_back(participator[i]);
    }

    for (int i = 0; i < uservec.size(); ++i)
    {
     for (int index = 0; index < uservec.size(); ++index)
     {
      if (i != index && uservec[i] == uservec[index])
      {
      throw MyException("Multiply names!");
      }
     }
    }//the same

//cout<<"dddd"<<endl;
    for (int i = 0; i < uservec.size(); ++i)
    {
      string str = uservec[i];
    auto queryuser = [str](const User& user){
    return (user.getName() == str);
   };
   if ((m_storage->queryUser(queryuser)).empty())
   {
    throw MyException("The user hasn't been assigned!");
   }//judge participator
    

   auto querydate = [str,startDate,endDate](const Meeting& meeting){
   if (!(meeting.getSponsor() == str ||meeting.isParticipator(str))) return false;
  
    Date start(startDate);
    Date end(endDate);
    if (meeting.getStartDate() >= end || meeting.getEndDate() <= start)
    {
     return false;
    }
    return true;
   };
  
   auto mlist = m_storage->queryMeeting(querydate);
   if (mlist.size() > 0)
   {
    throw MyException("The user has the other meeting at the same time!");
   }

    }
   // cout<<"dddd3"<<endl;
   m_storage->createMeeting(Meeting(userName,participator,start,end,title));
   return true;
  }

  /**
   * add a participator to a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @return if success, true will be returned
   */
  bool AgendaService::addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator){
    if (userName == participator)
    {
      throw MyException("userName equal to participator!");
    }
   auto queryuser = [participator](const User& user){
    return (user.getName() == participator);
   };
   if ((m_storage->queryUser(queryuser)).size() <= 0 )
   {
    throw MyException("The user hasn't been assigned!");
   }
   auto queryuserName = [userName](const User& user){
    return (user.getName() == userName);
   };
   if ((m_storage->queryUser(queryuserName)).size() <= 0 )
   {
    throw MyException("The user hasn't been assigned!");
   }
   //query user
   auto findtitle = [title](const Meeting& meeting){
       if (meeting.getTitle() == title)
       {
        return true;
       }
       return false;
      };
      if (m_storage->queryMeeting(findtitle).empty())
      {
       throw MyException("No this title!");
      }
      auto findsponsor = [title,userName](const Meeting& meeting){
       if (meeting.getTitle() == title && meeting.getSponsor() == userName)
       {
        return true;
       }
       return false;
      };
      if (m_storage->queryMeeting(findsponsor).empty())
      {
       throw MyException("You are not the sponsor!");
      }

   auto findmeeting = [userName,title,participator](const Meeting& meeting){
       if (!(meeting.getTitle() == title && meeting.getSponsor() == userName))
       {
        return false;
       }
       
       if (meeting.isParticipator(participator))
       {
        return false;
       }
       
       return true;
      };
      auto found = m_storage->queryMeeting(findmeeting);
      if (found.size() > 1 || found.size() <= 0)
      {
       throw MyException("The user has been the participator!");
      }

      auto m_iterator = found.begin();
      string startDate = Date::dateToString((*m_iterator).getStartDate());
      string endDate = Date::dateToString((*m_iterator).getEndDate());


   auto querydate = [participator,startDate,endDate](const Meeting& meeting){
   if (!(meeting.getSponsor() == participator ||meeting.isParticipator(participator))) return false;
  
    Date start(startDate);
    Date end(endDate);
    if (meeting.getStartDate() >= end || meeting.getEndDate() <= start)
    {
     return false;
    }
   // cout<<Date::dateToString(meeting.getStartDate())<<endl;F
    //cout<<Date::dateToString(meeting.getEndDate())<<endl;
    //cout<<Date::dateToString(start)<<endl;
    //cout<<Date::dateToString(end)<<endl;
    return true;
   };
  
   auto mlist = m_storage->queryMeeting(querydate);
   if (mlist.size() > 0)
   {
    throw MyException("The user has the other meeting at the same time!");
   }
   //judge date



      auto func = [userName,title,participator](const Meeting& meeting){
       if (!(meeting.getTitle() == title && meeting.getSponsor() == userName))
       {
        return false;
       }
       
       if (meeting.isParticipator(participator))
       {
        return false;
       }
       
       return true;
       
      };

      auto operate = [participator](Meeting& meeting){
       meeting.addParticipator(participator);
      };
      int count = m_storage->updateMeeting(func,operate);
      if (count < 0)
      {
        throw MyException("Add participator failed!");
      }
      if(count > 0){
        return true;
      }
      
  }

  /**
   * remove a participator from a meeting
   * @param userName the sponsor's userName
   * @param title the meeting's title
   * @param participator the meeting's participator
   * @return if success, true will be returned
   */
  bool AgendaService::removeMeetingParticipator(const std::string &userName,
                                 const std::string &title,
                                 const std::string &participator){
    if (userName == participator)
    {
      throw MyException("userName == participator!");
    }
    auto queryuser = [participator](const User& user){
    return (user.getName() == participator);
   };
   if ((m_storage->queryUser(queryuser)).size() <= 0 )
   {
   throw MyException("The user hasn't been assigned!");
   }
   auto queryuserName = [userName](const User& user){
    return (user.getName() == userName);
   };
   if ((m_storage->queryUser(queryuserName)).size() <= 0 )
   {
   throw MyException("The user hasn't been assigned!");
   }
   //query user
    auto findtitle = [title](const Meeting& meeting){
       if (meeting.getTitle() == title)
       {
        return true;
       }
       return false;
      };
      if (m_storage->queryMeeting(findtitle).empty())
      {
       throw MyException("No this title!");
      }
      auto findsponsor = [title,userName](const Meeting& meeting){
       if (meeting.getTitle() == title && meeting.getSponsor() == userName)
       {
        return true;
       }
       return false;
      };
      if (m_storage->queryMeeting(findsponsor).empty())
      {
       throw MyException("You are not the sponsor!");
      }


 auto func = [userName,title,participator](const Meeting& meeting){
    if (meeting.isParticipator(participator) && meeting.getTitle() == title && meeting.getSponsor() == userName)
    {
     
     return true;
    }
    return false;
    
   };
  // cout<<"start"<<endl;
   auto operate = [participator](Meeting& meeting){
    meeting.removeParticipator(participator);
   };
   //remove participator
   int count = m_storage->updateMeeting(func,operate);
   if (count > 0){
    auto deletemetg = [](const Meeting& meeting){
     auto plist = meeting.getParticipator();
     if(plist.empty()) return true;
     return false;
    };

   int size = m_storage->deleteMeeting(deletemetg);
   return true;

   }
   throw MyException("No this participator!");
  }

  /**
   * quit from a meeting
   * @param userName the current userName. no need to be the sponsor
   * @param title the meeting's title
   * @return if success, true will be returned
   */
  bool AgendaService::quitMeeting(const std::string &userName, const std::string &title){
   
    auto func = [userName,title](const Meeting& meeting){
    return (meeting.isParticipator(userName) && meeting.getTitle() == title);    
   };

   auto operate = [userName](Meeting& meeting){
    meeting.removeParticipator(userName);
   };

   int count = m_storage->updateMeeting(func,operate);
   if (count > 0) {

    auto deletemetg = [](const Meeting& meeting){
     auto plist = meeting.getParticipator();
     if(plist.empty()) return true;
     return false;
    };

   int size = m_storage->deleteMeeting(deletemetg);
   return true;
   }
   stringstream ss;
   ss<<"You have no meeting call \""<<title<<"\"! ";
  throw MyException(ss.str());
  }

  /**
   * search a meeting by username and title
   * @param uesrName the sponsor's userName
   * @param title the meeting's title
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &title) const{
    auto queryuser = [userName](const User& user){
    return (user.getName() == userName);
   };
   if ((m_storage->queryUser(queryuser)).size() <= 0 )
   {
    auto nulllist = [](const Meeting& meeting){
      return false;
   };
   return m_storage->queryMeeting(nulllist);
   }
   auto func = [userName,title](const Meeting& meeting){
    return ((meeting.getSponsor()==userName || meeting.isParticipator(userName))&& meeting.getTitle()== title);
    
   };
   return m_storage->queryMeeting(func);

  }
  /**
   * search a meeting by username, time interval
   * @param uesrName the sponsor's userName
   * @param startDate time interval's start date
   * @param endDate time interval's end date
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const{
    auto nulllist = [](const Meeting& meeting){
      return false;
   };


    auto queryuser = [userName](const User& user){
    return (user.getName() == userName);
   };
   if ((m_storage->queryUser(queryuser)).size() <= 0 )
   {
   return m_storage->queryMeeting(nulllist);
   }
   Date start(startDate);
    Date end(endDate);
    if(!(Date::isValid(start) && Date::isValid(end)) || (start > end)){
       return m_storage->queryMeeting(nulllist);
    }


   auto func = [userName,startDate,endDate](const Meeting& meeting){
    if (!(meeting.getSponsor() == userName ||meeting.isParticipator(userName))) return false;
    Date start(startDate);
    Date end(endDate);
    if(!(Date::isValid(start) && Date::isValid(end))) return false;
    if (start > end) return false;
    if (meeting.getStartDate() > end || meeting.getEndDate() < start)
    {
     return false;
    }
    return true;
    
   };

   return m_storage->queryMeeting(func);
  }

  /**
   * list all meetings the user take part in
   * @param userName user's username
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const{
   auto func = [&](const Meeting& meeting){
    return (meeting.isParticipator(userName) || meeting.getSponsor() == userName);
    
   };
   return m_storage->queryMeeting(func);
  }

  /**
   * list all meetings the user sponsor
   * @param userName user's username
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const{
   auto func = [&](const Meeting& meeting){
    return (meeting.getSponsor() == userName);
    
   };
   return m_storage->queryMeeting(func);
  }

  /**
   * list all meetings the user take part in and sponsor by other
   * @param userName user's username
   * @return a meeting list result
   */
  std::list<Meeting> AgendaService::listAllParticipateMeetings(
      const std::string &userName) const{
   auto func = [&](const Meeting& meeting){
    return (meeting.isParticipator(userName));
    
   };
   return m_storage->queryMeeting(func);
  }

  /**
   * delete a meeting by title and its sponsor
   * @param userName sponsor's username
   * @param title meeting's title
   * @return if success, true will be returned
   */
  bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){
   auto findtitle = [title](const Meeting& meeting){
       if (meeting.getTitle() == title)
       {
        return true;
       }
       return false;
      };
      if (m_storage->queryMeeting(findtitle).empty())
      {
       throw MyException("No this title! ");
      }
      auto findsponsor = [title,userName](const Meeting& meeting){
       if (meeting.getTitle() == title && meeting.getSponsor() == userName)
       {
        return true;
       }
       return false;
      };
      if (m_storage->queryMeeting(findsponsor).empty())
      {
       throw MyException("You are not the sponsor! ");
      }
      
   auto func = [userName,title](const Meeting& meeting){
    return(meeting.getSponsor()==userName && meeting.getTitle()== title);
   };
   int count = m_storage->deleteMeeting(func);
   if(count > 0){
    return true;
   }
   if(count <= 0)throw MyException("Delete the meeting failed! ");
  }

  /**
   * delete all meetings by sponsor
   * @param userName sponsor's username
   * @return if success, true will be returned
   */
  
  bool AgendaService::deleteAllMeetings(const std::string &userName){
   auto func = [userName](const Meeting& meeting){
    return(meeting.getSponsor()==userName);
   };
   int count = m_storage->deleteMeeting(func);
   return (count > 0);
  }

  /**
   * start Agenda service and connect to storage
   */
  void AgendaService::startAgenda(void){
   m_storage = Storage::getInstance();
  }

  /**
   * quit Agenda service
   */
  void AgendaService::quitAgenda(void){
   m_storage->sync();
  }

/*
 private:
  std::shared_ptr<Storage> m_storage;
};

#endif
*/