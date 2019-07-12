#include <iostream>
#include <string>
#include "AgendaService.hpp"
#include "AgendaUI.hpp"
#include <list>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
using namespace std;
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)


  AgendaUI::AgendaUI(){
    for (int i = 0; i < 100; ++i)
    {
      cout<<endl;
    }
    printf("\033[2J");
    m_agendaService.startAgenda();
    startAgenda();
    
  }
  void AgendaUI::OperationLoop(void){
    bool flag = true;
while(flag){
    printf("\033[2J");
    cout<<"-----------------------------------Agenda------------MADEBY: S.H. CHAN------"<<endl;
    cout<<"Action:"<<endl;
    cout<<"o      - log out Agenda"<<endl;
    cout<<"dc     - delete Agenda account"<<endl;
    cout<<"lu     - list all Agenda user"<<endl;
    cout<<"cm     - create a meeting"<<endl;
    cout<<"amp    - add meeting participator"<<endl;
    cout<<"rmp    - remove meeting participator"<<endl;
    cout<<"rqm    - request to quit meeting"<<endl;
    cout<<"la     - list all meetings"<<endl;
    cout<<"las    - list all sponsor meetings"<<endl;
    cout<<"lap    - list all participator meetings"<<endl;
    cout<<"qm     - query meeting by title"<<endl;
    cout<<"qt     - query meeting by time interval"<<endl;
    cout<<"dm     - delete meeting by title"<<endl;
    cout<<"da     - delete all meetings"<<endl;
    cout<<"rp     - remember the password"<<endl;
    cout<<"drp    - delete the remembered password"<<endl;
    cout<<"-----------------------------------TERMIAL-----------------------------------"<<endl;
    string str = getOperation();
    while (str !="o"&& str !="dc"&& str !="lu"&& str !="cm"&& str !="amp"&& str !="rmp"&& str !="rqm"&&
      str !="la"&& str !="las"&& str !="lap"&& str !="qm"&& str !="qt"&& str !="dm"&&str !="da")
    {
      cout<<"invalid input!"<<endl;
     cout<<"Agenda@"<<m_userName<<":~#";
    cin>>str;
    }
     flag = executeOperation(str);
    }

  }






// private:

  /**
   * constructor
   */
  void AgendaUI::startAgenda(void){
    
    string operation;
     
      printf("\033[2J");
      cout<<"-----------------------------------Agenda------------MADEBY: S.H. CHAN------"<<endl;
    cout<<"Action:"<<endl;
    cout<<"l      - log in Agenda by user name and password"<<endl;
    cout<<"r      - register an Agenda account"<<endl;
    cout<<"q      - quit Agenda"<<endl;
    cout<<"aug    - auto login"<<endl;
    cout<<"-----------------------------------TERMIAL-----------------------------------"<<endl;
    cout<<"Agenda@"<<":~#";




while (operation != "q")
     {
      cin>>operation;
        if (operation == "l") userLogIn();
        else if(operation =="r") userRegister();
        else if(operation == "aug") autoLogIn();
        else if (operation == "q"){quitAgenda(); break;}
        else{
            cout<<"invalid input!"<<endl;
         continue;
        }
      }
  }

  /**p-
   * catch user's operation
   * @return the operation
   */
  std::string AgendaUI::getOperation(){
    cout<<"Agenda@";
    cout<<m_userName;
    cout<<":~#";
    std::string operation;
    cin>>operation;
    return operation;

  }
  void AgendaUI::autoWrite(){
    ofstream ofs;
    Path pth;
    pfs.open(pth.loginPath);
    if (!pfs.is_open())
    {
      cout<<"[remember password] Conneted \033[31merror\033[0m!"<<endl;
      return;
    }
      ofs<<"\""<<m_userName<<"\""<<","<<"\""<<m_userPassword<<"\"";
      ofs<<endl;
      ofs.close();
      return;
      cout<<"[remember password] remember \033[32msucceed\033[0m!"<<endl;
      sleep(1);
  }
  void AgendaUI::autoDelete(){
     ofstream ofs;
    Path pth;
    pfs.open(pth.loginPath);
    if (!pfs.is_open())
    {
      cout<<"[delete remembered password] Conneted \033[31merror\033[0m!"<<endl;
      return;
    }
    cout<<"[delete remembered password] remember \033[32msucceed\033[0m!"<<endl;
      sleep(1);
  }
  void AgendaUI::autoLogIn(){
    ifstream ifs;
    Path pth;
    ifs.open(pth.loginPath);
    if (!ifs.is_open())
    {
      cout<<"[auto login] No remembered password!"<<endl;
      return;
    }
    string str;
    getline(ifs,str);
    if (str.size() == 0)
    {
      cout<<"[auto login] No remembered password!"<<endl;
      return;
    }
        int index = 0, start, end;
        string name,passmword;

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
        //read from the file
    m_userName = name;
    m_userPassword = password;

    cout<<"[log in] [username]"<<endl;
    cout<<"[log in] "<<m_userName;
    cout<<"[log in] [password](less than 20)"<<endl;
    cout<<"[log in] "<<m_userPassword;
    cout<<"[log in] "<<"\033[32msucceed\033[0m!"<<endl;
    sleep(1);
      OperationLoop();
    


  }

  /**
   * execute the operation
   * @return if the operationloop continue
   */
  bool AgendaUI::executeOperation(const std::string &t_operation){
    if(t_operation == "o"){ userLogOut();return false;}

else if(t_operation == "dc") { deleteUser(); return false;}
  else if(t_operation == "lu")listAllUsers();
    else if(t_operation == "cm") createMeeting();
      else if(t_operation == "amp") addMeetingParticipator();
        else if(t_operation == "rmp") removeMeetingParticipator();
          else if(t_operation == "rqm")quitMeeting();
            else if(t_operation == "la") listAllMeetings();
              else if(t_operation == "las")listAllSponsorMeetings();
                else if(t_operation == "lap")listAllParticipateMeetings();
                  else if(t_operation == "qm")queryMeetingByTitle();
                    else if(t_operation == "qt") queryMeetingByTimeInterval();
                      else if(t_operation == "dm")deleteMeetingByTitle();
                        else if(t_operation == "da") deleteAllMeetings();
                          else if(t_operation == "rp") autoWrite(); 
                            else if(t_operation == "drp") autoDelete(); 
    return true;
  }

  /**
   * user Login
   */
  int set_disp_mode(int fd, int option){
    int err;
    struct termios term;
    if (tcgetattr(fd,&term) == -1)
    {
        perror("Cannot get the attribution of the terminal");
        return 1;
    }
    if (option)
    {
      term.c_lflag |= ECHOFLAGS;
    }
    else term.c_lflag &=~ECHOFLAGS;
    err = tcsetattr(fd,TCSAFLUSH,&term);
    if (err == -1 && err == EINTR)
    {
      perror("Cannot set the attribution of the terminal");
      return 1;
    }
    return 0;
  }
  void getpassword(char* passwd, int size){
    int c;
    int n = 0;
    do{
      c = getchar();
      if (c != '\n' || c != '\r')
      {
       passwd[n++] = c;
      }
    }while(c != '\n' && c != '\r' && n < (size-1));
    passwd[n] = '\0';
  }
  void AgendaUI::userLogIn(void){
    srand((unsigned)time(NULL));
    int rand = rand()%((9999-1000)+1)+1000;
    cout<<"[log in] [username]"<<endl;
    cout<<"[log in] ";
    cin>>m_userName;
    cout<<"[log in] [password](less than 20)"<<endl;
    cout<<"[log in] ";
    char *p,passwd[40];
    getchar();
    set_disp_mode(STDIN_FILENO,0);
    getpassword(passwd,sizeof(passwd));
    p = passwd;
    while(*p != '\n') p++;
    *p = '\0';
    cout<<endl;
    cout<<"[press any key to continue]"<<endl;
    set_disp_mode(STDIN_FILENO,1);
    getchar();
    m_userPassword = passwd;
    cout<<"[please input the verification code]"<<endl;
    cout<<"[verification code]";
    cin>>input;
    cout<<endl;
    cout<<"[log in] ";
    bool flag = m_agendaService.userLogIn(m_userName,m_userPassword) && (input == rand);
    if (!flag)
    {
      printf("\033[2J");
      cout<<"[log in] "<<"password \033[31merror\033[0m or user doesn't exist!"<<endl;
      sleep(2);
    }
    else {
      cout<<"[log in] "<<"\033[32msucceed\033[0m!"<<endl;
      sleep(1);
      OperationLoop();
    }
  }

  /**
   * user regist
   */
  void AgendaUI::userRegister(void){
    cout<<"[register] [username] [password] [email] [phone]"<<endl;
    cout<<"[register] ";
    string name,password,email,phone;
    cin>>name>>password>>email>>phone;
    cout<<"[register] ";
    bool flag = m_agendaService.userRegister(name,password,email,phone);
    if (!flag)
    {
      cout<<"[register] "<<"This username has been registered!"<<endl;
    }
    else {
     cout<<"[register] "<<"\033[32msucceed\033[0m!"<<endl; 
    }
    sleep(1);
  }

  /**
   * user logout
   */
  void AgendaUI::userLogOut(void){
    m_userName.clear();
    m_userPassword.clear();
  }

  /**
   * quit the Agenda
   */
  void AgendaUI::quitAgenda(void){
    m_agendaService.quitAgenda();
   
    printf("\033[2J");
    cout<<"------------Goodbye!------------"<<endl;
    sleep(1);
    printf("\033[2J");
  }

  /**
   * delete a user from storage
   */
  void AgendaUI::deleteUser(void){
    printf("\033[2J");
    cout<<"Are you sure gonna to delete your account? press 'y' to delete"<<endl;
    char ch;
    cin>>ch;
    if (ch != 'y')
    {
      cout<<"[delete agenda account] \033[31merror\033[0m!"<<endl;
      sleep(1);
      return;
    }
    cout<<"Please input your password..."<<endl;
    string password;
    char *p,passwd[40];
    getchar();
    set_disp_mode(STDIN_FILENO,0);
    getpassword(passwd,sizeof(passwd));
    p = passwd;
    while(*p != '\n') p++;
    *p = '\0';
    cout<<endl;
    cout<<"[press any key to continue]"<<endl;
    set_disp_mode(STDIN_FILENO,1);
    getchar();
    password = passwd;

    if(password != m_userPassword){
      cout<<"[delete agenda account] \033[31merror\033[0m!"<<endl;
      sleep(1);
      return;
    }

    cout<<"[delete agenda account] ";
    bool flag = m_agendaService.deleteUser(m_userName,m_userPassword);
    if(flag) cout<<"\033[32msucceed\033[0m!"<<endl;
    else cout<<"\033[31merror\033[0m!"<<endl;
    sleep(1);
  }

  /**
   * list all users from storage
   */
  void AgendaUI::listAllUsers(void){
    printf("\033[2J");
    cout<<"[list all users]"<<endl;
    cout<<"-----------------------------------Agenda------------MADEBY: S.H. CHAN------"<<endl;
    cout<<setiosflags(ios::left)<<setw(20)<<"name";
cout<<setiosflags(ios::left)<<setw(20)<<"email";
cout<<setiosflags(ios::left)<<setw(20)<<"phone";
   cout<<endl;
    auto ulist = m_agendaService.listAllUsers();
    for (auto iter = ulist.begin(); iter != ulist.end(); iter++)
    {
     cout<<setiosflags(ios::left)<<setw(20)<<(*iter).getName();

     cout<<setiosflags(ios::left)<<setw(20)<<(*iter).getEmail();
   
     cout<<setiosflags(ios::left)<<setw(20)<<(*iter).getPhone()<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"[press any key to back] ";
    char ch;
    cin>>ch;

  }

  /**
   * user create a meeting with someone else
   */
  void AgendaUI::createMeeting(void){
     printf("\033[2J");
    
    cout<<"[create meeting] "<<"[the number of participators]"<<endl;
    int sum;
    vector<string> participators;
    cout<<"[create meeting] ";
    cin>>sum;
    for (int i = 0; i < sum; ++i)
    {
      string name;
      cout<<"[create meeting] "<<"[please enter the participator "<<i+1<<" ]"<<endl;
      cout<<"[create meeting] ";
    cin>>name;
    participators.push_back(name);
    }
    cout<<"[create meeting] "<<"[title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
    string title,startDate,endDate;
    cout<<"[create meeting] ";
    cin>>title>>startDate>>endDate;
    bool flag = m_agendaService.createMeeting(m_userName,title,startDate,endDate,participators);
     cout<<"[create meeting] ";
    if (flag)
    {
      cout<<"\033[32msucceed\033[0m!"<<endl;
    }
    else cout<<"\033[31merror\033[0m!"<<endl;
     sleep(1);


  }

  /**
   * sponsor add a participator to the meeting
   */
  void AgendaUI::addMeetingParticipator(void){
    printf("\033[2J");
    cout<<"[add participator] "<<"[meeting title] "<<"[participator username]"<<endl;
      string name,title;
      cout<<"[add participator] ";
    cin>>title>>name;
    bool flag = m_agendaService.addMeetingParticipator(m_userName,title,name);
     cout<<"[add participator] ";
    if (flag)
    {
      cout<<"\033[32msucceed\033[0m!"<<endl;
    }
    else cout<<"\033[31merror\033[0m!"<<endl;
     sleep(1);
  }

  /**
   * sponsor add a participator to the meeting
   */
  void AgendaUI::removeMeetingParticipator(void){
    printf("\033[2J");
    cout<<"[remove participator] "<<"[meeting title] "<<"[participator username]"<<endl;
      string name,title;
      cout<<"[remove participator] ";
    cin>>title>>name;
    bool flag = m_agendaService.removeMeetingParticipator(m_userName,title,name);
     cout<<"[remove participator] ";
    if (flag)
    {
      cout<<"\033[32msucceed\033[0m!"<<endl;
    }
    else cout<<"\033[31merror\033[0m!"<<endl;
     sleep(1);
  }

  /**
   * user quit from meeting
   */
  void AgendaUI::quitMeeting(void){
    printf("\033[2J");
    cout<<"[quit meeting] "<<"[meeting title]"<<endl;
      string title;
      cout<<"[quit meeting] ";
    cin>>title;
    bool flag = m_agendaService.quitMeeting(m_userName,title);
     cout<<"[quit meeting] ";
    if (flag)
    {
      cout<<"\033[32msucceed\033[0m!"<<endl;
    }
    else cout<<"\033[31merror\033[0m!"<<endl;
     sleep(1);
  }

  /**
   * list all meetings from storage
   */
  void AgendaUI::listAllMeetings(void){
    printf("\033[2J");
    cout<<"[list all meetings]"<<endl;
    auto mlist = m_agendaService.listAllMeetings(m_userName);
    printMeetings(mlist);

  }

  /**
   * list all meetings that this user sponsored
   */
  void AgendaUI::listAllSponsorMeetings(void){
    cout<<"[list all sponsor meetings]"<<endl;
    auto mlist = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(mlist);
  }

  /**
   * list all meetings that this user take part in
   */
  void AgendaUI::listAllParticipateMeetings(void){
    cout<<"[list all participator meetings]"<<endl;
    auto mlist = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(mlist);
  }

  /**
   * search meetings by title from storage
   */
  void AgendaUI::queryMeetingByTitle(void){
    printf("\033[2J");
    cout<<"[query meeting] [title]"<<endl;
    cout<<"[query meeting] ";
    string title;
    cin>>title;
    auto mlist = m_agendaService.meetingQuery(m_userName,title);
    printMeetings(mlist);
  }

  /**
   * search meetings by timeinterval from storage
   */
  void AgendaUI::queryMeetingByTimeInterval(void){
    printf("\033[2J");
    cout<<"[query meetings] "<<"[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
    string startDate,endDate;
    cout<<"[query meetings] ";
    cin>>startDate>>endDate;
    auto mlist = m_agendaService.meetingQuery(m_userName,startDate,endDate);
    printMeetings(mlist);
  }

  /**
   * delete meetings by title from storage
   */
  void AgendaUI::deleteMeetingByTitle(void){
    printf("\033[2J");
    cout<<"[delete meeting] [title]"<<endl;
    cout<<"[delete meeting] ";
    string title;
    cin>>title;
    bool flag = m_agendaService.deleteMeeting(m_userName,title);
    if(flag) cout<<"[delete meeting] \033[32msucceed\033[0m!"<<endl;
    else cout<<"[\033[31merror\033[0m] delete meeting fail!"<<endl;
}
  /**
   * delete all meetings that this user sponsored
   */
  void AgendaUI::deleteAllMeetings(void){
    printf("\033[2J");
    bool flag = m_agendaService.deleteAllMeetings(m_userName);
    if(flag) cout<<"[delete all meeting] \033[32msucceed\033[0m!"<<endl;
    else cout<<"[\033[31merror\033[0m] delete meeting fail!"<<endl;
  }

  /**
   * show the meetings in the screen
   */
  void AgendaUI::printMeetings(const std::list<Meeting> &t_meetings){
     printf("\033[2J");
     cout<<"-----------------------------------Agenda------------MADEBY: S.H. CHAN--------------------------------------------------------------------------------------------"<<endl;
    printf("%-30s%-30s%-30s%-30s%-30s\n","title","sponsor","start time","end time","participators");
    for (auto iter = t_meetings.begin(); iter != t_meetings.end(); iter++)
    {

     printf("%-30s%-30s%-30s%-30s",(*iter).getTitle().c_str(),(*iter).getSponsor().c_str(),Date::dateToString((*iter).getStartDate()).c_str(),Date::dateToString((*iter).getEndDate()).c_str());
      for (int index = 0; index < (*iter).getParticipator().size(); index++)
      {
        cout<<(*iter).getParticipator()[index];
        if (index < ((*iter).getParticipator().size() - 1))
        {
          cout<<",";
        }
      }
      cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"[press any key to back] ";
    char ch;
    cin>>ch;
  }
  // dates

int main(int argc, char const *argv[])
{
  AgendaUI ui;
  return 0;
}