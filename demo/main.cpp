#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "PhysicsSystem.h"
#include "Collider2D.h"
#include "Rigidbody.h"
#include "Geometry2D.h"

using namespace elysian;

struct DemoObject {
    Rigidbody* rigidbody;
    Collider2D* collider;
    sf::Color color;
    std::unique_ptr<Circle> circleShape;
    std::unique_ptr<OrientedRectangle> boxShape;
    Shape type;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Physics Engine Demo");
    window.setFramerateLimit(60);

    PhysicsSystem physics;
    physics.SetGravity(vec2(0.0f, 9.8f));

    std::vector<std::unique_ptr<DemoObject>> objects;
    std::vector<std::unique_ptr<Rigidbody>> rigidbodies;
    std::vector<std::unique_ptr<Collider2D>> colliders;

    // Ground
    {
        auto rb = std::make_unique<Rigidbody>(vec2(640, 700), 0.0f, vec2(1, 1));
        rb->mass = 0.0f;
        rb->inverseMass = 0.0f;
        rb->isGravityOn = false;

        auto rect = std::make_unique<OrientedRectangle>(vec2(640, 700), vec2(600, 20), 0.0f);
        auto col = std::make_unique<BoxCollider>(rect.get(), rb->transform);
        col->rigidbody = rb.get();

        physics.AddRigidbody(rb.get());
        physics.AddCollider(col.get());

        auto obj = std::make_unique<DemoObject>();
        obj->rigidbody = rb.get();
        obj->collider = col.get();
        obj->color = sf::Color(100, 100, 100);
        obj->boxShape = std::move(rect);
        obj->type = Shape::box;

        rigidbodies.push_back(std::move(rb));
        colliders.push_back(std::move(col));
        objects.push_back(std::move(obj));
    }

    // Falling boxes
    for (int i = 0; i < 5; i++) {
        auto rb = std::make_unique<Rigidbody>(vec2(400 + i * 80, 200 - i * 60), 0.0f, vec2(1, 1));
        rb->bounciness = 0.3f;

        auto rect = std::make_unique<OrientedRectangle>(vec2(400 + i * 80, 200 - i * 60), vec2(25, 25), 0.0f);
        auto col = std::make_unique<BoxCollider>(rect.get(), rb->transform);
        col->rigidbody = rb.get();

        physics.AddRigidbody(rb.get());
        physics.AddCollider(col.get());

        sf::Color color(100 + i * 30, 50 + i * 20, 200 - i * 30);
        auto obj = std::make_unique<DemoObject>();
        obj->rigidbody = rb.get();
        obj->collider = col.get();
        obj->color = color;
        obj->boxShape = std::move(rect);
        obj->type = Shape::box;

        rigidbodies.push_back(std::move(rb));
        colliders.push_back(std::move(col));
        objects.push_back(std::move(obj));
    }

    // Falling circles
    for (int i = 0; i < 3; i++) {
        auto rb = std::make_unique<Rigidbody>(vec2(700 + i * 100, 100), 0.0f, vec2(1, 1));
        rb->bounciness = 0.5f;

        auto circle = std::make_unique<Circle>(vec2(700 + i * 100, 100), 25.0f);
        auto col = std::make_unique<CircleCollider>(circle.get(), rb->transform);
        col->rigidbody = rb.get();

        physics.AddRigidbody(rb.get());
        physics.AddCollider(col.get());

        sf::Color color(200, 100 + i * 50, 100);
        auto obj = std::make_unique<DemoObject>();
        obj->rigidbody = rb.get();
        obj->collider = col.get();
        obj->color = color;
        obj->circleShape = std::move(circle);
        obj->type = Shape::circle;

        rigidbodies.push_back(std::move(rb));
        colliders.push_back(std::move(col));
        objects.push_back(std::move(obj));
    }

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.033f) dt = 0.033f;

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }
        }

        physics.Step(dt);

        window.clear(sf::Color(30, 30, 30));

        for (auto& obj : objects) {
            if (obj->type == Shape::box) {
                auto& rect = *obj->boxShape;
                sf::RectangleShape shape(sf::Vector2f(rect.halfExtents.x * 2, rect.halfExtents.y * 2));
                shape.setOrigin(sf::Vector2f(rect.halfExtents.x, rect.halfExtents.y));
                shape.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
                shape.setRotation(sf::degrees(rect.rotation));
                shape.setFillColor(obj->color);
                window.draw(shape);
            } else if (obj->type == Shape::circle) {
                auto& circle = *obj->circleShape;
                sf::CircleShape shape(circle.radius);
                shape.setOrigin(sf::Vector2f(circle.radius, circle.radius));
                shape.setPosition(sf::Vector2f(circle.Position.x, circle.Position.y));
                shape.setFillColor(obj->color);
                window.draw(shape);
            }
        }

        window.display();
    }

    return 0;
}
