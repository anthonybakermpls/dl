
// Operating system includes
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// C++ includes
#include <iostream>
#include <fstream>
#include <string>


// set default global namespace
using namespace std;


int main(int argc, char** argv)
{

	ofstream f;
	f.open("a2.cpp");
	f << "#include <iostream>" << endl << "using namespace std;" << endl << "int main(){ cout << \"Hello world!\" << endl; return 0;}" << endl; 
	f.close();


	string line;
	ifstream f2("a2.cpp");
	if(f2.is_open())
	{
		while(getline(f2,line))
		{
			cout << line << endl;
		}
		f2.close();
	}
	else cout << "Unable to open file" << endl;




	pid_t pid;
	int status,died;
	switch(pid=fork())
	{

	case -1: cout << "Can't fork." << endl; 
		exit(-1);

	case 0: // child runs here 
		int rc;  
		rc=execl("/usr/bin/clang++", "clang++", "a2.cpp", "-o","a2.out", (char*)0);


	default: died=wait(&status); // parent code here

		if(WIFEXITED(status))
		cout << "The child, pid=" << pid << ", has returned " << WEXITSTATUS(status) << endl;
		else
		cout << "The child process was sent a " << WTERMSIG(status) << " signal\n";

		cout << "Parent done." << endl;
	}

	return 0;
}


