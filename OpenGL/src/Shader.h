#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	// caching for uniforms
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(): m_RendererID(0) {};
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1iv(const std::string& name, unsigned int count, int samplers[]);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);

	static Shader* FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
private:
	void LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name) const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};