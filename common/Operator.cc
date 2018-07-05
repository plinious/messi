#include <sstream>
#include <stdexcept>
#include <libwws/Logger.h>

#include <libwws/Operator.h>
#include "json/json.h"

static const std::string __g_placeholder_key("stomp2metaq_placeholder_key");

namespace WWS {

    namespace detail {
        std::string getString(const Json::Value &stObject, const std::string &sName) {
            Json::Value stValue = stObject.get(sName, Json::Value::null);
            if(!stValue.isString()) {
                ErrLog(__func__ << " get json type error sName = " << sName);
                return "";
            }
            return stValue.asString();
        }
        Json::Value getArray(const Json::Value &stObject, const std::string &sName) {
            Json::Value stValue = stObject.get(sName, Json::Value::null);
            if(!stValue.isArray()) {
                ErrLog(__func__ << " get json type error sName = " << sName);
                return Json::Value();
            }
            return stValue;

        }
        std::string getStringElement(const Json::Value &array, unsigned int idx) {
            Json::Value stValue = array[idx];
            if(!stValue.isString()) {
                ErrLog(__func__ << " get json type error idx = " << idx);
                return "";
            }
            return stValue.asString();
        }
        Json::Value getObjectElement(const Json::Value &array, unsigned int idx) {
            Json::Value stValue = array[idx];
            if(!stValue.isObject()) {
                ErrLog(__func__ << " get json type error idx = " << idx);
                return Json::Value();
            }
            return stValue;
        }
    }

    bool RuleSt::json2rulest(const std::string &str) {
        try {
            Json::Reader stReader;
            Json::Value root;
            bool bRet = false;
            try {
                bRet = stReader.parse(str, root);
            }catch (...){
                ErrLog(__func__ << " parse json exception str = " << str);
                return false;
            }

            if(!bRet) { // simple mode
                WarnLog(__func__ << " FAILED_PARSE_JSON, sContent = " << str);
                Strings svec = StringUtil::split(str, ':');
                if (svec.size() == 2) {
                    mSimpleMode = true;
                    mTopic = StringUtil::trim(svec[0]);
                    mTag = StringUtil::trim(svec[1]);
                    return true;
                }else {
                    ErrLog(__func__ << " parse json error, it is also not simplemode. msg=" << str);
                    return false;
                }
            }

            // not simple mode
            mSimpleMode = false;
            mTopic = detail::getString(root, "topic");
            mTag = detail::getString(root, "tag");
            std::string typeStr = detail::getString(root, "type");
            mTopOptype = (typeStr == "&" ? OP_AND: OP_OR);

            mComplexExpressions.clear();
            Json::Value arrayObj = detail::getArray(root, "exp");
            for (size_t i = 0; i < arrayObj.size(); i++) {
                Json::Value jsonCexp = detail::getObjectElement(arrayObj, i);
                ComplexExpression cexp;
                typeStr = detail::getString(jsonCexp, "type");
                cexp.mOptype = (typeStr == "&" ? OP_AND: OP_OR);

                Json::Value expArrayObj = detail::getArray(jsonCexp, "exp");
                for (size_t j = 0; j < expArrayObj.size(); j++) {
                    std::string expStr = detail::getStringElement(expArrayObj, j);
                    Strings expvec = StringUtil::split(expStr, ',');
                    if (expvec.size() < 3) {
                        ErrLog(__func__ << " init expression fail , expstr = " << expStr);
                        return false;
                    }
                    Expression exp;
                    exp.mKey = expvec[0];
                    exp.mOp = OperatorFactory::NewOperator(expvec[1], expvec[2]);
                    if (!exp.mOp) {
                        ErrLog(__func__ << " init operator fail , expstr = " << expStr);
                        return false;
                    }
                    if (expvec[1] == "alwaystrue") {
                        exp.mKey = __g_placeholder_key;
                    }
                    cexp.mExpressions.push_back(exp);
                }
                mComplexExpressions.push_back(cexp);
            }
            return true;
        } catch (std::exception & e) {
            ErrLog(__func__ << " init rule exception fail : " << e.what());
        } catch (...) {
            ErrLog(__func__ << " init rule exception fail");
        }
        return false;
    }

    bool RuleSt::Init(const std::string &str) {
        bool ret= json2rulest(str);
        if (ret) {
            InfoLog(" init rule succ : " << toString());
        }
        return ret;
    }

    std::string RuleSt::toString() const {
        std::stringstream ss;
        if (mSimpleMode) {
            ss << "simplemode " << mTopic << ":" << mTag;
        } else {
            Json::Value root;
            Json::FastWriter writer;
            try {
                root["topic"] = mTopic;
                root["tag"] = mTag;
                root["type"] = (mTopOptype == OP_AND ? "&" : "|");
                Json::Value cexps_json;
                for (size_t i = 0; i < mComplexExpressions.size(); ++i) {
                    const ComplexExpression &cexp = mComplexExpressions[i];
                    Json::Value cexp_json;
                    cexp_json["type"] = (cexp.mOptype == OP_AND ? "&" : "|");
                    Json::Value exps_json;
                    for (size_t j = 0; j < cexp.mExpressions.size(); ++j) {
                        exps_json[(unsigned int)j] = cexp.mExpressions[j].toString();
                    }
                    cexp_json["exp"] = exps_json;
                    cexps_json[(unsigned int)i] = cexp_json;
                }
                root["exp"] = cexps_json;
                ss << writer.write(root);
                return ss.str();
            } catch (...) {
                return "json toString failed";
            }
        }
        return ss.str();
    }

} // namespace WWS
