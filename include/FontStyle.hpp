#ifndef INCLUDE_FONTSTYLE_HPP_
#define INCLUDE_FONTSTYLE_HPP_

#include <SDL2/SDL_ttf.h>
#include <string>

enum class FontRenderMode {
  Blended, // Should rendered by TTF_RenderUTF8_Blended_Wrapped
  LCD, // Should rendered by TTF_RenderUTF8_LCD_Wrapped
  Shaded, // Should rendered by TTF_RenderUTF8_Shaded_Wrapped
  Solid, // Should rendered by TTF_RenderUTF8_Solid_Wrapped
};

struct FontStyle {
  std::string source; // path to .ttf file
  FontRenderMode render_mode{ FontRenderMode::Blended };
  SDL_Color fg;
  SDL_Color bg;
  int size{ 16 };
  int outline{ 0 };
  int align{ TTF_WRAPPED_ALIGN_LEFT }; // See https://wiki.libsdl.org/SDL2_ttf/TTF_SetFontWrappedAlign
  int style{ TTF_STYLE_NORMAL }; // See https://wiki.libsdl.org/SDL2_ttf/TTF_SetFontStyle
  uint32_t wrap_length{ 0 }; // 0: only wrap on newline characters.
};

#endif  // INCLUDE_FONTSTYLE_HPP_
