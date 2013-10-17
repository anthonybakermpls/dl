
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


    string line;
    ifstream in_f("main.cpp");
    if(in_f.is_open())
    {
        ofstream f;
        f.open("main2.cpp");
        while(getline(in_f,line))
        {
            f << line << endl;
        }
        f.close();
        in_f.close();
    }
    else cout << "Unable to open file" << endl;



	int rc;
    pid_t pid;
	int status,died;




    cout << "rm main.cpp" << endl;
	switch(pid=fork())
	{
        case -1: cout << "Can't fork." << endl;
            exit(-1);
            break;
        case 0: // child runs here
            rc=execl("/bin/rm", "rm", "main2.cpp", (char*)0);
            break;
        default:
            died=wait(&status); // parent code here
            if(WIFEXITED(status))
            cout << "The child, pid=" << pid << ", has returned " << WEXITSTATUS(status) << endl;
            else
            cout << "The child process was sent a " << WTERMSIG(status) << " signal\n";

            cout << "mv main2.cpp main.cpp" << endl;
            switch(pid=fork())
            {
                case -1: cout << "Can't fork." << endl;
                    exit(-1);
                    break;
                case 0: // child runs here
                    rc=execl("/usr/bin/mv", "mv", "main2.cpp", "main.cpp", (char*)0);
                    break;
                default:
                    died=wait(&status); // parent code here
                    if(WIFEXITED(status))
                    cout << "The child, pid=" << pid << ", has returned " << WEXITSTATUS(status) << endl;
                    else
                    cout << "The child process was sent a " << WTERMSIG(status) << " signal\n";

                    cout << "clang++ main.cpp -o a.out" << endl;
                    switch(pid=fork())
                    {
                        case -1: cout << "Can't fork." << endl;
                            exit(-1);
                            break;
                        case 0: // child runs here
                            rc=execl("/usr/bin/clang++", "clang++", "main.cpp", "-o","a.out", (char*)0);
                            break;
                        default:
                            died=wait(&status); // parent code here
                            if(WIFEXITED(status))
                            cout << "The child, pid=" << pid << ", has returned " << WEXITSTATUS(status) << endl;
                            else
                            cout << "The child process was sent a " << WTERMSIG(status) << " signal\n";
                            break;
                    }// end 3rd fork
                    break;
            }// end 2nd fork
            break;
	} // end first fork











	return 0;
}


