#ifndef B6B1A21D_2C15_4A2B_A64D_2177BECF26C1
#define B6B1A21D_2C15_4A2B_A64D_2177BECF26C1

#include "../STD_DefaultInclude.hpp"
#include "../ALLEGRO_DefaultInclude.hpp"

class ShaderManager
{
private:    
    static inline std::map<std::string, ALLEGRO_SHADER*> built_shaders {};
public:
    ShaderManager(){};
    ~ShaderManager();
    static bool LoadShader(std::string name, std::string path, ALLEGRO_SHADER_PLATFORM allegro_shader_platform, ALLEGRO_SHADER_TYPE allgero_shader_type);
    static ALLEGRO_SHADER *GetShader(std::string name);
};


#endif /* B6B1A21D_2C15_4A2B_A64D_2177BECF26C1 */
