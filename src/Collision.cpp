#include "Collision.h"

void Collision::checkCollision(std::vector<Ball*>& balls)
{
    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = i + 1; j < balls.size(); j++)
        {
            Ball* a = balls[i];
            Ball* b = balls[j];

            // Direction from ball A to ball B
            sf::Vector2f normal = b->midpoint - a->midpoint;

            float distanceSquared =
                normal.x * normal.x +
                normal.y * normal.y;

            float radiusSum = a->radius + b->radius;

            if (distanceSquared < radiusSum * radiusSum)
            {
                float distance = std::sqrt(distanceSquared);

                // Avoid divide by zero if balls are exactly at same position
                if (distance == 0.0f)
                {
                    normal = sf::Vector2f(1.0f, 0.0f);
                    distance = 1.0f;
                }
                else
                {
                    // Normalize collision direction
                    normal.x /= distance;
                    normal.y /= distance;
                }

                // Relative velocity
                sf::Vector2f relativeVelocity = b->velocity - a->velocity;

                // How fast they are moving along the collision normal
                float velocityAlongNormal =
                    relativeVelocity.x * normal.x +
                    relativeVelocity.y * normal.y;

                // If they are already moving away, don't apply impulse
                if (velocityAlongNormal > 0)
                    continue;

                // Bounciness
                float restitution = 0.8f;

                // Masses
                float massA = a->mass;
                float massB = b->mass;

                float inverseMassA = 1.0f / massA;
                float inverseMassB = 1.0f / massB;

                // Impulse scalar
                float impulseMagnitude =
                    -(1.0f + restitution) * velocityAlongNormal /
                    (inverseMassA + inverseMassB);

                // Impulse vector
                sf::Vector2f impulse = impulseMagnitude * normal;

                // Apply impulse
                a->velocity -= inverseMassA * impulse;
                b->velocity += inverseMassB * impulse;

                // Positional correction to stop balls sticking together
                float penetration = radiusSum - distance;

                float percent = 1.0f; // correction strength
                float slop = 0.01f;   // small allowed overlap

                sf::Vector2f correction =
                    std::max(penetration - slop, 0.0f) /
                    (inverseMassA + inverseMassB) *
                    percent *
                    normal;

                a->position -= inverseMassA * correction;
                b->position += inverseMassB * correction;
            }
        }
    }
}

void Collision::checkBallRect(Ball* ball, Rectangle* rect)
{
    // 1. Find the closest point on the rect to the ball center
    float closestX = std::max(rect->position.x,
        std::min(ball->midpoint.x, rect->position.x + rect->width));
    float closestY = std::max(rect->position.y,
        std::min(ball->midpoint.y, rect->position.y + rect->height));

    // 2. Vector from closest point to ball center
    sf::Vector2f delta = ball->midpoint - sf::Vector2f(closestX, closestY);
    float distSq = delta.x * delta.x + delta.y * delta.y;

    if (distSq >= ball->radius * ball->radius)
        return; // No collision

    float distance = std::sqrt(distSq);
    sf::Vector2f normal;

    // 3. Special case: ball center is INSIDE the rectangle
    if (distance == 0.0f)
    {
        // Find the nearest edge and use that as the push-out direction
        float distLeft = ball->midpoint.x - rect->position.x;
        float distRight = (rect->position.x + rect->width) - ball->midpoint.x;
        float distTop = ball->midpoint.y - rect->position.y;
        float distBottom = (rect->position.y + rect->height) - ball->midpoint.y;

        float minDist = std::min({ distLeft, distRight, distTop, distBottom });

        if (minDist == distLeft)   normal = { -1.f,  0.f };
        else if (minDist == distRight)  normal = { 1.f,  0.f };
        else if (minDist == distTop)    normal = { 0.f, -1.f };
        else                            normal = { 0.f,  1.f };

        distance = minDist; // penetration depth
    }
    else
    {
        normal = delta / distance; // normalized push direction
    }

    // 4. Positional correction — push ball out of rect
    float penetration = ball->radius - distance;
    ball->position += normal * penetration;

    // 5. Reflect velocity along the collision normal (with restitution)
    float velAlongNormal = ball->velocity.x * normal.x + ball->velocity.y * normal.y;

    if (velAlongNormal < 0.f) // only resolve if moving toward rect
    {
        float restitution = 0.8f;
        ball->velocity -= (1.f + restitution) * velAlongNormal * normal;
    }
}