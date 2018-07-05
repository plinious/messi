#ifndef MESSI_COMMON_NUM_RANGE_H
#define MESSI_COMMON_NUM_RANGE_H

#include "types.h"

#include "IpAddr.h"

// 抽象的区间
// 用map实现.可以是0到多个小区间的集合
// 元素可以是数字，ip，或其他实现了<操作符和==操作符的类,有复制语义

MESSI_NAMESPACE_START

enum RangeType {
    CLOSE_CLOSE = 0, // 前闭后闭区间. [low, upper]
    CLOSE_OPEN,      // 前闭后开区间. [low, upper)
    OPEN_CLOSE,      // 前开后闭区间. (low, upper]
    OPEN_OPEN,       // 前开后开区间. (low, upper)
    TYPE_END
};

template <class T>
class BaseRange {
    public:
        typedef std::map<T, T> RangeMap;
        typedef RangeMap::const_iterator ConstIter;
        typedef RangeMap::iterator Iter;

        explicit BaseRange(RangeType type = CLOSE_CLOSE) : type_(type) {}
        virtual ~BaseRange() {}
        BaseRange(const BaseRange &br) : type_(br.getRangeType()), rangeMap_(br.getMap()) {}
        BaseRange &operator=(const BaseRange &br) {
            if (&br == this) {
                return *this;
            }
            this->type_ = br.getRangeType();
            this->rangeMap_ = br.getMap();
            return *this;
        }
        void clear() { rangeMap_.clear(); }

    public:

        bool isEmpty() { return rangeMap_.empty(); }

        bool addRange(const T &e1, const T &e2) {
            if (e1 > e2) {
                T tmp = e1;
                e1 = e2;
                e2 = tmp;
            }
            if (e1 == e2 && type_ != CLOSE_CLOSE) { // e1 == e2只有在[]区间才有意义,其他区间直接返回
                return true;
            }
            Iter it1 = getIter(e1);
            if (it1 == rangeMap_.end()) { // 比现有区间都要大
                rangeMap_[e2] = e1;
                return true;
            }
            T lower_final = (it1->second < e1 ? it1->second : e1);

            // 检查,区间下限是取e1,还是跟现有区间合并
            bool lowerNeedMerge = false;
            if (e1 < it1->second) {
                lowerNeedMerge = false;
            }else if (e1 > it1->second) {
                lowerNeedMerge = true;
            }else {
                lowerNeedMerge = !(type_ == OPEN_OPEN);
            }

            Iter it2 = getIter(e2);
            bool upperNeedMerge = false;
            if (it2 != rangeMap_.end()) {
                // 检查,区间上限是取e2,还是跟现有区间合并
                if (e2 < it2->second) {
                    upperNeedMerge = false;
                }else if (e2 > it2->second) {
                    upperNeedMerge = true;
                }else {
                    upperNeedMerge = (type_ == CLOSE_OPEN || type_ == CLOSE_CLOSE);
                }
            }
            rangeMap_.erase(it1, it2);
            if (upperNeedMerge) {
                it2->second = lower_final;
            }else {
                rangeMap_[e2] = lower_final;
            }
            return true;
        }

        bool isInRange(const T &element) {
            ConstIter it = getIter(element);
            if (it == rangeMap_.end() || element < it->second) {
                return false;
            }
            if (element == it->second) {
                if (type_ == OPEN_OPEN || type_ == OPEN_CLOSE) {
                    return false;
                }
            }
            return true;
        }

        void setRangeType(RangeType type) { type_ = type; }
        RangeType getRangeType(RangeType type) { return type_; }
        void setMap(const std::map<T, T> &rangeMap) {rangeMap_ = rangeMap; }
        RangeMap &getMap() { return rangeMap_; }

    private:
        ConstIter getIter(const T &e) {
            if (type_ == CLOSE_CLOSE || type_ == OPEN_CLOSE) {
                it = rangeMap_.lower_bound(e);
            }else {
                it = rangeMap_.upper_bound(e);
            }
            return it;
        }

    private:
        RangeType  type_;
        RangeMap   rangeMap_;
};

typedef BaseRange<uint32_t> UIntRange;
typedef BaseRange<int32_t>  IntRange;
typedef BaseRange<uint64_t> ULongRange;
typedef BaseRange<int64_t>  LongRange;
typedef BaseRange<IpAddr>   IpRange;

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_NUM_RANGE_H
