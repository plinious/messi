#ifndef MESSI_COMMON_APPLICARION_H
#define MESSI_COMMON_APPLICARION_H

#include "types.h"
#include "Singleton.h"
#include "AppModule.h"
//#include "AppContext.h"

MESSI_NAMESPACE_START

class Application : public Singleton<Application> {
    public:
        Application() {}
        ~Application() {}

    public:
        void run();
        void shutdown(const std::string &reason);
        void registerAppModule(AppModulePtr modulePtr);

        std::string getAppName();
        std::string setAppName();
        std::string getVersion();
        std::string setVersion();

    private:
        std::string name_;
        std::string version_;
        bool isShutDown_;
        std::string shutdownReason_;
        bool isRestart_;
        bool isReload_;
        bool loopIntervalMs_;
//        AppContext context_;
        AppModulePtrList modules_;
        //TimeChecker timer_;
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_APPLICARION_H
