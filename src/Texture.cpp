#include <Vonsai/Texture.hpp>
#include <Vonsai/Utils/Files.hpp>
#include <Vonsai/Wraps/_gl.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Vonsai {

void Texture::bind() const {
  GL_ASSERT(glActiveTexture(GL_TEXTURE0 + ID));
  GL_ASSERT(glBindTexture(GL_TEXTURE_2D, ID));
}
void Texture::unbind() const {
  GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
  GL_ASSERT(glActiveTexture(GL_TEXTURE0));
}

Texture::Texture(char const *path) {
  if (!Files::isValid(path, true)) { return; }

  // Parse image data
  auto pixels = stbi_load(path, &width, &height, &bytes, 4);

  if (!pixels) {
    vo_err("Failed loading texture: {}", path);
    return;
  }

  // Create opengl resource
  GL_ASSERT(glGenTextures(1, &ID));
  BindGuard bg{*this};

  // Attach image data to the texture
  GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels));

  // Free the pixels resource
  stbi_image_free(pixels);

  // MipMap generation and texture parameters
  GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
  GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);)
  GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);)
  GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);)
  GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);)
}

} // namespace Vonsai
