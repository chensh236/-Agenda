#include "User.hpp"
#include <cstring>
  /**
  * @brief the default constructor
  */
  /**
  * constructor with arguments
  */
  User::User(const std::string &t_userName, const std::string &t_userPassword,
       const std::string &t_userEmail, const std::string &t_userPhone){


    m_name = t_userName;
    m_password = t_userPassword;
   
    m_email = t_userEmail;
    m_phone = t_userPhone;
  };

  /**
  * @brief copy constructor
  */
  User::User(const User &t_user){
    m_name = t_user.m_name;
    m_password = t_user.m_password;
    m_email = t_user.m_email;
    m_phone = t_user.m_phone;
  }

  /**
  * @brief get the name of the user
  * @return   return a string indicate the name of the user
  */
  std::string User::getName() const{
    return m_name;
  }

  /**
  * @brief set the name of the user
  * @param   a string indicate the new name of the user
  */
  void User::setName(const std::string &t_name){
    m_name = t_name;
  }

  /**
  * @brief get the password of the user
  * @return   return a string indicate the password of the user
  */
  std::string User::getPassword() const{
    return m_password;
  }

  /**
  * @brief set the password of the user
  * @param   a string indicate the new password of the user
  */
  void User::setPassword(const std::string &t_password){
    m_password = t_password;
  }

  /**
  * @brief get the email of the user
  * @return   return a string indicate the email of the user
  */
  std::string User::getEmail() const{
    return m_email;
  }

  /**
  * @brief set the email of the user
  * @param   a string indicate the new email of the user
  */
  void User::setEmail(const std::string &t_email){
    m_email = t_email;
  }

  /**
  * @brief get the phone of the user
  * @return   return a string indicate the phone of the user
  */
  std::string User::getPhone() const{
    return m_phone;
  }

  /**
  * @brief set the phone of the user
  * @param   a string indicate the new phone of the user
  */
  void User::setPhone(const std::string &t_phone){
    m_phone = t_phone;
  }
/*
 private:
  std::string m_name;
  std::string m_password;
  std::string m_email;
  std::string m_phone;
*/