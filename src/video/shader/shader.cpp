#include <ngengine/video/shader/shader.h>
#include <iostream>
#include <fstream>

using namespace nge::video::shader;

Shader::Shader()
{
  _projection = nullptr;
  _modelview = nullptr;
  _id = 0;
}

Shader::~Shader()
{
  glDeleteShader(_vertex_id);
  glDeleteShader(_fragment_id);
  glDeleteProgram(_id);
}

bool Shader::load_files(std::string vertex_source, std::string fragment_source)
{
  bool ret;

  ret =  this->read_file(vertex_source, &_vertex_source);
  ret = ret && this->read_file(fragment_source, &_fragment_source);

  return ret;
}

bool Shader::compile()
{
  // Destruction d'un éventuel ancien Shader

  if(glIsShader(_vertex_id) == GL_TRUE)
    glDeleteShader(_vertex_id);

  if(glIsShader(_fragment_id) == GL_TRUE)
    glDeleteShader(_fragment_id);

  if(glIsProgram(_id) == GL_TRUE)
    glDeleteProgram(_id);


  // Compilation des shaders

  if(!compilerShader(_vertex_id, GL_VERTEX_SHADER, _vertex_source))
    return false;

  if(!compilerShader(_fragment_id, GL_FRAGMENT_SHADER, _fragment_source))
    return false;


  // Création du programme

  _id = glCreateProgram();


  // Association des shaders

  glAttachShader(_id, _vertex_id);
  glAttachShader(_id, _fragment_id);


  // Verrouillage des entrées shader

  glBindAttribLocation(_id, 0, "in_Vertex");
  glBindAttribLocation(_id, 1, "in_Color");
  glBindAttribLocation(_id, 2, "in_TexCoord0");


  // Linkage du programme

  glLinkProgram(_id);


  // Vérification du linkage

  GLint erreurLink(0);
  glGetProgramiv(_id, GL_LINK_STATUS, &erreurLink);


  // S'il y a eu une erreur

  if(erreurLink != GL_TRUE)
  {
    // Récupération de la taille de l'erreur

    GLint tailleErreur(0);
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &tailleErreur);


    // Allocation de mémoire

    char *erreur = new char[tailleErreur + 1];


    // Récupération de l'erreur

    glGetShaderInfoLog(_id, tailleErreur, &tailleErreur, erreur);
    erreur[tailleErreur] = '\0';


    // Affichage de l'erreur

    std::cout << erreur << std::endl;


    // Libération de la mémoire et retour du booléen false

    delete[] erreur;
    glDeleteProgram(_id);

    return false;
  }



  // Sinon c'est que tout s'est bien passé

  else
    return true;
}

bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &code_source)
{
  // shader's creation

  shader = glCreateShader(type);

  // shader's verification
  if(shader == 0)
  {
    std::cout << "Error, shader type (" << type << ") doesn't exist" << std::endl;
    return false;
  }

  // Récupération de la chaine C du code source

  const GLchar* chaineCode_source = code_source.c_str();


  // Envoi du code source au shader

  glShaderSource(shader, 1, &chaineCode_source, 0);


  // Compilation du shader

  glCompileShader(shader);


  // Vérification de la compilation

  GLint erreurCompilation(0);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);


  // S'il y a eu une erreur

  if(erreurCompilation != GL_TRUE)
  {
    // Récupération de la taille de l'erreur

    GLint tailleErreur(0);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);


    // Allocation de mémoire

    char *erreur = new char[tailleErreur + 1];


    // Récupération de l'erreur

    glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
    erreur[tailleErreur] = '\0';


    // Affichage de l'erreur

    std::cout << erreur << std::endl;


    // Libération de la mémoire et retour du booléen false

    delete[] erreur;
    glDeleteShader(shader);

    return false;
  }


  // Sinon c'est que tout s'est bien passé

  else
    return true;
}

GLuint Shader::get_id()
{
  return _id;
}

void Shader::set_matrix(glm::mat4 *projection, glm::mat4 *modelview)
{
  _projection = projection;
  _modelview = modelview;
}

void Shader::update_matrix()
{
  if(_modelview && _projection) {

    glUniformMatrix4fv(
      glGetUniformLocation(_id, "modelview"), 1, GL_FALSE, glm::value_ptr(*_modelview)
    );
    glUniformMatrix4fv(
      glGetUniformLocation(_id, "projection"), 1, GL_FALSE, glm::value_ptr(*_projection)
    );
  }
  else;
}

bool Shader::read_file(std::string filename, std::string *dest)
{
  bool ret = true;

  std::ifstream file(filename.c_str());

  if(!file) {
    std::cout << "Error file " << filename << " not present" << std::endl;
    ret = false;
  }
  else {
    *dest = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
  }

  return ret;
}

