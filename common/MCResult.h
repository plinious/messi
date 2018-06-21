#ifndef MESSI_COMMON_MC_RESULT_H
#define MESSI_COMMON_MC_RESULT_H

MESSI_NAMESPACE_START

template <class T>
class MCResult {
    public:
        MCResult() {}
        ~MCResult() {}

        bool        isSuccess() const   { return success_; }
        std::string getErrCode()const   { return errCode_; }
        std::string getErrMsg() const   { return errMsg_; }
        T           getResult() const   { return result_; }
        T          &getResultRef() const { return result_; }
        void       *getExt()    const   { return ext_; }

        void setSuccess(bool success) { success_ = success; }
        void setErrCode(const std::string &errCode) { errCode_ = errCode; }
        void setErrMsg(const std::string &errMsg) { errMsg_ = errMsg; }
        void setResult(const T &result) { result_ = result; }
        void setExt(void *ext) { ext_ = ext; }

    public:
        static MCResult<T> getSuccessResult(const T &result) {
            MCResult<T> mcr;
            mcr.setSuccess(true);
            mcr.setErrCode("0");
            mcr.setErrCode("success");
            mcr.setResult(result);
            mcr.setExt((void *)NULL);
            return mcr;
        }

        static MCResult<T> getFailureResult(const std::string &code, const std::string &msg) {
            MCResult<T> mcr;
            mcr.setSuccess(false);
            mcr.setErrCode(code);
            mcr.setErrCode(msg);
            mcr.setExt((void *)NULL);
            return mcr;
        }

    private:
        bool        success_;
        std::string errCode_;;
        std::string errMsg_;
        T           result_;
        void *      ext_;
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_MC_RESULT_H
