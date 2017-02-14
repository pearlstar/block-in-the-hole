#include "headerFile.h"

bool gridMatrix[10][10] = {
  {1,1,1,1,1,0,1,1,0,0},
  {0,0,0,1,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,0,0,0,0,0},
  {0,0,0,1,1,1,1,0,0,0},
  {0,0,0,0,0,1,1,0,0,0},
  {0,0,0,1,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0,0,0}
};

void createTile (float angle, float x, float y, float z, float height, float width, float depth, COLOR color, COLOR color2, COLOR color3, COLOR color4) {
  float w=width/2,h=height/2,d=depth/2;
  static const GLfloat vertex_buffer_data [] = {
    -w, h, d,
    -w, -h, d,
    w, -h, d,
    -w, h, d,
    w, -h, d,
    w, h, d,
    w, h, d,
    w, -h, d,
    w, -h, -d,
    w, h, d,
    w, -h, -d,
    w, h, -d,
    w, h, -d,
    w, -h, -d,
    -w, -h, -d,
    w, h, -d,
    -w, -h, -d,
    -w, h, -d,
    -w, h, -d,
    -w, -h, -d,
    -w, -h, d,
    -w, h, -d,
    -w, -h, d,
    -w, h, d,
    -w, h, -d,
    -w, h, d,
    w, h, d,
    -w, h, -d,
    w, h, d,
    w, h, -d,
    -w, -h, d,
    -w, -h, -d,
    w, -h, -d,
    -w, -h, d,
    w, -h, -d,
    w, -h, d,
    -w, h, d,
    w, h, -d,
    w, h, -d,
  };

  GLfloat color_buffer_data [] = {
    color4.r,color4.g,color4.b, // color 1
    color4.r,color4.g,color4.b, // color 2
    color4.r,color4.g,color4.b, // color 3

    color4.r,color4.g,color4.b, // color 4
    color4.r,color4.g,color4.b, // color 5
    color4.r,color4.g,color4.b, // color 6

    color4.r,color4.g,color4.b, // color 1
    color4.r,color4.g,color4.b, // color 2
    color4.r,color4.g,color4.b, // color 3

    color4.r,color4.g,color4.b, // color 4
    color4.r,color4.g,color4.b, // color 5
    color4.r,color4.g,color4.b, // color 6

    color4.r,color4.g,color4.b, // color 1
    color4.r,color4.g,color4.b, // color 2
    color4.r,color4.g,color4.b, // color 3

    color4.r,color4.g,color4.b, // color 4
    color4.r,color4.g,color4.b, // color 5
    color4.r,color4.g,color4.b, // color 6

    color4.r,color4.g,color4.b, // color 1
    color4.r,color4.g,color4.b, // color 2
    color4.r,color4.g,color4.b, // color 3

    color4.r,color4.g,color4.b, // color 4
    color4.r,color4.g,color4.b, // color 5
    color4.r,color4.g,color4.b, // color 6

    color.r,color.g,color.b, // color 1
    color2.r,color2.g,color2.b, // color 2
    color3.r,color3.g,color3.b, // color 3

    color3.r,color3.g,color3.b, // color 4
    color4.r,color4.g,color4.b, // color 5
    color.r,color.g,color.b, // color 6

    color.r,color.g,color.b, // color 1
    color2.r,color2.g,color2.b, // color 2
    color3.r,color3.g,color3.b, // color 3

    color3.r,color3.g,color3.b, // color 4
    color4.r,color4.g,color4.b, // color 5
    color.r,color.g,color.b, // color 6
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  VAO *object = create3DObject(GL_TRIANGLES, 13*3, vertex_buffer_data, color_buffer_data, GL_FILL);
  ENTITY tile = {};
  tile.x = x;
  tile.y = y;
  tile.z = z;
  tile.height = height;
  tile.width = width;
  tile.depth = depth;
  tile.object = object;
  tile.state = 0;
  Tile.push_back(tile);
}

void gridEngine() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (gridMatrix[i][j]) {
        if ((i+j)%2) createTile(0, 2*(i-3), 0, 2*(j-3), 1, 2, 2, brown1, darkbrown, brown1, darkbrown);
        else createTile(0, 2*(i-3), 0, 2*(j-3), 1, 2, 2, brown2, lightbrown, brown2, lightbrown);
      }
    }
  }
}

int isEnd() {
  int i, i1, i2, j, j1, j2;
  switch (cuboid.orientation) {
    case 'x':
    i1 = (cuboid.x - cuboid.height/4.0)/2.0 + 3.0;
    i2 = (cuboid.x + cuboid.height/4.0)/2.0 + 3.0;
    j = cuboid.z/2.0 + 3.0;
    if (i1 < 0 || i2 < 0 || j < 0 || (!gridMatrix[i1][j] && !gridMatrix[i2][j])) return 1;
    break;
    case 'y':
    i = cuboid.x/2.0 + 3.0;
    j = cuboid.z/2.0 + 3.0;
    if (!gridMatrix[i][j]) return 1;
    break;
    case 'z':
    i = cuboid.x/2.0 + 3.0;
    j1 = (cuboid.z - cuboid.height/4.0)/2.0 + 3.0;
    j2 = (cuboid.z + cuboid.height/4.0)/2.0 + 3.0;
    if (i < 0 || j1 < 0 || j2 < 0 || (!gridMatrix[i][j1] && !gridMatrix[i][j2])) return 1;
    break;
    default:
    break;
  }
  return 0;
}
