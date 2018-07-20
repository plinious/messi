#include <unistd.h> 

#include "Application.h"

MESSI_NAMESPACE_START

void Application::registerAppModule(AppModulePtr modulePtr) {
    modules_.push_back(modulePtr);
}

void Application::run() {
    while (true) {
        isShutDown_ = false;
        
        AppModulePtrList::const_iterator it = modules_.begin();
        for (; it != modules_.end(); ++it){
            // TODO 失败后的处理
            // 规定几个运行模式》strict模式，
            (*it)->onLoad();
        }

        while (true) {
            if (isShutDown_) {
                WarnLog(__func__ << " shutdown for reason: " << shutdownReason_);
                break;
            }
            usleep(loopIntervalMs_ * 1000);

//            if (timer_.isTimeout()) {
//                continue;
//            }
            usleep(5*1000*1000);
            for (it = modules_.begin(); it != modules_.end(); ++it){
                (*it)->onTimer();
            }
        }

        for (it = modules_.begin(); it != modules_.end(); ++it){
            (*it)->unLoad();
        }
    }
}

void Application::shutdown(const std::string &reason) {
    isShutDown_ = true;
    shutdownReason_ = reason;
}

MESSI_NAMESPACE_END
