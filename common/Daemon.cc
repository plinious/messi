#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Daemon.h"

MESSI_NAMESPACE_START

MCResult<bool> Daemon::daemon(const std::string &pidfile, bool chdir, bool closeFd) {
    if (!pidfile.empty()) {
        // write into pidfile
    }

    // first fork
    pid_t pid = fork();
    if (pid < 0) {
        return MCResult<bool>::getFailureResult("2", "first fork fail");
    }
    if (pid > 0) {
        exit(0);
    }

    if (chdir && ::chdir("/") < 0) {
        return MCResult<bool>::getFailureResult("3", "chdir fail");
    }
    if (setsid() < 0) {
        // create session and set process group ID
        return MCResult<bool>::getFailureResult("4", "setsid fail");
    }
    umask(0);

    // second fork.防止重新打开控制终端
    pid = fork();
    if (pid < 0) {
        return MCResult<bool>::getFailureResult("5", "second fork fail");
    }
    if (pid > 0) {
        exit(0);
    }

    fflush(stdout);
    fflush(stderr);
    if (closeFd) {
        int fd = open("/dev/null", O_RDWR, 0);
        if (fd < 0) {
            return MCResult<bool>::getFailureResult("6", "open file fail");
        }
        if (dup2(fd, STDIN_FILENO) < 0 || dup2(fd, STDOUT_FILENO) < 0 || dup2(fd, STDERR_FILENO) < 0) {
            return MCResult<bool>::getFailureResult("7", "dup2 fail");
        }
        if (fd > STDERR_FILENO) {
            close(fd);
        }
    }
    return MCResult<bool>::getSuccessResult(true);
}

MESSI_NAMESPACE_END
