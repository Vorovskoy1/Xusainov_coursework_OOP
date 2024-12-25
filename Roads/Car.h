#pragma once
#include "SimpleObject.h"

namespace Roads {
	using namespace System::Drawing;

	// Машина
	ref class Car : public SimpleObject {
	private:
		Point speed; // В каком направлении движется
	public:

		// Геттеры - сеттеры
		Point getSpeed() {
			return speed;
		}

		void setSpeed(Point speed) {
			this->speed = speed;
		}

		Point getNextPos() {
			return Point(pos.X + speed.X, pos.Y + speed.Y);
		}

		// Конструктор
		Car(Point pos) : SimpleObject(pos) {
			if (pos.X == 0) {
				setSpeed(Point(1, 0));
			}
			else if (pos.Y == 0) {
				setSpeed(Point(0, 1));
			}
			else if (pos.X < pos.Y) {
				setSpeed(Point(0, -1));
			}
			else {
				setSpeed(Point(-1, 0));
			}
			setColor(Brushes::Brown);
		}

		// Обновление состояния
		void update(double dt) override {
			pos.X += speed.X;
			pos.Y += speed.Y;
		}

		// Проверка выхода за границы
		bool outOfBounds(int w, int h) {
			return pos.X < 0 || pos.X >= w || pos.Y < 0 || pos.Y >= h;
		}

		// Отрисовка
		void draw(Graphics^ ctx, int size) override {
			ctx->FillRectangle(getColor(), Rectangle(pos.X * size + 1, pos.Y * size + 1, size - 1, size - 1));
		}
	};
}
