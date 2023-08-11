#define APPLEWIDTH 12
#define APPLEHEIGHT 13

typedef struct
{
  u16 *bitmap;
  int x;
  int y;
  int width;
  int height;
  int active;
} APPLE;

extern APPLE apple;

// function prototypes
void initializeApple();
void drawApple(int x, int y, APPLE *apple_ptr);