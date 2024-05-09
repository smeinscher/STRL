//
// Created by Sterling on 2/8/2024.
//

#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include <string>

namespace strl
{

class OpenGLTexture
{
  public:
    OpenGLTexture();
    OpenGLTexture(int internal_format, int image_format, int wrap_s, int wrap_t, int filter_min, int filter_max);

    [[nodiscard]] unsigned int get_id() const;

    bool generate(const std::string &path);

    void bind() const;

    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;

  private:
    int width_{};
    int height_{};

    unsigned int id_{};

    int internal_format_;
    int image_format_;

    int wrap_s_;
    int wrap_t_;
    int filter_min_;
    int filter_max_;
};

} // namespace strl

#endif // OPENGLTEXTURE_H
