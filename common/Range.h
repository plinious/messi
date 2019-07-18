#pragma once

#include <string>
#include <memory>

namespace messi {

// Range is a class template that represent a set of ranges of numer of other
// object that support compare. Range is copyable, and may be inited as a empty
// object or from a map, or another Range object.
template <class T>
class Range {
 public:
  using ObjMap = std::map<T, T>;

  Range() = default;
  explicit Range(const ObjMap &m) {
    initByMap(m);
  }
  Range(const Range &br) : range_map_(br.getMap()) {}
  Range &operator=(const Range &br) {
    if (&br == this) {
      return *this;
    }
    this->range_map_ = br.getMap();
    return *this;
  }
  ~Range() = default;

  void setMap(const ObjMap &range_map) {
    initByMap(range_map);
  }

  const ObjMap &getMap() const {
    return range_map_;
  }

 public:
  bool empty() const {
    return range_map_.empty();
  }

  size_t size() const {
    return range_map_.size();
  }

  void clear() {
    range_map_.clear();
  }

  void put(const T &e1, const T &e2) {
    auto const *p1 = &e1;
    auto const *p2 = &e2;
    if (e1 > e2) {
      p1 = &e2;
      p2 = &e1;
    }

    auto it1 = getIter(*p1);
    if (it1 == range_map_.end()) {
      range_map_[*p2] = *p1;
      return;
    }
    auto lower = it1->second;
    if (*p1 <= lower) {
      lower = *p1;
    }
    auto it2 = getIter(*p2);
    range_map_.erase(it1, it2);
    if (it2 == range_map_.end() || *p2 < it2->second) {
      range_map_[*p2] = lower;
    }else {
      range_map_[it2->first] = lower;
    }
    return;
  }

  void remove(const T &e1, const T &e2) {
    auto const *p1 = &e1;
    auto const *p2 = &e2;
    if (e1 > e2) {
      p1 = &e2;
      p2 = &e1;
    }
    auto it1 = getIter(*p1);
    if (it1 == range_map_.end()) {
      return;
    }
    auto it2 = getIter(*p2);
    if (*p1 > it1->second) {
      range_map_[*p1] = it1->second;
    }
    range_map_.erase(it1, it2);
    if (it2 != range_map_.end() && *p2 > it2->second) {
      range_map_[it2->first] = *p2;
    }
  }

  bool isIn(const T &e) const {
    auto it = getIter(e);
    return it != range_map_.end() && e >= it->second;
  }

 private:
  typename ObjMap::const_iterator getIter(const T &e) const {
    return range_map_.lower_bound(e);
  }

  void initByMap(const ObjMap &obj_map) {
    for (auto entry : obj_map) {
      put(entry.first, entry.second);
    }
  }

 private:
  ObjMap range_map_;
};

using UIntRange = Range<uint32_t>;
using IntRange = Range<int32_t>;
using ULongRange = Range<uint64_t>;
using LongRange = Range<int64_t>;

} // namespace messi
