# Space Invaders :space_invader:
3D adaptation of Space Invaders game

## In game controls

- :arrow_backward: :arrow_forward: | ship movement
- :arrow_up_small: :arrow_down_small: | camera control
- :regional_indicator_a: :regional_indicator_d: | ship rotation
- `SPACEBAR` | fire a projectile
- :mouse_three_button: movements | world rotation

## Build instructions
To build the game run the following commands:
```bash
$ mkdir build/
$ cd build/
$ cmake ..
$ make
```

To run the game you can use on of the following commands:
```bash
./space_invaders
make run
make run-mesa # Forces MESA version to minimal required, use this command if your graphics card is too old to support OpenGL in version 3.3
```

