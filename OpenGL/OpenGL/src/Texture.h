#pragma once

class Texture
{
public:
	Texture() noexcept;

	void use_texture_unit(int texture_unit) const;
	void load_texture_jpg(const char* texturePath = nullptr) const;
	void load_texture_png(const char* texturePath = nullptr) const;
	void set_params() const;
	void bind() const;
private:
	unsigned int texture;
};