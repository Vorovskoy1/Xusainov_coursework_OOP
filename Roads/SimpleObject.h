#pragma once

namespace Roads {
	using namespace System::Drawing;

	// Простой объект
	ref class SimpleObject {
	protected:
		Point pos; // Позиция на поле
		Brush^ br; // Цвет отрисовки
	public:

		// Геттеры - сеттеры
		Point getPos() {
			return pos;
		}

		Brush^ getColor() {
			return br;
		}

		void setPos(Point pos) {
			this->pos = pos;
		}

		void setColor(Brush^ br) {
			this->br = br;
		}

		// Конструктор
		SimpleObject(Point pos) {
			setPos(pos);
		}

		// Обновление состояния
		virtual void update(double dt) = 0;

		// Отрисовка
		virtual void draw(Graphics^ ctx, int size) = 0;
	};
}
