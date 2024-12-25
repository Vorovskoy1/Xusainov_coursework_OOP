#pragma once
#include <cassert>
#include "Car.h"
#include "Light.h"

namespace Roads {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		List<Car^>^ cars; // Машины
		List<Light^>^ lights; // Светофоры
		Random^ rd; // Счетчик случайных чисел
		double pCreate = 0.3; // Вероятность создания новой машины

		// Клетки по которым создаются машины
		Point up = Point(7, 0);
		Point left = Point(0, 7);
		Point right = Point(15, 6);
		Point down = Point(8, 13);

		int size = 25; // Размер одной клетки
		Graphics^ ctx; // Контекст для рисования

		// Перекресток дорог
		array<Point>^ crossroads;

		// Конструктор
		MyForm(void)
		{
			InitializeComponent();
			rd = gcnew Random();
			crossroads = gcnew array<Point>(4);
			crossroads[0] = Point(7, 6);
			crossroads[1] = Point(8, 6);
			crossroads[2] = Point(7, 7);
			crossroads[3] = Point(8, 7);
			reset();
			testClasses();
		}

		// Отрисовка модели
		void draw() {

			// Создаем битовую карту
			Bitmap^ buffer = gcnew Bitmap(pictureBox->Width, pictureBox->Height);
			ctx = Graphics::FromImage(buffer);

			// Закрашиваем все белым цветом
			ctx->FillRectangle(gcnew SolidBrush(Color::White), 0, 0,
				pictureBox->Width, pictureBox->Height);

			// Отрисовка дорог
			// Горизонталь
			ctx->FillRectangle(Brushes::DarkGray, Rectangle(1, 6 * size + 1, pictureBox->Width - 1, 2 * size - 1));

			// Вертикаль
			ctx->FillRectangle(Brushes::DarkGray, Rectangle(7 * size + 1, 1, 2 * size - 1, pictureBox->Height - 1));

			// Клеточное поле
			// Горизонтали
			for (int i = 0; i < pictureBox->Height; i += size)
			{
				ctx->DrawLine(gcnew Pen(Color::Black), Point(0, i), Point(pictureBox->Width, i));
			}

			// Вертикали
			for (int i = 0; i < pictureBox->Width; i += size)
			{
				ctx->DrawLine(gcnew Pen(Color::Black), Point(i, 0), Point(i, pictureBox->Height));
			}

			// Отрисовка светофоров
			for (int i = 0; i < lights->Count; i++) {
				lights[i]->draw(ctx, size);
			}

			// Отрисовка машин
			for (int i = 0; i < cars->Count; i++) {
				cars[i]->draw(ctx, size);
			}

			// Заменяем
			pictureBox->Image = buffer;
		}

		// Точка на перекрестке
		bool isOnCrossroads(Point p) {
			for (int c = 0; c < crossroads->Length; c++) {
				if (p == crossroads[c])
					return true;
			}
			return false;
		}

		// Свободна ли клетка для движения
		bool isCellFree(Point pos, int ignoreIndex) {
			for (int k = 0; k < cars->Count; k++) {
				if (k != ignoreIndex && cars[k]->getPos() == pos) {
					return false;
				}
			}
			return true;
		}

		// Сброс параметров модели
		void reset() {
			cars = gcnew List<Car^>();
			lights = gcnew List<Light^>();
			cars->Add(gcnew Car(up));
			cars->Add(gcnew Car(left));
			cars->Add(gcnew Car(right));
			cars->Add(gcnew Car(down));
			lights->Add(gcnew Light(Point(6, 5), 0));
			lights->Add(gcnew Light(Point(9, 8), 5));
			draw();
		}

		// Тест классов
		void MyForm::testClasses() {

			// Тест Car
			Car^ testCar = gcnew Car(Point(0, 0));
			assert(testCar->getPos() == Point(0, 0));
			assert(testCar->getSpeed() == Point(1, 0));
			testCar->update(0);
			assert(testCar->getPos() == Point(1, 0));
			assert(!testCar->outOfBounds(10, 10));

			// Тест Light
			Light^ testLight = gcnew Light(Point(0, 0), 0);
			assert(testLight->getColor() == Brushes::Red);
			testLight->update(5.0);
			assert(testLight->getColor() == Brushes::Green);
			testLight->update(4.0);
			assert(testLight->getColor() == Brushes::Yellow);
			testLight->update(1.0);
			assert(testLight->getColor() == Brushes::Red);
			//MessageBox::Show("Все тесты пройдены успешно!");
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox;
	private: System::Windows::Forms::GroupBox^ groupBoxParams;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Button^ buttonStart;
	private: System::Windows::Forms::Button^ buttonReset;
	private: System::Windows::Forms::Button^ buttonExit;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Требуемый метод для поддержки конструктора — не изменяйте 
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			   this->groupBoxParams = (gcnew System::Windows::Forms::GroupBox());
			   this->buttonExit = (gcnew System::Windows::Forms::Button());
			   this->buttonReset = (gcnew System::Windows::Forms::Button());
			   this->buttonStart = (gcnew System::Windows::Forms::Button());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			   this->groupBoxParams->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // pictureBox
			   // 
			   this->pictureBox->Location = System::Drawing::Point(12, 12);
			   this->pictureBox->Name = L"pictureBox";
			   this->pictureBox->Size = System::Drawing::Size(535, 432);
			   this->pictureBox->TabIndex = 0;
			   this->pictureBox->TabStop = false;
			   // 
			   // groupBoxParams
			   // 
			   this->groupBoxParams->Controls->Add(this->label3);
			   this->groupBoxParams->Controls->Add(this->label2);
			   this->groupBoxParams->Controls->Add(this->label1);
			   this->groupBoxParams->Controls->Add(this->pictureBox3);
			   this->groupBoxParams->Controls->Add(this->pictureBox2);
			   this->groupBoxParams->Controls->Add(this->pictureBox1);
			   this->groupBoxParams->Controls->Add(this->buttonExit);
			   this->groupBoxParams->Controls->Add(this->buttonReset);
			   this->groupBoxParams->Controls->Add(this->buttonStart);
			   this->groupBoxParams->Location = System::Drawing::Point(553, 12);
			   this->groupBoxParams->Name = L"groupBoxParams";
			   this->groupBoxParams->Size = System::Drawing::Size(188, 432);
			   this->groupBoxParams->TabIndex = 1;
			   this->groupBoxParams->TabStop = false;
			   this->groupBoxParams->Text = L"Управление";
			   // 
			   // buttonExit
			   // 
			   this->buttonExit->Location = System::Drawing::Point(6, 388);
			   this->buttonExit->Name = L"buttonExit";
			   this->buttonExit->Size = System::Drawing::Size(176, 38);
			   this->buttonExit->TabIndex = 0;
			   this->buttonExit->Text = L"Выход";
			   this->buttonExit->UseVisualStyleBackColor = true;
			   this->buttonExit->Click += gcnew System::EventHandler(this, &MyForm::buttonExit_Click);
			   // 
			   // buttonReset
			   // 
			   this->buttonReset->Location = System::Drawing::Point(6, 78);
			   this->buttonReset->Name = L"buttonReset";
			   this->buttonReset->Size = System::Drawing::Size(176, 38);
			   this->buttonReset->TabIndex = 0;
			   this->buttonReset->Text = L"Сброс";
			   this->buttonReset->UseVisualStyleBackColor = true;
			   this->buttonReset->Click += gcnew System::EventHandler(this, &MyForm::buttonReset_Click);
			   // 
			   // buttonStart
			   // 
			   this->buttonStart->Location = System::Drawing::Point(6, 34);
			   this->buttonStart->Name = L"buttonStart";
			   this->buttonStart->Size = System::Drawing::Size(176, 38);
			   this->buttonStart->TabIndex = 0;
			   this->buttonStart->Text = L"Старт / Пауза";
			   this->buttonStart->UseVisualStyleBackColor = true;
			   this->buttonStart->Click += gcnew System::EventHandler(this, &MyForm::buttonStart_Click);
			   // 
			   // timer1
			   // 
			   this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::Color::DarkGray;
			   this->pictureBox1->Location = System::Drawing::Point(32, 136);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(36, 34);
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->BackColor = System::Drawing::Color::Red;
			   this->pictureBox2->Location = System::Drawing::Point(32, 176);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(36, 34);
			   this->pictureBox2->TabIndex = 1;
			   this->pictureBox2->TabStop = false;
			   // 
			   // pictureBox3
			   // 
			   this->pictureBox3->BackColor = System::Drawing::Color::Brown;
			   this->pictureBox3->Location = System::Drawing::Point(32, 216);
			   this->pictureBox3->Name = L"pictureBox3";
			   this->pictureBox3->Size = System::Drawing::Size(36, 34);
			   this->pictureBox3->TabIndex = 1;
			   this->pictureBox3->TabStop = false;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(74, 145);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(60, 16);
			   this->label1->TabIndex = 2;
			   this->label1->Text = L"- дорога";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(74, 185);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(79, 16);
			   this->label2->TabIndex = 2;
			   this->label2->Text = L"- светофор";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(74, 225);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(64, 16);
			   this->label3->TabIndex = 2;
			   this->label3->Text = L"- машина";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(755, 462);
			   this->Controls->Add(this->groupBoxParams);
			   this->Controls->Add(this->pictureBox);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			   this->Name = L"MyForm";
			   this->Text = L"Перекресток дорог";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			   this->groupBoxParams->ResumeLayout(false);
			   this->groupBoxParams->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		// Обновление светофоров
		for (int i = 0; i < lights->Count; i++) {
			lights[i]->update(timer1->Interval / 1000.0);
		}

		// Обновление машин
		for (int i = 0; i < cars->Count; i++) {

			// Следующая позиция машины
			Point next = cars[i]->getNextPos();

			// Свободна ли следующая клетка
			bool freeNext = isCellFree(next, i);

			// На перекрестке или нет
			bool crossPos = isOnCrossroads(cars[i]->getPos());

			// Следующая клетка на перекрестке или нет
			bool crossNext = isOnCrossroads(next);

			// Движется вертикально
			bool vert = cars[i]->getSpeed().X != 0;

			// Состояния первого светофора
			Light^ leftup = lights[0];

			// Зеленый
			if (leftup->getColor() == Brushes::Green && vert) {
				cars[i]->update(0);
			}

			// Красный, значит доезжаем до перекрестка или его уже проехали
			else if (leftup->getColor() == Brushes::Red && vert && !crossNext && freeNext) {
				cars[i]->update(0);
			}

			// Желтый, можем проехать перекресток, если уже на него наехали
			else if (leftup->getColor() == Brushes::Yellow && vert && (crossPos || !crossNext) && freeNext) {
				cars[i]->update(0);
			}

			// Состояния второго светофора
			Light^ rightdown = lights[1];

			// Зеленый
			if (rightdown->getColor() == Brushes::Green && !vert) {
				cars[i]->update(0);
			}

			// Красный, значит доезжаем до перекрестка или его уже проехали
			else if (rightdown->getColor() == Brushes::Red && !vert && !crossNext && freeNext) {
				cars[i]->update(0);
			}

			// Желтый, можем проехать перекресток, если уже на него наехали
			else if (rightdown->getColor() == Brushes::Yellow && !vert && (crossPos || !crossNext) && freeNext) {
				cars[i]->update(0);
			}
		}

		// Убираем машины, которые вышли за границы холста
		int j = 0;
		while (j < cars->Count) {
			if (cars[j]->outOfBounds(pictureBox->Width / size, pictureBox->Height / size)) {
				cars->RemoveAt(j);
			}
			else
				j++;
		}

		// Создаем новые машины если это возможно
		if (rd->NextDouble() <= pCreate) {

			// Выбираем случайным образом клетку
			int dir = rd->Next(4);
			Point pos;
			if (dir == 0) pos = up;
			else if (dir == 1) pos = left;
			else if (dir == 2) pos = right;
			else pos = down;

			// Проверяем, чтобы текущая клетка была свободна и её соседи
			// Так как машин не так много, то можно себе позволить не использовать доп. массив
			array<Point>^ dirs = gcnew array<Point>(5) {
				Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1), Point(0, 0)
			};
			bool flag = true;
			for (int i = 0; i < cars->Count && flag; i++) {
				for (int j = 0; j < dirs->Length && flag; j++) {
					int x = pos.X + dirs[j].X;
					int y = pos.Y + dirs[j].Y;

					// Эта клетка уже занята
					if (cars[i]->getPos().X == x && cars[i]->getPos().Y == y) {
						flag = false;
					}
				}
			}

			// Можно добавить новую машину
			if (flag) {
				cars->Add(gcnew Car(pos));
			}
		}

		// Отрисовка
		draw();
	}
	private: System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e) {

		// Старт / пауза
		if (timer1->Enabled) {
			timer1->Stop();
		}
		else {
			timer1->Start();
		}
	}
	private: System::Void buttonReset_Click(System::Object^ sender, System::EventArgs^ e) {

		// Сброс
		if (timer1->Enabled) {
			timer1->Stop();
		}
		reset();
	}
	private: System::Void buttonExit_Click(System::Object^ sender, System::EventArgs^ e) {

		// Выход
		if (timer1->Enabled) {
			timer1->Stop();
		}
		Application::Exit();
	}
	};
}
