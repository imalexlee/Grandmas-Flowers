#define HEARTWIDTH 13
#define HEARTHEIGHT 11
#define HEARTCOUNT 3

typedef struct
{
  int x;
  int y;
  int oldx;
  int oldy;
  u16 *bitmap;
  int active;
} HEART;

extern HEART hearts[HEARTCOUNT];
extern u16 *heartBitmaps[HEARTCOUNT];

// function prototypes
void initializeHearts();
void drawHeart(int x, int y, HEART *heart_ptr);