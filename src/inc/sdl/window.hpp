#ifndef window_h
#define window_h

#include <string>
#include <iostream>

#include "constants.hpp"

class Window {
 public:
  Window (int width, int height, const std::string &title);

  ~Window ();

  void Clear ();

  void swapBuffers ();
  SDL_Window *main;
  SDL_GLContext glContext;

  bool getClosed ()
  { return closed; };

 private:

  bool closed;
};

#endif
