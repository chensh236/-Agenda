#include <iostream>
#include "AgendaService.hpp"
#include "Date.hpp"
#include "User.hpp"
#include "Meeting.hpp"
#include "Storage.hpp"

#include <vector>
using namespace std;
int main(int argc, char const *argv[])
{
	AgendaService tst;
	
	bool flag = tst.removeMeetingParticipator("test4","meeting4","test2");
	cout<<"quit:"<<flag <<endl;

	return 0;
}