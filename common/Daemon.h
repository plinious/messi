#ifndef MESSI_COMMON_DAEMON_H
#define MESSI_COMMON_DAEMON_H

#include "types.h"
#include "MCResult.h"

MESSI_NAMESPACE_START

class Daemon {
    public:
        static MCResult<bool> daemon(const std::string &pidfile, bool chdir = false, bool closeFd = true);
        static void setPidfile(const std::string &pidfile) {
            pidfile_ = pidfile;
        }

    private:
        static std::string pidfile_;
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_DAEMON_H
