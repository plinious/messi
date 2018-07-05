#ifndef MESSI_COMMON_FSUTIL_H
#define MESSI_COMMON_FSUTIL_H

#include "types.h"
#include "MCResult.h"

MESSI_NAMESPACE_START

class FSUtil {
public:

    /*
     * if the path start with / ,then it is a absolutely path, otherwise not
     * input : output
     * empty : false
     * /a/b : true
     * a/b : false
     */
    static bool isAbsPath(const std::string& path);

    /*
     * get the dirname from the input string path,
     * no fs operation is taken. notice that the api is
     * not the same with the shell command "dirname"
     *
     * input : output
     * empty : empty
     * /a/b/c : /a/b
     * /a/b///c : /a/b
     * /a/b/c/d/ : /a/b/c/d
     * abc : empty
     * // : empty
     * / : empty
     */
    static std::string getDirName(const std::string& path);

    /*
     * get the basename from the input string path, 
     * no fs operation is taken. notice that the api is
     * not the same with the shell command "basename"
     *
     * input : output
     * empty : empty
     * /a/b/c : c
     * /a/b/c/d/ : empty
     * abc : abc
     * // : empty 
     *
     */
    static std::string getBaseName(const std::string& path);

    /*
     * get the dirname from the input string path,
     * no fs operation is taken. notice that the api is
     * the same with the shell command "dirname"
     *
     * input : output
     * empty : .
     * /a/b/c : /a/b
     * /a/b///c : /a/b
     * /a/b/c/d/ : /a/b/c
     * abc : .
     * // : /
     * / : /
     */
    static std::string getShellDirName(const std::string& path);

    /*
     * get the basename from the input string path, 
     * no fs operation is taken. notice that the api is
     * the same with the shell command "basename"
     *
     * input : output
     * empty : empty
     * /a/b/c : c
     * /a/b/c/d/ : d
     * abc : abc
     * // : /
     * / : /
     */
    static std::string getShellBaseName(const std::string& path);

    /*
     * get the ext name, which is after "."
     *
     * input : output
     * a/b/c.txt : txt
     * a/b.cc/a : empty
     * empty:empty
     * abc : empty
     * abc. : empty
     */
    static std::string getFileExtName(const std::string& path);

    /*
     * get a well-formed path, and remove the multi "//", ".", and ".." 
     *
     * input:output
     * ../ : /a
     * empty : empty
     * ./a/../b/c : b/c
     * /a/b//c/.. : /a/b
     */
    static std::string getNormalizePath(const std::string& path);

    /*
     *  split every level of path into a vector
     * input : output
     * /a/b/c/d : [a,b,c,d]
     * empty: []
     * //a/ : [a]
     * ./a/../b : [.,a,..,b]
     */
    static Strings splitPath(const std::string& path);

    /*
     * merge every level of path into a string
     * [a,b,c,d] : a/b/c/d
     * [] : empty
     * [/,a,b] : /a/b
     */
    static std::string joinPath(const Strings &svec);

    /*
     * merge every level of path into a string
     * [a,b,c,d] : a/b/c/d
     * [] : empty
     * [/,a,b] : /a/b
     */
    static std::string joinPath(size_t argc, ...);

    /*
     * get current dir
     */
    static MCResult<std::string> getCurrentDir();

    /*
     * for a relative path : get current path, add to "path",and get a well-formed one
     * for a absolutely path : re-forme it
     *
     * input : output
     * /aa/b//c/.. : /aa/b
     * ../a/b/./c/ : /0/a/b/c  (current path : /0/1)
     * empty : empty
     */
    static MCResult<std::string> getAbsPath(const std::string& path);

    /*
     * similar with getNormalizePath,
     * but add an addition action : follow symbol link
     */ 
    static MCResult<std::string> getRealPath(const std::string& path);

    /*
     * following method are all based on system call (access)
     */
    static MCResult<bool> exist(const std::string& path);
    static MCResult<bool> readable(const std::string& path);
    static MCResult<bool> writable(const std::string& path);
    static MCResult<bool> executable(const std::string& path);

    /*
     * following method are all based on system call (stat)
     */
    static MCResult<bool> isDir(const std::string& path);
    static MCResult<bool> isFile(const std::string& path);
    static MCResult<bool> isSoftLink(const std::string& path);
    static MCResult<bool> isSocketFile(const std::string& path);
    static MCResult<size_t> size(const std::string& path);
    static MCResult<time_t> aTime(const std::string& path);
    static MCResult<time_t> mTime(const std::string& path);
    static MCResult<time_t> cTime(const std::string& path);

    /*
     * list files under a dir
     */
//    static bool listFile(const std::string& path, Strings& fileVec);
//    static bool listAll(const std::string& path, Strings& retVec, bool bDir = false);

    /*
     * cp,mv,del,mkdir
     */
    static bool unlink(const std::string& path);
    static bool move(const std::string& src, const std::string &dest, bool isOverride = true);
    static bool makeDirs(const std::string& path, bool subDir = true);
    static bool copyFile(const std::string& src, const std::string &dest, bool isOverride = true);


    /*
     * read and write file
     */
    static MCResult<Strings> getLines(const std::string& path);
    static MCResult<std::string> loadFromFile(const std::string& path);
    static MCResult<bool> writeToFile(const std::string& path, const std::string& content);
    static MCResult<bool> writeToFile(const std::string& path, const char *data, size_t size);
    static MCResult<bool> appendToFile(const std::string& path, const std::string& content);
    static MCResult<bool> appendToFile(const std::string& path, const char *data, size_t size);
};

MESSI_NAMESPACE_END

#endif // MESSI_COMMON_FSUTIL_H
