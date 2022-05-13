#ifdef FT_DEBUG_TREE
#include <sstream>
#endif

...

#ifdef FT_DEBUG_TREE
        std::string to_string() {
            std::stringstream ss;
            ss << first << ": " << second;
            return ss.str();
        }
#endif
