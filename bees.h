#define BEEWIDTH 11
#define BEEHEIGHT 10
#define BEECOUNT 1

typedef struct
{
  int x;
  int y;
  int oldx;
  int oldy;
  u16 *bitmap;
} BEE;

extern BEE bees[BEECOUNT];
extern u16 *beeBitmaps[BEECOUNT];

// function prototypes
void initializeBees();
void drawBee(int x, int y, BEE *bee_ptr);