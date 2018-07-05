#ifndef MESSI_COMMON_OPERATOR_H
#define MESSI_COMMON_OPERATOR_H

#include <libwws/StringUtil.h>
#include "types.h"

MESSI_NAMESPACE_START

class Operator : public RefObj {
    public:
        virtual bool GetResult(const std::string &value) const = 0;
        virtual std::string toString() const = 0;
};
typedef RefPtr<Operator> OperatorPtr;

class AlwaysTrue : public Operator {
    public:
        AlwaysTrue(const std::string &val) : mValue("default_val") {}
        virtual bool GetResult(const std::string &value) const {
            return true;
        }
        virtual std::string toString() const {
            std::string s("alwaystrue ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class StartWith : public Operator {
    public:
        StartWith(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            if (value.size() < mValue.size()) {
                return false;
            }
            return strncmp(value.c_str(), mValue.c_str(), mValue.size()) == 0;
        }
        virtual std::string toString() const {
            std::string s("startwith ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class NotStartWith : public Operator {
    public:
        NotStartWith(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            if (value.size() < mValue.size()) {
                return true;
            }
            return strncmp(value.c_str(), mValue.c_str(), mValue.size()) != 0;
        }
        virtual std::string toString() const {
            std::string s("notstartwith ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class EndWith : public Operator {
    public:
        EndWith(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            if (value.size() < mValue.size()) {
                return false;
            }
            return strncmp(value.c_str() + value.size() - mValue.size(),
                    mValue.c_str(),
                    mValue.size()) == 0;
        }
        virtual std::string toString() const {
            std::string s("endwith ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class NotEndWith : public Operator {
    public:
        NotEndWith(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            if (value.size() < mValue.size()) {
                return true;
            }
            return strncmp(value.c_str() + value.size() - mValue.size(),
                    mValue.c_str(),
                    mValue.size()) != 0;
        }
        virtual std::string toString() const {
            std::string s("notendwith ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class Contain : public Operator {
    public:
        Contain(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return value.find(mValue) != std::string::npos;
        }
        virtual std::string toString() const {
            std::string s("contain ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class NotContain : public Operator {
    public:
        NotContain(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return value.find(mValue) == std::string::npos;
        }
        virtual std::string toString() const {
            std::string s("notcontain ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class Equal : public Operator {
    public:
        Equal(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return value == mValue;
        }
        virtual std::string toString() const {
            std::string s("equal ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class NotEqual : public Operator {
    public:
        NotEqual(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return value != mValue;
        }
        virtual std::string toString() const {
            std::string s("notequal ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

// in a set of strings
class In : public Operator {
    public:
        In(const std::string &val) {
            mOrigValue = val;
            mValues = StringUtil::string2set(val, '|');
        }
        virtual bool GetResult(const std::string &value) const {
            return mValues.find(value) != mValues.end();
        }
        virtual std::string toString() const {
            std::string s("in ");
            return s.append(mOrigValue);
        }

    private:
        StringSet   mValues;
        std::string mOrigValue;
};

class NotIn : public Operator {
    public:
        NotIn(const std::string &val) {
            mOrigValue = val;
            mValues = StringUtil::string2set(val, '|');
        }
        virtual bool GetResult(const std::string &value) const {
            return mValues.find(value) == mValues.end();
        }
        virtual std::string toString() const {
            std::string s("notin ");
            return s.append(mOrigValue);
        }

    private:
        std::string mOrigValue;
        StringSet mValues;
};

class Greater : public Operator {
    public:
        Greater(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return strcmp(value.c_str(), mValue.c_str()) > 0;
        }
        virtual std::string toString() const {
            std::string s("greater ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class GreaterEqual : public Operator {
    public:
        GreaterEqual(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return strcmp(value.c_str(), mValue.c_str()) >= 0;
        }
        virtual std::string toString() const {
            std::string s("greaterequal ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class Less : public Operator {
    public:
        Less(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return strcmp(value.c_str(), mValue.c_str()) < 0;
        }
        virtual std::string toString() const {
            std::string s("less ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class LessEqual : public Operator {
    public:
        LessEqual(const std::string &val) : mValue(val) {}
        virtual bool GetResult(const std::string &value) const {
            return strcmp(value.c_str(), mValue.c_str()) <= 0;
        }
        virtual std::string toString() const {
            std::string s("lessequal ");
            return s.append(mValue);
        }

    private:
        std::string mValue;
};

class DigitalGreater : public Operator {
    public:
        DigitalGreater(const std::string &val) {
            mOrigValue = val;
            mValue = StringUtil::atoi(val);
        }
        virtual bool GetResult(const std::string &value) const {
            int32_t val = StringUtil::atoi(value);
            return val > mValue;
        }
        virtual std::string toString() const {
            std::string s("digitalgreater ");
            return s.append(mOrigValue);
        }

    private:
        std::string mOrigValue;
        int32_t     mValue;
};

class DigitalGreaterEqual : public Operator {
    public:
        DigitalGreaterEqual(const std::string &val) {
            mOrigValue = val;
            mValue = StringUtil::atoi(val);
        }
        virtual bool GetResult(const std::string &value) const {
            int32_t val = StringUtil::atoi(value);
            return val >= mValue;
        }
        virtual std::string toString() const {
            std::string s("digitalgreaterequal ");
            return s.append(mOrigValue);
        }

    private:
        std::string mOrigValue;
        int32_t mValue;
};

class DigitalLess : public Operator {
    public:
        DigitalLess(const std::string &val) {
            mOrigValue = val;
            mValue = StringUtil::atoi(val);
        }
        virtual bool GetResult(const std::string &value) const {
            int32_t val = StringUtil::atoi(value);
            return val < mValue;
        }
        virtual std::string toString() const {
            std::string s("digitalless ");
            return s.append(mOrigValue);
        }

    private:
        std::string mOrigValue;
        int32_t mValue;
};

class DigitalLessEqual : public Operator {
    public:
        DigitalLessEqual(const std::string &val) {
            mOrigValue = val;
            mValue = StringUtil::atoi(val);
        }
        virtual bool GetResult(const std::string &value) const {
            int32_t val = StringUtil::atoi(value);
            return val <= mValue;
        }
        virtual std::string toString() const {
            std::string s("digitallessequal ");
            return s.append(mOrigValue);
        }

    private:
        std::string mOrigValue;
        int32_t mValue;
};

class Empty : public Operator {
    public:
        Empty(const std::string &val) { }
        virtual bool GetResult(const std::string &value) const {
            return value.empty();
        }
        virtual std::string toString() const {
            return "empty placement_rval";
        }
};

class NotEmpty : public Operator {
    public:
        NotEmpty(const std::string &val) { }
        virtual bool GetResult(const std::string &value) const {
            return !value.empty();
        }
        virtual std::string toString() const {
            return "notempty placement_rval";
        }
};

class OperatorFactory {
    public:
        static RefPtr<Operator> NewOperator(const std::string &op, const std::string &rval) {
            if (op  == std::string("startwith")) {
                return RefPtr<Operator>(new StartWith(rval));
            }else if (op  == std::string("notstartwith")) {
                return RefPtr<Operator>(new NotStartWith(rval));
            }else if (op  == std::string("endwith")) {
                return RefPtr<Operator>(new EndWith(rval));
            }else if (op  == std::string("notendwith")) {
                return RefPtr<Operator>(new NotEndWith(rval));
            }else if (op  == std::string("contain")) {
                return RefPtr<Operator>(new Contain(rval));
            }else if (op  == std::string("notcontain")) {
                return RefPtr<Operator>(new NotContain(rval));
            }else if (op  == std::string("equal")) {
                return RefPtr<Operator>(new Equal(rval));
            }else if (op  == std::string("notequal")) {
                return RefPtr<Operator>(new NotEqual(rval));
            }else if (op  == std::string("in")) {
                return RefPtr<Operator>(new In(rval));
            }else if (op  == std::string("notin")) {
                return RefPtr<Operator>(new NotIn(rval));
            }else if (op  == std::string("greater")) {
                return RefPtr<Operator>(new Greater(rval));
            }else if (op  == std::string("greaterequal")) {
                return RefPtr<Operator>(new GreaterEqual(rval));
            }else if (op  == std::string("less")) {
                return RefPtr<Operator>(new Less(rval));
            }else if (op  == std::string("notless")) {
                return RefPtr<Operator>(new LessEqual(rval));
            }else if (op  == std::string("digitalgreater")) {
                return RefPtr<Operator>(new DigitalGreater(rval));
            }else if (op  == std::string("digitalgreaterequal")) {
                return RefPtr<Operator>(new DigitalGreaterEqual(rval));
            }else if (op  == std::string("digitalless")) {
                return RefPtr<Operator>(new DigitalLess(rval));
            }else if (op  == std::string("digitallessequal")) {
                return RefPtr<Operator>(new DigitalLessEqual(rval));
            }else if (op  == std::string("alwaystrue")) {
                return RefPtr<Operator>(new AlwaysTrue(rval));
            }else if (op  == std::string("empty")) {
                return RefPtr<Operator>(new Empty(rval));
            }else if (op  == std::string("notempty")) {
                return RefPtr<Operator>(new NotEmpty(rval));
            }else {
                return RefPtr<Operator>();
            }
        }
};

// 单个表达式
// for example:
// key1 contain "abc"
// key2 startwith "abc"
// key3 digitalless 100
class Expression : public RefObj {
    public:
        std::string mKey;
        OperatorPtr mOp;
        bool GetResult(const std::string &key) const {
            if (!mOp) {
                return false;
            }
            return mOp->GetResult(key);
        }
        std::string toString() const {
            return mKey + " " + mOp->toString();
        }
};

enum OPTYPE {
    OP_AND,
    OP_OR,
};

// 由多个Expression组成的复杂表达式, 多个表达式的"与"、"或"关系
// for example:
// Expression1 && Expression2 ...
// Expression1 || Expression2 || Expression3 ...
class ComplexExpression {
    public:
        std::vector<Expression> mExpressions;
        OPTYPE mOptype;

    public:
        template <class MAP>
            std::string getValue(const MAP &smap, const std::string &key) const {
                typename MAP::const_iterator it = smap.find(key);
                if (it == smap.end()) {
                    return __s_empty;
                }
                return it->second;
            }

        template <class MAP>
            bool GetResult(const MAP &smap) const {
                if (mOptype == OP_AND) {
                    for (int i = 0; i < mExpressions.size(); ++i) {
                        std::string lval = getValue(smap, mExpressions[i].mKey);
                        if (!mExpressions[i].GetResult(lval)) {
                            return false;
                        }
                    }
                    return true;
                } else if (mOptype == OP_OR) {
                    for (int i = 0; i < mExpressions.size(); ++i) {
                        std::string lval = getValue(smap, mExpressions[i].mKey);
                        if (mExpressions[i].GetResult(lval)) {
                            return true;
                        }
                    }
                    return false;
                }
                return false;
            }
};

class RuleSt {
    public:

        // 多个ComplexExpression之间的"与"、"或"关系
        // 无论多么复杂的逻辑关系,都可以化简为"与-或"式,以及"或-与"试
        // "与-或"式:
        // (exp1 && exp2) || (exp3 && exp4 && exp5)
        // "或-与"式:
        // (exp1 || exp2) && (exp3 || exp4 || exp5)
        std::vector<ComplexExpression> mComplexExpressions;
        OPTYPE mTopOptype;

        std::string mTopic;
        std::string mTag;
        bool        mSimpleMode;

    public:
        bool Init(const std::string &str);
        bool json2rulest(const std::string &str);

        std::string toString() const;

        template <class MAP>
            bool GetResult(const MAP &smap) const {
                if (mTopOptype == OP_AND) {
                    for (int i = 0; i < mComplexExpressions.size(); ++i) {
                        if (!mComplexExpressions[i].GetResult(smap)) {
                            return false;
                        }
                    }
                    return true;
                } else if (mTopOptype == OP_OR) {
                    for (int i = 0; i < mComplexExpressions.size(); ++i) {
                        if (mComplexExpressions[i].GetResult(smap)) {
                            return true;
                        }
                    }
                    return false;
                }
                return false;
            }

};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_OPERATOR_H
