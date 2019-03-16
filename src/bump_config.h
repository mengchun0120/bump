#ifndef INCLUDE_BUMP_CONFIG
#define INCLUDE_BUMP_CONFIG

#include <string>

namespace bump {

class Config {
public:
    enum ConfigValueType {
        TYPE_INT,
        TYPE_STRING,
        TYPE_DOUBLE
    };

    struct ConfigItem {
        const char* m_name;
        ConfigValueType m_type;
        void* m_mem;
        bool m_required;
        bool m_set;
    };

public:
    Config();

    ~Config();

    bool load(const char* fileName);

public:
    int m_width;
    int m_height;
    std::string m_bumpVertexShaderFile;
    std::string m_bumpFragShaderFile;
    std::string m_title;
};

} // end of namespace bump

#endif
