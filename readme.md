# Grandmas Flowers
<img width="900" alt="Screenshot 2023-08-11 at 12 45 34 AM" src="https://github.com/imalexlee/Grandmas-Flowers/assets/106715298/01cc88bb-42cf-4538-883f-e817471ea406">
<img width="900" alt="Screenshot 2023-08-11 at 12 46 50 AM" src="https://github.com/imalexlee/Grandmas-Flowers/assets/106715298/b501c025-bff0-41bd-b6c9-4660f1796734">

### _Guide_

### The story of Grandmas Flowers is simple...

- Grandma requires 20 flowers before the end of the week
- There is a magical bee with an infinite stinger
- This bee guards the only flower patch in town

### Instructions

- To start the game, pause the game, or restart the game once you've lost or won, press START
- Once paused, you can press SELECT to start over
- Use UP, DOWN, LEFT, and RIGHT to move yourself around on the screen
- Avoid getting stung by the bee! You have 3 chances before you DIE
- Eating an apple gives you a sugar rush and makes you go twice as fast
- Pick up flowers while you run from the bee
- Before you get 10 flowers, walking around the top right of the screen (special area) will reduce your speed by half
- When you get at least 10 flowers, the entire top section of the field will slow you down (down to 25 pixels from top)
- When you get 20 flowers, you can get the heck up out of there and give grandma those flowers!

# Install and Run

1. #### Replace the highlighted path with the path of YOUR mGBA.app location from the inside of the folder

![Screenshot 2023-08-11 at 12 59 24 AM](https://github.com/imalexlee/Grandmas-Flowers/assets/106715298/0e71e1e3-fab1-4157-bbca-87a6273f838e)

2. #### Instal Docker desktop and run the aaaronic/gba-compiler provided with the given dockerfile. The image MUST be running for game to work!

3. #### **Open mGBA** - Run `open <YOUR PATH TO MGBA.APP> ./Project.gba` in the project directory or skip this step if using Visual Studio Code when building

4. #### **Build and Run** - Run `docker run --rm -it -v ${PWD}:/gba aaaronic/gba-compiler:1.2` in the project directory or press **cmd + shift + B** on Mac or **Ctrl + Shift + B** on Windows (If using Visual Studio Code)

5. #### **Clean** - Run `docker run --rm -it -v ${PWD}:/gba aaaronic/gba-compiler:1.2 bash -c 'cd /gba && make clean'` in the project directory or go to Terminal>Run Task...>clean (If using Visual Studio Code)