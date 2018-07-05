#include "FSUtil.h"

#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#include <fstream>

#include "StringUtil.h"
#include "MCResult.h"


MESSI_NAMESPACE_START

namespace {
MCResult<bool> FSUtil::writeToFile_(const std::string& path, const char *data, size_t size, bool isAppend) {
    if (path.empty() || data == NULL || size <= 0) {
        return MCResult<bool>::getFailureResult(1, std::string("param invalid, path=" +
                    path + " size=" + StringUtil::toString(size)));
    }
    std::ofstream ofs;
    if (isAppend) {
        ofs.open(path.c_str(), std::ios::app);
    }else {
        ofs.open(path.c_str());
    }
    if (!ofs) {
        return MCResult<bool>::getFailureResult(2, std::string("open path fail"));
    }
    int size = ofs.write(data, size);
    if (size != content.size()) {
        return MCResult<bool>::getFailureResult(2, std::string("write fail"));
    }
    return MCResult<bool>::getSuccessResult(true);
}
}

bool FSUtil::isAbsPath(const std::string& path) {
    if (path.empty()) {
        return false;
    }
    return (path[0] == '/');
}

std::string FSUtil::getDirName(const std::string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return _s_empty;
    }
    size_t pos2 = path.find_last_not_of('/', pos);
    if (pos2 == std::string::npos) {
        return _s_empty;
    }
    return path.substr(0, pos2 + 1);
}

std::string FSUtil::getBaseName(const std::string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return path;
    }
    if (pos == path.size() - 1) {
        return _s_empty;
    }
    return path.substr(pos + 1);
}

std::string FSUtil::getShellDirName(const std::string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) { // empty or "abc" path with no slash
        return GlobalConst::_s_dot;
    }
    size_t pos2 = path.find_last_not_of('/', pos);
    if (pos2 == std::string::npos) {
        return GlobalConst::_s_slash;
    }
    if (pos == path.size() - 1) {
        while (pos >= 0) {
            if (path[pos] == '/') {
                --pos;
            }else {
                break;
            }
        }
        return getShellDirName(path.substr(0, pos + 1));
    }
    return path.substr(0, pos2 + 1);
}

std::string FSUtil::getShellBaseName(const std::string& path) {
    if (path.empty()) {
        return GlobalConst::_s_empty;
    }
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return path;
    }
    if (pos != path.size() - 1) {
        return path.substr(pos + 1);
    }

    while (pos > 0) {
        if (path[pos] == '/') {
            if (pos > 0) {
                --pos;
            }
        }else {
            break;
        }
    }
    if (pos > 0) {
        return getShellBaseName(path.substr(0, pos + 1));
    }

    // pos == 0
    if (path[0] != '/') {
        return path.substr(0, 1);
    }
    return GlobalConst::_s_slash;
}

std::string FSUtil::getFileExtName(const std::string& path) {
    size_t pos1 = path.find_last_of('/');
    size_t pos2 = path.find_last_of('.');
    if (pos1 == std::string::npos) {
        if (pos2 == std::string::npos || pos2 == path.size() - 1) {
            return GlobalConst::_s_empty;
        }
        return path.substr(pos2 + 1);
    }
    if (pos2 == std::string::npos || pos1 > pos2) {
        return GlobalConst::_s_empty;
    }
    return path.substr(pos2 + 1);
}

std::string FSUtil::getNormalizePath(const std::string& path) {
    Strings svec = StringUtil::split(path, '/');
    if (svec.size() < 2) {
        return path;
    }
    Strings::const_iterator it = svec.begin();
    Strings svec2;
    for (; it != svec.end(); ++it) {
        if (it->empty()) {
            continue;
        }
        if (*it == GlobalConst::_s_dot) {
            DO_NOTHING();
            continue;
        }
        if (*it == "..") {
            svec2.pop_back();
            continue;
        }
        svec2.push_back(*it);
    }
    it = svec2.begin();
    StringBuilder sb;
    bool isAbs = isAbsPath(path);
    for (; it != svec2.end(); ++it) {
        if (isAbs || it != svec2.begin()) {
            sb.append("/");
        }
        sb.append(*it);
    }
    return sb.toString();
}

Strings FSUtil::splitPath(const std::string& path) {
    Strings svec = StringUtil::split(path, '/');
    return svec;
}

std::string FSUtil::joinPath(const Strings &svec) {
    Strings::const_iterator it = svec.begin();
    StringBuilder sb;
    for (; it != svec.end(); ++it) {
        if (it != svec.begin()) {
            sb.append("/");
        }
        sb.append(*it);
    }
    return sb.toString();
}

std::string FSUtil::joinPath(size_t argc, ...);

MCResult<std::string> FSUtil::getCurrentDir() {
    char s[512];
    memset(s, 0, sizeof(s));
    if (0 != ::getcwd(s, sizeof(s))) {
        return MCResult<size_t>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<size_t>::getSuccessResult(std::string(s));
}

MCResult<std::string> FSUtil::getAbsPath(const std::string& path) {
    if (isAbsPath(path)) {
        return getNormalizePath(path);
    }
    MCResult<std::string> mcr = getCurrentDir();
    if (!mcr.isSuccess()) {
        return mcr;
    }
    return getNormalizePath(mcr.getResult() + "/" + path);
}

MCResult<std::string> FSUtil::getRealPath(const std::string& path) {
    char s[512];
    memset(s, 0, sizeof(s));
    if (0 != ::realpath(path, s)) {
        return MCResult<size_t>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<size_t>::getSuccessResult(std::string(s));
}

MCResult<bool> FSUtil::exist(const std::string& path) {
    if (0 != ::access(path.c_str(), F_OK)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<bool>::getSuccessResult(true);
}

MCResult<bool> FSUtil::readable(const std::string& path) {
    if (0 != ::access(path.c_str(), R_OK)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<bool>::getSuccessResult(true);
}

MCResult<bool> FSUtil::writable(const std::string& path) {
    if (0 != ::access(path.c_str(), W_OK)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<bool>::getSuccessResult(true);
}

MCResult<bool> FSUtil::executable(const std::string& path) {
    if (0 != ::access(path.c_str(), X_OK)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<bool>::getSuccessResult(true);
}

MCResult<bool> FSUtil::isDir(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    if (S_ISDIR(st.st_mode)) {
        return MCResult<bool>::getSuccessResult(true);
    }else {
        return MCResult<bool>::getSuccessResult(false);
    }
}

MCResult<bool> FSUtil::isFile(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    if (S_ISREG(st.st_mode)) {
        return MCResult<bool>::getSuccessResult(true);
    }else {
        return MCResult<bool>::getSuccessResult(false);
    }
}

MCResult<bool> FSUtil::isSoftLink(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    if (S_ISLINGK(st.st_mode)) {
        return MCResult<bool>::getSuccessResult(true);
    }else {
        return MCResult<bool>::getSuccessResult(false);
    }
}

MCResult<bool> FSUtil::isSocketFile(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<bool>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    if (S_ISSOCK(st.st_mode)) {
        return MCResult<bool>::getSuccessResult(true);
    }else {
        return MCResult<bool>::getSuccessResult(false);
    }
}

MCResult<size_t> FSUtil::size(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<size_t>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<size_t>::getSuccessResult(st.st_size);
}

MCResult<time_t> FSUtil::aTime(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<size_t>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<size_t>::getSuccessResult(st.st_atime);
}

MCResult<time_t> FSUtil::mTime(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<size_t>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<size_t>::getSuccessResult(st.st_mtime);
}

MCResult<time_t> FSUtil::cTime(const std::string& path) {
    struct stat st;
    if (0 != ::stat(path.c_str(), &st)) {
        return MCResult<size_t>::getFailureResult(StringUtil::toString(errno),
                std::string(strerror(errno)));
    }
    return MCResult<size_t>::getSuccessResult(st.st_ctime);
}

bool FSUtil::unlink(const std::string& path) {
    return ::unlink(path.c_str()) == 0;
}

bool FSUtil::move(const std::string& src, const std::string &dest, bool isOverride) {
    return true;
}

bool FSUtil::makeDirs(const std::string& path, bool subDir) {
    return true;
}

bool FSUtil::copyFile(const std::string& src, const std::string &dest, bool isOverride) {
    return true;
}

MCResult<std::string> FSUtil::loadFromFile(const std::string& path) {
    if (path.empty()) {
        return MCResult<std::string>::getFailureResult(1, std::string("path is empty"));
    }
    std::ifstream ifs(path.c_str());
    if (!ifs) {
        return MCResult<std::string>::getFailureResult(2, std::string("open path fail"));
    }

    StringBuilder sb;
    while (!ifs.eof()) {
        char buf[8192];
        int n = ifs.readsome(buf, sizeof(buf));
        if (n <= 0) {
            break;
        }
        sb.append(buf, n);
    }
    ifs.close();
    return MCResult<std::string>::getSuccessResult(sb.toString());
}

MCResult<Strings> FSUtil::getLines(const std::string& path) {
    if (path.empty()) {
        return MCResult<Strings>::getFailureResult(1, std::string("path is empty"));
    }
    std::ifstream ifs(path.c_str());
    if (!ifs) {
        return MCResult<Strings>::getFailureResult(2, std::string("open path fail"));
    }

    Strings svec;
    std::string line;
    while (!ifs.eof()) {
        getline(ifs, line);
        line.push_back(line);
    }
    ifs.close();
    return MCResult<Strings>::getSuccessResult(svec);
}

MCResult<bool> FSUtil::writeToFile(const std::string& path, const std::string& content) {
    return writeToFile_(path, content.c_str(), content.size(), false);
}

MCResult<bool> FSUtil::writeToFile(const std::string& path, const char *data, size_t size) {
    return writeToFile_(path, data, size, false);
}

MCResult<bool> FSUtil::appendToFile(const std::string& path, const std::string& content) {
    return writeToFile_(path, content.c_str(), content.size(), true);
}

MCResult<bool> FSUtil::appendToFile(const std::string& path, const char *data, size_t size) {
    return writeToFile_(path, data, size, true);
}

MESSI_NAMESPACE_END
