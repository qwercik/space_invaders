#pragma once

namespace space_invaders::game {
    class Bullet {
    public:
        Bullet(float x, float y, int target);
        float getX();
        float getY();
        void setY(float y);
        int getTarget();
        bool isValid();
        void invalidate();

        bool operator==(Bullet &other);

        static int checkXCollision(float x, float targetX);
        static int checkYCollision(float y, float targetY);

    private:
        float x;
        float y;
        int target;
        bool valid;
    };
}
