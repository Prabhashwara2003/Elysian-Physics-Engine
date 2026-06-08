#include "CollisionDetecter.h"

bool CollisionDetecter::Detect(Collider2D& collider1, Collider2D& collider2) {
	CircleCollider* a = dynamic_cast<CircleCollider*>(&collider1);
	CircleCollider* b = dynamic_cast<CircleCollider*>(&collider2);
	if (a && b) {

		return CircleVsCircle(*a->circle, *b->circle);
	}

	BoxCollider* c = dynamic_cast<BoxCollider*>(&collider1);
	CircleCollider* d = dynamic_cast<CircleCollider*>(&collider2);
	if (a && b) {
		return CircleVsBox(*d->circle, *c->rectangle);
	}

	BoxCollider* e = dynamic_cast<BoxCollider*>(&collider2);
	CircleCollider* f = dynamic_cast<CircleCollider*>(&collider1);
	if (a && b) {
		return CircleVsBox(*f->circle, *e->rectangle);
	}

	BoxCollider* g = dynamic_cast<BoxCollider*>(&collider1);
	BoxCollider* h = dynamic_cast<BoxCollider*>(&collider2);	
	return BoxVsBox(*g->rectangle, *h->rectangle);
	

}

bool CollisionDetecter::CircleVsCircle(Circle& c1, Circle& c2) {
	return CircleCircle(c1, c2);
}

bool CollisionDetecter::CircleVsBox(Circle& circle, OrientedRectangle& rectangle) {
	return CircleOrientedRectangle(circle, rectangle);
}

bool CollisionDetecter::BoxVsBox(OrientedRectangle& box1, OrientedRectangle& box2) {
	return RectagleOrientedRectangle(box1, box2);
}
