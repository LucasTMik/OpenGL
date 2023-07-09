#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

static std::string ReadFileAsString(const std::string& filepath)
{
    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        result.resize((size_t)in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else
    {
        std::cout << "Could not open file '{0}'" << filepath << std::endl;
    }

    return result;
}

Shader::Shader(const std::string& filepath) : m_Filepath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(m_Filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

Shader* Shader::FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    Shader* shader = new Shader();
    shader->LoadFromGLSLTextFiles(vertexShaderPath, fragmentShaderPath);
    return shader;
}

void Shader::LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    std::string vertexSource = ReadFileAsString(vertexShaderPath);
    std::string fragmentSource = ReadFileAsString(fragmentShaderPath);

    GLuint program = glCreateProgram();
    int glShaderIDIndex = 0;

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    glAttachShader(program, vertexShader);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_RendererID = program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }


    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& pathname)
{
    std::ifstream stream(pathname);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return {
        ss[0].str(), ss[1].str()
    };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLint location = GetUniformLocation(name);
    GLCall(glUniform1i(location, value));
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
    GLint location = GetUniformLocation(name);
    GLCall(glUniform1f(location, v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLint location = GetUniformLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3))
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix)
{
    GLint location = GetUniformLocation(name);
    GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    m_UniformLocationCache[name] = location;
    return location;
}