#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <surfaces/surface.hpp>
#include <SDL.h>
#include <string>

struct Image : public Surface {
  Image(const std::string& path);
};

#endif // IMAGE_HPP
