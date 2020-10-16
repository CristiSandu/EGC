#pragma once

#include <Component/SimpleScene.h>

class Laborator1 : public SimpleScene
{
	public:
		Laborator1();
		~Laborator1();

		void Init() override;

	private:
		std::string obiectNou;
		glm::vec3 scalaObj;
		int randomObj;
		glm::vec3 color;
		GLfloat degrees;
		
		glm::vec3 objects_pos;

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void changeColor(int nr);
		void changeObj(int nr);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
};
