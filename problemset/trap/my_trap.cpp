#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/user.h>
#include <sstream>

using namespace std;

void errquit(const char *msg) {
	perror(msg);
	exit(-1);
}

int main(int argc, char* argv[]){
    string input;
    char op[3];
    cin >> input;
    stringstream ss(input);
    
    pid_t child;
	if((child = fork()) < 0) errquit("fork");
	if(child == 0) {
		if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) errquit("ptrace");
		execlp("./no_more_traps", "./no_more_traps", NULL);
		errquit("execvp");
	} else {
		int status;
        unsigned long code, target;
		while(waitpid(child, &status, 0) > 0) {
			struct user_regs_struct regs;
			if(!WIFSTOPPED(status)) continue;
			if(ptrace(PTRACE_GETREGS, child, 0, &regs) != 0)
				errquit("ptrace(GETREGS)");
			
            target = regs.rip-1;
            code = ptrace(PTRACE_PEEKTEXT, child, target, 0);
            if((code & 0xff)== 0xcc){
                ss.read(op, 2);
                op[3] = '\0';
                int opcode = (int)strtol(op, NULL, 16);
                //printf("%X\n", opcode);  
                if(ptrace(PTRACE_POKETEXT, child, target, (code & 0xffffffffffffff00) | opcode) != 0)
                    errquit("ptrace(POKETEXT)");
                
                regs.rip = regs.rip-1;
                regs.rdx = regs.rax;
                if(ptrace(PTRACE_SETREGS, child, 0, &regs) != 0) errquit("ptrace(SETREGS)");
            }
			ptrace(PTRACE_CONT, child, 0, 0);
		}
	}
    return 0;
}