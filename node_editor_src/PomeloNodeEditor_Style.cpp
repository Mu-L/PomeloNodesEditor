// PomeloNodeEditor_Style.
#include "PomeloNodeEditor.h"

using namespace std;

namespace PNE {
	namespace system {
		void style_config::guistyle_cyan(ImVec4* colors) {
			colors[ImGuiCol_Text] =           ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			colors[ImGuiCol_WindowBg] =       ImVec4(0.0f, 0.24f, 0.32f, 1.0f);
			colors[ImGuiCol_TitleBg] =        ImVec4(0.0f, 1.0f, 1.0f, 0.0f);  // progress_bar 0.
			colors[ImGuiCol_TitleBgActive] =  ImVec4(0.0f, 1.0f, 1.0f, 0.0f);  // progress_bar 1.
			colors[ImGuiCol_Button] =         ImVec4(0.0f, 1.0f, 1.0f, 0.24f); // button 0.
			colors[ImGuiCol_ButtonHovered] =  ImVec4(0.0f, 1.0f, 1.0f, 0.58f); // button H
			colors[ImGuiCol_ButtonActive] =   ImVec4(0.0f, 1.0f, 1.0f, 0.76f); // button 1.
			colors[ImGuiCol_CheckMark] =      ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.0f, 1.0f, 1.0f, 0.1f);  // ��ͣ��ɫ.
		}

		void style_config::guistyle_orange(ImVec4* colors) {
			colors[ImGuiCol_Text] =           ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
			colors[ImGuiCol_WindowBg] =       ImVec4(0.2f, 0.1f, 0.0f, 1.0f);
			colors[ImGuiCol_TitleBg] =        ImVec4(1.0f, 0.5f, 0.0f, 0.0f);  // progress_bar 0.
			colors[ImGuiCol_TitleBgActive] =  ImVec4(1.0f, 0.5f, 0.0f, 0.0f);  // progress_bar 1.
			colors[ImGuiCol_Button] =         ImVec4(1.0f, 0.5f, 0.0f, 0.24f); // button 0.
			colors[ImGuiCol_ButtonHovered] =  ImVec4(1.0f, 0.5f, 0.0f, 0.58f); // button H
			colors[ImGuiCol_ButtonActive] =   ImVec4(1.0f, 0.5f, 0.0f, 0.76f); // button 1.
			colors[ImGuiCol_CheckMark] =      ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(1.0f, 0.5f, 0.0f, 0.1f);  // ��ͣ��ɫ.
		}

		void style_config::guistyle_pink(ImVec4* colors) {
			colors[ImGuiCol_Text] =           ImVec4(0.7f, 0.0f, 1.0f, 1.0f);
			colors[ImGuiCol_WindowBg] =       ImVec4(0.2f, 0.0f, 0.17f, 1.0f);
			colors[ImGuiCol_TitleBg] =        ImVec4(0.7f, 0.0f, 1.0f, 0.0f);  // progress_bar 0.
			colors[ImGuiCol_TitleBgActive] =  ImVec4(0.7f, 0.0f, 1.0f, 0.0f);  // progress_bar 1.
			colors[ImGuiCol_Button] =         ImVec4(0.7f, 0.0f, 1.0f, 0.24f); // button 0.
			colors[ImGuiCol_ButtonHovered] =  ImVec4(0.7f, 0.0f, 1.0f, 0.58f); // button H
			colors[ImGuiCol_ButtonActive] =   ImVec4(0.7f, 0.0f, 1.0f, 0.76f); // button 1.
			colors[ImGuiCol_CheckMark] =      ImVec4(0.7f, 0.0f, 1.0f, 1.0f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.7f, 0.0f, 1.0f, 0.1f);  // ��ͣ��ɫ.
		}

		void style_config::StyleConfig_panel() {

			ImGuiStyle* config_style = &ImGui::GetStyle();
			ImVec4*     config_colors = config_style->Colors;

			ImGui::ColorEdit4(u8"�ı���ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_Text]));
			ImGui::ColorEdit4(u8"���ڱ�����ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_WindowBg]));
			ImGui::ColorEdit4(u8"��������ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_TitleBg]));
			ImGui::ColorEdit4(u8"���������ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_TitleBgActive]));
			ImGui::ColorEdit4(u8"��ť��ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_Button]));
			ImGui::ColorEdit4(u8"��ͣ��ť��ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_ButtonHovered]));
			ImGui::ColorEdit4(u8"��ť������ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_ButtonActive]));
			ImGui::ColorEdit4(u8"ѡ������ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_CheckMark]));
			ImGui::ColorEdit4(u8"��ͣ�򱳾���ɫ", reinterpret_cast<float*>(&config_colors[ImGuiCol_FrameBgHovered]));
		}
	}
}