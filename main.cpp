#include "headerFile.h"

struct GLMatrices {
  glm::mat4 projection;
  glm::mat4 model;
  glm::mat4 view;
  GLuint MatrixID;
} Matrices;

vector <ENTITY> Tile;
ENTITY cuboid;
int bridge1_i = 3;
int bridge1_j = 3;
int bridge2_i = 4;
int bridge2_j = 3;
int switch_i = 2;
int switch_j = 3;
int victory_i = 7;
int victory_j = 3;
vector <pair<int, int> > fragile_tiles;
map <string, ENTITY> Led;

float eye_x,eye_y,eye_z;
float target_x,target_y,target_z;
int camera_follow=0;
int camera_follow_adjust=0;
// int camera_top=0;
// int camera_fps=0;
float camera_radius;
float camera_fov=1.3;
float fps_head_offset=0;
float fps_head_offset_x=0;
// int tower=1;
int helicopter=0;
int camera_self=0;
int orient_right=0;
int orient_left=0;
int orient_forward=0;
int orient_backward=0;
int mouse_click=0,right_mouse_click=0;
int keyboard_press=0;
double mouse_pos_x, mouse_pos_y;
double prev_mouse_pos_x,prev_mouse_pos_y;
int roundi=0;
int partition=0;

COLOR grey = {168.0/255.0,168.0/255.0,168.0/255.0};
COLOR silver = {192.0/255.0,192.0/255.0,192.0/255.0};
COLOR sun = {233.0/255.0,189.0/255.0,21.0/255.0};
COLOR gold = {218.0/255.0,165.0/255.0,32.0/255.0};
COLOR coingold = {255.0/255.0,223.0/255.0,0.0/255.0};
COLOR red = {255.0/255.0,51.0/255.0,51.0/255.0};
COLOR lightgreen = {57/255.0,230/255.0,0/255.0};
COLOR darkgreen = {51/255.0,102/255.0,0/255.0};
COLOR black = {30/255.0,30/255.0,21/255.0};
COLOR blue = {0,0,1};
COLOR darkbrown = {46/255.0,46/255.0,31/255.0};
COLOR lightbrown = {95/255.0,63/255.0,32/255.0};
COLOR brown1 = {117/255.0,78/255.0,40/255.0};
COLOR brown2 = {134/255.0,89/255.0,40/255.0};
COLOR brown3 = {46/255.0,46/255.0,31/255.0};
COLOR cratebrown = {153/255.0,102/255.0,0/255.0};
COLOR cratebrown1 = {121/255.0,85/255.0,0/255.0};
COLOR cratebrown2 = {102/255.0,68/255.0,0/255.0};
COLOR skyblue2 = {113/255.0,185/255.0,209/255.0};
COLOR skyblue1 = {123/255.0,201/255.0,227/255.0};
COLOR skyblue = {132/255.0,217/255.0,245/255.0};
COLOR cloudwhite = {229/255.0,255/255.0,255/255.0};
COLOR cloudwhite1 = {204/255.0,255/255.0,255/255.0};
COLOR lightpink = {255/255.0,122/255.0,173/255.0};
COLOR darkpink = {255/255.0,51/255.0,119/255.0};
COLOR white = {255/255.0,255/255.0,255/255.0};
COLOR scorecolor = {117/255.0,78/255.0,40/255.0};

int do_rot, floor_rel;
GLuint programID;
double last_update_time, current_time;
glm::vec3 rect_pos, floor_pos;

/**************************
* Customizable functions *
**************************/

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods) {
  // Function is called first on GLFW_PRESS.

  if (action == GLFW_RELEASE) {
    switch (key) {
      case GLFW_KEY_LEFT:
      cuboid.x_rotation_status = 1;
      cuboid.x_rotation_angle = -90;
      break;
      case GLFW_KEY_RIGHT:
      cuboid.x_rotation_status = 1;
      cuboid.x_rotation_angle = 90;
      break;
      case GLFW_KEY_UP:
      cuboid.z_rotation_status = 1;
      cuboid.z_rotation_angle = -90;
      break;
      case GLFW_KEY_DOWN:
      cuboid.z_rotation_status = 1;
      cuboid.z_rotation_angle = 90;
      break;
      case GLFW_KEY_C:
      break;
      case GLFW_KEY_X:
      // do something ..
      break;
      case GLFW_KEY_T:
      camera_follow=0;
      camera_self=0;
      helicopter=0;
      eye_x = 0+cos(45*M_PI/180);
      eye_z = 0;
      eye_y=20;
      target_x=0;
      target_y=0;
      target_z=0;
      break;
      case GLFW_KEY_R:
      camera_follow=0;
      camera_self=0;
      helicopter=0;
      eye_x = 0 ,
      eye_y = 12;
      eye_z = 15;
      target_z = 0;
      target_y = 0;
      target_x = 0;
      break;
      case GLFW_KEY_F:
      camera_follow=1;
      camera_self=0;
      helicopter=0;
      break;
      case GLFW_KEY_P:
      camera_follow=0;
      camera_self=0;
      helicopter=1;
      break;
      case GLFW_KEY_I:
      camera_follow=0;
      camera_self=1;
      helicopter=0;
      break;
      default:
      break;
    }
  }
  else if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
      quit(window);
      break;
      default:
      break;
    }
  }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key) {
  switch (key) {
    case 'Q':
    case 'q':
    quit(window);
    break;
    case 'a':
    if(camera_follow==1 || camera_self==1) {
      eye_x = cuboid.x-((camera_follow) ? 5 : 3);
      eye_y = cuboid.y;
      eye_z = cuboid.z;
      target_x = 1000;
      target_y = cuboid.y;
      target_z = cuboid.z;
    }
    break;
    case 'd':
    if(camera_follow==1 ||  camera_self==1) {
      eye_x = cuboid.x+((camera_follow) ? 5 : 3);
      eye_y = cuboid.y;
      eye_z = cuboid.z;
      target_x = -1000;
      target_y = cuboid.y;
      target_z = cuboid.z;
    }
    break;
    case 'w':
    if(camera_follow==1 ||camera_self==1) {
      eye_x = cuboid.x;
      eye_y = cuboid.y;
      eye_z = cuboid.z-((camera_follow) ? 5 : 3);
      target_x = cuboid.x;
      target_y = cuboid.y;
      target_z = 1000;
    }
    break;
    case 's':
    if(camera_follow==1 || camera_self==1) {
      eye_x = cuboid.x;
      eye_y = cuboid.y;
      eye_z = cuboid.z+((camera_follow) ? 5 : 3);
      target_x = cuboid.x;
      target_y = cuboid.y;
      target_z = -1000;
    }
    break;
    case 'r':
    rect_pos.z -= 0.1;
    break;
    case 'f':
    rect_pos.z += 0.1;
    break;
    case 'e':
    break;
    case 'j':
    floor_pos.x -= 0.1;
    break;
    case 'l':
    floor_pos.x += 0.1;
    break;
    case 'i':
    floor_pos.y += 0.1;
    break;
    case 'k':
    floor_pos.y -= 0.1;
    break;
    case 'y':
    floor_pos.z -= 0.1;
    break;
    case 'h':
    floor_pos.z += 0.1;
    break;
    case 'g':
    floor_rel ^= 1;
    break;
    case ' ':
    do_rot ^= 1;
    break;
    default:
    break;
  }
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods) {
  switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
    if(action == GLFW_PRESS) {
      mouse_click=1;
      keyboard_press=0;
      right_mouse_click=0;
    }
    if(action == GLFW_RELEASE) mouse_click=0;
    break;
    case GLFW_MOUSE_BUTTON_RIGHT:
    if(action == GLFW_PRESS) {
      right_mouse_click=1;
      keyboard_press=0;
      mouse_click=0;
    }
    if(action == GLFW_RELEASE) right_mouse_click=0;
    break;
    default:
    break;
  }
}

/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
  int fbwidth=width, fbheight=height;
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);

  GLfloat fov = M_PI/2;

  // sets the viewport of openGL renderer
  glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

  // Store the projection matrix in a variable for future use
  // Perspective projection for 3D views
  Matrices.projection = glm::perspective(fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

  // Ortho projection for 2D views
  //Matrices.projection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 0.1f, 500.0f);
}

float camera_rotation_angle = 90;
float angle;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw (GLFWwindow* window, int doM, int doV, int doP)
{
  glUseProgram(programID);
  glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
  if(helicopter==1) {
    if(mouse_click==1) {
      angle=(mouse_pos_x)*360/600;
      eye_x = 20*cos(angle*M_PI/180);
      eye_z = 20*sin(angle*M_PI/180);
      target_x = 0;
      target_z = 0;
      target_y = 0;
    }
    if(right_mouse_click==1) {
      angle = 90-(mouse_pos_y)*90/600;
      eye_y = 20*sin(angle*M_PI/180);
      target_x = 0;
      target_z = 0;
      target_y = 0;
    }
  }
  prev_mouse_pos_x = mouse_pos_x;
  prev_mouse_pos_y = mouse_pos_y;
  if(camera_self==0 && camera_follow==0) {
    orient_forward=1;
    orient_right=0;
    orient_left=0;
    orient_backward=0;
  }
  glm::vec3 eye(eye_x,eye_y,eye_z);
  //glm::vec3 eye ( 8*sin(camera_rotation_angle*M_PI/180.0f), 3, 8*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (target_x,target_y,target_z);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
  if(doV)
  Matrices.view = glm::lookAt(eye, target, up); // Fixed camera for 2D (ortho) in XY plane
  else
  Matrices.view = glm::mat4(1.0f);

  // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
  glm::mat4 VP;
  if (doP) VP = Matrices.projection * Matrices.view;
  else VP = Matrices.view;

  // Send our transformation to the currently bound shader, in the "MVP" uniform
  // For each model you render, since the MVP will be different (at least the M part)
  glm::mat4 MVP;	// MVP = Projection * View * Model

  for (auto i = Tile.begin(); i != Tile.end(); i++) {
    if (!i->state) continue;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translateObject = glm::translate(glm::vec3(i->x, i->y, i->z));
    Matrices.model *= translateObject;
    if(doM) MVP = VP * Matrices.model;
    else MVP = VP;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(i->object);
  }

  Matrices.model = glm::mat4(1.0f);
  glm::mat4 translateObject = glm::translate(glm::vec3(cuboid.x, cuboid.y, cuboid.z));
  glm::mat4 rotateObject;
  glm::mat4 rotateObject2;
  switch (cuboid.orientation) {
    case 'x':
    rotateObject = glm::rotate((float)(cuboid.x_angle*M_PI/180.0f), glm::vec3(0,0,1));
    if (cuboid.prev_orientation == 'x') {
      rotateObject2 = glm::rotate((float)(cuboid.z_angle*M_PI/180.0f), glm::vec3(1,0,0));
      Matrices.model *= translateObject*rotateObject2*rotateObject;
    } else Matrices.model *= translateObject*rotateObject;
    break;
    case 'z':
    rotateObject = glm::rotate((float)(cuboid.z_angle*M_PI/180.0f), glm::vec3(1,0,0));
    if (cuboid.prev_orientation == 'z') {
      rotateObject2 = glm::rotate((float)(cuboid.x_angle*M_PI/180.0f), glm::vec3(0,0,1));
      Matrices.model *= translateObject*rotateObject2*rotateObject;
    } else Matrices.model *= translateObject*rotateObject;
    break;
    default:
    Matrices.model *= translateObject;
    break;
  }
  // glm::mat4 rotateObject2 = glm::rotate((float)(cuboid.z_angle*M_PI/180.0f), glm::vec3(1,0,0));
  // glm::mat4 rotateObject = glm::rotate((float)(cuboid.x_angle*M_PI/180.0f), glm::vec3(0,0,1));
  // Matrices.model *= translateObject*rotateObject;
  // if (cuboid.state) Matrices.model *= translateObject*rotateObject1*rotateObject2;
  // else Matrices.model *= translateObject*rotateObject2*rotateObject1;
  if(doM) MVP = VP * Matrices.model;
  else MVP = VP;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(cuboid.object);

  if (cuboid.orientation == 'y') {
    if (cuboid.x_rotation_status) {
      cuboid.x_angle = (cuboid.x_rotation_angle > 0) ? 90 : -90;//int(cuboid.x_angle + cuboid.x_rotation_angle) % 360;
      cuboid.x += ((cuboid.x_rotation_angle > 0) ? 1 : -1)*(cuboid.height + cuboid.width)/2.0 ;
      cuboid.y = 0.5 + cuboid.width/2.0;
      cuboid.x_rotation_status = 0;
      cuboid.orientation = 'x';
      cuboid.prev_orientation = 'y';
      // cout << " | " << cuboid.x/2+3 << " | " << cuboid.z/2+3 << endl;
      checkSwitch();
      // cuboid.state = 0;
      cout << "state:" << cuboid.orientation << " | " << cuboid.x_angle << " | " << cuboid.z_angle << endl;
    }
    if (cuboid.z_rotation_status) {
      cuboid.z_angle = (cuboid.z_rotation_angle> 0) ? 90 : -90;//int(cuboid.z_angle + cuboid.z_rotation_angle) % 360;
      cuboid.z += ((cuboid.z_rotation_angle > 0) ? 1 : -1)*(cuboid.height + cuboid.width)/2.0;
      cuboid.y = 0.5 + cuboid.depth/2.0;
      cuboid.z_rotation_status = 0;
      cuboid.orientation = 'z';
      cuboid.prev_orientation = 'y';
      // cout << " | " << cuboid.x/2+3 << " | " << cuboid.z/2+3 << endl;
      checkSwitch();
      // cuboid.state = 1;
      cout << "state:" << cuboid.orientation << " | " << cuboid.x_angle << " | " << cuboid.z_angle << endl;
    }
  } else if (cuboid.orientation == 'x') {
    if (cuboid.x_rotation_status) {
      cuboid.x_angle = int(cuboid.x_angle + cuboid.x_rotation_angle) % 360;
      cuboid.x += ((cuboid.x_rotation_angle > 0) ? 1 : -1)*(cuboid.height + cuboid.width)/2.0;
      cuboid.y = 0.5 + cuboid.height/2.0;
      cuboid.x_rotation_status = 0;
      cuboid.orientation = 'y';
      cuboid.transition = 'y';
      cuboid.prev_orientation= 'x';
      checkSwitch();
      // cuboid.state = 1;
      cout << "state:" << cuboid.orientation << " | " << cuboid.x_angle << " | " << cuboid.z_angle << endl;
    }
    if (cuboid.z_rotation_status) {
      cuboid.z_angle = int(cuboid.z_angle + cuboid.z_rotation_angle) % 360;
      cuboid.z += ((cuboid.z_rotation_angle > 0) ? 1 : -1)*cuboid.depth;
      cuboid.z_rotation_status = 0;
      cuboid.prev_orientation = 'x';
      checkSwitch();
      // cuboid.state = 1;
      cout << "state:" << cuboid.orientation << " | " << cuboid.x_angle << " | " << cuboid.z_angle << endl;
    }
  } else {
    if (cuboid.x_rotation_status) {
      cuboid.x_angle = int(cuboid.x_angle + cuboid.x_rotation_angle) % 360;
      cuboid.x += ((cuboid.x_rotation_angle > 0) ? 1 : -1)*cuboid.width;
      cuboid.x_rotation_status = 0;
      cuboid.prev_orientation = 'z';
      checkSwitch();
      // cuboid.state = 0;
      cout << "state:" << cuboid.orientation << " | " << cuboid.x_angle << " | " << cuboid.z_angle << endl;
    }
    if (cuboid.z_rotation_status) {
      cuboid.z_angle = int(cuboid.z_angle + cuboid.z_rotation_angle) % 360;
      cuboid.z += ((cuboid.z_rotation_angle > 0) ? 1 : -1)*(cuboid.height + cuboid.depth)/2.0;
      cuboid.y = 0.5 + cuboid.height/2.0;
      cuboid.z_rotation_status = 0;
      cuboid.orientation = 'y';
      cuboid.transition = 'y';
      cuboid.prev_orientation = 'z';
      checkSwitch();
      // cuboid.state = 0;
      cout << "state:" << cuboid.orientation << " | " << cuboid.x_angle << " | " << cuboid.z_angle << endl;
    }
  }
  if (checkVictory()) {
    cout << "congo!!!! You Won!!!\n";
    quit(window);
  }
  if (isEnd()) quit(window);
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height){
  GLFWwindow* window; // window desciptor/handle

  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

  if (!window) {
    exit(EXIT_FAILURE);
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);
  //    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval( 1 );
  glfwSetFramebufferSizeCallback(window, reshapeWindow);
  glfwSetWindowSizeCallback(window, reshapeWindow);
  glfwSetWindowCloseCallback(window, quit);
  glfwSetKeyCallback(window, keyboard);      // general keyboard input
  glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling
  glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks

  return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
  /* Objects should be created before any other gl function and shaders */
  // Create the models

  // Create and compile our GLSL program from the shaders
  programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
  // Get a handle for our "MVP" uniform
  Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

  gridEngine();
  cuboidEngine();

  reshapeWindow (window, width, height);

  // Background color of the scene
  glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
  glClearDepth (1.0f);

  eye_x = 0 ,
  eye_y = 12;
  eye_z = 15;
  target_z = 0;
  target_y = 0;
  target_x = 0;

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);

  // cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
  // cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
  // cout << "VERSION: " << glGetString(GL_VERSION) << endl;
  // cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main (int argc, char** argv)
{
  ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
		printf("Could not startup engine\n");
	}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped
	engine->play2D("irrKlang-64bit-1.5.0/media/welcome2.wav", false);

  int width = 600;
  int height = 600;
  rect_pos = glm::vec3(0, 0, 0);
  floor_pos = glm::vec3(0, 0, 0);
  do_rot = 0;
  floor_rel = 1;

  GLFWwindow* window = initGLFW(width, height);
  initGLEW();
  initGL (window, width, height);

  last_update_time = glfwGetTime();
  /* Draw in loop */
  while (!glfwWindowShouldClose(window)) {

    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // OpenGL Draw commands
    current_time = glfwGetTime();
    // if(do_rot)
    // camera_rotation_angle += 90*(current_time - last_update_time); // Simulating camera rotation
    // if(camera_rotation_angle > 720)
    // camera_rotation_angle -= 720;
    last_update_time = current_time;
    draw(window, 1, 1, 1);
    // draw(window, 0.5, 0, 0.5, 0.5, 0, 1, 1);
    // draw(window, 0, 0.5, 0.5, 0.5, 1, 0, 1);
    // draw(window, 0.5, 0.5, 0.5, 0.5, 0, 0, 1);

    // Swap Frame Buffer in double buffering
    glfwSwapBuffers(window);

    // Poll for Keyboard and mouse events
    glfwPollEvents();
  }

  glfwTerminate();
  //    exit(EXIT_SUCCESS);
}
