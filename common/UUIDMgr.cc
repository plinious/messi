#include "UUIDMgr.h"

#if ((defined ALL_USE_BOOST) || (defined UUID_USE_BOOST))
    // https://www.boost.org/doc/libs/1_67_0/libs/uuid/doc/uuid.html
    #include <boost/uuid/uuid.hpp>  
    #include <boost/uuid/uuid_generators.hpp>  
    #include <boost/uuid/uuid_io.hpp> 
#elif
    // https://linux.die.net/man/3/libuuid
    #include <uuid/uuid.h>
#endif

namespace messi {

    std::string UUIDMgr::generateUUID() {

#if ((defined ALL_USE_BOOST) || (defined UUID_USE_BOOST))
        // 使用boost uuid
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        return boost::lexical_cast<std::string>(uuid);
#elif 
        // 使用libuuid
        uuid_t u;
        uuid_generate(u);
        char s[36 + 1];
        std::string s;
        s.resize();
        uuid_unparse(u, s);
        return std::string(s, s + 36);
#endif
    }
}
