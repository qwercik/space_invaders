#pragma once

namespace space_invaders::game {
    class Spaceship {
    public:
        Spaceship(int gridWidth, float speed);
        float getX();
        void setDirection(int direction);
        void modifyDirection(int modificator);
        void move(float time);

    private:
        int gridWidth;
        float x;
        float speed;
        int direction;
        int health;
    };
}
