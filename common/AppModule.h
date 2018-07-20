#ifndef MESSI_COMMON_APPMODULE_H
#define MESSI_COMMON_APPMODULE_H

#include <list>

#include "types.h"
#include "RefObj.h"
#include "AppModuleStat.h"

MESSI_NAMESPACE_START

class AppModule : public RefObj {
    public:
        AppModule() {}
        virtual ~AppModule() {}

    public:
        virtual void onLoad() = 0;
        virtual void onTimer() = 0;
        virtual void onReload() = 0;
        virtual void onRestart() = 0;
        virtual void unLoad() = 0;
        virtual AppModuleStat getStatus() = 0;

    protected:
        AppModuleStat stat_;

};

typedef RefPtr<AppModule> AppModulePtr;
typedef std::list<AppModulePtr> AppModulePtrList;

class DemoModule : public AppModule {
    public:
        DemoModule() {}
        ~DemoModule() {}

    void onLoad() {
        InfoLog(__func__ << " DemoModule");
    }

    void onTimer() {
        InfoLog(__func__ << " DemoModule");
    }

    void onReload() {
        InfoLog(__func__ << " DemoModule");
    }

    void onRestart() {
        InfoLog(__func__ << " DemoModule");
    }

    void unLoad() {
        InfoLog(__func__ << " DemoModule");
    }

    AppModuleStat getStatus() {
        return stat_;
    }
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_APPMODULE_H
