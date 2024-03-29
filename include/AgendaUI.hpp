#ifndef AGENDAUI_H
#define AGENDAUI_H
#include <iostream>
#include <string>
#include <fstream>
#include "AgendaService.hpp"
#include <list>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <regex>
#include <time.h>

class AgendaUI {
 public:
  AgendaUI();
  void OperationLoop(void);

 private:
  /**
   * constructor
   */
  void autoWrite();
  void autoDelete();
  void autoLogIn();
  void startAgenda(void);

  /**
   * catch user's operation
   * @return the operation
   */
  std::string getOperation();

  /**
   * execute the operation
   * @return if the operationloop continue
   */
  bool executeOperation(const std::string &t_operation);

  /**
   * user Login
   */
  void userLogIn(void);

  /**
   * user regist
   */
  void userRegister(void);

  /**
   * user logout
   */
  void userLogOut(void);

  /**
   * quit the Agenda
   */
  void quitAgenda(void);

  /**
   * delete a user from storage
   */
  void deleteUser(void);

  /**
   * list all users from storage
   */
  void listAllUsers(void);

  /**
   * user create a meeting with someone else
   */
  void createMeeting(void);

  /**
   * sponsor add a participator to the meeting
   */
  void addMeetingParticipator(void);

  /**
   * sponsor add a participator to the meeting
   */
  void removeMeetingParticipator(void);

  /**
   * user quit from meeting
   */
  void quitMeeting(void);

  /**
   * list all meetings from storage
   */
  void listAllMeetings(void);

  /**
   * list all meetings that this user sponsored
   */
  void listAllSponsorMeetings(void);

  /**
   * list all meetings that this user take part in
   */
  void listAllParticipateMeetings(void);

  /**
   * search meetings by title from storage
   */
  void queryMeetingByTitle(void);

  /**
   * search meetings by timeinterval from storage
   */
  void queryMeetingByTimeInterval(void);

  /**
   * delete meetings by title from storage
   */
  void deleteMeetingByTitle(void);

  /**
   * delete all meetings that this user sponsored
   */
  void deleteAllMeetings(void);

  /**
   * show the meetings in the screen
   */
  void printMeetings(const std::list<Meeting> &t_meetings);
  // dates
  std::string m_userName;
  std::string m_userPassword;
  AgendaService m_agendaService;
};

#endif
