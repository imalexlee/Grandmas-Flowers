#define PLAYERWIDTH 14
#define PLAYERHEIGHT 16

typedef struct
{
  u16 *bitmap;
  int x;
  int y;
  int oldx;
  int oldy;
  int xVelocity;
  int yVelocity;
  int width;
  int height;
} PLAYER;

extern PLAYER player;

// function prototypes
void initializePlayer();
void drawPlayer(int x, int y, PLAYER *player_ptr);