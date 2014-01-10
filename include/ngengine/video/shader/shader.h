#ifndef NATIV_GAMES_ENGINE_VIDEO_SHADER_SHADER_H
#define NATIV_GAMES_ENGINE_VIDEO_SHADER_SHADER_H

#include <string>
#include <ngengine/video/opengl/opengl.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nge {
namespace video {
namespace shader {

  class Shader {
    public:

      Shader();
      Shader(std::string vertex_source, std::string fragment_source); // filenames
      ~Shader();

      bool compile();

      GLuint get_id();

      void set_matrix(glm::mat4 *projection, glm::mat4 *modelview);
      void update_matrix(); // envoie au shader opengl les matrices

    // public attributes

      std::string _vertex_source;
      std::string _fragment_source;

    private:

      bool compilerShader(GLuint &shader, GLenum type, std::string const &fichier_source);
      std::string read_file(std::string filename);

      
      GLuint _id; // program id
      GLuint _vertex_id;
      GLuint _fragment_id;
      glm::mat4 *_projection;
      glm::mat4 *_modelview;
  };

}
}
}

#endif

