#ifndef __Operator_ext_h__
#define __Operator_ext_h__

#include <libwws/StringUtil.h>
#include <libwws/RefObj.h>

#include "Operator.h"

namespace spider {

    enum ExpNodeType {
        ND_START = 0,
        ND_EXP, // 表达式节点,也就是叶子节点
        ND_AND, // 与节点
        ND_OR, // 或节点
        ND_LEFT_PARENTHESES, // 左括号,只在初始化时有用
        ND_RIGHT_PARENTHESES, // 左括号,只在初始化时有用
        N_END
    };


    class ExpressionExt : public RefObj {

    private:
        ExpNodeType mNodeType;

        // mNodeType == ND_EXP 时有效
        ExpressionPtr mExpPtr;

        // mNodeType == ND_AND 或ND_OR 时有效
        std::vector<RefPtr<ExpressionExt> > mSubExps;

    private:
        bool isCalculateSymbol() {
            return mNodeType == N_AND || mNodeType == N_OR;
        }
        bool amIHigherYou(const ExpressionExt &ti) {
            if (mNodeType == N_AND && ti.mNodeType == N_OR) {
                return true;
            }
            return false;
        }

    public:
        ExpressionExt() : mNodeType(ND_EXP) {}
        ExpressionExt &assign(const ExpressionExt &ee) {
            if (this != &ee) {
                mNodeType = ee.mNodeType;
                mExpPtr = ee.mExpPtr;
                mSubExps = ee.mSubExps;
            }
            return *this;
        }

        bool isValid() {
            if (mNodeType == ND_EXP) {
                return !! mExpPtr;
            }
            if (mNodeType == ND_AND || mNodeType == ND_OR) {
                return !mSubExps.empty();
            }
            if (mNodeType == ND_LEFT_PARENTHESES || mNodeType == ND_RIGHT_PARENTHESES) {
                return true;
            }
            return false;
        }

        // 参数为中缀表达式
        // 2.再由后缀表达式转为树
        // 3.再对树适当合并一下(相邻两级的运算符相同的话则合并掉,直到相邻两级的运算符全都不同)
        // 规则形如 exp1 & exp2 | (exp3 | exp4)
        bool initialize(const std::string &s) {
            if (s.empty()) {
                return false;
            }

            // 0.先切割字符串
            Strings vs = toStrings(s);
            if (vs.empty()) {
                return false;
            }
            std::vector<ExpressionExt> exp_vec;
            if (!getItemVector(vs, exp_vec)) {
                return false;
            }

            // 1.转为后缀表达式
            std::vector<ExpressionExt> res_vec;
            if (!transformToSuffixExpression(tiv, res_vec)) {
                return false;
            }

            // 2.后缀表达式转为树
            if (res_vec.size() <= 0) {
                return false;
            }
            std::stack<ExpressionExt> exp_stack;
            for (size_t i = 0; i < res_vec.size(); ++i) {
                // 1.遇到表达式则直接入栈
                // 2.遇到运算符,则pop两个表达式出来进行计算
                if (res_vec[i].mNodeType == ND_EXP) {
                    exp_stack.push(res_vec[i]);
                    continue;
                }
                if (res_vec[i].mNodeType == ND_AND || res_vec[i].mNodeType == ND_OR) {
                    if (exp_stack.size() < 2) {
                        ErrLog(__func__ << " unexpected stack size should >= 2, s: " << s);
                        return false;
                    }

                    ExpressionExt e1 = exp_stack.top();
                    exp_stack.pop();
                    ExpressionExt e2 = exp_stack.top();
                    exp_stack.pop();
                    if (e1.mNodeType != ND_EXP || e2.mNodeType != ND_EXP) {
                        ErrLog(__func__ << " unexpected node type , s: " << s);
                        return false;
                    }
                    ExpressionExt tmp_ti;
                    tmp_ti.mNodeType = res_vec[i].mNodeType;
                    tmp_ti.push_back(e1);
                    tmp_ti.push_back(e2);
                    exp_stack.push(tmp_ti);
                    //
                    continue;
                }
                ErrLog(__func__ << " unexpected nodetype : " << res[i].mNodeType);
            }
            if (exp_stack.size() != 1) {
                ErrLog(__func__ << " final stack size not 1 size =  " << exp_stack.size());
                return false;
            }
            assign(exp_stack.top());
            return false;
        }

        Strings toStrings(const std::string &s) {
            Strings vs;
            size_t i = 0;
            size_t j = 0;
            size_t size = s.size();
            while {

                // 找到第一个非空字符
                while (i < size && isblank(s[i]) != 0) { ++i; }
                if (i >= size) {
                    break;
                }

                // 从非空字符开始,找到第一个空字符或字符串结尾
                j = i + 1;
                while (j < size && isblank(s[j]) == 0) { ++j; }
                std::string tmp_str(s, i, j);
                vs.push_back(tmp_str);
                if (j >= size) {
                    break;
                }
                i = j + 1;
            }(i < size && j < size);
            return vs;
        }

        bool getItemVector(const Strings &vs, std::vector<ExpressionExt> &eev) {
            for (size_t i = 0; i < vs.size(); ++i) {
                ExpressionExt ee;
                if (vs[i] == "(") {
                    ee.mNodeType = ND_LEFT_PARENTHESES;
                    eev.push_back(ee);
                    continue;
                }
                if (vs[i] == ")") {
                    ee.mNodeType = ND_RIGHT_PARENTHESES;
                    eev.push_back(ee);
                    continue;
                }
                if (vs[i] == "|") {
                    ee.mNodeType = ND_OR;
                    eev.push_back(ee);
                    continue;
                }
                if (vs[i] == "&") {
                    ee.mNodeType = ND_AND;
                    eev.push_back(ee);
                    continue;
                }

                if (i + 2 >= vs.size()) { // 表达式必须由 "key operator value" 3部分组成
                    ErrLog(__func__ << " init operator fail size too small, i = " << i << " expstr = " << s);
                    return false;
                }
                ExpressionPtr exp = new Expression();
                exp->mKey = vs[i];
                exp->mOp = OperatorFactory::NewOperator(vs[i + 1], vs[i + 2]);
                if (!exp->mOp) {
                    ErrLog(__func__ << " init operator fail , expstr = " << s);
                    return false;
                }

                ee.mNodeType = NO_EXP;
                ee.mExpPtr = exp;
                ee.mSubExps.clear();
                eev.push_back(ee);
                i += 2;
            }
            return true;
        }

        bool transformToSuffixExpression(const std::vector<ExpressionExt> &tiv, std::vector<ExpressionExt> &s2) {
            std::stack<ExpressionExt> s1;
            for (size_t i = 0; i < tiv.size(); ++i) {
                if (tiv[i].mNodeType == ND_EXP) {
                    s2.push_back(tiv[i]);
                    continue;
                }
                if (tiv[i].isCalculateSymbol()) {
                    if (i == 0 || tiv[i - 1].mNodeType != ND_EXP) {
                        // 运算符之前只能是值,不能是括号或其他运算符
                        ErrLog(__func__ << " CalculateSymbol invalid s = " << s);
                        return false;
                    }
                    if (!s1.top().isCalculateSymbol() || tiv[i].amIHigherYou(s1.top())) {
                        s1.push(tiv[i]);
                    }else {
                        while (!s1.empty()) {
                            ExpressionExt &tmpItem = s1.top();
                            if (!tmpItem.isCalculateSymbol() || tiv[i].amIHigherYou(tmpItem)) {
                                break;
                            }else {
                                s2.push_back(tmpItem);
                                s1.pop();
                            }
                            s2.push_back(tiv[i]);
                        }
                    }
                    continue;
                }
                if (tiv[i].mNodeType == ND_LEFT_PARENTHESES) {
                    s1.push(tiv[i]);
                    continue;
                }
                if (tiv[i].mNodeType == ND_RIGHT_PARENTHESES) {
                    // 将s1元素逐个出栈,并丢弃遇到的最近的一个"(".如果没有"(",说明表达式无效
                    while (!s1.empty()) {
                        ExpressionExt &tmpItem = s1.top();
                        if (tmpItem.mNodeType == ND_LEFT_PARENTHESES) {
                            break;
                        }else {
                            s2.push_back(tmpItem);
                            s1.pop();
                        }
                    }
                    if (s1.top().mNodeType == ND_LEFT_PARENTHESES) {
                        s1.pop();
                    }else {
                        ErrLog(__func__ << " need a N_LEFT_PARENTHESES , the expression invalid " << s);
                        return false;
                    }
                    continue;
                }
            }
            if (!s1.empty()) {
                ErrLog(__func__ << " stack1 not empty , the expression is invalid" << s);
                return false;
            }
            return true;
        }

        template <class MAP>
        bool GetResult(const MAP &smap) const {
            // 1.叶子节点
            if (mNodeType == ND_EXP) {
                if (!mExpPtr) {
                    // 初始化时表达式为空的节点应该置为invalid报错,不会走到这个分支
                    return false;
                }
                return mExpPtr->GetResult(smap);
            }

            // 2.parent节点
            if (mSubExps.empty()) {
                // 初始化时表达式为空的节点应该置为invalid报错,不会走到这个分支
                return false;
            }
            if (mOptype == OP_AND) {
                for (int i = 0; i < mSubExps.size(); ++i) {
                    if (!mSubExps[i].GetResult(smap)) {
                        return false;
                    }
                }
                return true;
            }
            // mOptype == OP_OR
            for (int i = 0; i < mSubExps.size(); ++i) {
                std::string lval = getValue(smap);
                if (mSubExps[i].GetResult(smap)) {
                    return true;
                }
            }
            return false;
        }

    private:
        template <class MAP>
            std::string getValue(const MAP &smap, const std::string &key) const {
                typename MAP::const_iterator it = smap.find(key);
                if (it == smap.end()) {
                    return __s_empty;
                }
                return it->second;
            }
    };
    typedef RefPtr<ExpressionExt>  ExpressionExtPtr;

} // namespace WWS

#endif // __Operator_ext_h__
