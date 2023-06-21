#ifndef B9649648_48CE_4E49_8459_7F551C3A8F02
#define B9649648_48CE_4E49_8459_7F551C3A8F02

#include <allegro5/allegro5.h>
#include <vector>
#include <string>
#include <iostream>

class ShaderManager
{
private:    
    std::vector<std::pair<std::string, ALLEGRO_SHADER*>> BuiltShaders;
public:
    ShaderManager();
    ~ShaderManager();
    bool LoadShader(std::string name, std::string path, ALLEGRO_SHADER_PLATFORM allegro_shader_platform, ALLEGRO_SHADER_TYPE allgero_shader_type);
    ALLEGRO_SHADER *GetShader(std::string name);
};


#endif /* B9649648_48CE_4E49_8459_7F551C3A8F02 */
