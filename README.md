# Black Frame Insertion
This **LD_PRELOAD** library inserts black every other frame to reduce motion blur. Works with any OpenGL game uses glXSwapBuffers. The game may be darker and there may be flickering which could annoy some people. It is recommended that you increase backlight brightness , enable VSync and if possible use a 120+hz monitor to prevent flickering and dark images.

### Compiling and running
Compile using `gcc -Wall -fPIC -shared -o blackframe.so main.c -lGL -ldl` and run with `LD_PRELOAD=blackframe.so **GAMEEXECUTABLE**`. All games that use glXSwapBuffers are supported and EGL support is planned in the future. Since this game injects code into the game some anti-cheat software may get you banned.

## Contributing
Just submit a pull request or create an issue of whatever you want. If you are making a pull request be sure to keep the code looking clean and not messy.

If you think that this software is not garbage and has been useful to you then consider donating bitcoin to 
[1Curio6aUa7wQeekAChqoyGF6tB7fXpSZW](https://blockchain.info/payment_request?address=1Curio6aUa7wQeekAChqoyGF6tB7fXpSZW&message=donating+to+Curi0)
