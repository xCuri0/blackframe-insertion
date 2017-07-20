# Black Frame Insertion
This **LD_PRELOAD** library inserts black every other frame to reduce motion blur. Works with any OpenGL game that doesn't use `glXGetProcAddress` to find `glXSwapBuffers`. The game may be darker and there may be flickering which could annoy some people. It is recommended that you increase backlight brightness , enable VSync and if possible use a 120+hz monitor to prevent flickering and dark images.

### Compiling and running
Compile using `gcc -Wall -fPIC -shared -o blackframe.so main.c -lGL -ldl` and run with `LD_PRELOAD=blackframe.so **GAMEEXECUTABLE**`. Some games such as *Minecraft , SuperTux and Neverball* do not work since they use `glXGetProcAddress`. I am currently working on this issue

## Contributing
Just submit a pull request or create an issue of whatever you want. If you are making a pull request be sure to keep the code looking clean and not messy.
