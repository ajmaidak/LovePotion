// This code is licensed under the MIT Open Source License.

// Copyright (c) 2015 Ruairidh Carmichael - ruairidhcarmichael@live.co.uk

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "shared.h"

char *rootDir = "game";

lua_State *L;

int initLove(lua_State *L);

int main() {

	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_requiref(L, "love", initLove, 1);

	sf2d_init(); // 2D Drawing lib.
	sftd_init(); // Text Drawing lib.

	sf2d_set_clear_color(RGBA8(0x0, 0x0, 0x0, 0xFF)); // Reset background color.

	consoleInit(GFX_TOP, NULL);

	luaL_dostring(L, "print(''); print('\x1b[1;36mLovePotion 0.1.0\x1b[0m (LOVE for 3DS)'); print('')"); // Ew again.

	luaL_dostring(L, "package.path = 'game/?.lua;game/?/init.lua'"); // Set default requiring path.
	luaL_dostring(L, "package.cpath = 'game/?.lua;game/?/init.lua'");

	if (luaL_dofile(L, "game/main.lua")) printf("Error: %s", lua_tostring(L,-1));

	if (luaL_dostring(L, "if love.load then love.load() end")) printf("Error: %s", lua_tostring(L,-1));

	while (aptMainLoop()) {

		if (shouldQuit == 1) break; // Quit event

		if (luaL_dostring(L,
			"love.keyboard.scan()\n"
			"love.timer.step()\n"
			"if love.update then love.update(love.timer.getDelta()) end")) {
				printf("\x1b[3;3HError: %s", lua_tostring(L,-1));
		}

		// sf2d_start_frame(GFX_TOP, GFX_LEFT);

		// 	if (luaL_dostring(L, "if love.draw then love.draw() end")) printf("\x1b[3;3HError: %s", lua_tostring(L,-1));

		// sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

			luaL_dostring(L, "if love.draw then love.draw() end");

		sf2d_end_frame();

		luaL_dostring(L, "love.graphics.present()");

	}

	lua_close(L);

	sftd_fini();
	sf2d_fini();

	return 0;

}