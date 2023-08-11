#define FLOWERWIDTH 7
#define FLOWERHEIGHT 14
#define FLOWERCOUNT 5

typedef struct
{
  int x;
  int y;
  int oldx;
  int oldy;
  u16 *bitmap;
  int active;
} FLOWER;

extern FLOWER flowers[FLOWERCOUNT];
extern u16 *flowerBitmaps[FLOWERCOUNT];

// prototypes
void initializeFlowers();
void drawFlower(int x, int y, FLOWER *flower_ptr);