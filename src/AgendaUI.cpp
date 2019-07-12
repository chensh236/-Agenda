#include <iostream>
#include <string>
#include "AgendaUI.hpp"
#include "md5.h"
#include "Path2.hpp"
#include "Myexception.hpp"
using namespace std;
/*注释by 思航*/

//Linux串口编程
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

//ECHO 可以抑制输入字符的回显
//ECHOE 在接收EPASE时执行Backspace,Space,Backspace组合 
//ECHOK 在KILL字符上执行清除行
//ECHONL 回显新行字符
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
    cout<<"      User:\033[33m"<<m_userName<<"\033[0m"<<endl<<endl;
    cout<<"\033[7mAction:\033[0m"<<endl;
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
    //cout<<"pg     - play the snake game"<<endl;
    cout<<"-----------------------------------TERMIAL-----------------------------------"<<endl;
    string str = getOperation();
    while (str !="o"&& str !="dc"&& str !="lu"&& str !="cm"&& str !="amp"&& str !="rmp"&& str !="rqm"&&
      str !="la"&& str !="las"&& str !="lap"&& str !="qm"&& str !="qt"&& str !="dm"&&str !="da"&&str !="rp"&&str !="drp"/*&&str !="pg"*/)
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
     while(operation != "q"){
      printf("\033[2J");
      cout<<"-----------------------------------Agenda------------MADEBY: S.H. CHAN------"<<endl;
      cout<<"     humanized UI is only belong to you!"<<endl<<endl<<endl;
    cout<<"\033[7mAction:\033[0m"<<endl;
    cout<<"l      - log in Agenda by user name and password"<<endl;
    cout<<"r      - register an Agenda account"<<endl;
    cout<<"q      - quit Agenda"<<endl;
    cout<<"aug    - auto login"<<endl;
    cout<<"-----------------------------------TERMIAL-----------------------------------"<<endl;
   




      cout<<"Agenda@"<<":~#";
      cin>>operation;
        if (operation == "l") userLogIn();
        else if(operation =="r") userRegister();
        else if(operation == "aug") autoLogIn();
        else if (operation == "q"){quitAgenda(); break;}
        else{
            cout<<"invalid input!"<<endl;
            sleep(1);
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
    Path2 pth;
    ofs.open(pth.loginPath);
    if (!ofs.is_open())
    {
      cout<<"[remember password] Conneted \033[31merror\033[0m!"<<endl;
      return;
    }
      ofs<<"\""<<m_userName<<"\""<<","<<"\""<<m_userPassword<<"\"";
      ofs<<endl;
      ofs.close();
      cout<<"[remember password] remember \033[32msucceed\033[0m!"<<endl;
      sleep(1);
  }
  void AgendaUI::autoDelete(){
     ofstream ofs;
     Path2 pth;
    ofs.open(pth.loginPath);
    if (!ofs.is_open())
    {
      cout<<"[delete remembered password] Conneted \033[31merror\033[0m!"<<endl;
      return;
    }
    cout<<"[delete remembered password] remember \033[32msucceed\033[0m!"<<endl;
      sleep(1);
  }
  void AgendaUI::autoLogIn(){
    ifstream ifs;
   Path2 pth;
    ifs.open(pth.loginPath);
    if (!ifs.is_open())
    {
      cout<<"[auto login] \033[7m\033[31mNo remembered password!\033[0m"<<endl;
      sleep(1);
      return;
    }
    string str;
    getline(ifs,str);
    if (str.size() == 0)
    {
      cout<<"[auto login] \033[7m\033[31mNo remembered password!\033[0m"<<endl;
      sleep(1);
      return;
    }
        int index = 0, start, end;
        string name,password;

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
    m_userPassword = password;
    m_userName = name;
    cout<<"[log in]   "<<"\033[33m"<<m_userName<<"\033[0m"<<"  Welcome back!"<<endl;
    sleep(2);
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
                          else if(t_operation == "rp"){ autoWrite();} 
                            else if(t_operation == "drp") autoDelete();
    return true;
  }

  /**
   * user Login
   */
  //STDIN_FILENO等是文件描述符，是非负整数，一般定义为0, 1, 2，属于没有buffer的I/O，直接调用系统调用
  //类似于std::in
  int set_disp_mode(int fd, int option){
    int err;
    struct termios term;
    //termios 结构是在POSIX规范中定义的标准接口.在linx中对终端借口进行控制
    //tcgetattr 获取终端的相关参数
    if (tcgetattr(fd,&term) == -1)//成功返回 0  失败返回 -1
    {
      //) perr 用来将上一个函数发生错误的原因输出到标准设备
        perror("Cannot get the attribution of the terminal");
        return 1;
    }
    //打开
    if (option)
    {
      term.c_lflag |= ECHOFLAGS;
    }
    //关闭
    else term.c_lflag &=~ECHOFLAGS;
    // ecsetattr 设置众终端参数
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
    cout<<"******"<<endl;
  }
  void AgendaUI::userLogIn(void){
    try{
    m_userPassword = "";
    srand((unsigned)time(NULL));
    int randone = (rand())%((9999-1000)+1)+1000;
    cout<<"[log in] [username]"<<endl;
    cout<<"[log in] ";
    cin>>m_userName;
    cout<<"[log in] [password]"<<endl;
    cout<<"[log in] ";
    char *p,passwd[40];
    getchar();
    set_disp_mode(STDIN_FILENO,0);
    //开启
    getpassword(passwd,sizeof(passwd));
    p = passwd;
    while(*p != '\n') p++;
    *p = '\0';
    cout<<endl;
    cout<<"[press any key to continue]"<<endl;
    //关闭
    set_disp_mode(STDIN_FILENO,1);
    getchar();
    m_userPassword = passwd;//password

    cout<<"[please input the verification code] :"<<randone<<endl;
    cout<<"[verification code]";


    string input;
    cin>>input;
    cout<<endl;
    unsigned char digest[16];
    MD5_CTX context;
    MD5Init (&context);
    MD5Update (&context, (unsigned char*)m_userPassword.c_str(), (unsigned int)strlen(m_userPassword.c_str()));
    MD5Final (digest,&context);

    m_userPassword = "";
    for (int i = 0; i < 16; ++i)
    {
      int arr = digest[i],index = 0;
      //cout<<"original"<<arr<<endl;
      char storage[2]={0,0};
       storage[index] = arr % 16;
        switch(storage[index]){
          case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
          storage[index] += '0';
          break;
          case 10: storage[index] = 'A';break;
          case 11: storage[index] = 'B';break;
          case 12: storage[index] = 'C';break;
          case 13: storage[index] = 'D';break;
          case 14: storage[index] = 'E';break;
          case 15: storage[index] = 'F';break;
        }
        arr /= 16;
        index++;
      storage[index] = arr;
      switch(storage[index]){
          case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
          storage[index] += '0';
          break;
          case 10: storage[index] = 'A';break;
          case 11: storage[index] = 'B';break;
          case 12: storage[index] = 'C';break;
          case 13: storage[index] = 'D';break;
          case 14: storage[index] = 'E';break;
          case 15: storage[index] = 'F';break;
        }
      for (int count = index; count >= 0; --count)
      {
        m_userPassword += storage[count];
      }
      
    }
    //cout<<m_userPassword<<endl;
    for (int i = 0; i < input.size(); ++i)
    {
      if (!(input[i] >= '0' && input[i] <= '9') )
      {
         throw MyException("[verification code] \033[31merror\033[0m!");
      
      }
    }
    char tmp[5];
    string s;
    sprintf(tmp, "%d", randone);
    s = tmp;
    if(input != s){
      throw MyException("[verification code] error!");
    }
   if(!m_agendaService.userLogIn(m_userName,m_userPassword)) {
      throw MyException("[log in] password \033[31merror\033[0m or user doesn't exist!");
   }
  }
    catch (MyException e)
    {
      cout<<e.what()<<endl;
      sleep(1);
      return;
    }
      cout<<"\033[32msucceed\033[0m!"<<endl;
      sleep(1);
      OperationLoop();
  }

  /**
   * user regist
   */
  void AgendaUI::userRegister(void){
    m_userPassword = "";
    cout<<"[register] [username] [password (storage in MD5 in decimal system)]";
    cout<<" [email] [phone]"<<endl;
    cout<<"[register] ";
    try{
    string name,password,email,phone;
    cin>>name>>password>>email>>phone;
    cout<<"[register] ";
    unsigned char digest[16]; //16位
    MD5_CTX context;
    MD5Init (&context);
    MD5Update (&context, (unsigned char*)password.c_str(), (unsigned int)strlen(password.c_str()));
    MD5Final (digest,&context);
    string storagepassword = "";
   for (int i = 0; i < 16; ++i)
    {

      int arr = digest[i],index = 0;
      //cout<<"original"<<arr<<endl;
      char storage[2]={0,0};
        
        storage[index] = arr % 16;
        switch(storage[index]){
          case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
          storage[index] += '0';
          break;
          case 10: storage[index] = 'A';break;
          case 11: storage[index] = 'B';break;
          case 12: storage[index] = 'C';break;
          case 13: storage[index] = 'D';break;
          case 14: storage[index] = 'E';break;
          case 15: storage[index] = 'F';break;
        }
        arr /= 16;
        index++;
      storage[index] = arr;
      switch(storage[index]){
          case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
          storage[index] += '0';
          break;
          case 10: storage[index] = 'A';break;
          case 11: storage[index] = 'B';break;
          case 12: storage[index] = 'C';break;
          case 13: storage[index] = 'D';break;
          case 14: storage[index] = 'E';break;
          case 15: storage[index] = 'F';break;
        }
      for (int count = index; count >= 0; --count)
      {
        storagepassword += storage[count];
      }
      
    }
    //cout<<"MD5"<<storagepassword<<endl;
    // e mail
    regex templte("([0-9A-Za-z\\-_\\.]+)@([0-9A-Za-z]+\\.[0-9A-Za-z]{2,3}(\\.[a-z]{2})?)");
    //+ 匹配前面的子表达式一次或多次
    //{n,m} 最少匹配 n 次且最多匹配 m 次
    // ? 匹配前面的子表达式零次或一次
    if (!regex_match( email,templte)){
     throw MyException("[register] inValid Email!  Are you kidding me?");
   }
    regex templtephone("^(13[0-9]|15[0-9]|18[0-9]|17[0|1|2])\\d{8}$");
    //^匹配输入字符串的开始位置
    //{}匹配确定的 n 次
    //\d 0-9数字
    //$ 匹配结尾
    if (!regex_match( phone,templtephone)){
      throw MyException("[register] inValid phone! Are you kidding me?");
    }
    bool flag = m_agendaService.userRegister(name,storagepassword,email,phone);
    if (!flag)
    {
       throw MyException("[register] This username has been registered!");
    }
     }
    catch(MyException e) {cout<<"Exception: "<<endl<<e.what()<<endl;
    sleep(1);
    return;
    }
     cout<<"\033[32msucceed\033[0m!"<<endl; 
    
    
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
    unsigned char digest[16];
    MD5_CTX context;
    MD5Init (&context);
    MD5Update (&context, (unsigned char*)password.c_str(), (unsigned int)strlen(password.c_str()));
    MD5Final (digest,&context);
    password = "";
    for (int i = 0; i < 16; ++i)
    {
     int arr = digest[i],index = 0;
      //cout<<"original"<<arr<<endl;
      char storage[2]={0,0};
       storage[index] = arr % 16;
        switch(storage[index]){
          case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
          storage[index] += '0';
          break;
          case 10: storage[index] = 'A';break;
          case 11: storage[index] = 'B';break;
          case 12: storage[index] = 'C';break;
          case 13: storage[index] = 'D';break;
          case 14: storage[index] = 'E';break;
          case 15: storage[index] = 'F';break;
        }
        arr /= 16;
        index++;
      storage[index] = arr;
      switch(storage[index]){
          case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
          storage[index] += '0';
          break;
          case 10: storage[index] = 'A';break;
          case 11: storage[index] = 'B';break;
          case 12: storage[index] = 'C';break;
          case 13: storage[index] = 'D';break;
          case 14: storage[index] = 'E';break;
          case 15: storage[index] = 'F';break;
        }
      for (int count = index; count >= 0; --count)
      {
        password += storage[count];
      }
    }
    if(password != m_userPassword){
      cout<<"[delete agenda account] password \033[31merror\033[0m!"<<endl;
      sleep(1);
      return;
    }

    cout<<"[delete agenda account] ";
    bool flag = m_agendaService.deleteUser(m_userName,m_userPassword);
    if(flag) cout<<"\033[32msucceed\033[0m!"<<endl;
    else cout<<"\033[31merror\033[0m!"<<endl;
    sleep(1);

    //delete remembered password
    ifstream ifs;
    Path2 pth;
    ifs.open(pth.loginPath);
    string str;
    getline(ifs,str);
     if (str.size() == 0)
    {
      return;
    }
        int index = 0, start, end;
        string name;

        start = ++index;
        while(str[index]!='\"'){
          index++;
        }
        end = index - 1;
        name = str.substr(start,end - start + 1);
    if(m_userName == name) {
      ofstream ofs;
      Path2 pth;
      ofs.open(pth.loginPath);
    }
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
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
   
    cout<<"[press any key to back] ";
    char ch;
    cin>>ch;

  }

  /**
   * user create a meeting with someone else
   */
  void AgendaUI::createMeeting(void){
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
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"[create meeting] "<<"[the number of participators]"<<endl;
    string sum;
    vector<string> participators;
    cout<<"[create meeting] ";
    cin>>sum;
    bool flag = true;
    for (int i = 0; i < sum.size(); ++i)
    {
      if (!(sum[i]>='0' & sum[i]<='9'))
      {
        flag = false;
        break;
      }
    }
    if (!flag)
    {
       cout<<"[create meeting] "<<"\033[31merror\033[0m! Try once again! or press \'q\' to quit"<<endl;
      string input;
      cin>>input;
      if (input == "q")
      {
      return;
      }
     createMeeting();
     return;
    }
    int count = 0;
     for (int i = 0; i < sum.size(); ++i)
    {
      count = 10 * count + sum[i] - '0';
    }


    //count sum
    for (int i = 0; i < count; ++i)
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
    try{
    flag = m_agendaService.createMeeting(m_userName,title,startDate,endDate,participators);
     if (flag)
     {
       cout<<"[create meeting] "<<"\033[32msucceed\033[0m!"<<endl;
      sleep(1);
      return; 
     }

   }
   catch(MyException e){
    cout<<"[create meeting] "<<"\033[31merror\033[0m! "<<e.what()<<" Try once again! or press \'q\' to quit"<<endl;
    string input;
      cin>>input;
      if (input == "q")
      {
      return;
      }
     createMeeting();
     return;
   }
      

  }

  /**
   * sponsor add a participator to the meeting
   */
  void AgendaUI::addMeetingParticipator(void){
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
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"[add participator] "<<"[meeting title] "<<"[participator username]"<<endl;
      string name,title;
      cout<<"[add participator] ";
    cin>>title>>name;
    cout<<"[add participator] ";
    try{
    bool flag = m_agendaService.addMeetingParticipator(m_userName,title,name);
     cout<<"[add participator] ";
    if(flag){ cout<<"\033[32msucceed\033[0m!"<<endl;
     sleep(1);
     return;
    }
    }
    catch(MyException e){
    cout<<"\033[31merror\033[0m! "<<e.what()<<" Try once again! or press \'q\' to quit"<<endl;
    string input;
      cin>>input;
      if (input == "q")
      {
      return;
      }
     addMeetingParticipator();
     return;
   }
     
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
    cout<<"[remove participator] ";
    try{
    bool flag = m_agendaService.removeMeetingParticipator(m_userName,title,name);
     cout<<"[remove participator] ";
      if (flag)
      {
        cout<<"\033[32msucceed\033[0m!"<<endl;
     sleep(1);
     return;
      }
    }
    catch(MyException e){
    cout<<"\033[31merror\033[0m! "<<e.what()<<" Try once again! or press \'q\' to quit"<<endl;
    string input;
      cin>>input;
      if (input == "q")
      {
      return;
      }
     removeMeetingParticipator();
     return;
   }
      
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
    cout<<"[quit meeting] ";
    try{
    bool flag = m_agendaService.quitMeeting(m_userName,title);
     cout<<"[quit meeting] ";
     if (flag)
     {
       cout<<"\033[32msucceed\033[0m!"<<endl;
      sleep(1);
      return;
     }
}
catch(MyException e){
    cout<<"\033[31merror\033[0m! "<<e.what()<<" Try once again! or press \'q\' to quit"<<endl;
    string input;
      cin>>input;
      if (input == "q")
      {
      return;
      }
     quitMeeting();
     return;
   }
    
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
    cout<<"[delete meeting] ";
    try{
    bool flag = m_agendaService.deleteMeeting(m_userName,title);
    if (flag)
    {
      cout<<"\033[32msucceed\033[0m!"<<endl;
      sleep(1);
      return;
    }
    }
    catch(MyException e){
    cout<<"\033[31merror\033[0m! "<<e.what()<<" Try once again! or press \'q\' to quit"<<endl;
    string input;
      cin>>input;
      if (input == "q")
      {
      return;
      }
     deleteMeetingByTitle();
     return;
   }
    
}
  /**
   * delete all meetings that this user sponsored
   */
  void AgendaUI::deleteAllMeetings(void){
    printf("\033[2J");
    bool flag = m_agendaService.deleteAllMeetings(m_userName);
    if(flag) cout<<"[delete all meeting] \033[32msucceed\033[0m!"<<endl;
    else cout<<"[\033[31merror\033[0m] You have no meeting!"<<endl;
    sleep(1);
  }

  /**
   * show the meetings in the screen
   */
  void AgendaUI::printMeetings(const std::list<Meeting> &t_meetings){
     printf("\033[2J");
     cout<<"\033[7m-----------------------------------Agenda------------MADEBY: S.H. CHAN--------------------------------------------------------------------------------------------\033[0m"<<endl;
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
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"[press any key to back] ";
    char ch;
    cin>>ch;
  }
  // dates