#pragma once

namespace space_invaders::game {
    class Spaceship {
    public:
        Spaceship(int health, int gridWidth, float speed);
        float getX();
        float getY();
        float getCooldown();
        void setCooldown(float cooldown);
        bool isAlive();
        void modifyHealth(int value);
        void setDirection(int direction);
        void modifyDirection(int modificator);
        void move(float time);

    private:
        int gridWidth;
        float x;
        const float y;
        float speed;
        int direction;
        int health;
        float cooldown;
    };
}
