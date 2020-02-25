-- The main boot script.
-- This code is licensed under the MIT Open Source License.

-- Copyright (c) 2018-2020
--    Jeremy S. Postelnek - jeremy.postelnek@gmail.com
--    Logan Hickok-Dickson - notquiteapex@gmail.com
-- Copyright (c) 2016 Ruairidh Carmichael - ruairidhcarmichael@live.co.uk

-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:

-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.

-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

-- 3DS and Switch can't load external C libraries,
-- so we need to prevent require from searching for them
package.path = "./?.lua;./?/init.lua"
package.cpath = "./?.lua;./?/init.lua"

-- make sure love exists
local love = require("love")

local config =
{
    identity = "SuperGame",
    appendidentity = false,
    version = "2.0.0",
    console = false,

    modules =
    {
        audio = true,
        data = true,
        event = true,
        font = true,
        graphics = true,
        image = true,
        joystick = true,
        keyboard = true,
        math = true,
        mouse = true,
        physics = true,
        sound = true,
        system = true,
        thread = true,
        timer = true,
        touch = true,
        video = true,
        window = true
    },

    -- Anything from here after in the config
    -- is only included for legacy purposes

    accelerometerjoystick = true,
    externalstorage = false,

    gammacorrect = true,

    audio =
    {
        mixwithsystem = true
    },

    window =
    {
        title = "Untitled",
        icon = nil,

        width = 1280,
        height = 720,

        borderless = false,
        resizable = false,

        minwidth = 1,
        minheight = 1,

        fullscreen = false,
        fullscreentype = "desktop",

        vsync = 1,
        msaa = 0,

        depth = nil,
        stencil = nil,

        highdpi = false,

        x = nil,
        y = nil,
    }
}

function love.createhandlers()
    love.handlers = setmetatable({
        keypressed = function (key)
            if love.keypressed then
                return love.keypressed(key)
            end
        end,
        keyreleased = function (key)
            if love.keyreleased then
                return love.keyreleased(key)
            end
        end,
        mousemoved = function (x,y,dx,dy,t)
            if love.mousemoved then
                return love.mousemoved(x,y,dx,dy,t)
            end
        end,
        mousepressed = function (x, y, button)
            if love.mousepressed then
                return love.mousepressed(x, y, button)
            end
        end,
        mousereleased = function (x, y, button)
            if love.mousereleased then
                return love.mousereleased(x, y, button)
            end
        end,
        joystickpressed = function (joystick, button)
            if love.joystickpressed then
                return love.joystickpressed(joystick, button)
            end
        end,
        joystickreleased = function (joystick, button)
            if love.joystickreleased then
                return love.joystickreleased(joystick, button)
            end
        end,
        joystickaxis = function (joystick, axis, value)
            if love.joystickaxis then
                return love.joystickaxis(joystick, axis, value)
            end
        end,
        joystickhat = function (joystick, hat, value)
            if love.joystickhat then
                return love.joystickhat(joystick, hat, value)
            end
        end,
        joystickadded = function(joystick)
            if love.joystickadded then
                return love.joystickadded(joystick)
            end
        end,
        joystickremoved = function(joystick)
            if love.joystickremoved then
                return love.joystickremoved(joystick)
            end
        end,
        gamepadpressed = function (joystick, button)
            if love.gamepadpressed then
                return love.gamepadpressed(joystick, button)
            end
        end,
        gamepadreleased = function (joystick, button)
            if love.gamepadreleased then
                return love.gamepadreleased(joystick, button)
            end
        end,
        gamepadaxis = function (joystick, axis, value)
            if love.gamepadaxis then
                return love.gamepadaxis(joystick, axis, value)
            end
        end,
        textinput = function(text)
            if love.textinput then
                return love.textinput(text)
            end
        end,
        touchpressed = function(id, x, y, pressure)
            if love.touchpressed then
                return love.touchpressed(id, x, y, pressure)
            end
        end,
        touchreleased = function(id, x, y, pressure)
            if love.touchreleased then
                return love.touchreleased(id, x, y, pressure)
            end
        end,
        touchmoved = function(id, x, y, pressure)
            if love.touchmoved then
                return love.touchmoved(id, x, y, pressure)
            end
        end,
        focus = function (focus)
            if love.focus then
                return love.focus(focus)
            end
        end,
        visible = function (visible)
            if love.visible then
                return love.visible(visible)
            end
        end,
        quit = function ()
            return
        end,
        threaderror = function (t, err)
            if love.threaderror then return love.threaderror(t, err) end
        end,
        lowmemory = function ()
            collectgarbage()
            if love.lowmemory then return love.lowmemory() end
        end
    }, {
        __index = function(self, name)
            error('Unknown event: ' .. tostring(name))
        end,
    })
end

local screens = {
    ["Switch"] = {nil},
    ["3DS"] = {"top", "top", "bottom"}
}

function love.run()
    if love.load then
        love.load()
    end

    local delta = 0

    return function()
        if love.event and love.event.pump then
            love.event.pump()

            for name, a, b, c, d, e, f in love.event.poll() do
                if name == "quit" then
                    if not love.quit or not love.quit() then
                        return a or 0
                    end
                end
                love.handlers[name](a, b, c, d, e, f)
            end
        end

        if love.timer then
            delta = love.timer.step()
        end

        if love.update then
            love.update(delta)
        end

        if love.graphics then
            love.graphics.clear(love.graphics.getBackgroundColor())

            for display = 1, love.window.getDisplayCount() do
                love.graphics.setScreen(display)

                if love.draw then
                    local screen = screens[love._console_name][display]
                    love.draw(screen)
                end
            end

            love.graphics.present()
        end

        if love.timer then
            love.timer.sleep(0.001)
        end
    end
end

function love.errorhandler(message)
    message = tostring(message)

    message = message:gsub("^(./)", "")

    local err = {}

    table.insert(err, message .. "\n")

    if love.audio then
        love.audio.stop()
    end

    local trace = debug.traceback()

    for l in trace:gmatch("(.-)\n") do
        if not l:match("boot.lua") then
            l = l:gsub("stack traceback:", "Traceback:\n")
            table.insert(err, l)
        end
    end

    local realError = table.concat(err, "\n")
    realError = realError:gsub("\t", "")
    realError = realError:gsub("%[string \"(.-)\"%]", "%1")

    -- MAKE A COPY FOR THE CRASH LOG --

    local copy = err
    table.insert(copy, "\nLöve Potion " .. love._potion_version .. " (API " .. love._version .. ")")

    local dateTime = os.date("%c")
    table.insert(copy, "\nDate and Time: " .. dateTime)
    table.insert(copy, "\nA log has been saved to " .. love.filesystem.getSaveDirectory() .. "crash.txt")

    -----------------------------------

    local fullError = table.concat(err, "\n")

    love.filesystem.write("crash.txt", fullError)

    if not love.window.isOpen() then
        return
    end

    local function draw()
        if love.graphics then
            love.graphics.clear(0.35, 0.62, 0.86)

            for display = 1, love.window.getDisplayCount() do
                love.graphics.setScreen(display) --just to clear it

                if display == 1 then
                    -- render our error message
                    -- love.graphics.print(msg, 10, 10)
                end
            end

            love.graphics.present()
        end
    end

    return function()
        if love.event then
            love.event.pump()

            for name, a, b, c, d, e, f in love.event.poll() do
                if name == "quit" then
                    return 1
                elseif name == "gamepadpressed" and b == "start" then
                    return 1
                end
            end
        end

        draw()

        if love.timer then
            love.timer.sleep(0.1)
        end
    end
end

love.errhand = love.errorhandler

--################--
-- BOOT THE GAME! --
--################--
local function error_printer(msg, layer)
    trace = debug.traceback("Error: " .. tostring(msg), 1 + (layer or 1))
    trace = trace:gsub("\n[^\n]+$", "")

    file = io.open("crash.txt", "w")
    file:write(trace)
    file:close()
end

function love.boot()
    -- Load the LOVE filesystem module, its absolutely needed
    require("love.filesystem")

    -- We can't throw any errors just yet because we want to see if we can
    -- load and use conf.lua in case the user doesn't want to use certain
    -- modules, but we also can't error because graphics haven't been loaded.
    local confok, conferr

    if love.filesystem.getInfo("conf.lua") then
        confok, conferr = pcall(require, "conf")

        if confok and love.conf then
            confok, conferr = pcall(love.conf, config)
        end
    end

    -- Set the game identity for saving.
    love.filesystem.setIdentity(config.identity)

    -- Modules to load
    local modules =
    {
        "window",
        "event",
        "joystick",
        "timer",
        "graphics"
    }

    -- Load them all!
    for i, v in ipairs(modules) do
        if config.modules[v] then
            require("love." .. v)
        end
    end

    if love.event then
        love.createhandlers()
    end

    -- Take our first step.
    if love.timer then
        love.timer.step()
    end

    -- Now we can throw any errors from `conf.lua`.
    if not confok and conferr then
        error(conferr)
    end

    --[[local __defaultFont = love.graphics.newFont()
    love.graphics.setFont(__defaultFont)]]

    if love.filesystem.getInfo("main.lua") then
        -- Try to load `main.lua`.
        require("main")
    else
        -- If there's no game to load then we'll just load up something on the
        -- screen to tell the user that there's NO GAME!
        --love._nogame()
    end
end

return function()
    local func
    local inerror = false

    local function deferErrhand(...)
        local errhand = love.errhandler or love.errhand
        local handler = (not inerror and errhand) or error_printer

        inerror = true
        func = handler(...)
    end

    local function earlyInit()
        local result = xpcall(love.boot, error_printer)

        -- quit immediately
        if not result then
            return 1
        end

        result = xpcall(love._ensureApplicationType, deferErrhand)

        -- let errhand take over
        if not result then
            return
        end

        local main
        result, main = xpcall(love.run, deferErrhand)

        if result then
            func = main
        end
    end

    func = earlyInit

    while func do
        local _, retval = xpcall(func, deferErrhand)

        if retval then
            return retval
        end

        coroutine.yield()
    end

    return 1
end
