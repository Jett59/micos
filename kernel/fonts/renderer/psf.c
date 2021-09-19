#include <display.h>
#include <fonts/renderer.h>

#define PSF_FONT_MAGIC 0x864ab572

typedef struct __attribute__((__packed__)) {
  u32_t magic;         /* magic bytes to identify PSF */
  u32_t version;       /* zero */
  u32_t header_size;   /* offset of bitmaps in file, 32 */
  u32_t flags;         /* 0 if there's no unicode table */
  u32_t number_glyphs; /* number of glyphs */
  u32_t glyph_bytes;   /* size of each glyph */
  u32_t height;        /* height in pixels */
  u32_t width;         /* width in pixels */
} psf_font_header;

extern psf_font_header font_start;

static u8_t* glyph_pointer;

void initialise_font() {
  if (font_start.magic == PSF_FONT_MAGIC) {
    glyph_pointer = ((u8_t*)&font_start) + font_start.header_size;
  }
}

void render_character(int x, int y, u32_t code_point, display_pixel foreground,
                      display_pixel background) {
  code_point = code_point < font_start.number_glyphs ? code_point : 0;
  u8_t* glyph = glyph_pointer + code_point * font_start.glyph_bytes - 1;
  int screen_offset_y = y * font_start.height;
  int screen_offset_x = x * (font_start.width + 1);
  int used_bytes = 0;
  for (int glyph_y = 0; glyph_y < font_start.height; glyph_y++) {
    for (int glyph_x = 0; glyph_x < font_start.width; glyph_x++) {
      if (glyph_x % 8 == 0) {
        glyph++;
        used_bytes++;
      }
      if ((*glyph) & (1 << (7 - (glyph_x % 8)))) {
        write_pixel(screen_offset_x + glyph_x, screen_offset_y + glyph_y,
                    foreground);
      } else {
        write_pixel(screen_offset_x + glyph_x, screen_offset_y + glyph_y,
                    background);
      }
    }
  }
}

int get_character_width() { return font_start.width; }
int get_character_height() { return font_start.height; }
