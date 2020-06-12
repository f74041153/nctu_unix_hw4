#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <cstdio>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return -1;
  }
  pid_t pid = fork();
  if (pid < 0) {
    return -1;
  } else if (pid == 0) {
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0)
      return -1;
    execvp(argv[1], argv + 1);
    return -1;
  } else {
    int status;
    if (waitpid(pid, &status, 0) < 0)
      return -1;
    assert(WIFSTOPPED(status));
    ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);
    ptrace(PTRACE_CONT, pid, 0, 0);
    waitpid(pid, &status, 0);
    perror("done");
  }
  return 0;
}