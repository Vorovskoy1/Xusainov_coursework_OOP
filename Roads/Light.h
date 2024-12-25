#pragma once
#include "SimpleObject.h"

namespace Roads {
	using namespace System::Drawing;

	// Светофор
	ref class Light : public SimpleObject {
	private:
		double time; // Накопленное время
	public:

		// Геттеры - сеттеры
		double getTime() {
			return time;
		}

		void setTime(double time) {
			this->time = time;
		}

		// Конструктор
		Light(Point pos, int time) : SimpleObject(pos) {
			this->time = time;
			setColor(Brushes::Red);
		}

		// Обновление состояния
		void update(double dt) override {
			time += dt;

			// Если горит красный
			if (getColor() == Brushes::Red && time >= 5.0) {

				// Меняем на зеленый
				setColor(Brushes::Green);
				time = 0;
			}

			// Зеленый
			else if (getColor() == Brushes::Green && time >= 4.0) {

				// Меняем на желтый
				setColor(Brushes::Yellow);
				time = 0;
			}

			// Желтый
			else if (getColor() == Brushes::Yellow && time >= 1.0) {

				// Меняем на красный
				setColor(Brushes::Red);
				time = 0;
			}
		}

		// Отрисовка
		void draw(Graphics^ ctx, int size) override {
			ctx->FillEllipse(getColor(), Rectangle(pos.X * size + 1, pos.Y * size + 1, size - 2, size - 2));
		}
	};
}
